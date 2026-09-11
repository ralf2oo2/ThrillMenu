//
// Created by ralf2oo2 on 9/11/26.
//
#include "console.h"
#include "../ext/imgui/imgui.h"
LuaConsole console;

static int lua_console_print(lua_State *L) {
    int nargs = lua_gettop(L);
    std::string output;
    for (int i = 1; i <= nargs; i++) {
        size_t len;
        const char* str = lua_tolstring(L, i, &len);
        if (str) output += str;
        if (i < nargs) output += "\t";
        lua_pop(L, 1);
    }
    console.items.push_back("[Output] " + output);
    return 0;
}

void SetupLuaConsole(lua_State *L) {
    lua_register(L, "print", lua_console_print);
}

void ExecuteCommand(lua_State *L, const char* command) {
    console.items.push_back("> " + std::string(command));

    int error = luaL_dostring(L, command);
    if (error) {
        const char* err_msg = lua_tostring(L, -1);
        console.items.push_back("[Error] " + std::string(err_msg ? err_msg : "Unknown error"));
        lua_pop(L, 1);
    }
    console.scroll_to_bottom = true;
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

