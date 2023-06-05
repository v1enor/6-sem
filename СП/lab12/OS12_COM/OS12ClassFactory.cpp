#include "pch.h"
#include "OS12ClassFactory.h"
#include "OS12.h"

OS12ClassFactory::OS12ClassFactory()
	:m_refCount{0}
{}

OS12ClassFactory::~OS12ClassFactory()
{}

STDMETHODIMP OS12ClassFactory::QueryInterface(const IID& riid, void** ppvObject)
{
	if(riid == IID_IClassFactory || riid == IID_IUnknown)
	{
		*ppvObject = static_cast<IClassFactory*>(this);
		AddRef();
		return S_OK;
	}
	return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) OS12ClassFactory::AddRef()
{
	return InterlockedIncrement(&m_refCount);
}

STDMETHODIMP_(ULONG) OS12ClassFactory::Release()
{
	return InterlockedDecrement(&m_refCount);
}

STDMETHODIMP OS12ClassFactory::CreateInstance(IUnknown* pUnkOuter, const IID& riid, void** ppvObject)
{
	OS12* pOs;
	HRESULT hr{};

	if (pUnkOuter != NULL)
		return CLASS_E_NOAGGREGATION;

	*ppvObject = 0;

	pOs = new OS12;
	if (pOs == 0)
		return E_OUTOFMEMORY;

	hr = pOs->QueryInterface(riid, ppvObject);

	if (FAILED(hr))
		delete pOs;

	return hr;
}

STDMETHODIMP OS12ClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&g_lLocks);
	else
		InterlockedDecrement(&g_lLocks);
	return S_OK;
}

