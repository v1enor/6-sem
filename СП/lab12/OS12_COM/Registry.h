#pragma once
#include "Windows.h"
#include <assert.h>
#include <objbase.h>

HRESULT RegisterServer(HMODULE, const CLSID&, const WCHAR*, const WCHAR*, const WCHAR*);

HRESULT UnregisterServer(const CLSID&, const WCHAR*, const WCHAR*);
