#pragma once
#include <Windows.h>


//#ifdef MATHLIBRARY_EXPORTS
//#define MATHLIBRARY_API __declspec(dllexport)
//#else
//#define MATHLIBRARY_API __declspec(dllimport)
//#endif


#define MATHLIBRARY_API __declspec(dllexport)

namespace HT    // HT API
{
	// API HT - ����������� ��������� ��� ������� � ��-��������� 
	//          ��-��������� ������������� ��� �������� ������ � �� � ������� ����/��������
	//          ���������������� (�����������) ������ �������������� � ������� snapshot-���������� 
	//          Create - �������  � ������� HT-��������� ��� �������������   
	//          Open   - ������� HT-��������� ��� �������������
	//          Insert - ������� ������� ������
	//          Delete - ������� ������� ������    
	//          Get    - ������  ������� ������
	//          Update - �������� ������� ������
	//          Snap   - �������� snapshot
	//          Close  - ��������� Snap � ������� HT-��������� ��� �������������
	//          GetLastError - �������� ��������� � ��������� ������


	MATHLIBRARY_API struct HTHANDLE    // ���� ���������� HT
	{
		HTHANDLE();
		MATHLIBRARY_API HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const wchar_t FileName[512]);
		int     Capacity = 20;               // ������� ��������� � ���������� ��������� 
		int     SecSnapshotInterval = 120;    // ������������� ���������� � ���. 
		int     MaxKeyLength = 64;           // ������������ ����� �����
		int     MaxPayloadLength = 64;       // ������������ ����� ������
		wchar_t    FileName[512] = L"map.txt";          // ��� ����� 
		HANDLE  File = 0;                   // File HANDLE != 0, ���� ���� ������
		HANDLE  FileMapping = 0;            // Mapping File HANDLE != 0, ���� mapping ������  
		LPVOID  Addr = 0;                   // Addr != NULL, ���� mapview ��������. ����� � ����� ���������� ��������  
		char    LastErrorMessage[512] = "\0";  // ��������� �� ��������� ������ ��� 0x00  
		time_t  lastsnaptime = 0;           // ���� ���������� snap'a (time())  
		bool letjoin;

		wchar_t mutexName[512];
		wchar_t fileMapName[512];
		wchar_t timerName[512];
		DWORD creatorPid;
		HANDLE hTimer;
		HANDLE hTimerThread;
	};

	extern "C" MATHLIBRARY_API struct Element   // ������� 
	{
		//Element();
		Element(const void* key, int keylength);                                             // for Get
		MATHLIBRARY_API Element(const void* key, int keylength, const void* payload, int  payloadlength);    // for Insert
		//MATHLIBRARY_API Element(Element* oldelement, const void* newpayload, int  newpayloadlength);         // for update
		void* key;                 // �������� ����� 
		int             keylength;           // ������ �����
		void* payload;             // ������ 
		int             payloadlength;       // ������ ������
	};

	extern "C" MATHLIBRARY_API HTHANDLE* Create   //  ������� HT             
	(
		int	  Capacity,					   // ������� ���������
		int   SecSnapshotInterval,		   // ������������� ���������� � ���.
		int   MaxKeyLength,                // ������������ ������ �����
		int   MaxPayloadLength,            // ������������ ������ ������
		const char  FileName[512]          // ��� ����� 
	); 	// != NULL �������� ����������  

	extern "C" MATHLIBRARY_API  HTHANDLE* Open     //  ������� HT             
	(
		const char    FileName[512]         // ��� ����� 
	); 	// != NULL �������� ����������  

	extern "C" MATHLIBRARY_API  BOOL Snap         // ��������� Snapshot
	(
		const HTHANDLE* hthandle           // ���������� HT (File, FileMapping)
	);


	extern "C" MATHLIBRARY_API BOOL Close        // Snap � ������� HT  �  �������� HTHANDLE
	(
		const HTHANDLE* hthandle           // ���������� HT (File, FileMapping)
	);	//  == TRUE �������� ����������   


	extern "C" MATHLIBRARY_API BOOL Insert      // �������� ������� � ���������
	(
		const HTHANDLE* hthandle,            // ���������� HT
		const Element* element              // �������
	);	//  == TRUE �������� ���������� 


	extern "C" MATHLIBRARY_API BOOL Delete      // ������� ������� � ���������
	(
		const HTHANDLE* hthandle,            // ���������� HT (����)
		const Element* element              // ������� 
	);	//  == TRUE �������� ���������� 

	extern "C" MATHLIBRARY_API Element* Get     //  ������ ������� � ���������
	(
		const HTHANDLE* hthandle,            // ���������� HT
		const Element* element              // ������� 
	); 	//  != NULL �������� ���������� 

	extern "C" MATHLIBRARY_API int PrintAll     // print all elements aand return their count
	(
		HTHANDLE* ht           // ���������� HT
	); 	//  != NULL �������� ���������� 


	extern "C" MATHLIBRARY_API BOOL Update     //  ������� ������� � ���������
	(
		const HTHANDLE* hthandle,            // ���������� HT
		const Element* oldelement,          // ������ ������� (����, ������ �����)
		const void* newpayload,          // ����� ������  
		int             newpayloadlength     // ������ ����� ������
	); 	//  != NULL �������� ���������� 

	extern "C" MATHLIBRARY_API char* GetLastHtError  // �������� ��������� � ��������� ������
	(
		HTHANDLE* ht                         // ���������� HT
	);

	extern "C" MATHLIBRARY_API void print                               // ����������� ������� 
	(
		const Element* element              // ������� 
	);
	extern "C" MATHLIBRARY_API int sum(int a, int b);
};
