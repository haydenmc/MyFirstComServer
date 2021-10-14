#include "interfaces.h"
#include "iid.h"
#include <iostream>

int main()
{
    CoInitialize(nullptr);
    HRESULT hr;
    IClassFactory* pCF{ nullptr };
    ICreateCar* pICreateCar{ nullptr };
    IStats* pStats{ nullptr };
    IEngine* pEngine{ nullptr };

    hr = CoGetClassObject(CLSID_CoCar, CLSCTX_INPROC_SERVER, nullptr,
        IID_IClassFactory, reinterpret_cast<void**>(&pCF));
    hr = pCF->CreateInstance(nullptr, IID_ICreateCar, reinterpret_cast<void**>(&pICreateCar));
    pCF->Release();
    if (SUCCEEDED(hr))
    {
        pICreateCar->SetMaxSpeed(30);
        BSTR petName = SysAllocString(L"Shazzam!");
        pICreateCar->SetPetName(petName);
        SysFreeString(petName);

        hr = pICreateCar->QueryInterface(IID_IStats, reinterpret_cast<void**>(&pStats));
        pICreateCar->Release();
    }
    if (SUCCEEDED(hr))
    {
        pStats->DisplayStats();
        hr = pStats->QueryInterface(IID_IEngine, reinterpret_cast<void**>(&pEngine));
    }
    if (SUCCEEDED(hr))
    {
        int curSp = 0;
        int maxSp = 0;
        pEngine->GetMaxSpeed(&maxSp);
        do
        {
            pEngine->SpeedUp();
            pEngine->GetCurSpeed(&curSp);
        }
        while (curSp <= maxSp);
        char buff[80];
        BSTR bstr;
        pStats->GetPetName(&bstr);
        WideCharToMultiByte(CP_ACP, 0, bstr, -1, buff, 80, nullptr, nullptr);
        std::cout << buff << " has blown up! Lead Foot!" << std::endl;
        SysFreeString(bstr);
        if (pEngine)
        {
            pEngine->Release();
        }
        if (pStats)
        {
            pStats->Release();
        }
    }
    CoUninitialize();
    return 0;
}