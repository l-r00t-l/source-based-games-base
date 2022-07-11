// dllmain.cpp : Defines the entry point for the DLL application.
#define WIN32_LEAN_AND_MEAN
#include "pch.h"
#include "sdk/sdk.hpp"

/*

Initalization queue
c_logger
c_modules
c_interfaces
c_render
c_netvars
c_hooks
c_events

*/



auto instance(HMODULE hModule) -> int
{
    // Wait for latest module to load
#ifdef RELEASE_BUILD
    while (!GetModuleHandleA("mss32.dll") || !GetModuleHandleA("materialsystem.dll"))
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
#endif
    c_logger::get()->init("console");
    c_logger::get()->greeting();

    c_modules::get()->init();
    c_interfaces::get()->init();
    c_netvars::get()->init();
    c_hooks::get()->init();
    c_events::get()->init();

    while(!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

    c_events::get()->destroy();
    c_hooks::get()->restore();

    std::this_thread::sleep_for(std::chrono::seconds(3));
    c_logger::get()->destroy();

    FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    DisableThreadLibraryCalls(hModule);
    if (ul_reason_for_call != DLL_PROCESS_ATTACH)
        return FALSE;

    // Attached
    // TODO: play a sound when attached
    Beep(800, 200); // 523 hz for 200 ms
    if (const HANDLE thread = CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(instance), hModule, NULL, nullptr))
        CloseHandle(thread);

    return TRUE;
}