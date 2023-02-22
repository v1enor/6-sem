// FileSystem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream.h>
 






int _tmain(int argc, _TCHAR* argv[])
{



	

	return 0;
}


//HANDLE CreateFile(                    // создание и открытие файла
//        LPCSTR lpFileName,            // полное имя  
//        DWORD dwDesiredAccess,        // способ доступа 
//        DWORD dwShareMode,            // режим совместного использования
//        LPSECURITY_ATTRIBUTES lpSecurityAttributes,  // атрибуты защиты
//        DWORD dwCreationDisposition,  // cоздание или открытие файла       
//        DWORD dwFlagsAndAttributes,   // флаги и атрибуты
//        HANDLE hTemplateFile        // файл атрибутов
//    );
//  INVALID_HANDLE_VALUE  - в случае ошибки (GetLastError)
// 
//   dwDesiredAccess  NULL (только определять атрибуты доступа)
//                    комбинация GENERIC_READ|GENERIC_WRITE
//   dwShareMode      NULL(не используется совместно)
//                    комбинация FILE_SHARE_WRITE|FILE_SHARE_READ
//                    FILE_SHARE_DELETE (если прогрвммы имеют право удалять)
// dwCreationDisposition {CREATE_NEW, OPEN_EXISTING,  OPEN_ALWAYS, 
//                        TRUNCATE_EXISTING, CREATE_ALWAYS}
// dwFlagsAndAttributes  FILE_ATTRIBUTE_ARCHIVE|FILE_ATTRIBUTE_HIDDEN ...
//                       FILE_FLAG_POSIX_SEMANTICS (стандартPOSIX), ...
// hTemplateFile         HANDLE файла-образца для атрибутов (везде NULL
//------------------------------------------------------------------------------------------

//
// BOOL DeleteFileW(
//    LPCWSTR lpFileName // полное имя  
//                 );
//
//BOOL WriteFile(            //  писать в файл 
//              HANDLE hFile,                   // файл     
//              LPCVOID lpBuffer,               // буфер 
//              DWORD nNumberOfBytesToWrite,    // писать байт
//              LPDWORD lpNumberOfBytesWritten, // записано байт
//              LPOVERLAPPED lpOverlapped       // для аснхронной записи
//    );




//BOOL FlushFileBuffers( // освободть буфер 
//                 HANDLE hFile   // файл
//                );

//BOOL ReadFile(
//            HANDLE hFile,                 // файл 
//            LPVOID lpBuffer,              // буфер 
//            DWORD nNumberOfBytesToRead,   // читать байт
//            LPDWORD lpNumberOfBytesRead,  // прочитатно байт
//            LPOVERLAPPED lpOverlapped     // для аснхронной работы
//    );
//


//BOOL CopyFile(
//          LPCWSTR lpExistingFileName,  // имя  файла 
//          LPCWSTR lpNewFileName,       // имя  нового  файла
//          BOOL bFailIfExists           // если есть ?  (FALSE -перезаписать)
//    );

//BOOL MoveFileW(
//    LPCWSTR lpExistingFileName, // имя  файла 
//    LPCWSTR lpNewFileName         // имя  нового  файла
//    );


//BOOL ReplaceFile(  // замещение 
//            LPCWSTR lpReplacedFileName,      // имя  файла 
//            LPCWSTR lpReplacementFileName,   // имя  нового  файла
//            LPCWSTR lpBackupFileName,        // имя  нового резервного  файла
//            DWORD   dwReplaceFlags,          // опции замещения
//            LPVOID  lpExclude,               // не используется 
//            LPVOID  lpReserved               // не используется
//    );


//DWORD SetFilePointer(  // сдвинуть указатель 
//                 HANDLE hFile,               
//                 LONG lDistanceToMove,        // младшая часть сдвига 
//                 PLONG lpDistanceToMoveHigh,  // старшая  часть сдвига [IN, OUT] 
//                 DWORD dwMoveMethod           // текущая позиция {FILE_BEGIN,FILE_CURRENT,FILE_END}
//           );
// возвращает младшую новой часть позиции, старшая в lDistanceToMove,  
// если переместиться на 0 - полчишь текущую позицию 


//BOOL SetFilePointerEx( // сдвинуть указатель WindowsNT 
//      HANDLE hFile,                      // файл 
//      LARGE_INTEGER liDistanceToMove,    //  сдвиг 
//	  PLARGE_INTEGER lpNewFilePointer,     // новая позиция [out] 
//      DWORD dwMoveMethod                 // текущая позиция {FILE_BEGIN,FILE_CURRENT,FILE_END}
//    );


//DWORD GetFileAttributesA(        // получить атрибуты 
//            LPCSTR lpFileName     // имя  файла 
//                       );


//BOOL SetFileAttributesA( // установить атрибуты 
//          LPCSTR lpFileName,         // имя  файла 
//          DWORD dwFileAttributes     // маска атрибутов 
//    );



//BOOL GetFileSizeEx(       // определить разме рфайла 
//                 HANDLE hFile,             // имя  файла 
//                 PLARGE_INTEGER lpFileSize  // размер файла  
//                 );


//BOOL SetEndOfFile(  // установить EndOfFile в текущую позицию
//             HANDLE hFile          // файл 
//                 );


//BOOL LockFile(     // заблокировать файл 
//      HANDLE hFile,                       // файл 
//      DWORD dwFileOffsetLow,              // младшая часть смещения от начала
//      DWORD dwFileOffsetHigh,             // старшая часть смещения 
//      DWORD nNumberOfBytesToLockLow,      // младшая часть количества байт 
//      DWORD nNumberOfBytesToLockHigh      // старшая  часть количества байт 
//    );

//BOOL UnlockFile(
//       HANDLE hFile,                        // файл 
//       DWORD dwFileOffsetLow,               // младшая часть смещения от начала
//       DWORD dwFileOffsetHigh,              // старшая часть смещения 
//       DWORD nNumberOfBytesToUnlockLow,     // младшая часть количества байт   
//       DWORD nNumberOfBytesToUnlockHigh     // старшая  часть количества байт 
//    );



//
//BOOL GetFileInformationByHandle(
//     HANDLE hFile,                             // файл  
//     LPBY_HANDLE_FILE_INFORMATION lpFileInformation  // информация 
//    );
//typedef struct _BY_HANDLE_FILE_INFORMATION {
//    DWORD dwFileAttributes;           // атрибуты файла 
//    FILETIME ftCreationTime;          // время создания 
//    FILETIME ftLastAccessTime;        // время  последнего доступа 
//    FILETIME ftLastWriteTime;         // время последней записи 
//    DWORD dwVolumeSerialNumber;       // серийный номер тома  
//    DWORD nFileSizeHigh;              // старшая часть размера  
//    DWORD nFileSizeLow;               // младшая часть размера  
//    DWORD nNumberOfLinks;             // количество ссылок на файл  
//    DWORD nFileIndexHigh;             // старшая часть индекса файла  
//    DWORD nFileIndexLow;              // младшая часть индекса файла   
//} BY_HANDLE_FILE_INFORMATION, *PBY_HANDLE_FILE_INFORMATION, *LPBY_HANDLE_FILE_INFORMATION;


//BOOL FileTimeToSystemTime( преобразовать время 
//     CONST FILETIME *lpFileTime, // время в формате FILETIME 
//     LPSYSTEMTIME lpSystemTime   // время в формате SystemTime
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


//DWORD GetFileType(   // определить тип файла     
//               HANDLE hFile   // файл 
//                 );
//  {FILE_TYPE_CHAR (принтер, консоль), FILE_TYPE_DISK,
//  FILE_TYPE_PIPE, FILE_TYPE_UNKNOWN,FILE_TYPE_REMOTE}


    
//BOOL GetBinaryType( // определить тип исполняого файла 
//    LPCWSTR lpApplicationName, //имя мсаолняемого файла
//    LPDWORD  lpBinaryType      //[out] тип исполняемого файла 
//    );
//{SCS_32BIT_BINARY, SCS_64BIT_BINARY, SCS_POSIX_BINARY ...}

//BOOL CreateDirectory( // создать каталог 
//                LPCWSTR lpPathName, //имя каталога 
//                LPSECURITY_ATTRIBUTES lpSecurityAttributes // атрибуты безопасности 
//                    );

//
//BOOL CreateDirectoryEx( // создать каталог по шаблону 
//     LPCSTR lpTemplateDirectory, //имя шаблона каталога 
//     LPCSTR lpNewDirectory,      //имя каталога
//     LPSECURITY_ATTRIBUTES lpSecurityAttributes // атрибуты безопасности 
//    );


//HANDLE FindFirstFile( // найти первый файл 
//          LPCWSTR lpFileName,     // образец для поиска
//          LPWIN32_FIND_DATAW lpFindFileData // адрес данных 
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
//BOOL FindNextFile( // найти первый файл 
//     HANDLE hFindFile,  // HANDLE FindFirstFile
//     LPWIN32_FIND_DATAA lpFindFileData
//    );
//
//WINAPI FindClose( // закрыть поиск  
//     HANDLE hFindFile // HANDLE FindFirstFile
//    );


//BOOL RemoveDirectory( // удалить каталог
//       LPCWSTR lpPathName //имя каталога
//       );

//BOOL MoveFile(
//    LPCWSTR lpExistingFileName,   // имя  каталога  
//    LPCWSTR lpNewFileName         // имя  нового  каталога 
//    );



//DWORD GetCurrentDirectory( // определить текущий директорий 
//          DWORD nBufferLength,      // размер буфера  
//          LPWSTR lpBuffer           // указатель на буфер  
//                          );
// функция возвращает количество символов записанных в буфер


//BOOL SetCurrentDirectory(  // установить текущий директорий 
//                      LPCSTR lpPathName
//                        );



//HANDLE FindFirstChangeNotification(  // установить наблюдение за каталогом  
//                           LPCWSTR lpPathName,  // имя каталога 
//                           BOOL bWatchSubtree,  // TRUE - наблюдать за всем деревом
//                           DWORD dwNotifyFilter  // фильтр
//                                  );
// фильтр = {FILE_NOTIFY_CHANGE_ATTRIBUTES |FILE_NOTIFY_CHANGE_DIR_NAME|
//           FILE_NOTIFY_CHANGE_FILE_NAME|FILE_NOTIFY_CHANGE_LAST_WRITE|FILE_NOTIFY_CHANGE_SIZE}

//
//BOOL FindNextChangeNotification( // продолжить  наблюдение за каталогом 
//                    HANDLE hChangeHandle  // HANDLE FindFirstChangeNotification
//                               );
//
//BOOL FindCloseChangeNotification( // остановить   наблюдение за каталогом 
//                    HANDLE hChangeHandle // HANDLE FindFirstChangeNotification
//                               );
//
//DWORD WaitForSingleObject( // ожидать изменения в каталоге
//                     HANDLE hHandle,         // HANDLE FindFirstChangeNotification
//                     DWORD dwMilliseconds    // 0 - INFINITY
//                      );
//  WAIT_OBJECT_0 == WaitForSingleObject() - есть изменения   


//typedef struct _OVERLAPPED {   // структура для асинхронного ввода/вывода
//    ULONG_PTR Internal;        //зарезервировано Windows      
//    ULONG_PTR InternalHigh;    //зарезервировано Windows
//    union {
//        struct { 
//            DWORD Offset;      // младшая часть смещения   
//            DWORD OffsetHigh;  // старшая часть смещения 
//        };
//        PVOID Pointer;
//    };
//    HANDLE  hEvent;           // событие (окончание ввода/вывода)                     
//} OVERLAPPED, *LPOVERLAPPED;


//BOOL LockFileEx(  // заблокировать файл (асинхронно)
//        HANDLE hFile,                 // файл 
//        DWORD dwFlags,                // опции блокирования    
//        DWORD dwReserved, 
//        DWORD nNumberOfBytesToLockLow,  // младшая часть количества байт 
//        DWORD nNumberOfBytesToLockHigh, // старшая  часть количества байт 
//        LPOVERLAPPED lpOverlapped       // структура _OVERLAPPED
//    );
//   dwFlags =  LOCKFILE_FAIL_IMMEDIATELY|LOCKFILE_EXCLUSIVE_LOCK  


//BOOL UnlockFile(
//       HANDLE hFile,                        // файл 
//       DWORD dwFileOffsetLow,               // младшая часть смещения от начала
//       DWORD dwFileOffsetHigh,              // старшая часть смещения 
//       DWORD nNumberOfBytesToUnlockLow,     // младшая часть количества байт   
//       DWORD nNumberOfBytesToUnlockHigh     // старшая  часть количества байт 
//    );

//BOOL UnlockFileEx(
//        HANDLE hFile,                     // файл 
//        DWORD dwReserved,
//        DWORD nNumberOfBytesToUnlockLow,  // младшая часть количества байт   
//        DWORD nNumberOfBytesToUnlockHigh, // старшая  часть количества байт 
//        LPOVERLAPPED lpOverlapped          // структура _OVERLAPPED
//    );

//BOOL GetOverlappedResult(       // получить состояние ввода/вывода 
//     HANDLE hFile,                       // файл 
//     LPOVERLAPPED lpOverlapped,          // структура _OVERLAPPED
//     LPDWORD lpNumberOfBytesTransferred, // текущее количество переданных байт 
//     BOOL bWait                          //TRUE/FALSE ждать/не ждать завершения операции
//    );


//BOOL CancelIo( // отмена операции ввода/вывода
//        HANDLE hFile // файл 
//            );

//BOOL HasOverlappedIoCompleted( // асинхронная операция завешилась? 
//						 LPOVERLAPPED lpOverlapped
//						 )



//BOOL WriteFile(            //  писать в файл 
//              HANDLE hFile,                   // файл     
//              LPCVOID lpBuffer,               // буфер 
//              DWORD nNumberOfBytesToWrite,    // писать байт
//              LPDWORD lpNumberOfBytesWritten, // записано байт
//              LPOVERLAPPED lpOverlapped       // для аснхронной записи
//    );


//
//BOOL ReadFileEx(   //  писать в файл 
//       HANDLE hFile,                           // файл  
//       LPVOID lpBuffer,                        // буфер  
//       DWORD nNumberOfBytesToRead,             // писать байт 
//       LPOVERLAPPED lpOverlapped,              // для аснхронной записи
//       LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine // процедура завершения
//    );
//
//
//BOOL WriteFileEx(  //  читать файл 
//       HANDLE hFile,                          // файл  
//       LPCVOID lpBuffer,                      // буфер 
//       DWORD nNumberOfBytesToWrite,           // писать байт 
//       LPOVERLAPPED lpOverlapped,             // для аснхронной записи   
//       LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine // процедура завершения
//    );
//
// в очередь асинхронных процедур (SleepEx, WaitForSingleObjectEx, ... )
//VOID CALLBACK имя_процедуры( // процедура завершения ввода/вывода
//       DWORD ErrorCode,                      // код завершения операции 
//       DWORD nNumberOfBytesTransfered,       // количетво переданных байт 
//       LPOVERLAPPED lpOverlapped             // информация о асинхронной операции 
//			




//HANDLE CreateIoCompletionPort(   // создать порт 
//           HANDLE FileHandle,               // файл/pipe/socket
//           HANDLE ExistingCompletionPort,   // {NULL, HANDLE CreateIoCompletionPort}
//           ULONG_PTR CompletionKey,         //  ключ завершения
//           DWORD NumberOfConcurrentThreads  // количество параллельных потоков  
//    );

//BOOL GetQueuedCompletionStatus( // получить пакет  порта завершения
//     HANDLE CompletionPort,      //HANDLE CreateIoCompletionPort    
//     LPDWORD lpNumberOfBytesTransferred, // количество переданных байтов
//     PULONG_PTR lpCompletionKey, // ключ завершения 
//     LPOVERLAPPED *lpOverlapped, // структура  _OVERLAPPED
//     DWORD dwMilliseconds        // {INFINITE, время ожидания}
//    );

//BOOL PostQueuedCompletionStatus( // поcлать пакет в  порт завершения
//      HANDLE CompletionPort,     //HANDLE CreateIoCompletionPort
//      DWORD dwNumberOfBytesTransferred, // в GetQueuedCompletionStatus
//      ULONG_PTR dwCompletionKey,        // в GetQueuedCompletionStatus
//      LPOVERLAPPED lpOverlapped         // в GetQueuedCompletionStatus 
//    );




