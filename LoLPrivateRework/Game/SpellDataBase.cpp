#pragma once
#include "SpellDataBase.h"
#include "../Obfuscation.h"

#include <map>

SpellDataInfo::SpellDataInfo()
{
	this->slot = Unknown_Slot;
	this->type = unknown_type;
	this->speed = 0.f;
	this->range = 0.f;
	this->delay = 0.f;
	this->radius = 0.f;
	this->angle = 0.f;
	this->danger = 0;
	this->cc = false;
	this->collision = false;
	this->windwall = false;
};
SpellDataInfo::SpellDataInfo(
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
) {
	this->slot = slot;
	this->type = type;
	this->speed = speed;
	this->range = range;
	this->delay = delay;
	this->radius = radius;
	this->angle = 0.f;
	this->danger = danger;
	this->cc = cc;
	this->collision = collision;
	this->windwall = windwall;
}

SpellDataInfo::SpellDataInfo(
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
) {
	this->slot = slot;
	this->type = type;
	this->speed = speed;
	this->range = range;
	this->delay = delay;
	this->radius = radius;
	this->angle = angle;
	this->danger = danger;
	this->cc = cc;
	this->collision = collision;
	this->windwall = windwall;
}

void SpellDataBase::LoadDataBase() {
	Spells["AatroxW"] = new SpellDataInfo{ SpellSlotID::W,linear, 1800, 825, 0.25f, 80, 2, true, true, true };
	Spells["AhriOrbofDeception"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2500, 880, 0.25f, 100, 2, false, false, true };
	Spells["AhriOrbMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2500, 880, 0.25f, 100, 2, false, false, true };
	Spells["AhriSeduce"] = new SpellDataInfo{ SpellSlotID::E,linear, 1500, 975, 0.25f, 60, 1, true, true, true };
	Spells["AhriSeduceMissile"] = new SpellDataInfo{ SpellSlotID::E,linear, 1500, 975, 0.25f, 60, 1, true, true, true };
	Spells["AkaliQ"] = new SpellDataInfo{ SpellSlotID::Q,conic, 3200, 550, 0.25f, 60, 45, 2, false, false, true };
	Spells["AkaliQMis"] = new SpellDataInfo{ SpellSlotID::Q,conic, 3200, 550, 0.25f, 60, 45, 2, false, false, true };
	Spells["AkaliE"] = new SpellDataInfo{ SpellSlotID::E,linear, 1800, 825, 0.25f, 70, 2, false, true, true };
	Spells["AkaliEMis"] = new SpellDataInfo{ SpellSlotID::E,linear, 1800, 825, 0.25f, 70, 2, false, true, true };
	Spells["AkaliR"] = new SpellDataInfo{ SpellSlotID::R,linear, 1800, 525, 0, 65, 4, true, false, false };
	Spells["AkaliRb"] = new SpellDataInfo{ SpellSlotID::R,linear, 3600, 525, 0, 65, 4, false, false, false };
	Spells["Pulverize"] = new SpellDataInfo{ SpellSlotID::Q,circular, HUGE_VALF, 0, 0.25f, 365, 3, true, false, false };
	Spells["BandageToss"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2000, 1100, 0.25f, 80, 3, true, true, true };
	Spells["SadMummyBandageToss"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2000, 1100, 0.25f, 80, 3, true, true, true };
	Spells["CurseoftheSadMummy"] = new SpellDataInfo{ SpellSlotID::R,circular, HUGE_VALF, 0, 0.25f, 550, 5, true, false, false };
	Spells["FlashFrostSpell"] = new SpellDataInfo{ SpellSlotID::Q,linear, 850, 1100, 0.25f, 110, 2, true, false, true };
	Spells["AnnieW"] = new SpellDataInfo{ SpellSlotID::W,conic, HUGE_VALF, 600, 0.25f, 0, 50, 2, false, false, false };
	Spells["AnnieR"] = new SpellDataInfo{ SpellSlotID::R,circular, HUGE_VALF, 600, 0.25f, 0, 290, 5, false, false, false };
	Spells["Volley"] = new SpellDataInfo{ SpellSlotID::W,conic, 2000, 1200, 0.25f, 20, 40, 2, true, true, true };
	Spells["VolleyRightAttack"] = new SpellDataInfo{ SpellSlotID::W,conic, 2000, 1200, 0.25f, 20, 40, 2, true, true, true };
	Spells["EnchantedCrystalArrow"] = new SpellDataInfo{ SpellSlotID::R,linear, 1600, 25000, 0.25f, 130, 4, true, false, true };
	Spells["AurelionSolQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 850, 25000, 0, 110, 2, true, false, true };
	Spells["AurelionSolQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 850, 25000, 0, 110, 2, true, false, true };
	Spells["AzirR"] = new SpellDataInfo{ SpellSlotID::R,linear, 1400, 500, 0.3f, 250, 5, true, false, false };
	Spells["BardQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1500, 950, 0.25f, 60, 2, true, true, true };
	Spells["BardQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1500, 950, 0.25f, 60, 2, true, true, true };
	Spells["BardR"] = new SpellDataInfo{ SpellSlotID::R,circular, 2100, 3400, 0.5f, 350, 2, true, false, false };
	Spells["BardRMissile"] = new SpellDataInfo{ SpellSlotID::R,circular, 2100, 3400, 0.5f, 350, 2, true, false, false };
	Spells["RocketGrab"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1800, 1050, 0.25f, 70, 3, true, true, true };
	Spells["RocketGrabMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1800, 1050, 0.25f, 70, 3, true, true, true };
	Spells["BrandQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1600, 1050, 0.25f, 60, 1, true, true, true };
	Spells["BrandQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1600, 1050, 0.25f, 60, 1, true, true, true };
	Spells["BrandW"] = new SpellDataInfo{ SpellSlotID::W,circular, HUGE_VALF, 900, 0.85f, 250, 2, false, false, false };
	Spells["BraumQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1700, 1000, 0.25f, 70, 3, true, true, true };
	Spells["BraumQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1700, 1000, 0.25f, 70, 3, true, true, true };
	Spells["BraumR"] = new SpellDataInfo{ SpellSlotID::R,linear, 1400, 1250, 0.5f, 115, 4, true, false, true };
	Spells["BraumRMissile"] = new SpellDataInfo{ SpellSlotID::R,linear, 1400, 1250, 0.5f, 115, 4, true, false, true };
	Spells["CaitlynPiltoverPeacemaker"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2200, 1250, 0.625f, 60, 90, 1, false, false, true };
	Spells["CaitlynYordleTrap"] = new SpellDataInfo{ SpellSlotID::W,circular, HUGE_VALF, 800, 0.25f, 75, 1, true, false, false };
	Spells["CaitlynEntrapment"] = new SpellDataInfo{ SpellSlotID::E,linear, 1600, 750, 0.15f, 70, 2, true, true, true };
	Spells["CamilleEMissile"] = new SpellDataInfo{ SpellSlotID::E,linear, 1900, 925, 0, 60, 1, false, false, false };
	Spells["CassiopeiaQ"] = new SpellDataInfo{ SpellSlotID::Q,circular, HUGE_VALF, 850, 0.75f, 150, 2, false, false, false };
	Spells["CassiopeiaW"] = new SpellDataInfo{ SpellSlotID::W,circular, 2500, 800, 0.75f, 160, 2, true, false, true };
	Spells["CassiopeiaR"] = new SpellDataInfo{ SpellSlotID::R,conic, HUGE_VALF, 825, 0.5f, 0, 80, 5, true, false, false };
	Spells["Rupture"] = new SpellDataInfo{ SpellSlotID::Q,circular, HUGE_VALF, 950, 1.2f, 250, 2, true, false, false };
	Spells["FeralScream"] = new SpellDataInfo{ SpellSlotID::W,conic, HUGE_VALF, 650, 0.5f, 0, 56, 2, true, false, false };
	Spells["PhosphorusBomb"] = new SpellDataInfo{ SpellSlotID::Q,circular, 1000, 825, 0.25f, 250, 2, false, false, true };
	Spells["PhosphorusBombMissile"] = new SpellDataInfo{ SpellSlotID::Q,circular, 1000, 825, 0.25f, 250, 2, false, false, true };
	Spells["MissileBarrageMissile"] = new SpellDataInfo{ SpellSlotID::R,linear, 2000, 1300, 0.175f, 40, 1, false, true, true };
	Spells["MissileBarrageMissile2"] = new SpellDataInfo{ SpellSlotID::R,linear, 2000, 1500, 0.175f, 40, 1, false, true, true };
	Spells["DianaArc"] = new SpellDataInfo{ SpellSlotID::Q,circular, 1400, 900, 0.25f, 185, 2, false, true, true };
	Spells["InfectedCleaverMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2000, 975, 0.25f, 60, 2, true, true, true };
	Spells["DravenDoubleShot"] = new SpellDataInfo{ SpellSlotID::E,linear, 1600, 1050, 0.25f, 130, 3, true, false, true };
	Spells["DravenDoubleShotMissile"] = new SpellDataInfo{ SpellSlotID::E,linear, 1600, 1050, 0.25f, 130, 3, true, false, true };
	Spells["DravenRCast"] = new SpellDataInfo{ SpellSlotID::R,linear, 2000, 25000, 0.25f, 160, 4, false, false, true };
	Spells["DravenR"] = new SpellDataInfo{ SpellSlotID::R,linear, 2000, 25000, 0.25f, 160, 4, false, false, true };
	Spells["EkkoQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1650, 1175, 0.25f, 60, 1, true, false, true };
	Spells["EkkoQMis"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1650, 1175, 0.25f, 60, 1, true, false, true };
	Spells["EkkoW"] = new SpellDataInfo{ SpellSlotID::W,circular, HUGE_VALF, 1600, 3.35f, 400, 1, true, false, false };
	Spells["EkkoWMis"] = new SpellDataInfo{ SpellSlotID::W,circular, HUGE_VALF, 1600, 3.35f, 400, 1, true, false, false };
	Spells["EliseHumanE"] = new SpellDataInfo{ SpellSlotID::E,linear, 1600, 1075, 0.25f, 55, 1, true, true, true };
	Spells["EvelynnQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2400, 800, 0.25f, 60, 2, false, true, true };
	Spells["EvelynnR"] = new SpellDataInfo{ SpellSlotID::R,conic, HUGE_VALF, 450, 0.35f, 180, 180, 5, false, false, false };
	Spells["EzrealQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2000, 1150, 0.25f, 60, 1, false, true, true };
	Spells["EzrealW"] = new SpellDataInfo{ SpellSlotID::W,linear, 2000, 1150, 0.25f, 60, 1, false, false, true };
	Spells["EzrealR"] = new SpellDataInfo{ SpellSlotID::R,linear, 2000, 25000, 1, 160, 4, false, false, true };
	Spells["FizzR"] = new SpellDataInfo{ SpellSlotID::R,linear, 1300, 1300, 0.25f, 150, 5, true, false, true };
	Spells["FizzRMissile"] = new SpellDataInfo{ SpellSlotID::R,linear, 1300, 1300, 0.25f, 150, 5, true, false, true };
	Spells["GalioQ"] = new SpellDataInfo{ SpellSlotID::Q,circular, 1150, 825, 0.25f, 235, 2, false, false, true };
	Spells["GalioQMissileR"] = new SpellDataInfo{ SpellSlotID::Q,circular, 1150, 825, 0.25f, 235, 2, false, false, true };
	Spells["GalioE"] = new SpellDataInfo{ SpellSlotID::E,linear, 2300, 650, 0.4f, 160, 3, true, false, false };
	Spells["GnarQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2500, 1125, 0.25f, 55, 2, true, false, true };
	Spells["GnarBigQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2100, 1125, 0.5f, 90, 2, true, true, true };
	Spells["GnarBigW"] = new SpellDataInfo{ SpellSlotID::W,linear, HUGE_VALF, 575, 0.6f, 100, 3, true, false, false };
	Spells["GnarR"] = new SpellDataInfo{ SpellSlotID::R,circular, HUGE_VALF, 0, 0.25f, 475, 5, true, false, false };
	Spells["GragasQ"] = new SpellDataInfo{ SpellSlotID::Q,circular, 1000, 850, 0.25f, 275, 2, true, false, true };
	Spells["GragasQMissile"] = new SpellDataInfo{ SpellSlotID::Q,circular, 1000, 850, 0.25f, 275, 2, true, false, true };
	Spells["GragasR"] = new SpellDataInfo{ SpellSlotID::R,circular, 1800, 1000, 0.25f, 400, 5, true, false, true };
	Spells["GragasRBoom"] = new SpellDataInfo{ SpellSlotID::R,circular, 1800, 1000, 0.25f, 400, 5, true, false, true };
	Spells["GravesQLineSpell"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2000, 700, 0.095f, 20, 1, false, false, true };
	Spells["GravesClusterShotSoundMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2000, 700, 0.095f, 20, 1, false, false, true };
	Spells["GravesSmokeGrenade"] = new SpellDataInfo{ SpellSlotID::W,circular, 1500, 950, 0.15f, 250, 2, true, false, true };
	Spells["GravesSmokeGrenadeBoom"] = new SpellDataInfo{ SpellSlotID::W,circular, 1500, 950, 0.15f, 250, 2, true, false, true };
	Spells["GravesChargeShot"] = new SpellDataInfo{ SpellSlotID::R,linear, 2100, 1000, 0.25f, 100, 5, false, false, true };
	Spells["GravesChargeShotShot"] = new SpellDataInfo{ SpellSlotID::R,linear, 2100, 1000, 0.25f, 100, 5, false, false, true };
	Spells["HecarimUltMissile"] = new SpellDataInfo{ SpellSlotID::R,linear, 1100, 1650, 0.2f, 280, 4, true, false, false };
	Spells["HeimerdingerW"] = new SpellDataInfo{ SpellSlotID::W,linear, 2050, 1325, 0.25f, 100, 2, false, false, true };
	Spells["HeimerdingerWAttack2"] = new SpellDataInfo{ SpellSlotID::W,linear, 2050, 1325, 0.25f, 100, 2, false, false, true };
	Spells["HeimerdingerE"] = new SpellDataInfo{ SpellSlotID::E,circular, 1200, 970, 0.25f, 250, 2, true, false, true };
	Spells["HeimerdingerESpell"] = new SpellDataInfo{ SpellSlotID::E,circular, 1200, 970, 0.25f, 250, 2, true, false, true };
	Spells["HeimerdingerEUlt"] = new SpellDataInfo{ SpellSlotID::E,circular, 1200, 970, 0.25f, 250, 3, true, false, true };
	Spells["HeimerdingerESpell_ult"] = new SpellDataInfo{ SpellSlotID::E,circular, 1200, 970, 0.25f, 250, 3, true, false, true };
	Spells["IllaoiQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, HUGE_VALF, 850, 0.75f, 100, 2, false, true, false };
	Spells["IllaoiE"] = new SpellDataInfo{ SpellSlotID::E,linear, 1900, 900, 0.25f, 50, 1, false, true, true };
	Spells["IllaoiEMis"] = new SpellDataInfo{ SpellSlotID::E,linear, 1900, 900, 0.25f, 50, 1, false, true, true };
	Spells["IreliaW2"] = new SpellDataInfo{ SpellSlotID::W,linear, HUGE_VALF, 775, 0.25f, 120, 3, true, false, false };
	Spells["IreliaR"] = new SpellDataInfo{ SpellSlotID::R,linear, 2000, 950, 0.4f, 160, 4, true, false, true };
	Spells["IvernQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1300, 1075, 0.25f, 80, 1, true, true, true };
	Spells["HowlingGaleSpell"] = new SpellDataInfo{ SpellSlotID::Q,linear, 667, 995, 0, 120, 1, true, false, true };
	Spells["HowlingGaleSpell2"] = new SpellDataInfo{ SpellSlotID::Q,linear, 700, 1045, 0, 120, 1, true, false, true };
	Spells["HowlingGaleSpell3"] = new SpellDataInfo{ SpellSlotID::Q,linear, 733, 1095, 0, 120, 1, true, false, true };
	Spells["HowlingGaleSpell4"] = new SpellDataInfo{ SpellSlotID::Q,linear, 767, 1145, 0, 120, 1, true, false, true };
	Spells["HowlingGaleSpell5"] = new SpellDataInfo{ SpellSlotID::Q,linear, 800, 1195, 0, 120, 1, true, false, true };
	Spells["HowlingGaleSpell6"] = new SpellDataInfo{ SpellSlotID::Q,linear, 833, 1245, 0, 120, 1, true, false, true };
	Spells["HowlingGaleSpell7"] = new SpellDataInfo{ SpellSlotID::Q,linear, 867, 1295, 0, 120, 1, true, false, true };
	Spells["HowlingGaleSpell8"] = new SpellDataInfo{ SpellSlotID::Q,linear, 900, 1345, 0, 120, 1, true, false, true };
	Spells["HowlingGaleSpell9"] = new SpellDataInfo{ SpellSlotID::Q,linear, 933, 1395, 0, 120, 1, true, false, true };
	Spells["HowlingGaleSpell10"] = new SpellDataInfo{ SpellSlotID::Q,linear, 967, 1445, 0, 120, 1, true, false, true };
	Spells["HowlingGaleSpell11"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1000, 1495, 0, 120, 2, true, false, true };
	Spells["HowlingGaleSpell12"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1033, 1545, 0, 120, 2, true, false, true };
	Spells["HowlingGaleSpell13"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1067, 1595, 0, 120, 2, true, false, true };
	Spells["HowlingGaleSpell14"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1100, 1645, 0, 120, 2, true, false, true };
	Spells["HowlingGaleSpell15"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1133, 1695, 0, 120, 2, true, false, true };
	Spells["HowlingGaleSpell16"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1167, 1745, 0, 120, 2, true, false, true };
	Spells["JarvanIVDragonStrike"] = new SpellDataInfo{ SpellSlotID::Q,linear, HUGE_VALF, 770, 0.4f, 70, 2, true, false, false };
	Spells["JayceShockBlast"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1450, 1050, 0.214f, 70, 1, false, true, true };
	Spells["JayceShockBlastMis"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1450, 1050, 0.214f, 70, 1, false, true, true };
	Spells["JhinW"] = new SpellDataInfo{ SpellSlotID::W,linear, 5000, 2550, 0.75f, 40, 1, true, false, true };
	Spells["JhinE"] = new SpellDataInfo{ SpellSlotID::E,circular, 1600, 750, 0.25f, 130, 1, true, false, false };
	Spells["JhinETrap"] = new SpellDataInfo{ SpellSlotID::E,circular, 1600, 750, 0.25f, 130, 1, true, false, false };
	Spells["JhinRShotMis"] = new SpellDataInfo{ SpellSlotID::R,linear, 5000, 3500, 0.25f, 80, 3, true, false, true };
	Spells["JinxWMissile"] = new SpellDataInfo{ SpellSlotID::W,linear, 3300, 1450, 0.6f, 60, 1, true, true, true };
	Spells["JinxEHit"] = new SpellDataInfo{ SpellSlotID::E,circular, 1750, 900, 0, 120, 3, true, false, true };
	Spells["JinxR"] = new SpellDataInfo{ SpellSlotID::R,linear, 1700, 25000, 0.6f, 140, 4, false, false, true };
	Spells["KalistaMysticShot"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2400, 1150, 0.25f, 40, 1, false, true, true };
	Spells["KalistaMysticShotMisTrue"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2400, 1150, 0.25f, 40, 1, false, true, true };
	Spells["KarmaQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1700, 950, 0.25f, 60, 2, true, true, true };
	Spells["KarmaQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1700, 950, 0.25f, 60, 2, true, true, true };
	Spells["KarmaQMantra"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1700, 950, 0.25f, 80, 2, true, true, true };
	Spells["KarmaQMissileMantra"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1700, 950, 0.25f, 80, 2, true, true, true };
	Spells["KarthusLayWasteA1"] = new SpellDataInfo{ SpellSlotID::Q,circular, HUGE_VALF, 875, 0.9f, 175, 1, false, false, false };
	Spells["KarthusLayWasteA2"] = new SpellDataInfo{ SpellSlotID::Q,circular, HUGE_VALF, 875, 0.9f, 175, 1, false, false, false };
	Spells["KarthusLayWasteA3"] = new SpellDataInfo{ SpellSlotID::Q,circular, HUGE_VALF, 875, 0.9f, 175, 1, false, false, false };
	Spells["ForcePulse"] = new SpellDataInfo{ SpellSlotID::E,conic, HUGE_VALF, 600, 0.3f, 0, 80, 3, true, false, false };
	Spells["RiftWalk"] = new SpellDataInfo{ SpellSlotID::R,circular, HUGE_VALF, 500, 0.25f, 250, 3, false, false, false };
	Spells["KayleQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2000, 850, 0.5f, 60, 1, true, false, true };
	Spells["KayleQMisVFX"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2000, 850, 0.5f, 60, 1, true, false, true };
	Spells["KaynW"] = new SpellDataInfo{ SpellSlotID::W,linear, HUGE_VALF, 700, 0.55f, 90, 2, true, false, false };
	Spells["KennenShurikenHurlMissile1"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1700, 1050, 0.175f, 50, 2, false, true, true };
	Spells["KhazixW"] = new SpellDataInfo{ SpellSlotID::W,linear, 1700, 1000, 0.25f, 70, 1, false, true, true };
	Spells["KhazixWMissile"] = new SpellDataInfo{ SpellSlotID::W,linear, 1700, 1000, 0.25f, 70, 1, false, true, true };
	Spells["KhazixWLong"] = new SpellDataInfo{ SpellSlotID::W,threeway, 1700, 1000, 0.25f, 70, 23, 2, true, true, true };
	Spells["KledQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1600, 800, 0.25f, 45, 1, true, true, true };
	Spells["KledQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1600, 800, 0.25f, 45, 1, true, true, true };
	Spells["KledRiderQ"] = new SpellDataInfo{ SpellSlotID::Q,conic, 3000, 700, 0.25f, 0, 25, 3, false, false, true };
	Spells["KledRiderQMissile"] = new SpellDataInfo{ SpellSlotID::Q,conic, 3000, 700, 0.25f, 0, 25, 3, false, false, true };
	Spells["KogMawQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1650, 1175, 0.25f, 70, 1, false, true, true };
	Spells["KogMawVoidOozeMissile"] = new SpellDataInfo{ SpellSlotID::E,linear, 1400, 1360, 0.25f, 120, 2, true, false, true };
	Spells["KogMawLivingArtillery"] = new SpellDataInfo{ SpellSlotID::R,circular, HUGE_VALF, 1300, 1.1f, 200, 1, false, false, false };
	Spells["LeblancE"] = new SpellDataInfo{ SpellSlotID::E,linear, 1750, 925, 0.25f, 55, 1, true, true, true };
	Spells["LeblancEMissile"] = new SpellDataInfo{ SpellSlotID::E,linear, 1750, 925, 0.25f, 55, 1, true, true, true };
	Spells["LeblancRE"] = new SpellDataInfo{ SpellSlotID::E,linear, 1750, 925, 0.25f, 55, 1, true, true, true };
	Spells["LeblancREMissile"] = new SpellDataInfo{ SpellSlotID::E,linear, 1750, 925, 0.25f, 55, 1, true, true, true };
	Spells["BlindMonkQOne"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1800, 1100, 0.25f, 60, 1, false, true, true };
	Spells["LeonaZenithBlade"] = new SpellDataInfo{ SpellSlotID::E,linear, 2000, 875, 0.25f, 70, 2, true, false, true };
	Spells["LeonaSolarFlare"] = new SpellDataInfo{ SpellSlotID::R,circular, HUGE_VALF, 1200, 0.85f, 300, 5, true, false, false };
	Spells["LissandraQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2200, 750, 0.25f, 75, 2, true, false, true };
	Spells["LissandraEMissile"] = new SpellDataInfo{ SpellSlotID::E,linear, 850, 1025, 0.25f, 125, 2, false, false, true };
	Spells["LucianQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, HUGE_VALF, 900, 0.35f, 65, 2, false, false, false };
	Spells["LucianW"] = new SpellDataInfo{ SpellSlotID::W,linear, 1600, 900, 0.25f, 80, 2, false, true, true };
	Spells["LucianRMissile"] = new SpellDataInfo{ SpellSlotID::R,linear, 2800, 1200, 0, 110, 3, false, true, true };
	Spells["LuluQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1450, 925, 0.25f, 60, 1, true, false, true };
	Spells["LuluQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1450, 925, 0.25f, 60, 1, true, false, true };
	Spells["LuxLightBinding"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1200, 1175, 0.25f, 50, 1, true, true, true };
	Spells["LuxLightBindingDummy"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1200, 1175, 0.25f, 50, 1, true, true, true };
	Spells["LuxLightStrikeKugel"] = new SpellDataInfo{ SpellSlotID::E,circular, 1200, 1100, 0.25f, 300, 3, true, true, true };
	Spells["LuxMaliceCannonMis"] = new SpellDataInfo{ SpellSlotID::R,linear, HUGE_VALF, 3340, 1, 120, 4, false, false, false };
	Spells["Landslide"] = new SpellDataInfo{ SpellSlotID::E,circular, HUGE_VALF, 0, 0.242f, 400, 2, true, false, false };
	Spells["MalzaharQ"] = new SpellDataInfo{ SpellSlotID::Q,rectangular, 1600, 900, 0.5f, 400, 100, 1, true, false, false };
	Spells["MalzaharQMissile"] = new SpellDataInfo{ SpellSlotID::Q,rectangular, 1600, 900, 0.5f, 400, 100, 1, true, false, false };
	Spells["MaokaiQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1600, 600, 0.375f, 110, 2, true, false, true };
	Spells["MaokaiQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1600, 600, 0.375f, 110, 2, true, false, true };
	Spells["MissFortuneBulletTime"] = new SpellDataInfo{ SpellSlotID::R,conic, 2000, 1400, 0.25f, 100, 34, 4, false, false, true };
	Spells["MordekaiserSyphonOfDestruction"] = new SpellDataInfo{ SpellSlotID::E,conic, HUGE_VALF, 700, 0.25f, 0, 50, 2, false, false, false };
	Spells["MorganaQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1200, 1250, 0.25f, 70, 1, true, true, true };
	Spells["MorganaW"] = new SpellDataInfo{ SpellSlotID::W,circular, HUGE_VALF, 900, 0.25f, 275, 2, false, false, false };
	Spells["NamiQ"] = new SpellDataInfo{ SpellSlotID::Q,circular, HUGE_VALF, 875, 1, 180, 1, true, false, true };
	Spells["NamiRMissile"] = new SpellDataInfo{ SpellSlotID::R,linear, 850, 2750, 0.5f, 250, 3, true, false, true };
	Spells["NautilusAnchorDragMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2000, 925, 0.25f, 90, 3, true, true, true };
	Spells["NeekoQ"] = new SpellDataInfo{ SpellSlotID::Q,circular, 1500, 800, 0.25f, 200, 2, true, false, true };
	Spells["NeekoE"] = new SpellDataInfo{ SpellSlotID::E,linear, 1400, 1000, 0.25f, 65, 1, true, false, true };
	Spells["JavelinToss"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1300, 1500, 0.25f, 40, 1, false, true, true };
	Spells["Swipe"] = new SpellDataInfo{ SpellSlotID::E,conic, HUGE_VALF, 350, 0.25f, 0, 180, 2, false, false, false };
	Spells["NocturneDuskbringer"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1600, 1200, 0.25f, 60, 2, false, false, true };
	Spells["NunuR"] = new SpellDataInfo{ SpellSlotID::R,circular, HUGE_VALF, 0, 3, 650, 5, true, false, false };
	Spells["OlafAxeThrowCast"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1600, 1000, 0.25f, 90, 2, true, false, true };
	Spells["OlafAxeThrow"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1600, 1000, 0.25f, 90, 2, true, false, true };
	Spells["OrnnQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1800, 800, 0.3f, 65, 1, true, false, true };
	Spells["OrnnE"] = new SpellDataInfo{ SpellSlotID::E,linear, 1800, 800, 0.35f, 150, 3, true, false, false };
	Spells["OrnnRCharge"] = new SpellDataInfo{ SpellSlotID::R,linear, 1650, 2500, 0.5f, 200, 3, true, false, true };
	Spells["PantheonE"] = new SpellDataInfo{ SpellSlotID::E,conic, HUGE_VALF, 400, 0.389f, 0, 70, 3, false, false, false };
	Spells["PoppyQSpell"] = new SpellDataInfo{ SpellSlotID::Q,linear, HUGE_VALF, 430, 0.332f, 100, 2, true, false, false };
	Spells["PoppyRSpell"] = new SpellDataInfo{ SpellSlotID::R,linear, 2000, 1200, 0.33f, 100, 3, true, false, true };
	Spells["PoppyRSpellMissile"] = new SpellDataInfo{ SpellSlotID::R,linear, 2000, 1200, 0.33f, 100, 3, true, false, true };
	Spells["PykeQMelee"] = new SpellDataInfo{ SpellSlotID::Q,linear, HUGE_VALF, 400, 0.25f, 70, 2, true, false, false };
	Spells["PykeQRange"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2000, 1100, 0.2f, 70, 2, true, true, true };
	Spells["PykeE"] = new SpellDataInfo{ SpellSlotID::E,linear, 3000, 25000, 0, 110, 2, true, false, false };
	Spells["PykeEMissile"] = new SpellDataInfo{ SpellSlotID::E,linear, 3000, 25000, 0, 110, 2, true, false, false };
	Spells["PykeR"] = new SpellDataInfo{ SpellSlotID::R,circular, HUGE_VALF, 750, 0.5f, 350, 100, 5, false, false, false };
	Spells["QuinnQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1550, 1025, 0.25f, 60, 1, false, true, true };
	Spells["RakanQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1850, 850, 0.25f, 65, 1, false, true, true };
	Spells["RakanQMis"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1850, 850, 0.25f, 65, 1, false, true, true };
	Spells["RakanW"] = new SpellDataInfo{ SpellSlotID::W,circular, HUGE_VALF, 650, 0.7f, 265, 3, true, false, false };
	Spells["RekSaiQBurrowed"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1950, 1625, 0.125f, 65, 2, false, true, true };
	Spells["RekSaiQBurrowedMis"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1950, 1625, 0.125f, 65, 2, false, true, true };
	Spells["RengarE"] = new SpellDataInfo{ SpellSlotID::E,linear, 1500, 1000, 0.25f, 70, 1, true, true, true };
	Spells["RengarEMis"] = new SpellDataInfo{ SpellSlotID::E,linear, 1500, 1000, 0.25f, 70, 1, true, true, true };
	Spells["RumbleGrenade"] = new SpellDataInfo{ SpellSlotID::E,linear, 2000, 850, 0.25f, 60, 2, true, true, true };
	Spells["RumbleGrenadeMissile"] = new SpellDataInfo{ SpellSlotID::E,linear, 2000, 850, 0.25f, 60, 2, true, true, true };
	Spells["RyzeQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1700, 1000, 0.25f, 55, 1, false, true, true };
	Spells["SejuaniR"] = new SpellDataInfo{ SpellSlotID::R,linear, 1600, 1300, 0.25f, 120, 5, true, false, true };
	Spells["SejuaniRMissile"] = new SpellDataInfo{ SpellSlotID::R,linear, 1600, 1300, 0.25f, 120, 5, true, false, true };
	Spells["ShyvanaFireball"] = new SpellDataInfo{ SpellSlotID::E,linear, 1575, 925, 0.25f, 60, 1, false, false, true };
	Spells["ShyvanaFireballMissile"] = new SpellDataInfo{ SpellSlotID::E,linear, 1575, 925, 0.25f, 60, 1, false, false, true };
	Spells["ShyvanaFireballDragon2"] = new SpellDataInfo{ SpellSlotID::E,linear, 1575, 975, 0.333f, 60, 2, false, false, true };
	Spells["ShyvanaFireballDragonMissile"] = new SpellDataInfo{ SpellSlotID::E,linear, 1575, 975, 0.333f, 60, 2, false, false, true };
	Spells["ShyvanaTransformLeap"] = new SpellDataInfo{ SpellSlotID::R,linear, 700, 850, 0.25f, 150, 4, true, false, false };
	Spells["SionQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, HUGE_VALF, 750, 2, 150, 3, true, false, false };
	Spells["SionE"] = new SpellDataInfo{ SpellSlotID::E,linear, 1800, 800, 0.25f, 80, 2, true, false, true };
	Spells["SionEMissile"] = new SpellDataInfo{ SpellSlotID::E,linear, 1800, 800, 0.25f, 80, 2, true, false, true };
	Spells["SivirQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1350, 1250, 0.25f, 90, 2, false, false, true };
	Spells["SivirQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1350, 1250, 0.25f, 90, 2, false, false, true };
	Spells["SkarnerFractureMissile"] = new SpellDataInfo{ SpellSlotID::E,linear, 1500, 1000, 0.25f, 70, 1, true, false, true };
	Spells["SonaR"] = new SpellDataInfo{ SpellSlotID::R,linear, 2400, 1000, 0.25f, 140, 4, true, false, true };
	Spells["SonaRMissile"] = new SpellDataInfo{ SpellSlotID::R,linear, 2400, 1000, 0.25f, 140, 4, true, false, true };
	Spells["SorakaQ"] = new SpellDataInfo{ SpellSlotID::Q,circular, 1150, 810, 0.25f, 235, 2, true, false, false };
	Spells["SorakaQMissile"] = new SpellDataInfo{ SpellSlotID::Q,circular, 1150, 810, 0.25f, 235, 2, true, false, false };
	Spells["SwainQ"] = new SpellDataInfo{ SpellSlotID::Q,conic, 5000, 725, 0.25f, 0, 45, 2, false, false, true };
	Spells["SwainW"] = new SpellDataInfo{ SpellSlotID::W,circular, HUGE_VALF, 3500, 1.5f, 300, 1, true, false, false };
	Spells["SwainE"] = new SpellDataInfo{ SpellSlotID::E,linear, 1800, 850, 0.25f, 85, 2, true, false, true };
	Spells["SyndraQSpell"] = new SpellDataInfo{ SpellSlotID::Q,circular, HUGE_VALF, 800, 0.625f, 200, 1, false, false, false };
	Spells["SyndraE"] = new SpellDataInfo{ SpellSlotID::E,conic, 1600, 700, 0.25f, 0, 40, 3, true, false, true };
	Spells["SyndraEMissile"] = new SpellDataInfo{ SpellSlotID::E,conic, 1600, 700, 0.25f, 0, 40, 3, true, false, true };
	Spells["SyndraESphereMissile"] = new SpellDataInfo{ SpellSlotID::E,linear, 2000, 950, 0.25f, 100, 2, true, false, false };
	Spells["TahmKenchQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2800, 800, 0.25f, 70, 2, true, true, true };
	Spells["TahmKenchQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2800, 800, 0.25f, 70, 2, true, true, true };
	Spells["TaliyahQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 3600, 1000, 0.25f, 100, 2, false, true, true };
	Spells["TaliyahQMis"] = new SpellDataInfo{ SpellSlotID::Q,linear, 3600, 1000, 0.25f, 100, 2, false, true, true };
	Spells["TaliyahWVC"] = new SpellDataInfo{ SpellSlotID::W,circular, HUGE_VALF, 900, 0.85f, 150, 1, true, false, false };
	Spells["TaliyahE"] = new SpellDataInfo{ SpellSlotID::E,conic, 2000, 800, 0.45f, 0, 80, 2, true, false, false };
	Spells["TaliyahR"] = new SpellDataInfo{ SpellSlotID::R,linear, 1700, 3000, 1, 120, 1, true, false, false };
	Spells["TaliyahRMis"] = new SpellDataInfo{ SpellSlotID::R,linear, 1700, 3000, 1, 120, 1, true, false, false };
	Spells["TalonW"] = new SpellDataInfo{ SpellSlotID::W,conic, 2500, 650, 0.25f, 75, 26, 2, true, false, true };
	Spells["TalonWMissileOne"] = new SpellDataInfo{ SpellSlotID::W,conic, 2500, 650, 0.25f, 75, 26, 2, true, false, true };
	//Spells["ThreshQInternal"] = new SpellDataInfo {SpellSlotID::Q,linear, 1900, 1075, 0.5f, 70, 1, true, true, true };
	Spells["ThreshQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1900, 1075, 0.5f, 70, 1, true, true, true };
	Spells["ThreshE"] = new SpellDataInfo{ SpellSlotID::E,linear, HUGE_VALF, 500, 0.389f, 110, 3, true, true, false };
	Spells["ThreshEMissile1"] = new SpellDataInfo{ SpellSlotID::E,linear, HUGE_VALF, 500, 0.389f, 110, 3, true, true, false };
	Spells["TristanaW"] = new SpellDataInfo{ SpellSlotID::W,circular, 1100, 900, 0.25f, 300, 2, true, false, false };
	Spells["WildCards"] = new SpellDataInfo{ SpellSlotID::Q,threeway, 1000, 1450, 0.25f, 40, 28, 1, false, false, true };
	Spells["SealFateMissile"] = new SpellDataInfo{ SpellSlotID::Q,threeway, 1000, 1450, 0.25f, 40, 28, 1, false, false, true };
	Spells["UrgotQ"] = new SpellDataInfo{ SpellSlotID::Q,circular, HUGE_VALF, 800, 0.6f, 180, 2, true, false, true };
	Spells["UrgotQMissile"] = new SpellDataInfo{ SpellSlotID::Q,circular, HUGE_VALF, 800, 0.6f, 180, 2, true, false, true };
	Spells["UrgotE"] = new SpellDataInfo{ SpellSlotID::E,linear, 1500, 475, 0.45f, 100, 2, true, false, false };
	Spells["UrgotR"] = new SpellDataInfo{ SpellSlotID::R,linear, 3200, 1600, 0.4f, 80, 4, true, false, true };
	Spells["VarusQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1900, 1525, 0, 70, 1, false, false, true };
	Spells["VarusE"] = new SpellDataInfo{ SpellSlotID::E,circular, 1500, 925, 0.242f, 260, 3, true, false, true };
	Spells["VarusEMissile"] = new SpellDataInfo{ SpellSlotID::E,circular, 1500, 925, 0.242f, 260, 3, true, false, true };
	Spells["VarusR"] = new SpellDataInfo{ SpellSlotID::R,linear, 1950, 1200, 0.25f, 120, 4, true, false, true };
	Spells["VarusRMissile"] = new SpellDataInfo{ SpellSlotID::R,linear, 1950, 1200, 0.25f, 120, 4, true, false, true };
	Spells["VeigarBalefulStrike"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2200, 900, 0.25f, 70, 2, false, true, true };
	Spells["VeigarBalefulStrikeMis"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2200, 900, 0.25f, 70, 2, false, true, true };
	Spells["VeigarDarkMatterCastLockout"] = new SpellDataInfo{ SpellSlotID::W,circular, HUGE_VALF, 900, 1.25f, 200, 1, false, false, false };
	Spells["VeigarEventHorizon"] = new SpellDataInfo{ SpellSlotID::E,annular, HUGE_VALF, 700, 1, 375, 2, true, false, false };
	Spells["VelkozQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1300, 1050, 0.25f, 50, 1, true, true, true };
	Spells["VelkozQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1300, 1050, 0.25f, 50, 1, true, true, true };
	Spells["VelkozQMissileSplit"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2100, 1100, 0.25f, 45, 2, true, true, true };
	Spells["VelkozW"] = new SpellDataInfo{ SpellSlotID::W,linear, 1700, 1050, 0.25f, 87.5f, 1, false, false, true };
	Spells["VelkozWMissile"] = new SpellDataInfo{ SpellSlotID::W,linear, 1700, 1050, 0.25f, 87.5f, 1, false, false, true };
	Spells["VelkozE"] = new SpellDataInfo{ SpellSlotID::E,circular, HUGE_VALF, 800, 0.8f, 185, 2, true, false, false };
	Spells["VelkozEMissile"] = new SpellDataInfo{ SpellSlotID::E,circular, HUGE_VALF, 800, 0.8f, 185, 2, true, false, false };
	Spells["ViktorGravitonField"] = new SpellDataInfo{ SpellSlotID::W,circular, HUGE_VALF, 800, 1.75f, 270, 1, true, false, false };
	Spells["ViktorDeathRayMissile"] = new SpellDataInfo{ SpellSlotID::E,linear, 1050, 750, 0, 80, 2, false, false, true };
	Spells["WarwickR"] = new SpellDataInfo{ SpellSlotID::R,linear, 1800, 3000, 0.1f, 55, 4, true, false, false };
	Spells["XayahQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2075, 1100, 0.5f, 45, 1, false, false, true };
	Spells["XerathArcaneBarrage2"] = new SpellDataInfo{ SpellSlotID::W,circular, HUGE_VALF, 1000, 0.75f, 235, 3, true, false, false };
	Spells["XerathMageSpear"] = new SpellDataInfo{ SpellSlotID::E,linear, 1400, 1050, 0.2f, 60, 1, true, true, true };
	Spells["XerathMageSpearMissile"] = new SpellDataInfo{ SpellSlotID::E,linear, 1400, 1050, 0.2f, 60, 1, true, true, true };
	Spells["XerathLocusPulse"] = new SpellDataInfo{ SpellSlotID::R,circular, HUGE_VALF, 5600, 0.7f, 200, 2, false, false, false };
	Spells["XinZhaoW"] = new SpellDataInfo{ SpellSlotID::W,linear, 5000, 900, 0.5f, 40, 1, true, false, false };
	Spells["YasuoQ3Mis"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1200, 1100, 0.318f, 90, 2, true, false, true };
	Spells["ZacQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2800, 800, 0.33f, 120, 2, true, false, true };
	Spells["ZacQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 2800, 800, 0.33f, 120, 2, true, false, true };
	Spells["ZedQ"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1700, 900, 0.25f, 50, 1, false, false, true };
	Spells["ZedQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1700, 900, 0.25f, 50, 1, false, false, true };
	Spells["ZedW"] = new SpellDataInfo{ SpellSlotID::W,linear, 1750, 700, 0, 60, 1, false, false, false };
	Spells["ZedWMissile"] = new SpellDataInfo{ SpellSlotID::W,linear, 1750, 700, 0, 60, 1, false, false, false };
	Spells["ZiggsQ"] = new SpellDataInfo{ SpellSlotID::Q,circular, 1700, 850, 0.25f, 120, 1, false, true, true };
	Spells["ZiggsQSpell"] = new SpellDataInfo{ SpellSlotID::Q,circular, 1700, 850, 0.25f, 120, 1, false, true, true };
	Spells["ZiggsW"] = new SpellDataInfo{ SpellSlotID::W,circular, 1750, 1000, 0.25f, 240, 2, true, false, true };
	Spells["ZiggsE"] = new SpellDataInfo{ SpellSlotID::E,circular, 1800, 900, 0.25f, 250, 2, true, false, true };
	Spells["ZiggsR"] = new SpellDataInfo{ SpellSlotID::R,circular, 1550, 5000, 0.375f, 480, 4, false, false, false };
	Spells["ZiggsRBoom"] = new SpellDataInfo{ SpellSlotID::R,circular, 1550, 5000, 0.375f, 480, 4, false, false, false };
	Spells["ZileanQ"] = new SpellDataInfo{ SpellSlotID::Q,circular, HUGE_VALF, 900, 0.8f, 150, 2, true, false, true };
	Spells["ZileanQMissile"] = new SpellDataInfo{ SpellSlotID::Q,circular, HUGE_VALF, 900, 0.8f, 150, 2, true, false, true };
	Spells["ZoeQMissile"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1200, 800, 0.25f, 50, 1, false, true, true };
	Spells["ZoeQMMis2"] = new SpellDataInfo{ SpellSlotID::Q,linear, 1200, 800, 0.25f, 50, 1, false, true, true };
	Spells["ZoeE"] = new SpellDataInfo{ SpellSlotID::E,linear, 1700, 800, 0.3f, 50, 2, true, true, true };
	Spells["ZoeEMissile"] = new SpellDataInfo{ SpellSlotID::E,linear, 1700, 800, 0.3f, 50, 2, true, true, true };
	Spells["ZyraQ"] = new SpellDataInfo{ SpellSlotID::Q,rectangular, HUGE_VALF, 800, 0.825f, 400, 200, 1, false, false, false };
	Spells["ZyraE"] = new SpellDataInfo{ SpellSlotID::E,linear, 1150, 1100, 0.25f, 70, 1, true, false, true };
	Spells["ZyraR"] = new SpellDataInfo{ SpellSlotID::R,circular, HUGE_VALF, 700, 2, 500, 4, true, false, false };
}
