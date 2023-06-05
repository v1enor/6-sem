#include "pch.h"
#include "HT.h"
#include <Windows.h>
#include <algorithm>
#include<iomanip>
#include <iostream>

long g_lLocks{ 0 };
long g_lObjs{ 0 };

LPCWSTR  FriendlyName = L"HT.COM";
LPCWSTR  VerIndProg = L"HT";
LPCWSTR  ProgID = L"HT.1.0";

HANDLE Addr;

std::wstring getFileNameFromPath(const std::wstring& path)
{
	// Находим последний символ '/' или '\\', чтобы разделить путь и имя файла
	size_t pos = path.find_last_of(L"/\\");

	// Если такой символ не найден, возвращаем исходную строку
	if (pos == std::wstring::npos)
	{
		return path;
	}

	// Извлекаем имя файла
	return path.substr(pos + 1);
}


DWORD WINAPI SnapShotCycle(HTHANDLE* ht);

HT::HT()
	:m_refCount{0}
{
	InterlockedIncrement(&g_lObjs);
}

HT::~HT()
{
	InterlockedDecrement(&g_lObjs);
}

STDMETHODIMP HT::QueryInterface(const IID& riid, void** ppvObject)
{
	if(riid == IID_IUnknown || riid == IID_IHT)
	{
		*ppvObject = static_cast<IHT*>(this);
		AddRef();
		return S_OK;
	}

	*ppvObject = NULL;
	return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) HT::AddRef()
{
	return InterlockedIncrement(&m_refCount);
}

STDMETHODIMP_(ULONG) HT::Release()
{
	return InterlockedDecrement(&m_refCount);
}

STDMETHODIMP_(HTHANDLE*) HT::Create(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const std::wstring FileName)
{
	if (Capacity < 0 || SecSnapshotInterval < 0 || MaxKeyLength < 0 || MaxPayloadLength < 0)
	{
		std::cout << "Err param" << std::endl;
		return NULL;
	}

	HANDLE hf = CreateFile(FileName.c_str(),GENERIC_WRITE | GENERIC_READ, NULL, NULL,
		CREATE_NEW, FILE_ATTRIBUTE_NORMAL,NULL);
	if (hf == INVALID_HANDLE_VALUE)
	{
		std::cout << "Err create file" << std::endl;
		return NULL;
	}

	DWORD HTsize = sizeof(HTHANDLE) + Capacity * (MaxKeyLength + MaxPayloadLength + 2 * sizeof(int));
	HANDLE hm = CreateFileMapping(
		hf,
		NULL,
		PAGE_READWRITE,
		0, HTsize, NULL);
	if (!hm)
		return NULL;
	std::cout << "Open FileMapping: " << hm << std::endl;

	LPVOID lp = MapViewOfFile(
		hm,
		FILE_MAP_ALL_ACCESS | FILE_MAP_READ | FILE_MAP_WRITE,
		0, 0, 0);
	if (!lp)
		return NULL;
	std::cout << "Open MapViewOfFile: " << lp << std::endl;

	ZeroMemory(lp, HTsize);
	HTHANDLE *ht = new(lp) HTHANDLE(
		Capacity,
		SecSnapshotInterval,
		MaxKeyLength,
		MaxPayloadLength,
		FileName.c_str());

	ht->File = hf;
	ht->FileMapping = hm;
	ht->Addr = lp;
	ht->lastsnaptime = time(NULL);

	return ht;

}

STDMETHODIMP HT::Open(const std::wstring FileName)
{
	auto file = getFileNameFromPath(FileName);

	HANDLE hf = CreateFile(FileName.c_str(), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hf == INVALID_HANDLE_VALUE)
	{
		std::cout << _Post_equals_last_error_::GetLastError();
		return E_FAIL;
	}

	HANDLE hm = CreateFileMapping(hf, NULL, PAGE_READWRITE, 0, 0, file.c_str());
	if (!hm)
		return E_FAIL;

	std::cout << "Open FileMapping: " << hm << std::endl;

	LPVOID lp = MapViewOfFile(hm, FILE_MAP_ALL_ACCESS | FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);

	Addr = lp;
	if (!lp)
	{
		return E_FAIL;
	}
	std::cout << "Open MapViewOfFile: " << lp << std::endl;

	HTHANDLE* ht = (HTHANDLE*)lp;
	ht->File = hf;
	ht->FileMapping = hm;
	ht->Addr = lp;
	ht->Mutex = CreateMutex(NULL, FALSE, L"mutex");

	DWORD SnapShotThread = NULL;
	if (!(ht->SnapshotThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SnapShotCycle, ht, 0, &SnapShotThread))) 
		return E_FAIL;
	return S_OK;
}

STDMETHODIMP_(HTHANDLE*) HT::OpenExist(const std::wstring FileName)
{
	auto file = getFileNameFromPath(FileName);

	std::wcout << std::endl << FileName << std::endl << GenerateViewName(FileName.c_str()) << std::endl;

	HANDLE hm;
	HANDLE mutex = CreateMutex(NULL, FALSE, L"mutex");
	if (mutex == INVALID_HANDLE_VALUE)
	{
		std::cout << _Post_equals_last_error_::GetLastError() << std::endl;
		return NULL;
	}

	WaitForSingleObject(mutex, INFINITE);

	hm = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, file.c_str());
	if (!hm)
	{
		std::cout << _Post_equals_last_error_::GetLastError() << std::endl;
		return NULL;
	}

	LPVOID lp = MapViewOfFile(hm, FILE_MAP_ALL_ACCESS | FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
	Addr = lp;
	if (!lp)
	{
		std::cout << _Post_equals_last_error_::GetLastError() << std::endl;
		return NULL;
	}

	ReleaseMutex(mutex);
	HTHANDLE* ht = (HTHANDLE*)lp;
	ht->FileMapping = hm;
	ht->Addr = lp;
	ht->Mutex = mutex;

	return ht;
}

STDMETHODIMP HT::Snap(HTHANDLE* hthandle) {
	std::cout << "-----SNAPSHOT WAIT-----" << std::endl;
	WaitForSingleObject(hthandle->Mutex, INFINITE);
	if (!FlushViewOfFile(hthandle->Addr, NULL)) {
		SetErrorMessage(hthandle, "Snapshot error", 15);
		ReleaseMutex(hthandle->Mutex);
		return E_INVALIDARG;
	}
	std::cout << "-----SNAPSHOT-----" << std::endl;
	hthandle->lastsnaptime = time(NULL);
	ReleaseMutex(hthandle->Mutex);
	return S_OK;
}

STDMETHODIMP HT::Close(const HTHANDLE* hthandle)
{
	HANDLE mapping, file, mutex;

	memcpy(&mapping, &hthandle->FileMapping, sizeof(HANDLE));
	memcpy(&file, &hthandle->File, sizeof(HANDLE));
	memcpy(&mutex, &hthandle->Mutex, sizeof(HANDLE));

	TerminateThread(hthandle->SnapshotThread, 0);

	if (!CloseHandle(mapping))
		return E_INVALIDARG;
	if (!CloseHandle(file))
		return E_INVALIDARG;
	if (!CloseHandle(mutex))
		return E_INVALIDARG;
	return S_OK;
}

STDMETHODIMP HT::CloseExist(const HTHANDLE* hthandle) {
	if (!UnmapViewOfFile(hthandle->Addr))
	{
		return E_INVALIDARG;
	}
	return S_OK;
}

STDMETHODIMP HT::Insert(HTHANDLE* hthandle, Element* element)
{
	if (!CheckParmLength(hthandle, element))
	{
		std::cout << "You param length is incorect" << std::endl;
		return E_INVALIDARG;
	}
	WaitForSingleObject(hthandle->Mutex, INFINITE);
	bool inserted = false;

	if (hthandle->N != hthandle->Capacity)
	{
		for (int i = 0, j = HashFunction(element, hthandle->Capacity, 0);
			i != hthandle->Capacity && !inserted;  j = Next_hash(j, hthandle->Capacity, ++i)) {
			Element* elFromHT = GetElementFromHT(hthandle, j);
			if (elFromHT != NULL && !IsDeleted(elFromHT)) {
				if (EqualElementKeys(elFromHT, element)) {
					SetErrorMessage(hthandle, "Key exists\n", 12);
					ReleaseMutex(hthandle->Mutex);
					return E_INVALIDARG;
				}
			}
			SetElementToHT(hthandle, element, j);
			hthandle->N++;
			inserted = true;

		}
	}
	ReleaseMutex(hthandle->Mutex);
	if (inserted)
		return S_OK;
	else
		return E_ABORT;
}

STDMETHODIMP_(Element*) HT::Get(HTHANDLE* hthandle, Element* element)
{
	if (!CheckParmLength(hthandle, element))
	{
		std::cout << "You param length is incorect" << std::endl;
		return NULL;
	}
	WaitForSingleObject(hthandle->Mutex, INFINITE);

	int indexInHT = -1;
	bool found = false;
	if (hthandle->N != 0)
		for (int i = 0, j = HashFunction(element, hthandle->Capacity, 0);
			GetElementFromHT(hthandle, j) != NULL && i != hthandle->Capacity && !found;
			j = Next_hash(j, hthandle->Capacity, ++i)) {
		Element* elFromHT = GetElementFromHT(hthandle, j);
		if (!IsDeleted(elFromHT)) {
			if (EqualElementKeys(elFromHT, element)) {
				indexInHT = j; found = true;
			}
		}
	}
	if (indexInHT < 0) {
		SetErrorMessage(hthandle, "Not found key\n", 15);
		ReleaseMutex(hthandle->Mutex);
		return NULL;
	}
	ReleaseMutex(hthandle->Mutex);
	return GetElementFromHT(hthandle, indexInHT);
}

STDMETHODIMP HT::Delete(HTHANDLE* hthandle, Element* element)
{
	if (!CheckParmLength(hthandle, element))
		return E_INVALIDARG;
	WaitForSingleObject(hthandle->Mutex, INFINITE);
	int indexInHT = -1;
	bool deleted = false;
	if (hthandle->N != 0)
		for (int i = 0, j = HashFunction(element, hthandle->Capacity, 0);
			GetElementFromHT(hthandle, j) != NULL && i != hthandle->Capacity && !deleted;
			j = Next_hash(j, hthandle->Capacity, ++i)) {
		Element* elFromHT = GetElementFromHT(hthandle, j);
		if (!IsDeleted(elFromHT)) {
			if (EqualElementKeys(elFromHT, element)) {
				indexInHT = j; deleted = true;
			}
		}
	}
	if (indexInHT < 0) {
		SetErrorMessage(hthandle, "Not found key\n", 15);
		ReleaseMutex(hthandle->Mutex);
		return E_INVALIDARG;
	}

	SetDeletedFlag(GetElementFromHT(hthandle, indexInHT));
	hthandle->N--;
	ReleaseMutex(hthandle->Mutex);
	return S_OK;
}

STDMETHODIMP HT::Update(HTHANDLE* hthandle, Element* oldelement, void* newpayload, int newpayloadlength)
{
	if (!CheckParmLength(hthandle, oldelement) || !CheckParmLength(hthandle, newpayloadlength))
		return E_INVALIDARG;
	WaitForSingleObject(hthandle->Mutex, INFINITE);
	int indexInHT = -1;
	bool updated = false;
	if (hthandle->N != 0)
		for (int i = 0, j = HashFunction(oldelement, hthandle->Capacity, 0);
			GetElementFromHT(hthandle, j) != NULL && i != hthandle->Capacity && !updated;
			j = Next_hash(j, hthandle->Capacity, ++i)) {
		Element* elFromHT = GetElementFromHT(hthandle, j);
		if (!IsDeleted(elFromHT)) {
			if (EqualElementKeys(elFromHT, oldelement)) {
				indexInHT = j; updated = true;
			}
		}
	}
	if (indexInHT < 0) {
		SetErrorMessage(hthandle, "Not found key\n", 15);
		ReleaseMutex(hthandle->Mutex);
		return E_INVALIDARG;
	}

	UpdateElement(hthandle, GetElementFromHT(hthandle, indexInHT), newpayload, newpayloadlength);
	ReleaseMutex(hthandle->Mutex);
	return S_OK;
}

STDMETHODIMP_(char*) HT::GetLastErrorProg(HTHANDLE* ht) {
	return ht->LastErrorMessage;
}

STDMETHODIMP HT::print(const Element* element) {
	char* key = (char*)element->key;
	std::cout << std::right << std::setfill('=') << std::setw(30) << '|' << std::endl;
	std::cout << std::left << std::setfill(' ') << std::setw(10) << "KEY";
	for (int i = 0; i < element->keylength; i++) {
		std::cout << key[i];
	}
	std::cout << std::left << std::setfill(' ') << std::setw(10) << "\nVALUE";
	char* payload = (char*)element->payload;
	for (int i = 0; i < element->payloadlength; i++) {
		std::cout << payload[i];
	}
	std::cout << std::endl;
	std::cout << std::right << std::setfill('=') << std::setw(30) << '|' << std::endl;
	return S_OK;
}

STDMETHODIMP_(Element*) HT::CreateNewFullElement(const void* key, int keylength, const void* payload, int payloadlength)
{
	return new Element(key, keylength, payload, payloadlength);
}

STDMETHODIMP_(Element*) HT::CreateNewKeyElement(const void* key, int keylength)
{
	return new Element(key, keylength);
}

Element* HT::GetElementFromHT(HTHANDLE* ht, int n) {
	void* elementsAddr = ht + 1;
	int defaultElementSize = ht->MaxKeyLength + ht->MaxPayloadLength + 2 * sizeof(int);
	void* elementAddr = (char*)elementsAddr + defaultElementSize * n;

	Element* element = new Element();
	element->key = elementAddr;
	element->keylength = *(int*)((char*)elementAddr + ht->MaxKeyLength);
	element->payload = ((char*)elementAddr + ht->MaxKeyLength + sizeof(int));
	element->payloadlength = *(int*)((char*)elementAddr + ht->MaxKeyLength + sizeof(int) + ht->MaxPayloadLength);
	if (element->keylength == 0) {
		delete element;
		return NULL;
	}
	return element;
}

BOOL HT::SetElementToHT(HTHANDLE* ht, Element* element, int n) {
	void* elementsAddr = ht + 1;
	int defaultElementSize = ht->MaxKeyLength + ht->MaxPayloadLength + 2 * sizeof(int);
	void* elementAddr = (char*)elementsAddr + defaultElementSize * n;

	memcpy(elementAddr, element->key, element->keylength);
	memcpy(((char*)elementAddr + ht->MaxKeyLength), &element->keylength, sizeof(int));
	memcpy(((char*)elementAddr + ht->MaxKeyLength + sizeof(int)), element->payload, element->payloadlength);
	memcpy(((char*)elementAddr + ht->MaxKeyLength + sizeof(int) + ht->MaxPayloadLength), &element->payloadlength, sizeof(int));
	return TRUE;
}

BOOL HT::IsDeleted(Element* ptr) {
	if (*(int*)ptr->key == -1) {
		return TRUE;
	}
	return FALSE;
}

BOOL HT::EqualElementKeys(Element* el1, Element* el2) {
	return !memcmp(el1->key, el2->key, el2->keylength) ? TRUE : FALSE;
}

void HT::SetErrorMessage(HTHANDLE* ht, const char* message, int messageLen) {
	char* err = (char*)message;
	memcpy(ht->LastErrorMessage, err, messageLen);
}

void HT::SetDeletedFlag(Element* ptr) {
	memcpy(ptr->key, &DELETED, sizeof(DELETED));
}

void HT::UpdateElement(HTHANDLE* ht, Element* el, void* newpayload, int newpayloadlength) {
	ZeroMemory(el->payload, ht->MaxPayloadLength + sizeof(int));
	memcpy(el->payload, newpayload, newpayloadlength);
	memcpy((char*)el->payload + ht->MaxPayloadLength, &newpayloadlength, sizeof(int));
}

int HT::HashFunction(const Element* element, int size, int p)    //Хеш-функция
{
	char* arrKeyBytes = new char[element->keylength];
	memcpy(arrKeyBytes, element->key, element->keylength);
	int sumBytes = 0;
	for (int i = 0; i < element->keylength; i++) {
		sumBytes += arrKeyBytes[i];
	}
	delete[] arrKeyBytes;
	return (p + sumBytes) % size;
}
int HT::Next_hash(int hash, int size, int p)
{
	return (hash + 5 * p + 3 * p * p) % size;
}

DWORD WINAPI SnapShotCycle(HTHANDLE* ht)
{
	while (true)
	{
		if (ht) {
			if (time(NULL) >= ht->lastsnaptime + ht->SecSnapshotInterval)
			{
				WaitForSingleObject(ht->Mutex, INFINITE);
				if (!FlushViewOfFile(Addr, NULL)) {
					HT::SetErrorMessage(ht, "Snapshot error", 15);
					return FALSE;
				}
				ht->lastsnaptime = time(NULL);
				std::cout << "----SNAPSHOT in Thread----" << std::endl;

				ReleaseMutex(ht->Mutex);
			}
		}
		else
			break;
	}
	return TRUE;
}

wchar_t* HT::GenerateMutexName(const wchar_t* pathToHT) {
	std::wstring s(pathToHT);
	std::wstring mutexName;
	s.erase(std::remove(s.begin(), s.end(), '\\'), s.end());
	std::wcout << s;
	return (wchar_t*)s.c_str();
}

wchar_t* HT::GenerateViewName(const wchar_t* pathToHT) {
	std::wstring s(pathToHT);
	std::wstring mutexName;
	s.erase(std::remove(s.begin(), s.end(), '\\'), s.end());
	std::wcout << std::endl << s << std::endl;
	return (wchar_t*)s.c_str();
}

BOOL HT::CheckParmLength(HTHANDLE* ht, Element* element) {
	if (element->keylength > ht->MaxKeyLength) {
		SetErrorMessage(ht, "KeyLength > maxKeyLength\n", strlen("KeyLength > maxKeyLength\n") + 1);
		return FALSE;
	}
	return TRUE;
}

BOOL HT::CheckParmLength(HTHANDLE* ht, int payloadLength) {
	if (payloadLength > ht->MaxPayloadLength) {
		HT::SetErrorMessage(ht, "PayloadLength > maxPayloadLength\n", strlen("PayloadLength > maxPayloadLength\n") + 1);
		return FALSE;
	}
	return TRUE;
}
