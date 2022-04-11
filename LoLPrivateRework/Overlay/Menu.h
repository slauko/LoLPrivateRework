#pragma once
#include "../Includes.h"
class Menu {
public:
	static DWORD combokey;
	static DWORD harasskey;
	static DWORD laneclearkey;
	static DWORD lasthitkey;
	static DWORD smitekey;

	static bool UseQ;
	static bool UseW;
	static bool UseE;

	static bool ChangeComboKey;
	static bool ChangeHarrassKey;
	static bool ChangeLaneclearKey;
	static bool ChangeLasthitKey;
	static bool ChangeSmiteKey;

	static int SetKeyname(const char* buffer, int keycode);
	static int GetKeyPressed(int CurrentKeyCode);

	static void UpdateMenu();
};