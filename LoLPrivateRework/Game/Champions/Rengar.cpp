#pragma once
#include "Rengar.h"
#include "ChampionIncludes.h"

float Rengar::QRange = 0.f;
float Rengar::WRange = 0.f;
float Rengar::ERange = 0.f;
float Rengar::RRange = 0.f;

float Rengar::QSpeed = HUGE_VALF;
float Rengar::WSpeed = HUGE_VALF;
float Rengar::ESpeed = HUGE_VALF;
float Rengar::RSpeed = HUGE_VALF;

float Rengar::QDelay = 0.f;
float Rengar::WDelay = 0.f;
float Rengar::EDelay = 0.f;
float Rengar::RDelay = 0.f;

bool Rengar::Initialized = false;
bool Rengar::Initialize() {

	QRange = 150.f;
	WRange = 450.f;
	ERange = 1000.f;
	RRange = 25000.f;

	QSpeed = HUGE_VALF;
	WSpeed = HUGE_VALF;
	ESpeed = 1600.f;
	RSpeed = HUGE_VALF;

	QDelay = 0.f;
	WDelay = 0.f;
	EDelay = 0.25f;
	RDelay = 0.f;

	return true;
}

int Rengar::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;

	int RengarPassive = Engine::pLocalPlayer->GetBuffManager()->HasBuff("rengarpassivebuff");
	GameObject* PassiveTarget = TargetSelector::ComboTarget(Engine::pLocalPlayer->GetPosition(), 125.f, 1);

	if (RengarPassive)
	{
		GameObject* JumpTarget = TargetSelector::ComboTarget(Engine::pLocalPlayer->GetPosition(), 725.f, 1);
		if (JumpTarget && !Engine::MouseObject)
		{
			if (Engine::GetDistance3D(Engine::pLocalPlayer->GetPosition(), JumpTarget) > (JumpTarget->GetBoundingRadius() + Engine::pLocalPlayer->GetBoundingRadius() + 155.f))
			{
				Engine::IssueOrder(Engine::pLocalPlayer, Movetype_Attack, &JumpTarget->GetPosition(), JumpTarget, 0, 0, true);
				Engine::ResetAttackTimer();
				return 1;
			}
		}
		if (Engine::MouseObject)
		{
			if (Engine::GetDistance3D(Engine::pLocalPlayer->GetPosition(), Engine::MouseObject) > (Engine::MouseObject->GetBoundingRadius() + Engine::pLocalPlayer->GetBoundingRadius() + 155.f))
			{
				if (Engine::GetDistance3D(Engine::pLocalPlayer->GetPosition(), Engine::MouseObject) < (Engine::pLocalPlayer->GetBoundingRadius() + 725.f))
				{
					Engine::IssueOrder(Engine::pLocalPlayer, Movetype_Attack, &Engine::MouseObject->GetPosition(), Engine::MouseObject, 0, 0, true);
					Engine::ResetAttackTimer();
					return 1;
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
			if (Target && !RengarPassive)
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				if (Engine::GetDistance3D(PlayerPos, PredPos) < GetSpellRange(Spell))
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
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target)
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
	if (Menu::UseW)
	{
		SpellSlotID Spell = W;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target && !RengarPassive)
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

int Rengar::Harrass() {
	return 0;
}

int Rengar::Laneclear() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_LaneClear;

	int RengarPassive = Engine::pLocalPlayer->GetBuffManager()->HasBuff("rengarpassivebuff");
	GameObject* PassiveTarget = TargetSelector::ComboTarget(Engine::pLocalPlayer->GetPosition(), 125.f, 1);

	if (RengarPassive)
	{
		GameObject* JumpTarget = TargetSelector::ComboTarget(Engine::pLocalPlayer->GetPosition(), 725.f, 1);
		if (JumpTarget && !Engine::MouseObject)
		{
			if (Engine::GetDistance3D(Engine::pLocalPlayer->GetPosition(), JumpTarget) > (JumpTarget->GetBoundingRadius() + Engine::pLocalPlayer->GetBoundingRadius() + 155.f))
			{
				Engine::IssueOrder(Engine::pLocalPlayer, Movetype_Attack, &JumpTarget->GetPosition(), JumpTarget, 0, 0, true);
				Engine::ResetAttackTimer();
				return 1;
			}
		}
		if (Engine::MouseObject)
		{
			if (Engine::GetDistance3D(Engine::pLocalPlayer->GetPosition(), Engine::MouseObject) > (Engine::MouseObject->GetBoundingRadius() + Engine::pLocalPlayer->GetBoundingRadius() + 155.f))
			{
				if (Engine::GetDistance3D(Engine::pLocalPlayer->GetPosition(), Engine::MouseObject) < (Engine::pLocalPlayer->GetBoundingRadius() + 725.f))
				{
					Engine::IssueOrder(Engine::pLocalPlayer, Movetype_Attack, &Engine::MouseObject->GetPosition(), Engine::MouseObject, 0, 0, true);
					Engine::ResetAttackTimer();
					return 1;
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
			if (Target && !RengarPassive)
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				if (Engine::GetDistance3D(PlayerPos, PredPos) < GetSpellRange(Spell))
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
			if (Target && !RengarPassive)
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

int Rengar::Lasthit() {
	return 0;
}

int Rengar::Rotation() {
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
