#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Menu.h"
#include "Settings.h"
#include "../Obfuscation.h"


DWORD Menu::combokey;
DWORD Menu::harasskey;
DWORD Menu::laneclearkey;
DWORD Menu::lasthitkey;
DWORD Menu::smitekey;

bool Menu::UseQ;
bool Menu::UseW;
bool Menu::UseE;

bool Menu::ChangeComboKey = false;
bool Menu::ChangeHarrassKey = false;
bool Menu::ChangeLaneclearKey = false;
bool Menu::ChangeLasthitKey = false;
bool Menu::ChangeSmiteKey = false;

int Menu::SetKeyname(const char* buffer, int keycode) {
	if (keycode == 4)
	{
		strcpy((LPSTR)buffer, "MB_Middle");
		return 1;
	}
	if (keycode == 5)
	{
		strcpy((LPSTR)buffer, "MB_X1");
		return 1;
	}
	if (keycode == 6)
	{
		strcpy((LPSTR)buffer, "MB_X2");
		return 1;
	}
	UINT scancode = MapVirtualKeyW(keycode, MAPVK_VK_TO_VSC);
	GetKeyNameText(scancode << 16, (LPSTR)buffer, 50);
	return 1;
}

int Menu::GetKeyPressed(int CurrentKeyCode) {
	for (int i = 4; i < 255; i++)
	{
		if (GetKeyState(i) & 0x8000)
		{
			return i;
		}
	}
	return CurrentKeyCode;
}

void GenerateKey(int vk, BOOL bExtended) {

	KEYBDINPUT  kb = { 0 };
	INPUT       Input = { 0 };

	/* Generate a "key down" */
	if (bExtended) { kb.dwFlags = KEYEVENTF_EXTENDEDKEY; }
	kb.wVk = vk;
	Input.type = INPUT_KEYBOARD;
	Input.ki = kb;
	SendInput(1, &Input, sizeof(Input));

	/* Generate a "key up" */
	ZeroMemory(&kb, sizeof(KEYBDINPUT));
	ZeroMemory(&Input, sizeof(INPUT));
	kb.dwFlags = KEYEVENTF_KEYUP;
	if (bExtended) { kb.dwFlags |= KEYEVENTF_EXTENDEDKEY; }
	kb.wVk = vk;
	Input.type = INPUT_KEYBOARD;
	Input.ki = kb;
	SendInput(1, &Input, sizeof(Input));

	return;
}

void Menu::UpdateMenu() {

}

