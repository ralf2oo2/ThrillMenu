# CMakeList.txt : CMake project for ThrillMenu, include source and define
# project specific logic here.
#

# Add source to this project's executable.

add_library (ThrillMenu SHARED "dllmain.cpp"   "hooks/hooks.cpp" "hooks/hooks.h" "ext/imgui/imconfig.h" "ext/imgui/imgui.cpp" "ext/imgui/imgui.h" "ext/imgui/imgui_demo.cpp" "ext/imgui/imgui_draw.cpp" "ext/imgui/imgui_impl_dx9.cpp" "ext/imgui/imgui_impl_dx9.h" "ext/imgui/imgui_impl_win32.cpp" "ext/imgui/imgui_impl_win32.h" "ext/imgui/imgui_internal.h" "ext/imgui/imgui_tables.cpp" "ext/imgui/imgui_widgets.cpp" "ext/imgui/imstb_rectpack.h" "ext/imgui/imstb_textedit.h" "ext/imgui/imstb_truetype.h" "ext/minhook/buffer.c" "ext/minhook/buffer.h" "ext/minhook/hde/hde32.c" "ext/minhook/hde/hde32.h" "ext/minhook/hde/hde64.c" "ext/minhook/hde/hde64.h" "ext/minhook/hde/pstdint.h" "ext/minhook/hde/table32.h" "ext/minhook/hde/table64.h" "ext/minhook/hook.c" "ext/minhook/MinHook.h" "ext/minhook/trampoline.c" "ext/minhook/trampoline.h" "gui/gui.h" "gui/gui.cpp" "hooks/gamehooks.cpp" "hooks/gamehooks.h" "game/lua/internallua.h"
        console/console.h
        console/console.cpp
        game/globals.h
        game/engine.h
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ThrillMenu PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(ThrillMenu PRIVATE ${CMAKE_SOURCE_DIR}/ThrillMenu/ext/lua51/include)
target_link_libraries(
        ThrillMenu
        d3d9
        gdi32
        dwmapi
)

if(DEFINED ENV{THRILLVILLE_DIR})
  set(GAME_PATH "$ENV{THRILLVILLE_DIR}")
else()
  # Optional default fallback path
  set(GAME_PATH "${CMAKE_BINARY_DIR}")
endif()

set_target_properties(ThrillMenu PROPERTIES
    OUTPUT_NAME "ThrillMenu"  # This removes the default extension
    SUFFIX ".asi"             # Set the extension to '.asi'
    RUNTIME_OUTPUT_DIRECTORY "${GAME_PATH}"
    LIBRARY_OUTPUT_DIRECTORY "${GAME_PATH}"
)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")
# TODO: Add tests and install targets if needed.
