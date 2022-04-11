#pragma once
#include "Settings.h"
#include "Menu.h"
#include "../Obfuscation.h"
#include "../Game/Engine.h"

std::string Settings::GetChampionName(int input) {
	switch (input) {
	case 1:
		return "Annie";
	case 2:
		return "Brand";
	case 3:
		return "Caitlyn";
	case 4:
		return "Darius";
	case 5:
		return "Darius";
	case 6:
		return "Evelynn";
	case 7:
		return "Ezreal";
	case 8:
		return "Fiora";
	case 9:
		return "Gangplank";
	case 10:
		return "Graves";
	case 11:
		return "Janna";
	case 12:
		return "Jax";
	case 13:
		return "Jhin";
	case 14:
		return "Kalista";
	case 15:
		return "Karthus";
	case 16:
		return "Kayle";
	case 17:
		return "KogMaw";
	case 18:
		return "Lucian";
	case 19:
		return "Lulu";
	case 20:
		return "Lux";
	case 21:
		return "Olaf";
	case 22:
		return "Orianna";
	case 23:
		return "Rengar";
	case 24:
		return "Riven";
	case 25:
		return "Ryze";
	case 26:
		return "Talon";
	case 27:
		return "Thresh";
	case 28:
		return "Twitch";
	case 29:
		return "Vayne";
	case 30:
		return "Viktor";
	case 31:
		return "Vladimir";
	case 32:
		return "Xayah";
	case 33:
		return "Xerath";
	case 34:
		return "XinZhao";
	case 35:
		return "Yasuo";
	case 36:
		return "Zilean";
	default:
		return "NULL";
	}
}
void Settings::createSettingsFile() {
	WritePrivateProfileString("KeyBinds", "Use VK_Keys", "https://msdn.microsoft.com/de-de/library/windows/desktop/dd375731%28v=vs.85%29.aspx", "./settings.ini");
	WritePrivateProfileString("KeyBinds", "combokey", std::to_string(VK_SPACE).c_str(), "./settings.ini");
	WritePrivateProfileString("KeyBinds", "harasskey", std::to_string(VK_C).c_str(), "./settings.ini");
	WritePrivateProfileString("KeyBinds", "laneclearkey", std::to_string(VK_V).c_str(), "./settings.ini");
	WritePrivateProfileString("KeyBinds", "lasthitkey", std::to_string(VK_X).c_str(), "./settings.ini");
	WritePrivateProfileString("KeyBinds", "smitekey", std::to_string(SmiteKey).c_str(), "./settings.ini");
	for (int i = 1; i < 255; i++) {
		if (GetChampionName(i) != "NULL") {
			WritePrivateProfileString(GetChampionName(i).c_str(), "useQ", "1", "./settings.ini");
			WritePrivateProfileString(GetChampionName(i).c_str(), "useW", "1", "./settings.ini");
			WritePrivateProfileString(GetChampionName(i).c_str(), "useE", "1", "./settings.ini");
		}
	}
	LoadSettings();
}
void Settings::LoadSettings() {
	Menu::combokey = GetPrivateProfileInt("KeyBinds", "combokey", NULL, "./settings.ini");
	Menu::harasskey = GetPrivateProfileInt("KeyBinds", "harasskey", NULL, "./settings.ini");
	Menu::laneclearkey = GetPrivateProfileInt("KeyBinds", "laneclearkey", NULL, "./settings.ini");
	Menu::lasthitkey = GetPrivateProfileInt("KeyBinds", "lasthitkey", NULL, "./settings.ini");
	Menu::smitekey = GetPrivateProfileInt("KeyBinds", "smitekey", NULL, "./settings.ini");
	//std::cout << Engine::pLocalPlayer->GetChampionName().c_str() << std::endl;
	std::string champname = Engine::pLocalPlayer->GetChampionName().c_str();
	if (strstr(champname.c_str(),"Orianna"))
	{
		Menu::UseQ = GetPrivateProfileInt("Orianna", "useQ", NULL, "./settings.ini");
		Menu::UseW = GetPrivateProfileInt("Orianna", "useW", NULL, "./settings.ini");
		Menu::UseE = GetPrivateProfileInt("Orianna", "useE", NULL, "./settings.ini");
	}
	else if (strstr(champname.c_str(),"Lux")) {
		Menu::UseQ = GetPrivateProfileInt("Lux", "useQ", NULL, "./settings.ini");
		Menu::UseW = GetPrivateProfileInt("Lux", "useW", NULL, "./settings.ini");
		Menu::UseE = GetPrivateProfileInt("Lux", "useE", NULL, "./settings.ini");
	}
	else {
		Menu::UseQ = GetPrivateProfileInt(champname.c_str(), "useQ", NULL, "./settings.ini");
		Menu::UseW = GetPrivateProfileInt(champname.c_str(), "useW", NULL, "./settings.ini");
		Menu::UseE = GetPrivateProfileInt(champname.c_str(), "useE", NULL, "./settings.ini");
	}
}
void Settings::SaveSettings() {
	Menu::combokey = WritePrivateProfileString("KeyBinds", "combokey", std::to_string(Menu::combokey).c_str(), "./settings.ini");
	Menu::harasskey = WritePrivateProfileString("KeyBinds", "harasskey", std::to_string(Menu::harasskey).c_str(), "./settings.ini");
	Menu::laneclearkey = WritePrivateProfileString("KeyBinds", "laneclearkey", std::to_string(Menu::laneclearkey).c_str(), "./settings.ini");
	Menu::lasthitkey = WritePrivateProfileString("KeyBinds", "lasthitkey", std::to_string(Menu::lasthitkey).c_str(), "./settings.ini");
	Menu::smitekey = WritePrivateProfileString("KeyBinds", "smitekey", std::to_string(Menu::smitekey).c_str(), "./settings.ini");
	std::string champname = Engine::pLocalPlayer->GetChampionName().c_str();
	if (strstr(champname.c_str(), "Orianna"))
	{
		WritePrivateProfileString("Orianna", "useQ", std::to_string(Menu::UseQ).c_str(), "./settings.ini");
		WritePrivateProfileString("Orianna", "useW", std::to_string(Menu::UseW).c_str(), "./settings.ini");
		WritePrivateProfileString("Orianna", "useE", std::to_string(Menu::UseE).c_str(), "./settings.ini");
	}
	else if (strstr(champname.c_str(), "Lux")) {
		WritePrivateProfileString("Lux", "useQ", std::to_string(Menu::UseQ).c_str(), "./settings.ini");
		WritePrivateProfileString("Lux", "useW", std::to_string(Menu::UseW).c_str(), "./settings.ini");
		WritePrivateProfileString("Lux", "useE", std::to_string(Menu::UseE).c_str(), "./settings.ini");
	}
	else {
		WritePrivateProfileString(champname.c_str(), "useQ", std::to_string(Menu::UseQ).c_str(), "./settings.ini");
		WritePrivateProfileString(champname.c_str(), "useW", std::to_string(Menu::UseW).c_str(), "./settings.ini");
		WritePrivateProfileString(champname.c_str(), "useE", std::to_string(Menu::UseE).c_str(), "./settings.ini");
	}
	LoadSettings();
}

