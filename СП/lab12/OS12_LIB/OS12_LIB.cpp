#include "pch.h"
#include "framework.h"

#include <iostream>
#include <objbase.h>

#include "OS12.h"
#include "OS12_LIB.h"


OS12HANDEL OS12_LIB::Init()
{
	try
	{
		p_adder = nullptr;
		p_multiplier = nullptr;

		IUnknown* pIUnknown = NULL;
		CoInitialize(NULL);                        // инициализация библиотеки OLE32
		HRESULT hr = CoCreateInstance(CLSID_OS12, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pIUnknown);
		if (!SUCCEEDED(hr))
			throw hr;
		return pIUnknown;
	}
	catch(HRESULT rc)
	{
		OutputErrorHandle(rc);
		return NULL;
	}
}

double OS12_LIB::Adder::Add(OS12HANDEL h, double x, double y)
{
	try
	{
		HRESULT hr{};
		if (!SUCCEEDED((hr = static_cast<IUnknown*>(h)->QueryInterface(IID_IAdder, (void**)&p_adder))))
			throw hr;

		double z{};
		if(!SUCCEEDED(hr = p_adder->Add(x, y, z)))
			throw hr;
		p_adder->Release();
		return z;
	}
	catch(HRESULT rc)
	{
		OutputErrorHandle(rc);
		return NULL;
	}
}

double OS12_LIB::Adder::Sub(OS12HANDEL h, double x, double y)
{
	try
	{
		HRESULT hr{};
		if (!SUCCEEDED((hr = static_cast<IUnknown*>(h)->QueryInterface(IID_IAdder, (void**)&p_adder))))
			throw hr;

		double z{};
		if (!SUCCEEDED(hr = p_adder->Sub(x, y, z)))
			throw hr;
		p_adder->Release();
		return z;
	}
	catch (HRESULT rc)
	{
		OutputErrorHandle(rc);
		return NULL;
	}
}

double OS12_LIB::Multiplier::Mul(OS12HANDEL h, double x, double y)
{
	try
	{
		HRESULT hr{};
		if (!SUCCEEDED((hr = static_cast<IUnknown*>(h)->QueryInterface(IID_IMultiplier, (void**)&p_multiplier))))
			throw hr;

		double z{};
		if (!SUCCEEDED(hr = p_multiplier->Mul(x, y, z)))
			throw hr;
		p_multiplier->Release();
		return z;
	}
	catch (HRESULT rc)
	{
		OutputErrorHandle(rc);
		return NULL;
	}
}

double OS12_LIB::Multiplier::Div(OS12HANDEL h, double x, double y)
{
	try
	{
		HRESULT hr{};
		if (!SUCCEEDED((hr = static_cast<IUnknown*>(h)->QueryInterface(IID_IMultiplier, (void**)&p_multiplier))))
			throw hr;

		double z{};
		if (!SUCCEEDED(hr = p_multiplier->Div(x, y, z)))
			throw hr;
		p_multiplier->Release();
		return z;
	}
	catch (HRESULT rc)
	{
		OutputErrorHandle(rc);
		return NULL;
	}
}

void OS12_LIB::Dispose(OS12HANDEL h)
{
	static_cast<IUnknown*>(h)->Release();
	CoFreeUnusedLibraries();
}

void OS12_LIB::OutputErrorHandle(int rc)
{
	LPWSTR errorText = nullptr;
	FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		nullptr, rc, 0, (LPWSTR)&errorText, 0, nullptr);
	std::wcout << L"Error: " << rc << L" - " << errorText << std::endl;
	LocalFree(errorText);
}

