#include "pch.h"
#include "framework.h"

#define _CRT_SECURE_NO_WARNINGS

#include <objbase.h>
#include <Windows.h>
#include <wchar.h>

#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <ctime>
#include <chrono>
#include <iomanip>

#include "HT.h"
#include "HT_LIB.h"

OS13HANDEL HT_LIB::Init()
{
	try
	{
		IUnknown* pIUnknown = NULL;
		CoInitialize(NULL);                        // инициализация библиотеки OLE32
		HRESULT hr = CoCreateInstance(CLSID_HT, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pIUnknown);
		if (!SUCCEEDED(hr))
			throw hr;
		return pIUnknown;
	}
	catch (HRESULT rc)
	{
		OutputErrorHandle(rc);
		return NULL;
	}
}

void HT_LIB::Dispose(OS13HANDEL h)
{
	static_cast<IUnknown*>(h)->Release();
	CoFreeUnusedLibraries();
}

void HT_LIB::OutputErrorHandle(int hr)
{
	char buffer[256];
	DWORD errorMessageId = hr;
	if (HRESULT_FACILITY(hr) == FACILITY_WINDOWS) {
		errorMessageId = HRESULT_CODE(hr);
	}
	if (FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorMessageId,
		MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
		buffer,
		sizeof(buffer),
		NULL)) {
		std::cout << std::endl << buffer << std::endl;
	}
	else {
		std::cout << std::endl << "Cant casting hresult to string" << std::endl;
	}
}

HTHANDLE* HT_LIB::HT::Create(OS13HANDEL h, int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const wchar_t HTUsersGroup[512], const wchar_t FileName[512])
{
	try
	{
		HRESULT hr{};
		if (!SUCCEEDED(hr = static_cast<IUnknown*>(h)->QueryInterface(IID_IHT, (void**)&p_Ht)))
			throw hr;

		HTHANDLE *ht{nullptr};
		if ((ht = p_Ht->Create(Capacity, SecSnapshotInterval, MaxKeyLength, MaxPayloadLength, HTUsersGroup, FileName)) == NULL)
			throw "Error create ht";
		p_Ht->Release();
		return ht;
	}
	catch (char* err)
	{
		std::cout << std::endl << err << std::endl;
		return NULL;
	}
	catch (HRESULT rc)
	{
		OutputErrorHandle(rc);
		return NULL;
	}
}

HTHANDLE* HT_LIB::HT::Open(OS13HANDEL h, const std::wstring FileName)
{
	HTHANDLE* ht{ nullptr };
	try
	{
		HRESULT hr{};
		if (!SUCCEEDED((hr = static_cast<IUnknown*>(h)->QueryInterface(IID_IHT, (void**)&p_Ht))))
			throw hr;

		HTHANDLE* ht;
		if (!(ht = p_Ht->Open(FileName)))
			throw "Error open HT";
		p_Ht->Release();
		return ht;
	}
	catch (char* err)
	{
		std::cout << std::endl << err << std::endl;
		return NULL;
	}
	catch (HRESULT rc)
	{
		OutputErrorHandle(rc);
		return NULL;
	}
}

HTHANDLE* HT_LIB::HT::Open(OS13HANDEL h, const std::wstring HTUser, const std::wstring HTPassword, const std::wstring FileName)
{
	HTHANDLE* ht{ nullptr };
	try
	{
		HRESULT hr{};
		if (!SUCCEEDED((hr = static_cast<IUnknown*>(h)->QueryInterface(IID_IHT, (void**)&p_Ht))))
			throw hr;

		HTHANDLE* ht;
		if (!(ht = p_Ht->Open(HTUser, HTPassword, FileName)))
			throw "Error open HT";
		p_Ht->Release();
		return ht;
	}
	catch (char* err)
	{
		std::cout << std::endl << err << std::endl;
		return NULL;
	}
	catch (HRESULT rc)
	{
		OutputErrorHandle(rc);
		return NULL;
	}
}

HTHANDLE* HT_LIB::HT::OpenExist(OS13HANDEL h, std::wstring FileName)
{
	HTHANDLE* ht{nullptr};
	try
	{
		HRESULT hr{};
		if (!SUCCEEDED((hr = static_cast<IUnknown*>(h)->QueryInterface(IID_IHT, (void**)&p_Ht))))
			throw hr;

		if ((ht = p_Ht->OpenExist(FileName)) == NULL)
			throw "Error open exist HT";
		p_Ht->Release();
		return ht;
	}
	catch (char* err)
	{
		std::cout << std::endl << err << std::endl;
		return NULL;
	}
	catch (HRESULT rc)
	{
		OutputErrorHandle(rc);
		return NULL;
	}
}

HTHANDLE* HT_LIB::HT::OpenExist(void* h, std::wstring HTUser, std::wstring HTPassword, std::wstring FileName)
{
	HTHANDLE* ht{ nullptr };
	try
	{
		HRESULT hr{};
		if (!SUCCEEDED((hr = static_cast<IUnknown*>(h)->QueryInterface(IID_IHT, (void**)&p_Ht))))
			throw hr;

		if ((ht = p_Ht->OpenExist(HTUser, HTPassword,FileName)) == NULL)
			throw "Error open exist HT";
		p_Ht->Release();
		return ht;
	}
	catch (char* err)
	{
		std::cout << std::endl << err << std::endl;
		return NULL;
	}
	catch (HRESULT rc)
	{
		OutputErrorHandle(rc);
		return NULL;
	}
}

BOOL HT_LIB::HT::Insert(OS13HANDEL h, HTHANDLE* ht, Element* el)
{
	try
	{
		HRESULT hr{};
		if (!SUCCEEDED((hr = static_cast<IUnknown*>(h)->QueryInterface(IID_IHT, (void**)&p_Ht))))
			throw hr;

		if(!SUCCEEDED(hr = p_Ht->Insert(ht, el)))
			throw hr;

		p_Ht->Release();
		return TRUE;
	}
	catch (HRESULT rc)
	{
		OutputErrorHandle(rc);
		return FALSE;
	}
}

Element* HT_LIB::HT::Get(OS13HANDEL h, HTHANDLE* ht, Element* el)
{
	try
	{
		HRESULT hr{};
		if (!SUCCEEDED((hr = static_cast<IUnknown*>(h)->QueryInterface(IID_IHT, (void**)&p_Ht))))
			throw hr;

		Element* nel{nullptr};
		if ((nel = p_Ht->Get(ht, el)) == NULL)
			return NULL;
		p_Ht->Release();
		return nel;
	}
	catch (HRESULT rc)
	{
		OutputErrorHandle(rc);
		return NULL;
	}
	catch (char* err)
	{
		std::cout << std::endl << err << std::endl;
		return NULL;
	}
}

BOOL HT_LIB::HT::Update(OS13HANDEL h, HTHANDLE* hthandle, Element* oldelement, Element* newelement)
{
	try
	{
		HRESULT hr{};
		if (!SUCCEEDED((hr = static_cast<IUnknown*>(h)->QueryInterface(IID_IHT, (void**)&p_Ht))))
			throw hr;

		if(!SUCCEEDED(hr = p_Ht->Update(hthandle, oldelement, newelement->payload, newelement->payloadlength)))
			throw hr;
		p_Ht->Release();
		return TRUE;
	}
	catch (HRESULT rc)
	{
		OutputErrorHandle(rc);
		return FALSE;
	}
}

void HT_LIB::HT::Close(OS13HANDEL h, const HTHANDLE* ht)
{
	try
	{
		HRESULT hr{};
		if (!SUCCEEDED(hr == static_cast<IUnknown*>(h)->QueryInterface(IID_IHT, (void**)&p_Ht)))
			throw hr;

		if (!SUCCEEDED(hr = p_Ht->Close(ht)))
			throw hr;

		p_Ht->Release();
	}
	catch(HRESULT rc)
	{
		OutputErrorHandle(rc);
	}
}

BOOL HT_LIB::HT::Delete(OS13HANDEL h, HTHANDLE* ht, Element* el)
{
	try
	{
		HRESULT hr{};
		if (!SUCCEEDED((hr = static_cast<IUnknown*>(h)->QueryInterface(IID_IHT, (void**)&p_Ht))))
			throw hr;

		if(!SUCCEEDED(hr = p_Ht->Delete(ht, el)))
			throw hr;
		p_Ht->Release();
		return TRUE;
	}
	catch (HRESULT rc)
	{
		OutputErrorHandle(rc);
		return FALSE;
	}
}

char* HT_LIB::HT::GetLastError(OS13HANDEL h, HTHANDLE* ht)
{
	try
	{
		HRESULT hr{};
		if (!SUCCEEDED((hr = static_cast<IUnknown*>(h)->QueryInterface(IID_IHT, (void**)&p_Ht))))
			throw hr;
		char* err{nullptr};
		if((err = p_Ht->GetLastErrorProg(ht)) == NULL)
			throw "Error get string err";
		p_Ht->Release();
		return err;
	}
	catch (HRESULT rc)
	{
		OutputErrorHandle(rc);
		return NULL;
	}
}

void HT_LIB::HT::print(OS13HANDEL h, const Element* el)
{
	try
	{
		HRESULT hr{};
		if (!SUCCEEDED((hr = static_cast<IUnknown*>(h)->QueryInterface(IID_IHT, (void**)&p_Ht))))
			throw hr;

		if(!SUCCEEDED(hr = p_Ht->print(el)))
			throw hr;

		p_Ht->Release();
		return;
	}
	catch (HRESULT rc)
	{
		OutputErrorHandle(rc);
	}
}

void HT_LIB::HT::printHT(const HTHANDLE* ht)
{
	std::wcout << "filename: " << ht->FileName << std::endl;
	std::cout << "snapshotIntervalSec: " << ht->SecSnapshotInterval << std::endl;
	std::cout << "capacity: " << ht->Capacity << std::endl;
	std::cout << "maxKeyLength: " << ht->MaxKeyLength << std::endl;
	std::cout << "maxPayloadLength: " << ht->MaxPayloadLength << std::endl;
}

int* HT_LIB::HT::GetPayload(Element* el)
{
	std::stringstream ss;
	int num;
	ss << *(char*)el->payload;
	ss >> num;
	return &num;
}

Element* HT_LIB::HT::CreateNewFullElement(OS13HANDEL h, const void* key, int keylength, const void* payload, int payloadlength)
{
	try
	{
		HRESULT hr{};
		if (!SUCCEEDED((hr = static_cast<IUnknown*>(h)->QueryInterface(IID_IHT, (void**)&p_Ht))))
			throw hr;

		Element* el{ nullptr };

		if ((el = p_Ht->CreateNewFullElement(key, keylength, payload, payloadlength)) == NULL)
			throw E_INVALIDARG;

		p_Ht->Release();
		return el;
	}
	catch (HRESULT rc)
	{
		OutputErrorHandle(rc);
		return NULL;
	}
}

Element* HT_LIB::HT::CreateNewKeyElement(OS13HANDEL h, const void* key, int keylength)
{
	try
	{
		HRESULT hr{};
		if (!SUCCEEDED((hr = static_cast<IUnknown*>(h)->QueryInterface(IID_IHT, (void**)&p_Ht))))
			throw hr;

		Element* el{ nullptr };

		if ((el = p_Ht->CreateNewKeyElement(key, keylength)) == NULL)
			throw E_INVALIDARG;

		p_Ht->Release();
		return el;
	}
	catch (HRESULT rc)
	{
		OutputErrorHandle(rc);
		return NULL;
	}
}

DWORD WINAPI HT_LIB::HT::RecordingWork(LPVOID point)
{
	try {
		return true;
		auto tp = reinterpret_cast<std::tuple<Element*, bool, std::wstring, std::wstring>*>(point);
		Element* el = std::get<0>(*tp);
		bool suc = std::get<1>(*tp);
		std::wstring fileName = std::get<2>(*tp);
		std::wstring typeOperation = std::get<3>(*tp);

		std::cout << "Recording...." << std::endl;

		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		std::tm* now_tm = std::localtime(&now_c);

		std::wstringstream ss;
		ss << std::put_time(now_tm, L"%Y-%m-%d_%H-%M-%S") << L".txt";
		std::wstring date = ss.str();

		// !!!!!!!!!!!!!!!!!!!!!! add ..\\ in next path !!!!!!!!!!!!!!!!!!!!!!
		std::wstring filePath(L"..\\..\\Records\\" + typeOperation + L"\\" + date);

		auto file = CreateFile(filePath.c_str(), GENERIC_READ | GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (file == INVALID_HANDLE_VALUE)
			throw "Error create file record";

		const char* key_str = static_cast<const char*>(el->key);
		const char* payload_str = static_cast<const char*>(el->payload);

		std::string key;
		std::string payload;

		for (int i{}; i < el->keylength; i++)
		{
			if (key_str[i] != '\n')
				key.push_back(key_str[i]);
		}
		for (int i{}; i < el->payloadlength; i++)
		{
			if (payload_str[i] != '\n')
			{
				if (payload_str[i] == '0')
					payload.push_back('0');
				else
					payload.push_back(payload_str[i]);
			}
		}

		std::string string_suc = (suc ? "true" : "false");
		std::string str = std::string(typeOperation.begin(), typeOperation.end()) + "\telement:\tKey : " + key + "\tPayload : " + payload + "\tSuccess : " + string_suc + "\tOn file : " + std::string(fileName.begin(), fileName.end());

		if (!WriteFile(file, str.c_str(), static_cast<DWORD>(str.size() + 1), NULL, NULL))
			throw "Error write file record";

		if (!CloseHandle(file))
			throw "Error close file record";

		std::cout << "Record success" << std::endl;

		return 0;
	}
	catch (char* err)
	{
		std::cout << err << std::endl;
		return 1;
	}
}
