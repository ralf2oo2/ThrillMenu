//
// Created by ralf2oo2 on 9/11/26.
//
#include "console.h"
#include "../ext/imgui/imgui.h"
#include "../game/lua/internallua.h"
#include <iostream>
LuaConsole console;

static int __fastcall lua_console_print(lua_State *L) {
    std::cout << "[Debug] lua_console_print was invoked!" << std::endl;

    int nargs = internallua::lua_gettop(L);
    std::cout << "[Debug] Argument count (nargs): " << nargs << std::endl;
    std::string output;
    for (int i = 1; i <= nargs; i++) {
        size_t len = 0;
        const char* str = internallua::lua_tolstring(L, i, &len);
        if (str) {
            output.append(str, len);
        } else {
            output += "nil";
        }
        if (i < nargs) output += "\t";
    }
    console.items.push_back("[Output] " + output);
    console.scroll_to_bottom = true;
    return 0;
}

void SetupLuaConsole(lua_State *L) {
    if (!L) {
        return;
    }

    internallua::lua_pushcclosure(L, reinterpret_cast<internallua::lua_CFunction>(lua_console_print), 0);
    internallua::luaL_setfield(L, LUA_GLOBALSINDEX, "print");
}

void ExecuteCommand(lua_State *L, const char* command) {
    std::cout << "[Debug] Executing command: " << command << std::endl;
    console.items.push_back("> " + std::string(command));

    std::cout << "[Debug] Calling luaL_loadstring at pointer..." << std::endl;
    if (internallua::luaL_loadstring(L, command) == 0) {
        std::cout << "[Debug] Loadstring survived" << std::endl;
        if (internallua::lua_pcall(L, 0, 0, 0) != 0) {
            const char* err_msg = internallua::lua_tolstring(L, -1, nullptr);
            std::cout << "[Error] pcall failed: " << (err_msg ? err_msg : "unknown") << std::endl;
            console.items.push_back("[Error] " + std::string(err_msg ? err_msg : "Unknown execution error"));

            internallua::lua_settop(L, -2);
        } else {
            std::cout << "[Debug] survived pcall" << std::endl;
        }
    } else {
        std::cout << "[Debug] Error branch" << std::endl;
        const char* err_msg = internallua::lua_tolstring(L, -1, nullptr);
        std::cout << "[Error] Loadstring failed: " << (err_msg ? err_msg : "unknown") << std::endl;
        console.items.push_back("[Error] " + std::string(err_msg ? err_msg : "Syntax error"));
        internallua::lua_settop(L, -2);
    }
}

void RenderLuaConsole(lua_State *L) {
    if (!L) {
        ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.2f, 1.0f), "Lua context not found");
        return;
    }

    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();

    if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar)) {
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));

        for (const auto& item : console.items) {
            bool is_error = item.rfind("[Error]", 0) == 0;
            if (is_error)
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));

            ImGui::TextUnformatted(item.c_str());

            if (is_error)
                ImGui::PopStyleColor();
        }
        if (console.scroll_to_bottom)
            ImGui::SetScrollHereY(1.0f);
        console.scroll_to_bottom = false;

        ImGui::PopStyleVar();
    }
    ImGui::EndChild();

    ImGui::Separator();

    bool reclaim_focus = false;
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue;

    if (ImGui::InputText("Input", console.input_buf, IM_ARRAYSIZE(console.input_buf), input_text_flags)) {
        std::string s(console.input_buf);
        if (!s.empty()) {
            ExecuteCommand(L, s.c_str());
            console.history.push_back(s);
            console.history_pos = static_cast<int>(console.history.size());
        }
        strcpy_s(console.input_buf, "");
        reclaim_focus = true;
    }

    ImGui::SetItemDefaultFocus();
    if (reclaim_focus || console.focus_input) {
        ImGui::SetKeyboardFocusHere(-1);
        console.focus_input = false;
    }
}

