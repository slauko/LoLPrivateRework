#pragma once
#include "Offsets.h"
#include "SpellDataBase.h"

class Engine {
public:
	static bool OlafSelected;
	static bool YasuoSelected;

	static bool ForceEvade;
	static bool BlockAA;
	static Vector3 EvadePos;
	static bool AlwaysEvade;
	static bool FirstMoveAfterAA;
	static bool AfterAAReset;
	static bool AfterAA;
	static float LastDash;
#pragma region utility
	static void DrawAroundObject(GameObject* Object, float range, DWORD* color);
	static bool SpellReady(SpellSlotID Slot);
	static SpellSlotID getSmiteSlot(SpellBook* Spellbook);
	static SpellSlotID getBladeSlot(SpellBook* Spellbook);
	static SpellSlotID getHydraSlot(SpellBook* Spellbook);
	static SpellSlotID getPotionSlot(SpellBook* Spellbook);
	static float GetDistance3D(Vector3 Position, GameObject* Target);
	static float GetDistance3D(Vector3 From, Vector3 To);
	static bool isBigJungle(GameObject *Target);
	static bool isEpicJungle(GameObject* Target);
	static bool isDeadWard(GameObject* Object);
	static bool isWard(GameObject* Object);
	static bool isPlant(GameObject *Object);
	static float GetBuffDmgMod(GameObject* Target, float AttackDamage);
	static bool canLasthit(GameObject* Target);
	static bool IsAlreadyDead(GameObject* Target);
	static TargetMode getOrbMode();
#pragma endregion
#pragma region Orbwalker
	static void ResetMoveTimer();
	static void ResetAttackTimer();
	static void ResetClickerTimer();
	static double CalcMoveDelay();
	static double CalcAttackDelay();
	static double CalcClickerDelay();
	static double getWindup();
	static float LastMoveCommand;
	static bool MoveReady();
	static bool AAReset();
	static bool NoAutoAttack(const char* AttackName);
	static bool IsAutoAttack(const char* AttackName);
	static const char* LastAttack;
	static bool AfterSpecialAA();
	static bool IsChanneling();
	static bool AttackReady();
	static bool AACancelPossible();
	static void DEBUG_SHOWTARGETBUFFS(GameObject* Target);
	static bool ClickDelay(float delay);
	static int Orbwalk(GameObject* Target);
	static int OrbBot();
#pragma endregion

	//typedef int(__thiscall* _fnChatCommand)(Chat*, std::string*);
	//typedef int(__thiscall* _fnPrintChat)(ChatClient*, const char* Message, int type); // 0 orange, 4 white
	//typedef int(__thiscall* _fnSendChat)(const char* Message, int a);
	//typedef void(__thiscall* _fnGameUpdate)(); // i don't remember the argument actually so be careful
	//typedef int(__thiscall* _fnCreateObj)(GameObject*, DWORD);
	//typedef int(__stdcall* _fnDeleteObj)(GameObject*);
	//typedef int(__thiscall* _fnUpdateBuff)(BuffInstance*, GameObject*, int, float, char*);
	//typedef int(__thiscall* _fnRemoveBuff)(BuffInstance*);
	//typedef bool(__thiscall* _fnSellItem)(DWORD ptr, DWORD slot); // add +6 if you wanna get the real slot
	//typedef void(__thiscall* _fnLevelSpell)(DWORD ptr, int slot);
	//typedef GameObject*(__stdcall* _fnIdentifyObject)(DWORD Handle); // object+0x8 = Handle
	//typedef int(__thiscall* _fnDoEmote)(UINT8 emoteID); // from 0 to 5
	
	typedef int(__thiscall* _GetSpellstate)(SpellBook* pSpellBook, SpellSlotID slot, BYTE* null);
	typedef int(__thiscall* _CastSpell)(SpellBook* pSpellBook, Spell* pSpellslot, SpellSlotID slot, Vector3* pStartPosition, Vector3* pEndPosition, DWORD targetNetworkId);
	typedef void(__thiscall* _UpdateChargeableSpell)(SpellBook* pSpellBook, Spell* pSpellslot, SpellSlotID slot, Vector3* pPosition, bool ReleaseCast);


	typedef int(__cdecl* _DrawCircle) (Vector3* position, float range, DWORD* color, int a4, float a5, int a6, float alpha);
	typedef int(__thiscall* _IssueOrder)(GameObject* Player, DWORD MoveType, Vector3* TargetPos, GameObject* Target, DWORD, DWORD, BOOL);
	typedef float(__cdecl* _GetAttackDelay)(GameObject* pObj);
	typedef float(__cdecl* _GetAttackCastDelay)(GameObject* pObj, int index);

	typedef bool(__cdecl* _IsMissile)(GameObject* pObject);
	typedef bool(__cdecl* _IsMinion)(GameObject *pObject);
	typedef bool(__cdecl* _IsHero)(GameObject *pObject);
	typedef bool(__cdecl* _IsWall)(Vector3* Position, uint16_t index);
	typedef bool(__thiscall* _IsTargetable)(GameObject *pObject);
//	typedef bool(__cdecl* _IsAlive)(GameObject *pObject);

	typedef bool(__cdecl* _World2Screen)(Vector3* from, Vector3* to);
	typedef int(__thiscall* _GetBasicAttack)(GameObject* Player, int index);

	static SpellDataBase SpellDataBase;
	
	//---------------------------------------------------------------
	static _GetSpellstate GetSpellstate;
	static _CastSpell CastSpell;
	static int CastAimedSpell(Vector3 Position,SpellSlotID Spell);
	static int CastTargetedSpell(GameObject* Target, SpellSlotID Spell);

	//---------------------------------------------------------------
	static _UpdateChargeableSpell UpdateChargeableSpell;
	static int ReleaseSpell(Vector3 Position, SpellSlotID Spell);


	//---------------------------------------------------------------
	static _DrawCircle DrawCircle;
	static _IssueOrder IssueOrder;
	static _GetAttackDelay GetAttackDelay;
	static _GetAttackCastDelay GetAttackCastDelay;

	static _IsMissile IsMissile;
	static _IsMinion IsMinion;
	static _IsHero IsHero;
	static _IsTargetable IsTargetable;
//	static _IsAlive IsAlive;
//	static _IsTurret IsTurret;

	static _World2Screen World2Screen;
	static _GetBasicAttack GetBasicAttack;
	static _IsWall IsWall;


	static DWORD BaseAddress;
	static float *GameTime;
	static LocalPlayerBase *pLPBase;
	static ObjectManagerBase *pObjMngrBase;
	static pHudInstanceBase *pHUDBase;
	static ChatClient *ChatClient;

	static GameObject *pLocalPlayer;
	static ObjectManager *pObjectManager;
	static Mouse *pMouse;

	static GameObject* MouseObject;

	//timer statics
	static clock_t movetimer;
	static clock_t attacktimer;
	static clock_t clickertimer;
};

