#pragma once
#include "GameIncludes.h"
#include "Champions/Champions.h"

bool Utility::customHydraUsage;
int Utility::ChampSelect() {
	customHydraUsage = false;
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Annie") == NULL)
	{
		Annie::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Brand") == NULL)
	{
		Brand::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Caitlyn") == NULL)
	{
		Caitlyn::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Cassiopeia") == NULL)
	{
		Cassiopeia::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Darius") == NULL)
	{
		Darius::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Evelynn") == NULL)
	{
		Evelynn::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Ezreal") == NULL)
	{
		Ezreal::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Fiora") == NULL)
	{
		Fiora::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Thresh") == NULL)
	{
		Thresh::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Twitch") == NULL)
	{
		Twitch::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Gangplank") == NULL)
	{
		Gangplank::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Graves") == NULL)
	{
		Graves::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Janna") == NULL)
	{
		Janna::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Jax") == NULL)
	{
		Jax::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Jhin") == NULL)
	{
		Jhin::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Kalista") == NULL)
	{
		Kalista::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Karthus") == NULL)
	{
		Karthus::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Kayle") == NULL)
	{
		Kayle::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "KogMaw") == NULL)
	{
		KogMaw::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Lissandra") == NULL)
	{
		Lissandra::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Lucian") == NULL)
	{
		Lucian::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Lulu") == NULL)
	{
		Lulu::Rotation();
		return 1;
	}
	if (strstr(Engine::pLocalPlayer->GetChampionName().c_str(), "Lux"))
	{
		Lux::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Olaf") == NULL)
	{
		Olaf::Rotation();
		return 1;
	}
	if (strstr(Engine::pLocalPlayer->GetChampionName().c_str(), "Orianna"))
	{
		Orianna::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Rengar") == NULL)
	{
		Rengar::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Riven") == NULL)
	{
		Riven::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Ryze") == NULL)
	{
		Ryze::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Talon") == NULL)
	{
		Talon::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Vayne") == NULL)
	{
		Vayne::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Viktor") == NULL)
	{
		Viktor::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Vladimir") == NULL)
	{
		Vladimir::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Xayah") == NULL)
	{
		Xayah::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Xerath") == NULL)
	{
		Xerath::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "XinZhao") == NULL)
	{
		XinZhao::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Yasuo") == NULL)
	{
		Yasuo::Rotation();
		return 1;
	}
	if (strcmp(Engine::pLocalPlayer->GetChampionName().c_str(), "Zilean") == NULL)
	{
		Zilean::Rotation();
		return 1;
	}
	return 0;
}
int Utility::SmiteBot() {
	GameObject* Target = TargetSelector::SmiteTarget(500.f);
	SpellSlotID Slot = Engine::getSmiteSlot(Engine::pLocalPlayer->GetSpellbook());
	if (Slot != Unknown_Slot)
	{
		Spell* pSmite = Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(Slot);

		float SmiteDMG = pSmite->GetSmiteDamage();
		if (Target)
		{
			DWORD color = 0x00fffff;
			Engine::DrawAroundObject(Target, 65, &color);
			if (Engine::IsMinion(Target))
			{
				if (Target->GetHealth() <= SmiteDMG)
				{
					if (Engine::Engine::SpellReady(Slot))
					{
						Engine::CastSpell(Engine::pLocalPlayer->GetSpellbook(), pSmite, Slot, &Target->GetPosition(), &Target->GetPosition(), Target->GetNetworkID());
						return 1;
					}
				}
			}
			if (Engine::IsHero(Target))
			{
				if (Engine::Engine::SpellReady(Slot))
				{
					Engine::CastSpell(Engine::pLocalPlayer->GetSpellbook(), pSmite, Slot, &Target->GetPosition(), &Target->GetPosition(), Target->GetNetworkID());
					return 1;
				}
			}
		}
	}
	return 0;
}
int Utility::ItemManager() {
	SpellSlotID BladeSlot = Engine::getBladeSlot(Engine::pLocalPlayer->GetSpellbook());
	SpellSlotID PotionSlot = Engine::getPotionSlot(Engine::pLocalPlayer->GetSpellbook());
	if (BladeSlot)
	{
		GameObject* Blade_Target;
		if (Engine::MouseObject && Engine::GetDistance3D(Engine::pLocalPlayer->GetPosition(), Engine::MouseObject) <= 550.f)
		{
			Blade_Target = Engine::MouseObject;
		}
		else {
			Blade_Target = TargetSelector::ComboTarget(Engine::pLocalPlayer->GetPosition(), 550.f, 1);
		}
		if (Engine::IsHero(Blade_Target))
		{
			if (Engine::SpellReady(BladeSlot))
			{
				Engine::CastSpell(Engine::pLocalPlayer->GetSpellbook(), Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(BladeSlot), BladeSlot, &Blade_Target->GetPosition(), &Blade_Target->GetPosition(), Blade_Target->GetNetworkID());
				return 1;
			}
		}
	}
	if (!customHydraUsage)
	{
		UseHydraReset();
	}
	return 0;
}
int Utility::UseHydraReset() {
	if (Engine::pLocalPlayer->GetSpellbook()->GetActiveSpellEntry())
	{
		if (Engine::pLocalPlayer->GetSpellbook()->GetActiveSpellEntry()->GetActiveSpellInfo())
		{
			const char* AttackName = Engine::pLocalPlayer->GetSpellbook()->GetActiveSpellEntry()->GetActiveSpellInfo()->GetSpellName().c_str();
			//cout << AttackName << endl;
			if (strstr(AttackName, "Attack"))
			{
				if (Engine::CalcMoveDelay() > Engine::getWindup())
				{
					UseHydra();
					return 1;
				}
			}
		}
	}
	return 0;
}
int Utility::UseHydra() {
	SpellSlotID HydraSlot = Engine::getHydraSlot(Engine::pLocalPlayer->GetSpellbook());
	bool HydraReady = false;
	if (HydraSlot)
	{
		HydraReady = Engine::SpellReady(HydraSlot);
	}
	if (HydraReady)
	{
		Engine::CastSpell(Engine::pLocalPlayer->GetSpellbook(), Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(HydraSlot), HydraSlot, &Engine::pMouse->MousePos, &Engine::pMouse->MousePos, 0);
		return 1;
	}
	return 0;
}