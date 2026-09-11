#include "gamehooks.h"
#include "../game/lua/internallua.h"
#include <iostream>

#include "../game/globals.h"

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

void __fastcall gamehooks::LuaCall(void *L, int nargs, int nresults) {
	gamehooks::LuaCallOg(L, nargs, nresults);

	Globals::SetLuaState(static_cast<lua_State *>(L));

	std::cout << "Possible lua context near: " << std::hex << L << std::endl;
}

void gamehooks::DumpAllGlobalNames(void* L) {
	char* statePtr = reinterpret_cast<char*>(L);

char** topPtr = reinterpret_cast<char**>(statePtr + 8);
char* currentTop = *topPtr;

*reinterpret_cast<int*>(currentTop + 12) = 0;

*topPtr = currentTop + 0x10;

	while (internallua::lua_next(L, -10002) != 0) {
		size_t len = 0;
		const char* keyName = internallua::lua_tolstring(L, -2, &len);

		if (keyName) {
			std::cout << "Found Global: " << keyName << " = ";

			// Read type tag directly from the stack slot at index -1
			int valType = *reinterpret_cast<int*>(currentTop - 16 + 8);

			switch (valType) {
				case 4: // LUA_TSTRING
				{
					size_t vLen = 0;
					const char* valStr = internallua::lua_tolstring(L, -1, &vLen);
					std::cout << "\"" << (valStr ? valStr : "") << "\" (string)" << std::endl;
					break;
				}
				case 3: // LUA_TNUMBER
				{
					// Read the 8-byte double value directly from the start of the TValue struct
					double valNum = *reinterpret_cast<double*>(currentTop - 16);
					std::cout << valNum << " (number)" << std::endl;
					break;
				}
				case 1: // LUA_TBOOLEAN
				{
					int valBool = *reinterpret_cast<int*>(currentTop - 16);
					std::cout << (valBool ? "true" : "false") << " (boolean)" << std::endl;
					break;
				}
				case 5: // LUA_TTABLE
					std::cout << "table" << std::endl;
					break;
				case 6: // LUA_TFUNCTION
					std::cout << "function" << std::endl;
					break;
				case 7: // LUA_TUSERDATA
					std::cout << "userdata" << std::endl;
					break;
				case 2: // LUA_TLIGHTUSERDATA
					std::cout << "lightuserdata" << std::endl;
					break;
				case 0: // LUA_TNIL
					std::cout << "nil" << std::endl;
					break;
				default:
					std::cout << "type(" << valType << ")" << std::endl;
					break;
			}
		}

		internallua::lua_settop(L, -2);
	}
}