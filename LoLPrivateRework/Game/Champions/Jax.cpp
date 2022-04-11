#pragma once
#include "Jax.h"
#include "ChampionIncludes.h"

float Jax::QRange = 0.f;
float Jax::WRange = 0.f;
float Jax::ERange = 0.f;
float Jax::RRange = 0.f;

float Jax::QSpeed = HUGE_VALF;
float Jax::WSpeed = HUGE_VALF;
float Jax::ESpeed = HUGE_VALF;
float Jax::RSpeed = HUGE_VALF;

float Jax::QDelay = 0.f;
float Jax::WDelay = 0.f;
float Jax::EDelay = 0.f;
float Jax::RDelay = 0.f;

bool Jax::Initialized = false;
bool Jax::Initialize() {

	QRange = 700.f;
	WRange = 300.f;
	ERange = 300.f;
	RRange = 200.f;

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

int Jax::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;

	bool WBuff = Engine::pLocalPlayer->GetBuffManager()->HasBuff("jaxempowertwo");
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
				if (Engine::AACancelPossible())
				{
					return Engine::CastAimedSpell(Engine::pMouse->MousePos, Spell);
				}
			}
		}
	}
	int useHydra = 0;
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
				useHydra = 1;
			}
		}
		if (useHydra)
		{
			Utility::UseHydra();
		}
	}
	return 0;
}

int Jax::Harrass() {
	return 0;
}

int Jax::Laneclear() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_LaneClear;

	bool WBuff = Engine::pLocalPlayer->GetBuffManager()->HasBuff("jaxempowertwo");
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
				if (Engine::AACancelPossible())
				{
					return Engine::CastAimedSpell(Engine::pMouse->MousePos, Spell);
				}
			}
		}
	}
	int useHydra = 0;
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
				useHydra = 1;
			}
		}
		if (useHydra)
		{
			Utility::UseHydra();
		}
	}
	return 0;
}

int Jax::Lasthit() {
	return 0;
}

int Jax::Rotation() {
	if (!Initialized)
	{
		Initialized = Initialize();
	}
	Utility::customHydraUsage = true;

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
