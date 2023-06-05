// HashTable.cpp : Определяет функции для статической библиотеки.
#include <Windows.h>
#include "pch.h"
#include "HashTable.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <time.h>

#define SECOND 10000000
using namespace std;

namespace HT 
{
	bool CompareMemory(void* mem1, void* mem2, int len) 
	{
		if (memcmp(mem1, mem2, len) == 0)
			return true;
		else
			return false;
	}
	const wchar_t* GetWC(const char* c)
	{
		const size_t cSize = strlen(c) + 1;
		wchar_t* wc = new wchar_t[cSize];
		size_t outSize;
		mbstowcs_s(&outSize, wc, cSize, c, cSize - 1);

		return wc;
	}

	void SetLastErrorMsg(HTHANDLE* ht, string msg) 
	{
		strcpy_s(ht->LastErrorMessage, msg.length() + 1, msg.c_str());
	}

	//return element in memory, which is pointed by pointer)
	//It takes memory region and return element strucutre, based on this memory region
	Element* CreateElementOnMemory(HTHANDLE* ht, byte* pointer) 
	{	
		Element* result = (Element*)pointer;
		result->key = (pointer + sizeof(Element));
		result->payload = (pointer + sizeof(Element) + ht->MaxKeyLength);
		return result;
	}

	//get pointer on free memory region in HT
	byte* GetFreeMemoryForElement(HTHANDLE* ht) 
	{
		byte* pointer = (byte*)(ht)+sizeof(HTHANDLE);
		int countOfElements = 0;
		Element* tempEl;
		while (countOfElements < ht->Capacity) 
		{
			pointer = (byte*)(ht)+sizeof(HTHANDLE) + countOfElements * (sizeof(Element) + ht->MaxKeyLength + ht->MaxPayloadLength);
			tempEl = (Element*)pointer;
			if (tempEl->keylength == 0) 
			{
				return pointer;
			}

			countOfElements++;
		}
		return NULL;
	}

	byte* FindElement(HTHANDLE* ht, void* key, int keyLen) 
	{
		byte* pointer = (byte*)(ht)+sizeof(HTHANDLE);
		int countOfElements = 0;
		Element* tempEl;
		while (countOfElements < ht->Capacity) 
		{
			pointer = (byte*)(ht)+sizeof(HTHANDLE) + countOfElements * (sizeof(Element) + ht->MaxKeyLength + ht->MaxPayloadLength);
			tempEl = CreateElementOnMemory(ht, pointer);
			if (tempEl->keylength != 0 && tempEl->keylength == keyLen 
				&& CompareMemory(tempEl->key,key,keyLen))
				return pointer;

			countOfElements++;
		}
		return NULL;
	}

	bool CheckMemotyForAccess(HTHANDLE* hthandle, bool dontNeedBossOpened = false) 
	{
		LPVOID buf = malloc(sizeof(HTHANDLE));
		if (!ReadProcessMemory(
			GetCurrentProcess(),
			hthandle,
			buf,
			sizeof(HTHANDLE),
			NULL
		)) 
		{
			free(buf);
			return false;
		}
		free(buf);
		if (hthandle->creatorPid == 0)
		{
			SetLastErrorMsg(hthandle, "MISTAKE! Table not available, closed)");
			return dontNeedBossOpened;	
		}
		return true;
	}

	DWORD WINAPI PeriodicSnapShot(LPVOID lpParam)
	{
		HTHANDLE* ht = (HTHANDLE*)lpParam;
		ht->hTimer = CreateWaitableTimer(NULL, false, ht->timerName);
		if (ht->hTimer == NULL) 
		{
			return 0;
		}
		long long timeToStartTimer = -ht->SecSnapshotInterval * SECOND;
		if (SetWaitableTimer(
			ht->hTimer,
			(LARGE_INTEGER*)&timeToStartTimer,
			ht->SecSnapshotInterval * 1000,
			NULL,
			NULL,
			false)) 
		{
			while (true) 
			{
				if (CheckMemotyForAccess((HTHANDLE*)ht)) 
				{
					WaitForSingleObject(ht->hTimer, INFINITE);
					printf("\nAsync snapping...");
					Snap(ht);
				}
				else 
				{
					printf("\nSnapshot timer is over(");
					return 0;
				}
			}
		}
		return 0;
	}

	BOOL HT::Snap         // выполнить Snapshot
	(
		const HTHANDLE* hthandle           // управление HT (File, FileMapping)
	) 
	{
		bool result = true;

		if (!CheckMemotyForAccess((HTHANDLE*)hthandle))
			return false;

		HANDLE hm = CreateMutex(NULL, FALSE, hthandle->mutexName);
		WaitForSingleObject(hm, INFINITE);

		if (!CheckMemotyForAccess((HTHANDLE*)hthandle)) 
		{
			ReleaseMutex(hm);
			return false;
		}
		int totalHtSize = sizeof(HTHANDLE);
		totalHtSize += hthandle->Capacity * (sizeof(Element) + hthandle->MaxKeyLength + hthandle->MaxPayloadLength);
		if (FlushViewOfFile(hthandle, totalHtSize)) 
		{
			//getting time
			time(&(((HTHANDLE*)hthandle)->lastsnaptime));
			char* buffer = new char[250];
			ctime_s(buffer, 250, &(((HTHANDLE*)hthandle)->lastsnaptime));
			//fprmatting time
			std::tm* ptm = new tm();
			localtime_s(ptm, &(((HTHANDLE*)hthandle)->lastsnaptime));
			strftime(buffer, 32, "_%d_%m_%Y__%H_%M_%S", ptm);
			delete ptm;
			printf("\nSync Snap at %s", buffer);
			//creating new file's path
			wstring newFile = wstring(hthandle->FileName);
			newFile.replace(newFile.find('.'), 0, GetWC(buffer));

			delete[] buffer;

			//creating new snap file 
			HANDLE hf = NULL;
			hf = CreateFile(
				newFile.c_str(),
				GENERIC_READ | GENERIC_WRITE,
				NULL,
				NULL,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL
			);
			if (hf == INVALID_HANDLE_VALUE) 
			{
				result = false;
				SetLastErrorMsg((HTHANDLE*)hthandle, "fail with snap file opening");
			}
			else 
			{
				//writing memory into created snap file 
				DWORD written = -1;
				int totalHtSize = sizeof(HTHANDLE);
				totalHtSize += hthandle->Capacity * (sizeof(Element) + hthandle->MaxKeyLength + hthandle->MaxPayloadLength);
				if (WriteFile(
					hf,
					hthandle,
					totalHtSize,
					&written,
					NULL
				)) 
				{
					CloseHandle(hf);
				}
				else 
				{
					SetLastErrorMsg((HTHANDLE*)hthandle, "fail with snap file writing");
				}
			}
			//delete &newFile;
			ReleaseMutex(hm);
			return result;
		}
		else 
		{
			ReleaseMutex(hm);
			return false;
		}
	}

	HTHANDLE::HTHANDLE() 
	{ }
	HTHANDLE::HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const wchar_t FileName[512]) 
	{
		this->Capacity = Capacity;
		this->SecSnapshotInterval = SecSnapshotInterval;
		this->MaxKeyLength = MaxKeyLength;
		this->MaxPayloadLength = MaxPayloadLength;
		wcscpy_s(this->FileName, _countof(this->FileName), FileName);
	}

	// for Get
	Element::Element(const void* key, int keylength) 
	{
		this->keylength = keylength;
		this->key = (void*)key;
	}
	// for Insert
	Element::Element(const void* key, int keylength, const void* payload, int  payloadlength) 
	{
		this->keylength = keylength;
		this->key = (void*)key;

		this->payloadlength = payloadlength;
		this->payload = (void*)payload;
	}

	//open map file and return hthandle, that was mapped there
	// != NULL успешное завершение  
	HTHANDLE* OpenHtFromFile     //  открыть HT             
	(
		const wchar_t    FileName[512],         // имя файла 
		int sizeOfFileIfCreating = 0
	) 
	{
		HANDLE hf = NULL;
		HANDLE hm = NULL;
		try 
		{
			hf = CreateFile(
				FileName,
				GENERIC_READ | GENERIC_WRITE,
				NULL,
				NULL,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL
			);
			if (hf == INVALID_HANDLE_VALUE)
				throw "create file error";

			int fileSize = GetFileSize(hf, NULL);
			if (sizeOfFileIfCreating!=0 && fileSize < sizeOfFileIfCreating) 
			{
				DWORD written;
				void* ht = malloc(sizeOfFileIfCreating);
				WriteFile(
					hf,
					ht,
					sizeOfFileIfCreating,
					&written,
					NULL
				);
				delete ht;
			}

			_wcslwr_s((wchar_t*)FileName, wcslen(FileName)+1);
			//map file name
			wstring mapFileName = wstring(FileName);
			std::replace(mapFileName.begin(), mapFileName.end(), '\\', '_');
			mapFileName += L"map";

			hm = CreateFileMapping(
				hf,
				NULL,
				PAGE_READWRITE,
				0, 0, mapFileName.c_str());
			if (!hm) throw "create filemapping error";

			LPVOID lp = MapViewOfFile(
				hm,
				FILE_MAP_ALL_ACCESS,
				0, 0, 0);
			if (!lp) throw "mapping file error";
			byte* pointer = (byte*)lp;

			HTHANDLE* ht = (HTHANDLE*)pointer;
			ht->Addr = pointer + sizeof(HTHANDLE);
			ht->File = hf;
			ht->FileMapping = hm;

			wcscpy_s(ht->FileName, _countof(ht->FileName), FileName);

			//mutex name
			wstring mutexName = wstring(FileName);
			std::replace(mutexName.begin(), mutexName.end(), '\\', '_');
			wcscpy_s(ht->mutexName, _countof(ht->mutexName), mutexName.c_str());
			//mpa file name
			wcscpy_s(ht->fileMapName, _countof(ht->fileMapName), mapFileName.c_str());
			//timer name
			wstring timerName = wstring(FileName);
			std::replace(timerName.begin(), timerName.end(), '\\', '_');
			timerName += L"timer";
			wcscpy_s(ht->timerName, _countof(ht->timerName), timerName.c_str());

			ht->creatorPid = GetCurrentProcessId();
			//timer
			DWORD   dwThreadId;

			ht->hTimerThread = NULL;
			ht->hTimerThread = CreateThread(
				NULL,                   // default security attributes
				0,                      // use default stack size  
				PeriodicSnapShot,       // thread function name
				ht,          // argument to thread function 
				0,                      // use default creation flags 
				&dwThreadId);   // returns the thread identifier 

			if (ht->hTimerThread == NULL)
			{
				throw "Creating snap shot thread error";
			}

			return ht;
		}
		catch (char* e) 
		{
			cout << "\nerror: " << e;
			CloseHandle(hf);
			CloseHandle(hm);
			DWORD er = _Post_equals_last_error_::GetLastError();
			er = er;
		}
		catch (const char* e) 
		{
			cout << "\nerror: " << e;
			CloseHandle(hf);
			CloseHandle(hm);
			DWORD er = _Post_equals_last_error_::GetLastError();
			er = er;
		}
		return NULL;
	}

	// != NULL успешное завершение  
	HTHANDLE* Create   //  создать HT             
	(
		int	  Capacity,					   // емкость хранилища
		int   SecSnapshotInterval,		   // переодичность сохранения в сек.
		int   MaxKeyLength,                // максимальный размер ключа
		int   MaxPayloadLength,            // максимальный размер данных
		const char  FileName[512]          // имя файла 
	) 
	{
		const wchar_t* wFileName = GetWC(FileName);
		HTHANDLE* ht = OpenHtFromFile(wFileName,Capacity * (MaxKeyLength + MaxPayloadLength + sizeof(Element)) + sizeof(HTHANDLE));
		if (ht == NULL) 
		{
			return NULL;
		}

		//clear memory, that may contains old elements
		int totalHtSize = 0;
		totalHtSize += Capacity * (sizeof(Element) + MaxKeyLength + MaxPayloadLength);
		ZeroMemory(ht->Addr, totalHtSize);

		ht->Capacity = Capacity;
		ht->SecSnapshotInterval = SecSnapshotInterval;
		ht->MaxKeyLength = MaxKeyLength;
		ht->MaxPayloadLength = MaxPayloadLength;
		ht->creatorPid = GetCurrentProcessId();

		return ht;
	}

	//open mapping file and return ith hthandle or return hthandle in already created virtual memory
	// != NULL успешное завершение  
	HTHANDLE* Open     //  открыть HT             
	(
		const char    FileName[512]         // имя файла 
	) 
	{
		const wchar_t* wFileName = GetWC(FileName);
		HTHANDLE* res = OpenHtFromFile(wFileName);
		if (res != NULL)
			return res;
		else 
		{
			try 
			{
				HANDLE hm;

				//map file name
				wstring mapFileName = wstring(wFileName);
				std::replace(mapFileName.begin(), mapFileName.end(), '\\', '_');
				mapFileName += L"map";
				_wcslwr_s((wchar_t*)mapFileName.c_str(), mapFileName.length()+1);
				hm = OpenFileMapping(
					FILE_MAP_ALL_ACCESS,   // read/write access
					FALSE,                 // do not inherit the name
					mapFileName.c_str());

				if (!hm) throw "create filemapping error";

				LPVOID lp = MapViewOfFile(
					hm,
					FILE_MAP_ALL_ACCESS,
					0, 0, 0);
				if (!lp) throw "mapping file error";
				return (HTHANDLE*)lp;
			}
			catch (char* e) 
			{
				cout << "\nerror: " << e;
			}
			catch (const char* e) 
			{
				cout << "\nerror: " << e;
			}
			return NULL;
		}
	}

	BOOL Close        // Snap и закрыть HT  и  очистить HTHANDLE
	(
		const HTHANDLE* hthandle           // управление HT (File, FileMapping)
	) 
	{
		HANDLE hm = NULL;
		try 
		{
			if (!CheckMemotyForAccess((HTHANDLE*)hthandle))
				return false;

			hm = CreateMutex(NULL, FALSE, hthandle->mutexName);
			WaitForSingleObject(hm, INFINITE);

			if (!CheckMemotyForAccess((HTHANDLE*)hthandle)) 
			{
				ReleaseMutex(hm);
				return false;
			}

			HANDLE map = hthandle->FileMapping;
			HANDLE file = hthandle->File;
			HANDLE timer = hthandle->hTimer;
			HANDLE timerThread = hthandle->hTimerThread;
			DWORD creatorPid = hthandle->creatorPid;

			if (creatorPid == GetCurrentProcessId()) 
			{
				((HTHANDLE*)hthandle)->File = NULL;
				((HTHANDLE*)hthandle)->FileMapping = NULL;
				((HTHANDLE*)hthandle)->hTimer = NULL;
				((HTHANDLE*)hthandle)->hTimerThread = NULL;
				((HTHANDLE*)hthandle)->creatorPid = 0;
			}
			if (!UnmapViewOfFile(hthandle)) throw "unmapping file error";
			if (creatorPid == GetCurrentProcessId()) 
			{
				if (map != NULL)
					if (!CloseHandle(map)) throw "close file mapping";
				if (file != NULL)
					if (!CloseHandle(file)) throw "close file";
				if (timer != NULL) 
				{
					if (!CancelWaitableTimer(timer)) throw "cancel timer";
					if (!CloseHandle(timer)) throw "close timer";
				}
				if (timerThread != NULL)
					if (!CloseHandle(timerThread)) throw "close timer thread";
			}
			ReleaseMutex(hm);
		}
		catch (const char* e) 
		{
			cout << "\nerror: " << e;
			SetLastErrorMsg((HTHANDLE*)hthandle, e);
			ReleaseMutex(hm);
			return false;
		}
		catch (...) 
		{
			SetLastErrorMsg((HTHANDLE*)hthandle, "some extra feil");
			ReleaseMutex(hm);
			return false;
		}
		return true;
	}	//  == TRUE успешное завершение   

	BOOL Insert      // добавить элемент в хранилище
	(
		const HTHANDLE* hthandle,            // управление HT
		const Element* element              // элемент
	) 
	{
		if (!CheckMemotyForAccess((HTHANDLE*)hthandle))
			return false;

		HANDLE hm = CreateMutex(NULL, FALSE, hthandle->mutexName);
		WaitForSingleObject(hm, INFINITE);

		if (!CheckMemotyForAccess((HTHANDLE*)hthandle)) 
		{
			ReleaseMutex(hm);
			return false;
		}
		if (element->keylength <= 0) 
		{
			SetLastErrorMsg((HTHANDLE*)hthandle, "Incorrect key len");

			ReleaseMutex(hm);
			return false;
		}
		byte* pointer = FindElement((HTHANDLE*)hthandle, element->key, element->keylength);
		if (pointer != NULL) 
		{
			SetLastErrorMsg((HTHANDLE*)hthandle, "There is such element for inserting");

			ReleaseMutex(hm);
			return false;
		}
		pointer = GetFreeMemoryForElement((HTHANDLE*)hthandle);
		if (pointer == NULL) 
		{
			SetLastErrorMsg((HTHANDLE*)hthandle, "There is no free places for insert(");
			ReleaseMutex(hm);
			return false;
		}
		else 
		{
			Element* newElement = CreateElementOnMemory((HTHANDLE*)hthandle, pointer);
			newElement->keylength = min(element->keylength, hthandle->MaxKeyLength);
			newElement->payloadlength = min(element->payloadlength, hthandle->MaxPayloadLength - 1);

			CopyMemory(newElement->key, element->key, newElement->keylength);
			CopyMemory(newElement->payload, element->payload, newElement->payloadlength);

			ReleaseMutex(hm);
			return true;
		}
	}	//  == TRUE успешное завершение 

	BOOL Delete      // удалить элемент в хранилище
	(
		const HTHANDLE* hthandle,            // управление HT (ключ)
		const Element* element              // элемент 
	) 
	{
		if (!CheckMemotyForAccess((HTHANDLE*)hthandle))
			return false;
		HANDLE hm = CreateMutex(NULL, FALSE, hthandle->mutexName);
		WaitForSingleObject(hm, INFINITE);
		if (!CheckMemotyForAccess((HTHANDLE*)hthandle)) 
		{
			ReleaseMutex(hm);
			return false;
		}
		byte* pointer = FindElement((HTHANDLE*)hthandle, element->key, element->keylength);
		if (pointer == NULL) 
		{
			SetLastErrorMsg((HTHANDLE*)hthandle, "There is no such element for deleting");
			ReleaseMutex(hm);
			return false;
		}
		else 
		{
			ZeroMemory(pointer, sizeof(Element) + hthandle->MaxKeyLength + hthandle->MaxPayloadLength);
			ReleaseMutex(hm);
			return true;
		}
	}	//  == TRUE успешное завершение 

	Element* Get     //  читать элемент в хранилище
	(
		const HTHANDLE* hthandle,            // управление HT
		const Element* element              // элемент 
	) 
	{
		if (!CheckMemotyForAccess((HTHANDLE*)hthandle))
			return NULL;
		HANDLE hm = CreateMutex(NULL, FALSE, hthandle->mutexName);
		WaitForSingleObject(hm, INFINITE);
		if (!CheckMemotyForAccess((HTHANDLE*)hthandle)) 
		{
			ReleaseMutex(hm);
			return NULL;
		}
		byte* pointer = FindElement((HTHANDLE*)hthandle, element->key, element->keylength);
		if (pointer == NULL) 
		{
			SetLastErrorMsg((HTHANDLE*)hthandle, "There is no such element for getting");
			ReleaseMutex(hm);
			return NULL;
		}
		else 
		{
			Element* result = CreateElementOnMemory((HTHANDLE*)hthandle, pointer);
			ReleaseMutex(hm);
			return result;
		}
	} 	//  != NULL успешное завершение 


	BOOL Update     //  именить элемент в хранилище
	(
		const HTHANDLE* hthandle,            // управление HT
		const Element* oldelement,          // старый элемент (ключ, размер ключа)
		const void* newpayload,          // новые данные  
		int             newpayloadlength     // размер новых данных
	) 
	{
		if (!CheckMemotyForAccess((HTHANDLE*)hthandle))
			return false;
		HANDLE hm = CreateMutex(NULL, FALSE, hthandle->mutexName);
		WaitForSingleObject(hm, INFINITE);
		if (!CheckMemotyForAccess((HTHANDLE*)hthandle)) 
		{
			ReleaseMutex(hm);
			return false;
		}
		byte* pointer = FindElement((HTHANDLE*)hthandle, oldelement->key,oldelement->keylength);
		if (pointer == NULL) 
		{
			SetLastErrorMsg((HTHANDLE*)hthandle, "There is no such element for updating");
			ReleaseMutex(hm);
			return false;
		}
		else 
		{
			oldelement = CreateElementOnMemory((HTHANDLE*)hthandle, pointer);
			newpayloadlength = min(newpayloadlength, hthandle->MaxPayloadLength);
			//((char*)newpayload)[newpayloadlength - 1] = '\0';
			CopyMemory(oldelement->payload, newpayload, newpayloadlength);
			((Element*)oldelement)->payloadlength = newpayloadlength;
			ReleaseMutex(hm);
			return true;
		}
	} 	//  != NULL успешное завершение 


	int PrintAll     // print all elements aand return their count
	(
		HTHANDLE* ht           // управление HT
	) 
	{
		if (!CheckMemotyForAccess((HTHANDLE*)ht))
			return -1;
		HANDLE hm = CreateMutex(NULL, FALSE, ht->mutexName);
		WaitForSingleObject(hm, INFINITE);
		if (!CheckMemotyForAccess((HTHANDLE*)ht)) 
		{
			ReleaseMutex(hm);
			return 0;
		}
		byte* pointer = (byte*)(ht)+sizeof(HTHANDLE);
		int countOfElements = 0;
		Element* tempEl;
		while (countOfElements < ht->Capacity) 
		{
			pointer = (byte*)(ht)+sizeof(HTHANDLE) + countOfElements * (sizeof(Element) + ht->MaxKeyLength + ht->MaxPayloadLength);
			tempEl = CreateElementOnMemory(ht, pointer);

			if (tempEl->keylength != 0) 
			{
				print(tempEl);
			}

			countOfElements++;
		}
		ReleaseMutex(hm);
		return countOfElements;
	}
	//  != NULL успешное завершение 

	char* GetLastHtError  // получить сообщение о последней ошибке
	(
		HTHANDLE* ht                         // управление HT
	) 
	{
		if (!CheckMemotyForAccess((HTHANDLE*)ht,true))
			return NULL;
		return ht->LastErrorMessage;
	}

	void print                               // распечатать элемент 
	(
		const Element* element              // элемент 
	) 
	{
		printf("\nelement value: %s, key: %s", (char*)element->payload, (char*)element->key);
	}

	int sum(int a, int b) 
	{
		return a + b;
	}
};