#include <windows.h>
#include "iid.h"
#include "CoCarClassFactory.h"

unsigned long g_lockCount = 0; // Number of client locks
unsigned long g_objCount = 0;  // Number of living objects

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
    HRESULT hr;
    CoCarClassFactory *pCFact{ nullptr };
    if (rclsid != CLSID_CoCar)
    {
        return CLASS_E_CLASSNOTAVAILABLE;
    }
    pCFact = new CoCarClassFactory();
    hr = pCFact->QueryInterface(riid, ppv);
    if (FAILED(hr))
    {
        delete pCFact;
    }
    return hr;
}

STDAPI DllCanUnloadNow()
{
    if ((g_lockCount == 0) && (g_objCount == 0))
    {
        return S_OK;
    }
    return S_FALSE;
}