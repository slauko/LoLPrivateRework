#pragma once
#include "Brand.h"
#include "ChampionIncludes.h"

float Brand::QRange = 0.f;
float Brand::WRange = 0.f;
float Brand::ERange = 0.f;
float Brand::RRange = 0.f;

float Brand::QSpeed = HUGE_VALF;
float Brand::WSpeed = HUGE_VALF;
float Brand::ESpeed = HUGE_VALF;
float Brand::RSpeed = HUGE_VALF;

float Brand::QDelay = 0.f;
float Brand::WDelay = 0.f;
float Brand::EDelay = 0.f;
float Brand::RDelay = 0.f;

bool Brand::Initialized = false;
bool Brand::Initialize() {
	
	QRange = 1050.f;
	WRange = 900.f;
	ERange = 550.f;
	RRange = 750.f;
	
	QSpeed = 1600.f;
	WSpeed = HUGE_VALF;
	ESpeed = HUGE_VALF;
	RSpeed = HUGE_VALF;

	QDelay = 0.25f;
	WDelay = 0.5f;
	EDelay = 0.f;
	RDelay = 0.f;

	return true;
}

int Brand::Combo() {
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
				Engine::CastTargetedSpell(Target, Spell);
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
				if (BM->HasBuff("BrandAblaze"))
				{
					Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
					float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 80, 1);
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

int Brand::Harrass() {
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
				Engine::CastTargetedSpell(Target, Spell);
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
				if (BM->HasBuff("BrandAblaze"))
				{
					Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
					float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 80, 1);
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
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
				if (HitChance > 0.1f)
				{
					return Engine::CastAimedSpell(PredPos, Spell);
				}
			}
		}
	}
	return 0;
}

int Brand::Laneclear() {
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
				Engine::CastTargetedSpell(Target, Spell);
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
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target)
			{
				BuffManager *BM = Target->GetBuffManager();
				if (BM->HasBuff("BrandAblaze"))
				{
					if (Engine::IsHero(Target))
					{
						Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
						float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 80, 1);
						if (HitChance > 0.5f)
						{
							return Engine::CastAimedSpell(PredPos, Spell);
						}
					}
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
	}
	return 0;
}

int Brand::Lasthit() {
	return 0;
}

int Brand::Rotation() {
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
