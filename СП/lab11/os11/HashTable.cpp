#include <Windows.h>
#include "HashTable.h"
#include <iostream>
#include <algorithm>
#include "Utilities.h"

#define SECOND 10000000


namespace HT    // HT API
{
#pragma region InnerFunctions

	byte* HashTable::GetMemorySpaceByIndex(int inIndex)
	{
		return (byte*)m_ElementsStartAddress + inIndex * (sizeof(Element) + this->m_MaxKeyLength + this->m_MaxValueLength);
	}

	Element* HashTable::ConvertPointerToElement(byte* inPointer)
	{
		Element* result = (Element*)inPointer;
		result->SetKeyPointer((char*)(inPointer + sizeof(Element)));
		result->SetValuePointer((char*)(inPointer + sizeof(Element) + m_MaxKeyLength));
		return result;
	}

	byte* HashTable::GetFreeMemoryForElement()
	{
		byte* pointer;
		int count_of_elements = 0;
		Element* temp_el;
		while (count_of_elements < this->m_Capacity)
		{
			pointer = GetMemorySpaceByIndex(count_of_elements);
			temp_el = (Element*)pointer;
			if (temp_el->GetKeyLength() == 0)
			{
				return pointer;
			}

			count_of_elements++;
		}
		return NULL;
	}

	byte* HashTable::FindElement(const char* inKey)
	{
		byte* pointer;
		int count_of_elements = 0;
		Element* tempEl;
		while (count_of_elements < this->m_Capacity)
		{
			pointer = GetMemorySpaceByIndex(count_of_elements);
			tempEl = ConvertPointerToElement(pointer);
			if (tempEl->GetKeyLength() != 0 && strcmp(inKey, tempEl->GetKey()) == 0)
			{
				return pointer;
			}

			count_of_elements++;
		}
		return NULL;
	}

#pragma endregion

#pragma region snap shots


	DWORD WINAPI HT::PeriodicSnapShot(LPVOID inHashTable)
	{
		HashTable* ht = (HashTable*)inHashTable;
		ht->m_TimerHandler = CreateWaitableTimer(NULL, false, ht->m_TimerName.c_str());
		if (ht->m_TimerHandler == NULL)
		{
			return 0;
		}

		long long timeToStartTimer = -ht->m_SnapShotIntervalInSec * SECOND;
		if (SetWaitableTimer(ht->m_TimerHandler, (LARGE_INTEGER*)&timeToStartTimer, ht->m_SnapShotIntervalInSec * 1000, NULL, NULL, false))
		{
			while (true)
			{
				if (ht->CheckMemoryForAccess())
				{
					WaitForSingleObject(ht->m_TimerHandler, INFINITE);
					printf("\nasync snapping...\n");
					ht->Snap();
				}
				else
				{
					printf("\nsnapshot timer is over");
					return 0;
				}
			}
		}
		return 0;

	}

	bool HashTable::Snap()
	{
		bool snapshot_success = true;

		if (!CheckMemoryForAccess())
		{
			snapshot_success = false;
			return snapshot_success;
		}

		HANDLE hm = CreateMutex(NULL, FALSE, m_MutexName.c_str());
		WaitForSingleObject(hm, INFINITE);

		if (!CheckMemoryForAccess())
		{
			ReleaseMutex(hm);
			snapshot_success = false;
			return snapshot_success;
		}

		int totalHtSize = sizeof(HashTable) + m_Capacity * (sizeof(Element) + m_MaxKeyLength + m_MaxValueLength);
		if (FlushViewOfFile(m_ElementsStartAddress, totalHtSize))
		{
			//getting time
			time(&this->m_LastSnapShotTime);
			char* buffer = new char[250];
			ctime_s(buffer, 250, &this->m_LastSnapShotTime);

			//formatting time
			std::tm* current_time = new tm();
			localtime_s(current_time, &this->m_LastSnapShotTime);
			strftime(buffer, 32, "_%d_%m_%Y__%H_%M_%S", current_time);
			delete current_time;
			printf("\nSync Snap at %s", buffer);

			//creating new file's path
			wstring new_file_snap = this->m_FileName;
			new_file_snap.replace(new_file_snap.find('.'), 0, Utilities::ConvertStringToWstring(buffer));

			delete[] buffer;

			//creating new snap file 
			HANDLE file_handler = NULL;
			file_handler = CreateFile(new_file_snap.c_str(), GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (file_handler == INVALID_HANDLE_VALUE)
			{
				snapshot_success = false;
				SetLastErrorMessage("fail with snap file opening");
			}
			else
			{
				//writing memory into created snap file 
				DWORD written = -1;
				int ht_size = sizeof(HashTable) + m_Capacity * (sizeof(Element) + m_MaxKeyLength + m_MaxValueLength);
				if (!WriteFile(file_handler, m_ElementsStartAddress, ht_size, &written, NULL))
				{
					SetLastErrorMessage("fail with snap file writing");
				}
			}

			ReleaseMutex(hm);
			return snapshot_success;
		}
		else
		{
			ReleaseMutex(hm);
			return false;
		}
	}

#pragma endregion

	HashTable::HashTable()
	{
		m_Capacity = 20;
		m_SnapShotIntervalInSec = 120;
		m_MaxKeyLength = 64;
		m_MaxValueLength = 64;
		m_LastSnapShotTime = 0;

		SetFileName(DEFAULT_FILE_NAME);

		m_CreatorPid = GetCurrentProcessId();

		m_FileHandler = NULL;
		m_FileMappingHandler = NULL;
		m_ElementsStartAddress = NULL;
		m_TimerHandler = NULL;
		m_TimerThreadHandler = NULL;

		InitHashTable();
	}

	HashTable::HashTable(int inCapacity, int inSecSnapshotInterval, int inMaxKeyLength, int inMaxValueLength, string inFileName)
	{
		m_Capacity = inCapacity;
		m_SnapShotIntervalInSec = inSecSnapshotInterval;
		m_MaxKeyLength = inMaxKeyLength;
		m_MaxValueLength = inMaxValueLength;

		SetFileName(inFileName);

		m_CreatorPid = GetCurrentProcessId();

		m_FileHandler = NULL;
		m_FileMappingHandler = NULL;
		m_ElementsStartAddress = NULL;
		m_TimerHandler = NULL;
		m_TimerThreadHandler = NULL;

		InitHashTable();
	}

	HashTable::~HashTable()
	{
		Close();
	}

#pragma region Getters and Setters
	int HashTable::GetCapacity() const
	{
		return m_Capacity;
	}

	int HashTable::GetCurrentSize() const
	{
		return m_CurrentSize;
	}

	int HashTable::GetSnapShotInterval() const
	{
		return m_SnapShotIntervalInSec;
	}

	void HashTable::ChangeSnapShotInterval(const int inSnapShotIntervalInSec)
	{
		m_SnapShotIntervalInSec = inSnapShotIntervalInSec;
	}

	int HashTable::GetMaxKeyLength() const
	{
		return m_MaxKeyLength;
	}

	void HashTable::SetMaxKeyLength(const int inMaxKeyLength)
	{
		m_MaxKeyLength = inMaxKeyLength;
	}

	int HashTable::GetMaxValueLength() const
	{
		return m_MaxValueLength;
	}

	void HashTable::SetMaxValueLength(const int inMaxValueLength)
	{
		m_MaxValueLength = inMaxValueLength;
	}

	void* HashTable::GetElementsStartAddress() const
	{
		return m_ElementsStartAddress;
	}

	time_t HashTable::GetLastSnapShotTime() const
	{
		return m_LastSnapShotTime;
	}

	string HashTable::GetLastErrorMessage() const
	{
		return m_LastErrorMessage;
	}

	wstring HashTable::GetFileName() const
	{
		return m_FileName;
	}

	void HashTable::SetLastErrorMessage(string inErrorMessage)
	{
		m_LastErrorMessage = inErrorMessage;
	}

	void HashTable::SetFileName(string inFileName)
	{
		m_FileName = wstring(Utilities::ConvertStringToWstring(Utilities::GetModulePath()));
		m_FileName += Utilities::ConvertStringToWstring(inFileName);
	}
#pragma endregion

	bool HashTable::InitHashTable()
	{
		bool success_init = false;
		if (success_init = OpenHashTableFromFile())
		{
			int totalHtSize = m_Capacity * (sizeof(HT::Element) + m_MaxKeyLength + m_MaxValueLength);

			bool valid_data = false;
			Element* element;
			for (int i = 0; i < m_Capacity; i++)
			{
				element = this->ConvertPointerToElement(this->GetMemorySpaceByIndex(i));
				if (element->GetKeyLength() > m_MaxKeyLength || element->GetValueLength() > m_MaxValueLength)
				{
					Clear();
					break;
				}
				else
				{
					if (element->GetKeyLength() > 0)
					{
						m_CurrentSize++;
					}
				}
			}
		}
		return success_init;
	}

	bool HashTable::OpenHashTableFromFile()
	{
		HANDLE file_handler = NULL;
		HANDLE file_mapping_handler = NULL;
		bool open_success = false;
		try
		{

			file_handler = CreateFile(m_FileName.c_str(), GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (file_handler == INVALID_HANDLE_VALUE)
			{
				throw "create file error";
			}
			m_FileHandler = file_handler;

			wstring general_prefix_name = wstring(m_FileName);
			std::replace(general_prefix_name.begin(), general_prefix_name.end(), '\\', '_');

			m_FileMapName = general_prefix_name + L"map";
			m_TimerName = general_prefix_name + L"timer";
			m_MutexName = general_prefix_name + L"mutex";

			file_mapping_handler = CreateFileMapping(file_handler, NULL, PAGE_READWRITE, 0, 0, m_FileMapName.c_str());
			if (!file_mapping_handler)
			{
				throw "create filemapping error";
			}
			m_FileMappingHandler = file_mapping_handler;

			LPVOID map_view_pointer = MapViewOfFile(file_mapping_handler, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			if (!map_view_pointer)
			{
				throw "mapping file error";
			}
			m_ElementsStartAddress = (byte*)map_view_pointer;

			DWORD timer_thread_id;
			m_TimerThreadHandler = NULL;
			m_TimerThreadHandler = CreateThread(NULL, NULL, HT::PeriodicSnapShot, this, NULL, &timer_thread_id);
			if (m_TimerThreadHandler == NULL)
			{
				throw "Creating snap shot thread error";
			}
			open_success = true;
		}
		catch (const char* e)
		{
			cout << "\nerror in HashTable::OpenHashTableFiles(): " << e << std::endl;
			CloseHandle(file_handler);
			CloseHandle(file_mapping_handler);
			SetLastErrorMessage(e);
			DWORD er = _Post_equals_last_error_::GetLastError();
			open_success = false;
		}
		catch (...)
		{
			SetLastErrorMessage("\n unhandled error in HashTable::OpenHashTableFiles()\n");
			cout << m_LastErrorMessage;
			open_success = false;
		}
		return open_success;
	}

	bool HashTable::CheckMemoryForAccess()
	{
		LPVOID buf = malloc(sizeof(HashTable));
		bool memory_available = false;
		if (ReadProcessMemory(GetCurrentProcess(), this, buf, sizeof(HashTable), NULL))
		{
			free(buf);
			memory_available = true;
		}
		else
		{
			free(buf);
			memory_available = false;
		}
		return memory_available;
	}

	bool HashTable::Close()
	{
		HANDLE mutex_handler = NULL;
		bool close_success = false;
		try
		{
			if (!CheckMemoryForAccess())
			{
				close_success = false;
				throw "have no access to the memory";
			}

			mutex_handler = CreateMutex(NULL, FALSE, this->m_MutexName.c_str());
			WaitForSingleObject(mutex_handler, INFINITE);

			if (!CheckMemoryForAccess())
			{
				ReleaseMutex(mutex_handler);
				close_success = false;
				throw "have no access to the memory";
			}

			if (!UnmapViewOfFile(this))
			{
				ReleaseMutex(mutex_handler);
				close_success = false;
				throw "unmapping file error";
			}
			if (m_CreatorPid == GetCurrentProcessId())
			{
				if (m_FileMappingHandler == NULL || !CloseHandle(m_FileMappingHandler))
				{
					close_success = false;
					throw "close file mapping";
				}

				if (m_FileHandler == NULL || !CloseHandle(m_FileHandler))
				{
					close_success = false;
					throw "close file";
				}

				if (m_TimerHandler != NULL)
				{
					if (!CancelWaitableTimer(m_TimerHandler))
					{
						close_success = false;
						throw "cancel timer";
					}
					if (!CloseHandle(m_TimerHandler))
					{
						close_success = false;
						throw "close timer";
					}
				}

				if (m_TimerThreadHandler == NULL || !CloseHandle(m_TimerThreadHandler))
				{
					close_success = false;
					throw "close timer thread";
				}

				this->m_FileHandler = NULL;
				this->m_FileMappingHandler = NULL;
				this->m_TimerHandler = NULL;
				this->m_TimerThreadHandler = NULL;
				close_success = true;

				Clear();
			}

			ReleaseMutex(mutex_handler);
		}
		catch (const char* e)
		{
			cout << "\nerror in HashTable::Close: " << e;
			SetLastErrorMessage(e);
			ReleaseMutex(mutex_handler);
			return false;
		}
		catch (...)
		{
			SetLastErrorMessage("unhandled error in HashTable::Close");
			cout << m_LastErrorMessage;
			ReleaseMutex(mutex_handler);
			return false;
		}
		return close_success;
	}


	bool HashTable::Insert(const char* inKey, int inKeyLength, const char* inValue, int inValueLength)
	{

		bool success_insert = false;
		if (!CheckMemoryForAccess())
		{
			success_insert = false;
			SetLastErrorMessage("HashTable::Insert - have no access for memory");
			throw GetLastErrorMessage();
		}

		HANDLE mutex_handler = CreateMutex(NULL, FALSE, this->m_MutexName.c_str());
		WaitForSingleObject(mutex_handler, INFINITE);

		if (!CheckMemoryForAccess())
		{
			ReleaseMutex(mutex_handler);
			success_insert = false;
			SetLastErrorMessage("HashTable::Insert - have no access for memory");
			throw GetLastErrorMessage();
		}

		byte* pointer = FindElement(inKey);
		if (pointer != NULL)
		{
			ReleaseMutex(mutex_handler);
			SetLastErrorMessage("HashTable::Insert - Hash Table already have such element");
			success_insert = false;
			throw GetLastErrorMessage();
		}
		pointer = GetFreeMemoryForElement();
		if (pointer == NULL)
		{
			ReleaseMutex(mutex_handler);
			SetLastErrorMessage("HashTable::Insert - can't give free memory range for new element");
			success_insert = false;
			throw GetLastErrorMessage();
		}
		else
		{
			Element* new_element = ConvertPointerToElement(pointer);
			string temp_string;
			temp_string = inKey;


			int new_size = min(inKeyLength, this->m_MaxKeyLength);
			temp_string.resize(new_size);
			new_element->ClearKey();
			new_element->SetKey(temp_string.c_str(), temp_string.length());

			temp_string = inValue;
			new_size = min(inValueLength, this->m_MaxKeyLength);
			temp_string.resize(new_size);
			new_element->ClearValue();
			new_element->SetValue(temp_string.c_str(), temp_string.length());

			ReleaseMutex(mutex_handler);
			success_insert = true;
			m_CurrentSize++;
		}

		return success_insert;
	}

	bool HashTable::Delete(const char* inElementKey)
	{
		bool success_deleting = false;
		if (!CheckMemoryForAccess())
		{
			success_deleting = false;
			SetLastErrorMessage("HashTable::Delete - have no access for memory");
			throw GetLastErrorMessage();
		}

		HANDLE hm = CreateMutex(NULL, FALSE, this->m_MutexName.c_str());
		WaitForSingleObject(hm, INFINITE);
		if (!CheckMemoryForAccess())
		{
			ReleaseMutex(hm);
			success_deleting = false;
			SetLastErrorMessage("HashTable::Delete - have no access for memory");
			throw GetLastErrorMessage();
		}
		byte* pointer = FindElement(inElementKey);
		if (pointer == NULL)
		{
			ReleaseMutex(hm);
			success_deleting = false;
			SetLastErrorMessage("HashTable::Delete - have not found such element");
			throw GetLastErrorMessage();
		}
		else
		{
			ZeroMemory(pointer, sizeof(Element) + this->m_MaxKeyLength + this->m_MaxValueLength);
			ReleaseMutex(hm);
			m_CurrentSize--;
			return true;
		}
	}

	const Element HashTable::Get(const char* inElementKey)
	{
		if (!CheckMemoryForAccess())
		{
			SetLastErrorMessage("HashTable::Get - have no access for memory");
			throw GetLastErrorMessage();
		}

		HANDLE hm = CreateMutex(NULL, FALSE, this->m_MutexName.c_str());
		WaitForSingleObject(hm, INFINITE);
		if (!CheckMemoryForAccess())
		{
			ReleaseMutex(hm);
			SetLastErrorMessage("HashTable::Get - have no access for memory");
			throw GetLastErrorMessage();
		}

		byte* pointer = FindElement(inElementKey);
		if (pointer == NULL)
		{
			ReleaseMutex(hm);
			SetLastErrorMessage("HashTable::Get - have not found such element");
			throw GetLastErrorMessage();
		}
		else
		{
			Element* result = ConvertPointerToElement(pointer);
			ReleaseMutex(hm);
			return *result;
		}
	}

	bool HashTable::Update(const char* inOldKey, const char* inNewValue, int inNewValueLength)
	{
		bool success_update = false;

		if (!CheckMemoryForAccess())
		{
			success_update = false;
			SetLastErrorMessage("HashTable::Update - have no access for memory");
			throw GetLastErrorMessage();
		}

		HANDLE hm = CreateMutex(NULL, FALSE, this->m_MutexName.c_str());
		WaitForSingleObject(hm, INFINITE);
		if (!CheckMemoryForAccess())
		{
			success_update = false;
			SetLastErrorMessage("HashTable::Update - have no access for memory");
			ReleaseMutex(hm);
			throw GetLastErrorMessage();
		}
		byte* pointer = FindElement(inOldKey);
		if (pointer == NULL)
		{
			success_update = false;
			SetLastErrorMessage("HashTable::Update - there is no such element for updating");
			ReleaseMutex(hm);
			throw GetLastErrorMessage();
		}
		else
		{
			Element* element = ConvertPointerToElement(pointer);

			string temp_string;
			temp_string = inNewValue;

			int new_size = min(inNewValueLength, this->m_MaxValueLength);
			temp_string.resize(new_size);
			element->ClearValue();
			element->SetValue(temp_string.c_str(), temp_string.length());

			ReleaseMutex(hm);
			success_update = true;
		}

		return success_update;
	}

	void HashTable::Clear()
	{
		int totalHtSize = m_Capacity * (sizeof(HT::Element) + m_MaxKeyLength + m_MaxValueLength);
		ZeroMemory(m_ElementsStartAddress, totalHtSize);
		m_CurrentSize = 0;
	}

	int HashTable::PrintAll()
	{
		if (!CheckMemoryForAccess())
		{
			SetLastErrorMessage("HashTable::PrintAll - have no access to the memory");
			throw GetLastErrorMessage();
		}
		HANDLE mutex_handler = CreateMutex(NULL, FALSE, this->m_MutexName.c_str());
		WaitForSingleObject(mutex_handler, INFINITE);
		if (!CheckMemoryForAccess())
		{
			SetLastErrorMessage("HashTable::PrintAll - have no access to the memory");
			ReleaseMutex(mutex_handler);
			throw GetLastErrorMessage();
		}
		byte* pointer;
		int count_of_elements = 0;
		Element* temp_el;
		while (count_of_elements < this->m_Capacity)
		{
			pointer = GetMemorySpaceByIndex(count_of_elements);
			temp_el = ConvertPointerToElement(pointer);

			if (temp_el->GetKeyLength() != 0)
			{
				Print(temp_el->GetKey());
				cout << endl;
			}
			count_of_elements++;
		}
		ReleaseMutex(mutex_handler);

		if (count_of_elements == 0)
		{
			cout << "Hash Table is empty\n";
		}

		return count_of_elements;
	}

	void HashTable::Print(const char* inElementKey)
	{
		byte* pointer = FindElement(inElementKey);
		if (pointer != NULL)
		{
			Element* result = ConvertPointerToElement(pointer);
			printf("key: %s, value: %s", result->GetKey(), result->GetValue());
		}
	}
};
