#pragma once
#include "KogMaw.h"
#include "ChampionIncludes.h"

float KogMaw::QRange = 0.f;
float KogMaw::WRange = 0.f;
float KogMaw::ERange = 0.f;
float KogMaw::RRange = 0.f;

float KogMaw::QSpeed = HUGE_VALF;
float KogMaw::WSpeed = HUGE_VALF;
float KogMaw::ESpeed = HUGE_VALF;
float KogMaw::RSpeed = HUGE_VALF;

float KogMaw::QDelay = 0.f;
float KogMaw::WDelay = 0.f;
float KogMaw::EDelay = 0.f;
float KogMaw::RDelay = 0.f;

bool KogMaw::UseR = true;

bool KogMaw::Initialized = false;
bool KogMaw::Initialize() {

	QRange = 1175.f;
	WRange = 500.f;
	ERange = 1360.f;
	RRange = 1300.f;

	QSpeed = 1650.f;
	WSpeed = HUGE_VALF;
	ESpeed = 1400.f;
	RSpeed = HUGE_VALF;

	QDelay = 0.25f;
	WDelay = 0.25f;
	EDelay = 0.f;
	RDelay = 1.1f;

	return true;
}

int KogMaw::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	
	int WLevel = Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(W)->GetSpellLevel();
	int RLevel = Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(R)->GetSpellLevel();
	float WAddRange[5] = { 130.f , 150.f , 170.f , 190.f , 210.f };
	float RCastRange[3] = { 1300.f, 1550.f, 1800.f };
	float AARange = Engine::pLocalPlayer->GetAttackRange();
	float Bound = Engine::pLocalPlayer->GetBoundingRadius();
	if (WLevel)
	{
		WRange = AARange + WAddRange[WLevel - 1];
	}
	if (RLevel)
	{
		RRange = RCastRange[RLevel - 1];
	}
	float QManaCost = Engine::pLocalPlayer->GetSpellbook()->GetManaCost(Q);
	float WManaCost = Engine::pLocalPlayer->GetSpellbook()->GetManaCost(W);
	float EManaCost = Engine::pLocalPlayer->GetSpellbook()->GetManaCost(E);
	float RManaCost = Engine::pLocalPlayer->GetSpellbook()->GetManaCost(R);

	//std::cout << "Q: " << Engine::SpellReady(Q) << std::endl;
	//std::cout << "W: " << Engine::SpellReady(W) << std::endl;
	//std::cout << "E: " << Engine::SpellReady(E) << std::endl;
	//std::cout << "R: " << Engine::SpellReady(R) << std::endl;


	float Mana = Engine::pLocalPlayer->GetMana();
	float ManaPercent = Mana / Engine::pLocalPlayer->GetMaxMana();

	if (KogMaw::UseR)
	{
		SpellSlotID Spell = R;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			//int TargetsInAARange = TargetSelector::GetEnemiesInRange(PlayerPos, Engine::pLocalPlayer->GetAttackRange()).size();
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target && (Mana - RManaCost) > WManaCost)
			{
				float TargetHealthPercent = Target->GetHealth() / Target->GetMaxHealth();
				if (TargetHealthPercent < 0.4f)
				{
					if (Engine::GetDistance3D(PlayerPos, Target->GetPosition()) > AARange + Bound)
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
	}
	if (Menu::UseW)
	{
		SpellSlotID Spell = W;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target)
			{
				return Engine::CastAimedSpell(Engine::pMouse->MousePos, Spell);
			}
		}
	}
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target && (Mana-EManaCost) > WManaCost)
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
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target && (Mana - QManaCost) > WManaCost)
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

int KogMaw::Harrass() {
	return 0;
}

int KogMaw::Laneclear() {
	return 0;
}

int KogMaw::Lasthit() {
	return 0;
}

int KogMaw::Rotation() {
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
