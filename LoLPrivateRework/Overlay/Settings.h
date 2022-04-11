#pragma once
#include "../Includes.h"
class Settings {
	public:
	static std::string GetChampionName(int input);
	static void createSettingsFile();
	static void LoadSettings();
	static void SaveSettings();
};
