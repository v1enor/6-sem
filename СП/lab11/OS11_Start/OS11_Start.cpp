#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include "HashTable.h"
#include <string>

using namespace std;

string key = "my_key";
string value = "my_value";
HT::HTHANDLE* ht = NULL;

void StartHT(LPCSTR FileName) 
{
	char cwd[MAX_PATH];
	GetModuleFileNameA(NULL, cwd, MAX_PATH);
	string path(cwd);
	int pos = path.find_last_of("/") + 1;
	string filePath = path.substr(0, pos) + FileName;
	char* filePathCost = (char*)filePath.c_str();

	HT::HTHANDLE* ht = HT::Open(filePathCost);
	
	if (ht != NULL) 
	{
		printf("\nHT-Storage Created filename=%s, snapshotinterval=%d, capacity = %d, maxkeylength = %d, maxdatalength = %d",
			filePathCost, ht->SecSnapshotInterval, ht->Capacity, ht->MaxKeyLength, ht->MaxPayloadLength);
		wprintf(L"\nFilemap name: %s", ht->fileMapName);
	}
	else 
	{
		printf("\nSome error fail@");
	}

	printf("\n");
	system("pause");
	if (HT::Snap(ht)) 
	{
		printf("\nSuccessful snap");
	}else 
	{
		printf("\nFeil snap");
	}
	HT::Close(ht);
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");
	int capacity = 20, keyLen = 20, valLen = 64, snapTime = 5;
	if (argc != 2) 
	{
		printf("\nDefault parameters are used", argc);
		argv[1] = (char*)"C:\\Users\\ila\\Desktop\\Домашка\\СП\\lab11\\file.txt";
	}
	StartHT(argv[1]);
	return 0;
}