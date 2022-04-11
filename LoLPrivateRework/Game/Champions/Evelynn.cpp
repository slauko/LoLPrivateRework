#pragma once
#include "Evelynn.h"
#include "ChampionIncludes.h"

float Evelynn::QRange = 0.f;
float Evelynn::WRange = 0.f;
float Evelynn::ERange = 0.f;
float Evelynn::RRange = 0.f;

float Evelynn::QSpeed = HUGE_VALF;
float Evelynn::WSpeed = HUGE_VALF;
float Evelynn::ESpeed = HUGE_VALF;
float Evelynn::RSpeed = HUGE_VALF;

float Evelynn::QDelay = 0.f;
float Evelynn::WDelay = 0.f;
float Evelynn::EDelay = 0.f;
float Evelynn::RDelay = 0.f;

bool Evelynn::Initialized = false;
bool Evelynn::Initialize() {

	QRange = 800.f;
	WRange = 1100.f;
	ERange = 235.f;
	RRange = 450.f;

	QSpeed = 1600.f;
	WSpeed = HUGE_VALF;
	ESpeed = HUGE_VALF;
	RSpeed = HUGE_VALF;

	QDelay = 0.2f;
	WDelay = 0.3f;
	EDelay = 0.f;
	RDelay = 0.25f;

	return true;
}

int Evelynn::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;

	int Evepassive = Engine::pLocalPlayer->GetBuffManager()->HasBuff("evelynnstealthring");

	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
		if (Target && Evepassive)
		{
			float WTime = 0;
			BuffManager *BM = Target->GetBuffManager();
			if (BM->GetBuffEntryByName("EvelynnW"))
			{
				WTime = *Engine::GameTime - BM->GetBuffEntryByName("EvelynnW")->GetBuffStartTime();
			}
			if (!strstr(Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(0)->GetSpellInfo()->GetSpellName().c_str(), "EvelynnQ2"))
			{
				if (Engine::SpellReady(Spell))
				{
					if (WTime > 2.5f)
					{
						Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
						float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 1);
						if (HitChance > 0.5f)
						{
							Engine::CastAimedSpell(PredPos, Spell);
						}
					}
				}
			}
			else
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 1);
				if (HitChance > 0.5f)
				{
					Engine::CastAimedSpell(PredPos, Spell);
				}
			}
		}
		if (Target && !Evepassive)
		{
			if (!strstr(Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(0)->GetSpellInfo()->GetSpellName().c_str(), "EvelynnQ2"))
			{
				if (Engine::SpellReady(Spell))
				{
					Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
					float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 1);
					if (HitChance > 0.5f)
					{
						Engine::CastAimedSpell(PredPos, Spell);
					}
				}
			}
			else
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 1);
				if (HitChance > 0.5f)
				{
					Engine::CastAimedSpell(PredPos, Spell);
				}
			}
		}
	}
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target && !Evepassive)
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
			GameObject* Target = TargetSelector::GetTarget(Target_Smite, PlayerPos, GetSpellRange(Spell), 1);
			if (Target)
			{
				return Engine::CastTargetedSpell(Target, Spell);
			}
		}
	}
	return 0;
}

int Evelynn::Harrass() {
	return 0;
}

int Evelynn::Laneclear() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_LaneClear;

	int Evepassive = Engine::pLocalPlayer->GetBuffManager()->HasBuff("evelynnstealthring");

	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
		if (Target && Evepassive)
		{
			float WTime = 0;
			BuffManager *BM = Target->GetBuffManager();
			if (BM->GetBuffEntryByName("EvelynnW"))
			{
				WTime = *Engine::GameTime - BM->GetBuffEntryByName("EvelynnW")->GetBuffStartTime();
			}
			if (!strstr(Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(0)->GetSpellInfo()->GetSpellName().c_str(), "EvelynnQ2"))
			{
				if (Engine::SpellReady(Spell))
				{
					Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
					float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
					if (HitChance > 0.5f)
					{
						Engine::CastAimedSpell(PredPos, Spell);
					}
				}
			}
			else
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
				if (HitChance > 0.5f)
				{
					Engine::CastAimedSpell(PredPos, Spell);
				}
			}
		}
		if (Target && !Evepassive)
		{
			if (!strstr(Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(0)->GetSpellInfo()->GetSpellName().c_str(), "EvelynnQ2"))
			{
				if (Engine::SpellReady(Spell))
				{
					Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
					float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
					if (HitChance > 0.5f)
					{
						Engine::CastAimedSpell(PredPos, Spell);
					}
				}
			}
			else
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
				if (HitChance > 0.5f)
				{
					Engine::CastAimedSpell(PredPos, Spell);
				}
			}
		}
	}
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target && !Evepassive)
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
			GameObject* Target = TargetSelector::GetTarget(Target_Smite, PlayerPos, GetSpellRange(Spell), 1);
			if (Target)
			{
				return Engine::CastTargetedSpell(Target, Spell);
			}
		}
	}
	return 0;
}

int Evelynn::Lasthit() {
	return 0;
}

int Evelynn::Rotation() {
	if (!Initialized)
	{
		Initialized = Initialize();
	}
	int WLevel = Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(1)->GetSpellLevel();
	WRange = 1100.f + (100.f * WLevel);


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
