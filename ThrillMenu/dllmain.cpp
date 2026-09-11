#include <windows.h>
#include <thread>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <memory>
#include "hooks/hooks.h"

class TeeBuf : public std::streambuf {
public:
    TeeBuf(std::streambuf* sb1, std::streambuf* sb2) : sb1_(sb1), sb2_(sb2) {}

protected:
    int overflow(int c) override {
        if (c == EOF) return EOF;
        if (sb1_->sputc(c) == EOF || sb2_->sputc(c) == EOF) return EOF;
        sb1_->pubsync();
        sb2_->pubsync();
        return c;
    }

    int sync() override {
        int r1 = sb1_->pubsync();
        int r2 = sb2_->pubsync();
        return (r1 == 0 && r2 == 0) ? 0 : -1;
    }

private:
    std::streambuf* sb1_;
    std::streambuf* sb2_;
};

std::ofstream g_LogFile;
std::unique_ptr<TeeBuf> g_TeeBuf;
std::streambuf* g_OriginalStdoutBuf = nullptr;

void Setup(const HINSTANCE instance) {
    try
    {
        AllocConsole();
        FILE* fDummy;
        freopen_s(&fDummy, "CONIN$", "r", stdin);
        freopen_s(&fDummy, "CONOUT$", "w", stderr);
        freopen_s(&fDummy, "CONOUT$", "w", stdout);

        g_LogFile.open("console_debug.log", std::ios::out | std::ios::trunc);
        if (g_LogFile.is_open()) {
            g_OriginalStdoutBuf = std::cout.rdbuf();
            g_TeeBuf = std::make_unique<TeeBuf>(g_OriginalStdoutBuf, g_LogFile.rdbuf());
            std::cout.rdbuf(g_TeeBuf.get());
        }

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
    if (g_OriginalStdoutBuf) {
        std::cout.rdbuf(g_OriginalStdoutBuf);
    }
    if (g_LogFile.is_open()) {
        g_LogFile.close();
    }

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
