#pragma once

#include <string>
#include "Element.h"
using namespace std;

#define DEFAULT_FILE_NAME "map.txt"


namespace HT    // HT API
{

	/**
	* HT-storage created for storing data in RAM in key-value format
	* Data conservation is ensured by the snapshot-mechanic
	*/
	class HashTable    
	{
		public:

		/**
		* Default constructor of HashTable, set vars and allocates memory for hash table
		* After this constructor HashTable ready for work
		* -----------Default Values-----------
		* Capacity = 20 - max capacity of elements in HashTable
		* SnapShotIntervalInSec = 120 - ones at this time hashtable will make snapshot from RAM to drive 
		* MaxKeyLength = 64 - max length of key
		* MaxValueLength = 64 - max length of value
		* FileName = file with name DEFAULT_FILE_NAME will be created in the folder where executable file is located
		*/
		HashTable();

		/**
		* Constructor of HashTable, set vars and allocates memory for hash table
		* After this constructor HashTable ready for work
		* -----------Default Values-----------
		* Capacity - max capacity of elements in HashTable
		* SnapShotIntervalInSec - ones at this time hashtable will make snapshot from RAM to drive
		* MaxKeyLength - max length of key
		* MaxValueLength - max length of value
		* FileName - name of file in the folder where executable file is located
		*/
		HashTable(int inCapacity, int inSecSnapshotInterval, int inMaxKeyLength, int inMaxValueLength, string inFileName);

		/**
		* Destructor of element, need for clearing data of HashTable
		*/
		~HashTable();

		/**
		* HT-storage capacity in elements count
		*/
		int GetCapacity() const;

		/**
		* HT-storage size in elements count
		*/
		int GetCurrentSize() const;

		/**
		* HT-storage timer interval in seconds that saves data from RAM to the drive
		*/
		int GetSnapShotInterval() const;

		/**
		* Change HT-storage interval for timer, which saves data from RAM to the drive every inSnapShotIntervalInSec 
		*/
		void ChangeSnapShotInterval(const int inSnapShotIntervalInSec);

		/**
		* Max length in bytes for HT-storage Element key
		*/
		int GetMaxKeyLength() const;

		/**
		* Change max length in bytes for HT-storage Element key
		*/
		void SetMaxKeyLength(const int inMaxKeyLength);

		/**
		* Max length in bytes for HT-storage Element value
		*/
		int GetMaxValueLength() const;

		/**
		* Change max length in bytes for HT-storage Element value
		*/
		void SetMaxValueLength(const int inMaxValueLength);

		/**
		* Address of first HT-storage Element in the RAM
		*/
		void* GetElementsStartAddress() const;

		/**
		* Time in tics when last conservation was made 
		*/
		time_t GetLastSnapShotTime() const;

		/**
		* Last error message. Will be empty if there wasn't an error
		*/
		string GetLastErrorMessage() const;

		/**
		* Get file name of physical view of hash table
		*/
		wstring GetFileName() const;

		/**
		* Add new element to the HashTable
		*/
		bool Insert(const char* inKey, int inKeyLength, const char* inValue, int inValueLength);

		/**
		* Delete element from HashTable and clear memory
		*/
		bool Delete(const char* inElementKey);

		/**
		* Delete all elements from table
		*/
		void Clear();

		/**
		* Returns element's info
		*/
		const Element Get(const char* inElementKey);

		/**
		* Change element in HashTable
		*/
		bool Update(const char* inOldKey, const char* inNewValue, int inNewValueLength);

		/**
		* Print all elements aand return their count
		*/
		int PrintAll();

		/**
		* Print element's info to the console
		*/
		void Print(const char* inElementKey);

		protected:
		
		/**
		* Set last error message. Should be empty if there wasn't an error
		*/
		void SetLastErrorMessage(string inErrorMessage);

		/**
		* This function converts inFileName to the wchar_t and concat module path with result
		* Sets FileName absolute path.
		*/
		void SetFileName(string inFileName);

		bool InitHashTable();

		/**
		* Open file for reading/editing
		* Open virtual view mapping of file
		*/
		bool OpenHashTableFromFile();

		/**
		* Close snapshots thread, clear handlers and used memory
		*/
		bool Close();

		/**
		* Is memory available
		*/
		bool CheckMemoryForAccess();

		/**
		* Implement snapshot
		*/
		bool Snap();

		private:

		int     m_CurrentSize;
		int     m_Capacity;
		int     m_SnapShotIntervalInSec;
		int     m_MaxKeyLength;
		int     m_MaxValueLength;
		time_t  m_LastSnapShotTime;

		void*	m_ElementsStartAddress;
		string  m_LastErrorMessage;
		      

		wstring m_MutexName;
		wstring m_FileName;
		wstring m_FileMapName;
		wstring m_TimerName;

		DWORD	m_CreatorPid;

		HANDLE  m_FileHandler;
		HANDLE  m_FileMappingHandler;
		HANDLE	m_TimerHandler;
		HANDLE	m_TimerThreadHandler;

		/**
		* Returns element in memory, which is pointed by pointer
		* It takes memory region and return element strucutre, based on this memory region
		*/
		Element* ConvertPointerToElement(byte* inPointer);

		/**
		* Get pointer on free memory region in HT
		*/
		byte* GetFreeMemoryForElement();

		/**
		* Get pointer on free memory region in HT
		*/
		byte* FindElement(const char* inKey);

		/**
		* Returns start of memory space of element
		*/
		byte* GetMemorySpaceByIndex(int inIndex);

		friend DWORD WINAPI PeriodicSnapShot(LPVOID inHashTable);
	};

	/**
	* This function will be called ones per SnapShotInterval
	*/
	DWORD WINAPI PeriodicSnapShot(LPVOID inHashTable);
};
