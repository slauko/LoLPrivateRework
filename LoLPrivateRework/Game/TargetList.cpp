#pragma once
#include "GameIncludes.h"

std::list<GameObject*> TargetList::ChampionList;
std::list<GameObject*> TargetList::MinionList;
std::list<GameObject*> TargetList::RecallList;
std::list<GameObject*> TargetList::MissileList;
std::list<GameObject*> TargetList::OriballObjects;
std::list<GameObject*> TargetList::FioraObjects;
std::list<GameObject*> TargetList::XayahFeathers;
std::list<GameObject*> TargetList::LuxEObject;
std::list<GameObject*> TargetList::LuluObjects;

void TargetList::GetTargetLists() {
	DWORD colorward = 0x00FF00FF;
	DWORD colorenemy = 0x00FF0000;
	DWORD colormouse = 0x00FF8000;
	for (int i = 0; i < MaxObjects; i++)
	{
		if (!Engine::pObjectManager->pObjectArray[i])
		{
			continue;
		}
		if (!strcmp(Engine::pObjectManager->pObjectArray[i]->GetName().c_str(), "RobotBuddy"))
		{
			if (Engine::pObjectManager->pObjectArray[i]->GetTeam() == Engine::pLocalPlayer->GetTeam())
			{
				LuluObjects.push_front(Engine::pObjectManager->pObjectArray[i]);
			}
		}
		if (strstr(Engine::pObjectManager->pObjectArray[i]->GetName().c_str(), "Lux_") && strstr(Engine::pObjectManager->pObjectArray[i]->GetName().c_str(), "_E_tar_aoe"))
		{
			LuxEObject.push_front(Engine::pObjectManager->pObjectArray[i]);
		}
		if (strstr(Engine::pObjectManager->pObjectArray[i]->GetName().c_str(), "Lux_") && strstr(Engine::pObjectManager->pObjectArray[i]->GetName().c_str(), "_E_mis"))
		{
			LuxEObject.push_front(Engine::pObjectManager->pObjectArray[i]);
		}
		if (!strcmp(Engine::pObjectManager->pObjectArray[i]->GetName().c_str(), "Feather"))
		{
			if (Engine::pObjectManager->pObjectArray[i]->GetTeam() == Engine::pLocalPlayer->GetTeam())
			{
				XayahFeathers.push_front(Engine::pObjectManager->pObjectArray[i]);
			}
		}
		if (strstr(Engine::pObjectManager->pObjectArray[i]->GetName().c_str(), "Xayah_") && strstr(Engine::pObjectManager->pObjectArray[i]->GetName().c_str(), "_Dagger_Mark"))
		{
			XayahFeathers.push_front(Engine::pObjectManager->pObjectArray[i]);
		}
		if (!strcmp(Engine::pObjectManager->pObjectArray[i]->GetName().c_str(), "TheDoomBall"))
		{
			if (Engine::pObjectManager->pObjectArray[i]->GetTeam() == Engine::pLocalPlayer->GetTeam())
			{
				OriballObjects.push_front(Engine::pObjectManager->pObjectArray[i]);
				//std::cout << "1" << std::endl;
			}
		}
		if (strstr(Engine::pObjectManager->pObjectArray[i]->GetName().c_str(), "Q_yomu_ring_green"))
		{
			OriballObjects.push_front(Engine::pObjectManager->pObjectArray[i]);
			//std::cout << "2" << std::endl;
		}
		if (strstr(Engine::pObjectManager->pObjectArray[i]->GetName().c_str(), "Q_Ghost_Bind"))
		{
			OriballObjects.push_front(Engine::pObjectManager->pObjectArray[i]);
			//std::cout << "2" << std::endl;
		}
		if (strstr(Engine::pObjectManager->pObjectArray[i]->GetName().c_str(), "Fiora") && (strstr(Engine::pObjectManager->pObjectArray[i]->GetName().c_str(), "Passive") || strstr(Engine::pObjectManager->pObjectArray[i]->GetName().c_str(), "_R_")))
		{
			FioraObjects.push_front(Engine::pObjectManager->pObjectArray[i]);
		}
		if (Engine::IsMissile(Engine::pObjectManager->pObjectArray[i]))
		{
			MissileList.push_front(Engine::pObjectManager->pObjectArray[i]); //get all missiles
		}
		if (!Engine::IsHero(Engine::pObjectManager->pObjectArray[i]) && !Engine::IsMinion(Engine::pObjectManager->pObjectArray[i]))
		{
			continue;
		}
		if (Engine::isDeadWard(Engine::pObjectManager->pObjectArray[i]))
		{
			continue;
		}
		if (Engine::isPlant(Engine::pObjectManager->pObjectArray[i]))
		{
			continue;
		}
		if (Engine::isWard(Engine::pObjectManager->pObjectArray[i]))
		{
			if (Engine::pObjectManager->pObjectArray[i]->GetTeam() != Engine::pLocalPlayer->GetTeam())
			{
				Engine::DrawAroundObject(Engine::pObjectManager->pObjectArray[i], 65.f, &colorward); //draw enemy wards
			}
		}
		if (!(Engine::pObjectManager->pObjectArray[i]->GetHealth() > 0.f))
		{
			continue;
		}
		if (Engine::IsHero(Engine::pObjectManager->pObjectArray[i])) 
		{
				RecallList.push_front(Engine::pObjectManager->pObjectArray[i]); //get all heros regardless if targetable or not, for later analysis in recalltracker
		}
		if (Engine::IsTargetable(Engine::pObjectManager->pObjectArray[i]))
		{
			if (Engine::IsHero(Engine::pObjectManager->pObjectArray[i]))
			{
				if (Engine::pObjectManager->pObjectArray[i]->GetTeam() != Engine::pLocalPlayer->GetTeam())
				{
					if (GetAsyncKeyState(VK_LBUTTON))
					{
						if (Engine::GetDistance3D(Engine::pMouse->MousePos, Engine::pObjectManager->pObjectArray[i]) < 100)
						{
							Engine::MouseObject = Engine::pObjectManager->pObjectArray[i]; //get champ near mouse
						}
					}
					if (GetAsyncKeyState(VK_LBUTTON)) {
						if (Engine::MouseObject)
						{
							if (Engine::GetDistance3D(Engine::pMouse->MousePos, Engine::MouseObject) > 100)
							{
								Engine::MouseObject = NULL; //reset mouse target
							}
						}
					}
				}
				if (Engine::MouseObject && Engine::IsTargetable(Engine::MouseObject))
				{
					Engine::DrawAroundObject(Engine::MouseObject, Engine::MouseObject->GetBoundingRadius(), &colormouse); //draw mouse object
				}
				if (Engine::pObjectManager->pObjectArray[i]->GetTeam() != Engine::pLocalPlayer->GetTeam())
				{
					Engine::DrawAroundObject(Engine::pObjectManager->pObjectArray[i], Engine::pObjectManager->pObjectArray[i]->GetAttackRange() + Engine::pObjectManager->pObjectArray[i]->GetBoundingRadius(), &colorenemy); //draw enemy champs
				}
				ChampionList.push_front(Engine::pObjectManager->pObjectArray[i]); //get all champs
			}
			if (Engine::IsMinion(Engine::pObjectManager->pObjectArray[i]))
			{
				MinionList.push_front(Engine::pObjectManager->pObjectArray[i]); //get all minions
			}
		}
	}
}