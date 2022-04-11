#pragma once
#include "../Includes.h"
#include "SpellDataBase.h"

class Prediction {
public:
	static float DistanceToLine2D(Vector3 line_start, Vector3 line_end, Vector3 point);
	static float DistanceToLine3D(Vector3 line_start, Vector3 line_end, Vector3 point);
	static Vector3 GetShortestPointToLine3D(Vector3 LineStart, Vector3 LineEnd, Vector3 Point);
	static bool LineIntersection2D(Vector3 line1_start, Vector3 line1_end, Vector3 line2_start, Vector3 line2_end, float *i_x, float *i_y);
	static bool LineIntersection3D(Vector3 line1_start, Vector3 line1_end, Vector3 line2_start, Vector3 line2_end, Vector3 &I_Point);
	static bool PointOnLineSegment(Vector3 pt1, Vector3 pt2, Vector3 pt, float epsilon);
	static bool PointOnLineSegment3D(Vector3 pt1, Vector3 pt2, Vector3 pt, float epsilon);
	static bool IsCollisioned(CollisionType type, Vector3 vec, float radius);
	static bool IsCollisioned(CollisionType type, Vector3 StartPos, Vector3 EndPos, float radius);
	static bool EnemySpellWillCollide(GameObject* Target, CollisionType type, Vector3 vec, float radius);
	static bool EnemySpellWillCollideWith(CollisionType type, Vector3 StartPos, Vector3 EndPos, float radius);
	static bool EnemySpellWillCollideWithMe(GameObject* Target, Vector3 vec, float radius);
	static bool EnemySpellWillCollideWithFriend(GameObject* Friend, Vector3 StartPos, Vector3 EndPos, float radius);
	static bool IsAttackingEnemy(GameObject* Target);
	static bool WallBetween(Vector3 Point1, Vector3 Point2, float radius);
	static bool IsImmobilized(GameObject* Target);
	static Vector3 GetPredPos(GameObject* Target, float misslespeed, float delay);
	static Vector3 TwoPointPrediction(GameObject* Origin, GameObject* Target, float misslespeed, float delay);
	static Vector3 TwoPointPrediction(Vector3 Origin, GameObject* Target, float misslespeed, float delay);
	static float TimeToHit(Vector3 StartPos, Vector3 PredPos, float missilespeed, float delay);
	static float GetHitchance(Vector3 StartPos, Vector3 PredPos, GameObject* Target, float range, float missilespeed, float delay, float radius, bool collision);
};