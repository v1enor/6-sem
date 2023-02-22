// PortIO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
CRITICAL_SECTION cs;
HANDLE hp;
DWORD WINAPI mythread(LPVOID); 
int _tmain(int argc, _TCHAR* argv[])
{
	
	OVERLAPPED ovlx;	ovlx.Offset = 0;	ovlx.OffsetHigh = 0;	ovlx.hEvent = 0;
	OVERLAPPED ovly;	ovly.Offset = 0;	ovly.OffsetHigh = 0;	ovly.hEvent = 0;
	char bufx[30], bufy[30];
	DWORD realreadx = 0,realready = 0;
	HANDLE hfx  = CreateFile(L"D:\\XXX.txt", GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);
	HANDLE hfy  = CreateFile(L"D:\\YYY.txt", GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);
	
	hp = CreateIoCompletionPort(hfx, NULL, (ULONG)77,2); 
	     CreateIoCompletionPort(hfy, hp,   (ULONG)88,3);     

	InitializeCriticalSection(&cs);
	HANDLE ht1 = CreateThread(NULL,0,mythread,NULL,0,NULL);  
	HANDLE ht2 = CreateThread(NULL,0,mythread,NULL,0,NULL);
    HANDLE ht3 = CreateThread(NULL,0,mythread,NULL,0,NULL);

	for (int k = 0; k < 10; k++)
	{
	  ReadFile(hfx,(LPVOID)bufx,12,&realreadx, &ovlx);
	  WaitForSingleObject(hfx,INFINITE);
	  ovlx.Offset+=realreadx;
      
	  PostQueuedCompletionStatus(hp, 0, 99, NULL);
	  
	  ReadFile(hfy,(LPVOID)bufy,12,&realready, &ovly);
	  WaitForSingleObject(hfy,INFINITE);
	  ovly.Offset+=realready;
	
	};  
	
	PostQueuedCompletionStatus(hp, 0, 99, NULL);

	CloseHandle(hfx);	CloseHandle(hfy);
	WaitForSingleObject(ht1,INFINITE); WaitForSingleObject(ht2,INFINITE); WaitForSingleObject(ht3,INFINITE); 
	DeleteCriticalSection(&cs); 
	system("pause");
	
	return 0;
}
DWORD WINAPI mythread(LPVOID)
{
	int k = 0;
	DWORD nb =  0;
	ULONG key = 0;
	LPOVERLAPPED lpovl;
	while(GetQueuedCompletionStatus(hp,&nb, &key, &lpovl,INFINITE))
	{
        EnterCriticalSection(&cs);	
		std::cout<<std::endl<<k++<<": " <<"ThreadID: "<< GetCurrentThreadId()<< " key: "<< key;
		LeaveCriticalSection(&cs);
	}
	return 0;
}
