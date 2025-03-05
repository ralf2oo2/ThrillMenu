#include <Windows.h>
#include <thread>
#include <cstdint>
#include <iostream>
#include "hooks/hooks.h"

void Setup(const HINSTANCE instance) {
    try
    {
        AllocConsole();
        FILE* fDummy;
        freopen_s(&fDummy, "CONIN$", "r", stdin);
        freopen_s(&fDummy, "CONOUT$", "w", stderr);
        freopen_s(&fDummy, "CONOUT$", "w", stdout);
        gui::Setup();
        hooks::Setup();
        std::cout << "Setup initialized!" << std::endl;
    }
    catch (const std::exception& error)
    {
        MessageBeep(MB_ICONERROR);
        MessageBox(
            0,
            error.what(),
            "Thrill menu error",
            MB_OK | MB_ICONEXCLAMATION
        );

        goto UNLOAD;
    }
    while (!GetAsyncKeyState(VK_END))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
UNLOAD:
    hooks::Destroy();
    gui::Destroy();

    FreeLibraryAndExitThread(instance, 0);
}

BOOL WINAPI DllMain(
    HINSTANCE instance,  // handle to DLL module
    DWORD reason,     // reason for calling function
    LPVOID lpvReserved)  // reserved
{
    if (reason == DLL_PROCESS_ATTACH) {
        //MessageBox(0, "Content", "Title", MB_OK);

        
        // Print debug information to the new console
        DisableThreadLibraryCalls(instance);

        const auto thread = CreateThread(
            nullptr,
            0,
            reinterpret_cast<LPTHREAD_START_ROUTINE>(Setup),
            instance,
            0,
            nullptr
        );
        if (thread) {
            CloseHandle(thread);
        }
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}
