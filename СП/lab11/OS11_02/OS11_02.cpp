#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include "HashTable.h"
#include <string>
#include <time.h>

using namespace std;

void Do(LPCSTR FileName) 
{
	char cwd[MAX_PATH];
	GetModuleFileNameA(NULL, cwd, MAX_PATH);
	string path(cwd);
	int pos = path.find_last_of("/") + 1;
	string filePath = path.substr(0, pos) + FileName;
	char* filePathCost = (char*)filePath.c_str();
	DWORD er;

	HT::HTHANDLE* ht = HT::Open(filePathCost);
	if (ht != NULL) 
	{
		printf("\nHT-Storage Created filename=%s, snapshotinterval=%d, capacity = %d, maxkeylength = %d, maxdatalength = %d",
			filePathCost, ht->SecSnapshotInterval, ht->Capacity, ht->MaxKeyLength, ht->MaxPayloadLength);
	}
	else 
	{
		printf("\n some error fail@: %d", GetLastError());
		return;
	}
	srand(time(NULL));
	HT::Element* element;
	int random;
	int value = 0;
	while (true) 
	{
		random = rand()%50;
		element = new HT::Element((const void*)&random, 4, &value, 4);
		if (HT::Insert(ht, element)) 
		{
			printf("\nSuccessful inserting key: %d", random);
		}
		else 
		{
			printf("\nFail with inserting key: %d. Message: %s", random, HT::GetLastHtError(ht));
		}
		Sleep(1000);
	}
	HT::Close(ht);
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");
	if (argc != 2) 
	{
		printf("\nDefault parameters are used", argc);
		argv[1] = (char*)"C:\\Users\\ila\\Desktop\\Домашка\\СП\\lab11\\file.txt";
	}
	Do(argv[1]);
	return 0;
}