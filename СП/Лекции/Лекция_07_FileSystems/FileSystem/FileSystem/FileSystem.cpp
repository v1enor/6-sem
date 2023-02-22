// FileSystem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream.h>
 






int _tmain(int argc, _TCHAR* argv[])
{



	

	return 0;
}


//HANDLE CreateFile(                    // �������� � �������� �����
//        LPCSTR lpFileName,            // ������ ���  
//        DWORD dwDesiredAccess,        // ������ ������� 
//        DWORD dwShareMode,            // ����� ����������� �������������
//        LPSECURITY_ATTRIBUTES lpSecurityAttributes,  // �������� ������
//        DWORD dwCreationDisposition,  // c������� ��� �������� �����       
//        DWORD dwFlagsAndAttributes,   // ����� � ��������
//        HANDLE hTemplateFile        // ���� ���������
//    );
//  INVALID_HANDLE_VALUE  - � ������ ������ (GetLastError)
// 
//   dwDesiredAccess  NULL (������ ���������� �������� �������)
//                    ���������� GENERIC_READ|GENERIC_WRITE
//   dwShareMode      NULL(�� ������������ ���������)
//                    ���������� FILE_SHARE_WRITE|FILE_SHARE_READ
//                    FILE_SHARE_DELETE (���� ��������� ����� ����� �������)
// dwCreationDisposition {CREATE_NEW, OPEN_EXISTING,  OPEN_ALWAYS, 
//                        TRUNCATE_EXISTING, CREATE_ALWAYS}
// dwFlagsAndAttributes  FILE_ATTRIBUTE_ARCHIVE|FILE_ATTRIBUTE_HIDDEN ...
//                       FILE_FLAG_POSIX_SEMANTICS (��������POSIX), ...
// hTemplateFile         HANDLE �����-������� ��� ��������� (����� NULL
//------------------------------------------------------------------------------------------

//
// BOOL DeleteFileW(
//    LPCWSTR lpFileName // ������ ���  
//                 );
//
//BOOL WriteFile(            //  ������ � ���� 
//              HANDLE hFile,                   // ����     
//              LPCVOID lpBuffer,               // ����� 
//              DWORD nNumberOfBytesToWrite,    // ������ ����
//              LPDWORD lpNumberOfBytesWritten, // �������� ����
//              LPOVERLAPPED lpOverlapped       // ��� ���������� ������
//    );




//BOOL FlushFileBuffers( // ��������� ����� 
//                 HANDLE hFile   // ����
//                );

//BOOL ReadFile(
//            HANDLE hFile,                 // ���� 
//            LPVOID lpBuffer,              // ����� 
//            DWORD nNumberOfBytesToRead,   // ������ ����
//            LPDWORD lpNumberOfBytesRead,  // ���������� ����
//            LPOVERLAPPED lpOverlapped     // ��� ���������� ������
//    );
//


//BOOL CopyFile(
//          LPCWSTR lpExistingFileName,  // ���  ����� 
//          LPCWSTR lpNewFileName,       // ���  ������  �����
//          BOOL bFailIfExists           // ���� ���� ?  (FALSE -������������)
//    );

//BOOL MoveFileW(
//    LPCWSTR lpExistingFileName, // ���  ����� 
//    LPCWSTR lpNewFileName         // ���  ������  �����
//    );


//BOOL ReplaceFile(  // ��������� 
//            LPCWSTR lpReplacedFileName,      // ���  ����� 
//            LPCWSTR lpReplacementFileName,   // ���  ������  �����
//            LPCWSTR lpBackupFileName,        // ���  ������ ����������  �����
//            DWORD   dwReplaceFlags,          // ����� ���������
//            LPVOID  lpExclude,               // �� ������������ 
//            LPVOID  lpReserved               // �� ������������
//    );


//DWORD SetFilePointer(  // �������� ��������� 
//                 HANDLE hFile,               
//                 LONG lDistanceToMove,        // ������� ����� ������ 
//                 PLONG lpDistanceToMoveHigh,  // �������  ����� ������ [IN, OUT] 
//                 DWORD dwMoveMethod           // ������� ������� {FILE_BEGIN,FILE_CURRENT,FILE_END}
//           );
// ���������� ������� ����� ����� �������, ������� � lDistanceToMove,  
// ���� ������������� �� 0 - ������� ������� ������� 


//BOOL SetFilePointerEx( // �������� ��������� WindowsNT 
//      HANDLE hFile,                      // ���� 
//      LARGE_INTEGER liDistanceToMove,    //  ����� 
//	  PLARGE_INTEGER lpNewFilePointer,     // ����� ������� [out] 
//      DWORD dwMoveMethod                 // ������� ������� {FILE_BEGIN,FILE_CURRENT,FILE_END}
//    );


//DWORD GetFileAttributesA(        // �������� �������� 
//            LPCSTR lpFileName     // ���  ����� 
//                       );


//BOOL SetFileAttributesA( // ���������� �������� 
//          LPCSTR lpFileName,         // ���  ����� 
//          DWORD dwFileAttributes     // ����� ��������� 
//    );



//BOOL GetFileSizeEx(       // ���������� ����� ������ 
//                 HANDLE hFile,             // ���  ����� 
//                 PLARGE_INTEGER lpFileSize  // ������ �����  
//                 );


//BOOL SetEndOfFile(  // ���������� EndOfFile � ������� �������
//             HANDLE hFile          // ���� 
//                 );


//BOOL LockFile(     // ������������� ���� 
//      HANDLE hFile,                       // ���� 
//      DWORD dwFileOffsetLow,              // ������� ����� �������� �� ������
//      DWORD dwFileOffsetHigh,             // ������� ����� �������� 
//      DWORD nNumberOfBytesToLockLow,      // ������� ����� ���������� ���� 
//      DWORD nNumberOfBytesToLockHigh      // �������  ����� ���������� ���� 
//    );

//BOOL UnlockFile(
//       HANDLE hFile,                        // ���� 
//       DWORD dwFileOffsetLow,               // ������� ����� �������� �� ������
//       DWORD dwFileOffsetHigh,              // ������� ����� �������� 
//       DWORD nNumberOfBytesToUnlockLow,     // ������� ����� ���������� ����   
//       DWORD nNumberOfBytesToUnlockHigh     // �������  ����� ���������� ���� 
//    );



//
//BOOL GetFileInformationByHandle(
//     HANDLE hFile,                             // ����  
//     LPBY_HANDLE_FILE_INFORMATION lpFileInformation  // ���������� 
//    );
//typedef struct _BY_HANDLE_FILE_INFORMATION {
//    DWORD dwFileAttributes;           // �������� ����� 
//    FILETIME ftCreationTime;          // ����� �������� 
//    FILETIME ftLastAccessTime;        // �����  ���������� ������� 
//    FILETIME ftLastWriteTime;         // ����� ��������� ������ 
//    DWORD dwVolumeSerialNumber;       // �������� ����� ����  
//    DWORD nFileSizeHigh;              // ������� ����� �������  
//    DWORD nFileSizeLow;               // ������� ����� �������  
//    DWORD nNumberOfLinks;             // ���������� ������ �� ����  
//    DWORD nFileIndexHigh;             // ������� ����� ������� �����  
//    DWORD nFileIndexLow;              // ������� ����� ������� �����   
//} BY_HANDLE_FILE_INFORMATION, *PBY_HANDLE_FILE_INFORMATION, *LPBY_HANDLE_FILE_INFORMATION;


//BOOL FileTimeToSystemTime( ������������� ����� 
//     CONST FILETIME *lpFileTime, // ����� � ������� FILETIME 
//     LPSYSTEMTIME lpSystemTime   // ����� � ������� SystemTime
//    );


//typedef struct _SYSTEMTIME {
//    WORD wYear;
//    WORD wMonth;
//    WORD wDayOfWeek;
//    WORD wDay;
//    WORD wHour;
//    WORD wMinute;
//    WORD wSecond;
//    WORD wMilliseconds;
//} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;


//DWORD GetFileType(   // ���������� ��� �����     
//               HANDLE hFile   // ���� 
//                 );
//  {FILE_TYPE_CHAR (�������, �������), FILE_TYPE_DISK,
//  FILE_TYPE_PIPE, FILE_TYPE_UNKNOWN,FILE_TYPE_REMOTE}


    
//BOOL GetBinaryType( // ���������� ��� ���������� ����� 
//    LPCWSTR lpApplicationName, //��� ������������ �����
//    LPDWORD  lpBinaryType      //[out] ��� ������������ ����� 
//    );
//{SCS_32BIT_BINARY, SCS_64BIT_BINARY, SCS_POSIX_BINARY ...}

//BOOL CreateDirectory( // ������� ������� 
//                LPCWSTR lpPathName, //��� �������� 
//                LPSECURITY_ATTRIBUTES lpSecurityAttributes // �������� ������������ 
//                    );

//
//BOOL CreateDirectoryEx( // ������� ������� �� ������� 
//     LPCSTR lpTemplateDirectory, //��� ������� �������� 
//     LPCSTR lpNewDirectory,      //��� ��������
//     LPSECURITY_ATTRIBUTES lpSecurityAttributes // �������� ������������ 
//    );


//HANDLE FindFirstFile( // ����� ������ ���� 
//          LPCWSTR lpFileName,     // ������� ��� ������
//          LPWIN32_FIND_DATAW lpFindFileData // ����� ������ 
//       );
// WIN32_FIND_DATAA, *PWIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;
//typedef struct _WIN32_FIND_DATAW {
//    DWORD dwFileAttributes;
//    FILETIME ftCreationTime;
//    FILETIME ftLastAccessTime;
//    FILETIME ftLastWriteTime;
//    DWORD nFileSizeHigh;
//    DWORD nFileSizeLow;
//    DWORD dwReserved0;
//    DWORD dwReserved1;
//    WCHAR  cFileName[ MAX_PATH ];
//    WCHAR  cAlternateFileName[ 14 ];
//} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;
//
//BOOL FindNextFile( // ����� ������ ���� 
//     HANDLE hFindFile,  // HANDLE FindFirstFile
//     LPWIN32_FIND_DATAA lpFindFileData
//    );
//
//WINAPI FindClose( // ������� �����  
//     HANDLE hFindFile // HANDLE FindFirstFile
//    );


//BOOL RemoveDirectory( // ������� �������
//       LPCWSTR lpPathName //��� ��������
//       );

//BOOL MoveFile(
//    LPCWSTR lpExistingFileName,   // ���  ��������  
//    LPCWSTR lpNewFileName         // ���  ������  �������� 
//    );



//DWORD GetCurrentDirectory( // ���������� ������� ���������� 
//          DWORD nBufferLength,      // ������ ������  
//          LPWSTR lpBuffer           // ��������� �� �����  
//                          );
// ������� ���������� ���������� �������� ���������� � �����


//BOOL SetCurrentDirectory(  // ���������� ������� ���������� 
//                      LPCSTR lpPathName
//                        );



//HANDLE FindFirstChangeNotification(  // ���������� ���������� �� ���������  
//                           LPCWSTR lpPathName,  // ��� �������� 
//                           BOOL bWatchSubtree,  // TRUE - ��������� �� ���� �������
//                           DWORD dwNotifyFilter  // ������
//                                  );
// ������ = {FILE_NOTIFY_CHANGE_ATTRIBUTES |FILE_NOTIFY_CHANGE_DIR_NAME|
//           FILE_NOTIFY_CHANGE_FILE_NAME|FILE_NOTIFY_CHANGE_LAST_WRITE|FILE_NOTIFY_CHANGE_SIZE}

//
//BOOL FindNextChangeNotification( // ����������  ���������� �� ��������� 
//                    HANDLE hChangeHandle  // HANDLE FindFirstChangeNotification
//                               );
//
//BOOL FindCloseChangeNotification( // ����������   ���������� �� ��������� 
//                    HANDLE hChangeHandle // HANDLE FindFirstChangeNotification
//                               );
//
//DWORD WaitForSingleObject( // ������� ��������� � ��������
//                     HANDLE hHandle,         // HANDLE FindFirstChangeNotification
//                     DWORD dwMilliseconds    // 0 - INFINITY
//                      );
//  WAIT_OBJECT_0 == WaitForSingleObject() - ���� ���������   


//typedef struct _OVERLAPPED {   // ��������� ��� ������������ �����/������
//    ULONG_PTR Internal;        //��������������� Windows      
//    ULONG_PTR InternalHigh;    //��������������� Windows
//    union {
//        struct { 
//            DWORD Offset;      // ������� ����� ��������   
//            DWORD OffsetHigh;  // ������� ����� �������� 
//        };
//        PVOID Pointer;
//    };
//    HANDLE  hEvent;           // ������� (��������� �����/������)                     
//} OVERLAPPED, *LPOVERLAPPED;


//BOOL LockFileEx(  // ������������� ���� (����������)
//        HANDLE hFile,                 // ���� 
//        DWORD dwFlags,                // ����� ������������    
//        DWORD dwReserved, 
//        DWORD nNumberOfBytesToLockLow,  // ������� ����� ���������� ���� 
//        DWORD nNumberOfBytesToLockHigh, // �������  ����� ���������� ���� 
//        LPOVERLAPPED lpOverlapped       // ��������� _OVERLAPPED
//    );
//   dwFlags =  LOCKFILE_FAIL_IMMEDIATELY|LOCKFILE_EXCLUSIVE_LOCK  


//BOOL UnlockFile(
//       HANDLE hFile,                        // ���� 
//       DWORD dwFileOffsetLow,               // ������� ����� �������� �� ������
//       DWORD dwFileOffsetHigh,              // ������� ����� �������� 
//       DWORD nNumberOfBytesToUnlockLow,     // ������� ����� ���������� ����   
//       DWORD nNumberOfBytesToUnlockHigh     // �������  ����� ���������� ���� 
//    );

//BOOL UnlockFileEx(
//        HANDLE hFile,                     // ���� 
//        DWORD dwReserved,
//        DWORD nNumberOfBytesToUnlockLow,  // ������� ����� ���������� ����   
//        DWORD nNumberOfBytesToUnlockHigh, // �������  ����� ���������� ���� 
//        LPOVERLAPPED lpOverlapped          // ��������� _OVERLAPPED
//    );

//BOOL GetOverlappedResult(       // �������� ��������� �����/������ 
//     HANDLE hFile,                       // ���� 
//     LPOVERLAPPED lpOverlapped,          // ��������� _OVERLAPPED
//     LPDWORD lpNumberOfBytesTransferred, // ������� ���������� ���������� ���� 
//     BOOL bWait                          //TRUE/FALSE �����/�� ����� ���������� ��������
//    );


//BOOL CancelIo( // ������ �������� �����/������
//        HANDLE hFile // ���� 
//            );

//BOOL HasOverlappedIoCompleted( // ����������� �������� ����������? 
//						 LPOVERLAPPED lpOverlapped
//						 )



//BOOL WriteFile(            //  ������ � ���� 
//              HANDLE hFile,                   // ����     
//              LPCVOID lpBuffer,               // ����� 
//              DWORD nNumberOfBytesToWrite,    // ������ ����
//              LPDWORD lpNumberOfBytesWritten, // �������� ����
//              LPOVERLAPPED lpOverlapped       // ��� ���������� ������
//    );


//
//BOOL ReadFileEx(   //  ������ � ���� 
//       HANDLE hFile,                           // ����  
//       LPVOID lpBuffer,                        // �����  
//       DWORD nNumberOfBytesToRead,             // ������ ���� 
//       LPOVERLAPPED lpOverlapped,              // ��� ���������� ������
//       LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine // ��������� ����������
//    );
//
//
//BOOL WriteFileEx(  //  ������ ���� 
//       HANDLE hFile,                          // ����  
//       LPCVOID lpBuffer,                      // ����� 
//       DWORD nNumberOfBytesToWrite,           // ������ ���� 
//       LPOVERLAPPED lpOverlapped,             // ��� ���������� ������   
//       LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine // ��������� ����������
//    );
//
// � ������� ����������� �������� (SleepEx, WaitForSingleObjectEx, ... )
//VOID CALLBACK ���_���������( // ��������� ���������� �����/������
//       DWORD ErrorCode,                      // ��� ���������� �������� 
//       DWORD nNumberOfBytesTransfered,       // ��������� ���������� ���� 
//       LPOVERLAPPED lpOverlapped             // ���������� � ����������� �������� 
//			




//HANDLE CreateIoCompletionPort(   // ������� ���� 
//           HANDLE FileHandle,               // ����/pipe/socket
//           HANDLE ExistingCompletionPort,   // {NULL, HANDLE CreateIoCompletionPort}
//           ULONG_PTR CompletionKey,         //  ���� ����������
//           DWORD NumberOfConcurrentThreads  // ���������� ������������ �������  
//    );

//BOOL GetQueuedCompletionStatus( // �������� �����  ����� ����������
//     HANDLE CompletionPort,      //HANDLE CreateIoCompletionPort    
//     LPDWORD lpNumberOfBytesTransferred, // ���������� ���������� ������
//     PULONG_PTR lpCompletionKey, // ���� ���������� 
//     LPOVERLAPPED *lpOverlapped, // ���������  _OVERLAPPED
//     DWORD dwMilliseconds        // {INFINITE, ����� ��������}
//    );

//BOOL PostQueuedCompletionStatus( // ��c���� ����� �  ���� ����������
//      HANDLE CompletionPort,     //HANDLE CreateIoCompletionPort
//      DWORD dwNumberOfBytesTransferred, // � GetQueuedCompletionStatus
//      ULONG_PTR dwCompletionKey,        // � GetQueuedCompletionStatus
//      LPOVERLAPPED lpOverlapped         // � GetQueuedCompletionStatus 
//    );




