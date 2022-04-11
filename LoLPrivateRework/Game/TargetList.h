#pragma once
#include "../Includes.h"
class TargetList {
public:
	static std::list<GameObject*> ChampionList;
	static std::list<GameObject*> MinionList;
	static std::list<GameObject*> RecallList;
	static std::list<GameObject*> MissileList; 
	
	static std::list<GameObject*> OriballObjects;
	static std::list<GameObject*> FioraObjects;
	static std::list<GameObject*> XayahFeathers;
	static std::list<GameObject*> LuxEObject;
	static std::list<GameObject*> LuluObjects;
	static void GetTargetLists();
};