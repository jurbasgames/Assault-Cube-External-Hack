// Assault Cube Hack.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"


int main()
{   
    int ammoOffset = 0x17E0A8;

    DWORD procId = GetProcessId(L"ac_client.exe");
    uintptr_t moduleBase = GetmoduleAddress(procId, L"ac_client.exe");

    HANDLE hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

    uintptr_t dynamicPtrBaseAddr = moduleBase + ammoOffset;

    std::cout << "moduleBase = " << "0x" << std::hex << moduleBase << std::endl;
    std::cout << "DynamicPtrBaseAddr = " << "0x" << std::hex << dynamicPtrBaseAddr << std::endl;

    std::vector<unsigned int> ammoOffsets = { 0x140 };
    uintptr_t ammoAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, ammoOffsets);

    std::cout << "ammoAddr = " << "0x" << std::hex << ammoAddr << std::endl;

    int ammoValue = 0;
    ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
    std::cout << "Current ammo = " << std::dec << ammoValue << std::endl;

    int newAmmo = 99999;
    WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);

    ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
    std::cout << "New ammo = " << std::dec << ammoValue << std::endl;

    getchar();
    return 0;

}