#pragma once
#include "Riven.h"
#include "ChampionIncludes.h"

float Riven::QRange = 0.f;
float Riven::WRange = 0.f;
float Riven::ERange = 0.f;
float Riven::RRange = 0.f;

float Riven::QSpeed = HUGE_VALF;
float Riven::WSpeed = HUGE_VALF;
float Riven::ESpeed = HUGE_VALF;
float Riven::RSpeed = HUGE_VALF;

float Riven::QDelay = 0.f;
float Riven::WDelay = 0.f;
float Riven::EDelay = 0.f;
float Riven::RDelay = 0.f;

bool Riven::Initialized = false;
bool Riven::Initialize() {
	QRange = 300.f;
	WRange = 125.f;
	ERange = 400.f;
	RRange = 900.f;

	QSpeed = HUGE_VALF;
	WSpeed = HUGE_VALF;
	ESpeed = HUGE_VALF;
	RSpeed = 1600.f;

	QDelay = 0.25f;
	WDelay = 0.25f;
	EDelay = 0.f;
	RDelay = 0.75f;

	return true;
}

int Riven::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target && Engine::AACancelPossible())
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
				if (HitChance > 0.5f)
				{
					return Engine::CastAimedSpell(PredPos, Spell);
				}
			}
		}
	}
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && Engine::BlockAA)
		{
			return Engine::CastAimedSpell(Engine::EvadePos, Spell);
		}
	}
	if (Menu::UseW)
	{
		SpellSlotID Spell = W;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target)
			{
				return Engine::CastTargetedSpell(Target, Spell);
			}
		}
	}
	return 0;
}

int Riven::Harrass() {
	return 0;
}

int Riven::Laneclear() {
	return 0;
}

int Riven::Lasthit() {
	return 0;
}

int Riven::Rotation() {
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
