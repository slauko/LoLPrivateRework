#pragma once
#include "Viktor.h"
#include "ChampionIncludes.h"

float Viktor::QRange = 0.f;
float Viktor::WRange = 0.f;
float Viktor::ERange = 0.f;
float Viktor::RRange = 0.f;

float Viktor::QSpeed = HUGE_VALF;
float Viktor::WSpeed = HUGE_VALF;
float Viktor::ESpeed = HUGE_VALF;
float Viktor::RSpeed = HUGE_VALF;

float Viktor::QDelay = 0.f;
float Viktor::WDelay = 0.f;
float Viktor::EDelay = 0.f;
float Viktor::RDelay = 0.f;

bool Viktor::Initialized = false;
bool Viktor::Initialize() {
	QRange = 600.f;
	WRange = 800.f;
	ERange = 1000.f;
	RRange = 700.f;

	QSpeed = HUGE_VALF;
	WSpeed = HUGE_VALF;
	ESpeed = 1350.f;
	RSpeed = HUGE_VALF;

	QDelay = 0.25f;
	WDelay = 0.25f;
	EDelay = 0.f;
	RDelay = 0.75f;

	return true;
}

Vector3 Viktor::GetViktorEStartPos(GameObject* Target) {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	Vector3 TargetPos = Target->GetPosition();
	Vector3 totargetvec = Vector3(TargetPos.x - PlayerPos.x, TargetPos.y - PlayerPos.y, TargetPos.z - PlayerPos.z);
	float length = sqrt((totargetvec.x * totargetvec.x) + (totargetvec.y * totargetvec.y) + (totargetvec.z * totargetvec.z));
	Vector3 totargetvecnorm = Vector3(totargetvec.x / length, totargetvec.y / length, totargetvec.z / length);
	float mod = 500.f;
	Vector3 ViktorEStartPos = Vector3(PlayerPos.x + (totargetvecnorm.x * mod), PlayerPos.y + (totargetvecnorm.y  * mod), PlayerPos.z + (totargetvecnorm.z  * mod));
	return ViktorEStartPos;
}


int Viktor::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell))
		{
			GameObject* E_Target1 = TargetSelector::ComboTarget(Engine::pLocalPlayer->GetPosition(), ERange-500.f, 1);
			if (E_Target1)
			{
				std::list<GameObject*> E_Targets = TargetSelector::GetEnemiesInRange(E_Target1->GetPosition(), 1000.f);
				int ETargetCount = E_Targets.size();
				if (ETargetCount > 1) // sort if more then 1 target only
				{
					E_Targets.sort([](GameObject* f, GameObject* s) { return f->GetHealth() < s->GetHealth(); });
				}
				for (GameObject* Target : E_Targets)
				{
					if (Target == E_Target1)
					{
						continue;
					}
					if (Engine::GetDistance3D(Target->GetPosition(), E_Target1) > (700.f + Target->GetBoundingRadius() + E_Target1->GetBoundingRadius()))
					{
						continue;
					}
					if (E_Target1 && Target)
					{
						Vector3 EStartPos = Prediction::GetPredPos(E_Target1, HUGE_VALF, EDelay);
						Vector3 EEndPos = Prediction::TwoPointPrediction(EStartPos, Target, ESpeed, EDelay);
						Engine::CastSpell(Engine::pLocalPlayer->GetSpellbook(), Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(2), E, &EStartPos, &EEndPos, 0);
						return 1;
					}
				}
			}
			GameObject* E_Target2 = TargetSelector::ComboTarget(Engine::pLocalPlayer->GetPosition(), ERange, 1);
			if (E_Target2)
			{
				Vector3 EStartPos = GetViktorEStartPos(E_Target2);
				Vector3 EEndPos = Prediction::TwoPointPrediction(EStartPos, E_Target2, ESpeed, EDelay);
				Engine::CastSpell(Engine::pLocalPlayer->GetSpellbook(), Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(2), E, &EStartPos, &EEndPos, 0);
				return 1;
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
				BuffManager* BM = Target->GetBuffManager();
				if (BM->HasBuffType(BuffType::Slow) || BM->HasBuffType(BuffType::Snare) || BM->HasBuffType(BuffType::Stun) || 
					BM->HasBuffType(BuffType::Fear) || BM->HasBuffType(BuffType::Charm) || BM->HasBuffType(BuffType::Asleep) || 
					BM->HasBuffType(BuffType::Knockup) || BM->HasBuffType(BuffType::Grounded) || BM->HasBuffType(BuffType::Taunt))
				{
					Vector3 PredPos = Prediction::GetPredPos(Target, ESpeed, EDelay);
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

int Viktor::Harrass() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_Combo;
	if (Menu::UseE)
	{
		SpellSlotID Spell = E;
		if (Engine::SpellReady(Spell))
		{
			GameObject* E_Target1 = TargetSelector::ComboTarget(Engine::pLocalPlayer->GetPosition(), ERange - 500.f, 1);
			if (E_Target1)
			{
				std::list<GameObject*> E_Targets = TargetSelector::GetEnemiesInRange(E_Target1->GetPosition(), 1000.f);
				int ETargetCount = E_Targets.size();
				if (ETargetCount > 1) // sort if more then 1 target only
				{
					E_Targets.sort([](GameObject* f, GameObject* s) { return f->GetHealth() < s->GetHealth(); });
				}
				for (GameObject* Target : E_Targets)
				{
					if (Target == E_Target1)
					{
						continue;
					}
					if (Engine::GetDistance3D(Target->GetPosition(), E_Target1) > (700.f + Target->GetBoundingRadius() + E_Target1->GetBoundingRadius()))
					{
						continue;
					}
					if (E_Target1 && Target)
					{
						Vector3 EStartPos = Prediction::GetPredPos(E_Target1, HUGE_VALF, EDelay);
						Vector3 EEndPos = Prediction::TwoPointPrediction(EStartPos, Target, ESpeed, EDelay);
						Engine::CastSpell(Engine::pLocalPlayer->GetSpellbook(), Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(2), E, &EStartPos, &EEndPos, 0);
						return 1;
					}
				}
			}
			GameObject* E_Target2 = TargetSelector::ComboTarget(Engine::pLocalPlayer->GetPosition(), ERange, 1);
			if (E_Target2)
			{
				Vector3 EStartPos = GetViktorEStartPos(E_Target2);
				Vector3 EEndPos = Prediction::TwoPointPrediction(EStartPos, E_Target2, ESpeed, EDelay);
				Engine::CastSpell(Engine::pLocalPlayer->GetSpellbook(), Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(2), E, &EStartPos, &EEndPos, 0);
				return 1;
			}
		}
	}
	return 0;
}

int Viktor::Laneclear() {
	return 0;
}

int Viktor::Lasthit() {
	return 0;
}

int Viktor::Rotation() {
	if (!Initialized)
	{
		Initialized = Initialize();
	}
	//Engine::DEBUG_SHOWTARGETBUFFS(Engine::pLocalPlayer);
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
