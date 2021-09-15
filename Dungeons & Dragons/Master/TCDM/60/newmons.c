/* []---------------------------------------------------------------------[] */
/* |              NewMons.cpp: Edit or create a new monster.               | */
/* |                                                                       | */
/* |             The NewMons.cpp source code and concepts are              | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __NEWMONS__

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

VOID Edit_Monster(NOARG);

GBL VOID Print_Char(AtrT DrawMode, IntT Whom);
GBL VOID Update_Data(IntT whichOne);
GBL VOID Compose_Char_Data(IntT character);
GBL VOID Init_Mons(IntT which);

WndT NewMonWind, EditMonWind;

GBL AtrT cAlt[4];
GBL ChrP alignment[];
GBL ChrP monstersize[];
GBL ChrP flyingclass[];
GBL WndT cWindow;

VOID Edit_Monster(NOARG)
{
	IntT j = 0, k = 0;
	KeyT c = 0;
	AtrT dataColor = 0;
	ChrT temp[80];
	IntT rLoc[] = { 0,  0,  0,  0,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3,
						 4,  4,  4,  4,  4,  4,  6,  6,  6,  6,  6,  6,  7,  7,
						 8,  8,  8,  8,  8,  8,  9,  9,  9,  9, 10, 10, 11, 11,
						12, 12, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
						15, 15};
	IntT cLoc[] = {
		 6, 32,		// Name
		 6, 32,		// Race
		11, 27,		// Alignment
		35, 37,		// Size
		15, 20,		// Movement
		26, 31,		// Fly MR
		35, 37,		// Movement Class
		 6, 11,		// Swim
		19, 24,		// Burrow
		29, 34,		// Web
		 9, 13,		// Base AC
		22, 26,		// with Armor
		33, 37,		// Other
		 0, 26,		// Hit Points and Hit Points Down
		10, 14,		// Hit Dice, number
		16, 19,		// Hit Dice, pluses
		34, 37,		// THAC0
		 8, 26,		// Damage per attack
		32, 37,		// Magic Resistance
		 4, 37,		// Special Attacks
		 4, 37,		// Special Defences
		 4, 37,		// Experience Points
		 0,  6,		// Mithral Pieces
		 6, 12,		// Platinum Pieces
		12, 19,		// Gold Pieces
		19, 25,		// Electrum Pieces
		25, 31,		// Silver Pieces
		31, 37,		// Copper Pieces
		 0, 37};		// Remarks

	MSupdat(TRUE, 0, 0, VidDep - 1, VidWid - 1);
	if (MonSta(MONNUM) == BLANK) {
		NewSheet = 1;
		Init_Mons(MONNUM);   /*  Initialize Monster Stats for this character */
		MonSta(MONNUM) = ALIVE;
		Print_Char(NORMAL, MONNUM);
		MonSta(MONNUM) = BLANK;
	}
	j = 0;

	while (c != Key_Esc) {

		HlpSet(HLP_MONS_EDIT + 1 + (j / 2));
		MSupdat(TRUE, 0, 0, VidDep - 1, VidWid - 1);

		if (MonSta(MONNUM) == DEAD)
			dataColor = cAlt[TCDM_DESELECT];
		else
			dataColor = cAlt[TCDM_WINDOW];
		if (MonSta(MONNUM) == ALIVE && MonHpd(MONNUM) >= MonHpt(MONNUM))
			dataColor = cAlt[TCDM_QUICK];

		Wactiv(cWindow);
		if (j == 2) {
			Wprts( 0, 1, cAlt[TCDM_WINDOW], "Race: ");
			sprintf(Message, "%-25s", MonRac(MONNUM));
			Wprts( 0, 7, dataColor, Message);
		}
		else {
			Wprts( 0, 1, cAlt[TCDM_WINDOW], "Name: ");
			sprintf(Message, "%-25s", MonNam(MONNUM));
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
//				if (MouRow == 4 && MouCol > 39 && MouCol < 69)
//					;
			}
		}

		if (c == Key_M_ClkR) {
			c = Key_Esc;
		}

		Wprtc(rLoc[j], cLoc[j], cAlt[TCDM_WINDOW], ' ');
		Wprtc(rLoc[j + 1], cLoc[j + 1], cAlt[TCDM_WINDOW], ' ');

		switch (c) {
			case Key_Ent :   /*  Enter  */
				MonSta(MONNUM) = ALIVE;
				mData[MONNUM].Changed = YES;
				switch (j) {
					case 0 :    /*  Enter the monster's name  */
					case 1 :
						HlpSet(HLP_MONS_EDIT_USERNAME);
						strcpy(temp, MonNam(MONNUM));
						NewMonWind = Wopen(2, 8, 2, 32, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "************************", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_USERNAME);
							if (EntGet(1) == 1)
								strcpy(MonNam(MONNUM), temp);
						WVclose(NewMonWind);
						break;
					case 2 :     /*  Enter the monster's race  */
					case 3 :
						HlpSet(HLP_MONS_EDIT_RACE);
						strcpy(temp, MonRac(MONNUM));
						NewMonWind = Wopen(2, 8, 2, 32, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "************************", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_RACE);
							if (EntGet(1) == 1)
								strcpy(MonRac(MONNUM), temp);
							WVclose(NewMonWind);
							break;
					case 4 :     /*  What is the monster alignment  */
					case 5 :
						HlpSet(HLP_MONS_EDIT_ALIGNMENT);
						NewMonWind = Wopen(4, 13, 4, 27, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							k = SelTxt(0, 0, cAlt[TCDM_BARINPUT], alignment, mData[MONNUM].Alignment);
							if (k != ERR_ARG)
								MonAli(MONNUM) = k;
							WVclose(NewMonWind);
							Update_Data(ALIGNMENT);
							break;
					case 6 :    /*  What is the monster's size  */
					case 7 :
						HlpSet(HLP_MONS_EDIT_SIZE);
						NewMonWind = Wopen(4, 37, 4, 37, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							k = SelTxt(0, 0, cAlt[TCDM_BARINPUT], monstersize, MonSiz(MONNUM));
							if (k != ERR_ARG)
								MonSiz(MONNUM) = monstersize[k][0];
						WVclose(NewMonWind);
						Update_Data(SIZE);
						break;
					case 8 : /* Walking movement rate */
					case 9 :
						HlpSet(HLP_MONS_EDIT_MOVE);
						NewMonWind = Wopen(5, 17, 5, 20, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "###", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_MOVE);
							if (EntGet(1) == 1)
								mData[MONNUM].Movement[0] = atoi(temp);
						WVclose(NewMonWind);
						Update_Data(MOVE);
						break;
					case 10 : /* flying movement rate */
					case 11 :
						HlpSet(HLP_MONS_EDIT_MOVE);
						NewMonWind = Wopen(5, 28, 5, 30, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "###", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_MOVE);
							if (EntGet(1) == 1)
								mData[MONNUM].Movement[1] = atoi(temp);
						WVclose(NewMonWind);
						Update_Data(FLY);
						break;
					case 12 : /* Flying Movement Class */
					case 13 :
						HlpSet(HLP_MONS_EDIT_MOVE);
						NewMonWind = Wopen(5, 37, 5, 37, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
								k = SelTxt(0, 0, cAlt[TCDM_BARINPUT], flyingclass, mData[MONNUM].Movement[1]);
								if (k != ERR_ARG)
									mData[MONNUM].Movement[2] = flyingclass[k][0];
						WVclose(NewMonWind);
						Update_Data(MOVECLASS);
						break;
					case 14 :  /* Swimming movement rate */
					case 15 :
						HlpSet(HLP_MONS_EDIT_MOVE);
						NewMonWind = Wopen(6, 8, 6, 10, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "###", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_MOVE);
								if (EntGet(1) == 1)
									mData[MONNUM].Movement[3] = atoi(temp);
						WVclose(NewMonWind);
						Update_Data(SWIM);
						break;
					case 16 : /* Burrowing Movement Rate */
					case 17 :
						HlpSet(HLP_MONS_EDIT_MOVE);
						NewMonWind = Wopen(6, 21, 6, 23, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "###", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_MOVE);
								if (EntGet(1) == 1)
									mData[MONNUM].Movement[4] = atoi(temp);
						WVclose(NewMonWind);
						Update_Data(BURROW);
						break;
					case 18 : /* Web movement rate */
					case 19 :
						HlpSet(HLP_MONS_EDIT_MOVE);
						NewMonWind = Wopen(6, 31, 6, 33, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "###", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_MOVE);
								if (EntGet(1) == 1)
									mData[MONNUM].Movement[6] = atoi(temp);
						WVclose(NewMonWind);
						Update_Data(WEB);
						break;
					case 20 : /* Base AC */
					case 21 :
						HlpSet(HLP_MONS_EDIT_BASEAC);
						NewMonWind = Wopen(8, 11, 8, 13, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "###", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_BASEAC);
								if (EntGet(1) == 1)
									MonArm(MONNUM, 0) = atoi(temp);
						WVclose(NewMonWind);
						Update_Data(BASEAC);
						break;
					case 22 : /* With Armor */
					case 23 :
						HlpSet(HLP_MONS_EDIT_WITH);
						NewMonWind = Wopen(8, 24, 8, 26, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "###", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_WITH);
								if (EntGet(1) == 1)
									MonArm(MONNUM, 1) = atoi(temp);
						WVclose(NewMonWind);
						Update_Data(WARMOR);
						break;
					case 24 : /* Other Armor information */
					case 25 :
						HlpSet(HLP_MONS_EDIT_OTHER);
						NewMonWind = Wopen(8, 35, 8, 37, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "###", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_OTHER);
								if (EntGet(1) == 1)
									MonArm(MONNUM, 2) = atoi(temp);
						WVclose(NewMonWind);
						Update_Data(OTHER);
						break;
					case 26 : /* Hit Points */
					case 27 :
						HlpSet(HLP_MONS_EDIT_HITPTS);
						itoa(MonHpt(MONNUM), temp, 10);
						itoa(MonHpd(MONNUM), Message, 10);
						Vgotoxy(10, 16);
						VatrSet(MsAtr((monitor==0 ? LGREY : DGREY) |_BLACK), 3);
						Vgotoxy(10, 26);
						VatrSet(MsAtr((monitor==0 ? LGREY : DGREY) |_BLACK), 3);
						KquePut(Key_BS);
						EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 2);
							EntFld(7, 13, temp, "###", FLD_NUL, 1, FLD_CHG, NULL, HLP_MONS_EDIT_HITPTS);
							EntFld(7, 23, Message, "###", FLD_NUL, 2, FLD_CHG, NULL, HLP_MONS_EDIT_HITPTS);
							if (EntGet(1) != ERR_ARG) {
								MonHpt(MONNUM) = cvtci(temp);
								MonHpd(MONNUM) = cvtci(Message);
								Update_Data(HITPOINTS);
							}
						Vgotoxy(9, 14);
						VatrSet(dataColor, 3);
						Vgotoxy(9, 24);
						VatrSet(dataColor, 3);
						Vgotoxy(10, 16);
						VatrSet(dataColor, 3);
						Vgotoxy(10, 26);
						VatrSet(dataColor, 3);
						break;
					case 28 :  /* Hit dice */
					case 29 :
						HlpSet(HLP_MONS_EDIT_HITDICE);
						NewMonWind = Wopen(10, 12, 10, 15, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "###", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_HITDICE);
								if (EntGet(1) == 1)
									MonHit(MONNUM) = atoi(temp);
						WVclose(NewMonWind);
						Update_Data(HITDICE);
						break;
					case 30 :  /* Any adds to the Hit Dice */
					case 31 :
						HlpSet(HLP_MONS_EDIT_HDADDS);
						NewMonWind = Wopen(10, 18, 10, 21, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "###", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_HDADDS);
								if (EntGet(1) == 1)
									MonHdm(MONNUM) = atoi(temp);
						WVclose(NewMonWind);
						Update_Data(HITDICEADDS);
						break;
					case 32 : /* THAC0 */
					case 33 :
						HlpSet(HLP_MONS_EDIT_THAC0);
						NewMonWind = Wopen(10, 36, 10, 38, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "###", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_THAC0);
								if (EntGet(1) == 1)
									MonTht(MONNUM) = atoi(temp);
						WVclose(NewMonWind);
						Update_Data(HITAC0);
						break;
					case 34 : /* Number of attacks per round and their damage */
					case 35 :
/*
			 1         2         3         4
01234567890123456789012345678901234567890
¦ Damage:                     MR:    % ¦ 1
*/
						break;
					case 36 : /* Magic Resistance */
					case 37 :
						HlpSet(HLP_MONS_EDIT_MR);
						NewMonWind = Wopen(11, 34, 11, 36, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "###", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_MR);
								if (EntGet(1) == 1)
									MonMag(MONNUM) = atoi(temp);
						WVclose(NewMonWind);
						Update_Data(MAGICADJ);
						break;
					case 38 :  /* Special Attacks */
					case 39 :
						HlpSet(HLP_MONS_EDIT_SA);
						strcpy(temp, MonSat(MONNUM));
						NewMonWind = Wopen(12, 5, 12, 37, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "********************************", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_SA);
								if (EntGet(1) == 1)
									strcpy(MonSat(MONNUM), temp);
						WVclose(NewMonWind);
						break;
					case 40 :  /* Special Defenses */
					case 41 :
						HlpSet(HLP_MONS_EDIT_SD);
						strcpy(temp, MonSdf(MONNUM));
						NewMonWind = Wopen(13, 5, 13, 37, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "********************************", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_SD);
								if (EntGet(1) == 1)
									strcpy(MonSdf(MONNUM), temp);
						WVclose(NewMonWind);
						break;
					case 42 :  /* Experience Points */
					case 43 :
						HlpSet(HLP_MONS_EDIT_EP);
						strcpy(temp, mData[MONNUM].Experience);
						NewMonWind = Wopen(14, 5, 14, 37, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "********************************", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_EP);
								if (EntGet(1) == 1)
									strcpy(mData[MONNUM].Experience, temp);
						WVclose(NewMonWind);
						break;
					case 44 :  /* Mithral Pieces */
					case 45 :
						HlpSet(HLP_MONS_EDIT_MONEY);
						NewMonWind = Wopen(16, 2, 16, 5, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "####", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_MONEY);
								if (EntGet(1) == 1)
									MonMon(MONNUM, 0) = atoi(temp);
						WVclose(NewMonWind);
						Update_Data(MITHRAL);
						break;
					case 46 :  /* Platinum Pieces */
					case 47 :
						HlpSet(HLP_MONS_EDIT_MONEY);
						NewMonWind = Wopen(16, 8, 16, 11, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "####", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_MONEY);
								if (EntGet(1) == 1)
									MonMon(MONNUM, 1) = atoi(temp);
						WVclose(NewMonWind);
						Update_Data(PLATINUM);
						break;
					case 48 :  /* Gold Pieces */
					case 49 :
						HlpSet(HLP_MONS_EDIT_MONEY);
						NewMonWind = Wopen(16, 14, 16, 18, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "#####", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_MONEY);
								if (EntGet(1) == 1)
									MonMon(MONNUM, 2) = atoi(temp);
						WVclose(NewMonWind);
						Update_Data(GOLD);
						break;
					case 50 :  /* Electrum Pieces */
					case 51 :
						HlpSet(HLP_MONS_EDIT_MONEY);
						NewMonWind = Wopen(16, 21, 16, 24, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "####", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_MONEY);
								if (EntGet(1) == 1)
									MonMon(MONNUM, 3) = atoi(temp);
						WVclose(NewMonWind);
						Update_Data(ELECTRUM);
						break;
					case 52 :  /* Silver Pieces */
					case 53 :
						HlpSet(HLP_MONS_EDIT_MONEY);
						NewMonWind = Wopen(16, 27, 16, 30, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "####", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_MONEY);
								if (EntGet(1) == 1)
									MonMon(MONNUM, 4) = atoi(temp);
						WVclose(NewMonWind);
						Update_Data(SILVER);
						break;
					case 54 :  /* Copper Pieces */
					case 55 :
						HlpSet(HLP_MONS_EDIT_MONEY);
						NewMonWind = Wopen(16, 33, 16, 36, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "####", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_MONEY);
								if (EntGet(1) == 1)
									MonMon(MONNUM, 5) = atoi(temp);
						WVclose(NewMonWind);
						Update_Data(COPPER);
						break;
					case 56 :  /* Remarks Field */
					case 57 :
						HlpSet(HLP_MONS_EDIT_REMARKS);
						strcpy(temp, MonRem(MONNUM));
						NewMonWind = Wopen(17, 2, 17, 37, BOX_SPA, cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT]);
							Fix_Shadow(NewMonWind);
							KquePut(Key_BS);
							EntDef(cAlt[TCDM_BARINPUT], cAlt[TCDM_BARINPUT], 1);
								EntFld(0, 0, temp, "********************************", FLD_TRM, 1, FLD_CHG, NULL, HLP_MONS_EDIT_REMARKS);
								if (EntGet(1) == 1)
									strcpy(MonRem(MONNUM), temp);
						WVclose(NewMonWind);
						break;
				}
				break;

			case Key_S_Home :   /*  7/Home */
			case Key_Home :
				j = 0;
				break;

			case Key_S_End :   /*  1/End  */
			case Key_End :
				j = 56;
				break;

			case Key_S_Rgt :   /*  6/RtArrow (Esc)  */
			case Key_Rgt :
				c = Key_Esc;
				break;

			case Key_S_Dwn :   /*  2/DnArrow  */
			case Key_Dwn :
				j++;
				j++;
				if (j > 56)
					j = 0;
/*				if ((j == 10 || j == 24) && Edit_Mode == EDITING) {
					j++;
					j++;
				}*/
				break;

			case Key_S_Up :   /*  8/UpArrow  */
			case Key_Up :
				j--;
				j--;
				if (j < 0)
					j = 56;
/*				if ((j == 10 || j == 24) && Edit_Mode == EDITING) {
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
		}
	}
	Compose_Char_Data(MONNUM);
	Print_Char(REVERSE, MONNUM);
	if (MonSta(MONNUM) == BLANK) {
		Wactiv(cWindow);
		WclrWin(cAlt[TCDM_WINDOW]);
	}
	MSupdat(FALSE, 0, 0, VidDep - 1, VidWid - 1);
	HlpSet(HLP_MAIN);
}

