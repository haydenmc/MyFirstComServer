#include "CoCar.h"
#include "iid.h"
#include <iostream>

extern unsigned long g_objCount;

HRESULT CarFactory(void** pIFace)
{
    HRESULT hr;
    IUnknown* pUnk = nullptr;
    CoCar* pCar = new CoCar();
    hr = pCar->QueryInterface(IID_IUnknown, reinterpret_cast<void**>(&pUnk));
    if (SUCCEEDED(hr))
    {
        *pIFace = pUnk;
        return S_OK;
    }
    delete pCar;
    return E_FAIL;
}

#pragma region Constructor/Destructor
CoCar::CoCar()
{
    ++g_objCount;
}

CoCar::~CoCar()
{
    if (m_petName)
    {
        SysFreeString(m_petName);
    }
    --g_objCount;
}
#pragma endregion Constructor/Destructor

#pragma region IUnknown
STDMETHODIMP_(ULONG) CoCar::AddRef()
{
    return ++m_refCount;
}

STDMETHODIMP_(ULONG) CoCar::Release()
{
    if (--m_refCount == 0)
    {
        delete this;
        return 0;
    }
    return m_refCount;
}

STDMETHODIMP CoCar::QueryInterface(REFIID riid, void** pIFace)
{
    if (riid == IID_IUnknown)
    {
        *pIFace = static_cast<IUnknown*>(static_cast<IEngine*>(this));
    }
    else if (riid == IID_IEngine)
    {
        *pIFace = static_cast<IEngine*>(this);
    }
    else if (riid == IID_IStats)
    {
        *pIFace = static_cast<IStats*>(this);
    }
    else if (riid == IID_ICreateCar)
    {
        *pIFace = static_cast<ICreateCar*>(this);
    }
    else
    {
        *pIFace = nullptr;
        return E_NOINTERFACE;
    }
    static_cast<IUnknown*>(*pIFace)->AddRef();
    return S_OK;
}
#pragma endregion IUnknown

#pragma region IEngine
STDMETHODIMP CoCar::SpeedUp()
{
    m_currSpeed += 10;
    return S_OK;
}

STDMETHODIMP CoCar::GetMaxSpeed(int* maxSpeed)
{
    *maxSpeed = m_maxSpeed;
    return S_OK;
}

STDMETHODIMP CoCar::GetCurSpeed(int* curSpeed)
{
    *curSpeed = m_currSpeed;
    return S_OK;
}
#pragma endregion IEngine

#pragma region IStats
STDMETHODIMP CoCar::DisplayStats()
{
    char buff[MAX_LENGTH];
    WideCharToMultiByte(CP_ACP, 0, m_petName, -1, buff, MAX_LENGTH, nullptr, nullptr);
    std::cout << buff << std::endl;
    return S_OK;
}

STDMETHODIMP CoCar::GetPetName(BSTR* petName)
{
    *petName = SysAllocString(m_petName);
    return S_OK;
}
#pragma endregion IStats

#pragma region ICreateCar
STDMETHODIMP CoCar::SetPetName(BSTR petName)
{
    SysReAllocString(&m_petName, petName);
    return S_OK;
}

STDMETHODIMP CoCar::SetMaxSpeed(int maxSp)
{
    if (maxSp < MAX_SPEED)
    {
        m_maxSpeed = maxSp;
    }
    return S_OK;
}
#pragma endregion ICreateCar