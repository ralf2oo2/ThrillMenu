#include "gamehooks.h"
#include "../game/lua/internallua.h"
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

void __fastcall gamehooks::LuaCall(void *L, int nargs, int nresults) {
	gamehooks::LuaCallOg(L, nargs, nresults);

	DumpAllGlobalNames(L);

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
			std::cout << "Found Global: " << keyName << std::endl;
		}

		internallua::lua_settop(L, -2);
	}
}