#include <Windows.h>
#include <iostream>
using namespace std;
#define FILE_PATH L"C:/Users/pcina/Desktop/Домашка/СП/Lab1/OS09_01.txt"
#define READ_BYTES 185





string getFileName(wchar_t* filePath)
{
    wstring ws(filePath);
    string filename(ws.begin(), ws.end());
    const size_t last_slash_idx = filename.find_last_of("\\/");
    if (string::npos != last_slash_idx)
        filename.erase(0, last_slash_idx + 1);
    return filename;
}




LPCWSTR getFileType(HANDLE file)
{
    switch (GetFileType(file))
    {
    case FILE_TYPE_UNKNOWN:
        return L"FILE_TYPE_UNKNOWN";
    case FILE_TYPE_DISK:
        return L"FILE_TYPE_DISK";
    case FILE_TYPE_CHAR:
        return L"FILE_TYPE_CHAR";
    case FILE_TYPE_PIPE:
        return L"FILE_TYPE_PIPE";
    case FILE_TYPE_REMOTE:
        return L"FILE_TYPE_REMOTE";
    default:
        return L"[ERROR]: WRITE FILE TYPE";
    }
}




BOOL printFileInfo(LPWSTR path) 
{
    HANDLE file = CreateFile(
        path,
        GENERIC_READ,
        NULL,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    SYSTEMTIME sysTime;
    BY_HANDLE_FILE_INFORMATION fi;
    BOOL fResult = GetFileInformationByHandle(file, &fi);
    if (fResult) 
    {
        cout << "File name:\t" << getFileName((wchar_t*)FILE_PATH);
        wcout << "\nFile type:\t" << getFileType(file);
        cout << "\nFile size:\t" << fi.nFileSizeLow << " bytes";
        FileTimeToSystemTime(&fi.ftCreationTime, &sysTime);
        cout << "\nCreate time:\t" << sysTime.wDay << '.' << sysTime.wMonth << '.' << sysTime.wYear << " " << sysTime.wHour + 3 << '.' << sysTime.wMinute << '.' << sysTime.wSecond;
        FileTimeToSystemTime(&fi.ftLastWriteTime, &sysTime);
        cout << "\nUpdate time:\t" << sysTime.wDay << '.' << sysTime.wMonth << '.' << sysTime.wYear << " " << sysTime.wHour + 3 << '.' << sysTime.wMinute << '.' << sysTime.wSecond;
    }
    CloseHandle(file);
    return true;
}



BOOL printFileTxt(LPWSTR path) 
{
    HANDLE file = CreateFile(
        path,
        GENERIC_READ,
        NULL,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    char buf[1024];
    DWORD countBytes = NULL;
    ZeroMemory(buf, sizeof(buf));
    BOOL b = ReadFile(
        file, 
        &buf, 
        READ_BYTES, 
        &countBytes, 
        NULL);
    if (!b) throw "[ERROR] Readfile throwed exception.";
    cout << "\n\n\tPrint file (" << countBytes << " bytes)\n" << buf << '\n';
}





int main()
{
    setlocale(LC_ALL, "ru");
    LPWSTR path = (LPWSTR)FILE_PATH;
    cout << "\n======================================\n\n";
    printFileInfo(path);
    cout << "\n\n======================================";
    printFileTxt(path);
    cout << "\n======================================\n";
}

