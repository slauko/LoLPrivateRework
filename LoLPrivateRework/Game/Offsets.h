#pragma once
#include "../Main.h"


// HotKeys
#define SmiteKey 0x06 // Mouse_X1

// VKeys
#define VK_V 0x56
#define VK_C 0x43
#define VK_X 0x58
// MaxObjects
#define MaxObjects 10000
// GameObject type
#define ENTITY		3073
#define STRUCTURE	131077
#define CHAMPION	5121
//target_position + target_velocity * ((timetoimpact + (target_movementspeed / 2.2) * 1.5)

typedef HRESULT(__stdcall* fnEndScene)(IDirect3DDevice9*);
class Offsets {
public:
	DWORD *pDeviceVTable;
	DWORD hkEndSceneAddy;
	fnEndScene pEndScene;

	void D3DHook();
	void Init();
}static offsets;

enum MoveType
{
	Movetype_Move = 2,
	Movetype_Attack = 3,
	Movetype_Stop = 0xA
};

enum TargetMode
{
	Target_Combo = 0,
	Target_LaneClear = 1,
	Target_LastHit = 2,
	Target_Harrass = 3,
	Target_Smite = 5,
	Idle = 6
};

class Vector2 {
public:
	float x;
	float y;
};

class Vector3
{
public:
	float x;
	float y;
	float z;
	Vector3(){
		x = 0;
		y = 0;
		z = 0;
	}
	Vector3(float X, float Y,float Z) {
		x = X;
		y = Y;
		z = Z;
	}
};

class LoLString
{
public:
	union
	{
		char* strPtr; // 0x0
		char strVal[16]; // 0x0
	};
	int len; // 0x10
	int max; // 0x14

	char* c_str()
	{
		if (max >= 16)
			return strPtr;
		return strVal;
	}
};

//-------------------------------------------------------------
enum BuffType : unsigned char
{
	Internal = 0,
	Aura = 1,
	CombatEnchancer = 2,
	CombatDehancer = 3,
	SpellShield = 4,
	Stun = 5,
	Invisibility = 6,
	Silence = 7,
	Taunt = 8,
	Polymorph = 9,
	Slow = 10,
	Snare = 11,
	Damage = 12,
	Heal = 13,
	Haste = 14,
	SpellImmunity = 15,
	PhysicalImmunity = 16,
	Invulnerability = 17,
	AttackSpeedSlow = 18,
	NearSight = 19,
	Fear = 20,
	Charm = 21,
	Suppression = 22,
	Poison = 23,
	Blind = 24,
	Counter = 25,
	Currency = 26,
	Shred = 27,
	Flee = 28,
	Knockup = 29,
	Knockback = 30,
	Disarm = 31,
	Grounded = 32,
	Drowsy = 33,
	Asleep = 34
};

class BuffEntry {
public:
	bool IsValid();
	BuffType GetBuffType();
	float GetBuffStartTime();
	float GetBuffEndTime();
	int GetBuffCountAlt();
	float GetBuffCountFloat();
	int GetBuffCountInt();
	const char* GetBuffName();
};


class BuffManager {
public:
	DWORD GetBuffArrayStart();
	DWORD GetBuffArrayEnd();
	bool HasBuffType(BuffType Type);
	BuffEntry* GetBuffEntryByName(const char* BuffName);
	void DEBUG_SHOWALLBUFFS();
	int HasBuff(const char* BuffName);
};
class SpellDataInst {
public:
	float GetSpellSpeed();
};

class SpellData {
public:
	SpellDataInst* GetSpellDataInst();
	float GetMissileSpeed();
};

class SpellInfo
{
public:
	LoLString GetSpellName();
	SpellData* GetSpellData();
};

class SpellEntry
{
public:
	SpellInfo* GetActiveSpellInfo();
	int GetSpellCounter();
	Vector3 GetSpellStartPos();
	Vector3 GetSpellEndPos();
	Vector3 GetSpellCastPos();
	short GetCastState();
};

class Spell
{
public:
	int GetSpellLevel();
	float GetSpellCooldown1();
	int GetSpellCharges();
	float GetSpellCooldown2();
	float GetSpellMaxCooldown();
	float GetSpellMaxCooldown2();
	float GetSmiteDamage();
	float GetStartTime();
	SpellInfo* GetSpellInfo();
	Vector3 GetSpellStartPos();
	Vector3 GetSpellEndPos();
};

class SpellBook
{
public:
	SpellEntry* GetActiveSpellEntry();
	float GetManaCost(int index);
	Spell* GetSpellSlot(int index);
};
class CAIManager {
public:
	Vector3 TargetPos();
	bool IsMoving();
	bool IsDashing();
	Vector3* GetNavBegin();
	Vector3* GetNavEnd();
	Vector3 CurrentPos();
	Vector3 Velocity();
};

class GameObject
{
public:
	int GetTeam();
	LoLString GetName();
	int GetNetworkID();
	Vector3 GetPosition();
	short GetSourceIndex();
	short GetTargetID();
	int GetVisibility();
	float GetMana();
	float GetMaxMana();
	float GetAmmo();
	int GetRecallState();
	float GetHealth();
	float GetMaxHealth();
	float GetBonusAtk();
	float GetBonusAP();
	float GetBaseAtk();
	float GetCritMod();
	float GetArmor();
	float GetMR();
	float GetMoveSpeed();
	float GetAttackRange();
	Vector3 GetDirection();
	LoLString GetChampionName();
	BuffManager* GetBuffManager();
	SpellBook* GetSpellbook();
	int GetLevel();

	float GetAAMissleSpeed();
	Vector3 GetMissileStartPos();
	Vector3 GetMissileEndPos();
	float GetBoundingRadius();
	CAIManager* GetAIManager();
	void ListVTable();
}; //Size: 0x4AE0

class LocalPlayerBase
{
public:
	class GameObject* pLocalPlayer; //0x0000
}; //Size: 0x0004

class ObjectManager
{
public:
	class GameObject* pObjectArray[10000]; //0x0000
}; //Size: 0x9C40

class ObjectManagerBase
{
public:
	char pad_0000[8]; //0x0000
	class ObjectManager* pObjectManager; //0x0008
	int32_t iMaxObjects; //0x000C
	int32_t iObjectsUsed; //0x0010
	int32_t iHighestObjectIndex; //0x0014
}; //Size: 0x0018

class GameVersion
{
public:
	char Version[40]; //0x0000
}; //Size: 0x0028



//------------------------------------------------------------------
class Mouse
{
public:
	char pad_0000[28]; //0x0000
	Vector3 MousePos; //0x001C
	char pad_0028[60]; //0x0028
}; //Size: 0x0064

class HudInstance
{
public:
	char pad_0000[20]; //0x0000
	class Mouse* pMouse; //0x0014
	char pad_0018[80]; //0x0018
	int8_t __ignoreme; //0x0068
	char pad_0069[2]; //0x0069
	uint8_t isTabbedOut; //0x006B
}; //Size: 0x006C

class pHudInstanceBase
{
public:
	class HudInstance* pHudInstance; //0x0000
}; //Size: 0x0004

class ChatClient
{
public:
	char pad_0000[124]; //0x0000
	bool ChatOpen; //0x007C
	char pad_007D[7]; //0x007D
}; //Size: 0x0084

class ChatClientBase
{
public:
	class ChatClient* pChatClient; //0x0000
}; //Size: 0x0004
