#pragma once
#include "Orianna.h"
#include "ChampionIncludes.h"

float Orianna::QRange = 0.f;
float Orianna::WRange = 0.f;
float Orianna::ERange = 0.f;
float Orianna::RRange = 0.f;

float Orianna::QSpeed = HUGE_VALF;
float Orianna::WSpeed = HUGE_VALF;
float Orianna::ESpeed = HUGE_VALF;
float Orianna::RSpeed = HUGE_VALF;

float Orianna::QDelay = 0.f;
float Orianna::WDelay = 0.f;
float Orianna::EDelay = 0.f;
float Orianna::RDelay = 0.f;

bool Orianna::Initialized = false;
bool Orianna::Initialize() {
	QRange = 825.f;
	WRange = 240.f;
	ERange = 1100.f;
	RRange = 425.f;

	QSpeed = 1400.f;
	WSpeed = HUGE_VALF;
	ESpeed = HUGE_VALF;
	RSpeed = HUGE_VALF;

	QDelay = 0.25f;
	WDelay = 0.f;
	EDelay = 0.f;
	RDelay = 0.75f;

	return true;
}

GameObject* Orianna::OriBall;
GameObject* Orianna::GetOriBall() {
	GameObject* DoomBall = NULL;
	GameObject* GreenRing = NULL;
	GameObject* GhostBind = NULL;
	for (GameObject* OriballObject : TargetList::OriballObjects)
	{
		//std::cout << OriballObject->GetName().c_str() << std::endl;
		if (!strcmp(OriballObject->GetName().c_str(), "TheDoomBall"))
		{
			DoomBall = OriballObject;
		}
		if (strstr(OriballObject->GetName().c_str(), "Q_yomu_ring_green"))
		{
			GreenRing = OriballObject;
		}
		if (strstr(OriballObject->GetName().c_str(), "Q_Ghost_Bind"))
		{
			GhostBind = TargetSelector::FriendlyTarget(OriballObject->GetPosition(),65.f,1);
		}
	}
	//std::cout << "-------------------" << std::endl;
	if (DoomBall && GreenRing)
	{
		//std::cout << "3" << std::endl;

		DWORD color = 0x00FF00FF;
		Engine::DrawAroundObject(GreenRing, WRange, &color);
		return GreenRing;
	}
	if (GhostBind)
	{
		//std::cout << "3" << std::endl;

		DWORD color = 0x00FF00FF;
		Engine::DrawAroundObject(GhostBind, WRange, &color);
		return GhostBind;
	}
	//std::cout << Engine::pLocalPlayer->GetChampionName().c_str() << std::endl;
	if (!strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "OriannaNoBall") == NULL)
	{
		DWORD color = 0x00FF00FF;
		Engine::DrawAroundObject(Engine::pLocalPlayer, WRange, &color);
		return Engine::pLocalPlayer;
	}
	return NULL;
}

int Orianna::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	if (!OriBall)
	{
		return 0;
	}
	Vector3 OriBallPos = OriBall->GetPosition();
	if (true/*Menu::UseR*/)
	{
		SpellSlotID Spell = R;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			int TargetsForR = 0;
			float RRange = GetSpellRange(Spell);
			std::list<GameObject*> RTargets = TargetSelector::GetEnemiesInRange(OriBallPos, RRange);
			for (GameObject* Target : RTargets)
			{
				float RRealRange = RRange - Target->GetBoundingRadius();
				if (Engine::GetDistance3D(OriBallPos, Target) < RRealRange)
				{
					TargetsForR++;
				}
			}
			if (TargetsForR > 1)
			{
				return Engine::CastAimedSpell(Engine::pMouse->MousePos, Spell);
			}
			if (TargetsForR > 0 && GetAsyncKeyState(Menu::smitekey)) //force R on 1 Target
			{
				return Engine::CastAimedSpell(Engine::pMouse->MousePos, Spell);
			}
		}
	}
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell))
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, OriBall->GetPosition(), GetSpellRange(Spell), 1);
			if (Target)
			{
				Vector3 PredPos = Prediction::TwoPointPrediction(OriBall, Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
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
		if (Engine::SpellReady(Spell))
		{
			float WRange = GetSpellRange(Spell);
			std::list<GameObject*> WTargets = TargetSelector::GetEnemiesInRange(OriBallPos, WRange);
			for (GameObject* Target : WTargets)
			{
				float WRealRange = WRange - Target->GetBoundingRadius();
				if (Engine::GetDistance3D(OriBallPos, Target) < WRealRange)
				{
					return Engine::CastAimedSpell(Engine::pMouse->MousePos, Spell);
				}
			}
		}
	}
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell))
		{
			GameObject* Friend = TargetSelector::GetShieldTarget(ERange, 0.8f);
			if (!Friend)
			{
				if (Prediction::IsCollisioned(Champion, OriBall->GetPosition(), 70))
				{
					return Engine::CastTargetedSpell(Engine::pLocalPlayer, Spell);
				}
			}
			if (Friend)
			{
				return Engine::CastTargetedSpell(Friend, Spell);
			}
		}
	}
	return 0;
}

int Orianna::Harrass() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	if (!OriBall)
	{
		return 0;
	}
	Vector3 OriBallPos = OriBall->GetPosition();
	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell))
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, OriBall->GetPosition(), GetSpellRange(Spell), 1);
			if (Target)
			{
				Vector3 PredPos = Prediction::TwoPointPrediction(OriBall, Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
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
		if (Engine::SpellReady(Spell))
		{
			float WRange = GetSpellRange(Spell);
			std::list<GameObject*> RTargets = TargetSelector::GetEnemiesInRange(OriBallPos, WRange);
			for (GameObject* Target : RTargets)
			{
				float WRealRange = WRange - Target->GetBoundingRadius();
				if (Engine::GetDistance3D(OriBallPos, Target) < WRealRange)
				{
					return Engine::CastAimedSpell(Engine::pMouse->MousePos, Spell);
				}
			}			
		}
	}
	return 0;
}

int Orianna::Laneclear() {
	if (!OriBall)
	{
		return 0;
	}
	return 0;
}

int Orianna::Lasthit() {
	if (!OriBall)
	{
		return 0;
	}
	return 0;
}

int Orianna::Rotation() {
	if (!Initialized)
	{
		Initialized = Initialize();
	}
	OriBall = GetOriBall();
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
