/* []---------------------------------------------------------------------[] */
/* |           SThrow.cpp: All code related to Saving Throws.              | */
/* |                                                                       | */
/* |            The SThrow.cpp source code and concepts are                | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __SAVINGTHROW__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <TcxlInp.H>
#include <TcxlCod.H>
#include <TcxlHlp.H>
#include <TcxlKey.H>
#include <TcxlMnu.H>
#include <TcxlVid.H>
#include <TcxlWin.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID Adjust_Saving_Throws(NOARG);
VOID CTYP Add_ST_Adj(NOARG);
VOID SavingThrows(IntT character);

ChrP saving_Throw_Types[] = { "Poison", "Paralyzation/Death Magic", 
    "Rods, Staves and Wands", "Petrification", "Breath Weapons", "Spells"};
WndT STWind;

GBL IntT lAst[2];
GBL AtrT cAlt[4];

VOID Adjust_Saving_Throws(NOARG)
{
    IntT j;
    ChrT temp[4];

    STWind = Wopen(lAst[0], lAst[1], lAst[0] + 7, lAst[1] + 31, 1, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW]);
        Fix_Shadow(STWind);
        Wtitle(" Adjust Saving Throws ", TTL_LFT, cAlt[TCDM_WINDOW]);
        for (j = 0; j < 6; j++) {
            itoa(cData[CHARNUM].STAdj[j], temp, 10);
            temp[strlen(temp)+1] = '\0';
            temp[strlen(temp)] = ' ';
            WprtFmt((BytT)j, 1, cAlt[TCDM_WINDOW], "???", temp);
        }
        MnuAct(6);
            for (j = 0; j < 6; j++) 
                MnuItm((BytT)j, 5, saving_Throw_Types[j], saving_Throw_Types[j][0], j + 1, 0, Add_ST_Adj, 0, HLP_SAVING_THROWS + j + 1);
        MnuEnd( 1, MNU_VER|MNU_OMN, 24, 0, cAlt[TCDM_WINDOW], cAlt[TCDM_QUICK], cAlt[TCDM_DESELECT], cAlt[TCDM_BARINPUT]);
        MnuGet();
    WVclose(STWind);
    HlpSet(HLP_MAIN);
}

VOID CTYP Add_ST_Adj(NOARG)
{
    IntT k;
    ChrT temp[4];
    WndT SModWind;

    Wshadoff();
    Wborder(BOX_SNG);
    k = MctlTag - 1;
	 HlpSet(HLP_SAVING_THROWS + MctlTag);
	 SModWind = Wopen(lAst[0] + 2, lAst[1] + 4, lAst[0] + 4, lAst[1] + strlen(saving_Throw_Types[k]) + 23, 1, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW]);
		  Fix_Shadow(SModWind);
		  Wprts(0, 1, cAlt[TCDM_WINDOW], saving_Throw_Types[k]);
		  Wgotoxy(0, (BytT)(strlen(saving_Throw_Types[k]) + 2));
		  KquePut(Key_BS);
		  VcurHid(1);
		  KwGetFmt(temp, "'Adjustment: '???");
		  VcurHid(0);
	 WVclose(SModWind);
	 cData[CHARNUM].STAdj[k] += atoi(temp);
	 if (cData[CHARNUM].STAdj[k] > 99)
		  cData[CHARNUM].STAdj[k] = 99;
	 if (cData[CHARNUM].STAdj[k] < -99)
		  cData[CHARNUM].STAdj[k] = -99;
	 itoa(cData[CHARNUM].STAdj[k], temp, 10);
	 temp[strlen(temp)+1] = '\0';
	 temp[strlen(temp)] = ' ';
	 WprtFmt((BytT)k, 1, cAlt[TCDM_WINDOW], "???", temp);
	 Wborder(BOX_DBL);
	 Fix_Shadow(STWind);
}

/*
	loop groups until 3
	  if level[loop] is >= 0
		 check for group class
			if group[loop] is priest
			  loop sthrow_type until 6
				 loop level until level < stable[0]
					if currentst > stable[sthrow]
					  currentst = stable[sthrow]
*/

VOID SavingThrows(IntT character)
{
	 IntT j, k, l;
	 IntT priests[7][7] = {
		  {  4, 10, 10, 14, 13, 16, 15},
		  {  7,  9,  9, 13, 12, 15, 14},
		  { 10,  7,  7, 11, 10, 13, 12},
		  { 13,  6,  6, 10,  9, 12, 11},
		  { 16,  5,  5,  9,  8, 11, 10},
		  { 19,  4,  4,  8,  7, 10,  9},
		  { 99,  2,  2,  6,  5,  8,  7}
	 };

	 IntT rogues[6][7] = {
		  {  5, 13, 13, 14, 12, 16, 15},
		  {  9, 12, 12, 12, 11, 15, 13},
		  { 13, 11, 11, 10, 10, 14, 11},
		  { 17, 10, 10,  8,  9, 13,  9},
		  { 21,  9,  9,  6,  8, 12,  7},
		  { 99,  8,  8,  4,  7, 11,  5}
	 };

	 IntT warriors[10][7] = {
		  {  1, 16, 16, 18, 17, 20, 19},
		  {  3, 14, 14, 16, 15, 17, 17},
		  {  5, 13, 13, 15, 14, 16, 16},
		  {  7, 11, 11, 13, 12, 13, 14},
		  {  9, 10, 10, 12, 11, 12, 13},
		  { 11,  8,  8, 10,  9,  9, 11},
		  { 13,  7,  7,  9,  8,  8, 10},
		  { 15,  5,  5,  7,  6,  5,  8},
        { 17,  4,  4,  6,  5,  4,  7},
        { 99,  3,  3,  5,  4,  4,  6}
    };
    
    IntT wizards[5][7] = {
        {  6, 14, 14, 11, 13, 15, 12},
        { 11, 13, 13,  9, 11, 13, 10},
        { 16, 11, 11,  7,  9, 11,  8},
        { 21, 10, 10,  5,  7,  9,  6},
        { 99,  8,  8,  3,  5,  7,  4}
    };

    IntT psionicists[6][7] = {
        {  5, 13, 13, 15, 10, 16, 15},
        {  9, 12, 12, 13,  9, 15, 14},
        { 13, 11, 11, 11,  8, 13, 12},
        { 17, 10, 10,  9,  7, 12, 11},
        { 21,  9,  9,  7,  6, 11,  9},
        { 99,  8,  8,  5,  5,  9,  7}
    };

    for (j = 0; j < 6; j++)
        cData[character].SThrows[j] = 99;
	 for (j = 0; j < 3; j++)
		  if (ClsLvl(character, j) >= 0)
				switch (ClsRch(character, j)) {
					 case PRIEST :
						  for (k = 0; k < 7; k++)
								if (ClsLvl(character, j) < priests[k][0])
									 break;
						  for (l = 1; l < 7; l++)
								if (cData[character].SThrows[l - 1] > priests[k][l])
									 cData[character].SThrows[l - 1] = priests[k][l];
						  break;

					 case ROGUE :
						  for (k = 0; k < 6; k++)
								if (ClsLvl(character, j) < rogues[k][0])
									 break;
						  for (l = 1; l < 7; l++)
								if (cData[character].SThrows[l - 1] > rogues[k][l])
									 cData[character].SThrows[l - 1] = rogues[k][l];
						  break;

					 case WARRIOR :
						  for (k = 0; k < 10; k++)
								if (ClsLvl(character, j) < warriors[k][0])
									 break;
						  for (l = 1; l < 7; l++)
								if (cData[character].SThrows[l - 1] > warriors[k][l])
									 cData[character].SThrows[l - 1] = warriors[k][l];
						  break;

					 case WIZARD :
						  for (k = 0; k < 5; k++)
								if (ClsLvl(character, j) < wizards[k][0])
                            break;
                    for (l = 1; l < 7; l++)
                        if (cData[character].SThrows[l - 1] > wizards[k][l])
                            cData[character].SThrows[l - 1] = wizards[k][l];
                    break;

                case PSIONICIST : 
                    for (k = 0; k < 6; k++)
                        if (ClsLvl(character, j) < psionicists[k][0])
                            break;
                    for (l = 1; l < 7; l++)
                        if (cData[character].SThrows[l - 1] > psionicists[k][l])
                            cData[character].SThrows[l - 1] = psionicists[k][l];
                    break;
            }
}

