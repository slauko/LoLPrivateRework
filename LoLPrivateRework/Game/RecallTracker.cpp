#pragma once
#include "GameIncludes.h"

bool RecallTracker::Init = false;
LPD3DXFONT RecallTracker::D3D_Font;
D3DCOLOR RecallTracker::TextColor;

void RecallTracker::FillRGB(LPDIRECT3DDEVICE9 pDevice, float x, float y, float w, float h, int r, int g, int b, int a)
{
	static ID3DXLine* pLine;

	if (!pLine)
		D3DXCreateLine(pDevice, &pLine);

	D3DXVECTOR2 vLine[2];

	pLine->SetAntialias(false);
	pLine->SetWidth(w);
	pLine->SetGLLines(true);

	vLine[1].x = x + w / 2;
	vLine[1].y = y + h;
	vLine[0].x = x + w / 2;
	vLine[0].y = y;

	pLine->Begin();
	pLine->Draw(vLine, 2, D3DCOLOR_RGBA(r, g, b, a));
	pLine->End();
}

GameObject* RecallTracker::RecallTarget[10];
float  RecallTracker::starttime[10];
void RecallTracker::DrawRecall(LPDIRECT3DDEVICE9 pDevice) {
	if (!Init)
	{
		D3DXCreateFontA(pDevice, 15, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &D3D_Font);
		TextColor = D3DCOLOR_XRGB(255, 255, 255);
		Init = !Init;
	}

	RECT NameRect;
	int index = 0;
	int menuentries = 0;

	for (GameObject* Target : TargetList::RecallList)
	{
		if (Target->GetTeam() == Engine::pLocalPlayer->GetTeam())
		{
			continue;
		}
		if (strcmp(Target->GetName().c_str(), "Target Dummy") == NULL)
		{
			continue;
		}
		RecallTarget[index] = Target;
		index++;
	}
	for (int i = 0; i < index; i++)
	{
		NameRect.left = 100;
		NameRect.right = NameRect.left + 100;
		NameRect.top = 150 + (20 * menuentries);
		NameRect.bottom = NameRect.top + 40;



		if (!RecallTarget[i])
		{
			continue;
		}
		if (RecallTarget[i]->GetRecallState() == 0) // no tp or recall just track gametime
		{
			starttime[i] = *Engine::GameTime;
		}
		if (RecallTarget[i]->GetRecallState() == 6) // recall , so duration 8
		{
			float duration = 8.f;
			float casttime = *Engine::GameTime - starttime[i];
			float timeleft = duration - casttime;
			std::stringstream outss;
			outss << std::setprecision(2) << timeleft;
			std::string output = outss.str();

			std::stringstream namess;
			namess << RecallTarget[i]->GetChampionName().c_str() << ":    " << output;
			std::string name = namess.str();

			D3D_Font->DrawTextA(NULL, name.c_str(), -1, &NameRect, 0, TextColor); // ChampName
			FillRGB(pDevice, (float)NameRect.right, (float)NameRect.top, 10.f*timeleft, 15.f, 255, 255, 255, 100);

			menuentries++;
		}
		if (RecallTarget[i]->GetRecallState() == 12) // tp , so duration 4
		{
			float duration = 4.f;
			float casttime = *Engine::GameTime - starttime[i];
			float timeleft = duration - casttime;
			std::stringstream outss;
			outss << std::setprecision(2) << timeleft;
			std::string output = outss.str();

			std::stringstream namess;
			namess << RecallTarget[i]->GetChampionName().c_str() << ":    " << output;
			std::string name = namess.str();

			D3D_Font->DrawTextA(NULL, name.c_str(), -1, &NameRect, 0, TextColor); // ChampName
			FillRGB(pDevice, (float)NameRect.right, (float)NameRect.top, 10.f*timeleft, 15.f, 255, 255, 255, 100);

			menuentries++;
		}
	}
}
