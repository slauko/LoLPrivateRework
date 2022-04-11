#pragma once
#include "Lucian.h"
#include "ChampionIncludes.h"

float Lucian::QRange = 0.f;
float Lucian::WRange = 0.f;
float Lucian::ERange = 0.f;
float Lucian::RRange = 0.f;

float Lucian::QSpeed = HUGE_VALF;
float Lucian::WSpeed = HUGE_VALF;
float Lucian::ESpeed = HUGE_VALF;
float Lucian::RSpeed = HUGE_VALF;

float Lucian::QDelay = 0.f;
float Lucian::WDelay = 0.f;
float Lucian::EDelay = 0.f;
float Lucian::RDelay = 0.f;

bool Lucian::Initialized = false;
bool Lucian::Initialize() {

	QRange = 550.f;
	WRange = 900.f;
	ERange = 550.f;
	RRange = 1200.f;

	QSpeed = HUGE_VALF;
	WSpeed = 2000.f;
	ESpeed = HUGE_VALF;
	RSpeed = HUGE_VALF;

	QDelay = 0.25f;
	WDelay = 0.25f;
	EDelay = 0.f;
	RDelay = 0.75f;

	return true;
}

bool Lucian::EUsed() {
	if (!Menu::UseE)
	{
		return true;
	}
	float maxecd = Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(2)->GetSpellMaxCooldown2();
	float leftecd = Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(2)->GetSpellCooldown1() - *Engine::GameTime;
	if ((maxecd - leftecd) > 0.3f)
	{
		return false;
	}
	return true;
}

int Lucian::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;

	const char* ChannelCheck = "";
	if (Engine::pLocalPlayer->GetSpellbook()->GetActiveSpellEntry())
	{
		ChannelCheck = Engine::pLocalPlayer->GetSpellbook()->GetActiveSpellEntry()->GetActiveSpellInfo()->GetSpellName().c_str();
	}
	int LucQCast = 0;
	if (!strcmp(ChannelCheck, "LucianQ")) {
		LucQCast = 1;
	}
	int LucWCast = 0;
	if (!strcmp(ChannelCheck, "LucianW")) {
		LucWCast = 1;
	}
	int LucR = Engine::pLocalPlayer->GetBuffManager()->HasBuff("LucianR");
	int LucP = Engine::pLocalPlayer->GetBuffManager()->HasBuff("LucianPassiveBuff");

	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && Engine::BlockAA)
		{
			Engine::CastAimedSpell(Engine::EvadePos, Spell);
		}
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target && !LucP && !LucR && Engine::AACancelPossible())
			{
				if (!LucQCast && !LucWCast)
				{
					return Engine::CastAimedSpell(Engine::pMouse->MousePos, Spell);
				}
			}
		}
	}
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA && !Engine::SpellReady(E))
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target && !LucP && !LucR && Engine::AACancelPossible())
			{
				return Engine::CastTargetedSpell(Target, Spell);
			}
		}
	}
	if (Menu::UseW)
	{
		SpellSlotID Spell = W;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA && !Engine::SpellReady(E))
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target && !LucP && !LucR && Engine::AACancelPossible())
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
	return 0;
}

int Lucian::Harrass() {
	return 0;
}

int Lucian::Laneclear() {
	return 0;
}

int Lucian::Lasthit() {
	return 0;
}

int Lucian::Rotation() {
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
