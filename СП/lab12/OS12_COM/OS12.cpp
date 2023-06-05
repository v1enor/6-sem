#include "pch.h"
#include "OS12.h"

long g_lObjs = 0;
long g_lLocks = 0;

OS12::OS12()
	:m_refCount{0}
{
	InterlockedIncrement(&g_lObjs);
}

OS12::~OS12()
{
	InterlockedDecrement(&g_lObjs);
}


STDMETHODIMP_(ULONG) OS12::AddRef()
{
	return InterlockedIncrement(&m_refCount);
}

STDMETHODIMP_(ULONG) OS12::Release()
{
	ULONG refCount = InterlockedDecrement(&m_refCount);
	if (refCount == 0)
	{
		delete this;
	}
	return refCount;
}

STDMETHODIMP OS12::QueryInterface(const IID& riid, void** ppvObject)
{
	if(riid == IID_IAdder || riid == IID_IUnknown)
	{
		*ppvObject = static_cast<IAdder*>(this);
		AddRef();
		return S_OK;
	}
	if(riid == IID_IMultiplier)
	{
		*ppvObject = static_cast<IMultiplier*>(this);
		AddRef();
		return S_OK;
	}
	
	*ppvObject = NULL;
	return E_NOINTERFACE;
}

STDMETHODIMP OS12::Add(const double x, const double y, double& z)
{
	z = x + y;
	return S_OK;
}

STDMETHODIMP OS12::Sub(const double x, const double y, double& z)
{
	z = x - y;
	return S_OK;
}

STDMETHODIMP OS12::Mul(const double x, const double y, double& z)
{
	z = x * y;
	return S_OK;

}

STDMETHODIMP OS12::Div(const double x, const double y, double& z)
{
	if (x == 0.0)
		return E_INVALIDARG;
	z = x / y;
	return S_OK;
}
