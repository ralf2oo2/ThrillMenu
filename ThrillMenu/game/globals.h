//
// Created by ralf2oo2 on 9/11/26.
//

#ifndef THRILLMENU_GLOBALS_H
#define THRILLMENU_GLOBALS_H
#include "../console/console.h"

extern "C" {
    #include <lua.h>
}


namespace Globals {
    inline lua_State* g_LuaState = nullptr;
    inline bool g_ConsoleInitialized = false;

    inline void SetLuaState(lua_State* L) {
        if (g_LuaState != L) {
            g_LuaState = L;
            g_ConsoleInitialized = false; // Reset if the game allocates a new state
        }

        if (L && !g_ConsoleInitialized) {
            SetupLuaConsole(L);
            g_ConsoleInitialized = true;
        }
    }
}

#endif //THRILLMENU_GLOBALS_H
