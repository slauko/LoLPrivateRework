#pragma once
#include "Xayah.h"
#include "ChampionIncludes.h"

float Xayah::QRange = 0.f;
float Xayah::WRange = 0.f;
float Xayah::ERange = 0.f;
float Xayah::RRange = 0.f;

float Xayah::QSpeed = HUGE_VALF;
float Xayah::WSpeed = HUGE_VALF;
float Xayah::ESpeed = HUGE_VALF;
float Xayah::RSpeed = HUGE_VALF;

float Xayah::QDelay = 0.f;
float Xayah::WDelay = 0.f;
float Xayah::EDelay = 0.f;
float Xayah::RDelay = 0.f;

bool Xayah::Initialized = false;
bool Xayah::Initialize() {

	QRange = 1000.f;
	WRange = 1150.f;
	ERange = 475.f;
	RRange = 1150.f;

	QSpeed = 2075.f;
	WSpeed = 2000.f;
	ESpeed = HUGE_VALF;
	RSpeed = HUGE_VALF;

	QDelay = 0.2f;
	WDelay = 0.25f;
	EDelay = 0.f;
	RDelay = 0.75f;

	return true;
}
bool Xayah::CanStunWithE() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	for (GameObject* Target : TargetList::ChampionList)
	{
		if (Target->GetTeam() == Engine::pLocalPlayer->GetTeam())
		{
			continue;
		}
		Vector3 TargetPos = Target->GetPosition();
		int FeathersHit = 0;
		for (GameObject* FeatherMark : TargetList::XayahFeathers)
		{
			if (!(strstr(FeatherMark->GetName().c_str(), "Xayah_") && strstr(FeatherMark->GetName().c_str(), "_Dagger_Mark")))
			{
				continue;
			}
			for (GameObject* Feather : TargetList::XayahFeathers)
			{
				if (!strstr(Feather->GetName().c_str(), "Feather"))
				{
					continue;
				}
				if (Engine::GetDistance3D(Feather->GetPosition(),FeatherMark->GetPosition()) < 45.f)
				{
					continue;
				}
				Vector3 FeatherPos = Feather->GetPosition();
				if (Prediction::PointOnLineSegment3D(PlayerPos,FeatherPos,TargetPos, 45.f))
				{
					FeathersHit++;
				}
			}
		}
		if (FeathersHit >=3)
		{
			return true;
		}
	}
	return false;
}


int Xayah::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	if (true/*Menu::UseR*/)
	{
		SpellSlotID Spell = R;
		if (Engine::SpellReady(Spell))
		{
			GameObject* ShieldTarget = TargetSelector::GetShieldTarget(65.f, 0.4f, false); //should be player
			if (ShieldTarget)
			{
				GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
				if (Target)
				{
					Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
					float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
					if (HitChance > 0.5f)
					{
						return Engine::CastAimedSpell(PredPos, Spell);
					}
				}
			}
			GameObject* AntiGapClose_Target = TargetSelector::AntiGapCloseTarget(Engine::pLocalPlayer->GetPosition(), 300.f);
			if (AntiGapClose_Target)
			{
				GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
				if (Target)
				{
					Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
					float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
					if (HitChance > 0.5f)
					{
						return Engine::CastAimedSpell(PredPos, Spell);
					}
				}
				Vector3 PredPos = Prediction::GetPredPos(AntiGapClose_Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, AntiGapClose_Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
				if (HitChance > 0.5f)
				{
					return Engine::CastAimedSpell(PredPos, Spell);
				}
			}
		}
	}
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			if (CanStunWithE())
			{
				Engine::CastAimedSpell(Engine::EvadePos, Spell);
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
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target && Engine::AACancelPossible())
			{
				return Engine::CastAimedSpell(Engine::pMouse->MousePos, Spell);
			}
		}
	}
	return 0;
}

int Xayah::Harrass() {
	return 0;
}

int Xayah::Laneclear() {
	return 0;
}

int Xayah::Lasthit() {
	return 0;
}

int Xayah::Rotation() {
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
