#pragma once
#include "Offsets.h"
class CDTracker {
public:
	static bool Init;
	static LPD3DXFONT D3D_Font;
	static D3DCOLOR TextColor;
	static std::string GetSummonerSpellName(Spell* Slot);
	static void DrawCooldowns(LPDIRECT3DDEVICE9 pDevice);
};