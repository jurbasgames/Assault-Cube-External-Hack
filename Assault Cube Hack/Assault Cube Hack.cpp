// Assault Cube Hack.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"
#include "mem.h"

int main()
{   
    int ammoOffset = 0x17E0A8;
    std::vector<unsigned int> ammoOffsets = { 0x368, 0x14, 0x0 };
    std::vector<unsigned int> healthOffsets = { 0xEC };
    bool ammoActive = false;
    bool infHealth = false;

    DWORD procId = GetProcessId(L"ac_client.exe");
    if (procId == 0) {
        std::cout << "Process not found" << std::endl;
        getchar();
        return 0;
    }
    
    uintptr_t moduleBase = GetmoduleAddress(procId, L"ac_client.exe");

    HANDLE hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

    uintptr_t dynamicPtrBaseAddr = moduleBase + ammoOffset;
    uintptr_t ammoAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, ammoOffsets);
    uintptr_t heathAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, healthOffsets);

    std::cout << "[F1] - Infinite Ammo" << std::endl;
    std::cout << "[F2] - Infinite Health" << std::endl;
    std::cout << "[HOME] - Exit" << std::endl;

    DWORD dwExit = 0;
    while (GetExitCodeProcess(hProcess, &dwExit) && dwExit == STILL_ACTIVE)
    {
        // Exit
        if (GetAsyncKeyState(VK_HOME) & 1) {
            return 0;
        }

        // Infinite ammo
        if (GetAsyncKeyState(VK_F1) & 1) {
            ammoActive = !ammoActive;
            if (ammoActive) {
                std::cout << "Ammo Activated" << std::endl;
            } else {
                std::cout << "Ammo Deactivated" << std::endl;
            }
        }

        if (ammoActive) {
            int newAmmo = 999;
            WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);
            Sleep(50);
        }


        //Infinite Health
        if (GetAsyncKeyState(VK_F2) & 1) {
            infHealth = !infHealth;
            if (infHealth) {
                std::cout << "Health Activated" << std::endl;
            }
            else {
                std::cout << "Health Deactivated" << std::endl;
            }
        }

        if (infHealth) {
            int newHealth = 999;
            WriteProcessMemory(hProcess, (BYTE*)heathAddr, &newHealth, sizeof(newHealth), nullptr);
            Sleep(50);
        }

        
             
    }







}