#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "HT_LIB.h"
#include <string>
#include <sstream>
#include <wchar.h>
#include <thread>
#include <ctime>
#include <chrono>
#include <iomanip>

HANDLE mutexName;

wchar_t* GetWC(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}

int main(int argc, char* argv[])
{
	srand(time(0));

	OS13HANDEL ht = nullptr;

	wchar_t* fileName;
	const wchar_t* directoryPath = L"..\\..\\HT";
	std::wstring filePath(L"..\\HT\\test.ht");
	std::wstring HTUsers = L"";
	std::wstring HTPassword = L"";
	HANDLE hStopEvent = CreateEvent(NULL,
		TRUE, //FALSE - автоматический сброс; TRUE - ручной
		FALSE,
		L"Global\\HTStopExist");
	try {
		if (argv[1]) {
			fileName = GetWC(argv[1]);
			std::wstring s(directoryPath);
			s += L"\\" + std::wstring(fileName);
			filePath = s;
			if (argc == 4)
			{
				HTUsers = GetWC(argv[2]);
				HTPassword = GetWC(argv[3]);
			}
		}

		HT_LIB::Mutex = CreateMutex(NULL, FALSE, L"Record");

		ht = HT_LIB::Init();

		HTHANDLE* HT;
		if (HTUsers.length() == 0 || HTPassword.length() == 0)
		{
			HT = HT_LIB::HT::OpenExist(ht, filePath.c_str());
			if (HT == NULL)
				throw "Invalid handle";
		}
		else
		{
			HT = HT_LIB::HT::OpenExist(ht, HTUsers, HTPassword, filePath);
			if (HT == NULL)
				throw "Invalid handle";
		}
		while (WaitForSingleObject(hStopEvent, 0) == WAIT_TIMEOUT)
		{
			int numberKey = rand() % 50 + 1;
			std::string key{};

			std::stringstream convert;
			convert << numberKey;
			key = convert.str();

			Element* el;
			Element* el1 = HT_LIB::HT::CreateNewKeyElement(ht, key.c_str(), key.length() + 1);
			Element* el2;

			if ((el = HT_LIB::HT::Get(ht, HT, el1)) == NULL)
			{
				std::cout << HT_LIB::HT::GetLastError(ht, HT) << std::endl;
			}
			else {
				std::cout << "Old element" << std::endl;
				HT_LIB::HT::print(ht, el);
				
				int newNum = *HT_LIB::HT::GetPayload(el) + 1;

				std::string payload;
				std::stringstream payloadConvert;
				payloadConvert << newNum;
				payload = payloadConvert.str();

				el2 = HT_LIB::HT::CreateNewFullElement(ht, key.c_str(), key.length() + 1, payload.c_str(), payload.length() + 1);

				std::tuple<Element*, bool, std::wstring, std::wstring> pr{ el, true, filePath, std::wstring(L"Update") };

				HANDLE hThread{ NULL };
				if (WaitForSingleObject(HT_LIB::Mutex, INFINITE) == WAIT_OBJECT_0)
					hThread = CreateThread(NULL, 0, HT_LIB::HT::RecordingWork, &pr, 0, NULL);

				WaitForSingleObject(hThread, INFINITE);

				ReleaseMutex(HT_LIB::Mutex);

				if (!HT_LIB::HT::Update(ht, HT, el1, el2)) {
					std::cout << HT_LIB::HT::GetLastError(ht, HT) << std::endl;
				}
				else
				{
					std::cout << "UPDATE SUCCESS" << std::endl;
				}
				if ((el = HT_LIB::HT::Get(ht, HT, el1)) == NULL)
					std::cout << HT_LIB::HT::GetLastError(ht, HT) << std::endl;
				else
				{
					std::cout << "New element" << std::endl;
					HT_LIB::HT::print(ht, el);
				}
			}

			Sleep(1000);
		}
		CloseHandle(HT_LIB::Mutex);
	}
	catch (const char* err)
	{
		std::cout << err << std::endl;
		return 1;
	}
}