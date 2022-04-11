#pragma once
#include "XinZhao.h"
#include "ChampionIncludes.h"

float XinZhao::QRange = 0.f;
float XinZhao::WRange = 0.f;
float XinZhao::ERange = 0.f;
float XinZhao::RRange = 0.f;

float XinZhao::QSpeed = HUGE_VALF;
float XinZhao::WSpeed = HUGE_VALF;
float XinZhao::ESpeed = HUGE_VALF;
float XinZhao::RSpeed = HUGE_VALF;

float XinZhao::QDelay = 0.f;
float XinZhao::WDelay = 0.f;
float XinZhao::EDelay = 0.f;
float XinZhao::RDelay = 0.f;

bool XinZhao::Initialized = false;
bool XinZhao::Initialize() {

	QRange = 300.f;
	WRange = 900.f;
	ERange = 475.f;
	RRange = 25000.f;

	QSpeed = 2000.f;
	WSpeed = 2000.f;
	ESpeed = HUGE_VALF;
	RSpeed = HUGE_VALF;

	QDelay = 0.25f;
	WDelay = 0.4f;
	EDelay = 0.f;
	RDelay = 0.75f;

	return true;
}

int XinZhao::Combo() {
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
				return Engine::CastAimedSpell(Engine::pMouse->MousePos, Spell);
			}
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
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 1);
				if (HitChance > 0.5f)
				{
					return Engine::CastAimedSpell(PredPos, Spell);
				}
			}
		}
	}
	return 0;
}

int XinZhao::Harrass() {
	return 0;
}

int XinZhao::Laneclear() {
	return 0;
}

int XinZhao::Lasthit() {
	return 0;
}

int XinZhao::Rotation() {
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
