#pragma once
#include "Janna.h"
#include "ChampionIncludes.h"

float Janna::QRange = 0.f;
float Janna::WRange = 0.f;
float Janna::ERange = 0.f;
float Janna::RRange = 0.f;

float Janna::QSpeed = HUGE_VALF;
float Janna::WSpeed = HUGE_VALF;
float Janna::ESpeed = HUGE_VALF;
float Janna::RSpeed = HUGE_VALF;

float Janna::QDelay = 0.f;
float Janna::WDelay = 0.f;
float Janna::EDelay = 0.f;
float Janna::RDelay = 0.f;

bool Janna::Initialized = false;
bool Janna::Initialize() {

	QRange = 1750.f;
	WRange = 550.f;
	ERange = 800.f;
	RRange = 725.f;

	QSpeed = 1200.f;
	WSpeed = 1200.f;
	ESpeed = 1200.f;
	RSpeed = HUGE_VALF;

	QDelay = 0.25f;
	WDelay = 0.25f;
	EDelay = 0.25f;
	RDelay = 0.f;

	return true;
}

int Janna::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell))
		{
			int AllyCount = TargetSelector::GetAlliesInRange(Engine::pLocalPlayer->GetPosition(), ERange * 1.5f).size();
			GameObject* Friend = TargetSelector::GetShieldTarget(ERange, 1.f, false);
			if (Friend)
			{
				return Engine::CastTargetedSpell(Friend, Spell);
			}
			Friend = TargetSelector::FriendlyTarget(Engine::pLocalPlayer->GetPosition(), ERange, 2);
			if (Friend)
			{
				GameObject* EnemyInAARange = TargetSelector::ComboTarget(Friend->GetPosition(), Friend->GetAttackRange(), 1);
				if (EnemyInAARange && Prediction::IsAttackingEnemy(Friend))
				{
					return Engine::CastTargetedSpell(Friend, Spell);
				}
			}
		}
	}
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::AntiGapCloseTarget(PlayerPos, 1000.f);
			if (Target)
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 80, 0);
				if (HitChance > 0.5f)
				{
					return Engine::CastAimedSpell(PredPos, Spell);
				}
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
				return Engine::CastTargetedSpell(Target, Spell);
			}
		}
	}
	return 0;
}

int Janna::Harrass() {
	return 0;
}

int Janna::Laneclear() {
	return 0;
}

int Janna::Lasthit() {
	return 0;
}

int Janna::Rotation() {
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
