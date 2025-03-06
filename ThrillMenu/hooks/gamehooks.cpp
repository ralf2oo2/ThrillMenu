#include "gamehooks.h"
#include <iostream>

void* __fastcall gamehooks::CameraController(void* pThis, void* edx) {
	void* pointer = gamehooks::CameraControllerOg(pThis);

	std::cout << "Address of void pointer: " << std::hex << pointer << std::endl;

	return pointer;
}

int __fastcall gamehooks::CameraRelated(void* pThis, void* edx, float a0, int a3) {
	int num = gamehooks::CameraRelatedOg(pThis, a0, a3);
	std::cout << "Address of void pointer: " << std::hex << a3 << std::endl;

	return num;
}
void* __fastcall gamehooks::Camera(void* pThis, void* edx, int a2) {
	void* pointer = gamehooks::CameraOg(pThis, a2);

	std::cout << "Camera: " << std::hex << pointer << std::endl;

	return pointer;
}