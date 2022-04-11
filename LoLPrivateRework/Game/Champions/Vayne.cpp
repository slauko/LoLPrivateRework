#pragma once
#include "Vayne.h"
#include "ChampionIncludes.h"

float Vayne::QRange = 0.f;
float Vayne::WRange = 0.f;
float Vayne::ERange = 0.f;
float Vayne::RRange = 0.f;

float Vayne::QSpeed = HUGE_VALF;
float Vayne::WSpeed = HUGE_VALF;
float Vayne::ESpeed = HUGE_VALF;
float Vayne::RSpeed = HUGE_VALF;

float Vayne::QDelay = 0.f;
float Vayne::WDelay = 0.f;
float Vayne::EDelay = 0.f;
float Vayne::RDelay = 0.f;

bool Vayne::Initialized = false;
bool Vayne::Initialize() {

	QRange = 550.f;
	WRange = 550.f;
	ERange = 550.f;
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

Vector3 Vayne::GetPushEndPos(GameObject* Target) {
	float EPushRange = 475.f;

	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	Vector3 TargetPos = Target->GetPosition();
	Vector3 totargetvec = Vector3(TargetPos.x - PlayerPos.x, TargetPos.y - PlayerPos.y, TargetPos.z - PlayerPos.z);

	float length = sqrt((totargetvec.x * totargetvec.x) + (totargetvec.y * totargetvec.y) + (totargetvec.z * totargetvec.z));
	Vector3 totargetvecnorm = Vector3(totargetvec.x / length, totargetvec.y / length, totargetvec.z / length);
	float mod = EPushRange;
	Vector3 PushEndPos = Vector3(TargetPos.x + (totargetvecnorm.x*mod), TargetPos.y + (totargetvecnorm.y*mod), TargetPos.z + (totargetvecnorm.z*mod));
	return PushEndPos;
}

int Vayne::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;


	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* AntiGapClose_Target = TargetSelector::AntiGapCloseTarget(Engine::pLocalPlayer->GetPosition(), 300.f);
			if (AntiGapClose_Target)
			{
				Engine::CastTargetedSpell(AntiGapClose_Target, Spell);
			}
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target)
			{
				DWORD pushcolor = 0x00FFFF00;
				Vector3 PushEndPos = GetPushEndPos(Target);
				Engine::DrawCircle(&PushEndPos, 10, &pushcolor, 0, 0, 0, 1.f);
				if (Prediction::WallBetween(Target->GetPosition(), PushEndPos, 1))
				{
					Engine::CastTargetedSpell(Target, Spell);
				}

			}
		}
	}
	return 0;
}

int Vayne::Harrass() {
	return 0;
}

int Vayne::Laneclear() {
	return 0;
}

int Vayne::Lasthit() {
	return 0;
}

int Vayne::Rotation() {
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
