#pragma once
#include "Thresh.h"
#include "ChampionIncludes.h"

float Thresh::QRange = 0.f;
float Thresh::WRange = 0.f;
float Thresh::ERange = 0.f;
float Thresh::RRange = 0.f;

float Thresh::QSpeed = HUGE_VALF;
float Thresh::WSpeed = HUGE_VALF;
float Thresh::ESpeed = HUGE_VALF;
float Thresh::RSpeed = HUGE_VALF;

float Thresh::QDelay = 0.f;
float Thresh::WDelay = 0.f;
float Thresh::EDelay = 0.f;
float Thresh::RDelay = 0.f;

bool Thresh::Initialized = false;
bool Thresh::Initialize() {
	QRange = 1075.f;
	WRange = 615.f;
	ERange = 435.f;
	RRange = 615.f;

	QSpeed = 1900.f;
	WSpeed = 2000.f;
	ESpeed = HUGE_VALF;
	RSpeed = HUGE_VALF;

	QDelay = 0.5f;
	WDelay = 0.25f;
	EDelay = 0.25f;
	RDelay = 0.75f;

	return true;
}

int Thresh::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;


	GameObject* AntiGapClose_Target = TargetSelector::AntiGapCloseTarget(Engine::pLocalPlayer->GetPosition(), ERange);
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target)
			{
				Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
				if (HitChance > 0.5f)
				{
					Vector3 PlayerToPos = { PlayerPos.x - PredPos.x,PlayerPos.y - PredPos.y ,PlayerPos.z - PredPos.z };
					Vector3 ECastPos = { PlayerPos.x + PlayerToPos.x,PlayerPos.y + PlayerToPos.y ,PlayerPos.z + PlayerToPos.z };

					return Engine::CastAimedSpell(ECastPos, Spell);
				}
			}
		}
	}

	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			if (!strstr(Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(0)->GetSpellInfo()->GetSpellName().c_str(), "ThreshQLeap"))
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
	}
	return 0;
}

int Thresh::Harrass() {
	return 0;
}

int Thresh::Laneclear() {
	return 0;
}

int Thresh::Lasthit() {
	return 0;
}

int Thresh::Rotation() {
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
