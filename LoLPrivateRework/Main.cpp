#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Includes.h"
#include "Game/CDTracker.h"
#include "Game/Engine.h"
#include "Game/Evade.h"
#include "Game/Prediction.h"
#include "Game/SpellDataBase.h"
#include "Game/TargetList.h"
#include "Game/TargetSelector.h"
#include "Game/RecallTracker.h"
#include "Game/Utility.h"
#include "Overlay/Menu.h"
#include "Overlay/Settings.h"

#include "Obfuscation.h"

//=====================================================================================
//=====================================================================================
//=====================================================================================
HRESULT WINAPI hkEndScene(LPDIRECT3DDEVICE9 Device_Interface)
{
	if (Engine::pLocalPlayer) {
		if (!Engine::pHUDBase->pHudInstance->isTabbedOut)
		{
			TargetList::GetTargetLists();
			DWORD colorself = 0x00A08080;
			Engine::DrawCircle(&Engine::pLocalPlayer->GetPosition(), Engine::pLocalPlayer->GetAttackRange() + Engine::pLocalPlayer->GetBoundingRadius(), &colorself, 0, 0, 0, 1.f);

			Evade::SpellHandler(Device_Interface);
			CDTracker::DrawCooldowns(Device_Interface);
			RecallTracker::DrawRecall(Device_Interface);

			if (!Engine::ChatClient->ChatOpen)
			{
				Menu::UpdateMenu();
				if (GetAsyncKeyState(Menu::smitekey))
				{
					Utility::SmiteBot();
				}
				if (!Utility::ChampSelect())
				{
					Engine::OrbBot(); //if no specific champ script is used, just orbwalk
				}
			}
			TargetList::ChampionList.clear();
			TargetList::MinionList.clear();
			TargetList::RecallList.clear();
			TargetList::MissileList.clear();
			TargetList::OriballObjects.clear();
			TargetList::FioraObjects.clear();
			TargetList::XayahFeathers.clear();
			TargetList::LuxEObject.clear();
			TargetList::LuluObjects.clear();
		}
	}
	if (GetAsyncKeyState(VK_F5) & 1)
	{
		Settings::LoadSettings();
	}
	HRESULT rtnadd = offsets.pEndScene(Device_Interface);
	offsets.D3DHook(); // ReHook
	return rtnadd;
}

//=====================================================================================
HINSTANCE hModuleOfDLL;
BOOL APIENTRY DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		AllocConsole();
		HWND hWnd = GetConsoleWindow();
		auto console = freopen(XorStr("CONOUT$"), XorStr("w"), stdout);
		SetConsoleTitle(XorStr("Menu"));
		DisableThreadLibraryCalls(hModule);

		hModuleOfDLL = hModule;
		offsets.hkEndSceneAddy = (DWORD)hkEndScene;
		offsets.Init();
	}
	return TRUE;
}
