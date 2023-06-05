#include "pch.h"
#include "Registry.h"
#include "HTFactory.h"
#include "HT.h"
#include "Seqlog.h"

HMODULE hmodule;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        hmodule = hModule;
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

STDAPI DllGetClassObject(const CLSID& clsid, const IID& iid, void** ppvObject)
{
    SEQ;
    HRESULT rc;
    HTFactory* pF{ nullptr };
    if (clsid != CLSID_HT)
        rc = CLASS_E_CLASSNOTAVAILABLE;
    else if ((pF = new HTFactory()) == NULL)
        rc = E_OUTOFMEMORY;
    else
    {
        rc = pF->QueryInterface(iid, ppvObject);
        pF->Release();
    }
    LOG("DllGetClassObject: rc = ", rc);
    return rc;
}

STDAPI DllCanUnloadNow(void)
{
    SEQ;
    HRESULT rc{ E_UNEXPECTED };
    if (g_lObjs == 0 && g_lLocks == 0)
        rc = S_OK;
    else
        rc = S_FALSE;
    LOG("DllCanUnloadNow: rc = ", rc);
    return rc;
}

STDAPI DllRegisterServer(void)
{
    SEQ;
    HRESULT rc = RegisterServer(hmodule, CLSID_HT, FriendlyName, VerIndProg, ProgID);
    LOG("DllRegisterServer: rc = ", rc);
    return rc;
}

STDAPI DllUnregisterServer(void)
{
    SEQ;
    HRESULT rc = UnregisterServer(CLSID_HT, VerIndProg, ProgID);
    LOG("DllRegisterServer: rc = ", rc);
    return rc;
}

STDAPI DllInstall(BOOL b, PCWSTR s)
{
    SEQ;
    LOG("DllInstall: rc = ", S_OK);
    return S_OK;
}