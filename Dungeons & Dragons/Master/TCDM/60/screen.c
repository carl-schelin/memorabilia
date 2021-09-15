/* []---------------------------------------------------------------------[] */
/* |          Screen.cpp: Screen Creation and Maintenance Routines.        | */
/* |                                                                       | */
/* |             The Screen.cpp source code and concepts are               | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __SCREEN__

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <TcxlAtr.H>
#include <TcxlCod.H>
#include <TcxlDef.H>
#include <TcxlInp.H>
#include <TcxlKey.H>
#include <TcxlSel.H>
#include <TcxlVid.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID Screen_Setup(IntT DoLogo);
VOID Main_Screen(NOARG);
VOID Regular(NOARG);
VOID PrintKeyList(NOARG);

GBL VOID Time_Keeping(IntT AddTime);
GBL VOID CSLogo(NOARG);
GBL VOID Compose_Char_Data(IntT character);
GBL VOID Print_Char(AtrT DrawMode, IntT Whom);
GBL VOID Attack_Line(AtrT DrawMode, IntT Whom);

WndT cWindow = 0, cHeader, cStatus, cPlayer, cCombat;
ChrT header[81];
IntT keyMode = 0, keyStatus = 0;

GBL AtrT cAlt[4];
GBL AtrT cMain[4];

VOID Screen_Setup(IntT DoLogo)
{
    VcurHid(0);
    if (DoLogo == TRUE)
		  CSLogo();
    cHeader = Wopen(0, 0, 0, VidWid - 1, BOX_SPA, RED|_LGREY, RED|_LGREY);
    cStatus = Wopen(VidDep - 1, 0, VidDep - 1, VidWid - 1, BOX_SPA, RED|_LGREY, RED|_LGREY);
    cCombat = Wopen(1, 40, VidDep - 2, 79, BOX_SPA, WHITE|_BLACK, WHITE|_BLACK);
    cPlayer = Wopen(1,  0, VidDep - 2, 39, BOX_SPA, WHITE|_BLACK, WHITE|_BLACK);
    Time_Keeping(MAINTAIN);
    Regular();
    Main_Screen();
}

VOID Main_Screen(NOARG)
{
    IntT j, k;

    NewSheet = RePrint = FALSE;
    if (combatMode == TRUE) {
        cWindow = Wopen(1, 40, VidDep - 2, 79, BOX_DBL, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW]);
        combatMode = FALSE;
        for (j = 0; j < charsOnScreen; j++) {
            if (j + charNumEx < totalChars) {
                Compose_Char_Data(j + charNumEx);
                if (ChrSta(j + charNumEx) != BLANK)
                    Print_Char(NORMAL, j + charNumEx);
            }
		  }
        Wactiv(cWindow);
        WclrWin(cAlt[TCDM_WINDOW]);
        combatMode = TRUE;
    }
    else {
        cWindow = Wopen(1, 0, VidDep - 2, 39, BOX_DBL, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW]);
        combatMode = TRUE;
        k = combatStatus;
        for (j = 0; j < charsOnScreen; j++) {
            combatStatus = MONSTER;
            if (j + monNumEx < totalChars) {
                Compose_Char_Data(j + monNumEx);
                if (MonSta(j + monNumEx) != BLANK)
                    Print_Char(NORMAL, j + monNumEx);
            }
            combatStatus = CHARACTER;
            if (j + charNumEx < totalChars) {
                Compose_Char_Data(j + charNumEx);
                if (ChrSta(j + charNumEx) != BLANK)
                    Print_Char(NORMAL, j + charNumEx);
            }
        }
        combatStatus = k;
		  Wactiv(cWindow);
        WclrWin(cAlt[TCDM_WINDOW]);
        combatMode = FALSE;
    }

    if (combatMode == TRUE) {
        Wslide(1, 0);
        k = combatStatus;
        for (j = 0; j < charsOnScreen; j++) {
            combatStatus = MONSTER;
            if (j + monNumEx < totalChars) {
                Compose_Char_Data(j + monNumEx);
                if (MonSta(j + monNumEx) != BLANK)
                    Print_Char(NORMAL, j + monNumEx);
            }
            combatStatus = CHARACTER;
            if (j + charNumEx < totalChars) {
                Compose_Char_Data(j + charNumEx);
                if (ChrSta(j + charNumEx) != BLANK)
                    Print_Char(NORMAL, j + charNumEx);
            }
            combatStatus = k;
        }
        NewSheet = RePrint = TRUE;
		  if (combatStatus == CHARACTER)
            Print_Char(REVERSE, CHARNUM);
        else
            Print_Char(REVERSE, MONNUM);
    }
    else {
        Wactiv(cWindow);
        Wslide(1, 40);
        for (j = 0; j < charsOnScreen; j++) {
            if (j + charNumEx < totalChars) {
                Compose_Char_Data(j + charNumEx);
                if (ChrSta(j + charNumEx) != BLANK)
                    Print_Char(NORMAL, j + charNumEx);
            }
        }
        NewSheet = RePrint = TRUE;
        Print_Char(REVERSE, CHARNUM);
    }
}

VOID Regular(NOARG)
{
    Wactiv(cHeader);
    Wprts(0, 0, cMain[TCDM_BARINPUT], header);
	 Wactiv(cPlayer);
    Wprts(0, 0, cMain[TCDM_QUICK], "NO Pseudonym      ST %% DX CN IN WS CH ");
    Wactiv(cCombat);
    Wprts(0, 1, cMain[TCDM_QUICK], "Race         THAC0   Name         THAC0");
    Wactiv(cStatus);
    Wprts(0, 1, cMain[TCDM_BARINPUT], SysDate(0));
    sprintf(Message, "%8s", SysTime(2));
    Wactiv(cStatus);
    Wprts(0, VidWid - 9, cMain[TCDM_BARINPUT], Message);
    PrintKeyList();
}

VOID PrintKeyList(NOARG)
{
    ChrP cKeyMode[]   = {
        " Normal ", 
        " Number ", 
        "Function"
    };
    ChrP cKeyStatus[] = {
        "Normal", 
        "Shift ", 
        " Ctrl ", 
        " Alt  "
	 };
    ChrP cKeyNum      = {
        "   1 2 3 4 5 6 7 8 9 10   "
    };
    ChrP cKeyText[]   = {
        "  CD F H   L    Q S       ",      /* Normal */
        "           L      S       ",      /* Shift  */
        "  CD       LM     ST      ",      /* Ctrl   */
        "  CDE   I  L   P RST V    "       /* Alt    */
    };

    sprintf(Message, "[%s] [%s] [%s]", cKeyMode[keyMode],
      keyMode == 0 ? cKeyText[keyStatus] : cKeyNum, cKeyStatus[keyStatus]);
    Wactiv(cStatus);
    Wprts(0, 21, cMain[TCDM_BARINPUT], Message);
}

