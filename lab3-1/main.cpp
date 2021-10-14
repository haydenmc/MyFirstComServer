#include "CoCar.h"
#include "iid.h"
#include <iostream>

const int MAX_NAME_LENGTH = 255;

int main()
{
    // Get IUnknown from a new CoCar
    IUnknown* pUnk;
    HRESULT hr;
    hr = CarFactory(reinterpret_cast<void**>(&pUnk));

    // Create a CoCar
    ICreateCar* pICreateCar;
    pUnk->QueryInterface(IID_ICreateCar, reinterpret_cast<void**>(&pICreateCar));
    pICreateCar->SetMaxSpeed(30);
    BSTR name = SysAllocString(OLESTR("Bertha"));
    pICreateCar->SetPetName(name);
    SysFreeString(name);

    // Rev it!
    int curSp = 0;
    int maxSp = 0;
    IEngine* pIEngine;
    pUnk->QueryInterface(IID_IEngine, reinterpret_cast<void**>(&pIEngine));
    pIEngine->GetMaxSpeed(&maxSp);
    do
    {
        pIEngine->SpeedUp();
        pIEngine->GetCurSpeed(&curSp);
        std::cout << "Speed is: " << curSp << std::endl;
    }
    while (curSp <= maxSp);

    IStats* pIStats;
    pUnk->QueryInterface(IID_IStats, reinterpret_cast<void**>(&pIStats));
    char buff[MAX_NAME_LENGTH];
    BSTR bstr;
    pIStats->GetPetName(&bstr);
    wcstombs(buff, bstr, MAX_NAME_LENGTH);
    std::cout << buff << " has blown up! Lead Foot!" << std::endl;
    SysFreeString(bstr);

    if (pUnk)
    {
        pUnk->Release();
    }
    if (pIEngine)
    {
        pIEngine->Release();
    }
    if (pIStats)
    {
        pIStats->Release();
    }
    if (pICreateCar)
    {
        pICreateCar->Release();
    }
}