/* []---------------------------------------------------------------------[] */
/* |         Cleric.cpp: Display cleric information in a window.           | */
/* |                                                                       | */
/* |             The Cleric.cpp source code and concepts are               | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __CLERIC__

#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <TcxlHlp.H>
#include <TcxlInp.H>
#include <TcxlMnu.H>
#include <TcxlWin.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

ChrP clericSkills[] = {"Skeleton", "Zombie", "Ghoul", "Shadow", "Wight", 
    "Ghast", "Wraith", "Mummy", "Spectre", "Vampire", "Ghost", "Lich", 
    "Special"};
ChrP clericGoodStats[] = {"*D", "*D", "*D", "*D", "*D", " D", " D", " T",
    " T", " 4", " 7", "10", "13", "16", "19", "20", "--", "--", "--", "--",
    "--", "--", "--", "--" };
ChrP clericEvilStats[] = {"*S", "*S", "*S", "*S", "*S", " S", " S", " O",
    " O", " 4", " 7", "10", "13", "16", "19", "20", "--", "--", "--", "--",
    "--", "--", "--", "--" };

GBL AtrT cAlt[4];

VOID Display_Cleric_Skills(NOARG)
{
    IntT j;
    WndT SkillWind;
    ChrT hold[15];
    IntT level = 0;

    for (j = 0; j < 3; j++)
        if (ClsLvl(CHARNUM, j) != -1) {
            if (ClsRch(CHARNUM, j) == PRIEST)
                level = ClsLvl(CHARNUM, j);
            if (ClsRch(CHARNUM, j) == WARRIOR && ClsCls(CHARNUM, j) == 2)
                level = ClsLvl(CHARNUM, j) - 2;
        }
    if (level > 9) {
        if (level == 10 || level == 11)
            level = 10;
        if (level == 12 || level == 13)
            level = 11;
        if (level > 13)
            level = 12;
    }

    if (level > 0) {
        level = 12 - level;
        HlpSet(HLP_CLASS_CLERIC);
        SkillWind = Wopen( 5, 10, 20, 29, BOX_DBL, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW]);
            Fix_Shadow(SkillWind);
            Wtitle(" Cleric Skills ", TTL_LFT, cAlt[TCDM_WINDOW]);
            if (ChrAli(CHARNUM) == 2 || ChrAli(CHARNUM) == 5 || ChrAli(CHARNUM) == 8) {
                Wprts(0, 1, cAlt[TCDM_WINDOW], " Undead   League");
                for (j = 0; j < 13; j++) {
                    sprintf(hold, "%-8s    %2s", clericSkills[j], clericEvilStats[level+j]);
                    Wprts(MsByt(j+1), 1, cAlt[TCDM_WINDOW], hold);
                }
            }
            else {
                Wprts(0, 1, cAlt[TCDM_WINDOW], " Undead   Turned");
                for (j = 0; j < 13; j++) {
                    sprintf(hold, "%-8s    %2s", clericSkills[j], clericGoodStats[level+j]);
                    Wprts(MsByt(j+1), 1, cAlt[TCDM_WINDOW], hold);
                }
            }
            KeyGetc();
        WVclose(SkillWind);
        HlpSet(HLP_MAIN);
    }
}

