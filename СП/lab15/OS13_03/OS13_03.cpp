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
	HT_LIB::Mutex = CreateMutex(NULL, FALSE, L"Record");

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

		HTHANDLE* HT;
		ht = HT_LIB::Init();
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
			Element* el1 = HT_LIB::HT::CreateNewFullElement(ht, key.c_str(), key.length() + 1, "0", 2);

			HANDLE hThread{ NULL };

			if ((el = HT_LIB::HT::Get(ht, HT, el1)) == NULL)
			{
				std::cout << HT_LIB::HT::GetLastError(ht, HT) << std::endl;
			}
			else {
				std::tuple<Element*, bool, std::wstring, std::wstring> pr{ el, true, filePath, std::wstring(L"Delete") };
				if (WaitForSingleObject(HT_LIB::Mutex, INFINITE) == WAIT_OBJECT_0)
					hThread = CreateThread(NULL, 0, HT_LIB::HT::RecordingWork, &pr, 0, NULL);

				WaitForSingleObject(hThread, INFINITE);

				ReleaseMutex(HT_LIB::Mutex);

				HT_LIB::HT::print(ht, el);
				if (!HT_LIB::HT::Delete(ht, HT, el1)) 
				{
					std::cout << HT_LIB::HT::GetLastError(ht, HT) << std::endl;
				}
				else
					std::cout << "DELETE SUCCESS" << std::endl;
			}

			Sleep(1000);
		}
	}
	catch (const char* err)
	{
		std::cout << err << std::endl;
		return 1;
	}
}