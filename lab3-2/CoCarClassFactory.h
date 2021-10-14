#pragma once
#include <windows.h>

class CoCarClassFactory : public IClassFactory
{
public:
    CoCarClassFactory() = default;
    virtual ~CoCarClassFactory() = default;

    // IUnknown
    STDMETHODIMP QueryInterface(REFIID riid, void** pIFace);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    // IClassFactory
    STDMETHODIMP LockServer(BOOL fLock);
    STDMETHODIMP CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, void** ppv);

private:
    unsigned long m_refCount{ 0 };
};