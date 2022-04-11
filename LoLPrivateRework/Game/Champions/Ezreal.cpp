#pragma once
#include "Ezreal.h"
#include "ChampionIncludes.h"

float Ezreal::QRange = 0.f;
float Ezreal::WRange = 0.f;
float Ezreal::ERange = 0.f;
float Ezreal::RRange = 0.f;

float Ezreal::QSpeed = HUGE_VALF;
float Ezreal::WSpeed = HUGE_VALF;
float Ezreal::ESpeed = HUGE_VALF;
float Ezreal::RSpeed = HUGE_VALF;

float Ezreal::QDelay = 0.f;
float Ezreal::WDelay = 0.f;
float Ezreal::EDelay = 0.f;
float Ezreal::RDelay = 0.f;

bool Ezreal::Initialized = false;
bool Ezreal::Initialize() {

	QRange = 1100.f;
	WRange = 1100.f;
	ERange = 475.f;
	RRange = 25000.f;

	QSpeed = 2000.f;
	WSpeed = 2000.f;
	ESpeed = HUGE_VALF;
	RSpeed = HUGE_VALF;

	QDelay = 0.25f;
	WDelay = 0.25f;
	EDelay = 0.f;
	RDelay = 0.75f;

	return true;
}

int Ezreal::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && Engine::BlockAA)
		{
			Engine::CastAimedSpell(Engine::EvadePos, Spell);
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
				if (HitChance > 0.5f)
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
			std::list<GameObject*> Q_Targets = TargetSelector::GetEnemiesInRange(PlayerPos, GetSpellRange(Spell));
			if (Q_Targets.size() > 1) // sort if more then 1 target only
			{
				Q_Targets.sort([](GameObject* f, GameObject* s) { return f->GetHealth() < s->GetHealth(); });
			}
			for (GameObject* Target : Q_Targets)
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

int Ezreal::Harrass() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			std::list<GameObject*> Q_Targets = TargetSelector::GetEnemiesInRange(PlayerPos, GetSpellRange(Spell));
			if (Q_Targets.size() > 1) // sort if more then 1 target only
			{
				Q_Targets.sort([](GameObject* f, GameObject* s) { return f->GetHealth() < s->GetHealth(); });
			}
			for (GameObject* Target : Q_Targets)
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

int Ezreal::Laneclear() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Smite;
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			std::list<GameObject*> Q_Targets = TargetSelector::GetEnemiesInRange(PlayerPos, 2200.f);
			if (Q_Targets.size() > 1) // sort if more then 1 target only
			{
				Q_Targets.sort([](GameObject* f, GameObject* s) { return f->GetHealth() < s->GetHealth(); });
			}
			for (GameObject* Target : Q_Targets)
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 1);
				if (HitChance > 0.5f)
				{
					return Engine::CastAimedSpell(PredPos, Spell);
				}
			}
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target)
			{
				if (Engine::IsMinion(Target))
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
	}
	return 0;
}

int Ezreal::Lasthit() {
	return 0;
}

int Ezreal::Rotation() {
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
