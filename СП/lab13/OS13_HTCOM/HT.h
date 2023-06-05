#pragma once
#include "IHT.h"
#include "HTHandle.h"
#include <initguid.h>

extern long g_lObjs;
extern long g_lLocks;

extern LPCWSTR  FriendlyName;
extern LPCWSTR  VerIndProg;
extern LPCWSTR  ProgID;

// {1479DCD4-C2B8-4CB4-B9FD-BC70701AFD38}
DEFINE_GUID(IID_IHT,
	0x1479dcd4, 0xc2b8, 0x4cb4, 0xb9, 0xfd, 0xbc, 0x70, 0x70, 0x1a, 0xfd, 0x38);

// {871A3D0A-5F35-4452-BEF3-5BD8C0FBDECB}
DEFINE_GUID(CLSID_HT,
	0x871a3d0a, 0x5f35, 0x4452, 0xbe, 0xf3, 0x5b, 0xd8, 0xc0, 0xfb, 0xde, 0xcb);


class HT : public IHT
{
public:
	HT();
	~HT();

	STDMETHOD(QueryInterface(const IID& riid, void** ppvObject));
	STDMETHOD_(ULONG, AddRef());
	STDMETHOD_(ULONG, Release());

	STDMETHOD_(HTHANDLE*, Create(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const std::wstring FileName));
	STDMETHOD(Open(const std::wstring FileName));
	STDMETHOD_(HTHANDLE*, OpenExist(const std::wstring FileName));
	STDMETHOD(CloseExist(const HTHANDLE* hthandle));
	STDMETHOD(Snap(HTHANDLE* hthandle));
	STDMETHOD(Insert(HTHANDLE* hthandle, Element* element));
	STDMETHOD(Update(HTHANDLE* hthandle, Element* oldelement, void* newpayload, int newpayloadlenth));
	STDMETHOD(Delete(HTHANDLE* hthandle, Element* element));
	STDMETHOD(Close(const HTHANDLE* htHandle));
	STDMETHOD_(Element*, Get(HTHANDLE* hthandle, Element* element));
	STDMETHOD_(char*, GetLastErrorProg(HTHANDLE* ht));
	STDMETHOD(print(const Element* element));
	STDMETHOD_(Element*, CreateNewKeyElement(const void* key, int keylength));
	STDMETHOD_(Element*, CreateNewFullElement(const void* key, int keylength, const void* payload, int payloadlength));

	static void SetErrorMessage(HTHANDLE* ht, const char* message, int messageLen);

private:
	int HashFunction(const Element* element, int size, int p);
	int Next_hash(int hash, int size, int p);
	wchar_t* GenerateMutexName(const wchar_t* pathToHT);
	wchar_t* GenerateViewName(const wchar_t* pathToHT);
	BOOL CheckParmLength(HTHANDLE* ht, Element* element);
	BOOL CheckParmLength(HTHANDLE* ht, int payloadLength);
	Element* GetElementFromHT(HTHANDLE* ht, int n);
	BOOL SetElementToHT(HTHANDLE* ht, Element* element, int n);
	BOOL IsDeleted(Element* ptr);
	void SetDeletedFlag(Element* ptr);
	BOOL EqualElementKeys(Element* el1, Element* el2);
	void UpdateElement(HTHANDLE* ht, Element* el, void* newpayload, int newpayloadlength);

	const int DELETED = -1;
	LONG m_refCount;
};