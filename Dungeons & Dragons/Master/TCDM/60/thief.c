/* []---------------------------------------------------------------------[] */
/* |          Thief.cpp: Display thief information in a window.            | */
/* |                                                                       | */
/* |              The Thief.cpp source code and concepts are               | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __THIEF__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <TcxlHlp.H>
#include <TcxlInp.H>
#include <TcxlMnu.H>
#include <TcxlWin.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID Display_Thief_Skills(NOARG);
VOID CTYP ModifyTSkills(NOARG);
VOID createTemps(IntT character);

ChrP thiefSkills[] = {"Pick Pockets", "Open Locks", "Find/Remove Traps",
	 "Move Silently", "Hide in Shadows", "Detect Noise", "Climb Walls",
	 "Read Languages", NULL};
IntT thiefBase[8] = {15, 10, 5, 10, 5, 15, 60, 0};
IntT thiefDexMods[17][8] = {
    {-15, -10, -10, -20,  -5,  0,  0,  0},   /*  9 */
    {-10,  -5,  -5, -15,   0,  0,  0,  0},   /* 10 */
    { -5,   0,   0, -10,   0,  0,  0,  0},   /* 11 */
    {  0,   0,   0,  -5,   0,  0,  0,  0},   /* 12 */
    {  0,   0,   0,   0,   0,  0,  0,  0},   /* 13 */
    {  0,   0,   0,   0,   0,  0,  0,  0},   /* 14 */
    {  0,   0,   0,   0,   0,  0,  0,  0},   /* 15 */
    {  0,   5,   0,   0,   0,  0,  0,  0},   /* 16 */
    {  5,  10,   0,   5,   5,  0,  0,  0},   /* 17 */
    { 10,  15,   5,  10,  10,  0,  0,  0},   /* 18 */
    { 15,  20,  10,  15,  15,  0,  0,  0},   /* 19 */
    { 20,  25,  15,  20,  20,  0,  0,  0},   /* 20 */
    { 25,  30,  20,  25,  25,  0,  0,  0},   /* 21 */
    { 30,  35,  25,  30,  30,  0,  0,  0},   /* 22 */
    { 35,  40,  30,  35,  35,  0,  0,  0},   /* 23 */
    { 40,  45,  35,  40,  40,  0,  0,  0},   /* 24 */
    { 45,  50,  40,  45,  45,  0,  0,  0}    /* 25 */
};
IntT thiefRaceMods[8][7] = {
    {  0,   5,   0,  10,   5,  0,   0},
	 { 10,  -5,   5,   0,   5,  0,   0},
    { 15,   0,  10,   0,   5,  0,   0},
	 {  0,   5,   5,   0,  10,  0,   0},
    {  0,  10,   5,   5,  15,  0,   0},
    {  0,   5,  10,   0,   5,  0,   0},
    {-10,   0, -10,   0, -15,  0,   0},
    { -5,   0,   0,   0,  -5,  0,   0}
};
IntT thiefArmMods[14][8] = {
    {-95, -80, -80, -95, -95, -70, -95, 0},    /* Full Plate   */
    {-95, -80, -80, -95, -95, -70, -95, 0},    /* Field Plate  */
    {-75, -40, -40, -80, -75, -50, -95, 0},    /* Plate        */
    {-50, -20, -20, -60, -50, -30, -90, 0},    /* Banded       */
    {-40, -15, -25, -40, -30, -25, -50, 0},    /* Splint       */
    {-20,  -5,  -5, -10, -10,  -5, -20, 0},    /* Elfin Chain  */
    {-40, -15, -15, -40, -30, -20, -40, 0},    /* Chain        */
    {-75, -40, -40, -80, -75, -50, -95, 0},    /* Bronze Plate */
    {-50, -20, -20, -60, -50, -30, -90, 0},    /* Scale        */
    {-40, -15, -15, -40, -30, -20, -40, 0},    /* Ring         */
    {-30, -10, -10, -20, -20, -10, -30, 0},    /* Studded      */
    {-30, -10, -10, -20, -20, -10, -30, 0},    /* Padded       */
    {  0,   0,   0,   0,   0,   0,   0, 0},    /* Leather      */
    {  5,   0,   0,  10,   5,   0,  10, 0}     /* No Armor     */
};
IntT thiefKitMods[18][8] = {
    {  5, -5, -5,  5,  0,  0,  5,  0},    /* Acrobat        */
	 {  0,  0,  0,  0,  0,  0,  0,  0},    /* Adventurer     */
    {  0,  0,  5,  0,  0,  0,  0, -5},    /* Assassin       */
    { -5,  0, 10,  0,  5,  0, -5, -5},    /* Bandit         */
    { 10, -5, -5,  0,  5,  0,  0, -5},    /* Begger         */
    {  0,  0,  5,  0,  0,  0, -5,  0},    /* Bounty Hunter  */
    { -5,  0,  0,  0,  0,  0,  0,  5},    /* Buccaneer      */
    { -5,  5,  0,  0,  0,  0,  5, -5},    /* Burglar        */
    { 10,  0,  0,  0,  0,  0, -5, -5},    /* Cutpurse       */
    {  0,  5,  5,  0, -5,  0, -5,  5},    /* Fence          */
    { -5,  0,  0,  0,  0,  5,  0,  0},    /* Investigator   */
    {  0,  0,  0, 10, 10,  0,  0,  0},    /* Scout          */
    { -5, -5,  0,  0,  5,  5, -5,  0},    /* Smuggler       */
    {  0,  0,  0,  0,  0,  0,  0,  0},    /* Spy            */
    {  0,  0,  0,  0,  0,  0,  0,  0},    /* Swashbuckler   */
    {  0, -5,  0,  0,  0,  0,  0,  5},    /* Swindler       */
	 {  0,  0,  0,  0,  0,  0,  0,  0},    /* Thug           */
	 {-10,  5,  5,  0,  0,  0,  0,  0}     /* Troubleshooter */
};
ChrT TArea[8][68];
IntT kitAble = -1;
WndT SkillWind, TModWind;

GBL AtrT cAlt[4];

VOID Display_Thief_Skills(NOARG)
{
	 IntT j;

	 for (j = 0; j < 3; j++)
		  if (ClsLvl(CHARNUM, j) != -1 && ClsRch(CHARNUM, j) == ROGUE)
				kitAble = ClsKit(CHARNUM, j);

	 SkillWind = Wopen( 6, 7, 16, 71, BOX_DBL, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW]);
        Fix_Shadow(SkillWind);
        Wtitle(" Thief Skills ", TTL_LFT, cAlt[TCDM_WINDOW]);
        Wprts(0, 19, cAlt[TCDM_WINDOW], "Base Race Dex  Kit  Arm LvTo  With/Out Armor");
        MnuAct(8);
        for (j = 0; j < 8; j++) {
            createTemps(j);
				MnuItm(MsByt(j+1), 1, TArea[j], TArea[j][0], j+1, ITM_NOR, ModifyTSkills, 0, HLP_CLASS_THIEF + j + 1);
		  }
		  MnuEnd(1, MNU_VER|MNU_OMN, 62, 0, cAlt[TCDM_WINDOW], cAlt[TCDM_QUICK], cAlt[TCDM_DESELECT], cAlt[TCDM_BARINPUT]);
		  MnuGet();
	 WVclose(SkillWind);
	 HlpSet(HLP_MAIN);
}

VOID CTYP ModifyTSkills(NOARG)
{
	 IntT k;
	 ChrT temp[5];

	 Wshadoff();
	 Wborder(BOX_SNG);
	 k = MctlTag - 1;
	 HlpSet(HLP_CLASS_THIEF + MctlTag);
	 TModWind = Wopen(9 + k, 12, 11 + k, 27 + strlen(thiefSkills[k]), BOX_DBL, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW]);
		  Fix_Shadow(TModWind);
		  Wprts(0, 1, cAlt[TCDM_WINDOW], thiefSkills[k]);
		  Wgotoxy(0, MsByt(strlen(thiefSkills[k]) + 2));
		  VcurHid(1);
		  if (KwGetFmt(temp, "'Score: '????") == ERR_NUL) {
				cData[CHARNUM].TAbilities[k] = atoi(temp);
				createTemps(k);
        }
        VcurHid(0);
    WVclose(TModWind);
    Wborder(BOX_DBL);
    Fix_Shadow(SkillWind);
}

VOID createTemps(IntT ability)
{
	IntT withArmor, withoutArmor, baseArmor;

	baseArmor =
		thiefBase[ability] +
		thiefRaceMods[ability][ChrRac(CHARNUM)] +
        thiefDexMods[StaDex(CHARNUM) - 9][ability] +
		(kitAble == -1 ? 0 : thiefKitMods[kitAble][ability]) +
		cData[CHARNUM].TAbilities[ability];
	withArmor		= baseArmor + thiefArmMods[cData[CHARNUM].AType][ability];
	withoutArmor	= baseArmor + thiefArmMods[13][ability];

	 sprintf(TArea[ability], "%-18s%3d  %3d  %3d  %3d  %3d %3d  = %4d%%%c/%4d%%%c",
		  thiefSkills[ability],
		  thiefBase[ability],
		  thiefRaceMods[ability][ChrRac(CHARNUM)],
          thiefDexMods[StaDex(CHARNUM) - 9][ability],
		  (kitAble == -1 ? 0 : thiefKitMods[kitAble][ability]),
		  thiefArmMods[cData[CHARNUM].AType][ability],
		  cData[CHARNUM].TAbilities[ability],
		  withArmor > 95 ? 95 : withArmor < 1 ? 1 : withArmor,
		  withArmor > 95 ? 'm' : withArmor < 1 ? 'm' : ' ',
		  withoutArmor > 95 ? 95 : withoutArmor < 1 ? 1 : withoutArmor,
		  withoutArmor > 95 ? 'm' : withoutArmor < 1 ? 'm' : ' '
	 );
}

