#pragma once
#include "../Includes.h"
#include "SpellDataBase.h"

class Evade {
public:
	enum DangerZone {
		Inside,
		AtBorder,
		Outside
	};

	static bool Init;
	static LPD3DXFONT D3D_Font;
	static D3DCOLOR TextColor;

	static DangerZone DZone;
	static bool OnlyCC;


	static Vector3 PlayerPredMovePos;
	static float LastEvadeCommand;

	static void CalcLinearSpellStartEndPos(Vector3 StartPos, Vector3 EndPos, SpellDataInfo* Spell, Vector3 &SpellStartPos, Vector3 &SpellEndPos);
	static void CalcLinearMissileStartEndPos(GameObject* Missile, Vector3 StartPos, Vector3 EndPos, SpellDataInfo* Spell, Vector3 &SpellStartPos, Vector3 &SpellEndPos);
	static Vector3* CalcLinearSpellHitbox3D(Vector3 StartPos, Vector3 EndPos, SpellDataInfo* Spell);
	static Vector3* CalcLinearSpellHitbox3D(Vector3 &StartPos, Vector3 &EndPos, SpellDataInfo* Spell, float RadiusAddition);
	static Vector3* CalcCircleSpellHitbox3D(Vector3 EndPos, SpellDataInfo* Spell, int precision);
	static Vector3* CalcEvadeCircle3D(Vector3 PlayerPos, int precision, float RadiusAddition);
	static Vector3 CalcEvadeDirection3D(Vector3 EvadePoint3D, float RadiusAddition);

	static Vector3* CalcLinearSpellHitbox2D(Vector3* corners3D);
	static Vector3* CalcCircleSpellHitbox2D(Vector3* pointOnCircle3D, int precision);
	
	static void DrawLine(LPDIRECT3DDEVICE9 pDevice, float x, float y, float xx, float yy, int r, int g, int b, int a);
	static void DrawCircleHitbox(LPDIRECT3DDEVICE9 pDevice, Vector3* pointOnCircle2D, int precision);
	static void DrawLineHitbox(LPDIRECT3DDEVICE9 pDevice, Vector3* corners2D);

	static void ClosestLineFromLinearHitbox2D(Vector3* corners2D, Vector3 *ClosestLineStart2D, Vector3 *ClosestLineEnd2D);
	static void ClosestLineFromLinearHitbox3D(Vector3* corners3D, Vector3 *ClosestLineStart3D, Vector3 *ClosestLineEnd3D);

	static Vector3 GetMissilePredPos(Vector3 MissileStartPos, Vector3 MissileEndPos, float misslespeed, float delay, float time);
	static float GetTimeToEvadePos(Vector3 EvadePos);
	static Vector3 ClosestPointFromCircle3D(Vector3* pointOnCircle3D, int precision);
	static Vector3 EvadePointClosestToMouse(Vector3 StartPos, Vector3 EndPos, Vector3* EvadeCircle, Vector3* HitBox, SpellDataInfo* Spell, int precision, float RadiusAddition);
	static Vector3 GetEvadePos(Vector3 StartPos, Vector3 EndPos, Vector3* HitBox, SpellDataInfo* Spell, int precision, float RadiusAddition);
	static int SpellHandler(LPDIRECT3DDEVICE9 pDevice);
};