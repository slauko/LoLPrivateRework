#pragma once
#include "Vladimir.h"
#include "ChampionIncludes.h"

float Vladimir::QRange = 0.f;
float Vladimir::WRange = 0.f;
float Vladimir::ERange = 0.f;
float Vladimir::RRange = 0.f;

float Vladimir::QSpeed = HUGE_VALF;
float Vladimir::WSpeed = HUGE_VALF;
float Vladimir::ESpeed = HUGE_VALF;
float Vladimir::RSpeed = HUGE_VALF;

float Vladimir::QDelay = 0.f;
float Vladimir::WDelay = 0.f;
float Vladimir::EDelay = 0.f;
float Vladimir::RDelay = 0.f;

bool Vladimir::Initialized = false;
bool Vladimir::Initialize() {

	QRange = 550.f;
	WRange = 550.f;
	ERange = 550.f;
	RRange = 700.f;

	QSpeed = HUGE_VALF;
	WSpeed = HUGE_VALF;
	ESpeed = HUGE_VALF;
	RSpeed = HUGE_VALF;

	QDelay = 0.25f;
	WDelay = 0.25f;
	EDelay = 0.f;
	RDelay = 0.75f;

	return true;
}

int Vladimir::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;

	float EStartTime = Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(2)->GetStartTime();
	float EChargeTime = 0;
	if (EStartTime)
	{
		EChargeTime = *Engine::GameTime - EStartTime;
	}


	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell))
		{
			GameObject* E_Target = TargetSelector::ComboTarget(Engine::pLocalPlayer->GetPosition(), ERange, 1);
			if (E_Target && Menu::UseE)
			{
				if (!EStartTime)
				{
					if (!Prediction::IsCollisioned(Minion, E_Target->GetPosition(), 60))
					{
						return Engine::CastAimedSpell(Engine::pMouse->MousePos, Spell);
					}
				}
				if (EChargeTime > 1.f)
				{
					if (!Prediction::IsCollisioned(Minion, E_Target->GetPosition(), 60))
					{
						return Engine::ReleaseSpell(Engine::pMouse->MousePos, Spell);
					}
				}
			}
		}
	}
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target && !EStartTime)
			{
				return Engine::CastTargetedSpell(Target, Spell);
			}
		}
	}
	return 0;
}

int Vladimir::Harrass() {
	return 0;
}

int Vladimir::Laneclear() {
	return 0;
}

int Vladimir::Lasthit() {
	return 0;
}

int Vladimir::Rotation() {
	if (!Initialized)
	{
		Initialized = Initialize();
	}

	if (Engine::getOrbMode() == Target_Combo)
	{
		if (!Engine::OrbBot())
		{
			return Combo();
		}
	}
	if (Engine::getOrbMode() == Target_Harrass)
	{
		if (!Engine::OrbBot())
		{
			return Harrass();
		}
	}
	if (Engine::getOrbMode() == Target_LaneClear)
	{
		if (!Engine::OrbBot())
		{
			return Laneclear();
		}
	}
	if (Engine::getOrbMode() == Target_LastHit)
	{
		if (!Engine::OrbBot())
		{
			return Lasthit();
		}
	}
	return 0;
}
