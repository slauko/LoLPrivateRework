#pragma once
#include "Twitch.h"
#include "ChampionIncludes.h"

float Twitch::QRange = 0.f;
float Twitch::WRange = 0.f;
float Twitch::ERange = 0.f;
float Twitch::RRange = 0.f;

float Twitch::QSpeed = HUGE_VALF;
float Twitch::WSpeed = HUGE_VALF;
float Twitch::ESpeed = HUGE_VALF;
float Twitch::RSpeed = HUGE_VALF;

float Twitch::QDelay = 0.f;
float Twitch::WDelay = 0.f;
float Twitch::EDelay = 0.f;
float Twitch::RDelay = 0.f;

bool Twitch::Initialized = false;
bool Twitch::Initialize() {
	QRange = 550.f;
	WRange = 615.f;
	ERange = 1200.f;
	RRange = 615.f;

	QSpeed = 1900.f;
	WSpeed = 2000.f;
	ESpeed = HUGE_VALF;
	RSpeed = HUGE_VALF;

	QDelay = 0.25f;
	WDelay = 0.25f;
	EDelay = 0.f;
	RDelay = 0.75f;

	return true;
}

int Twitch::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;


	GameObject* AntiGapClose_Target = TargetSelector::AntiGapCloseTarget(Engine::pLocalPlayer->GetPosition(), ERange);
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{

			int EStacks = 0;
			float EBaseDmg = 0;
			float EStackDmg = 0;
			float ERealDmg = 0;
			GameObject* Target = TargetSelector::ComboTarget(Engine::pLocalPlayer->GetPosition(), ERange, 7);
			if (Target)
			{
				if (Target->GetBuffManager()->HasBuff("TwitchDeadlyVenom"))
				{
					EStacks = Target->GetBuffManager()->GetBuffEntryByName("TwitchDeadlyVenom")->GetBuffCountInt();
				}
				if (EStacks)
				{
					float BonusAtkDmg = Engine::pLocalPlayer->GetBonusAtk();
					float AtkReduceMod = 100.f / (100.f + Target->GetArmor());
					EBaseDmg = 10.f + (Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(2)->GetSpellLevel() * 10.f);
					EStackDmg = ((10.f + (Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(2)->GetSpellLevel() * 5.f)) + (0.35f*BonusAtkDmg) * AtkReduceMod) * EStacks;
					ERealDmg = EBaseDmg + EStackDmg;
					if (Target->GetHealth() < (ERealDmg*0.95))
					{
						return Engine::CastAimedSpell(PlayerPos, Spell);
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
			if (!Engine::pLocalPlayer->GetBuffManager()->HasBuff("TwitchHideInShadows"))
			{
				return Engine::CastAimedSpell(PlayerPos, Spell);
			}
		}
	}
	return 0;
}

int Twitch::Harrass() {
	return 0;
}

int Twitch::Laneclear() {
	return 0;
}

int Twitch::Lasthit() {
	return 0;
}

int Twitch::Rotation() {
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
