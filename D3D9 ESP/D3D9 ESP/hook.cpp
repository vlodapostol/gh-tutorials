#include "includes.h"

void Patch(BYTE* dst, BYTE* src, unsigned int size) {
	DWORD oldProc;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProc);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldProc, &oldProc);
}

bool Hook(char* src, char* dst, int len) {
	if (len < 5) return false;
	DWORD oldProc;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &oldProc);
	memset(src, 0x90, len);
	uintptr_t relAddy = (uintptr_t)(dst - src - 5);
	*src = (char)0xE9;
	*(uintptr_t*)(src + 1) = (uintptr_t)relAddy;
	VirtualProtect(src, len, oldProc, &oldProc);
}

char* TrampHook(char* src, char* dst, unsigned int len) {
	if (len < 5) return 0;
	char* gateway = (char*)VirtualAlloc(0, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy(gateway, src, len);
	uintptr_t jumpAddy = (uintptr_t)(src - gateway - 5);
	*(gateway + len) = (char)0xE9;
	*(uintptr_t*)(gateway + len + 1) = jumpAddy;
	if (Hook(src, dst, len)) {
		return gateway;
	}
	else return nullptr;
}