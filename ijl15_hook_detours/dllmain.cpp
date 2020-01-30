// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "detours.h"
#pragma comment(lib,"detours.lib")

PVOID oldGetCommandLineA = NULL;

BOOL APIENTRY InstallHook();
BOOL APIENTRY UninstallHook();
int WINAPI DebuggingHook();

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		LoadLibraryA("aossdk.dll");
		InstallHook();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		UninstallHook();
		break;
	}
	return TRUE;
}

BOOL APIENTRY InstallHook() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	oldGetCommandLineA = DetourFindFunction("Kernel32.dll", "GetCommandLineA");
	DetourAttach(&oldGetCommandLineA, DebuggingHook);
	LONG ret = DetourTransactionCommit();
	return ret == NO_ERROR;
}

BOOL APIENTRY UninstallHook() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&oldGetCommandLineA, DebuggingHook);
	LONG ret = DetourTransactionCommit();
	return ret == NO_ERROR;
}

int WINAPI DebuggingHook() {
	MessageBoxA(0, "Debugging Time", "DEBUG", 0);
	return 0;
}