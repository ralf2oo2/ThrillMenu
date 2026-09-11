//
// Created by ralf2oo2 on 9/11/26.
//

#ifndef THRILLMENU_GLOBALS_H
#define THRILLMENU_GLOBALS_H
extern "C" {
    #include <lua.h>
}


namespace Globals {
    inline lua_State* g_LuaState = nullptr;
}

#endif //THRILLMENU_GLOBALS_H
