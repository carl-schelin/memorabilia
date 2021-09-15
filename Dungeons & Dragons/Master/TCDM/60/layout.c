/* []---------------------------------------------------------------------[] */
/* |          Layout.cpp: Edit marching order and combat layouts           | */
/* |                                                                       | */
/* |             The Layout.cpp source code and concepts are               | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

/* Have only Vgets() functions in this ... */

#define __LAYOUT__

#include <io.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <TcxlBox.H>
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

VOID Edit_Layout(IntT Edit_Mode);
VOID Drawing_Chars(IntT charCtrl, IntT pRow, IntT pCol);
VOID Selection_Box(NOARG);
VOID Change_Matrix(ChrT SelChar);

GBL AtrT cAlt[4];
GBL WndT cWindow;

WndT SelWind;

/* 
  edit layout
  
  arrow left places a < so you can select a character to place.
  allow deletion of a character number
  move around with cursor keys maybe <ins> to move to list or maybe a 
    selection menu.
  don't forget mouse
  line drawing as well, maybe insert any character, but want to tie in 
    each of the numbers so that they highlight when on that character and
    die (show damage) when appropriate.
  space over any but character data
  how to store information (or how to retrieve)
  type in anything I want, but ins/del only to modify character info

*/

VOID Edit_Layout(IntT Edit_Mode)
{
    IntT j = 0;
    KeyT c = 0;
    KeyT exitCode;
    IntT pRow = 0, pCol = 0;
    IntT overWrite = FALSE;
LCL WrdT charCtrl = 0;
    ChrT underChar[1];

    Edit_Mode = Edit_Mode; /* just to fool the compiler */
    Selection_Box();
    Wactiv(cWindow);
    HlpSet(HLP_LAYOUT_EDIT);
    MSupdat(TRUE, 0, 0, VidDep - 1, VidWid - 1);
    for (j = 0; (WrdT)j < VidDep - 4; j++)
        Wprts(MsByt(j), 0, cAlt[TCDM_WINDOW], layoutScreen[j]);

    Vgets(pRow + 2, pCol + 41, (ChrP)underChar, 1);
    Drawing_Chars(charCtrl, pRow, pCol);
    Wactiv(cWindow);

    while (c != Key_Esc) {

        for (;;) {
            Wactiv(cWindow);
            if (kbhit()) {
                c = KeyGetc();
                break;
            }
            MSstat();
            if (MouLbtn == 0x0001) {
                c = Key_M_ClkL;
                if (MouLbtn == 0x0001) 
                    Wprtc(MsByt(pRow), MsByt(pCol), cAlt[TCDM_WINDOW], underChar[0]);
                while (MouLbtn == 0x0001) {
                    MSstat();
                    if (combatMode == TRUE) {
                        if (MouCol > 0 && MouCol < 39 && MouRow > 1 && MouRow < VidDep - 2) {
                            if (MouRow - 2 != (unsigned)pRow || MouCol - 1 != (unsigned)pCol) {
                                Wprtc(MsByt(pRow), MsByt(pCol), cAlt[TCDM_WINDOW], (ChrT)charCtrl);
                                pRow = MouRow - 2;
                                pCol = MouCol - 1;
                                Wprtc(MsByt(pRow), MsByt(pCol), cAlt[TCDM_BARINPUT], (ChrT)charCtrl);
                            }
                        }
                        if (MouCol == 1 && MouRow == VidDep - 2) {
                            charCtrl--;
                            Drawing_Chars(charCtrl, pRow, pCol);
                            c = Key_BS;
                        }
                        if (MouCol == 38 && MouRow == VidDep - 2) {
                            if (++charCtrl > 255) charCtrl = 255;
                            Drawing_Chars(charCtrl, pRow, pCol);
                            c = Key_BS;
                        }
                    }
                    else {
                        if (MouCol > 40 && MouCol < 79 && MouRow > 1 && MouRow < VidDep - 2) {
                            if (MouRow - 2 != (unsigned)pRow || MouCol - 41 != (unsigned)pCol) {
                                Wprtc(MsByt(pRow), MsByt(pCol), cAlt[TCDM_WINDOW], (ChrT)charCtrl);
                                pRow = MouRow - 2;
                                pCol = MouCol - 41;
                                Wprtc(MsByt(pRow), MsByt(pCol), cAlt[TCDM_BARINPUT], (ChrT)charCtrl);
                            }
                        }
                        if (MouCol == 41 && MouRow == VidDep - 2) {
                            charCtrl--;
                            Drawing_Chars(charCtrl, pRow, pCol);
                            c = Key_BS;
                        }
                        if (MouCol == 78 && MouRow == VidDep - 2) {
                            if (++charCtrl > 255) charCtrl = 255;
                            Drawing_Chars(charCtrl, pRow, pCol);
                            c = Key_BS;
                        }
                    }
                }
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
            if (combatMode == TRUE) {
                if (MouCol > 0 && MouCol < 39 && MouRow > 1 && MouRow < VidDep - 2)
                    c = Key_Ent;
                if (MouCol == 1 && MouRow == VidDep - 2)
                    c = Key_C_Lft;
                if (MouCol == 38 && MouRow == VidDep - 2)
                    c = Key_C_Rgt;
            }
            else {
                if (MouCol > 40 && MouCol < 79 && MouRow > 1 && MouRow < VidDep - 2)
                    c = Key_Ent;
                if (MouCol == 41 && MouRow == VidDep - 2)
                    c = Key_C_Lft;
                if (MouCol == 78 && MouRow == VidDep - 2)
                    c = Key_C_Rgt;
            }
        }

        if (c == Key_M_ClkR)
            c = Key_Esc;

        switch (c) {
            case Key_Ent :   /*  Enter  */
                underChar[0] = (int)charCtrl;
                break;

            case Key_Ins :   /*  Insert  */
                if (overWrite == FALSE) 
                    overWrite = TRUE;
                else 
                    overWrite = FALSE;
                break;

            case Key_Tab :   /*  Tab to color selection window  */
                VcurHid(1);
                exitCode = 1;
                while (exitCode != Key_Esc) {
                    switch (exitCode) {
                        case 1 : 
                        
                            exitCode++;
                            break;
                        case 2 :
                            exitCode++;
                            break;
                        case 3 :
                            exitCode = Key_Esc;
                            break;
                    }
                }
                VcurHid(0);
                break;

            case Key_A_C :   /*  Clear Screen  */
                strcpy(Message, "                                      ");
                for (j = 0; (WrdT)j < VidDep - 5; j++)
                    Wprts(MsByt(j), 0, cAlt[TCDM_WINDOW], Message);
                break;

            case Key_S_Rgt :   /*  6/RtArrow  */
            case Key_Rgt :
                if (overWrite == TRUE) underChar[0] = charCtrl;
                Wprtc(MsByt(pRow), MsByt(pCol++), cAlt[TCDM_WINDOW], underChar[0]);
                if (pCol > 37) pCol = 37;
                Vgets(pRow + 2, pCol + (combatMode == TRUE ? 1 : 41), (ChrP)underChar, 1);
                Wprtc(MsByt(pRow), MsByt(pCol), cAlt[TCDM_BARINPUT], (ChrT)charCtrl);
                break;

            case Key_S_Lft :   /*  4/LtArrow  */
            case Key_Lft :
                if (overWrite == TRUE) underChar[0] = charCtrl;
                Wprtc(MsByt(pRow), MsByt(pCol--), cAlt[TCDM_WINDOW], underChar[0]);
                if (pCol < 0) pCol = 0;
                Vgets(pRow + 2, pCol + (combatMode == TRUE ? 1 : 41), (ChrP)underChar, 1);
                Wprtc(MsByt(pRow), MsByt(pCol), cAlt[TCDM_BARINPUT], (ChrT)charCtrl);
                break;

            case Key_S_Dwn :   /*  2/DnArrow  */
            case Key_Dwn :
                if (overWrite == TRUE) underChar[0] = charCtrl;
                Wprtc(MsByt(pRow++), MsByt(pCol), cAlt[TCDM_WINDOW], underChar[0]);
                if ((unsigned)pRow > VidDep - 5) pRow = VidDep - 5;
                Vgets(pRow + 2, pCol + (combatMode == TRUE ? 1 : 41), (ChrP)underChar, 1);
                Wprtc(MsByt(pRow), MsByt(pCol), cAlt[TCDM_BARINPUT], (ChrT)charCtrl);
                break;

            case Key_S_Up :   /*  8/UpArrow  */
            case Key_Up :
                if (overWrite == TRUE) underChar[0] = charCtrl;
                Wprtc(MsByt(pRow--), MsByt(pCol), cAlt[TCDM_WINDOW], underChar[0]);
                if (pRow < 0) pRow = 0;
                Vgets(pRow + 2, pCol + (combatMode == TRUE ? 1 : 41), (ChrP)underChar, 1);
                Wprtc(MsByt(pRow), MsByt(pCol), cAlt[TCDM_BARINPUT], (ChrT)charCtrl);
                break;

            case Key_S_Home :   /*  7/Home */
            case Key_Home :
                if (overWrite == TRUE) underChar[0] = charCtrl;
                Wprtc(MsByt(pRow--), MsByt(pCol--), cAlt[TCDM_WINDOW], underChar[0]);
                if (pRow < 0) pRow = 0;
                if (pCol < 0) pCol = 0;
                Vgets(pRow + 2, pCol + (combatMode == TRUE ? 1 : 41), (ChrP)underChar, 1);
                Wprtc(MsByt(pRow), MsByt(pCol), cAlt[TCDM_BARINPUT], (ChrT)charCtrl);
                break;

            case Key_S_End :   /*  1/End  */
            case Key_End :
                if (overWrite == TRUE) underChar[0] = charCtrl;
                Wprtc(MsByt(pRow++), MsByt(pCol--), cAlt[TCDM_WINDOW], underChar[0]);
                if ((unsigned)pRow > VidDep - 5) pRow = VidDep - 5;
                if (pCol < 0) pCol = 0;
                Vgets(pRow + 2, pCol + (combatMode == TRUE ? 1 : 41), (ChrP)underChar, 1);
                Wprtc(MsByt(pRow), MsByt(pCol), cAlt[TCDM_BARINPUT], (ChrT)charCtrl);
                break;

            case Key_S_PgUp :   /*  9/PgUp  */
            case Key_PgUp : 
                if (overWrite == TRUE) underChar[0] = charCtrl;
                Wprtc(MsByt(pRow--), MsByt(pCol++), cAlt[TCDM_WINDOW], underChar[0]);
                if (pRow < 0) pRow = 0;
                if (pCol > 37) pCol = 37;
                Vgets(pRow + 2, pCol + (combatMode == TRUE ? 1 : 41), (ChrP)underChar, 1);
                Wprtc(MsByt(pRow), MsByt(pCol), cAlt[TCDM_BARINPUT], (ChrT)charCtrl);
                break;

            case Key_S_PgDn :   /*  3/PgDn  */
            case Key_PgDn : 
                if (overWrite == TRUE) underChar[0] = charCtrl;
                Wprtc(MsByt(pRow++), MsByt(pCol++), cAlt[TCDM_WINDOW], underChar[0]);
                if ((unsigned)pRow > VidDep - 5) pRow = VidDep - 5;
                if (pCol > 37) pCol = 37;
                Vgets(pRow + 2, pCol + (combatMode == TRUE ? 1 : 41), (ChrP)underChar, 1);
                Wprtc(MsByt(pRow), MsByt(pCol), cAlt[TCDM_BARINPUT], (ChrT)charCtrl);
                break;

            case Key_C_Home :    /* Ctrl Home */
                charCtrl = 0;   /* no break on purpose. Let CtrlLft fix it */

            case Key_C_Lft :   /* Ctrl Left Arrow */
                charCtrl--;
                Drawing_Chars(charCtrl, pRow, pCol);
                break;

            case Key_C_End :   /* Ctrl End */
                charCtrl = 255;   /* no break on purpose. Let CtrlRgt fix it */

            case Key_C_Rgt :   /* Ctrl Right Arrow */
                if (++charCtrl > 255) charCtrl = 255;
                Drawing_Chars(charCtrl, pRow, pCol);
                break;

            default : /* print any other characters on screen and advance */
                if (c != Key_BS) {
                    Wprtc(MsByt(pRow), MsByt(pCol++), cAlt[TCDM_WINDOW], (ChrT)c);
                    if (pCol > 37) {
                        pCol = 0;
                        pRow++;
                    }
                    if ((unsigned)pRow > VidDep - 5) {
                        pRow = VidDep - 5;
                        pCol = 37;
                    }
                    charCtrl = c;
                    Drawing_Chars(charCtrl, pRow, pCol);
                    Vgets(pRow + 2, pCol + (combatMode == TRUE ? 1 : 41), (ChrP)underChar, 1);
                    Wprtc(MsByt(pRow), MsByt(pCol), cAlt[TCDM_BARINPUT], (ChrT)charCtrl);
                }
                else {
                    if (--pCol < 0) {
                        pCol = 37;
                        pRow--;
                    }
                    if (pRow < 0) {
                        pRow = 0;
                        pCol = 0;
                    }
                    Wprtc(MsByt(pRow), MsByt(pCol), cAlt[TCDM_WINDOW], ' ');
                }
                break;
        }
    }
    Wprtc(MsByt(pRow), MsByt(pCol), cAlt[TCDM_WINDOW], underChar[0]);
    for (j = 1; j < 39; j++) 
        Wbprintc(BRD_BOT, MsByt(j), cAlt[TCDM_WINDOW], (ChrT)0xCD);
    MSupdat(FALSE, 0, 0, VidDep - 1, VidWid - 1);
    for (j = 0; (WrdT)j < VidDep - 4; j++) {
        Vgets(j + 2, combatMode == TRUE ? 1 : 41, Message, 38);
        Message[39] = '\0';
        strcpy(layoutScreen[j], Message);
    }
	 HlpSet(HLP_MAIN);
	 WVclose(SelWind);
}

VOID Drawing_Chars(IntT charCtrl, IntT pRow, IntT pCol)
{
	 IntT j;

	 Wactiv(cWindow);
    MSupdat(FALSE, 0, 0, VidDep - 1, VidWid - 1);
    Wbprintc(BRD_BOT, 1, cAlt[TCDM_BARINPUT], 0x11);    /* < arrow */
    for (j = charCtrl; j < (36 + charCtrl); j++) 
        Wbprintc(BRD_BOT, MsByt((j - charCtrl) + 2), cAlt[TCDM_WINDOW], (ChrT)j);
    Wbprintc(BRD_BOT, 2, cAlt[TCDM_BARINPUT], (ChrT)charCtrl);
    Wbprintc(BRD_BOT, 38, cAlt[TCDM_BARINPUT], 0x10);    /* > arrow */
    Wprtc(MsByt(pRow), MsByt(pCol), cAlt[TCDM_BARINPUT], (ChrT)charCtrl);
    Change_Matrix(charCtrl);
    MSupdat(TRUE, 0, 0, VidDep - 1, VidWid - 1);
}

VOID Selection_Box(NOARG)
{
    LCL ChrT SelChar = '*';
//    LCL AtrT SelCol  = LGREEN|_GREEN;
    
    SelWind = Wopen(5, 5, 19, 33, BOX_DBL, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW]);
        Fix_Shadow(SelWind);
        Wtitle(" Color Selection ", TTL_CNT, cAlt[TCDM_BARINPUT]);
        Wprts(0, 7, cAlt[TCDM_WINDOW], "LGREEN|_GREEN");
        Wprts(1, 23, cAlt[TCDM_WINDOW], "");
        Wprts(8, 23, cAlt[TCDM_WINDOW], "");
        Change_Matrix(SelChar);
        Wprts(9, 1, cAlt[TCDM_WINDOW], "Blink [û]");
        Wprts(11, 1, cAlt[TCDM_WINDOW], "Link Character [ ]");
        Wprts(12, 1, cAlt[TCDM_WINDOW], "Link Monster   [ ]");
}

VOID Change_Matrix(ChrT SelChar)
{
    IntT j, k;

    Wactiv(SelWind);
    for (j = 0; j < 16; j++)
        for (k = 0; k < 8; k++)
            if (j < 8)
                Wprtc(k + 1, j + 5, MsAtr(j)|MsAtr(k * 16)|_BLINK, SelChar);
            else
                Wprtc(k + 1, j + 6, MsAtr(j)|MsAtr(k * 16)|_BLINK, SelChar);
    for (j = 2; j < 8; j++)
        Wprts(j, 23, cAlt[TCDM_WINDOW], "²");
    Wprts(3, 23, cAlt[TCDM_WINDOW], "þ");
}

