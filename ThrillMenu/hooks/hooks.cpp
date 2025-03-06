#include "hooks.h"
#include "gamehooks.h"

#include <stdexcept>
#include <intrin.h>

#include "../ext/minhook/MinHook.h"

#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_impl_win32.h"
#include "../ext/imgui/imgui_impl_dx9.h"
#include <iostream>

void hooks::Setup()
{
	if (MH_Initialize())
	{
		throw std::runtime_error("Unable to initialize minhook");
	}

	//DX hooks for imgui
	if (MH_CreateHook(
		VirtualFunction(gui::device, 42),
		&EndScene,
		reinterpret_cast<void**>(&EndSceneOriginal)
	)) throw std::runtime_error("Unable to hook EndScene()");

	if (MH_CreateHook(
		VirtualFunction(gui::device, 16),
		&Reset,
		reinterpret_cast<void**>(&ResetOriginal)
	)) throw std::runtime_error("Unable to hook Reset()");

	// Game related hooks

	gamehooks::CameraControllerOg = (gamehooks::CameraControllerOriginal)0x575920;
	if (MH_CreateHook((LPVOID)gamehooks::CameraControllerOg, &gamehooks::CameraController, reinterpret_cast<LPVOID*>(&gamehooks::CameraControllerOg)) != MH_OK)
	{
		throw std::runtime_error("Unable to enable cameraController hook");
	}
	
	gamehooks::CameraRelatedOg = (gamehooks::CameraRelatedOriginal)0x5766E0;
	if (MH_CreateHook((LPVOID)gamehooks::CameraRelatedOg, &gamehooks::CameraRelated, reinterpret_cast<LPVOID*>(&gamehooks::CameraRelatedOg)) != MH_OK)
	{
		throw std::runtime_error("Unable to enable cameraRelated hook");
	}

	gamehooks::CameraOg = (gamehooks::CameraOriginal)0x53B440;
	if (MH_CreateHook((LPVOID)gamehooks::CameraOg, &gamehooks::Camera, reinterpret_cast<LPVOID*>(&gamehooks::CameraOg)) != MH_OK)
	{
		throw std::runtime_error("Unable to enable camera hook");
	}

	if (MH_EnableHook(MH_ALL_HOOKS))
	{
		throw std::runtime_error("Unable to enable hooks");
	}
	gui::DestroyDirectX();
}
void hooks::Destroy() noexcept
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

long __stdcall hooks::EndScene(IDirect3DDevice9* device) noexcept
{
	//stops endscene getting called twice
	if (hooks::isInEndScene)
	{
		return EndSceneOriginal(device, device);
	}

	isInEndScene = true;

	if (!gui::setup)
	{
		gui::SetupMenu(device);
	}
	if (gui::open)
	{
		gui::Render();
	}
	const auto result = EndSceneOriginal(device, device);
	hooks::isInEndScene = false;
	return result;
}

HRESULT __stdcall hooks::Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept
{
	params->BackBufferWidth = 0;
	params->BackBufferHeight = 0;
	params->Flags = 0;
	params->FullScreen_RefreshRateInHz = 0;
	params->PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	params->Windowed = true;

	D3DDEVICE_CREATION_PARAMETERS creationParameters;
	device->GetCreationParameters(&creationParameters);
	HWND hWnd = creationParameters.hFocusWindow;

	LONG style = GetWindowLong(hWnd, GWL_STYLE);
	style &= ~WS_POPUP;
	style |= WS_OVERLAPPEDWINDOW;
	SetWindowLong(hWnd, GWL_STYLE, style);
	SetWindowPos(hWnd, NULL, 100, 100, 1280, 720, SWP_NOMOVE | SWP_FRAMECHANGED);

	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);

	ImGui_ImplDX9_InvalidateDeviceObjects();
	const auto result = ResetOriginal(device, device, params);
	ImGui_ImplDX9_CreateDeviceObjects();
	return result;
}