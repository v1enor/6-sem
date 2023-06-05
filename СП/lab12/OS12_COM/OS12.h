#pragma once
#include "IAdder.h"
#include "IMultiplier.h"
#include <initguid.h>

// {45E5AAF4-8512-4145-8644-1CBBD299478B}
DEFINE_GUID(IID_IAdder,
	0x45e5aaf4, 0x8512, 0x4145, 0x86, 0x44, 0x1c, 0xbb, 0xd2, 0x99, 0x47, 0x8b);

// {828D8AA9-B5C0-407F-AD56-49454D67744C}
DEFINE_GUID(IID_IMultiplier,
	0x828d8aa9, 0xb5c0, 0x407f, 0xad, 0x56, 0x49, 0x45, 0x4d, 0x67, 0x74, 0x4c);

// {9AEA4448-E0B0-4D3B-95F7-9742AFFFAC99}
DEFINE_GUID(CLSID_OS12,
	0x9aea4448, 0xe0b0, 0x4d3b, 0x95, 0xf7, 0x97, 0x42, 0xaf, 0xff, 0xac, 0x99);

extern long g_lObjs;
extern long g_lLocks;

static LPCWSTR  FriendlyName = L"Smw.OS12.COM";
static LPCWSTR  VerIndProg = L"Smw.OS12";
static LPCWSTR  ProgID = L"Smw.OS12.1";

class OS12 : public IAdder, public IMultiplier
{
public:
	OS12();
	~OS12();

	STDMETHOD_(ULONG, AddRef());
	STDMETHOD_(ULONG,Release());
	STDMETHOD(QueryInterface(const IID& riid, void** ppvObject));

	STDMETHOD(Add(const double x, const double y, double& z));
	STDMETHOD(Sub(const double x, const double y, double& z));
	STDMETHOD(Mul(const double x, const double y, double& z));
	STDMETHOD(Div(const double x, const double y, double& z));

private:
	LONG m_refCount;
};
