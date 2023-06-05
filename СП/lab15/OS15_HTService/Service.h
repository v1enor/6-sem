#pragma once
#include <iostream>
#include <windows.h>
#include <fstream>

#define SERVICENAME L"OS_ILUSHA"
#define TRACEPATH "D:\\Service.trace"

VOID ServiceWorkerThread();
VOID WINAPI  ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
VOID WINAPI ServiceHandler(DWORD fdwControl);

void trace(const char* msg, int r = std::ofstream::app);

extern BOOL bServicePause;