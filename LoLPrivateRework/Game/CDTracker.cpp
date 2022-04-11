#pragma once
#include "GameIncludes.h"

bool CDTracker::Init = false;
LPD3DXFONT CDTracker::D3D_Font;
D3DCOLOR CDTracker::TextColor;
std::string CDTracker::GetSummonerSpellName(Spell* Slot) {
	if (Slot)
	{
		if (Slot->GetSpellInfo())
		{
			std::string SpellName = Slot->GetSpellInfo()->GetSpellName().c_str();
			if (!SpellName.compare("SummonerDot"))
			{
				return "Ignite";
			}
			if (!SpellName.compare("SummonerFlash"))
			{
				return "Flash";
			}
			if (!SpellName.compare("SummonerHaste"))
			{
				return "Ghost";
			}
			if (!SpellName.compare("SummonerHeal"))
			{
				return "Heal";
			}
			if (!SpellName.compare("SummonerBarrier"))
			{
				return "Barrier";
			}
			if (!SpellName.compare("SummonerBoost"))
			{
				return "Cleanse";
			}
			if (!SpellName.compare("SummonerExhaust"))
			{
				return "Exhaust";
			}
			if (!SpellName.compare("SummonerTeleport"))
			{
				return "Teleport";
			}
			if (!SpellName.compare(0, 13, "SummonerSmite"))
			{
				return "Smite";
			}
			if (!SpellName.compare(0, 16, "S5_SummonerSmite"))
			{
				return "Smite";
			}
			return SpellName;
		}
	}
	return "";
}
void CDTracker::DrawCooldowns(LPDIRECT3DDEVICE9 pDevice) {
	if (!Init)
	{
		D3DXCreateFontA(pDevice, 15, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &D3D_Font);
		TextColor = D3DCOLOR_XRGB(255, 255, 255);
		Init = !Init;
	}

	std::string CDS;
	std::string CDSUMMS;

	int QCD = 0;
	int WCD = 0;
	int ECD = 0;
	int RCD = 0;
	int DCD = 0;
	int FCD = 0;

	std::string QCD_string = " ";
	std::string WCD_string = " ";
	std::string ECD_string = " ";
	std::string RCD_string = " ";
	std::string DCD_string = " ";
	std::string FCD_string = " ";

	for (GameObject* Target : TargetList::ChampionList)
	{
		if (Target->GetTeam() == Engine::pLocalPlayer->GetTeam())
		{
			continue;
		}
		if (strcmp(Target->GetName().c_str(),"Target Dummy") == NULL)
		{
			continue;
		}
		Vector3 WorldPos = Target->GetPosition();
		Vector3 ScreenPos;
		if (Engine::World2Screen(&WorldPos, &ScreenPos)) {
			//cout << "OnScreen!" << endl;
			if (Target->GetSpellbook()->GetSpellSlot(0)->GetSpellCooldown1())
			{
				QCD = (int)(Target->GetSpellbook()->GetSpellSlot(0)->GetSpellCooldown1() - *Engine::GameTime);
			}
			if (Target->GetSpellbook()->GetSpellSlot(1)->GetSpellCooldown1())
			{
				WCD = (int)(Target->GetSpellbook()->GetSpellSlot(1)->GetSpellCooldown1() - *Engine::GameTime);
			}
			if (Target->GetSpellbook()->GetSpellSlot(2)->GetSpellCooldown1())
			{
				ECD = (int)(Target->GetSpellbook()->GetSpellSlot(2)->GetSpellCooldown1() - *Engine::GameTime);
			}
			if (Target->GetSpellbook()->GetSpellSlot(3)->GetSpellCooldown1())
			{
				RCD = (int)(Target->GetSpellbook()->GetSpellSlot(3)->GetSpellCooldown1() - *Engine::GameTime);
			}
			//SummonerSpells
			if (Target->GetSpellbook()->GetSpellSlot(4)->GetSpellCooldown1())
			{
				DCD = (int)(Target->GetSpellbook()->GetSpellSlot(4)->GetSpellCooldown1() - *Engine::GameTime);
			}
			if (Target->GetSpellbook()->GetSpellSlot(5)->GetSpellCooldown1())
			{
				FCD = (int)(Target->GetSpellbook()->GetSpellSlot(5)->GetSpellCooldown1() - *Engine::GameTime);
			}
			if (Target->GetSpellbook()->GetSpellSlot(0)->GetSpellLevel())
			{
				QCD_string = "Q";
			}
			if (Target->GetSpellbook()->GetSpellSlot(1)->GetSpellLevel())
			{
				WCD_string = "W";
			}
			if (Target->GetSpellbook()->GetSpellSlot(2)->GetSpellLevel())
			{
				ECD_string = "E";
			}
			if (Target->GetSpellbook()->GetSpellSlot(3)->GetSpellLevel())
			{
				RCD_string = "R";
			}
			//SummonerSpells
			DCD_string = GetSummonerSpellName(Target->GetSpellbook()->GetSpellSlot(4));			
			FCD_string = GetSummonerSpellName(Target->GetSpellbook()->GetSpellSlot(5));
			if (QCD > 0)
			{
				QCD_string = std::to_string(QCD);
			}
			if (WCD > 0)
			{
				WCD_string = std::to_string(WCD);
			}
			if (ECD > 0)
			{
				ECD_string = std::to_string(ECD);
			}
			if (RCD > 0)
			{
				RCD_string = std::to_string(RCD);
			}
			//SummonerSpells
			if (DCD > 0)
			{
				DCD_string = std::to_string(DCD);
			}
			if (FCD > 0)
			{
				FCD_string = std::to_string(FCD);
			}
			std::stringstream QWER;
			std::stringstream SUMMS;
			QWER << QCD_string << "    " << WCD_string << "    " << ECD_string << "    " << RCD_string;
			SUMMS << DCD_string << std::endl << FCD_string;
			CDS = QWER.str();
			CDSUMMS = SUMMS.str();

			RECT QWER_Rect;
			QWER_Rect.left = (int)ScreenPos.x - 40;
			QWER_Rect.right = QWER_Rect.left + 100;
			QWER_Rect.top = (int)ScreenPos.y + 30;
			QWER_Rect.bottom = QWER_Rect.top + 20;

			RECT SUMMS_Rect;
			SUMMS_Rect.left = (int)ScreenPos.x - 40;
			SUMMS_Rect.right = SUMMS_Rect.left + 100;
			SUMMS_Rect.top = (int)ScreenPos.y + 50;
			SUMMS_Rect.bottom = SUMMS_Rect.top + 40;

			const char* CDtext = CDS.c_str();
			const char* SUMMStext = CDSUMMS.c_str();


			//DrawString("Test", 15, ScreenPos.x - 40, ScreenPos.y + 30, 1, 1, 1);
			//DrawString(SUMMStext, 15, ScreenPos.x - 40, ScreenPos.y + 50, 1, 1, 1);
			D3D_Font->DrawTextA(NULL, CDtext, -1, &QWER_Rect, 0, TextColor); // CDText
			D3D_Font->DrawTextA(NULL, SUMMStext, -1, &SUMMS_Rect, 0, TextColor); // SUMMSText

			//D3D_Font->Release();
		}
	}
}