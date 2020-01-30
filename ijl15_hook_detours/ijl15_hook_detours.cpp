// ijl15_hook_detours.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

HINSTANCE ijl15_base = LoadLibrary(L"ori_ijl15.dll");
auto ijlGetLibVersion_addr = GetProcAddress(ijl15_base, "ijlGetLibVerion_addr");
auto ijlInit_addr = GetProcAddress(ijl15_base, "ijlInit");
auto ijlFree_addr = GetProcAddress(ijl15_base, "ijlFree");
auto ijlRead_addr = GetProcAddress(ijl15_base, "ijlRead");
auto ijlWrite_addr = GetProcAddress(ijl15_base, "ijlWrite");
auto ijlErrorStr_addr = GetProcAddress(ijl15_base, "ijlErrorStr");

extern "C" __declspec(dllexport) void ijlGetLibVersion() { _asm { jmp dword ptr[ijlGetLibVersion_addr] } }
extern "C" __declspec(dllexport) void ijlInit() { _asm { jmp dword ptr[ijlInit_addr] } }
extern "C" __declspec(dllexport) void ijlFree() { _asm { jmp dword ptr[ijlFree_addr] } }
extern "C" __declspec(dllexport) void ijlRead() { _asm { jmp dword ptr[ijlRead_addr] } }
extern "C" __declspec(dllexport) void ijlWrite() { _asm { jmp dword ptr[ijlWrite_addr] } }
extern "C" __declspec(dllexport) void ijlErrorStr() { _asm { jmp dword ptr[ijlErrorStr_addr] } }