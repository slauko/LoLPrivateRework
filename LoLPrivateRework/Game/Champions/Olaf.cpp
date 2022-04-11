#pragma once
#include "Olaf.h"
#include "ChampionIncludes.h"
bool Engine::OlafSelected = false;

float Olaf::QRange = 0.f;
float Olaf::WRange = 0.f;
float Olaf::ERange = 0.f;
float Olaf::RRange = 0.f;

float Olaf::QSpeed = HUGE_VALF;
float Olaf::WSpeed = HUGE_VALF;
float Olaf::ESpeed = HUGE_VALF;
float Olaf::RSpeed = HUGE_VALF;

float Olaf::QDelay = 0.f;
float Olaf::WDelay = 0.f;
float Olaf::EDelay = 0.f;
float Olaf::RDelay = 0.f;

bool Olaf::Initialized = false;
bool Olaf::Initialize() {
	Engine::OlafSelected = true;

	QRange = 1150.f;
	WRange = 325.f;
	ERange = 325.f;
	RRange = 25000.f;

	QSpeed = 1600.f;
	WSpeed = HUGE_VALF;
	ESpeed = HUGE_VALF;
	RSpeed = HUGE_VALF;

	QDelay = 0.25f;
	WDelay = 0.f;
	EDelay = 0.f;
	RDelay = 0.f;

	return true;
}

Vector3 Olaf::GetAxePredPos(Vector3 PredPos) {
	Vector3 playerpos = Engine::pLocalPlayer->GetPosition();
	Vector3 totargetvec = Vector3(PredPos.x - playerpos.x, PredPos.y - playerpos.y, PredPos.z - playerpos.z);
	float length = sqrt((totargetvec.x * totargetvec.x) + (totargetvec.y * totargetvec.y) + (totargetvec.z * totargetvec.z));
	Vector3 totargetvecnorm = Vector3(totargetvec.x / length, totargetvec.y / length, totargetvec.z / length);
	float mod = 50.f;
	Vector3 AxePredPos = Vector3(PredPos.x + (totargetvecnorm.x*mod), PredPos.y + (totargetvecnorm.y*mod), PredPos.z + (totargetvecnorm.z*mod));
	return AxePredPos;
}

int Olaf::Combo() {
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
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				if (Engine::GetDistance3D(PlayerPos, PredPos) < GetSpellRange(Spell) && Engine::AACancelPossible())
				{
					return Engine::CastTargetedSpell(Target, Spell);
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
				Vector3 AxePred = GetAxePredPos(PredPos);
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
			if (Target)
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				if (Engine::GetDistance3D(PlayerPos, PredPos) < GetSpellRange(Spell))
				{
					return Engine::CastAimedSpell(PredPos, Spell);
				}
			}
		}
	}
	return 0;
}

int Olaf::Harrass() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target)
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				Vector3 AxePred = GetAxePredPos(PredPos);
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

int Olaf::Laneclear() {
	return 0;
}

int Olaf::Lasthit() {
	return 0;
}

int Olaf::Rotation() {
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
