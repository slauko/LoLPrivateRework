#pragma once
#include "Offsets.h"
#include "Engine.h"
#include "../Overlay/Settings.h"
#include "../Obfuscation.h"

// GameFunctions
//#define TARGET_GAMEVERSION "Version 8.24.255.8524 [PUBLIC]"
//#define oGetAttackDelay 0x5994E0 //
//#define oGetAttackCastDelay 0x599400 // 
//#define oDrawCircle 0x588780 //
//#define oIsAlive 0x1E01A0 //
//#define oIsTurret 0x227FD0 //
//#define oIsMinion 0x227E40 //
//#define oIsHero 0x227E00 //
//#define oIsTargetable 0x222170 //
//#define oIssueOrder 0x1BD6C0 //
//#define oGetSpellState 0x585EF0 //
//#define oCastSpell 0x590BF0
// GameObjects
//#define oLocalPlayer 0x2ED2BC0 //
//#define oObjManager 0x2ED1C08 //
//#define oGameTime 0x2ECE2E8 //
//#define oGameVersion 0x2EDB800

// GameObject Offsets
#define oObjTeam 0x0044
#define oObjName 0x0060
#define oObjNetworkID 0xB8 //0x110 //
#define oObjPos 0x019C
#define oObjSourceIndex 0x24C
#define oObjTargetID 0x298 
#define oObjVisibility 0x39C
#define oObjMana 0x03F8
#define oObjMaxMana 0x0408
#define oObjAmmo 0x0458
#define oObjRecallState 0xDA4
#define oObjHealth 0xDC4
#define oObjMaxHealth 0xDD4
#define oObjBonusAtk 0x11C0
#define oObjBonusAP 0x11D0
#define oObjBaseAtk 0x1240
#define oObjCritMod 0x1264
#define oObjArmor 0x1268
#define oObjMR 0x1270
#define oObjBonusMR 0x1274
#define oObjMoveSpeed 0x1280
#define oObjAtkRange 0x1288

#define oObjDirection 0x1B34

#define oObjBuffmanager 0x20F0
#define oObjSpellBook 0x28A8
#define oObjChampionName 0x3158 
#define oObjLevel 0x49EC

#define oObjSpellStartPos 0x264
#define oObjSpellEndPos 0x270

// BuffManager
#define O_BUFFMGR_TYPE 0x4
#define O_BUFFMGR_BUFFNAME 0x8
#define O_BUFFMGR_STARTTIME 0xC
#define O_BUFFMGR_ENDTIME 0x10
#define O_BUFFMGR_flBUFFCOUNT 0x30//0x2C
#define O_BUFFMGR_iBUFFCOUNT 0x74
// AIManager
#define O_AIMGR_TARGETPOS 0x10
#define O_AIMGR_ISMOVING 0x198
#define O_AIMGR_ISDASHING 0x1E8
#define O_AIMGR_NAVBEGIN 0x1BC //NOT VERIFIED
#define O_AIMGR_NAVEND 0x1C0 //NOT VERIFIED
#define O_AIMGR_HASNAVPATH 0x19C //NOT VERIFIED
#define O_AIMGR_CURRENTPOS 0x2BC //NOT VERIFIED
#define O_AIMGR_VELOCITY 0x2C8 //NOT VERIFIED


//// 9.1
//#define oGetAttackDelay 0x589BA0
//#define oGetAttackCastDelay 0x589AC0
//#define oDrawCircle 0x578960
//#define oIssueOrder 0x1BCA40
//#define oIsMinion 0x226BD0
//#define oIsHero 0x226B90
//#define oIsTargetable 0x220EB0
//#define oCastSpell 0x581020 
//#define oUpdateChargeableSpell 0x583AC0
//
//#define oWorld2Screen 0x7A7FB0
//
//#define oHudInstance 0x15CE9CC //
//
//#define oObjectManager 0x2E76C88
//#define oLocalPlayer 0x2E774E8
//#define oGameTime 0x2E73400

//// 9.2
//#define oPrintChat 0x5C9570
//#define oGetAttackDelay 0x597D10
//#define oGetAttackCastDelay 0x597C30
//#define oDrawCircle 0x587920
//#define oBaseDrawPosition 0x1B3E70
//#define oIsAlive 0x1DFA00
//#define oIsInhib 0x227810
//#define oIsNexus 0x227910
//#define oIsTroy 0x227C50
//#define oIsTurret 0x227B60
//#define oIsBaron 0x215C90
//#define oIsDragon 0x215040
////#define oIsMinion 0x2279D0
////#define oIsHero 0x227990
//#define oIsMissile 0x2279F0
////#define oIsTargetable 0x221CC0
////#define oIssueOrder 0x1BCEB0
//#define oGetSpellState 0x585080
//#define oCastSpell 0x590D20
//#define oUpdateChargeableSpell 0x593790
//
//#define oWorld2Screen 0x7BA640
//
//#define oLocalPlayer 0x2E996BC
//#define oObjectManager 0x2E99120
//#define oGameTime 0x2E957C8
//#define oGameVersion 0x2EA2EC0
//#define oZoomClass 0x2E955E4
//#define oChatClientPtr 0x15EE7B0
//#define oHudInstance 0x15F0E48
//
//#define oRenderer 0x2EB51D4
//#define oScreenWidth 0x18
//#define oScreenHeight 0x1C
//#define oViewMatrix 0x64
//#define oProjection 0xA4
//
////9.2.2
//
//#define oIssueOrder 0x1BCEE0
//#define oIsHero 0x2279B0
//#define oIsMinion 0x2279F0 
//#define oIsTargetable 0x221CE0

//9.3

//#define oPrintChat 0x5CD130
//#define oDrawCircle 0x58B200
//#define oBaseDrawPosition 0x1B15B0
//#define oWorldToScreen	0x7C47E0
//#define oUnderMouseObject 0x2268564
//#define oIsAlive 0x1DBAD0
//#define oIsInhib 0x227600
//#define oIsNexus 0x227700
//#define oIsTroy 0x227A40
//#define oIsTurret 0x227950
//#define oIsBaron 0x215240
//#define oIsDragon 0x214460
//#define oIsMinion 0x2277C0
//#define oIsHero 0x227780
//
//#define oIsWall 0x7373C0
//
//#define oIsMissile 0x2277E0
//#define oIsTargetable 0x221960
//#define oIssueOrder 0x1B9E60
//#define oGetAttackDelay 0x59B980
//#define oGetAttackCastDelay 0x59B8A0
//#define oGetBasicAttack	0x1B06E0
//#define oGetSpellState 0x588970
//#define oCastSpell 0x594740
//#define oUpdateChargeableSpell 0x5972D0

//#define oIssueOrder 0x1B9E60   
//#define oGetAttackDelay 0x59B980 
//#define oGetAttackCastDelay 0x59B8A0 
//#define oCastSpell 0x594740 
//#define oUpdateChargeableSpell 0x5972D0
//#define oDrawCircle 0x58B200
//#define oIsHero 0x227780 
//#define oIsMinion 0x2277C0  
////#define oWorld2Screen 0x7C47B0
//#define oIsTargetable 0x221960 

//#define oRenderer 0x2EDC604 
//#define oLocalPlayer 0x2EC1870  
//#define oObjectManager 0x2EC0508
//#define oUnderMouseObject 0x2268524 
//#define oHudInstance 0x1618248 
//#define oGameTime 0x2EBCBF0


//9.3.2
//#define oWorld2Screen 0x7C47E0
//#define oRenderer 0x2EDC644 
//#define oLocalPlayer 0x2EC18B0  
//#define oObjectManager 0x2EC0548
//#define oUnderMouseObject 0x2268564 
//#define oHudInstance 0x1618288 
//#define oGameTime 0x2EBCC30

//
////9.4
//#define oPrintChat 0x5DA690
//#define oDrawCircle 0x598C00
//#define oBaseDrawPosition 0x1B2DA0
//#define oWorld2Screen 0x7D3E20
//#define oUnderMouseObject 0x22D4B84
//#define oIsAlive 0x1E08C0
//#define oIsInhib 0x224B50
//#define oIsNexus 0x224C50
//#define oIsTroy 0x224F90
//#define oIsTurret 0x224EA0
//#define oIsBaron 0x214630
//#define oIsDragon 0x213900
//#define oIsMinion 0x224D10
//#define oIsHero 0x224CD0
//#define oIsMissile 0x224D30
//#define oIsTargetable 0x21DB90
//#define oIssueOrder 0x1BC3D0
//#define oGetAttackDelay 0x5A8CD0
//#define oGetAttackCastDelay 0x5A8BF0
//#define oGetBasicAttack 0x1B1D30
//#define oGetSpellState 0x596370
//#define oCastSpell 0x5A1DC0
//#define oUpdateChargeableSpell 0x5A47A0
//#define oChatClientPtr 0x1681D6C
//
//#define oIsWall 0x746A00
//
//
//#define oLocalPlayer 0x2F2F4F8
//#define oObjectManager 0x2F2EF60
//#define oHudInstance 0x16843C8
//#define oRenderer 0x2F4BFB4
//#define oZoomClass 0x2F2B414
//#define oGameTime 0x2F2B5F0
//#define oGameVersion 0x2F39620

////9.5
//#define oDrawCircle 0x5A7940
//#define oWorld2Screen 0x7E4CE0
//
//#define oIsTurret 0x226770
//#define oIsMinion 0x2265E0
//#define oIsHero 0x2265A0
//#define oIsMissile 0x226600
//#define oIsTargetable 0x21F600
//
//#define oIssueOrder 0x1BE3D0
//#define oGetAttackDelay 0x5B8030
//#define oGetAttackCastDelay 0x5B7F50
//#define oGetBasicAttack 0x1B3960
//
//#define oCastSpell 0x5AF790
//#define oUpdateChargeableSpell 0x5B1F60
//
//#define oIsWall 0x7576A0
//
//
//#define oLocalPlayer 0x2F407EC
//#define oObjectManager 0x2F3FF78
//#define oHudInstance 0x1695410
//#define oGameTime 0x2F3C6E8

////9.6
//#define oDrawCircle 0x5A7420
//#define oWorld2Screen 0x7E55F0
//
//#define oIsMinion 0x2271F0
//#define oIsHero 0x2271B0
//#define oIsMissile 0x227210
//#define oIsTargetable 0x21FEB0
//
//#define oIssueOrder 0x1BE7B0
//#define oGetAttackDelay 0x5B7B30
//#define oGetAttackCastDelay 0x5B7A50
//#define oGetBasicAttack 0x1B3D10
//
//#define oCastSpell 0x5AF100
//#define oUpdateChargeableSpell 0x5B1890
//
//#define oIsWall 0x758340
//
//
//#define oLocalPlayer 0x2F43900 //
//#define oObjectManager 0x2F43098 //
//#define oHudInstance 0x16984D0
//#define oChatClient 0x1695CC0
//
//#define oGameTime 0x2F3F7B0

////9.7
//#define oLocalPlayer 0x2F26120
//#define oObjectManager 0x16466F8
//
//#define oIsHero 0x226EC0
//#define oIsMinion 0x226F00
//#define oIsTargetable 0x21FB80
//#define oIsMissile 0x226F20
//
//#define oIssueOrder 0x1BE660
//#define oGetBasicAttack 0x1B39C0
//#define oGetAttackCastDelay 0x5A5FE0
//#define oGetAttackDelay 0x5A60C0
//
//#define oDrawCircle 0x596D40
//#define oCastSpell 0x59F3B0
//#define oUpdateChargeableSpell 0x5A1B10
//#define oIsWall 0x748840
//#define oWorld2Screen 0x7D59E0
//
//#define oHudInstance 0x168773C
//#define oGameTime 0x2F22148
//#define oChatClient 0x1685054
//#define oRenderer 0x2F43C1C

////9.8
//#define oCastSpell 0x5B6AD0 // 9.8 f
//#define oIsTroy 0x2283C0 // 9.8 f
//#define oIsMissile 0x228140 // 9.8 f
//#define oIsWall 0x7657E0 // 9.8 f
//#define oIsTargetable 0x220A80 // 9.8 f
//#define oIsNexus 0x228060 // 9.8 f
//#define oIsHero 0x2280E0 // 9.8 f
//#define oDrawCircle 0x5AE700 // 9.8 f
//#define oIsDragon 0x2160D0 // 9.8 f
//#define oUpdateChargeableSpell 0x5B9280 // 9.8 f
//#define oIsMinion 0x228120 // 9.8 f
//#define oIsBaron 0x216C80 // 9.8 f
//#define oIsAlive 0x1E3D80 // 9.8 f
//#define oIsInhib 0x227F60 // 9.8 f
//#define oPrintChat 0x5F1740 // 9.8 f
//#define oGetBasicAttack 0x1B43D0 // 9.8 f
//#define oIssueOrder 0x1BEE10 // 9.8 f
//#define oIsTurret 0x2282D0 // 9.8 f
//#define oGetAttackDelay 0x5BD350 // 9.8 f
//#define oGetAttackCastDelay 0x5BD270 // 9.8 f
//#define oGetSpellState 0x5AAAA0 // 9.8 f
//#define oWorld2Screen 0x7F2EE0 // 9.8 f
//#define oGetPing 0x35A300 // 9.8 f
//
//#define oRenderer 0x2F62FF4 // 9.8 f
//#define oChatClient 0x16A42E0 // 9.8 f
//#define oGameVersion 0x2F50530 // 9.8 f
//#define oObjectManager 0x16656F4 // 9.8 f
//#define oLocalPlayer 0x2F457FC // 9.8 f
//#define oGameTime 0x2F41498 // 9.8 f
//#define oZoomClass 0x2F413F4 // 9.8 f
//#define oHudInstance 0x16A6AA4 // 9.8 f
//#define oNetClient 0x2F4A538 // 9.8 f
//#define oUnderMouseObject 0x22F725C // 9.8 f
//#define oGameInfo 0x2F42980 // 9.8 f

////9.9
//#define oCastSpell 0x59DC80 // Works
//#define oIsMissile 0x227DC0
//#define oIsTargetable 0x220690
//#define oIsHero 0x227D60 // Works
//#define oDrawCircle 0x595ED0
//#define oIsDragon 0x215DE0
//#define oIsMinion 0x227DA0
//#define oIsBaron 0x216990 
//#define oIsAlive 0x1E3A20
//#define oIssueOrder 0x1BF5B0 // Works
//#define oGetAttackDelay 0x5A41A0 // Works
//#define oGetAttackCastDelay 0x5A40C0 // Works
//#define oGetSpellState 0x5923E0 // Works
//
//#define oGetBasicAttack 0x1B4690 
//
//#define oUpdateChargeableSpell 0x5A0470
//#define oWorld2Screen 0x7DA1E0
//#define oIsWall 0x74C690
//
//#define oObjectManager 0x164C524// Works
//#define oLocalPlayer 0x2F2AFA4 // Works
//#define oHudInstance 0x168C1A4 // Works
//
//#define oChatClient 0x1689AB8
//#define oGameTime 0x2F26BA8

//9.10
#define oCastSpell 0x5BEBE0 // 9.10
#define oUpdateChargeableSpell 0x5C0DB0
#define oIsWall 0x770170
#define oIsTroy 0x224FD0 //9.10
#define oIsMissile 0x224D50 //9.10
#define oDrawCircle 0x5B7B10 //9.10
#define oIsDragon 0x212B90 //9.10
#define oIsMinion 0x224D30 //9.10
#define oIsHero 0x224CF0
#define oIsBaron 0x212B9E // 9.10
#define oIsAlive 0x1E0750 //9.10
#define oIsTargetable 0x21D920 //9.10 

#define oIssueOrder 0x1BC510 //9.10
#define oIsTurret 0x224EE0 //9.10
#define oGetBasicAttack 0x1B15C0
#define oGetAttackDelay 0x5C52B0 // 9.10
#define oGetAttackCastDelay 0x5C51D0 //9.10
#define oGetSpellState 0x5B28A0 //9.10
#define oWorld2Screen 0x7FE0B0 // 9.10

#define oObjectManager 0x1678564 //9.10
#define oLocalPlayer 0x2F57094// 9.10
#define oHudInstance 0x16B866C //9.10
#define oGameTime 0x2F534D8
#define oChatClient 0x16B5EC4

void Offsets::D3DHook() {
	DWORD *pD3DInterface = *(DWORD**)(Engine::BaseAddress + 0x2F7C6AC); // <<<<< INSERT NEW DX9Query Device PTR HERE , EVERY PATCH
	DWORD *pDevice = *(DWORD**)((DWORD)pD3DInterface + 0x1A0);
	pDeviceVTable = *(DWORD**)pDevice;

	if (!pEndScene)
	{
		pEndScene = (fnEndScene)(pDeviceVTable[42]);
	}

	DWORD oldProt, newProt;
	VirtualProtect(pDeviceVTable, 0x400, PAGE_READWRITE, &oldProt);
	pDeviceVTable[42] = (DWORD)hkEndSceneAddy;
	VirtualProtect(pDeviceVTable, 0x400, oldProt, &newProt);

	//std::cout << "D3DHook!" << std::endl;
}
void Offsets::Init() {
	//Init Addys
	Engine::BaseAddress = (DWORD)(GetModuleHandleA(NULL));
	Engine::GameTime = (float*)(Engine::BaseAddress + oGameTime);
	Engine::pLPBase = (LocalPlayerBase*)(Engine::BaseAddress + oLocalPlayer);
	Engine::pObjMngrBase = (ObjectManagerBase*)(Engine::BaseAddress + oObjectManager);
	Engine::pHUDBase = (pHudInstanceBase*)(Engine::BaseAddress + oHudInstance);
	Engine::ChatClient = *(ChatClient**)(Engine::BaseAddress + oChatClient);
	//Init Functions
	Engine::GetSpellstate = (Engine::_GetSpellstate)(Engine::BaseAddress + oGetSpellState);
	Engine::CastSpell = (Engine::_CastSpell)(Engine::BaseAddress + oCastSpell);
	Engine::UpdateChargeableSpell = (Engine::_UpdateChargeableSpell)(Engine::BaseAddress + oUpdateChargeableSpell);

	Engine::IssueOrder = (Engine::_IssueOrder)(Engine::BaseAddress + oIssueOrder);
	Engine::GetAttackDelay = (Engine::_GetAttackDelay)(Engine::BaseAddress + oGetAttackDelay);
	Engine::GetAttackCastDelay = (Engine::_GetAttackCastDelay)(Engine::BaseAddress + oGetAttackCastDelay);
	Engine::DrawCircle = (Engine::_DrawCircle)(Engine::BaseAddress + oDrawCircle);
	//Engine::IsAlive = (Engine::_IsAlive)(Engine::BaseAddress + oIsAlive);
	//Engine::IsTurret = (Engine::_IsTurret)(Engine::BaseAddress + oIsTurret);

	Engine::IsMissile = (Engine::_IsMissile)(Engine::BaseAddress + oIsMissile);
	Engine::IsMinion = (Engine::_IsMinion)(Engine::BaseAddress + oIsMinion);
	Engine::IsHero = (Engine::_IsHero)(Engine::BaseAddress + oIsHero);
	Engine::IsTargetable = (Engine::_IsTargetable)(Engine::BaseAddress + oIsTargetable);

	Engine::World2Screen = (Engine::_World2Screen)(Engine::BaseAddress + oWorld2Screen);
	Engine::GetBasicAttack = (Engine::_GetBasicAttack)(Engine::BaseAddress + oGetBasicAttack);
	Engine::IsWall = (Engine::_IsWall)(Engine::BaseAddress + oIsWall);
	//Shorten some shit
	Engine::pLocalPlayer = Engine::pLPBase->pLocalPlayer;
	Engine::pObjectManager = Engine::pObjMngrBase->pObjectManager;
	Engine::pMouse = Engine::pHUDBase->pHudInstance->pMouse;

	//Engine::pLocalPlayer->ListVTable();
	Engine::SpellDataBase.LoadDataBase();
	std::cout << Engine::SpellDataBase.Spells.size() << " Spells loaded to DataBase." << std::endl;
	std::cout << "Loaded offsets.." << std::endl;
	//Settings create/load
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	std::string targetFile = "settings.ini";
	hFind = FindFirstFile("settings.ini", &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		for (int i = 0; i < 30; i++) {
			if (FindNextFile(hFind, &FindFileData)) {
				break;
			}
			else {
				continue;
			}
		}
		if (hFind == INVALID_HANDLE_VALUE) {
			std::cout << "No SettingsFile found, creating new one." << std::endl;
			Settings::createSettingsFile();
		}
	}
	else {
		std::cout << "SettingsFile found...loading!" << std::endl;
		Settings::LoadSettings();
	}

	//Init clocks
	Engine::movetimer = clock();
	Engine::attacktimer = clock();
	Engine::clickertimer = clock();
	//EndScene Hook

	//VTABLEHOOK START
	D3DHook();
	//VTABLEHOOK FINISHED	
}


template<typename Function> Function CallVirtual(PVOID Base, DWORD Index)
{
	PDWORD* VTablePointer = (PDWORD*)Base;
	PDWORD VTableFunctionBase = *VTablePointer;
	DWORD dwAddress = VTableFunctionBase[Index];

	return (Function)(dwAddress);
}

bool BuffEntry::IsValid() {
	float GameTime = *(float*)((DWORD)GetModuleHandleA(NULL) + oGameTime);
	if (this->GetBuffCountAlt() > 0 && GameTime < this->GetBuffEndTime())
		return true;

	return false;
}
BuffType BuffEntry::GetBuffType() {
	return *(BuffType*)((DWORD)this + O_BUFFMGR_TYPE);
}
float BuffEntry::GetBuffStartTime() {
	return *(float*)((DWORD)this + O_BUFFMGR_STARTTIME);
}
float BuffEntry::GetBuffEndTime() {
	return *(float*)((DWORD)this + O_BUFFMGR_ENDTIME);
}
int BuffEntry::GetBuffCountAlt() {
	return (*(int*)((DWORD)this + 0x24) - *(int*)((DWORD)this + 0x20)) >> 3;
}
float BuffEntry::GetBuffCountFloat() {
	return *(float*)((DWORD)this + O_BUFFMGR_flBUFFCOUNT);
}
int BuffEntry::GetBuffCountInt() {
	return *(int*)((DWORD)this + O_BUFFMGR_iBUFFCOUNT);
}
const char* BuffEntry::GetBuffName() {
	DWORD aux = *(DWORD*)((DWORD)this + O_BUFFMGR_BUFFNAME);
	if (aux == NULL)
		return "NULL";

	if (*(DWORD*)(aux + O_BUFFMGR_BUFFNAME) == NULL)
		return "NULL";

	return (char*)(aux + O_BUFFMGR_BUFFNAME);
}


DWORD BuffManager::GetBuffArrayStart() {
	return *(DWORD*)((DWORD)this + 0x10);
}
DWORD BuffManager::GetBuffArrayEnd() {
	return *(DWORD*)((DWORD)this + 0x14);
}
bool BuffManager::HasBuffType(BuffType Type) {
	for (DWORD pBuffPtr = this->GetBuffArrayStart(); pBuffPtr != this->GetBuffArrayEnd(); pBuffPtr += 0x8)
	{
		auto pBuff = *(BuffEntry**)pBuffPtr;
		if (!pBuff->IsValid()) continue;

		if (pBuff) {
			if (pBuff->GetBuffType() == Type) {
				//cout << pBuff->GetBuffName() << endl;
				return true;
			}
		}
	}
	return false;
}
BuffEntry* BuffManager::GetBuffEntryByName(const char* BuffName) {
	for (DWORD pBuffPtr = this->GetBuffArrayStart(); pBuffPtr != this->GetBuffArrayEnd(); pBuffPtr += 0x8)
	{
		auto pBuff = *(BuffEntry**)pBuffPtr;
		if (!pBuff->IsValid()) continue;

		if (pBuff) {
			if (!strcmp(pBuff->GetBuffName(), BuffName)) {
				return pBuff;
			}
		}
	}
	return NULL;
}
void BuffManager::DEBUG_SHOWALLBUFFS() {
	for (DWORD pBuffPtr = this->GetBuffArrayStart(); pBuffPtr != this->GetBuffArrayEnd(); pBuffPtr += 0x8)
	{
		auto pBuff = *(BuffEntry**)pBuffPtr;
		if (!pBuff->IsValid()) continue;

		if (pBuff) {
			if (pBuff->GetBuffCountAlt())
			{
				std::cout << pBuff->GetBuffName() << std::endl;

			}
		}
	}
	std::cout << "---------------" << std::endl;
}
int BuffManager::HasBuff(const char* BuffName) {
	for (DWORD pBuffPtr = this->GetBuffArrayStart(); pBuffPtr != this->GetBuffArrayEnd(); pBuffPtr += 0x8)
	{
		auto pBuff = *(BuffEntry**)pBuffPtr;
		if (!pBuff->IsValid()) continue;

		if (pBuff) {
			if (!_strcmpi(pBuff->GetBuffName(), BuffName)) {
				if (pBuff->GetBuffCountAlt())
				{
					return pBuff->GetBuffCountAlt();
				}
			}
		}
	}
	return 0;
}


float SpellDataInst::GetSpellSpeed() {
	return *(float*)((DWORD)this + 0x174);
}


SpellDataInst* SpellData::GetSpellDataInst() {
	return *(SpellDataInst**)((DWORD)this + 0x94);
}
float SpellData::GetMissileSpeed() {
	return *(float*)((DWORD)this + 0x440);
}


LoLString SpellInfo::GetSpellName() {
	return *(LoLString*)((DWORD)this + 0x18);
}
SpellData* SpellInfo::GetSpellData() {
	return *(SpellData**)((DWORD)this + 0x38);
}

	
SpellInfo* SpellEntry::GetActiveSpellInfo() {
	return *(SpellInfo**)((DWORD)this + 0x8);
}
int SpellEntry::GetSpellCounter() {
	return *(int*)((DWORD)this + 0x58);
}
Vector3 SpellEntry::GetSpellStartPos() {
	return *(Vector3*)((DWORD)this + 0x7C);
}
Vector3 SpellEntry::GetSpellEndPos() {
	return *(Vector3*)((DWORD)this + 0x88);
}
Vector3 SpellEntry::GetSpellCastPos() {
	return *(Vector3*)((DWORD)this + 0x94);
}
short SpellEntry::GetCastState() {
	return *(short*)((DWORD)this + 0x4D3);
}

int Spell::GetSpellLevel() {
	return *(int*)((DWORD)this + 0x20);
}
float Spell::GetSpellCooldown1() {
	return *(float*)((DWORD)this + 0x28);
}
int Spell::GetSpellCharges() {
	return *(int*)((DWORD)this + 0x58);
}
float Spell::GetSpellCooldown2() {
	return *(float*)((DWORD)this + 0x5C);
}
float Spell::GetSpellMaxCooldown() {
	return *(float*)((DWORD)this + 0x70);
}
float Spell::GetSpellMaxCooldown2() {
	return *(float*)((DWORD)this + 0x6C);
}
float Spell::GetSmiteDamage()
{
	return *(float*)((DWORD)this + 0x90);
}
float Spell::GetStartTime() {
	return *(float*)((DWORD)this + 0x100);
}
SpellInfo* Spell::GetSpellInfo() {
	return *(SpellInfo**)((DWORD)this + 0x134);
}
Vector3 Spell::GetSpellStartPos() {
	return *(Vector3*)((DWORD)this + 0x2E4);
}
Vector3 Spell::GetSpellEndPos() {
	return *(Vector3*)((DWORD)this + 0x2F0);
}


SpellEntry* SpellBook::GetActiveSpellEntry() {
	return *(SpellEntry**)((DWORD)this + 0x20);
}
float SpellBook::GetManaCost(int index) {
	return *(float*)((DWORD)this + 0x58 + (0x10 * index));
}
Spell* SpellBook::GetSpellSlot(int index) {
	return *(Spell**)((DWORD)this + 0x508 + (0x4 * index));
}


Vector3 CAIManager::TargetPos() {
	return *(Vector3*)((DWORD)this + O_AIMGR_TARGETPOS);
}
bool CAIManager::IsMoving() {
	return *(bool*)((DWORD)this + O_AIMGR_ISMOVING);
}
bool CAIManager::IsDashing() {
	return *(bool*)((DWORD)this + O_AIMGR_ISDASHING);
}
Vector3* CAIManager::GetNavBegin() {
	return *(Vector3**)((DWORD)this + O_AIMGR_NAVBEGIN);
}
Vector3* CAIManager::GetNavEnd() {
	return *(Vector3**)((DWORD)this + O_AIMGR_NAVEND);
}
Vector3 CAIManager::CurrentPos() {
	return *(Vector3*)((DWORD)this + O_AIMGR_CURRENTPOS);
}
Vector3 CAIManager::Velocity() {
	return *(Vector3*)((DWORD)this + O_AIMGR_VELOCITY);
}



int GameObject::GetTeam() {
	return *(int*)((DWORD)this + oObjTeam);
}
LoLString GameObject::GetName() {
	return *(LoLString*)((DWORD)this + oObjName);
}
int GameObject::GetNetworkID() {
	return *(int*)((DWORD)this + oObjNetworkID);
}
Vector3 GameObject::GetPosition() {
	return *(Vector3*)((DWORD)this + oObjPos);
}
short GameObject::GetSourceIndex() {
	return *(short*)((DWORD)this + oObjSourceIndex);
}
short GameObject::GetTargetID() {
	return *(short*)((DWORD)this + oObjTargetID);
}
int GameObject::GetVisibility() {
	return *(int*)((DWORD)this + oObjVisibility);
}
float GameObject::GetMana() {
	return *(float*)((DWORD)this + oObjMana);
}
float GameObject::GetMaxMana() {
	return *(float*)((DWORD)this + oObjMaxMana);
}
float GameObject::GetAmmo() {
	return *(float*)((DWORD)this + oObjAmmo);
}
int GameObject::GetRecallState() {
	return *(int*)((DWORD)this + oObjRecallState);
}
float GameObject::GetHealth() {
	return *(float*)((DWORD)this + oObjHealth);
}
float GameObject::GetMaxHealth() {
	return *(float*)((DWORD)this + oObjMaxHealth);
}
float GameObject::GetBonusAtk() {
	return *(float*)((DWORD)this + oObjBonusAtk);
}
float GameObject::GetBonusAP() {
	return *(float*)((DWORD)this + oObjBonusAP);
}
float GameObject::GetBaseAtk() {
	return *(float*)((DWORD)this + oObjBaseAtk);
}
float GameObject::GetCritMod() {
	return *(float*)((DWORD)this + oObjCritMod);
}
float GameObject::GetArmor() {
	return *(float*)((DWORD)this + oObjArmor);
}
float GameObject::GetMR() {
	return *(float*)((DWORD)this + oObjMR);
}
float GameObject::GetMoveSpeed() {
	return *(float*)((DWORD)this + oObjMoveSpeed);
}
float GameObject::GetAttackRange() {
	return *(float*)((DWORD)this + oObjAtkRange);
}
Vector3 GameObject::GetDirection() {
	return *(Vector3*)((DWORD)this + oObjDirection);
}
LoLString GameObject::GetChampionName() {
	return *(LoLString*)((DWORD)this + oObjChampionName);
}
BuffManager* GameObject::GetBuffManager() {
	return (BuffManager*)((DWORD)this + oObjBuffmanager);
}
SpellBook* GameObject::GetSpellbook() {
	return (SpellBook*)((DWORD)this + oObjSpellBook);
}
int GameObject::GetLevel() {
	return *(int*)((DWORD)this + oObjLevel);
}
float GameObject::GetAAMissleSpeed() {
	typedef int(__thiscall* _GetBasicAttack)(GameObject* Player, int index);
	_GetBasicAttack GetBasicAttack = (_GetBasicAttack)((DWORD)GetModuleHandleA(NULL) + oGetBasicAttack);
	SpellInfo* BasicAttack = *(SpellInfo**)GetBasicAttack(this, 64);
	return BasicAttack->GetSpellData()->GetMissileSpeed();
}
Vector3 GameObject::GetMissileStartPos() {
	return *(Vector3*)((DWORD)this + oObjSpellStartPos);
}
Vector3 GameObject::GetMissileEndPos() {
	return *(Vector3*)((DWORD)this + oObjSpellEndPos);
}
float GameObject::GetBoundingRadius() {
	typedef float(__thiscall* OriginalFn)(PVOID);
	return CallVirtual<OriginalFn>(this, 36)(this);
}
CAIManager* GameObject::GetAIManager() {
	typedef CAIManager*(__thiscall* OriginalFn)(PVOID);
	return CallVirtual<OriginalFn>(this, 147)(this);
}
void GameObject::ListVTable() {
	//DWORD vtable = *(DWORD*)this->GetSpellbook();
	//cout << hex << vtable << endl;
	for (int i = 35; i < 500; i++)
	{
		//DWORD vtblentry = *(DWORD*)(vtable + (i * 4));
		typedef float(__thiscall* OriginalFn)(PVOID);
		//return CallVirtual<OriginalFn>(this, 36)(this);
		//cout << dec << "VTable["<< i << "]: " << hex << vtblentry << endl;

		try {
			std::cout << "VTable[" << i << "]: " << CallVirtual<OriginalFn>(this, i)(this) << std::endl;
		}
		catch (...)
		{

		}



		//if (vtblentry == ((DWORD)(GetModuleHandleA(NULL)) + 0x596450))
		//{
		//	cout << dec << "OnProcessSpell FOUND AT VTABLE[" << i << "]" << endl;
		//}
	}
}