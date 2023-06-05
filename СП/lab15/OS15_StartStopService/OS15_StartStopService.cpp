#include <Windows.h>
#include <iostream>
#include <string>

#define SERVICENAME L"OS_ILUSHA"
#define SERVICEPATH L"C:\\Users\\Administrator\\Desktop\\HTService\\x64\\Debug\\OS15_HTService.exe"

char* errortxt(const char* msg, int code)
{
	char* buf = new char[512];
	sprintf_s(buf, 512, "%s: error code = %d\n", msg, code);
	return buf;
}

int main(int argc, char* argv[])
{
	SC_HANDLE schSCManager = NULL, schService = NULL;
	SERVICE_STATUS status;
	try
	{
		schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (!schSCManager)
			throw errortxt("OpenSCManager", GetLastError());

		if (std::string(argv[1]) == "/i")
		{
			schService = CreateService(
				schSCManager,
				SERVICENAME,
				SERVICENAME,
				SERVICE_ALL_ACCESS,
				SERVICE_WIN32_OWN_PROCESS,
				SERVICE_AUTO_START,
				SERVICE_ERROR_NORMAL,
				SERVICEPATH,
				NULL,
				NULL,
				NULL,
				NULL,//UserName.c_str(),
				NULL//UserPassword.c_str()
			);

			if (!schService)
				throw errortxt("CreateService", GetLastError());

			std::cout << "Successfully create service" << std::endl;
		}
		else if (std::string(argv[1]) == "/d")
		{
			schService = OpenService(schSCManager, SERVICENAME, DELETE);
			if (!schService)
			{
				printf("Failed to open service. Error code: %d\n", GetLastError());
				throw errortxt("OpenService", GetLastError());
			}

			if (!DeleteService(schService))
			{
				printf("Failed to delete service. Error code: %d\n", GetLastError());
				throw errortxt("DeleteService", GetLastError());
			}

			std::cout << "Service deleted successfully." << std::endl;
		}
		else if (std::string(argv[1]) == "/start")
		{
			schService = OpenService(schSCManager, SERVICENAME, SERVICE_START);
			if (!schService)
			{
				printf("Failed to open service. Error code: %d\n", GetLastError());
				throw errortxt("OpenService", GetLastError());
			}

			if (!StartServiceW(schService, 0, NULL))
				throw errortxt("StartService", GetLastError());

			std::cout << "Service started successfully." << std::endl;
		}
		else if (std::string(argv[1]) == "/stop")
		{
			schService = OpenService(schSCManager, SERVICENAME, SERVICE_ACCEPT_SHUTDOWN);
			if (!schService)
			{
				printf("Failed to open service. Error code: %d\n", GetLastError());
				throw errortxt("OpenService", GetLastError());
			}

			if (!ControlService(schService, SERVICE_CONTROL_STOP, &status))
				throw errortxt("ControlService", GetLastError());

			std::cout << "Service stopped successfully." << std::endl;
		}
		else
		{
			throw "Invalid command line argument.";
		}
	}
	catch (const char* txt)
	{
		std::cout << txt << "\n";
	}

	if (schService)
		CloseServiceHandle(schService);

	if (schSCManager)
		CloseServiceHandle(schSCManager);

	system("pause");
	return 0;
}
