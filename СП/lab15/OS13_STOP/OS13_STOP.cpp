#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <iostream>
#include <HT_LIB.h>

wchar_t* GetWC(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}

int main(int argc, char* argv[])
{
	auto ht = HT_LIB::Init();

	HTHANDLE* HT;

	auto filePath = GetWC(argv[1]);

	try
	{
		HT = HT_LIB::HT::OpenExist(ht, filePath);
		if (HT == NULL)
			throw "Invalid handle";

		HT_LIB::HT::Close(ht, HT);
	}
	catch(char* r)
	{
		std::cout << r << std::endl;
	}
}