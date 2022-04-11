#pragma once
#include "Lulu.h"
#include "ChampionIncludes.h"

float Lulu::QRange = 0.f;
float Lulu::WRange = 0.f;
float Lulu::ERange = 0.f;
float Lulu::RRange = 0.f;

float Lulu::QSpeed = HUGE_VALF;
float Lulu::WSpeed = HUGE_VALF;
float Lulu::ESpeed = HUGE_VALF;
float Lulu::RSpeed = HUGE_VALF;

float Lulu::QDelay = 0.f;
float Lulu::WDelay = 0.f;
float Lulu::EDelay = 0.f;
float Lulu::RDelay = 0.f;

bool Lulu::Initialized = false;
bool Lulu::Initialize() {
	QRange = 900.f;
	WRange = 550.f;
	ERange = 550.f;
	RRange = 800.f;

	QSpeed = 1450.f;
	WSpeed = HUGE_VALF;
	ESpeed = HUGE_VALF;
	RSpeed = HUGE_VALF;

	QDelay = 0.337f;
	WDelay = 0.f;
	EDelay = 0.f;
	RDelay = 0.f;

	return true;
}

int Lulu::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	if (true/*Menu::UseR*/)
	{
		SpellSlotID Spell = R;
		if (Engine::SpellReady(Spell))
		{
			GameObject* Target = TargetSelector::GetShieldTarget(RRange, 0.4f, false);
			if (Target)
			{
				return Engine::CastTargetedSpell(Target, Spell);
			}
			Target = TargetSelector::FriendlyTarget(PlayerPos, RRange, 1);
			if (Target)
			{
				float R_Target2_HealthPercent = Target->GetHealth() / Target->GetMaxHealth();

				int rtargets = TargetSelector::GetEnemiesInRange(Target->GetPosition(), 300.f).size();
				if (rtargets > 0)
				{
					if (R_Target2_HealthPercent < 0.4f)
					{
						return Engine::CastTargetedSpell(Target, Spell);
					}
				}
			}
			Target = TargetSelector::GetShieldTarget(RRange, 0.75f, false);
			if (Target)
			{
				GameObject* AntiGapClose = TargetSelector::AntiGapCloseTarget(Target->GetPosition(), 300.f);
				if (AntiGapClose)
				{
					return Engine::CastTargetedSpell(Target, Spell);
				}
			}
		}
	}
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
				GameObject* EnemyInAARange = TargetSelector::ComboTarget(Friend->GetPosition(), Friend->GetAttackRange()+150.f, 1);
				if (EnemyInAARange && Prediction::IsAttackingEnemy(Friend))
				{
					return Engine::CastTargetedSpell(Friend, Spell);
				}
			}
			GameObject* Enemy = TargetSelector::ComboTarget(Engine::pLocalPlayer->GetPosition(), ERange, 1);
			if (Enemy)
			{
				if (AllyCount < 2) // 1 when player alone .. FeelsBadMan
				{
					return Engine::CastTargetedSpell(Enemy, Spell);
				}
			}
		}
	}
	if (Menu::UseW)
	{
		SpellSlotID Spell = W;
		if (Engine::SpellReady(Spell))
		{
			GameObject* Friend = TargetSelector::FriendlyTarget(PlayerPos, WRange, 2);
			if (Friend)
			{
				float W_Target_HealthPercent = Friend->GetHealth() / Friend->GetMaxHealth();
				GameObject* EnemyInAARange = TargetSelector::ComboTarget(Friend->GetPosition(), Friend->GetAttackRange() + 150.f, 1);
				GameObject* EnemyGapClosing = TargetSelector::AntiGapCloseTarget(Friend->GetPosition(), 400.f);
				if (EnemyGapClosing)
				{
					if (Engine::GetDistance3D(Engine::pLocalPlayer->GetPosition(), EnemyGapClosing) < WRange)
					{
						return Engine::CastTargetedSpell(EnemyGapClosing, Spell);
					}
				}
				if (EnemyInAARange && Prediction::IsAttackingEnemy(Friend))
				{
					//if (!EnemyGapClosing && W_Target_HealthPercent <= 0.4f)
					//{
					//	if (Engine::GetDistance3D(Engine::pLocalPlayer->GetPosition(), EnemyInAARange) < WRange)
					//	{
							return Engine::CastTargetedSpell(Friend, Spell);
				//		}
				//	}
				//	if (!EnemyGapClosing && W_Target_HealthPercent > 0.8f)
				//	{
				//		return Engine::CastTargetedSpell(Friend, Spell);
				//	}
				//	if (!EnemyGapClosing && W_Target_HealthPercent <= 0.8f)
				//	{
				//		float EnemyInAARange_HealthPercent = EnemyInAARange->GetHealth() / EnemyInAARange->GetMaxHealth();
				//		if (EnemyInAARange_HealthPercent <= 0.6f)
				//		{
				//			return Engine::CastTargetedSpell(Friend, Spell);
				//		}
				//	}
				}
			}
		}
	}
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Pixi = NULL;
			for (GameObject* Pix : TargetList::LuluObjects){
				Pixi = Pix;
			}
			GameObject* Target = TargetSelector::ComboTarget(Engine::pLocalPlayer->GetPosition(), QRange, 1);
			if (Target)
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
				if (HitChance > 0.5f)
				{
					//DWORD colorself = 0x00A08080;
					//Engine::DrawCircle(&PredPos, Engine::pLocalPlayer->GetBoundingRadius(), &colorself, 0, 0, 0, 1.f);
					return Engine::CastAimedSpell(PredPos, Spell);
				}
			}
			if (Pixi)
			{
				Target = TargetSelector::ComboTarget(Pixi->GetPosition(), QRange, 1);
				if (Target)
				{
					Vector3 PredPos = Prediction::TwoPointPrediction(Pixi, Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
					float HitChance = Prediction::GetHitchance(Pixi->GetPosition(), PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
					if (HitChance > 0.5f)
					{
						//DWORD colorself = 0x00A08080;
						//Engine::DrawCircle(&PredPos, Engine::pLocalPlayer->GetBoundingRadius(), &colorself, 0, 0, 0, 1.f);
						return Engine::CastAimedSpell(PredPos, Spell);
					}
				}
			}
		}
	}
	return 0;
}

int Lulu::Harrass() {
	return 0;
}

int Lulu::Laneclear() {
	return 0;
}

int Lulu::Lasthit() {
	return 0;
}

int Lulu::Rotation() {
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
