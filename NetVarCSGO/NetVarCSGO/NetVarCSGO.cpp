// NetVarCSGO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"

int main()
{
	//Get ProcId of the target process
	DWORD procId = GetProcId(L"csgo.exe");

	//Getmodulebaseaddress
	uintptr_t moduleBase = GetModuleBaseAddress(procId, L"client.dll");

	//Get Handle to Process
	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	//Resolve base address of the pointer chain
	uintptr_t dynamicPtrBaseAddr = moduleBase + 0x0D3EC6C;

	std::cout << "DynamicPtrBaseAddr = " << "0x" << std::hex << dynamicPtrBaseAddr << std::endl;

	//Resolve pointer

	uintptr_t healthAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, {0x100});

	std::cout << "healthAddr = " << "0x" << std::hex << healthAddr << std::endl;

	//Read Health value
	int healthValue = 0;

	ReadProcessMemory(hProcess, (BYTE*)healthAddr, &healthValue, sizeof(healthValue), nullptr);
	std::cout << "Curent health = " << std::dec << healthValue << std::endl;

	getchar();

	return 0;
}