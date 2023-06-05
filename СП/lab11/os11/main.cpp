#include <iostream>
#include <Windows.h>
#include <cstdlib>

#include <string>
#include "../OS11_HTAPI/HashTable.h"

using namespace std;

string key = "my_key";
string value = "my_value";
HT::HTHANDLE* ht = NULL;

void InitHt(LPCSTR FileName) {
	HT::HTHANDLE* ht = HT::Create(40, 20, 64, 64, FileName);

	cout << "\ninserting...\n";
	string tempKey = "my_key";
	string tempValue = "my_value";
	char* error = NULL;
	for (int i = 0; i < 10; i++) {
		tempKey = key + to_string(i);
		tempValue = value + to_string(i);
		if (!HT::Insert(ht, new HT::Element(tempKey.c_str(), tempKey.length(), tempValue.c_str(), tempValue.length()))) {
			cout << "\nerror with inserting on " << i;
			error = HT::GetLastHtError(ht);
			if (error != NULL)
				cout << "\n" << error;
		}
	}
	cout << "\ninserted items:\n";
	HT::PrintAll(ht);

	HT::Close(ht);

	//CloseHandle(htFile);
	//DWORD er = GetLastError();
	delete[] error;
}
void DoTestCases(LPCSTR FileName) {

	char cwd[MAX_PATH];
	GetModuleFileNameA(NULL, cwd, MAX_PATH);
	string path(cwd);
	int pos = path.find_last_of("\\") + 1;
	string filePath = path.substr(0, pos) + FileName;
	DWORD er;
	char* filePathCost = (char*)filePath.c_str();
	InitHt(filePathCost);
}

int main()
{
	DoTestCases("map3.txt");
	int sum = HT::sum(2, 3);
	system("pause");
	return 0;
}