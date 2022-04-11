#pragma once
#include "Kalista.h"
#include "ChampionIncludes.h"

float Kalista::QRange = 0.f;
float Kalista::WRange = 0.f;
float Kalista::ERange = 0.f;
float Kalista::RRange = 0.f;

float Kalista::QSpeed = HUGE_VALF;
float Kalista::WSpeed = HUGE_VALF;
float Kalista::ESpeed = HUGE_VALF;
float Kalista::RSpeed = HUGE_VALF;

float Kalista::QDelay = 0.f;
float Kalista::WDelay = 0.f;
float Kalista::EDelay = 0.f;
float Kalista::RDelay = 0.f;

bool Kalista::Initialized = false;
bool Kalista::Initialize() {
	QRange = 1150.f;
	WRange = 25000.f;
	ERange = 1000.f;
	RRange = 25000.f;

	QSpeed = 2000.f;
	WSpeed = 2000.f;
	ESpeed = HUGE_VALF;
	RSpeed = HUGE_VALF;

	QDelay = 0.25f;
	WDelay = 0.25f;
	EDelay = 0.f;
	RDelay = 0.75f;

	return true;
}

float Kalista::GetRawRendDamage(GameObject* target)
{

	float RawRendDamage[5] = { 20 , 30 , 40 , 50 , 60 };
	float RawRendDamagePerSpear[5] = { 10, 14, 19, 25, 32 };
	float RawRendDamageMultiplier[5] = { 0.6f, 0.6f, 0.6f, 0.6f, 0.6f };
	float RawRendDamagePerSpearMultiplier[5] = { 0.20f , 0.2375f , 0.275f , 0.3125f , 0.35f };

	// Get buff
	GameObject* me = Engine::pLocalPlayer;
	auto buff = target->GetBuffManager();
	auto ELevel = me->GetSpellbook()->GetSpellSlot(2)->GetSpellLevel();

	if (buff != NULL) {
		auto tbuffcount = buff->HasBuff("kalistaexpungemarker");
		if (tbuffcount != 0 )
		{
			return (RawRendDamage[ELevel - 1] + RawRendDamageMultiplier[ELevel - 1] * (Engine::pLocalPlayer->GetBaseAtk() + Engine::pLocalPlayer->GetBonusAtk())) + // Base damage
				(tbuffcount - 1) * // Spear count
				(RawRendDamagePerSpear[ELevel - 1] + RawRendDamagePerSpearMultiplier[ELevel - 1] * (Engine::pLocalPlayer->GetBaseAtk() + Engine::pLocalPlayer->GetBonusAtk())); // Damage per spear
		}
	}
	return 0.f;
}

int Kalista::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			for (GameObject* E_Target : TargetList::ChampionList) //for execute
			{
				if (E_Target->GetTeam() == Engine::pLocalPlayer->GetTeam())
				{
					continue;
				}					
				if (Engine::GetDistance3D(PlayerPos, E_Target) > GetSpellRange(Spell))
				{
					continue;
				}
				if (!E_Target->GetBuffManager()->HasBuff("kalistaexpungemarker"))
				{
					continue;
				}
				for (GameObject* E_Target2 : TargetList::MinionList) //for slow
				{
					if (E_Target2->GetTeam() == Engine::pLocalPlayer->GetTeam())
					{
						continue;
					}
					if (Engine::GetDistance3D(PlayerPos, E_Target2) > GetSpellRange(Spell))
					{
						continue;
					}
					if (!E_Target2->GetBuffManager()->HasBuff("kalistaexpungemarker"))
					{
						continue;
					}
					float DmgReductionMod = 100.f / (100.f + E_Target2->GetArmor());
					float ERealDmg = GetRawRendDamage(E_Target2) * DmgReductionMod;
					if (Engine::isEpicJungle(E_Target2))
					{
						ERealDmg *= 0.5f;
					}
					if (E_Target2->GetHealth() < ERealDmg)
					{
						return Engine::CastAimedSpell(PlayerPos, Spell);
					}
				}
				float DmgReductionMod = 100.f / (100.f + E_Target->GetArmor());
				float ERealDmg = GetRawRendDamage(E_Target) * DmgReductionMod;
				if (E_Target->GetHealth() < ERealDmg)
				{
					return Engine::CastAimedSpell(PlayerPos, Spell);
				}
			}
		}
	}
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target)
			{
				return Engine::CastAimedSpell(Target->GetPosition(), Spell);
				Engine::IssueOrder(Engine::pLocalPlayer, Movetype_Move, &Engine::EvadePos, NULL, 0, 0, true);
			}
		}
	}
	return 0;
}

int Kalista::Harrass() {
	return 0;
}

int Kalista::Laneclear() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_LaneClear;
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			for (GameObject* E_Target : TargetList::MinionList)
			{
				if (E_Target->GetTeam() == Engine::pLocalPlayer->GetTeam())
				{
					continue;
				}
				if (Engine::GetDistance3D(PlayerPos, E_Target) > GetSpellRange(Spell))
				{
					continue;
				}
				float DmgReductionMod = 100.f / (100.f + E_Target->GetArmor());
				float ERealDmg = GetRawRendDamage(E_Target) * DmgReductionMod;
				if (Engine::isEpicJungle(E_Target))
				{
					ERealDmg *= 0.5f;
				}
				if (E_Target->GetHealth() < ERealDmg)
				{
					return Engine::CastAimedSpell(PlayerPos, Spell);
				}
			}
		}
	}
	return 0;
}

int Kalista::Lasthit() {
	return 0;
}

int Kalista::Rotation() {
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
