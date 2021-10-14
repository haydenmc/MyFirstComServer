#pragma once
#include "interfaces.h"

HRESULT CarFactory(void** pIFace);

class CoCar : public IEngine, public ICreateCar, public IStats
{
public:
    CoCar();
    virtual ~CoCar();
    // IUnknown
    STDMETHODIMP QueryInterface(REFIID riid, void** pIFace);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
    // IEngine
    STDMETHODIMP SpeedUp();
    STDMETHODIMP GetMaxSpeed(int* maxSpeed);
    STDMETHODIMP GetCurSpeed(int* curSpeed);
    // IStats
    STDMETHODIMP DisplayStats();
    STDMETHODIMP GetPetName(BSTR* petName);
    // ICreateCar
    STDMETHODIMP SetPetName(BSTR petName);
    STDMETHODIMP SetMaxSpeed(int maxSp);

private:
    static const int MAX_LENGTH { 255 };
    static const int MAX_SPEED{ 100 };
    unsigned long m_refCount{ 0 };
    BSTR m_petName { SysAllocString(L"Default Pet Name") };
    int m_maxSpeed{ 0 };
    int m_currSpeed{ 0 };
};