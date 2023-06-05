#include "pch.h"
#include "HT.h"
#include "HTFactory.h"

HTFactory::HTFactory()
	:m_refCount{ 0 }
{}

HTFactory::~HTFactory()
{}

STDMETHODIMP HTFactory::QueryInterface(const IID& riid, void** ppvObject)
{
	if (riid == IID_IClassFactory || riid == IID_IUnknown)
	{
		*ppvObject = static_cast<IClassFactory*>(this);
		AddRef();
		return S_OK;
	}
	return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) HTFactory::AddRef()
{
	return InterlockedIncrement(&m_refCount);
}

STDMETHODIMP_(ULONG) HTFactory::Release()
{
	return InterlockedDecrement(&m_refCount);
}

STDMETHODIMP HTFactory::CreateInstance(IUnknown* pUnkOuter, const IID& riid, void **ppvObject)
{
	HT* pOs;
	HRESULT hr{};

	if (pUnkOuter != NULL)
		return CLASS_E_NOAGGREGATION;

	*ppvObject = 0;

	pOs = new HT;
	if (pOs == 0)
		return E_OUTOFMEMORY;

	hr = pOs->QueryInterface(riid, ppvObject);

	if (FAILED(hr))
		delete pOs;

	return hr;
}

STDMETHODIMP HTFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&g_lLocks);
	else
		InterlockedDecrement(&g_lLocks);
	return S_OK;
}

