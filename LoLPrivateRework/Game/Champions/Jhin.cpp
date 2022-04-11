#pragma once
#include "Jhin.h"
#include "ChampionIncludes.h"

float Jhin::QRange = 0.f;
float Jhin::WRange = 0.f;
float Jhin::ERange = 0.f;
float Jhin::RRange = 0.f;

float Jhin::QSpeed = HUGE_VALF;
float Jhin::WSpeed = HUGE_VALF;
float Jhin::ESpeed = HUGE_VALF;
float Jhin::RSpeed = HUGE_VALF;

float Jhin::QDelay = 0.f;
float Jhin::WDelay = 0.f;
float Jhin::EDelay = 0.f;
float Jhin::RDelay = 0.f;

bool Jhin::Initialized = false;
bool Jhin::Initialize() {

	QRange = 550.f;
	WRange = 2600.f;
	ERange = 750.f;
	RRange = 3500.f;

	QSpeed = HUGE_VALF;
	WSpeed = HUGE_VALF;
	ESpeed = HUGE_VALF;
	RSpeed = 5000.f;

	QDelay = 0.25f;
	WDelay = 0.75f;
	EDelay = 0.25f;
	RDelay = 0.25f;

	return true;
}

int Jhin::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;

	

	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target)
			{
				BuffManager *BM = Target->GetBuffManager();
				if (BM->HasBuffType(BuffType::Slow) || BM->HasBuffType(BuffType::Snare) || BM->HasBuffType(BuffType::Stun) ||
					BM->HasBuffType(BuffType::Fear) || BM->HasBuffType(BuffType::Charm) || BM->HasBuffType(BuffType::Asleep) ||
					BM->HasBuffType(BuffType::Knockup) || BM->HasBuffType(BuffType::Grounded) || BM->HasBuffType(BuffType::Taunt) || Target->GetAIManager()->IsDashing())
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
				BuffManager *BM = Target->GetBuffManager();
				if (BM->HasBuff("jhinespotteddebuff"))
				{
					int EnemiesInAARange = TargetSelector::GetEnemiesInRange(PlayerPos, Engine::pLocalPlayer->GetAttackRange() + 200.f).size();
					Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
					float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
					if (HitChance > 0.5f)
					{
						if (Engine::GetDistance3D(PlayerPos, PredPos) > Engine::pLocalPlayer->GetAttackRange() + 200.f)
						{
							if (!EnemiesInAARange)
							{
								return Engine::CastAimedSpell(PredPos, Spell);
							}
						}
					}
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

int Jhin::Harrass() {
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
				return Engine::CastTargetedSpell(Target, Spell);
			}
		}
	}
	return 0;
}

int Jhin::Laneclear() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Smite;
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
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
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target && Engine::AACancelPossible())
			{
				return Engine::CastTargetedSpell(Target, Spell);
			}
		}
	}
	return 0;
}

int Jhin::Lasthit() {
	return 0;
}

int Jhin::Rotation() {
	if (!Initialized)
	{
		Initialized = Initialize();
	}

	if (Engine::getOrbMode() == Target_Combo)
	{
		Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
		TargetMode Mode = Target_Combo;
		float RStartTime = Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(3)->GetStartTime();
		if (RStartTime)
		{
			SpellSlotID Spell = R;
			DWORD mousecolor = 0x00808880;
			Engine::DrawCircle(&Engine::pMouse->MousePos, 500.f, &mousecolor, 0, 0, 0, 1.f);
			GameObject* Target = TargetSelector::GetTarget(Mode, Engine::pMouse->MousePos, 500.f, 1);
			if (Target)
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
				if (HitChance > 0.5f)
				{
					return Engine::CastAimedSpell(PredPos, Spell);
				}
			}
			return 1;
		}
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
