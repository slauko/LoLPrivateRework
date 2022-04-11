#pragma once
#include "Xerath.h"
#include "ChampionIncludes.h"

float Xerath::QRange = 0.f;
float Xerath::WRange = 0.f;
float Xerath::ERange = 0.f;
float Xerath::RRange = 0.f;

float Xerath::QSpeed = HUGE_VALF;
float Xerath::WSpeed = HUGE_VALF;
float Xerath::ESpeed = HUGE_VALF;
float Xerath::RSpeed = HUGE_VALF;

float Xerath::QDelay = 0.f;
float Xerath::WDelay = 0.f;
float Xerath::EDelay = 0.f;
float Xerath::RDelay = 0.f;

bool Xerath::Initialized = false;
bool Xerath::Initialize() {

	QRange = 1400.f;
	WRange = 900.f;
	ERange = 900.f;
	RRange = 7500.f;

	QSpeed = HUGE_VALF;
	WSpeed = HUGE_VALF;
	ESpeed = 1500.f;
	RSpeed = HUGE_VALF;

	QDelay = 0.45f;
	WDelay = 0.45f;
	EDelay = 0.25f;
	RDelay = 0.55f;

	return true;
}

int Xerath::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;

	float QChargeRange = 0.f;

	float QStartTime = Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(0)->GetStartTime();

	if (Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(3)->GetSpellLevel())
	{
		RRange = 2200.f + 1320.f * Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(3)->GetSpellLevel();
	}
	if (QStartTime)
	{
		float QChargeTime = *Engine::GameTime - QStartTime;
		QChargeRange = 750.f + (433.3333f*QChargeTime);
		if (QChargeRange > 1500.f)
		{
			QChargeRange = 1500.f;
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
				BuffManager* TargetBM = Target->GetBuffManager();
				if (TargetBM->HasBuffType(BuffType::Slow) || TargetBM->HasBuffType(BuffType::Snare) || TargetBM->HasBuffType(BuffType::Stun) || TargetBM->HasBuffType(BuffType::Fear) || TargetBM->HasBuffType(BuffType::Charm) || TargetBM->HasBuffType(BuffType::Asleep) || TargetBM->HasBuffType(BuffType::Knockup) || TargetBM->HasBuffType(BuffType::Grounded) || TargetBM->HasBuffType(BuffType::Taunt) || Target->GetAIManager()->IsDashing())
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
				float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
				if (HitChance > 0.1)
				{
					return Engine::CastAimedSpell(PredPos, Spell);
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
				if (!QStartTime)
				{
					return Engine::CastAimedSpell(Engine::pMouse->MousePos, Spell);
				}
			}
		}
		const char* ChannelCheck = "";
		if (Engine::pLocalPlayer->GetSpellbook()->GetActiveSpellEntry())
		{
			if (Engine::pLocalPlayer->GetSpellbook()->GetActiveSpellEntry()->GetActiveSpellInfo())
			{
				ChannelCheck = Engine::pLocalPlayer->GetSpellbook()->GetActiveSpellEntry()->GetActiveSpellInfo()->GetSpellName().c_str();
			}
		}
		if (Engine::MouseObject)
		{
			Vector3 PredPos = Prediction::GetPredPos(Engine::MouseObject, GetSpellSpeed(Spell), GetSpellDelay(Spell));
			float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Engine::MouseObject, QChargeRange-100.f, GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
			if (HitChance > 0.5f)
			{
				if (strcmp(ChannelCheck, "XerathArcanopulseChargeUp") == NULL)
				{
					return Engine::ReleaseSpell(PredPos, Q);
				}
			}
		}
		GameObject* Q2_Target = TargetSelector::ComboTarget(Engine::pLocalPlayer->GetPosition(), QChargeRange, 1);
		if (Q2_Target)
		{
			Vector3 PredPos = Prediction::GetPredPos(Q2_Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
			float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Q2_Target, QChargeRange-100.f, GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
			if (HitChance > 0.5f)
			{
				if (strcmp(ChannelCheck, "XerathArcanopulseChargeUp") == NULL)
				{
					return Engine::ReleaseSpell(PredPos, Q);
				}
			}
		}
	}
	return 0;
}

int Xerath::Harrass() {
	return 0;
}

int Xerath::Laneclear() {
	return 0;
}

int Xerath::Lasthit() {
	return 0;
}

int Xerath::Rotation() {
	if (!Initialized)
	{
		Initialized = Initialize();
	}
	float RStartTime = Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(3)->GetStartTime();
	//std::cout << RStartTime << std::endl;
	if (Engine::getOrbMode() == Target_Combo)
	{
		if (RStartTime)
		{
			Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
			TargetMode Mode = Target_Combo;
			SpellSlotID Spell = R;
			DWORD mousecolor = 0x00808880;
			Engine::DrawCircle(&Engine::pMouse->MousePos, 500.f, &mousecolor, 0, 0, 0, 1.f);
			GameObject* Target = TargetSelector::GetTarget(Mode, Engine::pMouse->MousePos, 500.f, 1);
			if (Target)
			{
				Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
				return Engine::CastAimedSpell(PredPos, Spell);
			}
			return 1;
		}
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
