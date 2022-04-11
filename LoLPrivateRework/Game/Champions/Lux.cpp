#pragma once
#include "Lux.h"
#include "ChampionIncludes.h"

float Lux::QRange = 0.f;
float Lux::WRange = 0.f;
float Lux::ERange = 0.f;
float Lux::RRange = 0.f;

float Lux::QSpeed = HUGE_VALF;
float Lux::WSpeed = HUGE_VALF;
float Lux::ESpeed = HUGE_VALF;
float Lux::RSpeed = HUGE_VALF;

float Lux::QDelay = 0.f;
float Lux::WDelay = 0.f;
float Lux::EDelay = 0.f;
float Lux::RDelay = 0.f;

bool Lux::Initialized = false;
bool Lux::Initialize() {

	QRange = 1175.f;
	WRange = 1075.f;
	ERange = 1100.f;
	RRange = 3340.f;

	QSpeed = 1200.f;
	WSpeed = 1200.f;
	ESpeed = 1800.f;
	RSpeed = HUGE_VALF;

	QDelay = 0.25f;
	WDelay = 0.25f;
	EDelay = 0.25f;
	RDelay = 0.f;

	return true;
}

int Lux::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	if (true/*Menu::UseR*/)
	{
		SpellSlotID Spell = R;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, 3340.f, 1);
			if (Target)
			{
				BuffManager* TargetBM = Target->GetBuffManager();
				if (TargetBM->HasBuffType(BuffType::Snare) ||
					TargetBM->HasBuffType(BuffType::Stun) ||
					TargetBM->HasBuffType(BuffType::Fear) ||
					TargetBM->HasBuffType(BuffType::Charm) ||
					TargetBM->HasBuffType(BuffType::Asleep) ||
					TargetBM->HasBuffType(BuffType::Knockup) ||
					TargetBM->HasBuffType(BuffType::Taunt) ||
					TargetBM->HasBuffType(BuffType::Slow))
				{
					if (Target->GetHealth() / Target->GetMaxHealth() < 0.5f)
					{
						Vector3 PredPos = Prediction::GetPredPos(Target, HUGE_VALF, 0.25f);
						float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, 3340.f, HUGE_VALF, 1.5f, 80, 0);
						if (HitChance > 0.5f)
						{
							return Engine::CastAimedSpell(PredPos, Spell);
						}
					}
				}
			}
		}
	}
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* LuxE = NULL;
			GameObject* LuxEMissile = NULL;
			for (GameObject* Object : TargetList::LuxEObject)
			{
				if (strstr(Object->GetName().c_str(), "Lux_") && strstr(Object->GetName().c_str(), "_E_tar_aoe_sound"))
				{
					LuxE = Object;
				}
				if (strstr(Object->GetName().c_str(), "Lux_") && strstr(Object->GetName().c_str(), "_E_mis"))
				{
					LuxEMissile = Object;
				}
			}
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target)
			{
				if (!LuxE && !LuxEMissile)
				{
					Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
					float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 80, 0);
					if (HitChance > 0.5f)
					{
						return Engine::CastAimedSpell(PredPos, Spell);
					}
				}
			}
			if (LuxE && !LuxEMissile)
			{
				Vector3 LuxEP = LuxE->GetPosition();
				Vector3 LuxEPos = { LuxEP.x,LuxEP.y - 100.f, LuxEP.z };
				float LuxERange = 300.f;
				std::list<GameObject*> ETargets = TargetSelector::GetEnemiesInRange(LuxEPos, LuxERange);
				for (GameObject* Target : ETargets)
				{
					float ERealRange = LuxERange - Target->GetBoundingRadius();
					if (Engine::GetDistance3D(LuxEPos, Target) < ERealRange)
					{
						return Engine::CastAimedSpell(Engine::pMouse->MousePos, Spell);
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
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 80, 1);
				if (HitChance >= 0.6f)
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
			GameObject* Target = TargetSelector::GetShieldTarget(GetSpellRange(Spell), 1.f, 0);
			if (Target)
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 80, 0);
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

int Lux::Harrass() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* LuxE = NULL;
			GameObject* LuxEMissile = NULL;
			for (GameObject* Object : TargetList::LuxEObject)
			{
				if (strstr(Object->GetName().c_str(), "Lux_") && strstr(Object->GetName().c_str(), "_E_tar_aoe_sound"))
				{
					LuxE = Object;
				}
				if (strstr(Object->GetName().c_str(), "Lux_") && strstr(Object->GetName().c_str(), "_E_mis"))
				{
					LuxEMissile = Object;
				}
			}
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target)
			{
				if (!LuxE && !LuxEMissile)
				{
					Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
					float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 80, 0);
					if (HitChance > 0.5f)
					{
						return Engine::CastAimedSpell(PredPos, Spell);
					}
				}
			}
			if (LuxE && !LuxEMissile)
			{
				Vector3 LuxEP = LuxE->GetPosition();
				Vector3 LuxEPos = { LuxEP.x,LuxEP.y - 100.f, LuxEP.z };
				float LuxERange = 300.f;
				std::list<GameObject*> ETargets = TargetSelector::GetEnemiesInRange(LuxEPos, LuxERange);
				
				DWORD color = 0x00FF00FF;
				Engine::DrawCircle(&LuxEPos, LuxERange, &color, 0, 0, 0, 1);
				
				for (GameObject* Target : ETargets)
				{
					float ERealRange = LuxERange - Target->GetBoundingRadius();
					if (Engine::GetDistance3D(LuxEPos, Target) < ERealRange)
					{
						return Engine::CastAimedSpell(Engine::pMouse->MousePos, Spell);
					}
				}
			}
		}
	}
	return 0;
}

int Lux::Laneclear() {
	return 0;
}

int Lux::Lasthit() {
	return 0;
}

int Lux::Rotation() {
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
