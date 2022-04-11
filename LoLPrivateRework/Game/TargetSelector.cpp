#pragma once
#include "GameIncludes.h"

GameObject* TargetSelector::AntiGapCloseTarget(Vector3 from, float Range) { //still very simple WIP
	for (GameObject* Target : TargetList::ChampionList)
	{
		float distance1 = (float)sqrt(pow((from.x - Target->GetPosition().x), 2) + pow((from.z - Target->GetPosition().z), 2));
		float distance2 = (float)sqrt(pow((from.x - Target->GetAIManager()->TargetPos().x), 2) + pow((from.z - Target->GetAIManager()->TargetPos().z), 2));
		if (distance1 > Range + Engine::pLocalPlayer->GetBoundingRadius() + Target->GetBoundingRadius())
		{
			continue;
		}
		if (Target->GetTeam() == Engine::pLocalPlayer->GetTeam())
		{
			continue;
		}
		if (!Target->GetAIManager()->IsDashing())
		{
			continue;
		}
		if (distance2 > Range)
		{
			continue;
		}
		return Target;
	}
	return NULL;
}
GameObject* TargetSelector::ComboTarget(Vector3 from, float Range, int Prio) {
	if (Engine::MouseObject)
	{
		if (Engine::GetDistance3D(from, Engine::MouseObject) < Range + Engine::pLocalPlayer->GetBoundingRadius() + Engine::MouseObject->GetBoundingRadius())
		{
			if (Engine::IsTargetable(Engine::MouseObject))
			{
				return Engine::MouseObject;
			}
		}
	}
	if (TargetList::ChampionList.size() > 1) // sort if more then 1 target only
	{
		if (Prio == 1) // 1 = Lowest Health 
		{
			TargetList::ChampionList.sort([](GameObject* f, GameObject* s) { return f->GetHealth() < s->GetHealth(); });
		}
		if (Prio == 5) // 5 = LuluE
		{
			TargetList::ChampionList.sort([](GameObject* f, GameObject* s) { return f->GetBuffManager()->HasBuff("luluevision") > s->GetBuffManager()->HasBuff("luluevision"); });
		}
		if (Prio == 6) // 6 = DariusStacks
		{
			TargetList::ChampionList.sort([](GameObject* f, GameObject* s) { return f->GetHealth() < s->GetHealth(); });
			TargetList::ChampionList.sort([](GameObject* f, GameObject* s) { return f->GetBuffManager()->HasBuff("DariusHemo") > s->GetBuffManager()->HasBuff("DariusHemo"); });
		}
		if (Prio == 7) // 7 = TwitchEStacks
		{
			TargetList::ChampionList.sort([](GameObject* f, GameObject* s) {
				if (f->GetBuffManager()->HasBuff("TwitchDeadlyVenom"))
				{
					if (s->GetBuffManager()->HasBuff("TwitchDeadlyVenom"))
					{
						return f->GetBuffManager()->GetBuffEntryByName("TwitchDeadlyVenom")->GetBuffCountInt() > s->GetBuffManager()->GetBuffEntryByName("TwitchDeadlyVenom")->GetBuffCountInt();
					}
					return true;
				}
				return true;
			});
		}
		if (Prio == 8) // 8 = KalistaEStacks
		{
			TargetList::ChampionList.sort([](GameObject* f, GameObject* s) { return f->GetBuffManager()->HasBuff("kalistaexpungemarker") > s->GetBuffManager()->HasBuff("kalistaexpungemarker"); });
		}
	}
	for (GameObject* Target : TargetList::ChampionList)
	{
		if (Engine::GetDistance3D(from, Target) > Range + Engine::pLocalPlayer->GetBoundingRadius() + Target->GetBoundingRadius())
		{
			continue;
		}
		if (Target->GetTeam() == Engine::pLocalPlayer->GetTeam())
		{
			continue;
		}
		return Target;
	}
	return NULL;
}
GameObject* TargetSelector::FriendlyTarget(Vector3 from, float Range, int Prio) {
	if (TargetList::ChampionList.size() > 1) // sort if more then 1 target only
	{
		if (Prio == 1) // 1 = Lowest Health 
		{
			TargetList::ChampionList.sort([](GameObject* f, GameObject* s) { return f->GetHealth() < s->GetHealth(); });
		}
		if (Prio == 2) // 2 = Highest AtkRange 
		{
			TargetList::ChampionList.sort([](GameObject* f, GameObject* s) { return f->GetAttackRange() > s->GetAttackRange(); });
		}
		if (Prio == 5) // 5 = LuluE
		{
			TargetList::ChampionList.sort([](GameObject* f, GameObject* s) { return f->GetBuffManager()->HasBuff("lulufaerieattackaid") > s->GetBuffManager()->HasBuff("lulufaerieattackaid"); });
		}
		if (Prio == 6) // 6 = DariusStacks
		{
			TargetList::ChampionList.sort([](GameObject* f, GameObject* s) { return f->GetBuffManager()->HasBuff("DariusHemo") > s->GetBuffManager()->HasBuff("DariusHemo"); });
		}
		if (Prio == 7) // 7 = TwitchEStacks
		{
			TargetList::ChampionList.sort([](GameObject* f, GameObject* s) {
				if (f->GetBuffManager()->HasBuff("TwitchDeadlyVenom"))
				{
					if (s->GetBuffManager()->HasBuff("TwitchDeadlyVenom"))
					{
						return f->GetBuffManager()->GetBuffEntryByName("TwitchDeadlyVenom")->GetBuffCountInt() > s->GetBuffManager()->GetBuffEntryByName("TwitchDeadlyVenom")->GetBuffCountInt();
					}
					return true;
				}
				return true;
			});
		}
	}
	for (GameObject* Target : TargetList::ChampionList)
	{
		if (Engine::GetDistance3D(from, Target) > Range + Engine::pLocalPlayer->GetBoundingRadius() + Target->GetBoundingRadius())
		{
			continue;
		}
		if (Target->GetTeam() != Engine::pLocalPlayer->GetTeam())
		{
			continue;
		}
		if (!strcmp(Target->GetName().c_str(),Engine::pLocalPlayer->GetName().c_str()))
		{
			continue;
		}
		return Target;
	}
	return NULL;
}
GameObject* TargetSelector::HarrassTarget(Vector3 from, float Range) {
	for (GameObject* Minion : TargetList::MinionList)
	{
		if (Engine::GetDistance3D(from, Minion) > Range + Engine::pLocalPlayer->GetBoundingRadius() + Minion->GetBoundingRadius())
		{
			continue;
		}
		if (Minion->GetTeam() == Engine::pLocalPlayer->GetTeam())
		{
			continue;
		}
		if (!Engine::canLasthit(Minion))
		{
			continue;
		}
		return Minion;
	}
	if (Engine::MouseObject)
	{
		if (Engine::GetDistance3D(from, Engine::MouseObject) < Range + Engine::pLocalPlayer->GetBoundingRadius() + Engine::MouseObject->GetBoundingRadius())
		{
			if (Engine::IsTargetable(Engine::MouseObject))
			{
				return Engine::MouseObject;
			}
		}
	}
	if (TargetList::ChampionList.size() > 1) // sort if more then 1 target only
	{
		TargetList::ChampionList.sort([](GameObject* f, GameObject* s) { return f->GetHealth() < s->GetHealth(); });
	}
	for (GameObject* Target : TargetList::ChampionList)
	{
		if (Engine::GetDistance3D(from, Target) > Range + Engine::pLocalPlayer->GetBoundingRadius() + Target->GetBoundingRadius())
		{
			continue;
		}
		if (Target->GetTeam() == Engine::pLocalPlayer->GetTeam())
		{
			continue;
		}
		return Target;
	}
	return NULL;
}
GameObject* TargetSelector::LaneclearTarget(Vector3 from, float Range) {
	if (TargetList::MinionList.size() > 1) // sort if more then 1 target only
	{
		TargetList::MinionList.sort([](GameObject* f, GameObject* s) { return f->GetHealth() < s->GetHealth(); });
	}
	for (GameObject* Minion : TargetList::MinionList)
	{
		if (Engine::GetDistance3D(from, Minion) > Range + Engine::pLocalPlayer->GetBoundingRadius() + Minion->GetBoundingRadius())
		{
			continue;
		}
		if (Minion->GetTeam() == Engine::pLocalPlayer->GetTeam())
		{
			continue;
		}
		//if (Engine::IsAlreadyDead(Minion))
		//{
		//	continue;
		//}
		if (!Engine::isBigJungle(Minion))
		{
			continue;
		}
		return Minion;
	}
	for (GameObject* Minion : TargetList::MinionList)
	{
		if (Engine::GetDistance3D(from, Minion) > Range + Engine::pLocalPlayer->GetBoundingRadius() + Minion->GetBoundingRadius())
		{
			continue;
		}
		if (Minion->GetTeam() == Engine::pLocalPlayer->GetTeam())
		{
			continue;
		}
		//if (Engine::IsAlreadyDead(Minion))
		//{
		//	continue;
		//}
		return Minion;
	}
	return NULL;
}
GameObject* TargetSelector::LasthitTarget(Vector3 from , float Range) {
	for (GameObject* Minion : TargetList::MinionList)
	{
		if (Engine::GetDistance3D(from, Minion) > Range + Engine::pLocalPlayer->GetBoundingRadius() + Minion->GetBoundingRadius())
		{
			continue;
		}
		if (Minion->GetTeam() == Engine::pLocalPlayer->GetTeam())
		{
			continue;
		}
		if (!Engine::canLasthit(Minion))
		{
			continue;
		}
		return Minion;
	}
	return NULL;
}
GameObject* TargetSelector::SmiteTarget(float Range) {
	for (GameObject* Minion : TargetList::MinionList)
	{
		if (Engine::GetDistance3D(Engine::pLocalPlayer->GetPosition(), Minion) > Range + Engine::pLocalPlayer->GetBoundingRadius() + Minion->GetBoundingRadius())
		{
			continue;
		}
		if (Minion->GetTeam() == Engine::pLocalPlayer->GetTeam())
		{
			continue;
		}
		if (!Engine::isBigJungle(Minion))
		{
			continue;
		}
		return Minion;
	}
	return ComboTarget(Engine::pLocalPlayer->GetPosition(), Range, 1);
}
std::list<GameObject*> TargetSelector::GetEnemiesInRange(Vector3 from, float Range) {
	std::list<GameObject*> EnemyList;
	for (GameObject* Target : TargetList::ChampionList)
	{
		if (Target->GetTeam() == Engine::pLocalPlayer->GetTeam())
		{
			continue;
		}
		if (Engine::GetDistance3D(from,Target) > Range)
		{
			continue;
		}
		EnemyList.push_front(Target);
	}
	return EnemyList;
}
std::list<GameObject*> TargetSelector::GetAlliesInRange(Vector3 from, float Range) {
	std::list<GameObject*> AllyList;
	for (GameObject* Target : TargetList::ChampionList)
	{
		if (Target->GetTeam() != Engine::pLocalPlayer->GetTeam())
		{
			continue;
		}
		if (Engine::GetDistance3D(from, Target) > Range)
		{
			continue;
		}
		AllyList.push_front(Target);
	}
	return AllyList;
}

GameObject* TargetSelector::GetShieldTarget(float ShieldRange, float healthpercent, bool useforminionattacks){
	std::list<GameObject*> ShieldTargets = TargetSelector::GetAlliesInRange(Engine::pLocalPlayer->GetPosition(), ShieldRange);
	if (ShieldTargets.size() > 1) // sort if more then 1 target only
	{
		ShieldTargets.sort([](GameObject* f, GameObject* s) { return f->GetHealth() < s->GetHealth(); });
	}
	for (GameObject* Friend : ShieldTargets)
	{
		float FriendHealthPercent = Friend->GetHealth() / Friend->GetMaxHealth();
		if (FriendHealthPercent > healthpercent)
		{
			continue;
		}
		for (GameObject* Missile : TargetList::MissileList)
		{
			GameObject* source = Engine::pObjectManager->pObjectArray[Missile->GetSourceIndex()];
			GameObject* target = Engine::pObjectManager->pObjectArray[Missile->GetTargetID()];
			//cout << Missile->GetTargetID() << endl;
			if (!useforminionattacks)
			{
				if (Engine::IsMinion(source))
				{
					continue; //ignore minion attacks
				}
			}
			if (source && Missile->GetTargetID()) //if targeted
			{
				//cout << "Target: " << target->GetName().c_str() << endl;
				if (source->GetTeam() == Engine::pLocalPlayer->GetTeam())
				{
					continue;
				}
				if (target != Friend)
				{
					continue;
				}
				if (!(Engine::GetDistance3D(Missile->GetPosition(), Friend) < 200.f))
				{
					continue;
				}
				return Friend;
			}
			if (source && !Missile->GetTargetID()) // if skillshot
			{
				SpellDataInfo* Spell = NULL;
				for (auto _Spell : Engine::SpellDataBase.Spells)
				{
					if (!_strcmpi(_Spell.first.c_str(), Missile->GetName().c_str()))
					{
						//MessageBox(Menu::hwnd, "Pause!", "Debug", MB_OK);
						Spell = _Spell.second;
					}
				}
				if (Spell)
				{
					Vector3 StartPos = Missile->GetMissileStartPos();
					Vector3 TargetPos = Missile->GetMissileEndPos();
					Vector3 totargetvec = Vector3(TargetPos.x - StartPos.x, TargetPos.y - StartPos.y, TargetPos.z - StartPos.z);

					float length = sqrt((totargetvec.x * totargetvec.x) + (totargetvec.y * totargetvec.y) + (totargetvec.z * totargetvec.z));
					Vector3 totargetvecnorm = Vector3(totargetvec.x / length, totargetvec.y / length, totargetvec.z / length);
					float mod = Spell->range;
					Vector3 EndPos = Vector3(StartPos.x + (totargetvecnorm.x*mod), StartPos.y + (totargetvecnorm.y*mod), StartPos.z + (totargetvecnorm.z*mod));
					//DWORD color = 0x00FFFFFF;
				//Engine::DrawCircle(&EndPos, 70.f, &color, 0, 0, 0, 1.f);
				//Engine::DrawCircle(&Missile->GetPosition(), 70.f, &color, 0, 0, 0, 1.f);

				//cout << hex << (DWORD)Missile << endl;
				//MessageBox(Menu::hwnd, "Pause!", "Debug", MB_OK);


					if (source->GetTeam() == Engine::pLocalPlayer->GetTeam())
					{
						continue;
					}
					if (!Prediction::EnemySpellWillCollideWithFriend(Friend, StartPos, EndPos, Spell->radius))
					{
						continue;
					}
					if (Spell->collision)
					{
						if (Prediction::EnemySpellWillCollide(Friend,Minion,StartPos,Spell->radius))
						{
							continue;
						}
					}
					if (!(Engine::GetDistance3D(Missile->GetPosition(), Friend) < 300.f))
					{
						continue;
					}
					return Friend;
				}
			}
		}
		std::list<GameObject*>MeleeTargets = TargetSelector::GetEnemiesInRange(Friend->GetPosition(), 300.f);
		for (GameObject* Target : MeleeTargets)
		{
			if (Target->GetAttackRange() > 300.f)
			{
				continue;
			}
			if (Engine::GetDistance3D(Friend->GetPosition(), Target) < Target->GetAttackRange())
			{
				return Friend;
			}
		}
	}
	return NULL;
}

GameObject* TargetSelector::GetTarget(TargetMode Mode, Vector3 from, float Range, int Prio) {
	if (Mode == Target_Combo)
	{
		return ComboTarget(from, Range, Prio);
	}
	if (Mode == Target_Harrass)
	{
		return HarrassTarget(from, Range);
	}
	if (Mode == Target_LaneClear)
	{
		return LaneclearTarget(from, Range);
	}
	if (Mode == Target_LastHit)
	{
		return LasthitTarget(from, Range);
	}
	if (Mode == Target_Smite)
	{
		return SmiteTarget(Range);
	}
	return NULL;
}
