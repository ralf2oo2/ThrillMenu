#include "gamehooks.h"
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include <iostream>

void* __fastcall gamehooks::CameraController(void* pThis, void* edx) {
	void* pointer = gamehooks::CameraControllerOg(pThis);

	std::cout << "Address of void pointer: " << std::hex << pointer << std::endl;

	return pointer;
}

int __fastcall gamehooks::CameraRelated(void* pThis, void* edx, float a0, int a3) {
	int num = gamehooks::CameraRelatedOg(pThis, a0, a3);
	//std::cout << "CameraRelated: " << std::hex << a3 << std::endl;

	return num;
}
void* __fastcall gamehooks::Camera(void* pThis, void* edx, int a2) {
	void* pointer = gamehooks::CameraOg(pThis, a2);

	std::cout << "Camera: " << std::hex << pointer << std::endl;

	return pointer;
}
void* __fastcall gamehooks::GameDocument(void* pThis, void* edx, float a2, float a3) {
	void* pointer = gamehooks::GameDocumentOg(pThis, a2, a3);

	std::cout << "Address of gamedocument pointer: " << std::hex << pointer << std::endl;
	std::cout << "Address of luamanager pointer: " << std::hex << reinterpret_cast<uintptr_t>(pointer) + 2570 * 4 << std::endl;

	return pointer;
}
void* __fastcall gamehooks::CareerLevelManager(void* pThis, void* edx, int a2, int a3) {
	void* pointer = gamehooks::CareerLevelManagerOg(pThis, a2, a3);

	std::cout << "Address of careerlevelmanager pointer: " << std::hex << pointer << std::endl;

	return pointer;
}

void* __fastcall gamehooks::CameraSwitcher(void* pThis, void* edx, int a2) {
	void* pointer = gamehooks::CameraSwitcherOg(pThis, a2);

	std::cout << "Address of cameraswitcher pointer: " << std::hex << pointer << std::endl;

	return pointer;
}

int __fastcall gamehooks::LuaGetField(lua_State* L, int index, const char* k) {
	int value = gamehooks::luaL_getfield(L, index, k);

	std::cout << "Address of realest lua pointer: " << std::hex << reinterpret_cast<uintptr_t>(L) << std::endl;

	return value;
}

void* __fastcall gamehooks::LuaCall(void* pThis, void* edx, char a2) {
	void* pointer = gamehooks::LuaCallOg(pThis, a2);

	std::cout << "Possible lua context near: " << std::hex << pThis << std::endl;

	uintptr_t luamanagerptr = *(uintptr_t*)0xA0C374;
	uintptr_t secondPointer = *(uintptr_t*)(luamanagerptr + 4);
	std::cout << "Possible lua: " << std::hex << secondPointer << std::endl;
	//lua_State* L = (lua_State*)0xDD0818;

	//const char* script = "print('Hello, Lua!')";
	//char* copy = _strdup(script);

	//int status = lua_status(L);
	//if (status == 0 || status == LUA_YIELD || status == LUA_ERRRUN) {
	//	printf("Valid lua_State detected\n");
	//	//gamehooks::LoadStringOg(L, copy);
	//	
	//	/*lua_getglobal(L, "Money");
	//	lua_pushnumber(L, 12345678);
	//	lua_setglobal(L, "player_health");*/
	//}
	//else {
	//	printf("Warning: Possibly invalid lua_State\n");
	//}

	//const char* script = "print('Hello, Lua!')";
	//char* copy = _strdup(script);

	//////// Load and run the Lua script
	//if (luaL_loadstring(L , copy) != 0) {
	//	// If there's an error, print the error message and return false
	//	const char* errorMsg = lua_tostring(L, -1);
	//	std::cout << "Lua error: " << errorMsg << std::endl;
	//}

	return pointer;
}

int __cdecl gamehooks::LoadStringLua(void* pThis, char* Str) {
	int result = gamehooks::LoadStringOg(pThis, Str);
	std::cout << "Address of lua real pointer: " << std::hex << pThis << std::endl;
	printf("%s\n", Str);

	return result;
}

int __fastcall gamehooks::PCall(void* pThis, void* edx) {
	int result = gamehooks::PCallOg(pThis);
	std::cout << "Address of lua real pointer: " << std::hex << pThis << std::endl;
	return result;
}