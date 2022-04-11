#pragma once
#include "GameIncludes.h"

#pragma region utility
void Engine::DrawAroundObject(GameObject* Object, float range, DWORD* color) {
	if (Object)
	{
		Engine::DrawCircle(&Object->GetPosition(), range, color, 0, 0, 0, 1.f);
	}
}
bool Engine::SpellReady(SpellSlotID Slot) {
	SpellBook* Spellbook = pLocalPlayer->GetSpellbook();
	//if (Spellbook->GetSpellSlot(Slot)->GetSpellLevel())
	//{
	//	if (Slot > 3)
	//	{
	//		if ((Spellbook->GetSpellSlot(Slot)->GetSpellCooldown1() < *GameTime))
	//		{
	//			return true;
	//		}
	//	}
	//	if ((Spellbook->GetSpellSlot(Slot)->GetSpellCooldown1() < *GameTime) && (Spellbook->GetSpellSlot(Slot)->GetSpellCooldown2() < *GameTime))
	//	{
	//		if (Spellbook->GetManaCost(Slot) <= pLocalPlayer->GetMana())
	//		{
	//			return true;
	//		}
	//	}
	//	if ((Spellbook->GetSpellSlot(Slot)->GetSpellCooldown1() < *GameTime) || Spellbook->GetSpellSlot(Slot)->GetSpellCharges()) //Spells with charges (e.g. xerath W,e , riven q)
	//	{
	//		if (Spellbook->GetManaCost(Slot) <= pLocalPlayer->GetMana())
	//		{
	//			return true;
	//		}
	//	}
	//}

	BYTE null = 0;
	if (!GetSpellstate(Spellbook,Slot, &null))
	{
		return true;
	}
	return false;
}
SpellSlotID Engine::getSmiteSlot(SpellBook* Spellbook) {
	std::string SmiteName = Spellbook->GetSpellSlot(D)->GetSpellInfo()->GetSpellName().c_str();
	if (SmiteName.compare(0, 13, "SummonerSmite") == NULL)
	{
		return D;
	}
	if (SmiteName.compare(0, 16, "S5_SummonerSmite") == NULL)
	{
		return D;
	}
	SmiteName = Spellbook->GetSpellSlot(F)->GetSpellInfo()->GetSpellName().c_str();
	if (SmiteName.compare(0, 13, "SummonerSmite") == NULL)
	{
		return F;
	}
	if (SmiteName.compare(0, 16, "S5_SummonerSmite") == NULL)
	{
		return F;
	}
	return Unknown_Slot;
}
SpellSlotID Engine::getBladeSlot(SpellBook* Spellbook) {
	for (int i = Item1; i <= Item6; i++)
	{
		if (Spellbook->GetSpellSlot(i))
		{
			if (Spellbook->GetSpellSlot(i)->GetSpellInfo())
			{
				const char* BladeName = Spellbook->GetSpellSlot(i)->GetSpellInfo()->GetSpellName().c_str();
				if (strcmp(BladeName, "ItemSwordOfFeastAndFamine") == NULL)
				{
					return (SpellSlotID)i;
				}
				if (strcmp(BladeName, "HextechGunblade") == NULL)
				{
					return (SpellSlotID)i;
				}
				if (strcmp(BladeName, "BilgewaterCutlass") == NULL)
				{
					return (SpellSlotID)i;
				}
			}
		}
	}
	return Unknown_Slot;
}
SpellSlotID Engine::getHydraSlot(SpellBook* Spellbook) {
	for (int i = Item1; i <= Item6; i++)
	{
		if (Spellbook->GetSpellSlot(i))
		{
			if (Spellbook->GetSpellSlot(i)->GetSpellInfo())
			{
				const char* HydraName = Spellbook->GetSpellSlot(i)->GetSpellInfo()->GetSpellName().c_str();
				if (strcmp(HydraName, "ItemTitanicHydraCleave") == NULL)
				{
					return (SpellSlotID)i;
				}
				if (strcmp(HydraName, "ItemTiamatCleave") == NULL)
				{
					return (SpellSlotID)i;
				}
			}
		}
	}
	return Unknown_Slot;
}
SpellSlotID Engine::getPotionSlot(SpellBook* Spellbook) {
	for (int i = Item1; i <= Item6; i++)
	{
		if (Spellbook->GetSpellSlot(i))
		{
			if (Spellbook->GetSpellSlot(i)->GetSpellInfo())
			{
				const char* PotionName = Spellbook->GetSpellSlot(i)->GetSpellInfo()->GetSpellName().c_str();
				if (strcmp(PotionName, "RegenerationPotion") == NULL)
				{
					return (SpellSlotID)i;
				}if (strcmp(PotionName, "ItemCrystalFlask") == NULL)
				{
					return (SpellSlotID)i;
				}
				if (strcmp(PotionName, "ItemCrystalFlaskJungle") == NULL)
				{
					return (SpellSlotID)i;
				}
				if (strcmp(PotionName, "ItemDarkCrystalFlask") == NULL)
				{
					return (SpellSlotID)i;
				}
			}
		}
	}
	return Unknown_Slot;
}
float Engine::GetDistance3D(Vector3 Position, GameObject* Target)
{
	return (float)sqrt(pow((Position.x - Target->GetPosition().x), 2) + pow((Position.z - Target->GetPosition().z), 2));
}
float Engine::GetDistance3D(Vector3 From, Vector3 To)
{
	return (float)sqrt(pow((From.x - To.x), 2) + pow((From.z - To.z), 2));
}
bool Engine::isBigJungle(GameObject *Target) {
	std::string TargetName = Target->GetName().c_str();
	//CampNames:
	//BlueSide:
	//	SRU_Blue1.1.1 
	//	SRU_Murkwolf2.1.1
	//	SRU_Razorbeak3.1.1
	//	SRU_Red4.1.1
	//	SRU_Krug5.1.1
	//Dragons:
	//	SRU_Dragon_Air6.1.1
	//	SRU_Dragon_Fire6.2.1
	//	SRU_Dragon_Water6.3.1
	//	SRU_Dragon_Earth6.4.1
	//	SRU_Dragon_Elder6.5.1
	//RedSide:
	//	SRU_Blue7.1.1	
	//	SRU_Murkwolf8.1.1
	//	SRU_Razorbeak9.1.1
	//	SRU_Red10.1.1
	//	SRU_Krug11.1.1

	//	SRU_Baron12.1.1
	//	SRU_Gromp13.1.1	//Blue
	//	SRU_Gromp14.1.1 //Red
	//	Sru_Crab15.1.1	//BotSide
	//	Sru_Crab16.1.1	//TopSide
	//	SRU_RiftHerald17.1.1
	//	------------------------
	if (TargetName.compare(0, 8, "SRU_Blue") == NULL)
	{
		return true;
	}
	if (TargetName.compare(0, 7, "SRU_Red") == NULL)
	{
		return true;
	}
	if (TargetName.compare(0, 9, "SRU_Gromp") == NULL)
	{
		return true;
	}
	if (TargetName.compare(0, 14, "SRU_Razorbeak9") == NULL)
	{
		return true;
	}
	if (TargetName.compare(0, 14, "SRU_Razorbeak3") == NULL)
	{
		return true;
	}
	if (TargetName.compare(0, 13, "SRU_Murkwolf8") == NULL)
	{
		return true;
	}
	if (TargetName.compare(0, 13, "SRU_Murkwolf2") == NULL)
	{
		return true;
	}
	if (TargetName.compare(0, 10, "SRU_Dragon") == NULL)
	{
		return true;
	}
	if (TargetName.compare(0, 8, "Sru_Crab") == NULL)
	{
		return true;
	}
	if (TargetName.compare(0, 9, "SRU_Baron") == NULL)
	{
		return true;
	}
	if (TargetName.compare(0, 14, "SRU_RiftHerald") == NULL)
	{
		return true;
	}
	if (TargetName.compare(0, 10, "SRU_Krug11") == NULL)
	{
		return true;
	}
	if (TargetName.compare(0, 9, "SRU_Krug5") == NULL)
	{
		return true;
	}
	//	Twisted TreeLine:
	//	TT_NWraith1.1.1
	//	TT_NGolem2.1.1
	//	TT_NWolf3.1.1
	//	TT_NWraith4.1.1
	//	TT_NGolem5.1.1
	//	TT_NWolf6.1.1
	//	TT_Spiderboss8.1.1
	if (strcmp(TargetName.c_str(), "TT_NWraith1.1.1") == NULL)
	{
		return true;
	}
	if (strcmp(TargetName.c_str(), "TT_NGolem2.1.1") == NULL)
	{
		return true;
	}
	if (strcmp(TargetName.c_str(), "TT_NWolf3.1.1") == NULL)
	{
		return true;
	}
	if (strcmp(TargetName.c_str(), "TT_NWraith4.1.1") == NULL)
	{
		return true;
	}
	if (strcmp(TargetName.c_str(), "TT_NGolem5.1.1") == NULL)
	{
		return true;
	}
	if (strcmp(TargetName.c_str(), "TT_NWolf6.1.1") == NULL)
	{
		return true;
	}
	if (strcmp(TargetName.c_str(), "TT_Spiderboss8.1.1") == NULL)
	{
		return true;
	}
	return false;
}
bool Engine::isEpicJungle(GameObject *Target) {
	std::string TargetName = Target->GetName().c_str();
	//CampNames:
	//Dragons:
	//	SRU_Dragon_Air6.1.1
	//	SRU_Dragon_Fire6.2.1
	//	SRU_Dragon_Water6.3.1
	//	SRU_Dragon_Earth6.4.1
	//	SRU_Dragon_Elder6.5.1

	//	SRU_Baron12.1.1
	//	SRU_RiftHerald17.1.1
	//	------------------------
	if (TargetName.compare(0, 10, "SRU_Dragon") == NULL)
	{
		return true;
	}
	if (TargetName.compare(0, 9, "SRU_Baron") == NULL)
	{
		return true;
	}
	if (TargetName.compare(0, 14, "SRU_RiftHerald") == NULL)
	{
		return true;
	}
	//	Twisted TreeLine:
	//	TT_Spiderboss8.1.1
	if (strcmp(TargetName.c_str(), "TT_Spiderboss8.1.1") == NULL)
	{
		return true;
	}
	return false;
}
bool Engine::isDeadWard(GameObject* Object) {
	if (strcmp(Object->GetName().c_str(), "WardCorpse") == NULL)
	{
		return true;
	}
	return false;
}
bool Engine::isWard(GameObject* Object) {
	//SightWard
	//WardCorpse
	//JammerDevice

	if (strcmp(Object->GetName().c_str(), "SightWard") == NULL)
	{
		return true;
	}
	if (strcmp(Object->GetName().c_str(), "VisionWard") == NULL)
	{
		return true;
	}
	if (strcmp(Object->GetName().c_str(), "JammerDevice") == NULL)
	{
		return true;
	}
	if (strcmp(Object->GetName().c_str(), "WardCorpse") == NULL)
	{
		return true;
	}
	return false;
}
bool Engine::isPlant(GameObject *Object) {
	if (strcmp(Object->GetName().c_str(), "PreSeason_Turret_Shield") == NULL)
	{
		return true;
	}
	if (strcmp(Object->GetName().c_str(), "Barrel") == NULL)
	{
		return true;
	}
	if (strcmp(Object->GetName().c_str(), "Seed") == NULL)
	{
		return true;
	}
	if (strcmp(Object->GetName().c_str(), "ShenArrowVfxHostMinion") == NULL)
	{
		return true;
	}
	if (strcmp(Object->GetName().c_str(), "MarkerMinion") == NULL)
	{
		return true;
	}
	if (strcmp(Object->GetName().c_str(), "PlantMasterMinion") == NULL)
	{
		return true;
	}
	if (strcmp(Object->GetName().c_str(), "PlantVision") == NULL)
	{
		return true;
	}
	if (strcmp(Object->GetName().c_str(), "PlantSatchel") == NULL)
	{
		return true;
	}
	if (strcmp(Object->GetName().c_str(), "PlantHealth") == NULL)
	{
		return true;
	}
	if (strcmp(Object->GetName().c_str(), "PlantHealthPack") == NULL)
	{
		return true;
	}
	if (strcmp(Object->GetName().c_str(), "PlantHealthMirrored") == NULL)
	{
		return true;
	}
	if (strcmp(Object->GetName().c_str(), "CampRespawn") == NULL)
	{
		return true;
	}
	return false;
}
float Engine::GetBuffDmgMod(GameObject* Target, float AttackDamage) {
	if (strcmp(pLocalPlayer->GetChampionName().c_str(), "Caitlyn") == NULL)
	{
		int caitheadshot = pLocalPlayer->GetBuffManager()->HasBuff("caitlynheadshot");
		if (caitheadshot > 0)
		{
			return AttackDamage * 2.f;
		}
	}
	if (strcmp(pLocalPlayer->GetChampionName().c_str(), "Lucian") == NULL)
	{
		if (pLocalPlayer->GetBuffManager()->HasBuff("LucianPassiveBuff"))
		{
			return AttackDamage * 2.f;
		}
	}
	if (strcmp(pLocalPlayer->GetChampionName().c_str(), "Vayne") == NULL)
	{
		float realdmg = 0;
		float qdmgmod = 0;
		float wdmg = 0;
		if (pLocalPlayer->GetBuffManager()->HasBuff("vaynetumblebonus"))
		{
			qdmgmod = 1.f + (((pLocalPlayer->GetSpellbook()->GetSpellSlot(0)->GetSpellLevel() * 5.f) + 45.f) / 100.f);
		}
		if (Target->GetBuffManager()->HasBuff("VayneSilveredDebuff") > 1)
		{
			if (pLocalPlayer->GetSpellbook()->GetSpellSlot(2)->GetSpellLevel() > 0)
			{
				wdmg = ((pLocalPlayer->GetSpellbook()->GetSpellSlot(2)->GetSpellLevel() * 2.5f) + 1.5f) * Target->GetMaxHealth();
				if (wdmg > 200.f)
				{
					wdmg = 200.f;
				}
			}
		}
		realdmg = ((1 * qdmgmod)*AttackDamage) + wdmg;
		if (realdmg)
		{
			return realdmg;
		}
		return AttackDamage;
	}
	return AttackDamage;
}
bool Engine::canLasthit(GameObject* Target) {
	if (pLocalPlayer && Target)
	{
		float healthreduce = 0.f;
		float health = Target->GetHealth();
		for (GameObject* Missile : TargetList::MissileList)
		{
			GameObject* source = Engine::pObjectManager->pObjectArray[Missile->GetSourceIndex()];
			if (!source)
			{
				continue;
			}
			if (source == pLocalPlayer)
			{
				continue;
			}
			if (strstr(source->GetName().c_str(), "Turret"))
			{
				continue;
			}
			GameObject* target = Engine::pObjectManager->pObjectArray[Missile->GetTargetID()];
			if (!target)
			{
				continue;
			}

			Vector3 PlayerPos = pLocalPlayer->GetPosition();
			Vector3 MissilePos = Missile->GetPosition();
			Vector3 SourcePos = source->GetPosition();
			Vector3 TargetPos = target->GetPosition();
			float fulldistance = sqrt(pow((SourcePos.x - TargetPos.x), 2) + pow((SourcePos.y - TargetPos.y), 2) + pow((SourcePos.z - TargetPos.z), 2));
			float missiledistance = sqrt(pow((MissilePos.x - TargetPos.x), 2) + pow((MissilePos.y - TargetPos.y), 2) + pow((MissilePos.z - TargetPos.z), 2));
			float playerdistance = sqrt(pow((PlayerPos.x - TargetPos.x), 2) + pow((PlayerPos.y - TargetPos.y), 2) + pow((PlayerPos.z - TargetPos.z), 2));

			float missilespeed = source->GetAAMissleSpeed();
			float playeraaspeed = pLocalPlayer->GetAAMissleSpeed();
			if (pLocalPlayer->GetAttackRange() < 300.f)
			{
				playeraaspeed = HUGE_VALF;
			}

			float missileimpacttime = missiledistance / missilespeed;
			float playerimpacttime = (playerdistance / playeraaspeed) + ((float)getWindup() * 0.8f);

			if (missileimpacttime < playerimpacttime)
			{
				if (target == Target)
				{
					healthreduce += source->GetBaseAtk();
				}
			}
		}
		healthreduce -= 5;
		//cout << health << endl;
		//cout << healthreduce << endl;
		health -= healthreduce;
		float PlayerAttackDmg = pLocalPlayer->GetBaseAtk() + pLocalPlayer->GetBonusAtk();
		float TargetArmor = Target->GetArmor();
		float dmgReductionMod = 100 / (100 + TargetArmor);
		float RealDmg = PlayerAttackDmg * dmgReductionMod;
		if (pLocalPlayer->GetCritMod() == 1.f)
		{
			RealDmg = RealDmg * 2;
		}
		RealDmg = GetBuffDmgMod(Target, RealDmg);
		if (strstr(pLocalPlayer->GetChampionName().c_str(), "Orianna"))
		{
			float AP = pLocalPlayer->GetBonusAP();
			float TargetMR = Target->GetMR();
			float dmgReductionModAP = 100 / (100 + TargetMR);
			

			float passivedmg = 10.f + (8.f * (float)((pLocalPlayer->GetLevel()-1) / 3));
			float APDmg = (passivedmg + (0.15f * AP)) * dmgReductionModAP;

			RealDmg = RealDmg + APDmg;
		}
		//Menu::DEBUG_MENUOUTPUT(RealDmg);
		if (health < RealDmg)
		{
			return true;
		}
	}
	return false;
}
bool Engine::IsAlreadyDead(GameObject* Target) {
	if (pLocalPlayer && Target)
	{
		float healthreduce = 0.f;
		float health = Target->GetHealth();
		for (GameObject* Missile : TargetList::MissileList)
		{
			GameObject* source = Engine::pObjectManager->pObjectArray[Missile->GetSourceIndex()];
			if (!source)
			{
				continue;
			}
			//if (source == pLocalPlayer)
			//{
			//	continue;
			//}
			if (strstr(source->GetName().c_str(), "Turret"))
			{
				continue;
			}
			GameObject* target = Engine::pObjectManager->pObjectArray[Missile->GetTargetID()];
			if (!target)
			{
				continue;
			}

			Vector3 PlayerPos = pLocalPlayer->GetPosition();
			Vector3 MissilePos = Missile->GetPosition();
			Vector3 SourcePos = source->GetPosition();
			Vector3 TargetPos = target->GetPosition();
			float fulldistance = sqrt(pow((SourcePos.x - TargetPos.x), 2) + pow((SourcePos.y - TargetPos.y), 2) + pow((SourcePos.z - TargetPos.z), 2));
			float missiledistance = sqrt(pow((MissilePos.x - TargetPos.x), 2) + pow((MissilePos.y - TargetPos.y), 2) + pow((MissilePos.z - TargetPos.z), 2));
			float playerdistance = sqrt(pow((PlayerPos.x - TargetPos.x), 2) + pow((PlayerPos.y - TargetPos.y), 2) + pow((PlayerPos.z - TargetPos.z), 2));

			float missilespeed = source->GetAAMissleSpeed();
			float playeraaspeed = pLocalPlayer->GetAAMissleSpeed();
			if (pLocalPlayer->GetAttackRange() < 300.f)
			{
				playeraaspeed = HUGE_VALF;
			}

			float missileimpacttime = missiledistance / missilespeed;
			float playerimpacttime = (playerdistance / playeraaspeed) + ((float)getWindup() * 0.8f);

			if (missileimpacttime < playerimpacttime)
			{
				if (target == Target)
				{
					healthreduce += source->GetBaseAtk();
				}
			}
		}
		health -= healthreduce;
		float PlayerAttackDmg = pLocalPlayer->GetBaseAtk() + pLocalPlayer->GetBonusAtk();
		float TargetArmor = Target->GetArmor();
		float dmgReductionMod = 100 / (100 + TargetArmor);
		float RealDmg = PlayerAttackDmg * dmgReductionMod;
		if (pLocalPlayer->GetCritMod() == 1.f)
		{
			RealDmg = RealDmg * 2;
		}
		RealDmg = GetBuffDmgMod(Target, RealDmg);
		//Menu::DEBUG_MENUOUTPUT(RealDmg);
		if (health < Target->GetHealth())
		{
			return true;
		}
	}
	return false;
}
TargetMode Engine::getOrbMode() {
	if (GetAsyncKeyState(Menu::combokey))
	{
		return Target_Combo;
	}
	if (GetAsyncKeyState(Menu::laneclearkey))
	{
		return Target_LaneClear;
	}
	if (GetAsyncKeyState(Menu::harasskey))
	{
		return Target_Harrass;
	}
	if (GetAsyncKeyState(Menu::lasthitkey))
	{
		return Target_LastHit;
	}
	return Idle;
}
#pragma endregion
#pragma region Orbwalker
void Engine::ResetMoveTimer()
{
	movetimer = clock();
}
void Engine::ResetAttackTimer()
{
	attacktimer = clock();
	AfterAAReset = false;
}
void Engine::ResetClickerTimer()
{
	clickertimer = clock();
}
double Engine::CalcMoveDelay()
{
	return ((double)clock() - (double)movetimer) / (double)CLOCKS_PER_SEC;
}
double Engine::CalcAttackDelay()
{
	return ((double)clock() - (double)attacktimer) / (double)CLOCKS_PER_SEC;
}
double Engine::CalcClickerDelay()
{
	return ((double)clock() - (double)clickertimer) / (double)CLOCKS_PER_SEC;
}
double Engine::getWindup()
{
	if (pLocalPlayer)
	{
		return GetAttackCastDelay(pLocalPlayer, 64);
	}
	return 0;
}
float Engine::LastMoveCommand = 0;
bool Engine::MoveReady()
{
	if (CalcMoveDelay() > getWindup()*1.15)
	{
		return true;
	}
	return false;
}
bool Engine::AAReset() {
	 //Spells that reset the attack timer.
	const char* AAResets[] =
	{
			//"viktorpowertransferreturn"
			"dariusnoxiantacticsonh", "sivirwmarker" , "rengarq", "rengarqemp", "garenq", "jaxempowertwo",
			"fioraflurry", "hecarimrapidslash", "jaycehypercharge", "leonashieldofdaybreak", "lucianpassivebuff",
			"monkeykingdoubleattack", "mordekaisermaceofspades", "nasusq", "nautiluspiercinggaze", "netherblade",
			"parley", "poppydevastatingblow", "powerfist", "renektonpreexecute", "shyvanadoubleattack",
			"takedown", "talonnoxiandiplomacy", "trundletrollsmash", "vie", "volibearq","xenzhaocombotarget", "yorickspectral", "reksaiq","itemtitanichydracleavebuff"
	};
	//pLocalPlayer->GetBuffManager()->DEBUG_SHOWALLBUFFS();
	for (const char* BuffName : AAResets)
	{
		if (!_strcmpi("sivir",pLocalPlayer->GetChampionName().c_str()))
		{
			if (strstr("sivirwmarker", BuffName))
			{
				if (pLocalPlayer->GetBuffManager()->HasBuff(BuffName) == 3)
				{
					return true;
				}
			}
		}
		else
		{
			if (pLocalPlayer->GetBuffManager()->HasBuff(BuffName))
			{
				return true;
			}
		}
	}
	return false;
}
bool Engine::NoAutoAttack(const char* AttackName) {
	const char* NoAttacks[] =
	{
		"garenqattack",
		"volleyattack", "volleyattackwithsound", "jarvanivcataclysmattack",
		"monkeykingdoubleattack", "shyvanadoubleattack",
		"shyvanadoubleattackdragon", "zyragraspingplantattack",
		"zyragraspingplantattack2", "zyragraspingplantattackfire",
		"zyragraspingplantattack2fire", "viktorpowertransfer",
		"sivirwattackbounce", "asheqattacknoonhit",
		"elisespiderlingbasicattack", "heimertyellowbasicattack",
		"heimertyellowbasicattack2", "heimertbluebasicattack",
		"annietibbersbasicattack", "annietibbersbasicattack2",
		"yorickdecayedghoulbasicattack", "yorickravenousghoulbasicattack",
		"yorickspectralghoulbasicattack", "malzaharvoidlingbasicattack",
		"malzaharvoidlingbasicattack2", "malzaharvoidlingbasicattack3",
		"kindredwolfBasicAttack", "kindredbasicattackoverridelightbombfinal"
	};
	for (const char* Name : NoAttacks)
	{
		if (!_strcmpi(Name,AttackName))
		{
			return true;
		}
	}
	return false;
}
bool Engine::IsAutoAttack(const char* AttackName) {
	const char* IsAutoAttack[] =
	{
		"caitlynheadshotmissile","masteryidoublestrike","frostarrow", "garenslash2",
		"kennenmegaproc", "quinnwenhanced", "renektonexecute", "vaynecondemn",
		"renektonsuperexecute", "rengarnewpassivebuffdash", "trundleq", "xenzhaothrust", "xenzhaothrust2",
		"xenzhaothrust3", "viktorqbuff","xinzhaoqthrust1","xinzhaoqthrust2","xinzhaoqthrust3"
	};
	for (const char* Name : IsAutoAttack)
	{
		//std::cout << AttackName << std::endl;
		if (!_strcmpi(Name, AttackName))
		{
			return true;
		}
	}
	return false;
}
const char* Engine::LastAttack = "";
bool Engine::AfterSpecialAA() {
	const char* SpecialAttack[] =
	{
		"vaynecondemn", "garenqattack", "lucianpassiveattack"
	};
	for (const char* Name : SpecialAttack)
	{
		if (!_strcmpi(Name, LastAttack))
		{
			if (CalcAttackDelay() < GetAttackDelay(pLocalPlayer)*0.85)
			{
				return true;
			}
		}
	}
	return false;
}
bool Engine::IsChanneling() {
	const char* ChannelCheck = "";
	if (pLocalPlayer->GetSpellbook()->GetActiveSpellEntry())
	{
		if (pLocalPlayer->GetSpellbook()->GetActiveSpellEntry()->GetActiveSpellInfo())
		{
			ChannelCheck = pLocalPlayer->GetSpellbook()->GetActiveSpellEntry()->GetActiveSpellInfo()->GetSpellName().c_str();
		}
	}
	const char* buffs[] = {
		"dariusqcast","garene","lucianr","vladimire","vladimirsanguinepool","xayahr"
	};

	const char* channels[] = {
		"kaisae","varusq","xeratharcanopulsechargeup","lucianr","vladimire","kayler"
	};
	for (const char* BuffName : buffs)
	{
		if (pLocalPlayer->GetBuffManager()->HasBuff(BuffName))
		{
			return true;
		}
	}
	for (const char* ChannelName : channels)
	{
		if (!_strcmpi(ChannelName, ChannelCheck))
		{
			return true;
		}
	}
	return false;
}
float Engine::LastDash = 0.f;
bool Engine::AttackReady() {
	if (pLocalPlayer)
	{
		if (IsChanneling())
		{
			return false;
		}
		if (strcmp(pLocalPlayer->GetChampionName().c_str(), "Yasuo") == NULL)
		{
			if (pLocalPlayer->GetAIManager()->IsDashing())
			{
				LastDash = *GameTime;
			}
			if (!SpellReady(Q))
			{
				if ((*GameTime - LastDash) < getWindup())
				{
					return false;
				}


				//float maxqcd = pLocalPlayer->GetSpellbook()->GetSpellSlot(0)->GetSpellMaxCooldown();
				//float leftqcd = pLocalPlayer->GetSpellbook()->GetSpellSlot(0)->GetSpellCooldown1() - *GameTime;
				//if ((maxqcd-leftqcd) < getWindup())
				//{
				//	float maxecd = pLocalPlayer->GetSpellbook()->GetSpellSlot(2)->GetSpellMaxCooldown();
				//	float leftecd = pLocalPlayer->GetSpellbook()->GetSpellSlot(2)->GetSpellCooldown1() - *GameTime;
				//	if ((maxecd - leftecd) < getWindup())
				//	{
				//		return false;
				//	}
				//}
			}
		}
		if (strcmp(pLocalPlayer->GetChampionName().c_str(), "Thresh") == NULL)
		{
			if (!strcmp(Engine::pLocalPlayer->GetSpellbook()->GetSpellSlot(0)->GetSpellInfo()->GetSpellName().c_str(), "ThreshQLeap"))
			{
				return false;
			}
		}
		if (strcmp(pLocalPlayer->GetChampionName().c_str(), "Graves") == NULL)
		{
			if (CalcAttackDelay() > (GetAttackDelay(pLocalPlayer)) / 2.f)
			{
				if (pLocalPlayer->GetAmmo() > 0.f)
				{
					return true;
				}
			}
		}
		if (strcmp(pLocalPlayer->GetChampionName().c_str(), "Jhin") == NULL)
		{
			if (CalcAttackDelay() > GetAttackDelay(pLocalPlayer)*0.85f)
			{
				if (pLocalPlayer->GetAmmo() > 0.f)
				{
					return true;
				}
			}
		}
		else if (CalcAttackDelay() > GetAttackDelay(pLocalPlayer)*0.85f)
		{
			return true;
		}
	}
	return false;
}

bool Engine::AACancelPossible() {
	if (pLocalPlayer->GetSpellbook()->GetActiveSpellEntry())
	{
		if (pLocalPlayer->GetSpellbook()->GetActiveSpellEntry()->GetActiveSpellInfo())
		{
			const char* AttackName = pLocalPlayer->GetSpellbook()->GetActiveSpellEntry()->GetActiveSpellInfo()->GetSpellName().c_str();
			if (strstr(AttackName, "Attack"))
			{
				if (CalcMoveDelay() > getWindup())
				{
					return true;
				}
			}
			if (strstr(AttackName, "ONHAttack"))
			{
				return true;
			}
		}
	}
	return false;
}
void Engine::DEBUG_SHOWTARGETBUFFS(GameObject* Target) {
	Target->GetBuffManager()->DEBUG_SHOWALLBUFFS();
}

Vector3 Engine::EvadePos;
bool Engine::BlockAA = false;
bool Engine::ForceEvade = false;
bool Engine::AlwaysEvade = false;
bool Engine::FirstMoveAfterAA = false;
bool Engine::AfterAAReset = false;
bool Engine::AfterAA = false;
bool Engine::ClickDelay(float delay) {
	float Delay = *Engine::GameTime - LastMoveCommand;
	//std::cout << Delay << std::endl;
	if (Delay > delay/1000)
	{
		return true;
	}
	return false;
}
int Engine::Orbwalk(GameObject* Target)
{
	const char* AttackName = "";
	DWORD colortarget = 0x0000FF00;
	//cout << ForceEvade << endl;
	//pLocalPlayer->GetBuffManager()->DEBUG_SHOWALLBUFFS();
	if (Target)
	{
		//std::cout << "name: " << Target->GetName().c_str() << std::endl;
		DrawAroundObject(Target, Target->GetBoundingRadius(), &colortarget);
	}
	if (strcmp(pLocalPlayer->GetChampionName().c_str(), "Kalista") != NULL)
	{
		if (pLocalPlayer->GetSpellbook()->GetActiveSpellEntry())
		{
			if (pLocalPlayer->GetSpellbook()->GetActiveSpellEntry()->GetActiveSpellInfo())
			{
				LastAttack = pLocalPlayer->GetSpellbook()->GetActiveSpellEntry()->GetActiveSpellInfo()->GetSpellName().c_str();
				AttackName = pLocalPlayer->GetSpellbook()->GetActiveSpellEntry()->GetActiveSpellInfo()->GetSpellName().c_str();
				//cout << AttackName << endl;
				if (AttackReady())
				{
					if (IsAutoAttack(AttackName)) {
						ResetAttackTimer();
						return 1;
					}
					if (strstr(AttackName, "Attack"))
					{
						if (!NoAutoAttack(AttackName))
						{
							ResetAttackTimer();
							ResetMoveTimer();
							return 1;
						}
					}
				}
			}
		}
		//DEBUG_SHOWTARGETBUFFS(pLocalPlayer);
		//cout << AAReset() << endl;
		if (AAReset() && Target && !BlockAA)
		{
			if (!IsChanneling())
			{
				IssueOrder(pLocalPlayer, Movetype_Attack, &Target->GetPosition(), Target, 0, 0, true);
				FirstMoveAfterAA = true;
				ResetAttackTimer();
				return 1;
			}
		}
		if (AttackReady() && Target && !BlockAA)
		{
			IssueOrder(pLocalPlayer, Movetype_Attack, &Target->GetPosition(), Target, 0, 0, true);
			FirstMoveAfterAA = true;
			ResetMoveTimer();
			return 1;
		}
		if ((!AttackReady() || !Target || AfterSpecialAA()) && !ForceEvade)
		{
			if ((MoveReady() || AfterSpecialAA()) && !ForceEvade)
			{
				Vector3 mousetoplayer = Vector3(pMouse->MousePos.x - pLocalPlayer->GetPosition().x, pMouse->MousePos.y - pLocalPlayer->GetPosition().y, pMouse->MousePos.z - pLocalPlayer->GetPosition().z);
				float length = sqrt((mousetoplayer.x * mousetoplayer.x) + (mousetoplayer.y * mousetoplayer.y) + (mousetoplayer.z * mousetoplayer.z));
				if (length >= 50.f)
				{
					if (ClickDelay(80) || FirstMoveAfterAA)
					{
						IssueOrder(pLocalPlayer, Movetype_Move, &pMouse->MousePos, NULL, 0, 0, true);
						FirstMoveAfterAA = false;
						LastMoveCommand = *Engine::GameTime;
						return 0;
					}
				}
				return 0;
			}
		}
		if (ForceEvade)
		{
			if (BlockAA)
			{
				if (ClickDelay(80) || FirstMoveAfterAA)
				{
					Evade::LastEvadeCommand = *Engine::GameTime;
					IssueOrder(pLocalPlayer, Movetype_Move, &EvadePos, NULL, 0, 0, true);
					FirstMoveAfterAA = false;
					LastMoveCommand = *Engine::GameTime;
					return 0;
				}
			}
			if (!BlockAA)
			{
				if (MoveReady() || AfterSpecialAA())
				{
					if (ClickDelay(80) || FirstMoveAfterAA)
					{
						IssueOrder(pLocalPlayer, Movetype_Move, &EvadePos, NULL, 0, 0, true);
						FirstMoveAfterAA = false;
						LastMoveCommand = *Engine::GameTime;
						return 0;
					}
				}
			}
		}
	}
	else {
		if (GetDistance3D(pMouse->MousePos, pLocalPlayer) > pLocalPlayer->GetBoundingRadius())
		{
			if (!ForceEvade) {
				Vector3 mousetoplayer = Vector3(pMouse->MousePos.x - pLocalPlayer->GetPosition().x, pMouse->MousePos.y - pLocalPlayer->GetPosition().y, pMouse->MousePos.z - pLocalPlayer->GetPosition().z);
				float length = sqrt((mousetoplayer.x * mousetoplayer.x) + (mousetoplayer.y * mousetoplayer.y) + (mousetoplayer.z * mousetoplayer.z));
				if (length >= 50.f)
				{
					if (ClickDelay(80) || FirstMoveAfterAA)
					{
						IssueOrder(pLocalPlayer, Movetype_Move, &pMouse->MousePos, NULL, 0, 0, true);
						FirstMoveAfterAA = false;
						LastMoveCommand = *Engine::GameTime;
						return 0;
					}
				}
				return 0;
			}
		}
		if (ForceEvade)
		{
			if (ClickDelay(80) || FirstMoveAfterAA)
			{
				IssueOrder(pLocalPlayer, Movetype_Move, &EvadePos, NULL, 0, 0, true);
				FirstMoveAfterAA = false;
				LastMoveCommand = *Engine::GameTime;
				return 0;
			}
		}
		if (Target)
		{
			if (ClickDelay(80))
			{
				IssueOrder(pLocalPlayer, Movetype_Attack, &Target->GetPosition(), Target, 0, 0, true);
				FirstMoveAfterAA = true;
				LastMoveCommand = *Engine::GameTime;
				return 1;
			}
		}
	}
	return 1;
}
int Engine::OrbBot() {
	if (getOrbMode() == Target_Combo)
	{
		Utility::ItemManager();
		return Orbwalk(TargetSelector::ComboTarget(pLocalPlayer->GetPosition(), pLocalPlayer->GetAttackRange(), 1));
	}
	if (getOrbMode() == Target_Harrass)
	{
		return Orbwalk(TargetSelector::HarrassTarget(pLocalPlayer->GetPosition(), pLocalPlayer->GetAttackRange()));
	}
	if (getOrbMode() == Target_LaneClear)
	{
		return Orbwalk(TargetSelector::LaneclearTarget(pLocalPlayer->GetPosition(), pLocalPlayer->GetAttackRange()));
	}
	if (getOrbMode() == Target_LastHit)
	{
		return Orbwalk(TargetSelector::LasthitTarget(pLocalPlayer->GetPosition(), pLocalPlayer->GetAttackRange()));
	}
	if (ForceEvade && AlwaysEvade)
	{
		return Orbwalk(NULL); //JustMove To Evade Pos
	}
	return 1;
}
#pragma endregion





SpellDataBase Engine::SpellDataBase;

//---------------------------------------------------------------
Engine::_GetSpellstate Engine::GetSpellstate;
Engine::_CastSpell Engine::CastSpell;
int Engine::CastAimedSpell(Vector3 Position, SpellSlotID Spell) {
	return CastSpell(pLocalPlayer->GetSpellbook(), pLocalPlayer->GetSpellbook()->GetSpellSlot(Spell), Spell, &Position, &Position, 0);
}
int Engine::CastTargetedSpell(GameObject* Target, SpellSlotID Spell) {
	return CastSpell(pLocalPlayer->GetSpellbook(), pLocalPlayer->GetSpellbook()->GetSpellSlot(Spell), Spell, &Target->GetPosition(), &Target->GetPosition(), Target->GetNetworkID());
}

//---------------------------------------------------------------

Engine::_UpdateChargeableSpell Engine::UpdateChargeableSpell;
int Engine::ReleaseSpell(Vector3 Position, SpellSlotID Spell) {
	UpdateChargeableSpell(pLocalPlayer->GetSpellbook(), pLocalPlayer->GetSpellbook()->GetSpellSlot(Spell), Spell, &Position, true);
	return 1;
}


//---------------------------------------------------------------

Engine::_DrawCircle Engine::DrawCircle;
Engine::_IssueOrder Engine::IssueOrder;
Engine::_GetAttackDelay Engine::GetAttackDelay;
Engine::_GetAttackCastDelay Engine::GetAttackCastDelay;

Engine::_IsMissile Engine::IsMissile;
Engine::_IsMinion Engine::IsMinion;
Engine::_IsHero Engine::IsHero;
Engine::_IsTargetable Engine::IsTargetable;

Engine::_World2Screen Engine::World2Screen;
Engine::_GetBasicAttack Engine::GetBasicAttack;
Engine::_IsWall Engine::IsWall;
//Engine::_IsAlive Engine::IsAlive;
//Engine::_IsTurret Engine::IsTurret;

DWORD Engine::BaseAddress;
float* Engine::GameTime;
LocalPlayerBase* Engine::pLPBase;
ObjectManagerBase* Engine::pObjMngrBase;
pHudInstanceBase* Engine::pHUDBase;
ChatClient* Engine::ChatClient;

GameObject* Engine::pLocalPlayer;
ObjectManager* Engine::pObjectManager;
Mouse* Engine::pMouse;
GameObject* Engine::MouseObject;

clock_t Engine::movetimer;
clock_t Engine::attacktimer;
clock_t Engine::clickertimer;

