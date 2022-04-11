#pragma once
#include "Karthus.h"
#include "ChampionIncludes.h"

int Karthus::Rotation() {
	float QRange = 875.f;
	float ERange = Engine::pLocalPlayer->GetAttackRange();
	float QSpeed = HUGE_VALF;
	float ESpeed = HUGE_VALF;
	float QDelay = 0.6f;
	float EDelay = 0.f;
	if (!Engine::OrbBot())
	{
	}
	return 0;
}
