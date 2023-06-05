#include "Service.h"
#include "HT_LIB.h"


WCHAR ServiceName[] = SERVICENAME;
SERVICE_STATUS_HANDLE   hServiceStatus;
SERVICE_STATUS          ServiceStatus;

BOOL bServicePause = false;

PROCESS_INFORMATION* OpenHT()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    std::wstring szExePath = L"C:\\Users\\Administrator\\Desktop\\HTService\\x64\\Debug\\OS15_START.exe C:\\Users\\Administrator\\Desktop\\HTService\\HT\\test.ht";

    // Запуск внешней программы
    if (!CreateProcess(NULL, const_cast<LPWSTR>(szExePath.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        char temp[121];
        sprintf_s(temp, "\nCreateProcess failed, error code = %d\n", GetLastError());
        trace(temp);
        return NULL;
    }

    return &pi;
}

bool FileExists(const wchar_t* filePath)
{
    DWORD fileAttributes = GetFileAttributes(filePath);
    return (fileAttributes != INVALID_FILE_ATTRIBUTES && !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY));
}

bool AddPrivileges()
{
    HANDLE token;
    TOKEN_PRIVILEGES tp;
    bool result = false;
    
    OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &token);
    LookupPrivilegeValue(NULL, SE_CREATE_GLOBAL_NAME, &tp.Privileges[0].Luid);

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    result = false != AdjustTokenPrivileges(token, FALSE, &tp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

    CloseHandle(token);
    return result;
}

VOID WINAPI  ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
    char temp[121];

    // Установка статуса службы на "запускается"
    ServiceStatus.dwServiceType = SERVICE_WIN32;
    ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE;
    ServiceStatus.dwWin32ExitCode = 0;
    ServiceStatus.dwServiceSpecificExitCode = 0;
    ServiceStatus.dwCheckPoint = 0;
    ServiceStatus.dwWaitHint = 0;

    hServiceStatus = RegisterServiceCtrlHandler(ServiceName, ServiceHandler);
    if (hServiceStatus == NULL)
    {
        sprintf_s(temp, "\nRegisterServiceCtrlService failed, error code = %d\n", GetLastError());
        trace(temp);
        return;
    }

    // Установка статуса службы на "работает"
    ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    ServiceStatus.dwCheckPoint = 0;
    ServiceStatus.dwWaitHint = 0;

    if(!SetServiceStatus(hServiceStatus, &ServiceStatus))
    {
        sprintf_s(temp, "\nSetServiceStatus failed, error code = %d\n", GetLastError());
        trace(temp);
        return;
    }

    if (!AddPrivileges())
    {
        sprintf_s(temp, "\nAddPrivileges failed, error code = %d\n", GetLastError());
        trace(temp);
        return;
    }

    PROCESS_INFORMATION *pi;
    if(!(pi = OpenHT()))
    {
        sprintf_s(temp, "\nOpenHT failed, error code = %d\n", GetLastError());
        trace(temp);
        return;
    }

    //system("start \"\" \"T:\\\\C3S2\\\\OS\\\\HTService\\\\x64\\\\Debug\\\\OS1_START.exe\" \"D:\\\\C3S2\\\\OS\\\\HTService\\\\HT\\\\storage.ht\"");

    trace("Start Service", std::ofstream::out);
    while(ServiceStatus.dwCurrentState == SERVICE_RUNNING)
    {
	    
    }

    TerminateProcess(pi->hProcess, 0);

    // Ожидание завершения работы процесса
    WaitForSingleObject(pi->hProcess, INFINITE);

    // Закрытие дескрипторов процесса и потока
    CloseHandle(pi->hProcess);
    CloseHandle(pi->hThread);

    // Установка статуса службы на "остановлена"
    ServiceStatus.dwCurrentState = SERVICE_STOPPED;
    SetServiceStatus(hServiceStatus, &ServiceStatus);
}

VOID WINAPI ServiceHandler(DWORD fdwControl)
{
    char temp[121];
    HANDLE hStopEvent = CreateEvent(NULL,
        TRUE,
        FALSE,
        L"Global\\HTStop");

    HANDLE hStopEventExist = CreateEvent(NULL,
        TRUE,
        FALSE,
        L"Global\\HTStopExist");

    switch (fdwControl)
    {
    case SERVICE_CONTROL_STOP:
    case SERVICE_CONTROL_SHUTDOWN:
    	ServiceStatus.dwWin32ExitCode = 0;
        ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        ServiceStatus.dwCheckPoint = 0;
    	ServiceStatus.dwWaitHint = 0;
        SetEvent(hStopEventExist);
        SetEvent(hStopEvent);
    	break;

    case SERVICE_CONTROL_PAUSE:
        ServiceStatus.dwCurrentState = SERVICE_PAUSED;
    	break;

    case SERVICE_CONTROL_CONTINUE:
    {
        ServiceStatus.dwCurrentState = SERVICE_RUNNING;
        break;
    }
    case SERVICE_CONTROL_INTERROGATE: 
        break;

    default:
    	sprintf_s(temp, "Unrecognized opcode %d\n", fdwControl);
    	trace(temp);
        break;
    }

    if (!SetServiceStatus(hServiceStatus, &ServiceStatus))
    {
        sprintf_s(temp, "SetServiceStatus failed, error code = %d\n", GetLastError());
    	trace(temp);
        return;
    }
}

void trace(const char* msg, int r)
{
	std::ofstream out;
	out.open(TRACEPATH, r);
	out << msg << "\n";
	out.close();
}
