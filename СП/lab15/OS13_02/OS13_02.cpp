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
#include <fstream>

HANDLE mutexName;

#define TRACEPATH "D:\\02.trace"

void trace(const char* msg, int r = std::ofstream::out)
{
	std::ofstream out;
	out.open(TRACEPATH, r);
	out << msg << "\n";
	out.close();
}

wchar_t* GetWC(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}

void printStr(char* str) {
	std::cout << "ERROR:\t";
	int i = 0;
	while (str[i]) {
		std::cout << str[i];
		i++;
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	srand(time(0));

	OS13HANDEL ht = nullptr;

	wchar_t* fileName;
	const wchar_t* directoryPath = L"..\\..\\HT";
	std::wstring filePath(L"..\\HT\\test2.ht");
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
			if(argc == 4)
			{
				HTUsers = GetWC(argv[2]);
				HTPassword = GetWC(argv[3]);
			}
		}

		filePath = GetWC(argv[1]);
		trace(std::string(filePath.begin(), filePath.end()).c_str());

		ht = HT_LIB::Init();

		HTHANDLE* HT;

		if (HTUsers.empty() || HTUsers.empty())
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

			Element* el = HT_LIB::HT::CreateNewFullElement(ht, key.c_str(), key.length() + 1, "0", 2);

			bool success = true;
			if (!HT_LIB::HT::Insert(ht, HT, el))
			{
				std::cout << HT_LIB::HT::GetLastError(ht, HT) << std::endl;
				success = false;
			}
			else
				HT_LIB::HT::print(ht, el);

			std::tuple<Element*, bool, std::wstring, std::wstring> pr{ el,success, filePath, std::wstring(L"Insert")};
			HANDLE hThread = CreateThread(NULL, 0, HT_LIB::HT::RecordingWork, &pr, 0, NULL);

			WaitForSingleObject(hThread, INFINITE);
			CloseHandle(hThread);

			Sleep(1000);
		}
	}
	catch (const char* err) 
	{
		std::cout << err << std::endl;
		return 1;
	}
}