#pragma once
#include "../Includes.h"
class TargetSelector {
public:
	static GameObject* AntiGapCloseTarget(Vector3 from, float Range);
	static GameObject* ComboTarget(Vector3 from, float Range, int Prio);
	static GameObject* FriendlyTarget(Vector3 from, float Range, int Prio);
	static GameObject* HarrassTarget(Vector3 from, float Range);
	static GameObject* LaneclearTarget(Vector3 from, float Range);
	static GameObject* LasthitTarget(Vector3 from, float Range);
	static GameObject* SmiteTarget(float Range);

	static std::list<GameObject*> GetEnemiesInRange(Vector3 from, float Range);
	static std::list<GameObject*> GetAlliesInRange(Vector3 from, float Range);
	static GameObject* GetShieldTarget(float ShieldRange, float healthpercent, bool useforminionattacks = true);

	static GameObject* GetTarget(TargetMode Mode, Vector3 from, float Range, int Prio);
};