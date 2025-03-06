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
}