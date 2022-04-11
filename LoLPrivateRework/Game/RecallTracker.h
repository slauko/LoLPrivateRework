#pragma once
#include "../Includes.h"
class RecallTracker {
public:
	static GameObject* RecallTarget[10];
	static float  starttime[10];

	static bool Init;
	static LPD3DXFONT D3D_Font;
	static D3DCOLOR TextColor;

	static void FillRGB(LPDIRECT3DDEVICE9 pDevice , float x, float y, float w, float h, int r, int g, int b, int a);
	static void DrawRecall(LPDIRECT3DDEVICE9 pDevice);
};