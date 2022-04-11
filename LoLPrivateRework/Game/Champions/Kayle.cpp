#pragma once
#include "Kayle.h"
#include "ChampionIncludes.h"

float Kayle::QRange = 0.f;
float Kayle::WRange = 0.f;
float Kayle::ERange = 0.f;
float Kayle::RRange = 0.f;

float Kayle::QSpeed = HUGE_VALF;
float Kayle::WSpeed = HUGE_VALF;
float Kayle::ESpeed = HUGE_VALF;
float Kayle::RSpeed = HUGE_VALF;

float Kayle::QDelay = 0.f;
float Kayle::WDelay = 0.f;
float Kayle::EDelay = 0.f;
float Kayle::RDelay = 0.f;

bool Kayle::Initialized = false;
bool Kayle::Initialize() {

	QRange = 850.f;
	WRange = 900.f;
	ERange = 550.f;
	RRange = 900.f;

	QSpeed = 2000.f;
	WSpeed = HUGE_VALF;
	ESpeed = HUGE_VALF;
	RSpeed = HUGE_VALF;

	QDelay = 0.25f;
	WDelay = 0.25f;
	EDelay = 0.f;
	RDelay = 0.75f;

	return true;
}

int Kayle::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	bool KayleE = Engine::pLocalPlayer->GetBuffManager()->HasBuff("KayleE");
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target && !KayleE)
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				if (Engine::GetDistance3D(PlayerPos, PredPos) < GetSpellRange(Spell))
				{
					return Engine::CastAimedSpell(PredPos, Spell);
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
			if (Target)
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
	return 0;
}

int Kayle::Harrass() {
	return 0;
}

int Kayle::Laneclear() {
	return 0;
}

int Kayle::Lasthit() {
	return 0;
}

int Kayle::Rotation() {
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
