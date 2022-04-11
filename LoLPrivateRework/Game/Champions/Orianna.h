#pragma once
#include "../Offsets.h"
#include "../SpellDataBase.h"

class Orianna {
public:
	static float QRange;
	static float WRange;
	static float ERange;
	static float RRange;

	static float QSpeed;
	static float WSpeed;
	static float ESpeed;
	static float RSpeed;

	static float QDelay;
	static float WDelay;
	static float EDelay;
	static float RDelay;

	static bool Initialized;
	static bool Initialize();

	static float GetSpellRange(SpellSlotID Spell) {
		if (Spell == Q)
		{
			return QRange;
		}
		if (Spell == W)
		{
			return WRange;
		}
		if (Spell == E)
		{
			return ERange;
		}
		if (Spell == R)
		{
			return RRange;
		}
		return 0.f;
	};
	static float GetSpellSpeed(SpellSlotID Spell) {
		if (Spell == Q)
		{
			return QSpeed;
		}
		if (Spell == W)
		{
			return WSpeed;
		}
		if (Spell == E)
		{
			return ESpeed;
		}
		if (Spell == R)
		{
			return RSpeed;
		}
		return 0.f;
	};
	static float GetSpellDelay(SpellSlotID Spell) {
		if (Spell == Q)
		{
			return QDelay;
		}
		if (Spell == W)
		{
			return WDelay;
		}
		if (Spell == E)
		{
			return EDelay;
		}
		if (Spell == R)
		{
			return RDelay;
		}
		return 0.f;
	};
	static GameObject* OriBall;
	static GameObject* GetOriBall();

	static int Combo();
	static int Harrass();
	static int Laneclear();
	static int Lasthit();

	static int Rotation();
};