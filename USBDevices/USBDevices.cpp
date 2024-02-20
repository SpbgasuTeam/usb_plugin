#include <Windows.h>
#include <SetupAPI.h>
#include <iostream>

#pragma comment(lib, "SetupAPI.lib")

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    HDEVINFO deviceInfoSet = SetupDiGetClassDevsA(NULL, "USB", NULL, DIGCF_PRESENT | DIGCF_ALLCLASSES);
    if (deviceInfoSet == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error: SetupDiGetClassDevsA failed" << std::endl;
        return 1;
    }

    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    for (DWORD i = 0; SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData); i++)
    {
        char deviceName[256];
        if (SetupDiGetDeviceRegistryPropertyA(deviceInfoSet, &deviceInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)deviceName, sizeof(deviceName), NULL))
        {
            std::cout << "Found USB Device: " << deviceName << std::endl;
        }
    }

    SetupDiDestroyDeviceInfoList(deviceInfoSet);
    return 0;
}
