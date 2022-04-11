#pragma once
#include "Darius.h"
#include "ChampionIncludes.h"

float Darius::QRange = 0.f;
float Darius::WRange = 0.f;
float Darius::ERange = 0.f;
float Darius::RRange = 0.f;

float Darius::QSpeed = HUGE_VALF;
float Darius::WSpeed = HUGE_VALF;
float Darius::ESpeed = HUGE_VALF;
float Darius::RSpeed = HUGE_VALF;

float Darius::QDelay = 0.f;
float Darius::WDelay = 0.f;
float Darius::EDelay = 0.f;
float Darius::RDelay = 0.f;


bool Darius::Initialized = false;
bool Darius::Initialize() {

	QRange = 425.f;
	WRange = 300.f;
	ERange = 535.f;
	RRange = 460.f;

	QSpeed = HUGE_VALF;
	WSpeed = HUGE_VALF;
	ESpeed = HUGE_VALF;
	RSpeed = HUGE_VALF;

	QDelay = 0.f;
	WDelay = 0.f;
	EDelay = 0.25f;
	RDelay = 0.f;

	return true;
}

int Darius::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	bool QCast = Engine::pLocalPlayer->GetBuffManager()->HasBuff("dariusqcast");
	bool WBuff = Engine::pLocalPlayer->GetBuffManager()->HasBuff("dariusnoxiantacticsonh");
	TargetMode Mode = Target_Combo;
	if (true/*Menu::UseR*/)
	{
		SpellSlotID Spell = R;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 6);
			if (Target)
			{
				int RStacks = Target->GetBuffManager()->HasBuff("DariusHemo");
				int RLevel = Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(3)->GetSpellLevel();
				float PlayerAtkDmg = Engine::pLocalPlayer->GetBaseAtk() + Engine::pLocalPlayer->GetBonusAtk();
				float DmgMod = 1.f + (0.2f * (float)RStacks);
				float RDamage = ((100.f * (float)RLevel * DmgMod) + (PlayerAtkDmg * 0.75f * DmgMod));

				if (Target->GetHealth() <= RDamage)
				{
					return Engine::CastTargetedSpell(Target, Spell);
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
			if (Target && !QCast)
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
				if (HitChance > 0.5f)
				{
					if (Engine::GetDistance3D(PlayerPos, PredPos) > 205.f)
					{
						Engine::CastAimedSpell(PredPos, Spell);
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
			if (Target && !QCast)
			{
				if (Engine::AACancelPossible())
				{
					return Engine::CastAimedSpell(Engine::pMouse->MousePos, Spell);
				}
			}
		}
	}
	int NoWReady = 0;
	if (!Engine::SpellReady(W))
	{
		float WDuration = 0.f;
		if (WBuff)
		{
			WDuration = 4.f;
		}
		float wleftcd = (Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(1)->GetSpellCooldown1() + WDuration) - *Engine::GameTime;
		if (wleftcd > WDuration)
		{
			if (Engine::AACancelPossible())
			{
				NoWReady = 1;
			}
			if (strstr(Engine::LastAttack, "ONHAttack"))
			{
				NoWReady = 1;
			}
		}
		if (NoWReady)
		{
			Utility::UseHydra();
		}
	}
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target && NoWReady && Engine::AACancelPossible())
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
				if (HitChance > 0.5f)
				{
					if (Engine::GetDistance3D(PlayerPos, PredPos) > 205.f)
					{
						Engine::CastAimedSpell(PredPos, Spell);
					}
				}
			}
		}
	}
	return 0;
}

int Darius::Harrass() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	bool QCast = Engine::pLocalPlayer->GetBuffManager()->HasBuff("dariusqcast");
	TargetMode Mode = Target_Combo;
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target && !QCast)
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
				if (HitChance > 0.5f)
				{
					if (Engine::GetDistance3D(PlayerPos, PredPos) > 205.f)
					{
						Engine::CastAimedSpell(PredPos, Spell);
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
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
				if (HitChance > 0.5f)
				{
					if (Engine::GetDistance3D(PlayerPos, PredPos) > 205.f)
					{
						Engine::CastAimedSpell(PredPos, Spell);
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
			if (Target && !QCast)
			{
				if (Engine::AACancelPossible())
				{
					return Engine::CastAimedSpell(Engine::pMouse->MousePos, Spell);
				}
			}
		}
	}
	return 0;
}

int Darius::Laneclear() {
	return 0;
}

int Darius::Lasthit() {
	return 0;
}

int Darius::Rotation() {
	if (!Initialized)
	{
		Initialized = Initialize();
	}
	Utility::customHydraUsage = true;
	//std::cout << Engine::AACancelPossible() << std::endl;

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

