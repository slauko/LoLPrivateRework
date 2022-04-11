#pragma once
#include "Fiora.h"
#include "ChampionIncludes.h"

float Fiora::QRange = 0.f;
float Fiora::WRange = 0.f;
float Fiora::ERange = 0.f;
float Fiora::RRange = 0.f;

float Fiora::QSpeed = HUGE_VALF;
float Fiora::WSpeed = HUGE_VALF;
float Fiora::ESpeed = HUGE_VALF;
float Fiora::RSpeed = HUGE_VALF;

float Fiora::QDelay = 0.f;
float Fiora::WDelay = 0.f;
float Fiora::EDelay = 0.f;
float Fiora::RDelay = 0.f;

bool Fiora::Initialized = false;
bool Fiora::Initialize() {

	QRange = 400.f;
	WRange = 750.f;
	ERange = 175.f;
	RRange = 500.f;

	QSpeed = HUGE_VALF;
	WSpeed = HUGE_VALF;
	ESpeed = HUGE_VALF;
	RSpeed = HUGE_VALF;

	QDelay = 0.25f;
	WDelay = 0.25f;
	EDelay = 0.f;
	RDelay = 0.f;

	return true;
}

GameObject* Fiora::GetVital() {
	for (GameObject* Vital : TargetList::FioraObjects)
	{
		if (!strstr(Vital->GetName().c_str(),"Warning") && !strstr(Vital->GetName().c_str(), "Speed") && !strstr(Vital->GetName().c_str(), "Hit") && !strstr(Vital->GetName().c_str(), "Heal") && !strstr(Vital->GetName().c_str(), "Indicator"))
		{
			return Vital;
		}
	}
	return NULL;
}
Vector3 Fiora::GetVitalSpot() {
// Fiora_*Skin*_Passive_NE "Top"
// Fiora_*Skin*_Passive_SE "Left"
// Fiora_*Skin*_Passive_SW "Bot"
// Fiora_*Skin*_Passive_NW "Right"
	GameObject* Vital = GetVital();
	if (Vital)
	{
		//cout << Vital->GetName().c_str() << endl;
		Vector3 VitalPos = Vital->GetPosition();
		if (strstr(Vital->GetName().c_str(), "NE"))
		{
			VitalPos = {VitalPos.x + 0, VitalPos.y, VitalPos.z + 100.f};
		}
		if (strstr(Vital->GetName().c_str(), "SE"))
		{
			VitalPos = { VitalPos.x - 100.f, VitalPos.y, VitalPos.z};
		}
		if (strstr(Vital->GetName().c_str(), "SW"))
		{
			VitalPos = { VitalPos.x + 0, VitalPos.y, VitalPos.z - 100.f };
		}
		if (strstr(Vital->GetName().c_str(), "NW"))
		{
			VitalPos = { VitalPos.x + 100.f, VitalPos.y, VitalPos.z};
		}
		return VitalPos;
	}
	return { 0.f,0.f,0.f };
}


int Fiora::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target && Engine::AACancelPossible())
			{
				Engine::CastAimedSpell(Engine::pMouse->MousePos, Spell);
			}
		}
	}
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, 1200.f, 1);
			if (Target)
			{
				Vector3 PredPos = GetVitalSpot();
				if (PredPos.x != 0.f &&PredPos.y != 0.f &&PredPos.z != 0.f)
				{
					if (Engine::GetDistance3D(PlayerPos, PredPos) < GetSpellRange(Spell))
					{
						return Engine::CastAimedSpell(PredPos, Spell);
					}
				}
			}
		}
	}
	if (Menu::UseW)
	{
		SpellSlotID Spell = W;
		if (Engine::SpellReady(Spell) && Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target)
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				if (Engine::GetDistance3D(PlayerPos, PredPos) < GetSpellRange(Spell))
				{
					GameObject* ShieldTarget = TargetSelector::GetShieldTarget(65.f, 100.f, false); //Should be Player cause 65.f Range
					if (ShieldTarget)
					{
						return Engine::CastAimedSpell(PredPos, Spell);
					}
				}
			}
		}
	}
	return 0;
}

int Fiora::Harrass() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, 1200.f, 1);
			if (Target)
			{
				Vector3 PredPos = GetVitalSpot();
				if (PredPos.x != 0.f &&PredPos.y != 0.f &&PredPos.z != 0.f)
				{
					if (Engine::GetDistance3D(PlayerPos, PredPos) < GetSpellRange(Spell))
					{
						return Engine::CastAimedSpell(PredPos, Spell);
					}
				}
			}
		}
	}
	return 0;
}

int Fiora::Laneclear() {
	return 0;
}

int Fiora::Lasthit() {
	return 0;
}

int Fiora::Rotation() {
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

