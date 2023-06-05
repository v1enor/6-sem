#include "Utilities.h"
#include <Windows.h>
#include <stdlib.h>


std::string Utilities::GetModulePath()
{
	char temp_module_char_path[MAX_PATH_LENGTH]{};
	GetModuleFileNameA(NULL, temp_module_char_path, MAX_PATH_LENGTH);
	std::string temp_module_path(temp_module_char_path);
	int last_slesh_position = temp_module_path.find_last_of('\\') + 1;

	return temp_module_path.substr(0, last_slesh_position);
}

std::wstring Utilities::ConvertStringToWstring(std::string inValue)
{
	std::wstring temp();
	wchar_t* temp_warray = new wchar_t[inValue.length()+2];
	unsigned int wc_out_size;	

	mbstowcs_s(&wc_out_size, temp_warray, inValue.length()+2, inValue.c_str(), inValue.length());

	return temp_warray;
}
