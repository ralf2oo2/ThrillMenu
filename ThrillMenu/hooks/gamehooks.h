#pragma once
namespace gamehooks
{
	typedef void* (__thiscall* CameraControllerOriginal)(void* pThis);
	inline CameraControllerOriginal CameraControllerOg = nullptr;
	void* __fastcall CameraController(void* pThis, void* edx);

	typedef int (__thiscall* CameraRelatedOriginal)(void* pThis, float a0, int a3);
	inline CameraRelatedOriginal CameraRelatedOg = nullptr;
	int __fastcall CameraRelated(void* pThis, void* edx, float a0, int a3);

	typedef void* (__thiscall* CameraOriginal)(void* pThis, int a2);
	inline CameraOriginal CameraOg = nullptr;
	void* __fastcall Camera(void* pThis, void* edx, int a2);

	typedef void* (__thiscall* GameDocumentOriginal)(void* pThi, float a2, float a3);
	inline GameDocumentOriginal GameDocumentOg = nullptr;
	void* __fastcall GameDocument(void* pThis, void* edx, float a2, float a3);

	typedef void* (__thiscall* CareerLevelManagerOriginal)(void* pThi, int a2, int a3);
	inline CareerLevelManagerOriginal CareerLevelManagerOg = nullptr;
	void* __fastcall CareerLevelManager(void* pThis, void* edx, int a2, int a3);

	typedef void* (__thiscall* CameraSwitcherOriginal)(void* pThi, int a2);
	inline CameraSwitcherOriginal CameraSwitcherOg = nullptr;
	void* __fastcall CameraSwitcher(void* pThis, void* edx, int a2);

	typedef void* (__thiscall* LuaCallOriginal)(void* pThi, char a2);
	inline LuaCallOriginal LuaCallOg = nullptr;
	void* __fastcall LuaCall(void* pThis, void* edx, char a2);

	typedef int (__cdecl *LoadStringOriginal)(void* pThi, char* Str);
	inline LoadStringOriginal LoadStringOg = nullptr;
	int __cdecl LoadStringLua(void* pThis, char* Str);

	typedef int(__thiscall* PCallOriginal)(void* pThi);
	inline PCallOriginal PCallOg = nullptr;
	int __fastcall PCall(void* pThis, void* edx);
}