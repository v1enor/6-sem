#pragma once
#include <objbase.h>
#include <assert.h>

HRESULT RegisterServer(HMODULE, const CLSID&, const WCHAR*, const WCHAR*, const WCHAR*);

HRESULT UnregisterServer(const CLSID&, const WCHAR*, const WCHAR*);
