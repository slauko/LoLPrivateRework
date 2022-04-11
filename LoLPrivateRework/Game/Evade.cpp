#pragma once
#include "GameIncludes.h"
#define _USE_MATH_DEFINES
#include <math.h>

bool Evade::Init = false;
LPD3DXFONT Evade::D3D_Font;
D3DCOLOR Evade::TextColor;

bool Evade::OnlyCC;
Evade::DangerZone Evade::DZone = Evade::Outside;

float Evade::LastEvadeCommand;
Vector3 Evade::PlayerPredMovePos;

void Evade::CalcLinearSpellStartEndPos(Vector3 StartPos, Vector3 EndPos, SpellDataInfo* Spell, Vector3 &SpellStartPos,Vector3 &SpellEndPos) {
	Vector3 totargetvec = Vector3(EndPos.x - StartPos.x, 0, EndPos.z - StartPos.z);
	float length = sqrt((totargetvec.x * totargetvec.x) + (totargetvec.y * totargetvec.y) + (totargetvec.z * totargetvec.z));
	Vector3 totargetvecnorm = Vector3(totargetvec.x / length, 0, totargetvec.z / length);
	float mod = Spell->range;
	EndPos = Vector3(StartPos.x + (totargetvecnorm.x*mod), StartPos.y + (totargetvecnorm.y*mod), StartPos.z + (totargetvecnorm.z*mod));
	Vector3 StartEndVec = Vector3(EndPos.x - StartPos.x, EndPos.y - StartPos.y, EndPos.z - StartPos.z);
	float length2 = sqrt((StartEndVec.x * StartEndVec.x) + (StartEndVec.y * StartEndVec.y) + (StartEndVec.z * StartEndVec.z));
	//---------------------------
	Vector3 Start2Screen;
	Vector3 End2Screen;
	if (Spell->range > 5000.f)
	{
		for (size_t i = 0; i < 25000; i += 100)
		{
			if (Engine::World2Screen(&StartPos, &Start2Screen))
			{
				if (i > 0)
				{
					StartPos = Vector3(StartPos.x - (totargetvecnorm.x * 2000), StartPos.y, StartPos.z - (totargetvecnorm.z * 2000));
				}
				break;
			}
			if (!Engine::World2Screen(&StartPos, &Start2Screen)) {
				StartPos = Vector3(StartPos.x + (totargetvecnorm.x* i), StartPos.y, StartPos.z + (totargetvecnorm.z* i));
			}
		}
		for (size_t i = 0; i < 25000; i += 100)
		{
			if (Engine::World2Screen(&EndPos, &End2Screen))
			{
				if (i > 0)
				{
					EndPos = Vector3(EndPos.x + (totargetvecnorm.x * 2000), EndPos.y, EndPos.z + (totargetvecnorm.z * 2000));
				}
				break;
			}
			if (!Engine::World2Screen(&EndPos, &End2Screen)) {
				EndPos = Vector3(EndPos.x - (totargetvecnorm.x* i), EndPos.y, EndPos.z - (totargetvecnorm.z* i));
			}
		}
	}
	SpellStartPos = StartPos;
	SpellEndPos = EndPos;
}
void Evade::CalcLinearMissileStartEndPos(GameObject* Missile, Vector3 StartPos, Vector3 EndPos, SpellDataInfo* Spell, Vector3 &SpellStartPos, Vector3 &SpellEndPos) {
	Vector3 MissilePos = Missile->GetPosition();
	Vector3 CurrentPos = { MissilePos.x,StartPos.y,MissilePos.z };
	Vector3 StartToCurrentPos = Vector3(CurrentPos.x - StartPos.x, 0, CurrentPos.z - StartPos.z);
	float DistToStartPos = sqrt((StartToCurrentPos.x * StartToCurrentPos.x) + (StartToCurrentPos.y * StartToCurrentPos.y) + (StartToCurrentPos.z * StartToCurrentPos.z));

	Vector3 totargetvec = Vector3(EndPos.x - StartPos.x, 0, EndPos.z - StartPos.z);
	float length = sqrt((totargetvec.x * totargetvec.x) + (totargetvec.y * totargetvec.y) + (totargetvec.z * totargetvec.z));
	Vector3 totargetvecnorm = Vector3(totargetvec.x / length, 0, totargetvec.z / length);
	float mod = Spell->range;
	EndPos = Vector3(StartPos.x + (totargetvecnorm.x*mod), StartPos.y + (totargetvecnorm.y*mod), StartPos.z + (totargetvecnorm.z*mod));
	Vector3 StartEndVec = Vector3(EndPos.x - StartPos.x, EndPos.y - StartPos.y, EndPos.z - StartPos.z);
	float length2 = sqrt((StartEndVec.x * StartEndVec.x) + (StartEndVec.y * StartEndVec.y) + (StartEndVec.z * StartEndVec.z));
	//---------------------------
	Vector3 Start2Screen;
	Vector3 End2Screen;
	if (Spell->range > 5000.f)
	{
		for (size_t i = 0; i < 25000; i += 100)
		{
			if (Engine::World2Screen(&StartPos, &Start2Screen))
			{
				if (i > 0)
				{
					StartPos = Vector3(StartPos.x - (totargetvecnorm.x * 2000), StartPos.y, StartPos.z - (totargetvecnorm.z * 2000));
				}
				break;
			}
			if (!Engine::World2Screen(&StartPos, &Start2Screen)) {
				StartPos = Vector3(StartPos.x + (totargetvecnorm.x* i), StartPos.y, StartPos.z + (totargetvecnorm.z* i));
			}
		}
		for (size_t i = 0; i < 25000; i += 100)
		{
			if (Engine::World2Screen(&EndPos, &End2Screen))
			{
				if (i > 0)
				{
					EndPos = Vector3(EndPos.x + (totargetvecnorm.x * 2000), EndPos.y, EndPos.z + (totargetvecnorm.z * 2000));
				}
				break;
			}
			if (!Engine::World2Screen(&EndPos, &End2Screen)) {
				EndPos = Vector3(EndPos.x - (totargetvecnorm.x* i), EndPos.y, EndPos.z - (totargetvecnorm.z* i));
			}
		}
	}
	if (DistToStartPos < length2)
	{
		SpellStartPos = CurrentPos;
	}
	else {
		SpellStartPos = EndPos;
	}
	
	SpellEndPos = EndPos;
}
Vector3* Evade::CalcLinearSpellHitbox3D(Vector3 StartPos, Vector3 EndPos, SpellDataInfo* Spell) {
	//---------------------------
	float x = StartPos.x;

	float y = StartPos.y;

	float z = StartPos.z;

	float xx = EndPos.x;

	float yy = StartPos.y;

	float zz = EndPos.z;

	//---------------------------
	float x3 = xx - x;

	float y3 = yy - y;

	float z3 = zz - z;

	//---------------------------
	float length3 = sqrt((x3 * x3) + (z3 * z3));
	x3 = (x3 / length3) * Spell->radius;
	z3 = (z3 / length3) * Spell->radius;
	Vector3* corners3D = new Vector3[4];

	float x4 = x - z3;
	float z4 = z + x3;

	float x5 = x + z3;
	float z5 = z - x3;

	float x6 = xx - z3;
	float z6 = zz + x3;

	float x7 = xx + z3;
	float z7 = zz - x3;

	corners3D[0] = { x4, y , z4 };
	corners3D[1] = { x5, y , z5 };
	corners3D[2] = { x6, yy ,z6 };
	corners3D[3] = { x7, yy ,z7 };
	return corners3D;
}
Vector3* Evade::CalcLinearSpellHitbox3D(Vector3 &StartPos, Vector3 &EndPos, SpellDataInfo* Spell,float RadiusAddition) {
	//Add some more SpellRange to be sure Spell wont hit on maxRange
	Vector3 totargetvec = Vector3(EndPos.x - StartPos.x, 0, EndPos.z - StartPos.z);
	float length = sqrt((totargetvec.x * totargetvec.x) + (totargetvec.y * totargetvec.y) + (totargetvec.z * totargetvec.z));
	Vector3 totargetvecnorm = Vector3(totargetvec.x / length, 0, totargetvec.z / length);
	float mod = Spell->range + RadiusAddition;
	EndPos = Vector3(StartPos.x + (totargetvecnorm.x * mod), StartPos.y + (totargetvecnorm.y * mod), StartPos.z + (totargetvecnorm.z * mod));

	//---------------------------
	float x = StartPos.x;

	float y = StartPos.y;

	float z = StartPos.z;

	float xx = EndPos.x;

	float yy = StartPos.y;

	float zz = EndPos.z;

	//---------------------------
	float x3 = xx - x;

	float y3 = yy - y;

	float z3 = zz - z;

	//---------------------------
	float length3 = sqrt((x3 * x3) + (z3 * z3));
	x3 = (x3 / length3) * (Spell->radius+RadiusAddition);
	z3 = (z3 / length3) * (Spell->radius+RadiusAddition);
	Vector3* corners3D = new Vector3[4];

	float x4 = x - z3;
	float z4 = z + x3;

	float x5 = x + z3;
	float z5 = z - x3;

	float x6 = xx - z3;
	float z6 = zz + x3;

	float x7 = xx + z3;
	float z7 = zz - x3;

	corners3D[0] = { x4, y , z4 };
	corners3D[1] = { x5, y , z5 };
	corners3D[2] = { x6, yy ,z6 };
	corners3D[3] = { x7, yy ,z7 };
	return corners3D;
}
Vector3* Evade::CalcCircleSpellHitbox3D(Vector3 EndPos, SpellDataInfo* Spell, int precision) {
	Vector3* pointOnCircle3D = new Vector3[precision];
	float radius = Spell->radius;
	for (int i = 0; i < precision; i++)
	{
		float angle = ((float)i * (float)M_PI) / 180.f;
		pointOnCircle3D[i].x = cos(angle) * radius + EndPos.x;
		pointOnCircle3D[i].y = EndPos.y;
		pointOnCircle3D[i].z = sin(angle) * radius + EndPos.z;
	}
	return pointOnCircle3D;
}
Vector3* Evade::CalcEvadeCircle3D(Vector3 PlayerPos, int precision, float RadiusAddition) {
	Vector3* pointOnCircle3D = new Vector3[precision];
	Vector3 MousePos = Engine::pMouse->MousePos;
	float MouseDistance = (float)sqrt(pow((MousePos.x - PlayerPos.x), 2) + pow((MousePos.z - PlayerPos.z), 2));
	float radius = MouseDistance;
	for (int i = 0; i < precision; i++)
	{
		float angle = ((float)i * (float)M_PI) / 180.f;
		pointOnCircle3D[i].x = cos(angle) * radius + PlayerPos.x;
		pointOnCircle3D[i].y = PlayerPos.y;
		pointOnCircle3D[i].z = sin(angle) * radius + PlayerPos.z;
	}
	return pointOnCircle3D;
}
Vector3 Evade::CalcEvadeDirection3D(Vector3 EvadePoint3D, float RadiusAddition) {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	float Bound = Engine::pLocalPlayer->GetBoundingRadius();

		Vector3 movetovector = Vector3(EvadePoint3D.x - PlayerPos.x, EvadePoint3D.y - PlayerPos.y, EvadePoint3D.z - PlayerPos.z);
		float length = sqrt((movetovector.x * movetovector.x) + (movetovector.y * movetovector.y) + (movetovector.z * movetovector.z));
		Vector3 movetovectornorm = Vector3(movetovector.x / length, movetovector.y / length, movetovector.z / length);
		float movespeed = Engine::pLocalPlayer->GetMoveSpeed();
		float mod = RadiusAddition;
		return Vector3(PlayerPos.x + (movetovectornorm.x*mod), PlayerPos.y + (movetovectornorm.y*mod), PlayerPos.z + (movetovectornorm.z*mod));
}
Vector3* Evade::CalcLinearSpellHitbox2D(Vector3* corners3D) {
	Vector3* corners2D = new Vector3[4];
	Engine::World2Screen(&corners3D[0], &corners2D[0]);
	Engine::World2Screen(&corners3D[1], &corners2D[1]);
	Engine::World2Screen(&corners3D[2], &corners2D[2]);
	Engine::World2Screen(&corners3D[3], &corners2D[3]);
	delete[] corners3D;
	return corners2D;
}
Vector3* Evade::CalcCircleSpellHitbox2D(Vector3* pointOnCircle3D, int precision) {
	Vector3* pointOnCircle2D = new Vector3[precision];
	for (int i = 0; i < precision; i++)
	{
		Engine::World2Screen(&pointOnCircle3D[i], &pointOnCircle2D[i]);
	}
	delete[] pointOnCircle3D;
	return pointOnCircle2D;
}
void Evade::DrawLine(LPDIRECT3DDEVICE9 pDevice, float x, float y, float xx, float yy, int r, int g, int b, int a)
{
	static ID3DXLine* pLine1;

	if (!pLine1)
		D3DXCreateLine(pDevice, &pLine1);

	D3DXVECTOR2 dLine[2];

	pLine1->SetWidth(1);
	pLine1->SetAntialias(true);
	pLine1->SetGLLines(true);

	dLine[0].x = x;
	dLine[0].y = y;

	dLine[1].x = xx;
	dLine[1].y = yy;

	pLine1->Draw(dLine, 2, D3DCOLOR_ARGB(a, r, g, b));

}
void Evade::DrawCircleHitbox(LPDIRECT3DDEVICE9 pDevice, Vector3* pointOnCircle2D, int precision) {
	for (int i = 0; i < precision-1; i++)
	{
		DrawLine(pDevice, pointOnCircle2D[i].x, pointOnCircle2D[i].y, pointOnCircle2D[i + 1].x, pointOnCircle2D[i + 1].y, 255, 255, 255, 255);
	}
}
void Evade::DrawLineHitbox(LPDIRECT3DDEVICE9 pDevice, Vector3* corners2D) {
	DrawLine(pDevice, corners2D[0].x, corners2D[0].y, corners2D[2].x, corners2D[2].y, 255, 255, 255, 255);
	DrawLine(pDevice, corners2D[1].x, corners2D[1].y, corners2D[3].x, corners2D[3].y, 255, 255, 255, 255);
	DrawLine(pDevice, corners2D[0].x, corners2D[0].y, corners2D[1].x, corners2D[1].y, 255, 0, 0, 255);
	DrawLine(pDevice, corners2D[2].x, corners2D[2].y, corners2D[3].x, corners2D[3].y, 255, 0, 0, 255);
	delete[] corners2D;
}
void Evade::ClosestLineFromLinearHitbox2D(Vector3* corners2D, Vector3 *ClosestLineStart2D, Vector3 *ClosestLineEnd2D) {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	Vector3 PlayerScreen;
	Engine::World2Screen(&PlayerPos, &PlayerScreen);
	float dist[4];
	dist[0] = Prediction::DistanceToLine2D(corners2D[0], corners2D[2], PlayerScreen);
	dist[1] = Prediction::DistanceToLine2D(corners2D[1], corners2D[3], PlayerScreen);
	dist[2] = Prediction::DistanceToLine2D(corners2D[0], corners2D[1], PlayerScreen);
	dist[3] = Prediction::DistanceToLine2D(corners2D[2], corners2D[3], PlayerScreen);
	int closestindex = 0;
	float n = dist[0];
	for (int i = 1; i < 4; ++i)
	{
		if (dist[i] < n)
		{
			n = dist[i];
			closestindex = i;
		}
	}
	switch (closestindex)
	{
	case 0:
		*ClosestLineStart2D = corners2D[0];
		*ClosestLineEnd2D = corners2D[2];
		break;
	case 1:
		*ClosestLineStart2D = corners2D[1];
		*ClosestLineEnd2D = corners2D[3];
		break;
	case 2:
		if (dist[0] < dist[0])
		{
			*ClosestLineStart2D = corners2D[0];
			*ClosestLineEnd2D = corners2D[2];
		}
		else {
			*ClosestLineStart2D = corners2D[1];
			*ClosestLineEnd2D = corners2D[3];
		}
		break;
	case 3:
		if (dist[0] < dist[0])
		{
			*ClosestLineStart2D = corners2D[0];
			*ClosestLineEnd2D = corners2D[2];
		}
		else {
			*ClosestLineStart2D = corners2D[1];
			*ClosestLineEnd2D = corners2D[3];
		}
		break;
	default:
		break;
	}
}
void Evade::ClosestLineFromLinearHitbox3D(Vector3* corners3D, Vector3 *ClosestLineStart3D, Vector3 *ClosestLineEnd3D) {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	float dist[4];
	dist[0] = Prediction::DistanceToLine3D(corners3D[0], corners3D[2], PlayerPos);
	dist[1] = Prediction::DistanceToLine3D(corners3D[1], corners3D[3], PlayerPos);
	dist[2] = Prediction::DistanceToLine3D(corners3D[0], corners3D[1], PlayerPos);
	dist[3] = Prediction::DistanceToLine3D(corners3D[2], corners3D[3], PlayerPos);
	int closestindex = 0;
	float n = dist[0];
	for (int i = 1; i < 4; ++i)
	{
		if (dist[i] < n)
		{
			n = dist[i];
			closestindex = i;
		}
	}
	switch (closestindex)
	{
	case 0:
		*ClosestLineStart3D = corners3D[0];
		*ClosestLineEnd3D = corners3D[2];
		break;
	case 1:
		*ClosestLineStart3D = corners3D[1];
		*ClosestLineEnd3D = corners3D[3];
		break;
	case 2:
		if (dist[0] < dist[1])
		{
			*ClosestLineStart3D = corners3D[0];
			*ClosestLineEnd3D = corners3D[2];
		}
		else {
			*ClosestLineStart3D = corners3D[1];
			*ClosestLineEnd3D = corners3D[3];
		}
		break;
	case 3:
		if (dist[0] < dist[1])
		{
			*ClosestLineStart3D = corners3D[0];
			*ClosestLineEnd3D = corners3D[2];
		}
		else {
			*ClosestLineStart3D = corners3D[1];
			*ClosestLineEnd3D = corners3D[3];
		}
		break;
	default:
		break;
	}
}
Vector3 Evade::ClosestPointFromCircle3D(Vector3* pointOnCircle3D, int precision) {
	float *dist = new float[precision];
	dist[0] = HUGE_VALF;
	for (int i = 0; i < precision - 1; i++)
	{
		dist[i] = Engine::GetDistance3D(pointOnCircle3D[i],Engine::pLocalPlayer);
	}
	int closestindex = 0;
	float n = dist[0];
	for (int i = 1; i < precision - 1; ++i)
	{
		if (dist[i] < n)
		{
			n = dist[i];
			closestindex = i;
		}
	}
	delete[] dist;
	return pointOnCircle3D[closestindex];
}
Vector3 Evade::GetMissilePredPos(Vector3 MissileStartPos,Vector3 MissileEndPos, float missilespeed, float delay,float time) {
	Vector3 StartPos = MissileStartPos;
	Vector3 EndPos = MissileEndPos;
	Vector3 totargetvec = Vector3(EndPos.x - StartPos.x, 0, EndPos.z - StartPos.z);
	float length = sqrt((totargetvec.x * totargetvec.x) + (totargetvec.y * totargetvec.y) + (totargetvec.z * totargetvec.z));
	Vector3 totargetvectornorm = Vector3(totargetvec.x / length, 0, totargetvec.z / length);
	float mod = missilespeed * (time - delay);
	Vector3 predpos = Vector3(StartPos.x + (totargetvectornorm.x*mod), StartPos.y + (totargetvectornorm.y*mod), StartPos.z + (totargetvectornorm.z*mod));
	return predpos;
}
float Evade::GetTimeToEvadePos(Vector3 EvadePos) {
	Vector3 StartPos = Engine::pLocalPlayer->GetPosition();
	Vector3 EndPos = EvadePos;
	Vector3 totargetvec = Vector3(EndPos.x - StartPos.x, 0, EndPos.z - StartPos.z);
	float distance = sqrt((totargetvec.x * totargetvec.x) + (totargetvec.y * totargetvec.y) + (totargetvec.z * totargetvec.z));
	float movespeed = Engine::pLocalPlayer->GetMoveSpeed();
	float time = distance / movespeed;
	return time;
}
Vector3 Evade::EvadePointClosestToMouse(Vector3 StartPos, Vector3 EndPos, Vector3* EvadeCircle, Vector3* HitBox, SpellDataInfo* Spell, int precision, float RadiusAddition) {
	Vector3 ClosestPoint = { 0.f,0.f,0.f };
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	Vector3 MousePos = Engine::pMouse->MousePos;
	float Bound = Engine::pLocalPlayer->GetBoundingRadius();
	float bufferdist = HUGE_VALF;
	DWORD colorself = 0x00FF88FF;
	for (int i = 0; i < precision; i++)
	{
		Vector3 Point = EvadeCircle[i];
		if (Prediction::PointOnLineSegment3D(StartPos, EndPos, Point, Spell->radius + RadiusAddition + Bound*2.f)) //If Pos in SkillShot
		{
			continue;
		}
		if (Prediction::WallBetween(PlayerPos,Point,10))
		{
			continue;
		}
		//Engine::DrawCircle(&Point, 65.f, &colorself, 0, 0, 0, 1.f);

		float MouseDistance = (float)sqrt(pow((Point.x - MousePos.x), 2) + pow((Point.z - MousePos.z), 2));
		if (MouseDistance < bufferdist)
		{
			bufferdist = MouseDistance;
			ClosestPoint = Point;
		}
	}
	//Engine::DrawCircle(&MousePos, 65.f, &colorself, 0, 0, 0, 1.f);

	return ClosestPoint;
}
Vector3 Evade::GetEvadePos(Vector3 StartPos, Vector3 EndPos, Vector3* HitBox, SpellDataInfo* Spell, int precision, float RadiusAddition) {
	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	Vector3 MousePos = Engine::pMouse->MousePos;
	float Bound = Engine::pLocalPlayer->GetBoundingRadius();
	if (Spell->type == linear)
	{
		Vector3 StartEndVec = Vector3(EndPos.x - StartPos.x, EndPos.y - StartPos.y, EndPos.z - StartPos.z);
		float Length = sqrt((StartEndVec.x * StartEndVec.x) + (StartEndVec.y * StartEndVec.y) + (StartEndVec.z * StartEndVec.z));
		Vector3 StartPlayerVec = Vector3(PlayerPos.x - StartPos.x, PlayerPos.y - StartPos.y, PlayerPos.z - StartPos.z);
		float DistanceToStartPos = sqrt((StartPlayerVec.x * StartPlayerVec.x) + (StartPlayerVec.y * StartPlayerVec.y) + (StartPlayerVec.z * StartPlayerVec.z));
		Vector3 EndPlayerVec = Vector3(PlayerPos.x - EndPos.x, PlayerPos.y - EndPos.y, PlayerPos.z - EndPos.z);
		float DistanceToEndPos = sqrt((EndPlayerVec.x * EndPlayerVec.x) + (EndPlayerVec.y * EndPlayerVec.y) + (EndPlayerVec.z * EndPlayerVec.z));
		Vector3 IntersectionPoint;
		Vector3 ClosestLineStart3D;
		Vector3 ClosestLineEnd3D;

		ClosestLineFromLinearHitbox3D(HitBox, &ClosestLineStart3D, &ClosestLineEnd3D);
		delete[] HitBox;

		//DWORD colorself = 0x00FF88FF;
		//Engine::DrawCircle(&ClosestLineStart3D, 65.f, &colorself, 0, 0, 0, 1.f);
		//Engine::DrawCircle(&ClosestLineEnd3D, 65.f, &colorself, 0, 0, 0, 1.f);


		PlayerPredMovePos = CalcEvadeDirection3D(MousePos, 50);

		Vector3 ClosestPoint = Prediction::GetShortestPointToLine3D(ClosestLineStart3D, ClosestLineEnd3D, PlayerPredMovePos);
		Vector3 ClosestDirection = CalcEvadeDirection3D(ClosestPoint, 300);
		if (Prediction::PointOnLineSegment3D(StartPos, EndPos, PlayerPos, Spell->radius + RadiusAddition/2)) //If Player in SkillShot move Out
		{
			//cout << "INSIDE: DOGE!" << endl;
			DZone = Inside;
			Engine::BlockAA = true;
			return ClosestDirection;
		}
		if (Prediction::PointOnLineSegment3D(StartPos, EndPos, PlayerPos, Spell->radius + RadiusAddition + Bound)) //If Player about to Leave SkillShot
		{
			DZone = AtBorder;
			Engine::BlockAA = false;
			//cout << "DANGERZONE: MoveToMouse" << endl;
			if (Prediction::LineIntersection3D(StartPos, EndPos, PlayerPos, MousePos, IntersectionPoint))
			{
				return Prediction::GetShortestPointToLine3D(ClosestLineStart3D, ClosestLineEnd3D, MousePos);
			}
			if (Prediction::PointOnLineSegment3D(StartPos, EndPos, MousePos, Spell->radius + RadiusAddition + Bound))
			{
				return Prediction::GetShortestPointToLine3D(ClosestLineStart3D, ClosestLineEnd3D, MousePos);
			}
			Engine::ForceEvade = false;
			//return MousePos;
		}
		if (Prediction::PointOnLineSegment3D(StartPos, EndPos, PlayerPos, Spell->radius + RadiusAddition*3.f)) //If Player outside but Mouse inside Skillshot, dont move In
		{
			if (Prediction::PointOnLineSegment3D(StartPos, EndPos, MousePos, Spell->radius + RadiusAddition + Bound) ||
				Prediction::LineIntersection3D(StartPos, EndPos, PlayerPos, MousePos, IntersectionPoint))
			{
				DZone = Outside;
				//cout << "OUTSIDE: ONLY MOVE TILL SKILLSHOT" << endl;
				Engine::BlockAA = false;
				if (Engine::getOrbMode() != Idle)
				{
					return  Prediction::GetShortestPointToLine3D(ClosestLineStart3D, ClosestLineEnd3D, MousePos);
				}
			}
		}
	}
	return Vector3(0.f, 0.f, 0.f);
}
bool PlayerHasOlafR() {
	if (Engine::pLocalPlayer->GetBuffManager()->HasBuff("OlafRagnarok"))
	{
		return true;
	}
	return false;
}
int EvadeToPoint(Vector3 Point, SpellDataInfo* Spell) {
	if (Point.x != 0 && Point.y != 0 && Point.z != 0)
	{
		if (Engine::YasuoSelected)
		{
			if (Menu::UseW && Engine::SpellReady(W))
			{
				Engine::BlockAA = false;
			}
		}
		//cout << "EVADE!" << endl;
		Engine::EvadePos = Point;
		Engine::ForceEvade = true;
		return 1;
	}
	return 0;
}
int  Evade::SpellHandler(LPDIRECT3DDEVICE9 pDevice) {
	Engine::BlockAA = false;
	Engine::ForceEvade = false;

	DZone = Outside;

	DWORD CircleColor = 0x000000FF;

	int precision = 361;
	float EvadeDelay = 0.2f;

	float RadiusAddition = Engine::pLocalPlayer->GetBoundingRadius()*2.5f;
	
	bool OnlyCC = false;
	bool EvadeActive = false;
	bool IgnoreCircular = true;

	if (Engine::getOrbMode() == Target_Combo)
	{
		OnlyCC = true;
		EvadeActive = true;
	}

	if (OnlyCC)
	{
		if (Engine::OlafSelected)
		{
			if (PlayerHasOlafR())
			{
				EvadeActive = false;
			}
		}
	}

	Vector3 PlayerPos = Engine::pLocalPlayer->GetPosition();
	for (GameObject* Enemy : TargetList::ChampionList)
	{
		if (Enemy->GetTeam() == Engine::pLocalPlayer->GetTeam())
		{
			continue;
		}
		if (Enemy->GetSpellbook()->GetActiveSpellEntry())
		{
			SpellEntry* CurrentSpell = Enemy->GetSpellbook()->GetActiveSpellEntry();
			const char* SpellName = CurrentSpell->GetActiveSpellInfo()->GetSpellName().c_str();
			if (strstr(SpellName,"Attack") || Engine::IsAutoAttack(SpellName))
			{
				continue;
			}
			for( auto _Spell : Engine::SpellDataBase.Spells)
			{
				//std::cout << Spell->spellName << std::endl;
				if (strstr(_Spell.first.c_str(), SpellName))
				{
					SpellDataInfo* Spell = _Spell.second;
					if (Spell->type == linear)
					{
						if (!CurrentSpell->GetCastState())
						{
							Vector3 StartPos, EndPos;
							Vector3 StartScreen, EndScreen;
							CalcLinearSpellStartEndPos(CurrentSpell->GetSpellStartPos(), CurrentSpell->GetSpellEndPos(), Spell, StartPos, EndPos);
							if (Spell->range <= 5000) // if "short spell"
							{
								if (Engine::World2Screen(&StartPos,&StartScreen) || Engine::World2Screen(&EndPos,&EndScreen)) // only draw when on screen
								{
									Vector3* corners3D = CalcLinearSpellHitbox3D(StartPos, EndPos, Spell);
									Vector3* corners2D = CalcLinearSpellHitbox2D(corners3D);
									DrawLineHitbox(pDevice, corners2D);
								}
							}
							if (Spell->range > 5000) //if global
							{
								Vector3* corners3D = CalcLinearSpellHitbox3D(StartPos, EndPos, Spell);
								Vector3* corners2D = CalcLinearSpellHitbox2D(corners3D);
								DrawLineHitbox(pDevice, corners2D);
							}
							if (OnlyCC && !Spell->cc)
							{
								EvadeActive = false;
							}
							if (EvadeActive && Prediction::PointOnLineSegment3D(StartPos, EndPos, PlayerPos, Spell->radius + RadiusAddition * 3.f)) //If Player in Range of Skillshot
							{

								if (Spell->collision)
								{
									if (Prediction::EnemySpellWillCollideWith(Minion, StartPos, EndPos, Spell->radius))
									{
										if (!Prediction::EnemySpellWillCollideWith(Minion, StartPos, PlayerPos, Spell->radius))
										{
											Vector3 *AdvancedHitbox = CalcLinearSpellHitbox3D(StartPos, EndPos, Spell, RadiusAddition);
											Vector3 Point = GetEvadePos(StartPos, EndPos, AdvancedHitbox, Spell, precision, RadiusAddition);
											EvadeToPoint(Point, Spell);
										}
									}
									else {
										Vector3 *AdvancedHitbox = CalcLinearSpellHitbox3D(StartPos, EndPos, Spell, RadiusAddition);
										Vector3 Point = GetEvadePos(StartPos, EndPos, AdvancedHitbox, Spell, precision, RadiusAddition);
										EvadeToPoint(Point, Spell);
									}
								}
								else {
									Vector3 *AdvancedHitbox = CalcLinearSpellHitbox3D(StartPos, EndPos, Spell, RadiusAddition);
									Vector3 Point = GetEvadePos(StartPos, EndPos, AdvancedHitbox, Spell, precision, RadiusAddition);
									EvadeToPoint(Point, Spell);
								}
							}
						}
					}
					if (Spell->type == circular)
					{
						if (!CurrentSpell->GetCastState())
						{
							Vector3 StartPos, EndPos;
							Vector3 StartScreen, EndScreen;
							StartPos = CurrentSpell->GetSpellEndPos();
							EndPos = CurrentSpell->GetSpellEndPos();
							if (Engine::World2Screen(&StartPos, &StartScreen) || Engine::World2Screen(&EndPos, &EndScreen)) // only draw when on screen
							{
								//Vector3* pointOnCircle3D = CalcCircleSpellHitbox3D(CurrentSpell->GetSpellEndPos(), Spell, precision);
								//Vector3* pointOnCircle2D = CalcCircleSpellHitbox2D(pointOnCircle3D, precision);
								//DrawCircleHitbox(pDevice, pointOnCircle2D, precision);

								Engine::DrawCircle(&EndPos, Spell->radius, &CircleColor, 0, 0, 0, 1.f);

							}
							Vector3 Point = GetEvadePos(StartPos, EndPos, NULL, Spell, precision, RadiusAddition);
							if (EvadeActive && !IgnoreCircular)
							{
								EvadeToPoint(Point, Spell);
							}
						}
					}
					break;
				}
			}
		}
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
					Vector3 StartPos, EndPos;
					Vector3 StartScreen, EndScreen;
					CalcLinearMissileStartEndPos(Missile, Missile->GetMissileStartPos(), Missile->GetMissileEndPos(), Spell, StartPos, EndPos);
					if (Spell->range <= 5000) // if "short spell"
					{
						if (Engine::World2Screen(&StartPos, &StartScreen) || Engine::World2Screen(&EndPos, &EndScreen)) // only draw when on screen
						{
							Vector3* corners3D = CalcLinearSpellHitbox3D(StartPos, EndPos, Spell);
							Vector3* corners2D = CalcLinearSpellHitbox2D(corners3D);
							DrawLineHitbox(pDevice, corners2D);
						}
					}
					if (Spell->range > 5000) //if global
					{
						Vector3* corners3D = CalcLinearSpellHitbox3D(StartPos, EndPos, Spell);
						Vector3* corners2D = CalcLinearSpellHitbox2D(corners3D);
						DrawLineHitbox(pDevice, corners2D);
					}
					if (OnlyCC && !Spell->cc)
					{
						EvadeActive = false;
					}
					//if (Spell->range <= 5000) // if "short spell"
					//{
					//	CalcLinearSpellStartEndPos(Missile->GetMissileStartPos(), Missile->GetMissileEndPos(), Spell, StartPos, EndPos); //always dodge full range of hitbox
					//}
					if (EvadeActive && Prediction::PointOnLineSegment3D(StartPos, EndPos, PlayerPos, Spell->radius + RadiusAddition * 3.f)) //If Player in Range of Skillshot
					{
						if (Spell->collision)
						{
							if (Prediction::EnemySpellWillCollideWith(Minion, StartPos, EndPos, Spell->radius))
							{
								if (!Prediction::EnemySpellWillCollideWith(Minion, StartPos, PlayerPos, Spell->radius))
								{
									Vector3 *AdvancedHitbox = CalcLinearSpellHitbox3D(StartPos, EndPos, Spell, RadiusAddition);
									Vector3 Point = GetEvadePos(StartPos, EndPos, AdvancedHitbox, Spell, precision, RadiusAddition);
									EvadeToPoint(Point, Spell);
								}
							}
							else {
								Vector3 *AdvancedHitbox = CalcLinearSpellHitbox3D(StartPos, EndPos, Spell, RadiusAddition);
								Vector3 Point = GetEvadePos(StartPos, EndPos, AdvancedHitbox, Spell, precision, RadiusAddition);
								EvadeToPoint(Point, Spell);
							}
						}
						else {
							Vector3 *AdvancedHitbox = CalcLinearSpellHitbox3D(StartPos, EndPos, Spell, RadiusAddition);
							Vector3 Point = GetEvadePos(StartPos, EndPos, AdvancedHitbox, Spell, precision, RadiusAddition);
							EvadeToPoint(Point, Spell);
						}
					}
				}
				if (Spell->type == circular)
				{
					Vector3 StartPos, EndPos;
					Vector3 StartScreen, EndScreen;
					StartPos = Missile->GetMissileEndPos();
					EndPos = Missile->GetMissileEndPos();
					if (Engine::World2Screen(&StartPos, &StartScreen) || Engine::World2Screen(&EndPos, &EndScreen)) // only draw when on screen
					{
						//Vector3* pointOnCircle3D = CalcCircleSpellHitbox3D(Missile->GetMissileEndPos(), Spell, precision);
						//Vector3* pointOnCircle2D = CalcCircleSpellHitbox2D(pointOnCircle3D, precision);
						//DrawCircleHitbox(pDevice, pointOnCircle2D, precision);
						Engine::DrawCircle(&EndPos, Spell->radius, &CircleColor, 0, 0, 0, 1.f);
					}
					if (EvadeActive && !IgnoreCircular)
					{
						Vector3 Point = GetEvadePos(StartPos, EndPos, NULL, Spell, precision, RadiusAddition);
						EvadeToPoint(Point, Spell);
					}
				}
				break;
			}
		}
	}

		//if (*Engine::GameTime - LastEvadeCommand < EvadeDelay)
		//{
		//	Engine::ForceEvade = false;
		//}

		////Test------------------------
		//auto TestSpell = new SpellDataInfo();
		//for (auto _Spell : Engine::SpellDataBase.Spells)
		//{
		//	if (!_strcmpi(_Spell.first.c_str(), "AhriSeduce"))
		//	{
		//		TestSpell = _Spell.second;
		//	}
		//}

		//Vector3 StartPos, EndPos;
		//Vector3 MissileStartPos = Vector3(400, 200, 400);
		//Vector3 MissileEndPos = Vector3(14340, 171, 14390);
		//CalcLinearSpellStartEndPos(MissileStartPos, MissileEndPos, TestSpell, StartPos, EndPos);
		//Vector3* corners3D = CalcLinearSpellHitbox3D(StartPos, EndPos, TestSpell);
		//Vector3* corners2D = CalcLinearSpellHitbox2D(corners3D);
		//DrawLineHitbox(pDevice, corners2D);

		//Vector3 *AdvancedHitbox = CalcLinearSpellHitbox3D(StartPos, EndPos, TestSpell, RadiusAddition); //Add BoundingRadius to Hitbox so Player actually moves out of HitZone
		//Vector3* Advanced2D = CalcLinearSpellHitbox2D(AdvancedHitbox);
		//DrawLineHitbox(pDevice, Advanced2D);
		//
		//AdvancedHitbox = CalcLinearSpellHitbox3D(StartPos, EndPos, TestSpell, RadiusAddition); //Add BoundingRadius to Hitbox so Player actually moves out of HitZone
		////std::list<Vector3> EvadePoints = CalcEvadePointsAroundPlayer(StartPos, EndPos, AdvancedHitbox, TestSpell, precision, RadiusAddition);
		//Vector3 Point = GetEvadePos(StartPos, EndPos, AdvancedHitbox, TestSpell, precision, RadiusAddition);
		//DWORD colorself = 0x000000FF;
		//Engine::DrawCircle(&Point, 65.f, &colorself, 0, 0, 0, 1.f);

		//EvadeToPoint(Point, TestSpell);
		//

		//----------------------------------
	
	return 0;
}