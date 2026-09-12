//
// Created by ralf2oo2 on 9/11/26.
//

#ifndef THRILLMENU_GLOBALS_H
#define THRILLMENU_GLOBALS_H
#include "engine.h"

extern "C" {
    #include <lua.h>
}

namespace Globals {
    constexpr uintptr_t g_Engine = 0xdd0818;

    inline Engine* GetEngine() {
        return *reinterpret_cast<Engine**>(g_Engine);
    }
}

#endif //THRILLMENU_GLOBALS_H
