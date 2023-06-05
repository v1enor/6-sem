#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

#include "../OS13_HTCOM_LIB/HT_LIB.h"

wchar_t* GetWC(const char* c)
{
	wchar_t* wc = new wchar_t[strlen(c) + 1];
	mbstowcs(wc, c, strlen(c) + 1);
	return wc;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	std::wcout.imbue(std::locale("ru_RU.UTF-8"));
	OS13HANDEL ht = nullptr;
	try
	{
		int capacity = 2000;
		int snapshotIntervalSec = 3;
		int maxKeyLength = 4;
		int maxPayloadLength = 4;
		wchar_t* fileName{ nullptr };
		const wchar_t* directoryPath = L"..\\..\\HT";
		std::wstring filePath(L"..\\HT\\test.ht");

		if (argc == 6)
		{
			capacity = std::stoi(argv[1]);
			snapshotIntervalSec = std::stoi(argv[2]);
			maxKeyLength = std::stoi(argv[3]);
			maxPayloadLength = std::stoi(argv[4]);
			std::cout << GetWC(argv[5]) << std::endl;
			std::cout << argv[5];
			fileName = GetWC(argv[5]);
			std::wstring s(directoryPath);
			s += L"\\" + std::wstring(fileName);
			filePath = s;
		}
		else
			std::cout << "Using default values" << std::endl;

		ht = HT_LIB::Init();
		if (ht == NULL)
			throw "Error init com";

		HTHANDLE* HT = nullptr;

		HT = HT_LIB::HT::Create(ht, capacity, snapshotIntervalSec, maxKeyLength,
			maxPayloadLength, filePath.c_str());

		if (HT == NULL || HT == INVALID_HANDLE_VALUE)
			throw "Invalid handle";

		std::cout << "HT-Storage Created " << std::endl;
		HT_LIB::HT::printHT(HT);

		HT_LIB::Dispose(ht);
		return 0;
	}
	catch (const char* err)
	{
		HT_LIB::Dispose(ht);
		std::cout << std::endl << err << std::endl;
		return 1;
	}
}
