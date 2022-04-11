#pragma once
#include <map>
#include <string>

enum CollisionType {
	Minion,
	Champion,
	Wall,
	YasuoWall
};

enum _SpellType {
	linear, conic, circular, threeway, rectangular, annular, unknown_type
};

enum SpellSlotID {
	Q, W, E, R, D, F, Item1, Item2, Item3, Item4, Item5, Item6, Trinket, Recall, Unknown_Slot
};

class SpellDataInfo {
public:
	SpellSlotID slot;
	_SpellType type;
	float speed;
	float range;
	float delay;
	float radius;
	float angle;
	int danger;
	bool cc;
	bool collision;
	bool windwall;
	SpellDataInfo();
	SpellDataInfo(
		SpellSlotID slot,
		_SpellType type,
		float speed,
		float range,
		float delay,
		float radius,
		int danger,
		bool cc,
		bool collision,
		bool windwall
	);
	SpellDataInfo(
		SpellSlotID slot,
		_SpellType type,
		float speed,
		float range,
		float delay,
		float radius,
		float angle,
		int danger,
		bool cc,
		bool collision,
		bool windwall
	);
};

class SpellDataBase {
public:
	std::map<std::string, SpellDataInfo*> Spells;
	void LoadDataBase();
};
