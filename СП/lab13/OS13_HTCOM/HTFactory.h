#pragma once
#include <objbase.h>

class HTFactory : public IClassFactory
{
public:
	HTFactory();
	~HTFactory();

	STDMETHOD(QueryInterface(const IID& riid, void** ppvObject));
	STDMETHOD_(ULONG, AddRef());
	STDMETHOD_(ULONG, Release());

	STDMETHOD(CreateInstance(IUnknown* pUnkOuter, const IID& riid, void** ppvObject));
	STDMETHOD(LockServer(BOOL fLock));
private:
	LONG m_refCount;
};