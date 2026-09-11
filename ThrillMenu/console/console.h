//
// Created by ralf2oo2 on 9/11/26.
//

#ifndef THRILLMENU_CONSOLE_H
#define THRILLMENU_CONSOLE_H

#include <vector>
#include <string>
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

struct LuaConsole {
    char input_buf[512] = "";
    std::vector<std::string> items;
    std::vector<std::string> history;
    int history_pos = -1;
    bool scroll_to_bottom = false;
    bool focus_input = false;
};

extern LuaConsole console;

void SetupLuaConsole(lua_State *L);
void ExecuteCommand(lua_State *L, const char* command);
void RenderLuaConsole(lua_State *L);

#endif //THRILLMENU_CONSOLE_H
