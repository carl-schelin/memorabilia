/* []---------------------------------------------------------------------[] */
/* |             NewChar.cpp: Edit or create a new character.              | */
/* |                                                                       | */
/* |             The NewChar.cpp source code and concepts are              | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __NEWCHAR__

#include <io.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TcxlEnt.H>
#include <TcxlHlp.H>
#include <TcxlInp.H>
#include <TcxlCod.H>
#include <TcxlMnu.H>
#include <TcxlMou.H>
#include <TcxlSel.H>
#include <TcxlStr.H>
#include <TcxlVid.H>
#include <TcxlWin.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID Edit_Character(IntT Edit_Mode);
VOID CTYP Edit_Statistics(NOARG);
VOID Edit_Classes(IntT multiClass);

GBL VOID Print_Char(AtrT DrawMode, IntT Whom);
GBL VOID Update_Data(IntT whichOne);
GBL VOID Adjust_Saving_Throws(NOARG);
GBL VOID Activate_Light(NOARG);
GBL VOID Compose_Char_Data(IntT character);
GBL VOID SavingThrows(IntT character);
GBL VOID Init_Char(IntT which);

WndT NewWind, EditWind;

GBL IntT dexterity[];
GBL IntT lExist[2];
GBL AtrT cAlt[4];
GBL AtrT cMain[4];
GBL ChrP alignment[];
GBL ChrP armorTypes[];
GBL ChrP shieldTypes[];
GBL ChrP helmTypes[];
GBL ChrP light_Types[];
GBL IntT light_Times[6];
GBL ChrP race[];
GBL ChrP groups[];
GBL ChrP classWarrior[];
GBL ChrP classWizard[];
GBL ChrP classPriest[];
GBL ChrP classRogue[];
GBL ChrP classPsionicist[];
GBL IntT Armor_Points[14][13];
GBL IntT Shield_Points[7][2];
GBL IntT Helm_Points[7][2];
GBL IntT Armor_Max[14];
GBL WndT cWindow;

/* have to edit these fields:
    IntT  ACAdj;                     Other Adjustments to AC
*/
VOID Edit_Character(IntT Edit_Mode)
{
    IntT j = 0, k = 0;
    KeyT c = 0;
    AtrT dataColor = 0;
    ChrT temp[80];
    /* 1/2 - Names, 3 - Hit Points, 4 - Alignment, 5 - Psionic, 6 - Race,   */
    /* 7/8/9 - Archtype/level/class, 10 - Armor/points, 11 - Shield/points, */
    /* 12 - Helm/points, 13 - ST Modifiers, 14 - Light/left, 15 - Exper     */
    /*              1   1   2   2   3   3   4   4   5   5   6   6   7   7   */
    /*      8   8   9   9  10  10  11  11  12  12  13  13  14  14  15  15   */
    IntT rLoc[] = { 0,  0,  0,  0,  2,  2,  3,  3,  3,  3,  4,  4,  6,  6,  7,  7,  8,  8, 11, 11, 12, 12, 13, 13, 15, 15, 19, 19, 20, 20};
    IntT cLoc[] = { 6, 31, 11, 36,  0, 27, 11, 28, 35, 37,  6, 15,  0, 37,  0, 37,  0, 37,  0, 36,  0, 36,  0, 36,  0, 37,  0, 37,  0, 18};

    MSupdat(TRUE, 0, 0, VidDep - 1, VidWid - 1);
    if (ChrSta(CHARNUM) == BLANK) {
        NewSheet = 1;
        Init_Char(CHARNUM);         /* Initialize Character stats */
        ChrSta(CHARNUM) = ALIVE;
        Print_Char(NORMAL, CHARNUM);
        ChrSta(CHARNUM) = BLANK;
    }
    j = 0;

    while (c != Key_Esc) {

		  HlpSet(HLP_CHAR_EDIT + 1 + (j / 2));
		  MSupdat(TRUE, 0, 0, VidDep - 1, VidWid - 1);

		  if (ChrSta(CHARNUM) == DEAD)
				dataColor = cAlt[TCDM_DESELECT];
		  else
				dataColor = cAlt[TCDM_WINDOW];
		  if (ChrSta(CHARNUM) == ALIVE && ChrHpd(CHARNUM) >= ChrHpt(CHARNUM))
				dataColor = cAlt[TCDM_QUICK];

		  Wactiv(cWindow);
		  if (j == 2) {
				Wprts( 0, 1, cAlt[TCDM_WINDOW], "Pseudonym: ");
				sprintf(Message, "%-25s", ChrPer(CHARNUM));
				Wprts( 0, 12, dataColor, Message);
		  }
		  else {
				Wprts( 0, 1, cAlt[TCDM_WINDOW], "Name: ");
				sprintf(Message, "%-30s", ChrChr(CHARNUM));
				Wprts( 0, 7, dataColor, Message);
		  }

        Wprtc(rLoc[j], cLoc[j], cAlt[TCDM_QUICK], '[');
        Wprtc(rLoc[j + 1], cLoc[j + 1], cAlt[TCDM_QUICK], ']');

        for (;;) {
            if (kbhit()) {
                c = KeyGetc();
                break;
            }
            MSstat();
            if (MouLbtn == 0x0001) {
                c = Key_M_ClkL;
                while (MouLbtn == 0x0001)
                    MSstat();
                break;
            }
            if (MouRbtn == 0x0001) {
                c = Key_M_ClkR;
                while (MouRbtn == 0x0001)
                    MSstat();
                break;
            }
        }

        if (c == Key_M_ClkL) {
            if (MouRow > 1 && MouRow < (VidDep -2) && MouCol > 39 && MouCol < 79) {
                Wprtc(rLoc[j], cLoc[j], cAlt[TCDM_WINDOW], ' ');
                Wprtc(rLoc[j + 1], cLoc[j + 1], cAlt[TCDM_WINDOW], ' ');
//                if (MouRow == 4 && MouCol > 39 && MouCol < 69)
//                    ;
            }
        }

        if (c == Key_M_ClkR) {
            c = Key_Esc;
        }

        Wprtc(rLoc[j], cLoc[j], cAlt[TCDM_WINDOW], ' ');
        Wprtc(rLoc[j + 1], cLoc[j + 1], cAlt[TCDM_WINDOW], ' ');

        switch (c) {
            case Key_Ent :   /*  Enter  */
                ChrSta(CHARNUM) = ALIVE;
                cData[CHARNUM].Changed = YES;
                switch (j) {
                    case 0 :    /*  Enter the character's name  */
                    case 1 :
								HlpSet(HLP_CHAR_EDIT_USERNAME);
								strcpy(temp, ChrChr(CHARNUM));
								NewWind = Wopen(2, 48, 2, 71, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
									 Fix_Shadow(NewWind);
									 KquePut(Key_BS);
									 EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
										  EntFld(0, 0, temp, "************************", FLD_TRM, 1, FLD_CHG, NULL, HLP_CHAR_EDIT_USERNAME);
                            if (EntGet(1) == 1) {
                                strcpy(ChrChr(CHARNUM), temp);
                                strncpy(ChrFil(CHARNUM), temp, 8);
                                sprintf(Message, "%s\\%s.Cha", saveDir, ChrFil(CHARNUM));
                                if (access(Message, 0) == 0)
                                    MessageWindow2(" That file exists, to avoid overwriting\n", " it, please type in a new name.");
                            }
                        WVclose(NewWind);
                        break;
                    case 2 :     /*  Enter the player's name  */
						  case 3 :
								HlpSet(HLP_CHAR_EDIT_PSEUDONYM);
                        strcpy(temp, ChrPer(CHARNUM));
                        NewWind = Wopen(2, 53, 2, 76, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
                            Fix_Shadow(NewWind);
                            KquePut(Key_BS);
                            EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
                                EntFld(0, 0, temp, "************************", FLD_TRM, 1, FLD_CHG, NULL, HLP_CHAR_EDIT_PSEUDONYM);
                            if (EntGet(1) == 1)
                                strcpy(ChrPer(CHARNUM), temp);
                        WVclose(NewWind);
                        break;
                    case 4 :     /*  Edit the hit points and down  */
                    case 5 :
                        HlpSet(HLP_CHAR_EDIT_HITPTS);
                        itoa(ChrHpt(CHARNUM), temp, 10);
                        itoa(ChrHpd(CHARNUM), Message, 10);
								Vgotoxy(5, 56);
								VatrSet(MsAtr((monitor==0 ? LGREY : DGREY) |_BLACK), 3);
								Vgotoxy(5, 66);
								VatrSet(MsAtr((monitor==0 ? LGREY : DGREY) |_BLACK), 3);
								KquePut(Key_BS);
								EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 2);
									 EntFld(2, 13, temp, "###", FLD_NUL, 1, FLD_CHG, NULL, HLP_CHAR_EDIT_HITPTS);
									 EntFld(2, 23, Message, "###", FLD_NUL, 2, FLD_CHG, NULL, HLP_CHAR_EDIT_HITPTS);
								if (EntGet(1) != ERR_ARG) {
									 cData[CHARNUM].HitPoints = cvtci(temp);
									 cData[CHARNUM].HPDown = cvtci(Message);
									 Update_Data(HITPOINTS);
								}
								Vgotoxy(4, 54);
								VatrSet(dataColor, 3);
								Vgotoxy(4, 64);
								VatrSet(dataColor, 3);
								Vgotoxy(5, 56);
								VatrSet(dataColor, 3);
								Vgotoxy(5, 66);
								VatrSet(dataColor, 3);
								break;
						  case 6 :    /*  What is the character's alignment  */
						  case 7 :
								HlpSet(HLP_CHAR_EDIT_ALIGNMENT);
                        NewWind = Wopen(5, 53, 5, 67, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
                            Fix_Shadow(NewWind);
                            k = SelTxt(0, 0, cAlt[TCDM_BARINPUT], alignment, cData[CHARNUM].Alignment);
                            if (k != ERR_ARG)
                                ChrAli(CHARNUM) = k;
                        WVclose(NewWind);
                        Update_Data(ALIGNMENT);
                        break;
                    case 8 :  /*  is he psionic? (probably replaced by psionicist)  */
                    case 9 : 
                        HlpSet(HLP_CHAR_EDIT_PSIONICS);
                        if (cData[CHARNUM].Psionic == 'N')
                            cData[CHARNUM].Psionic = 'Y';
                        else
                            cData[CHARNUM].Psionic = 'N';
                        Update_Data(PSIONIC);
                        break;
                    case 10 :  /*  what is his race  */
                    case 11 : 
                        HlpSet(HLP_CHAR_EDIT_RACE);
                        NewWind = Wopen(6, 48, 6, 55, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
                            Fix_Shadow(NewWind);
                            k = SelTxt(0, 0, cAlt[TCDM_BARINPUT], race, ChrRac(CHARNUM));
                            if (k != ERR_ARG)
                                ChrRac(CHARNUM) = k;
                        WVclose(NewWind);
                        Update_Data(RACE);
                        break;
                    case 12 :
                    case 13 : 
                        HlpSet(HLP_CHAR_EDIT_CLASS1);
                        Edit_Classes(0);
                        break;
                    case 14 :
                    case 15 : 
                        HlpSet(HLP_CHAR_EDIT_CLASS2);
                        Edit_Classes(1);
                        break;
                    case 16 :
                    case 17 : 
                        HlpSet(HLP_CHAR_EDIT_CLASS3);
                        Edit_Classes(2);
                        break;
                    case 18 :
                    case 19 : 
                        HlpSet(HLP_CHAR_EDIT_ARMOR);
                        NewWind = Wopen(13, 50, 13, 66, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
                            Fix_Shadow(NewWind);
                            k = SelTxt(0, 0, cAlt[TCDM_BARINPUT], armorTypes, cData[CHARNUM].AType);
                            if (k != ERR_ARG) 
                                cData[CHARNUM].AType = k;
                        WVclose(NewWind);
                        sprintf(Message, "%-17s", armorTypes[cData[CHARNUM].AType]);
                        Wprts(11, 9, cAlt[TCDM_WINDOW], Message);
                        itoa(cData[CHARNUM].APoints, temp, 10);
                        if (cData[CHARNUM].APoints <= 0)
                            itoa(Armor_Max[cData[CHARNUM].AType], temp, 10);
                        for (k = 0; k < 14; k++) {
                            if (Armor_Points[cData[CHARNUM].AType][k] < 999) {
                                if (cData[CHARNUM].APoints <= 0)
                                    itoa(Armor_Points[cData[CHARNUM].AType][k], temp, 10);
                                break;
                            }
                        }
                        if (cData[CHARNUM].AType < 13) {
                            NewWind = Wopen(13, 70, 13, 72, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
                                Fix_Shadow(NewWind);
                                EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
                                    EntFld(0, 0, temp, "999", FLD_DEC, 1, FLD_CHG, NULL, HLP_CHAR_EDIT_APOINTS);
                                if (EntGet(1) != ERR_ARG)
                                    cData[CHARNUM].APoints = cvtci(temp);
                            WVclose(NewWind);
                        }
                        sprintf(Message, "%3d", cData[CHARNUM].APoints);
                        Wprts(11, 29, cAlt[TCDM_WINDOW], Message);
                        itoa(cData[CHARNUM].AMagical, temp, 10);
                        NewWind = Wopen(13, 74, 13, 76, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
                            Fix_Shadow(NewWind);
                            EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
                                EntFld(0, 0, temp, "999", FLD_DEC, 1, FLD_CHG, NULL, HLP_CHAR_EDIT_AMAGIC);
                            if (EntGet(1) != ERR_ARG)
                                cData[CHARNUM].AMagical = cvtci(temp);
                        WVclose(NewWind);
                        Update_Data(ARMORCLASS);
                        Update_Data(ARMOR);
                        HlpSet(1);
                        break;
                    case 20 :
                    case 21 : 
                        HlpSet(HLP_CHAR_EDIT_SHIELD);
                        NewWind = Wopen(14, 50, 14, 64, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
                            Fix_Shadow(NewWind);
                            k = SelTxt(0, 0, cAlt[TCDM_BARINPUT], shieldTypes, cData[CHARNUM].SType);
                            if (k != ERR_ARG)
                                cData[CHARNUM].SType = k;
                        WVclose(NewWind);
                        sprintf(Message, "%-15s", shieldTypes[cData[CHARNUM].SType]);
                        Wprts(12, 9, cAlt[TCDM_WINDOW], Message);
                        itoa(cData[CHARNUM].SPoints, temp, 10);
                        if (cData[CHARNUM].SPoints <= 0)
                            itoa(Shield_Points[cData[CHARNUM].SType][1], temp, 10);
                        if (cData[CHARNUM].SType < 6) {
                            NewWind = Wopen(14, 71, 14, 72, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
                                Fix_Shadow(NewWind);
                                EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
                                    EntFld(0, 0, temp, "99", FLD_DEC, 1, FLD_CHG, NULL, HLP_CHAR_EDIT_SPOINTS);
                                if (EntGet(1) != ERR_ARG)
                                    cData[CHARNUM].SPoints = cvtci(temp);
                            WVclose(NewWind);
                        }
                        sprintf(Message, "%2d", cData[CHARNUM].SPoints);
                        Wprts(12, 30, cAlt[TCDM_WINDOW], Message);
                        itoa(cData[CHARNUM].SMagical, temp, 10);
                        NewWind = Wopen(14, 74, 14, 76, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
                            Fix_Shadow(NewWind);
                            EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
                                EntFld(0, 0, temp, "999", FLD_DEC, 1, FLD_CHG, NULL, HLP_CHAR_EDIT_SMAGIC);
                            if (EntGet(1) != ERR_ARG)
                                cData[CHARNUM].SMagical = cvtci(temp);
                        WVclose(NewWind);
                        Update_Data(ARMORCLASS);
                        Update_Data(SHIELD);
                        HlpSet(1);
                        break;
                    case 22 :
                    case 23 : 
                        HlpSet(HLP_CHAR_EDIT_HELM);
                        NewWind = Wopen(15, 50, 15, 60, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
                            Fix_Shadow(NewWind);
                            k = SelTxt(0, 0, cAlt[TCDM_BARINPUT], helmTypes, cData[CHARNUM].HType);
                            if (k != ERR_ARG)
                                cData[CHARNUM].HType = k;
                        WVclose(NewWind);
                        sprintf(Message, "%-11s", helmTypes[cData[CHARNUM].HType]);
                        Wprts(13, 9, cAlt[TCDM_WINDOW], Message);
                        itoa(cData[CHARNUM].HPoints, temp, 10);
                        if (cData[CHARNUM].HPoints <= 0)
                            itoa(Helm_Points[cData[CHARNUM].HType][1], temp, 10);
                        if (cData[CHARNUM].HType < 6) {
                            NewWind = Wopen(15, 71, 15, 72, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
                                Fix_Shadow(NewWind);
                                EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
                                    EntFld(0, 0, temp, "99", FLD_DEC, 1, FLD_CHG, NULL, HLP_CHAR_EDIT_HPOINTS);
                                if (EntGet(1) != ERR_ARG)
                                    cData[CHARNUM].HPoints = cvtci(temp);
                            WVclose(NewWind);
                        }
                        sprintf(Message, "%2d", cData[CHARNUM].HPoints);
                        Wprts(13, 30, cAlt[TCDM_WINDOW], Message);
                        itoa(cData[CHARNUM].HMagical, temp, 10);
                        NewWind = Wopen(15, 74, 15, 76, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
                            Fix_Shadow(NewWind);
                            EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
                                EntFld(0, 0, temp, "999", FLD_DEC, 1, FLD_CHG, NULL, HLP_CHAR_EDIT_HMAGIC);
                            if (EntGet(1) != ERR_ARG)
                                cData[CHARNUM].HMagical = cvtci(temp);
                        WVclose(NewWind);
                        Update_Data(ARMORCLASS);
                        Update_Data(HELM);
                        HlpSet(1);
                        break;
                    case 24 :
                    case 25 : 
                        HlpSet(HLP_CHAR_EDIT_STHROW);
                        if (Edit_Mode != EDITING)
                            Adjust_Saving_Throws();
                            Update_Data(SAVINGTHROWS);
                        break;
                    case 26 :
                    case 27 : 
                        HlpSet(HLP_CHAR_EDIT_LIGHT);
                        NewWind = Wopen(21, 49, 21, 61, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
                            Fix_Shadow(NewWind);
                            k = SelTxt(0, 0, cAlt[TCDM_BARINPUT], light_Types, LitTyp(CHARNUM));
                            if (k != ERR_ARG) {
                                LitTyp(CHARNUM) = k;
                                LitLft(CHARNUM) = light_Times[LitTyp(CHARNUM)];
                            }
                        WVclose(NewWind);
                        Update_Data(LIGHT);
                        break;
                    case 28 :
                    case 29 :
                        HlpSet(HLP_CHAR_EDIT_EXPERIENCE);
                        itoa(cData[CHARNUM].Experience, temp, 10);
                        NewWind = Wopen(22, 54, 22, 58, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
                            Fix_Shadow(NewWind);
                            EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
                                EntFld(0, 0, temp, "99999", FLD_DEC, 1, FLD_CHG, NULL, HLP_CHAR_EDIT_EXPERIENCE);
                            if (EntGet(1) != ERR_ARG)
                                cData[CHARNUM].Experience = cvtci(temp);
                        WVclose(NewWind);
                        sprintf(Message, "%5d", cData[CHARNUM].Experience);
                        Wprts(20, 13, cAlt[TCDM_WINDOW], Message);
                    }
                break;
    
            case Key_S_Home :   /*  7/Home */
            case Key_Home :
                j = 0;
                break;
    
            case Key_S_End :   /*  1/End  */
            case Key_End :
                j = 28;
                break;

            case Key_S_Lft :   /*  4/LtArrow (Esc)  */
            case Key_Lft :
                c = Key_Esc;
                break;

            case Key_S_Dwn :   /*  2/DnArrow  */
            case Key_Dwn :
                j++;
                j++;
                if (j > 28)
                    j = 0;
/*                if ((j == 10 || j == 24) && Edit_Mode == EDITING) {
                    j++;
                    j++;
                }*/
                break;
                
            case Key_S_Up :   /*  8/UpArrow  */
            case Key_Up :
                j--;
                j--;
                if (j < 0) 
                    j = 28;
/*                if ((j == 10 || j == 24) && Edit_Mode == EDITING) {
                    j--;
                    j--;
                }*/
                break;
    
            case Key_S_PgUp :   /*  9/PgUp  */
            case Key_PgUp : 
                break;
    
            case Key_S_PgDn :   /*  3/PgDn  */
            case Key_PgDn : 
                break;

            case Key_A_S :  /*  Alt S to modify statistics  */
                HlpSet(HLP_CHAR_EDIT_STATS);
                cData[CHARNUM].Changed = YES;
                NewWind = Wopen(5, 7, 12, 31, BOX_DBL, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW]);
                    Fix_Shadow(NewWind);
                    for (j = 0; j < 6; j++) {
                        sprintf(Message, ": %2d", cData[CHARNUM].Stats[j]);
                        Wprts(MsByt(j), 13, cAlt[TCDM_WINDOW], Message);
                    }
                    sprintf(Message, "%3d%%", StaStp(CHARNUM));
                    Wprts(0, 18, cAlt[TCDM_WINDOW], Message);
                    MnuAct(6);
                        MnuItm(0, 1, "Strength",     'S', 1, ITM_NOR, Edit_Statistics, 0, HLP_CHAR_EDIT_STATS);
                        MnuItm(1, 1, "Dexterity",    'D', 2, ITM_NOR, Edit_Statistics, 0, HLP_CHAR_EDIT_STATS);
                        MnuItm(2, 1, "Constitution", 'C', 3, ITM_NOR, Edit_Statistics, 0, HLP_CHAR_EDIT_STATS);
                        MnuItm(3, 1, "Intelligence", 'I', 4, ITM_NOR, Edit_Statistics, 0, HLP_CHAR_EDIT_STATS);
                        MnuItm(4, 1, "Wisdom",       'W', 5, ITM_NOR, Edit_Statistics, 0, HLP_CHAR_EDIT_STATS);
                        MnuItm(5, 1, "cHarisma",     'H', 6, ITM_NOR, Edit_Statistics, 0, HLP_CHAR_EDIT_STATS);
                    MnuEnd(1, MNU_HOR|MNU_OMN, 12, 0, cAlt[TCDM_WINDOW], cAlt[TCDM_QUICK], cAlt[TCDM_DESELECT], cAlt[TCDM_BARINPUT]);
                    MnuGet();
                    ChrSta(CHARNUM) = ALIVE;
                WVclose(NewWind);
                break;

        }
    }
    SavingThrows(CHARNUM);
    Update_Data(SAVINGTHROWS);
    Compose_Char_Data(CHARNUM);
    Print_Char(REVERSE, CHARNUM);
    if (ChrSta(CHARNUM) == BLANK) {
        Wactiv(cWindow);
        WclrWin(cAlt[TCDM_WINDOW]);
    }
    MSupdat(FALSE, 0, 0, VidDep - 1, VidWid - 1);
	 HlpSet(HLP_MAIN);
}

VOID CTYP Edit_Statistics(NOARG)
{
	 KeyT c = Key_A_F;  /*  fill it with something, what the hell  */

	 sprintf(Message, "%2d", cData[CHARNUM].Stats[(MctlTag - 1)]);
	 Wprts(MsByt((MctlTag - 1)), 15, cAlt[TCDM_BARINPUT], Message);
	 while (c != Key_Ent) {
		  if (kbhit())
				c = KeyGetc();
		  else
				c = Key_H;
		  if (c == Key_PlsG)
				if ((MctlTag - 1) == 0 && cData[CHARNUM].Stats[(MctlTag - 1)] == 18) {
					 StaStp(CHARNUM)++;
					 if (StaStp(CHARNUM) > 100) {
						  StaStp(CHARNUM) = 0;
						  StaStr(CHARNUM)++;
					 }
            }
            else {
                cData[CHARNUM].Stats[(MctlTag - 1)]++;
                if (cData[CHARNUM].Stats[(MctlTag - 1)] > 25)
                    cData[CHARNUM].Stats[(MctlTag - 1)] = 25;
            }
        if (c == Key_MinG)
            if ((MctlTag - 1) == 0 && cData[CHARNUM].Stats[(MctlTag - 1)] == 18) {
                if (StaStp(CHARNUM) == 0)
                    StaStr(CHARNUM)--;
                else 
                    StaStp(CHARNUM)--;
                if (StaStp(CHARNUM) < 0)
                    StaStp(CHARNUM) = 0;
            }
            else {
                cData[CHARNUM].Stats[(MctlTag - 1)]--;
                if ((MctlTag - 1) == 0 && cData[CHARNUM].Stats[(MctlTag - 1)] == 18)
                    StaStp(CHARNUM) = 100;
                if (cData[CHARNUM].Stats[(MctlTag - 1)] < 1)
                    cData[CHARNUM].Stats[(MctlTag - 1)] = 1;
            }
        if ((MctlTag - 1) == 0 && cData[CHARNUM].Stats[(MctlTag - 1)] == 18) {
            sprintf(Message, "%3d", StaStp(CHARNUM));
            Wprts(0, 18, cAlt[TCDM_BARINPUT], Message);
        }
        sprintf(Message, "%2d", cData[CHARNUM].Stats[(MctlTag - 1)]);
        Wprts(MsByt((MctlTag - 1)), 15, cAlt[TCDM_BARINPUT], Message);
    }
    if ((MctlTag - 1) == 0 && cData[CHARNUM].Stats[(MctlTag - 1)] == 18) {
        sprintf(Message, "%3d", StaStp(CHARNUM));
        Wprts(0, 18, cAlt[TCDM_WINDOW], Message);
    }
    sprintf(Message, "%2d", cData[CHARNUM].Stats[(MctlTag - 1)]);
    Wprts(MsByt((MctlTag - 1)), 15, cAlt[TCDM_WINDOW], Message);
}

VOID Edit_Classes(IntT multiClass)
{
    IntT k, cOffset = 0;
    ChrT temp[80];
    WndT EdWind;

    Wprts(6 + multiClass, 1, cAlt[TCDM_WINDOW], "                                    ");
    EdWind = Wopen(8 + multiClass, 42, 8 + multiClass, 51, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
        Fix_Shadow(EdWind);
        k = SelTxt(0, 0, cAlt[TCDM_BARINPUT], groups, ClsRch(CHARNUM, multiClass));
        if (k != ERR_ARG) {
            ClsRch(CHARNUM, multiClass) = k;
            ChrSta(CHARNUM) = ALIVE;
        }
    WVclose(EdWind);
    sprintf(Message, "%s", groups[ClsRch(CHARNUM, multiClass)]);
    Wprts(6 + multiClass, 1, cAlt[TCDM_WINDOW], Message);
    cOffset = strlen(groups[ClsRch(CHARNUM, multiClass)]);
    itoa(ClsLvl(CHARNUM, multiClass), temp, 10);
    EdWind = Wopen(8 + multiClass, 43 + cOffset, 8 + multiClass, 46 + cOffset, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
        Fix_Shadow(EdWind);
        EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
            EntFld(0, 0, temp, "9999", FLD_DEC, 1, FLD_CHG, NULL, HLP_CHAR_EDIT_CLASS1 + multiClass);
        k = EntGet(1);
        if (k != ERR_ARG) {
            ClsLvl(CHARNUM, multiClass) = cvtci(temp);
        }
    WVclose(EdWind);
    sprintf(Message, " %d", ClsLvl(CHARNUM, multiClass));
    Wprts(6 + multiClass, 1 + cOffset++, cAlt[TCDM_WINDOW], Message);
    if (ClsLvl(CHARNUM, multiClass) > 9)
        cOffset++;
    if (ClsLvl(CHARNUM, multiClass) > 99)
        cOffset++;
    if (ClsLvl(CHARNUM, multiClass) >= 0) {
        switch (ClsRch(CHARNUM, multiClass)) {
            case WARRIOR    : k = 6;  break;
            case WIZARD     : k = 10; break;
            case PRIEST     : k = 23; break;
            case ROGUE      : k = 7;  break;
            case PSIONICIST : k = 9;  break;
        }
        EdWind = Wopen(8 + multiClass, 44 + cOffset, 8 + multiClass, 44 + k + cOffset, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
            Fix_Shadow(EdWind);
            switch (ClsRch(CHARNUM, multiClass)) {
                case WARRIOR : 
                    k = SelTxt(0, 0, cAlt[TCDM_BARINPUT], classWarrior,    ClsCls(CHARNUM, multiClass));
                    break;
                case WIZARD : 
                    k = SelTxt(0, 0, cAlt[TCDM_BARINPUT], classWizard,     ClsCls(CHARNUM, multiClass));
                    break;
                case PRIEST : 
                    k = SelTxt(0, 0, cAlt[TCDM_BARINPUT], classPriest,     ClsCls(CHARNUM, multiClass));
                    break;
                case ROGUE : 
                    k = SelTxt(0, 0, cAlt[TCDM_BARINPUT], classRogue,      ClsCls(CHARNUM, multiClass));
                    break;
                case PSIONICIST : 
                    k = SelTxt(0, 0, cAlt[TCDM_BARINPUT], classPsionicist, ClsCls(CHARNUM, multiClass));
                    break;
            }
            if (k != ERR_ARG)
                ClsCls(CHARNUM, multiClass) = k;
        WVclose(EdWind);
    }
    Update_Data(CLASS);
}

