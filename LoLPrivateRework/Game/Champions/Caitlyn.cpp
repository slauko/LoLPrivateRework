#pragma once
#include "Caitlyn.h"
#include "ChampionIncludes.h"

float Caitlyn::QRange = 0.f;
float Caitlyn::WRange = 0.f;
float Caitlyn::ERange = 0.f;
float Caitlyn::RRange = 0.f;

float Caitlyn::QSpeed = HUGE_VALF;
float Caitlyn::WSpeed = HUGE_VALF;
float Caitlyn::ESpeed = HUGE_VALF;
float Caitlyn::RSpeed = HUGE_VALF;

float Caitlyn::QDelay = 0.f;
float Caitlyn::WDelay = 0.f;
float Caitlyn::EDelay = 0.f;
float Caitlyn::RDelay = 0.f;

bool Caitlyn::Initialized = false;
bool Caitlyn::Initialize() {
	
	QRange = 1250.f;
	WRange = 800.f;
	ERange = 750.f;
	RRange = 3500.f;
	
	QSpeed = 2200.f;
	WSpeed = HUGE_VALF;
	ESpeed = 1600.f;
	RSpeed = HUGE_VALF;

	QDelay = 0.25f;
	WDelay = 0.5f;
	EDelay = 0.25f;
	RDelay = 0.f;

	return true;
}

int Caitlyn::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;

	for (GameObject* Target : TargetList::ChampionList)
	{
		if (Target->GetTeam() == Engine::pLocalPlayer->GetTeam())
		{
			continue;
		}
		if (Engine::GetDistance3D(Engine::pLocalPlayer->GetPosition(), Target) <= 1300.f)
		{
			if (Target->GetBuffManager()->HasBuff("caitlynyordletrapinternal"))
			{
				return Engine::Orbwalk(Target);
			}
		}
	}


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
					float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 1);
					if (HitChance > 0.5f)
					{
						return Engine::CastAimedSpell(PredPos, Spell);
					}
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
				BuffManager *BM = Target->GetBuffManager();
				if (BM->HasBuffType(BuffType::Slow) || BM->HasBuffType(BuffType::Snare) || BM->HasBuffType(BuffType::Stun) ||
					BM->HasBuffType(BuffType::Fear) || BM->HasBuffType(BuffType::Charm) || BM->HasBuffType(BuffType::Asleep) ||
					BM->HasBuffType(BuffType::Knockup) || BM->HasBuffType(BuffType::Grounded) || BM->HasBuffType(BuffType::Taunt))
				{
					Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
					float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
					if (HitChance > 0.5f)
					{
						if (Engine::GetDistance3D(PlayerPos, PredPos) > 800.f)
						{
							return Engine::CastAimedSpell(PredPos, Spell);
						}
					}
				}
			}
		}
	}
	return 0;
}

int Caitlyn::Harrass() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;

	for (GameObject* Target : TargetList::ChampionList)
	{
		if (Target->GetTeam() == Engine::pLocalPlayer->GetTeam())
		{
			continue;
		}
		if (Engine::GetDistance3D(Engine::pLocalPlayer->GetPosition(), Target) <= 1300.f)
		{
			if (Target->GetBuffManager()->HasBuff("caitlynyordletrapinternal"))
			{
				return Engine::Orbwalk(Target);
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
					if (Engine::GetDistance3D(PlayerPos,PredPos) > 800.f)
					{
						return Engine::CastAimedSpell(PredPos, Spell);
					}
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
				BuffManager *BM = Target->GetBuffManager();
				if (BM->HasBuffType(BuffType::Slow) || BM->HasBuffType(BuffType::Snare) || BM->HasBuffType(BuffType::Stun) || BM->HasBuffType(BuffType::Fear) || BM->HasBuffType(BuffType::Charm) || BM->HasBuffType(BuffType::Asleep) || BM->HasBuffType(BuffType::Knockup) || BM->HasBuffType(BuffType::Grounded) || BM->HasBuffType(BuffType::Taunt) || Target->GetAIManager()->IsDashing())
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
	return 0;
}

int Caitlyn::Laneclear() {
	return 0;
}

int Caitlyn::Lasthit() {
	return 0;
}

int Caitlyn::Rotation() {
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
