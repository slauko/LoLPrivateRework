#pragma once
#include "GameIncludes.h"

float Prediction::DistanceToLine2D(Vector3 line_start, Vector3 line_end, Vector3 point)
{
	float normalLength = _hypotf(line_start.x - line_end.x, line_start.y - line_end.y);
	float distance = (float)((point.x - line_end.x) * (line_start.y - line_end.y) - (point.y - line_end.y) * (line_start.x - line_end.x)) / normalLength;
	return abs(distance);
}
float Prediction::DistanceToLine3D(Vector3 line_start, Vector3 line_end, Vector3 point)
{
	float normalLength = _hypotf(line_start.x - line_end.x, line_start.z - line_end.z);
	float distance = (float)((point.x - line_end.x) * (line_start.z - line_end.z) - (point.z - line_end.z) * (line_start.x - line_end.x)) / normalLength;
	return abs(distance);
}
Vector3 Prediction::GetShortestPointToLine3D(Vector3 LineStart,Vector3 LineEnd, Vector3 Point) {
	float xDiff = LineEnd.x - LineStart.x, zDiff = LineEnd.z - LineStart.z;
	float lenLine2 = xDiff * xDiff + zDiff * zDiff;
	float partDiv = ((Point.x - LineStart.x) * xDiff + (Point.z - LineStart.z) * zDiff) / lenLine2;
	float x = (LineStart.x + partDiv * (LineEnd.x - LineStart.x));
	float z = (LineStart.z + partDiv * (LineEnd.z - LineStart.z));
	return Vector3(x, Point.y, z);
}
bool Prediction::LineIntersection2D(Vector3 line1_start, Vector3 line1_end, Vector3 line2_start, Vector3 line2_end, float *i_x, float *i_y)
{
	float s1_x, s1_y, s2_x, s2_y;
	s1_x = line1_end.x - line1_start.x;     s1_y = line1_end.y - line1_start.y;
	s2_x = line2_end.x - line2_start.x;     s2_y = line2_end.y - line2_start.y;

	float s, t;
	s = (-s1_y * (line1_start.x - line2_start.x) + s1_x * (line1_start.y - line2_start.y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (line1_start.y - line2_start.y) - s2_y * (line1_start.x - line2_start.x)) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		// Collision detected
		if (i_x != NULL)
			*i_x = line1_start.x + (t * s1_x);
		if (i_y != NULL)
			*i_y = line1_start.y + (t * s1_y);
		return true;
	}

	return false; // No collision
}

bool Prediction::LineIntersection3D(Vector3 line1_start, Vector3 line1_end, Vector3 line2_start, Vector3 line2_end, Vector3 &I_Point)
{
	float s1_x, s1_z, s2_x, s2_z;
	s1_x = line1_end.x - line1_start.x;     s1_z = line1_end.z - line1_start.z;
	s2_x = line2_end.x - line2_start.x;     s2_z = line2_end.z - line2_start.z;

	float s, t;
	s = (-s1_z * (line1_start.x - line2_start.x) + s1_x * (line1_start.z - line2_start.z)) / (-s2_x * s1_z + s1_x * s2_z);
	t = (s2_x * (line1_start.z - line2_start.z) - s2_z * (line1_start.x - line2_start.x)) / (-s2_x * s1_z + s1_x * s2_z);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		// Collision detected
		Vector3 _I_Point = Vector3(line1_start.x + (t * s1_x), line1_start.y, line1_start.z + (t * s1_z));
		I_Point = _I_Point;
		return true;
	}
	return false; // No collision
}
bool Prediction::PointOnLineSegment(Vector3 pt1, Vector3 pt2, Vector3 pt, float epsilon = 0.001f)
{
	if (pt.x - std::fmax(pt1.x, pt2.x) > epsilon ||
		std::fmin(pt1.x, pt2.x) - pt.x > epsilon ||
		pt.y - std::fmax(pt1.y, pt2.y) > epsilon ||
		std::fmin(pt1.y, pt2.y) - pt.y > epsilon)
		return false;

	if (abs(pt2.x - pt1.x) < epsilon)
		return abs(pt1.x - pt.x) < epsilon || abs(pt2.x - pt.x) < epsilon;
	if (abs(pt2.y - pt1.y) < epsilon)
		return abs(pt1.y - pt.y) < epsilon || abs(pt2.y - pt.y) < epsilon;

	float x = pt1.x + (pt.y - pt1.y) * (pt2.x - pt1.x) / (pt2.y - pt1.y);
	float y = pt1.y + (pt.x - pt1.x) * (pt2.y - pt1.y) / (pt2.x - pt1.x);

	return abs(pt.x - x) < epsilon || abs(pt.y - y) < epsilon;
}
bool Prediction::PointOnLineSegment3D(Vector3 pt1, Vector3 pt2, Vector3 pt, float epsilon = 0.001f)
{
	if (pt.x - std::fmax(pt1.x, pt2.x) > epsilon ||
		std::fmin(pt1.x, pt2.x) - pt.x > epsilon ||
		pt.z - std::fmax(pt1.z, pt2.z) > epsilon ||
		std::fmin(pt1.z, pt2.z) - pt.z > epsilon)
		return false;

	if (abs(pt2.x - pt1.x) < epsilon)
		return abs(pt1.x - pt.x) < epsilon || abs(pt2.x - pt.x) < epsilon;
	if (abs(pt2.z - pt1.z) < epsilon)
		return abs(pt1.z - pt.z) < epsilon || abs(pt2.z - pt.z) < epsilon;

	float x = pt1.x + (pt.z - pt1.z) * (pt2.x - pt1.x) / (pt2.z - pt1.z);
	float z = pt1.z + (pt.x - pt1.x) * (pt2.z - pt1.z) / (pt2.x - pt1.x);

	return abs(pt.x - x) < epsilon || abs(pt.z - z) < epsilon;
}

bool Prediction::IsCollisioned(CollisionType type, Vector3 vec, float radius)
{
	auto local = Engine::pLocalPlayer;
	switch (type)
	{
	case Minion:
	{
		for (GameObject* minion : TargetList::MinionList)
		{
			auto base = minion;
			if (base->GetTeam() == Engine::pLocalPlayer->GetTeam())
			{
				continue;
			}
			auto basecord = base->GetPosition();
			Vector3 pt1, pt2, pt;
			if (!Engine::World2Screen(&basecord, &pt))
				continue;

			Engine::World2Screen(&local->GetPosition(), &pt1);
			Engine::World2Screen(&vec, &pt2);
			if (PointOnLineSegment(pt1, pt2, pt, radius))
			{
				return true;
			}
		}
		break;
	}
	case Champion:
	{
		for (GameObject* champion : TargetList::ChampionList)
		{
			auto base = champion;
			if (base->GetTeam() == Engine::pLocalPlayer->GetTeam())
			{
				continue;
			}
			auto basecord = base->GetPosition();
			Vector3 pt1, pt2, pt;
			if (!Engine::World2Screen(&basecord, &pt))
				continue;

			Engine::World2Screen(&local->GetPosition(), &pt1);
			Engine::World2Screen(&vec, &pt2);
			if (PointOnLineSegment(pt1, pt2, pt, radius))
			{
				return true;
			}
		}
		break;
	}
	}
	return false;
}

bool Prediction::IsCollisioned(CollisionType type, Vector3 StartPos, Vector3 EndPos, float radius)
{
	auto local = Engine::pLocalPlayer;
	switch (type)
	{
	case Minion:
	{
		for (GameObject* minion : TargetList::MinionList)
		{
			auto base = minion;
			if (base->GetTeam() == Engine::pLocalPlayer->GetTeam())
			{
				continue;
			}
			auto basecord = base->GetPosition();
			if (PointOnLineSegment3D(StartPos, EndPos, basecord, radius))
			{
				return true;
			}
		}
		break;
	}
	case Champion:
	{
		for (GameObject* champion : TargetList::ChampionList)
		{
			auto base = champion;
			if (base->GetTeam() == Engine::pLocalPlayer->GetTeam())
			{
				continue;
			}
			auto basecord = base->GetPosition();
			if (PointOnLineSegment3D(StartPos, EndPos, basecord, radius))
			{
				return true;
			}
		}
		break;
	}
	}
	return false;
}

bool Prediction::EnemySpellWillCollideWith(CollisionType type, Vector3 StartPos, Vector3 EndPos, float radius)
{
	switch (type)
	{
	case Minion:
	{
		for (GameObject* minion : TargetList::MinionList)
		{
			auto base = minion;
			if (base->GetTeam() != Engine::pLocalPlayer->GetTeam())
			{
				continue;
			}

			if (PointOnLineSegment3D(StartPos, EndPos, base->GetPosition(), radius))
			{
				return true;
			}
		}
		break;
	}
	case Champion:
	{
		for (GameObject* champion : TargetList::ChampionList)
		{
			auto base = champion;
			if (base->GetTeam() != Engine::pLocalPlayer->GetTeam())
			{
				continue;
			}

			if (PointOnLineSegment3D(StartPos, EndPos, base->GetPosition(), radius))
			{
				return true;
			}
		}
		break;
	}
	}
	return false;
}
bool Prediction::EnemySpellWillCollide(GameObject* Target, CollisionType type, Vector3 vec, float radius)
{
	auto local = Target;
	switch (type)
	{
	case Minion:
	{
		for (GameObject* minion : TargetList::MinionList)
		{
			auto base = minion;
			if (base->GetTeam() != Engine::pLocalPlayer->GetTeam())
			{
				continue;
			}
			auto basecord = base->GetPosition();
			Vector3 pt1, pt2, pt;
			if (!Engine::World2Screen(&basecord, &pt))
				continue;

			Engine::World2Screen(&local->GetPosition(), &pt1);
			Engine::World2Screen(&vec, &pt2);
			if (PointOnLineSegment(pt1, pt2, pt, radius))
			{
				return true;
			}
		}
		break;
	}
	case Champion:
	{
		for (GameObject* champion : TargetList::ChampionList)
		{
			auto base = champion;
			if (base->GetTeam() != Engine::pLocalPlayer->GetTeam())
			{
				continue;
			}
			auto basecord = base->GetPosition();
			Vector3 pt1, pt2, pt;
			if (!Engine::World2Screen(&basecord, &pt))
				continue;

			Engine::World2Screen(&local->GetPosition(), &pt1);
			Engine::World2Screen(&vec, &pt2);
			if (PointOnLineSegment(pt1, pt2, pt, radius))
			{
				return true;
			}
		}
		break;
	}
	}
	return false;
}

bool Prediction::EnemySpellWillCollideWithMe(GameObject* Target, Vector3 vec, float radius)
{
	auto local = Target;
	auto base = Engine::pLocalPlayer;
	auto basecord = base->GetPosition();
	Vector3 pt1, pt2, pt;
	
	Engine::World2Screen(&basecord, &pt);
	Engine::World2Screen(&local->GetPosition(), &pt1);
	Engine::World2Screen(&vec, &pt2);
	if (PointOnLineSegment(pt1, pt2, pt, radius))
	{
		return true;
	}
	return false;
}

bool Prediction::EnemySpellWillCollideWithFriend(GameObject* Friend, Vector3 StartPos, Vector3 EndPos, float radius)
{
	if (PointOnLineSegment3D(StartPos,EndPos,Friend->GetPosition(), radius))
	{
		return true;
	}
	return false;
}
bool Prediction::IsAttackingEnemy(GameObject* Target) {
	for (GameObject* Enemy : TargetList::ChampionList)
	{
		if (Enemy->GetTeam() == Target->GetTeam())
		{
			continue;
		}
		if (Target->GetAttackRange() < 300.f)
		{
			if (Engine::GetDistance3D(Enemy->GetPosition(),Target) < Target->GetAttackRange())
			{
				if (Engine::pLocalPlayer->GetSpellbook()->GetActiveSpellEntry())
				{
					if (Engine::pLocalPlayer->GetSpellbook()->GetActiveSpellEntry()->GetActiveSpellInfo())
					{
						const char* AttackName = Engine::pLocalPlayer->GetSpellbook()->GetActiveSpellEntry()->GetActiveSpellInfo()->GetSpellName().c_str();
						if (strstr(AttackName, "Attack"))
						{
							return true;
						}
						if (Engine::IsAutoAttack(AttackName)) {
							return true;
						}
					}
				}
			}
		}
		for (GameObject* Missile : TargetList::MissileList)
		{
			//cout << Missile->GetSourceIndex() << " : "; 
			if (!strstr(Missile->GetName().c_str(), "Attack"))
			{
				continue;
			}
			GameObject* source = Engine::pObjectManager->pObjectArray[Missile->GetSourceIndex()];
			if (source == Target)
			{
				//cout << source->GetName().c_str()<< " : ";
				GameObject* target = Engine::pObjectManager->pObjectArray[Missile->GetTargetID()];
				if (Engine::IsHero(target))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Prediction::WallBetween(Vector3 StartPos, Vector3 EndPos, float radius) {
	Vector3 toendpos = Vector3(EndPos.x - StartPos.x, EndPos.y - StartPos.y, EndPos.z - StartPos.z);
	float length = sqrt((toendpos.x * toendpos.x) + (toendpos.y * toendpos.y) + (toendpos.z * toendpos.z));
	Vector3 toendposnorm = Vector3(toendpos.x / length, toendpos.y / length, toendpos.z / length);

	for (size_t mod = 1; mod < length; mod++)
	{
		Vector3 predpos = Vector3(StartPos.x + (toendposnorm.x*mod), StartPos.y + (toendposnorm.y*mod), StartPos.z + (toendposnorm.z*mod));
		if (!Engine::IsWall(&predpos, 0))
		{
			Vector3 pt1, pt2, pt;
			Engine::World2Screen(&predpos, &pt);
			Engine::World2Screen(&StartPos, &pt1);
			Engine::World2Screen(&EndPos, &pt2);
			if (PointOnLineSegment(pt1, pt2, pt, radius))
			{
				//DWORD wallcolor = 0x0000FF00;
				//Engine::DrawCircle(&predpos, radius, &wallcolor, 0, 0, 0, 1.f);
				return true;
			}
		}
	}
	return false;
}
bool Prediction::IsImmobilized(GameObject* Target) {
	BuffManager* TargetBM = Target->GetBuffManager();
	if (TargetBM->HasBuffType(BuffType::Snare) || 
		TargetBM->HasBuffType(BuffType::Stun) || 
		TargetBM->HasBuffType(BuffType::Fear) || 
		TargetBM->HasBuffType(BuffType::Charm) || 
		TargetBM->HasBuffType(BuffType::Asleep) || 
		TargetBM->HasBuffType(BuffType::Knockup) || 
		TargetBM->HasBuffType(BuffType::Taunt))
	{
		return true;
	}
	return false;
}
Vector3 Prediction::GetPredPos(GameObject* Target, float misslespeed, float delay) {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	Vector3 TargetPos = Target->GetPosition();
	//---------------------------------------
	int NavPoints = 0;
	float PathDist = 0.f;
	Vector3* NavBegin = Target->GetAIManager()->GetNavBegin();
	Vector3* NavEnd = Target->GetAIManager()->GetNavEnd();

	Vector3 NextNavPoint = Target->GetAIManager()->TargetPos();
	for (Vector3* Path = NavBegin; Path < NavEnd; Path++)
	{
		Vector3* Current = Path;
		Vector3* Next = Path+1;
		if (Next != NavEnd)
		{
			PathDist += Engine::GetDistance3D(*Current, *Next);
			if (PointOnLineSegment3D(*Current, *Next, TargetPos,30.f))
			{
				NextNavPoint = *Next;
			}
		}
		NavPoints++;
	}
	if (NavPoints < 3)
	{
		NextNavPoint = Target->GetAIManager()->TargetPos();
	}
	//----------------------------------------

	//if (Target->GetAIManager()->IsDashing())
	//{
	//	return Target->GetAIManager()->TargetPos();
	//}
	float distancetoplayer = sqrt(pow((PlayerPos.x - TargetPos.x), 2) + pow((PlayerPos.y - TargetPos.y), 2) + pow((PlayerPos.z - TargetPos.z), 2));
	float movespeed = Target->GetMoveSpeed();

	Vector3 movetovector = Vector3(NextNavPoint.x - TargetPos.x, NextNavPoint.y - TargetPos.y, NextNavPoint.z - TargetPos.z);
	float length = sqrt((movetovector.x * movetovector.x) + (movetovector.y * movetovector.y) + (movetovector.z * movetovector.z));

	float Bound = Target->GetBoundingRadius();
	float mod = ((movespeed * (delay + (distancetoplayer / misslespeed))) - Bound);

	//DWORD colorself = 0x00A08080;
	//Engine::DrawCircle(&NextNavPoint,65.f,&colorself,0,0,0,1);
	//std::cout << NavPoints << std::endl;
	
	if (length > 0.f)
	{
		Vector3 movetovectornorm = Vector3(movetovector.x / length, movetovector.y / length, movetovector.z / length);
		Vector3 predpos = Vector3(TargetPos.x + (movetovectornorm.x*mod), TargetPos.y + (movetovectornorm.y*mod), TargetPos.z + (movetovectornorm.z*mod));
		float distancetopred = sqrt(pow((TargetPos.x - predpos.x), 2) + pow((TargetPos.y - predpos.y), 2) + pow((TargetPos.z - predpos.z), 2));
		float distancetotargetposto = sqrt(pow((TargetPos.x - NextNavPoint.x), 2) + pow((TargetPos.y - NextNavPoint.y), 2) + pow((TargetPos.z - NextNavPoint.z), 2));
		if (distancetopred > distancetotargetposto)
		{
			return NextNavPoint;
		}
		return predpos;
	}
	else {
		return TargetPos;
	}
}
Vector3 Prediction::TwoPointPrediction(GameObject* Origin, GameObject* Target, float misslespeed, float delay) {
	Vector3 PlayerPos = Origin->GetPosition();
	Vector3 TargetPos = Target->GetPosition();
	//---------------------------------------
	int NavPoints = 0;
	float PathDist = 0.f;
	Vector3* NavBegin = Target->GetAIManager()->GetNavBegin();
	Vector3* NavEnd = Target->GetAIManager()->GetNavEnd();

	Vector3 NextNavPoint = Target->GetAIManager()->TargetPos();
	for (Vector3* Path = NavBegin; Path < NavEnd; Path++)
	{
		Vector3* Current = Path;
		Vector3* Next = Path + 1;
		if (Next != NavEnd)
		{
			PathDist += Engine::GetDistance3D(*Current, *Next);
			if (PointOnLineSegment3D(*Current, *Next, TargetPos, 10.f))
			{
				NextNavPoint = *Next;
			}
		}
		NavPoints++;
	}
	//----------------------------------------

	if (Target->GetAIManager()->IsDashing())
	{
		return Target->GetAIManager()->TargetPos();
	}
	float distancetoplayer = sqrt(pow((PlayerPos.x - TargetPos.x), 2) + pow((PlayerPos.y - TargetPos.y), 2) + pow((PlayerPos.z - TargetPos.z), 2));
	float movespeed = Target->GetMoveSpeed();

	Vector3 movetovector = Vector3(NextNavPoint.x - TargetPos.x, NextNavPoint.y - TargetPos.y, NextNavPoint.z - TargetPos.z);
	float length = sqrt((movetovector.x * movetovector.x) + (movetovector.y * movetovector.y) + (movetovector.z * movetovector.z));

	float Bound = Target->GetBoundingRadius();
	float mod = (movespeed * (delay + (distancetoplayer / misslespeed))) - Bound;

	if (length > 0.f)
	{
		Vector3 movetovectornorm = Vector3(movetovector.x / length, movetovector.y / length, movetovector.z / length);
		Vector3 predpos = Vector3(TargetPos.x + (movetovectornorm.x*mod), TargetPos.y + (movetovectornorm.y*mod), TargetPos.z + (movetovectornorm.z*mod));
		float distancetopred = sqrt(pow((TargetPos.x - predpos.x), 2) + pow((TargetPos.y - predpos.y), 2) + pow((TargetPos.z - predpos.z), 2));
		float distancetotargetposto = sqrt(pow((TargetPos.x - NextNavPoint.x), 2) + pow((TargetPos.y - NextNavPoint.y), 2) + pow((TargetPos.z - NextNavPoint.z), 2));
		if (distancetopred > distancetotargetposto)
		{
			return NextNavPoint;
		}
		return predpos;
	}
	else {
		return TargetPos;
	}
}
Vector3 Prediction::TwoPointPrediction(Vector3 Origin, GameObject* Target, float misslespeed, float delay) {
	Vector3 PlayerPos = Origin;
	Vector3 TargetPos = Target->GetPosition();
	//---------------------------------------
	int NavPoints = 0;
	float PathDist = 0.f;
	Vector3* NavBegin = Target->GetAIManager()->GetNavBegin();
	Vector3* NavEnd = Target->GetAIManager()->GetNavEnd();

	Vector3 NextNavPoint = Target->GetAIManager()->TargetPos();
	for (Vector3* Path = NavBegin; Path < NavEnd; Path++)
	{
		Vector3* Current = Path;
		Vector3* Next = Path + 1;
		if (Next != NavEnd)
		{
			PathDist += Engine::GetDistance3D(*Current, *Next);
			if (PointOnLineSegment3D(*Current, *Next, TargetPos, 10.f))
			{
				NextNavPoint = *Next;
			}
		}
		NavPoints++;
	}
	//----------------------------------------

	if (Target->GetAIManager()->IsDashing())
	{
		return Target->GetAIManager()->TargetPos();
	}
	float distancetoplayer = sqrt(pow((PlayerPos.x - TargetPos.x), 2) + pow((PlayerPos.y - TargetPos.y), 2) + pow((PlayerPos.z - TargetPos.z), 2));
	float movespeed = Target->GetMoveSpeed();

	Vector3 movetovector = Vector3(NextNavPoint.x - TargetPos.x, NextNavPoint.y - TargetPos.y, NextNavPoint.z - TargetPos.z);
	float length = sqrt((movetovector.x * movetovector.x) + (movetovector.y * movetovector.y) + (movetovector.z * movetovector.z));

	float Bound = Target->GetBoundingRadius();
	float mod = (movespeed * (delay + (distancetoplayer / misslespeed))) - Bound;

	if (length > 0.f)
	{
		Vector3 movetovectornorm = Vector3(movetovector.x / length, movetovector.y / length, movetovector.z / length);
		Vector3 predpos = Vector3(TargetPos.x + (movetovectornorm.x*mod), TargetPos.y + (movetovectornorm.y*mod), TargetPos.z + (movetovectornorm.z*mod));
		float distancetopred = sqrt(pow((TargetPos.x - predpos.x), 2) + pow((TargetPos.y - predpos.y), 2) + pow((TargetPos.z - predpos.z), 2));
		float distancetotargetposto = sqrt(pow((TargetPos.x - NextNavPoint.x), 2) + pow((TargetPos.y - NextNavPoint.y), 2) + pow((TargetPos.z - NextNavPoint.z), 2));
		if (distancetopred > distancetotargetposto)
		{
			return NextNavPoint;
		}
		return predpos;
	}
	else {
		return TargetPos;
	}
}

float Prediction::TimeToHit(Vector3 StartPos, Vector3 PredPos, float missilespeed, float delay) {
	float Distance = Engine::GetDistance3D(StartPos, PredPos);
	float TimeToHit = (Distance / missilespeed) + delay;
	return TimeToHit;
}
float Prediction::GetHitchance(Vector3 StartPos, Vector3 PredPos, GameObject* Target, float range, float missilespeed, float delay, float radius, bool collision) {
	Vector3 PlayerPos = StartPos;
	Vector3 TargetPos = Target->GetPosition();
	//---------------------------------------
	int NavPoints = 0;
	float PathDist = 0.f;
	Vector3* NavBegin = Target->GetAIManager()->GetNavBegin();
	Vector3* NavEnd = Target->GetAIManager()->GetNavEnd();

	Vector3 NextNavPoint = Target->GetAIManager()->TargetPos();
	for (Vector3* Path = NavBegin; Path < NavEnd; Path++)
	{
		Vector3* Current = Path;
		Vector3* Next = Path + 1;
		if (Next != NavEnd)
		{
			PathDist += Engine::GetDistance3D(*Current, *Next);
			if (PointOnLineSegment3D(*Current, *Next, TargetPos, 10.f))
			{
				NextNavPoint = *Next;
			}
		}
		NavPoints++;
	}
	//----------------------------------------

	if (Target->GetAIManager()->IsDashing())
	{
		NextNavPoint = Target->GetAIManager()->TargetPos();
	}

	Vector3 PlayerToTarget = Vector3(PlayerPos.x - TargetPos.x, 0 , PlayerPos.z - TargetPos.z);
	Vector3 TargetToNextNav = Vector3(NextNavPoint.x - TargetPos.x, 0, NextNavPoint.z - TargetPos.z);

	float det = PlayerToTarget.x * TargetToNextNav.z - PlayerToTarget.z * TargetToNextNav.x;
	float dot = PlayerToTarget.x * TargetToNextNav.x + PlayerToTarget.z * TargetToNextNav.z;

	float angle = std::atan2(det,dot);

	//std::cout << std::abs(angle) << std::endl;
	//std::cout << std::endl;



	float timeToHit = TimeToHit(StartPos, PredPos, missilespeed, delay);
	float moveSpeed = Target->GetMoveSpeed();
	float HitChance = std::fminf(1.f, (radius * 2.f) / moveSpeed / timeToHit);





	//if (std::abs(angle) < 0.6f)
	//{
	//	HitChance *= 2.f;
	//}

	if (IsImmobilized(Target))
	{
		HitChance = 1.f;
	}
	if (collision)
	{
		if (IsCollisioned(Minion, StartPos, TargetPos, radius * 1.75f))
		{
			HitChance /= 2.f;
		}
		if (IsCollisioned(Minion, StartPos, PredPos, radius * 1.75f))
		{
			HitChance = 0.f;
		}
	}
	if (Engine::GetDistance3D(StartPos,PredPos) > range)
	{
		HitChance = 0.f;
	}
	return HitChance * 1.2f;
}