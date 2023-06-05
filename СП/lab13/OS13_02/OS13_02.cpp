#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include <string>
#include <sstream>
#include <wchar.h>
#include <thread>
#include <ctime>
#include <chrono>
#include <iomanip>

#include <HT_LIB.h>

HANDLE mutexName;

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
	std::wstring filePath(L"..\\HT\\test.ht");

	try {
		if (argv[1]) {
			fileName = GetWC(argv[1]);
			std::wstring s(directoryPath);
			s += L"\\" + std::wstring(fileName);
			filePath = s;
		}

		ht = HT_LIB::Init();

		HTHANDLE* HT;
		HT = HT_LIB::HT::OpenExist(ht, filePath.c_str());
		if (HT == NULL)
			throw "Invalid handle";

		while (true)
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
			//HANDLE hThread = CreateThread(NULL, 0, HT_LIB::HT::RecordingWork, &pr, 0, NULL);

			//WaitForSingleObject(hThread, INFINITE);
			//CloseHandle(hThread);

			Sleep(1000);
		}
	}
	catch (const char* err) 
	{
		std::cout << err << std::endl;
		return 1;
	}
}