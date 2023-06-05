#pragma once

#include <string>

struct HTHANDLE
{
	HTHANDLE();
	HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const wchar_t FileName[512]);
	int     Capacity;               // емкость хранилища в количестве элементов 
	int     SecSnapshotInterval;    // переодичность сохранения в сек. 
	int     MaxKeyLength;           // максимальная длина ключа
	int     MaxPayloadLength;       // максимальная длина данных
	char    FileName[512];          // имя файла 
	HANDLE  File;                   // File HANDLE != 0, если файл открыт
	HANDLE  FileMapping;            // Mapping File HANDLE != 0, если mapping создан  
	LPVOID  Addr;                   // Addr != NULL, если mapview выполнен  
	char    LastErrorMessage[512];  // сообщение об последней ошибке или 0x00  
	time_t  lastsnaptime;           // дата последнего snap'a (time())  

	HANDLE Mutex;
	int N;//текущее заполнение
	HANDLE SnapshotThread;

};

struct Element
{
	Element();
	Element(const void* key, int keylength);                                             // for Get
	Element(const void* key, int keylength, const void* payload, int  payloadlength);    // for Insert
	Element(Element* oldelement, const void* newpayload, int  newpayloadlength);         // for update
	void* key;                 // значение ключа 
	int             keylength;           // рахмер ключа
	void* payload;             // данные 
	int             payloadlength;       // размер данных
};