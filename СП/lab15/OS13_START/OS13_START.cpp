#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "HT_LIB.h"
#include <wchar.h>
#include <fstream>

#define TRACEPATH "D:\\Start.trace"

void trace(const char* msg, int r = std::ofstream::out)
{
	std::ofstream out;
	out.open(TRACEPATH, r);
	out << msg << "\n";
	out.close();
}

wchar_t* GetWC(const char* c)
{
	wchar_t* wc = new wchar_t[strlen(c) + 1];
	mbstowcs(wc, c, strlen(c) + 1);

	return wc;
}

int main(int argc, char* argv[])
{
	OS13HANDEL ht = nullptr;
	char temp[121];
	wchar_t* fileName{ nullptr };
	const std::wstring directoryPath = L"..\\..\\HT";
	std::wstring filePath(L"..\\HT\\test.ht");
	wchar_t* HTUsers{nullptr};
	wchar_t* HTPassword{nullptr};

	HANDLE hStopEvent = CreateEvent(NULL,
		TRUE, //FALSE - автоматический сброс; TRUE - ручной
		FALSE,
		L"Global\\HTStop");

	try {

		if (argv[1]) 
		{
			fileName = GetWC(argv[1]);
			std::wstring s(directoryPath);
			s += L"\\" + std::wstring(fileName);
			filePath = s;
			if(argc == 4)
			{
				HTUsers = GetWC(argv[2]);
				std::wcout << HTUsers << std::endl;
				HTPassword = GetWC(argv[3]);
			}
		}
		else
			std::cout << "Using default file path" << std::endl;


		filePath = GetWC(argv[1]);
		trace(std::string(filePath.begin(), filePath.end()).c_str());

		HTHANDLE* HT;

		ht = HT_LIB::Init();
		if (ht == NULL)
			throw "Error init com";

		if (HTUsers == nullptr || HTPassword == nullptr)
		{
			if (!(HT = HT_LIB::HT::Open(ht, filePath.c_str())))
				throw "Error open";
		}
		else
		{
			if (!(HT = HT_LIB::HT::Open(ht, HTUsers, HTPassword, filePath)))
				throw "Error open";
		}

		while (WaitForSingleObject(hStopEvent, 0) == WAIT_TIMEOUT)
		{
		}

		HT_LIB::HT::Close(ht, HT);

		//trace("CLOSE");

		HT_LIB::Dispose(ht);
		return 0;
	}
	catch (const char* err)
	{
		std::cout << "\t" << err << std::endl;
		return 1;
	}
}
