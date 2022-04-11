#pragma once
#include "Yasuo.h"
#include "ChampionIncludes.h"
bool Engine::YasuoSelected = false;

Yasuo::WallMode Yasuo::WMode = Yasuo::Nothing;

float Yasuo::QRange = 0.f;
float Yasuo::WRange = 0.f;
float Yasuo::ERange = 0.f;
float Yasuo::RRange = 0.f;

float Yasuo::QSpeed = HUGE_VALF;
float Yasuo::WSpeed = HUGE_VALF;
float Yasuo::ESpeed = HUGE_VALF;
float Yasuo::RSpeed = HUGE_VALF;

float Yasuo::QDelay = 0.f;
float Yasuo::WDelay = 0.f;
float Yasuo::EDelay = 0.f;
float Yasuo::RDelay = 0.f;

bool Yasuo::Initialized = false;
bool Yasuo::Initialize() {
	Engine::YasuoSelected = true;

	QRange = 475.f;
	WRange = 900.f;
	ERange = 475.f;
	RRange = 25000.f;

	QSpeed = HUGE_VALF;
	WSpeed = HUGE_VALF;
	ESpeed = HUGE_VALF;
	RSpeed = HUGE_VALF;

	QDelay = 0.318f;
	WDelay = 0.4f;
	EDelay = 0.f;
	RDelay = 0.75f;

	return true;
}

float Yasuo::LastDash = 0.f;
int Yasuo::Combo() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	Vector3 TargetPos = Engine::pLocalPlayer->GetAIManager()->TargetPos();
	float QDashKnockRange = Engine::pLocalPlayer->GetAttackRange() - Engine::pLocalPlayer->GetBoundingRadius();
	TargetMode Mode = Target_Combo;
	bool IsDashing = Engine::pLocalPlayer->GetAIManager()->IsDashing();
	float Q2Speed = 1337.f;
	float Q2Range = 1100.f;
	if (IsDashing)
	{
		LastDash = *Engine::GameTime;
		PlayerPos = Engine::pLocalPlayer->GetAIManager()->TargetPos();
	}
	float DashTimer = *Engine::GameTime - LastDash;

	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			if (!IsDashing)
			{
				int YasuoQ2 = Engine::pLocalPlayer->GetBuffManager()->HasBuff("YasuoQ2");
				GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, Q2Range, 1);
				if (Target && YasuoQ2)
				{
					Vector3 PredPos = Prediction::GetPredPos(Target, Q2Speed, GetSpellDelay(Spell));
					float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, Q2Range, GetSpellSpeed(Spell), GetSpellDelay(Spell), 70, 0);
					if (HitChance > 0.337f)
					{
						return Engine::CastAimedSpell(PredPos, Spell);
					}
				}
				Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
				if (Target && !YasuoQ2)
				{
					Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
					float HitChance = Prediction::GetHitchance(PlayerPos, PredPos, Target, GetSpellRange(Spell), GetSpellSpeed(Spell), 0.2f, 70, 0);
					if (HitChance > 0.337f)
					{
						return Engine::CastAimedSpell(PredPos, Spell);
					}
				}
			}
			if (IsDashing)
			{
				int YasuoQ2 = Engine::pLocalPlayer->GetBuffManager()->HasBuff("YasuoQ2");
				GameObject* Target = TargetSelector::GetTarget(Mode, TargetPos, QDashKnockRange, 1);
				if (Target && YasuoQ2)
				{
					Vector3 PredPos = Prediction::GetPredPos(Target, Q2Speed, GetSpellDelay(Spell));
					float HitChance = Prediction::GetHitchance(TargetPos, PredPos, Target, QDashKnockRange, GetSpellSpeed(Spell), 0.2f, 70, 0);
					if (HitChance > 0.1337f)
					{
						return Engine::CastAimedSpell(PredPos, Spell);
					}
				}
				Target = TargetSelector::GetTarget(Mode, TargetPos, QDashKnockRange, 1);
				if (Target && !YasuoQ2)
				{
					Vector3 PredPos = Prediction::GetPredPos(Target, GetSpellSpeed(Spell), GetSpellDelay(Spell));
					float HitChance = Prediction::GetHitchance(TargetPos, PredPos, Target, QDashKnockRange, GetSpellSpeed(Spell), 0.2f, 70, 0);
					if (HitChance > 0.1337f)
					{
						return Engine::CastAimedSpell(PredPos, Spell);
					}
				}
			}
		}
	}
	return 0;
}

int Yasuo::Harrass() {
	return 0;
}

int Yasuo::Laneclear() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	TargetMode Mode = Target_LaneClear;
	bool IsDashing = Engine::pLocalPlayer->GetAIManager()->IsDashing();
	if (IsDashing)
	{
		LastDash = *Engine::GameTime;
		PlayerPos = Engine::pLocalPlayer->GetAIManager()->TargetPos();
	}
	float DashTimer = *Engine::GameTime - LastDash;

	if (Menu::UseQ)
	{
		SpellSlotID Spell = Q;
		if (Engine::SpellReady(Spell) && !Engine::BlockAA)
		{
			int YasuoQ2 = Engine::pLocalPlayer->GetBuffManager()->HasBuff("YasuoQ2");
			GameObject* Target = TargetSelector::GetTarget(Mode, PlayerPos, GetSpellRange(Spell), 1);
			if (Target && !YasuoQ2)
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
	return 0;
}

int Yasuo::Lasthit() {
	return 0;
}

GameObject* Yasuo::GetSpellMissile() {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	if (WMode == Nothing)
	{
		return NULL;
	}
	for (GameObject* Missile : TargetList::MissileList)
	{
		GameObject* source = Engine::pObjectManager->pObjectArray[Missile->GetSourceIndex()];
		if (!source)
		{
			continue;
		}
		if (source->GetTeam() == Engine::pLocalPlayer->GetTeam())
		{
			continue;
		}
		if (Engine::IsMinion(source))
		{
			continue;
		}
		//cout << source->GetName().c_str() << endl;
		//cout << Missile->GetName().c_str() << endl;
		for (auto _Spell : Engine::SpellDataBase.Spells)
		{
			if (!_strcmpi(_Spell.first.c_str(), Missile->GetName().c_str()))
			{
				SpellDataInfo* Spell = _Spell.second;
				if (Spell->type == linear)
				{
					if (WMode == CCOnly)
					{
						if (!Spell->cc)
						{
							continue;
						}
						Vector3 StartPos, EndPos;
						Vector3 StartScreen, EndScreen;
						Evade::CalcLinearMissileStartEndPos(Missile, Missile->GetMissileStartPos(), Missile->GetMissileEndPos(), Spell, StartPos, EndPos);

						if (Prediction::PointOnLineSegment3D(StartPos, EndPos, PlayerPos, Spell->radius + 100)) //If Player in Range of Skillshot
						{
							if (Spell->collision)
							{
								if (Prediction::EnemySpellWillCollideWith(Minion, StartPos, EndPos, Spell->radius))
								{
									if (!Prediction::EnemySpellWillCollideWith(Minion, StartPos, PlayerPos, Spell->radius))
									{
										return NULL;
									}
								}
								else {
									return Missile;
								}
							}
							else {
								return Missile;
							}
						}
					}
				}
			}
		}
	}
	return NULL;
}

int Yasuo::WallHandler() {
	if (Menu::UseW)
	{
		SpellSlotID Spell = W;
		if (Engine::SpellReady(Spell))
		{
			if (Evade::DZone == Evade::Inside)
			{
				GameObject* Missile = GetSpellMissile();
				if (Missile)
				{
					if (Engine::GetDistance3D(Missile->GetPosition(),Engine::pLocalPlayer->GetPosition()) < 300.f)
					{
						Vector3 WallPos = Missile->GetPosition();
						Engine::CastAimedSpell(WallPos, W);
					}
				}
			}
		}
	}
	return 0;
}

int Yasuo::Rotation() {
	if (!Initialized)
	{
		Initialized = Initialize();
	}
	if (Menu::UseW)
	{
		WMode = CCOnly;
	}
	if (Engine::getOrbMode() == Target_Combo)
	{
		WallHandler();
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
