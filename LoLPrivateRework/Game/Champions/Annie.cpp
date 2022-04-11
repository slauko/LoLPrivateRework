#pragma once
#include "Annie.h"
#include "ChampionIncludes.h"

float Annie::QRange = 0.f;
float Annie::WRange = 0.f;
float Annie::ERange = 0.f;
float Annie::RRange = 0.f;

float Annie::QSpeed = HUGE_VALF;
float Annie::WSpeed = HUGE_VALF;
float Annie::ESpeed = HUGE_VALF;
float Annie::RSpeed = HUGE_VALF;

float Annie::QDelay = 0.f;
float Annie::WDelay = 0.f;
float Annie::EDelay = 0.f;
float Annie::RDelay = 0.f;

bool Annie::Initialized = false;
bool Annie::Initialize() {

	QRange = 575.f;
	WRange = 625.f;
	ERange = 550.f;
	RRange = 600.f;

	QSpeed = HUGE_VALF;
	WSpeed = HUGE_VALF;
	ESpeed = HUGE_VALF;
	RSpeed = HUGE_VALF;

	QDelay = 0.f;
	WDelay = 0.f;
	EDelay = 0.f;
	RDelay = 0.f;

	return true;
}
float Annie::CalcQDamage(GameObject* Target) {
	float QDamagePerLevel[] = { 80.f , 115.f , 150.f , 185.f , 220.f };
	float AP = Engine::pLocalPlayer->GetBonusAP();
	float MR = Target->GetMR();
	float DamageMod = 100 / (100 + MR);
	int SpellLevel = Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(Q)->GetSpellLevel();
	float SpellDamage = (AP * 0.8f) + QDamagePerLevel[SpellLevel - 1];
	float QDamage = SpellDamage * DamageMod;

	return QDamage;
}

int Annie::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			if (TargetSelector::GetShieldTarget(65.f, 1.f, 0))
			{
				return Engine::CastAimedSpell(PlayerPos, Spell);
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
				return Engine::CastTargetedSpell(Target, Spell);
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
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
				if (HitChance > 0.1f)
				{
					return Engine::CastAimedSpell(PredPos, Spell);
				}
			}
		}
	}
	//if (Menu::UseR)
	//{
	//SpellSlotID Spell = R;
	//if (Engine::SpellReady(Spell) && !Engine::BlockAA)
	//{
	//	GameObject* Target = TargetSelector::ComboTarget(PlayerPos, GetSpellRange(Spell), 1);
	//	if (Target)
	//	{
	//		Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));

	//	}
	//}
	//}
	return 0;
}

int Annie::Harrass() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
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

int Annie::Laneclear() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_LaneClear;
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target)
			{
				if (Target->GetHealth() < CalcQDamage(Target))
				{
					return Engine::CastTargetedSpell(Target, Spell);
				}
			}
		}
	}
	return 0;
}

int Annie::Lasthit() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_LaneClear;
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target)
			{
				if (Target->GetHealth() < CalcQDamage(Target))
				{
					Engine::CastTargetedSpell(Target, Spell);
				}
			}
		}
	}
	return 0;
}

int Annie::Rotation() {
	if (!Initialized)
	{
		Initialized = Initialize();
	}

	if (Engine::getOrbMode() == Target_Combo)
	{
		if (!Combo())
		{
			return Engine::OrbBot();
		}
	}
	if (Engine::getOrbMode() == Target_Harrass)
	{
		if (!Harrass())
		{
			return Engine::OrbBot();
		}

	}
	if (Engine::getOrbMode() == Target_LaneClear)
	{
		if (!Laneclear())
		{
			return Engine::OrbBot();
		}

	}
	if (Engine::getOrbMode() == Target_LastHit)
	{
		if (!Lasthit())
		{
			return Engine::OrbBot();
		}
	}
	return 0;
}
