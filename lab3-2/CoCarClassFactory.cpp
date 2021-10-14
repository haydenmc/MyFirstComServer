#include "CoCarClassFactory.h"
#include "CoCar.h"

extern unsigned long g_lockCount;

STDMETHODIMP_(ULONG) CoCarClassFactory::AddRef()
{
    return ++m_refCount;
}

STDMETHODIMP_(ULONG) CoCarClassFactory::Release()
{
    m_refCount -= 1;
    if (m_refCount == 0)
    {
        delete this;
        return 0;
    }
    return m_refCount;
}

STDMETHODIMP CoCarClassFactory::QueryInterface(REFIID riid, void** ppv)
{
    if (riid == IID_IUnknown)
    {
        *ppv = static_cast<IUnknown*>(this);
    }
    else if (riid == IID_IClassFactory)
    {
        *ppv = static_cast<IClassFactory*>(this);
    }
    else
    {
        *ppv = nullptr;
        return E_NOINTERFACE;
    }
    static_cast<IUnknown*>(*ppv)->AddRef();
    return S_OK;
}

STDMETHODIMP CoCarClassFactory::LockServer(BOOL fLock)
{
    if (fLock)
    {
        ++g_lockCount;
    }
    else
    {
        --g_lockCount;
    }
    return S_OK;
}

STDMETHODIMP CoCarClassFactory::CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, void** ppv)
{
    // We don't support aggregation in this class object
    if (pUnkOuter != nullptr)
    {
        return CLASS_E_NOAGGREGATION;
    }
    CoCar* pCarObj{ nullptr };
    HRESULT hr;
    // Create the car
    pCarObj = new CoCar();
    hr = pCarObj->QueryInterface(riid, ppv);
    if (FAILED(hr))
    {
        delete pCarObj;
    }
    return hr;
}