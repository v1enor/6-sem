#pragma once
#include <string>

#define MAX_PATH_LENGTH 1024

namespace Utilities
{
	/**
	* Returns path of folder where there is an executable file
	*/
	std::string GetModulePath();

	/**
	* Converts string to wstring
	*/
	std::wstring ConvertStringToWstring(std::string inValue);
}