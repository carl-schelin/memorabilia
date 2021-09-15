/* []---------------------------------------------------------------------[] */
/* |            InsDel.cpp: Delete and Restore character code.             | */
/* |                                                                       | */
/* |             The InsDel.cpp source code and concepts are               | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __INSDEL__

#include <stdio.h>
#include <string.h>
#include <TcxlHlp.H>
#include <TcxlSel.H>
#include <TcxlVid.H>
#include <TcxlWin.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

GBL VOID Compose_Char_Data(IntT character);
GBL VOID Print_Char(AtrT DrawMode, IntT Whom);
GBL VOID Init_Char(IntT which);
GBL VOID Init_Mons(IntT which);

VOID Delete_Character(NOARG);
VOID Insert_Character(NOARG);
VOID Delete_All(NOARG);
VOID Insert_All(NOARG);

GBL IntT lStdq[2];
GBL AtrT cErrors[4];
GBL AtrT cMessage[4];
GBL AtrT cMain[4];
GBL WndT cPlayer;

/**[ Void_Character ]**********************************************
 * 
 * Open a window and ask if to be wiped from the database
 * check to see if fawning mode is on, if so, fawn
 * check to see if it is monster mode or character mode
 * loop through the database searching for a blank spot
 * when we find a blank spot, copy it into the requested slot
 * compose the data for the current spot (blank now)
 * print it
 * 
 ******************************************************************/

VOID Void_Character(NOARG)
{
    IntT j;
	 WndT VCWind;
	 ChrP YesNo[] = {"Yes", "No", NULL};

    HlpSet(HLP_VOID);
    VCWind = Wopen(lStdq[0], lStdq[1], lStdq[0] + 4, lStdq[1] + 27, BOX_DBL, cErrors[TCDM_WINDOW], cErrors[TCDM_WINDOW]);
        Fix_Shadow(VCWind);
        Wtitle(" Exterminate Character ", TTL_LFT, cErrors[TCDM_WINDOW]);
        Wprts(1, 1, cErrors[TCDM_WINDOW], "Wipe this Character? ");
        j = SelTxt(1, 22, cErrors[TCDM_BARINPUT], YesNo, 0);
    WVclose(VCWind);
    HlpSet(HLP_MAIN);
    if (wStatus == 1) 
        MessageWindow(" My Master is all powerful!");
    if (j == 0)
        if (combatMode == TRUE) {
            if (combatStatus == MONSTER) {
                Init_Mons(MONNUM);
                mData[MONNUM].Status = BLANK;
                Compose_Char_Data(MONNUM);
                NewSheet = 1;
                Print_Char(REVERSE, MONNUM);
            }
            else {
                Init_Char(CHARNUM);
                ChrSta(CHARNUM) = BLANK;
                Compose_Char_Data(CHARNUM);
                NewSheet = 1;
                Print_Char(REVERSE, CHARNUM);
            }
        }
        else {
            Init_Char(CHARNUM);
            ChrSta(CHARNUM) = BLANK;
				Compose_Char_Data(CHARNUM);
				NewSheet = 1;
				Print_Char(REVERSE, CHARNUM);
		  }
}

VOID Delete_All(NOARG)
{
	 IntT j, someAlive = 0;
	 WndT DAWind;
	 ChrP YesNo[] = {"Yes", "No", NULL};

	 for (j = 0; j < totalChars; j++)
		  if (combatMode == TRUE) {
				if (mData[j].Status == ALIVE) {
					 someAlive = 1;
					 break;
				}
		  }
		  else {
				if (ChrSta(j) == ALIVE) {
					 someAlive = 1;
					 break;
				}
		  }

	 if (someAlive == 1) {
		  HlpSet(HLP_GENOCIDE);
		  DAWind = Wopen(lStdq[0], lStdq[1], lStdq[0] + 4, lStdq[1] + 20, BOX_DBL, cErrors[TCDM_WINDOW], cErrors[TCDM_WINDOW]);
				Fix_Shadow(DAWind);
				Wtitle(" Genocide ", TTL_LFT, cErrors[TCDM_WINDOW]);
				Wprts(1, 1, cErrors[TCDM_WINDOW], "Invoke Wrath? ");
				j = SelTxt(1, 15, cErrors[TCDM_BARINPUT], YesNo, 0);
        WVclose(DAWind);
        HlpSet(HLP_MAIN);
        if (wStatus == 1) 
            MessageWindow(" If thine eyes offend thee...");
        if (j == 0)
            for (j = 0; j < totalChars; j++) {
                if (combatMode == TRUE) {
                    if (mData[j].Status == ALIVE) {
                        mData[j].Status = DEAD;
                        Compose_Char_Data(j);
                        /* are we on page one and on monsters displayed on page one? */
                        if (monNumEx == 0 && j <= charsOnScreen)
                            Print_Char(MONNUM == j ? REVERSE : NORMAL, j);
                        /* are we on page two and on monsters displayed on page two? */
                        if (monNumEx > 0 && j > charsOnScreen)
                            Print_Char(MONNUM == j ? REVERSE : NORMAL, j);
                    }
                }
                else {
                    if (ChrSta(j) == ALIVE) {
                        ChrSta(j) = DEAD;
                        cData[j].Changed = YES;
                        ChrHpd(j) = ChrHpt(j) + 10;
                        Compose_Char_Data(j);
                        if (charNumEx == 0 && j <= charsOnScreen)
                            Print_Char(CHARNUM == j ? REVERSE : NORMAL, j);
                        if (charNumEx > 0 && j > charsOnScreen)
                            Print_Char(CHARNUM == j ? REVERSE : NORMAL, j);
                    }
                }
            }
    }
}

VOID Delete_Character(NOARG)
{
    IntT j;
	 WndT DelWind;
	 ChrP YesNo[] = {"Yes", "No", NULL};

	 HlpSet(HLP_DELETE);
	 DelWind = Wopen(lStdq[0], lStdq[1], lStdq[0] + 4, lStdq[1] + 29, BOX_DBL, cErrors[TCDM_WINDOW], cErrors[TCDM_WINDOW]);
		  Fix_Shadow(DelWind);
		  Wtitle(" Delete/Move Character ", TTL_LFT, cErrors[TCDM_WINDOW]);
		  Wprts(1, 1, cErrors[TCDM_WINDOW], "Remove this Character? ");
		  j = SelTxt(1, 24, cErrors[TCDM_BARINPUT], YesNo, 0);
    WVclose(DelWind);
    HlpSet(HLP_MAIN);
    if (wStatus == 1) 
        MessageWindow(" By your command...");
    if (j == 0) 
        if (combatMode == 1) {
            mData[MONNUM].Status = DEAD;
            RePrint = 1;
            Compose_Char_Data(MONNUM);
            Print_Char(REVERSE, MONNUM);
        }
		  else {
				ChrSta(CHARNUM) = DEAD;
				cData[CHARNUM].Changed = YES;
				ChrHpd(CHARNUM) = ChrHpt(CHARNUM) + 10;
				RePrint = 1;
				Compose_Char_Data(CHARNUM);
				Print_Char(REVERSE, CHARNUM);
		  }
}

VOID Insert_All(NOARG)
{
	 IntT j, someDead = 0;
	 WndT IAWind;
	 ChrP YesNo[] = {"Yes", "No", NULL};

	 for (j = 0; j < totalChars; j++)
		  if (combatMode == 1) {
				if (mData[j].Status == DEAD) {
					 someDead = 1;
					 break;
				}
		  }
		  else {
				if (ChrSta(j) == DEAD) {
					 someDead = 1;
					 break;
				}
		  }

	 if (someDead == 1) {
		  HlpSet(HLP_CREATE);
		  IAWind = Wopen(lStdq[0], lStdq[1], lStdq[0] + 4, lStdq[1] + 26, BOX_DBL, cMessage[TCDM_WINDOW], cMessage[TCDM_WINDOW]);
				Fix_Shadow(IAWind);
				Wtitle(" The Resurrection ", TTL_LFT, cMessage[TCDM_WINDOW]);
				Wprts(1, 1, cMessage[TCDM_WINDOW], "Restore the Masses? ");
				j = SelTxt(1, 21, cMessage[TCDM_BARINPUT], YesNo, 0);
        WVclose(IAWind);
        HlpSet(HLP_MAIN);
        if (wStatus == 1) 
            MessageWindow(" Thou art benevolent, Master.");
        if (j == 0) 
            for (j = 0; j < totalChars; j++) {
                if (combatMode == 1) {
                    if (mData[j].Status == DEAD)
                        mData[j].Status = ALIVE;
                    Compose_Char_Data(j);
                    Print_Char(MONNUM == j ? REVERSE : NORMAL, j);
                }
                else {
                    if (ChrSta(j) == DEAD) {
                        ChrHpd(j) = ChrHpt(j) - 1;
                        ChrSta(j) = ALIVE;
                        cData[j].Changed = YES;
                    }
                    Compose_Char_Data(j);
                    Print_Char(CHARNUM == j ? REVERSE : NORMAL, j);
                }
            }
    }
}

VOID Insert_Character(NOARG)
{
    IntT j;
    IntT k = 0;
    IntT length = 0;
    IntT CurrentChar = -1;
    ChrP DeadChars[CHARACTERS];
    IntT DCNumber[CHARACTERS];
    
    for (j = 0; j < totalChars; j++) 
        if (combatMode == 1) {
            if (mData[j].Status == DEAD) {
                if (MONNUM == j)
                    CurrentChar = k;
                DCNumber[k] = k;
                DeadChars[k++] = mData[j].Name;
                if (strlen(mData[j].Name) > (unsigned)length)
                    length = strlen(mData[j].Name);
            }
        }
        else {
            if (ChrSta(j) == DEAD) {
                if (CHARNUM == j)
                    CurrentChar = k;
                DCNumber[k] = j;
                DeadChars[k++] = ChrPer(j);
                if (strlen(ChrPer(j)) > (unsigned)length)
                    length = strlen(ChrPer(j));
            }
        }
    DeadChars[k] = '\0';
    if (combatMode == 1) {
        if (mData[MONNUM].Status == BLANK)
            CurrentChar = 0;
    }
    else {
        if (ChrSta(CHARNUM) == BLANK)
            CurrentChar = 0;
    }

    if (k > 0) {
        HlpSet(HLP_MOVE);
        Wactiv(cPlayer);
        j = SelStr(charNum + 2, 3, charNum + 2, 2 + length, BOX_SPA, cMain[TCDM_WINDOW], cMain[TCDM_WINDOW], cMain[TCDM_DESELECT], DeadChars, CurrentChar, NULL);
        HlpSet(HLP_MAIN);
        if (j != ERR_ARG) {
            if (combatMode == 1) {
                if (mData[MONNUM].Status == DEAD) {
                    if (DCNumber[j] == monNum) {
                        mData[MONNUM].Status = ALIVE;
                    }
                    else {
                        Resurrect_Monster(MONNUM, totalChars);
                        Resurrect_Monster(DCNumber[j], MONNUM);
                        Resurrect_Monster(totalChars, DCNumber[j]);
                        mData[MONNUM].Status = ALIVE;
                    }
                }
                if (mData[MONNUM].Status == BLANK) {
                    Resurrect_Monster(DCNumber[j], MONNUM);
                    mData[MONNUM].Status = ALIVE;
                    mData[DCNumber[j]].Status = BLANK;
                }
                Compose_Char_Data(MONNUM);
                Print_Char(NORMAL, MONNUM);
            }
            else {
                if (ChrSta(CHARNUM) == DEAD) {
                    if (DCNumber[j] == CHARNUM) {
                        ChrSta(CHARNUM) = ALIVE;
                        cData[CHARNUM].Changed = YES;
                        ChrHpd(CHARNUM) = ChrHpt(CHARNUM) - 1;
                    }
                    else {
                        Resurrect_Character(CHARNUM, totalChars);
                        Resurrect_Character(DCNumber[j], CHARNUM);
                        Resurrect_Character(totalChars, DCNumber[j]);
                        ChrSta(CHARNUM) = ALIVE;
                        cData[CHARNUM].Changed = YES;
                        ChrHpd(CHARNUM) = ChrHpt(CHARNUM) - 1;
                    }
                }
                if (ChrSta(CHARNUM) == BLANK) {
                    Resurrect_Character(DCNumber[j], CHARNUM);
                    ChrSta(CHARNUM) = ALIVE;
                    cData[CHARNUM].Changed = YES;
                    ChrHpd(CHARNUM) = ChrHpt(CHARNUM) - 1;
                    ChrSta(DCNumber[j]) = BLANK;
                }
                Compose_Char_Data(CHARNUM);
                Print_Char(REVERSE, CHARNUM);
            }
            if (wStatus == 1) 
                MessageWindow(" Thy powers are awesome, Master.");
        }
    }
}

