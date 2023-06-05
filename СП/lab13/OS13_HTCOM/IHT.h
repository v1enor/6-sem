#pragma once

#include <objbase.h>
#include <string>

struct HTHANDLE;
struct Element;

interface IHT : public IUnknown
{
	STDMETHOD_(HTHANDLE*, Create(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const std::wstring FileName)) PURE;
	STDMETHOD(Open(const std::wstring FileName)) PURE;
	STDMETHOD_(HTHANDLE*, OpenExist(const std::wstring FileName)) PURE;
	STDMETHOD(Snap(HTHANDLE* hthandle)) PURE;
	STDMETHOD(Insert(HTHANDLE* hthandle, Element* element)) PURE;
	STDMETHOD(Delete(HTHANDLE* hthandle, Element* element)) PURE;
	STDMETHOD_(Element*, Get(HTHANDLE* hthandle, Element* element)) PURE;
	STDMETHOD(Update(HTHANDLE* hthandle, Element* oldelement, void* newpayload, int newpayloadlenth)) PURE;
	STDMETHOD(Close(const HTHANDLE* htHandle)) PURE;
	STDMETHOD(CloseExist(const HTHANDLE* hthandle)) PURE;
	STDMETHOD_(char*, GetLastErrorProg(HTHANDLE* ht)) PURE;
	STDMETHOD(print(const Element* element)) PURE;
	STDMETHOD_(Element*, CreateNewKeyElement(const void* key, int keylength)) PURE;
	STDMETHOD_(Element*, CreateNewFullElement(const void* key, int keylength, const void* payload, int payloadlength)) PURE;
};
