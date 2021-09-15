/* []---------------------------------------------------------------------[] */
/* |     ChkMouse.cpp: If mouse clicked, converts it to right Keycode.     | */
/* |                                                                       | */
/* |            The ChkMouse.cpp source code and concepts are              | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __CHKMOUSE__

#include <conio.h>
#include <TcxlCod.H>
#include <TcxlMou.H>
#include <TcxlVid.H>
#include <TcxlInp.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

GBL VOID PrintKeyList(NOARG);
GBL VOID Print_Char(AtrT DrawMode, IntT Whom);
GBL VOID CTYP GetHelp(NOARG);
GBL VOID CTYP IncrementTime(NOARG);
GBL VOID CTYP MoveRight(NOARG);
GBL VOID CTYP MoveLeft(NOARG);
GBL VOID CTYP SubtractHitPoints(NOARG);
GBL VOID CTYP SubtractArmorPoints(NOARG);
GBL VOID CTYP SubtractShieldPoints(NOARG);
GBL VOID CTYP SubtractHelmetPoints(NOARG);
GBL VOID CTYP AddArmorPoints(NOARG);
GBL VOID CTYP AddShieldPoints(NOARG);
GBL VOID CTYP AddHelmetPoints(NOARG);
GBL VOID CTYP Set_Time(NOARG);
GBL VOID CTYP Set_Date(NOARG);

KeyT ChkMouse(KeyT c);
VOID CTYP retSlash(NOARG);

GBL IntT keyMode, keyStatus;
GBL AtrT cMain[4];

KeyT CheckMouse(KeyT c)
{
    if (c == Key_M_ClkL) {
        if (MouRow == 0) {
            if (MouCol < 13) /* moucol is unsigned so it can never be less than 0 */
                c = Key_F1;
            if (MouCol > 36 && MouCol < 41)
                c = Key_C_D;
            if (MouCol > 58 && MouCol < 63)
                c = Key_C_T;
            if (MouCol > 63 && MouCol < 76)
                c = Key_Ent;
        }
        if (MouRow == (VidDep - 1)) {
            if (MouCol > 21 && MouCol < 30) {
                if (++keyMode > 2)
						  keyMode = 0;
                PrintKeyList();
            }
            if (MouCol > 61 && MouCol < 68) {
                if (++keyStatus > 3)
                    keyStatus = 0;
                PrintKeyList();
            }
            if (keyMode == 0) {         /*  Normal Mode? */
                if (keyStatus == 0) {                  /* lower case character */
                    switch (MouCol) {
                        case 35 : c = Key_C; break;    /* Clear Screen */
                        case 36 : c = Key_D; break;    /* Load Dos */
                        case 38 : c = Key_F; break;    /* Fawning Mode */
                        case 40 : c = Key_H; break;    /* Test */
                        case 44 : c = Key_L; break;    /* Load Chars/Monsters */
                        case 49 : c = Key_Q; break;    /* Quit TCDM */
                        case 51 : c = Key_S; break;    /* Save Chars/Monsters */
                    }
                }
                if (keyStatus == 1) {                  /* upper case character */
                    switch (MouCol) {
                        case 44 : c = Key_S_L; break;  /* Load Layout File */
                        case 51 : c = Key_S_S; break;  /* Save Layout File */
                    }
                }
                if (keyStatus == 2) {                  /* ctrl character */
                    switch (MouCol) {
                        case 35 : c = Key_C_C; break;  /* Toggle Char */
                        case 36 : c = Key_C_D; break;  /* Game Date */
                        case 44 : c = Key_C_L; break;  /* Toggle Layout */
                        case 45 : c = Key_C_M; break;  /* Toggle Monster */
                        case 51 : c = Key_C_S; break;  /* Game Setting */
                        case 52 : c = Key_C_T; break;  /* Game Time */
                    }
                }
                if (keyStatus == 3) {                  /* alt character */
                    switch (MouCol) {
                        case 35 : c = Key_A_C; break;  /* Clear Experience */
                        case 36 : c = Key_A_D; break;  /* Kill all chars */
                        case 37 : c = Key_A_E; break;  /* Edit Chars */
                        case 41 : c = Key_A_I; break;  /* Restore Chars */
                        case 44 : c = Key_A_L; break;  /* Edit Light */
                        case 48 : c = Key_A_P; break;  /* Edit Psionics */
                        case 50 : c = Key_A_R; break;  /* Racial Information */
                        case 51 : c = Key_A_S; break;  /* Edit Saving Throws */
                        case 52 : c = Key_A_T; break;  /* Display Thief Info */
                        case 54 : c = Key_A_V; break;  /* Wipe Characters */
                    }
                }
            }
            if (keyMode == 1) {         /*  Number Mode  */
                if (keyStatus == 3) {                  /* alt number */
                    switch (MouCol) {
                        case 35 :
                        case 36 : c = Key_A_1; break;  /* Random 2 */
                        case 37 :
                        case 38 : c = Key_A_2; break;  /* Random 3 */
                        case 39 :
                        case 40 : c = Key_A_3; break;  /* Random 4 */
                        case 41 :
                        case 42 : c = Key_A_4; break;  /* Random 6 */
                        case 43 :
                        case 44 : c = Key_A_5; break;  /* Random 8 */
                        case 45 :
                        case 46 : c = Key_A_6; break;  /* Random 10 */
                        case 47 :
                        case 48 : c = Key_A_7; break;  /* Random 12 */
                        case 49 :
                        case 50 : c = Key_A_8; break;  /* Random 20 */
                        case 51 :
                        case 52 : c = Key_A_9; break;  /* Random 100 */
                    }
                }
            }
            if (keyMode == 2) {         /* Function Mode */
                if (keyStatus == 0) {                  /* F1 - F10 */
                    switch (MouCol) {
                        case 35 :
                        case 36 : c = Key_F1; break;   /* F1 */
                        case 37 :
                        case 38 : c = Key_F2; break;   /* F2 */
                        case 39 :
                        case 40 : c = Key_F3; break;   /* F3 */
                        case 41 :
                        case 42 : c = Key_F4; break;   /* F4 */
                        case 43 :
                        case 44 : c = Key_F5; break;   /* F5 */
                        case 45 :
                        case 46 : c = Key_F6; break;   /* F6 */
                        case 47 :
                        case 48 : c = Key_F7; break;   /* F7 */
                        case 49 :
                        case 50 : c = Key_F8; break;   /* F8 */
                        case 51 :
                        case 52 : c = Key_F9; break;   /* F9 */
                        case 53 :
                        case 54 :
                        case 55 : c = Key_F10; break;  /* F10 */
                    }
                }
                if (keyStatus == 1) {             /* Shift F1 - F10 */
                    switch (MouCol) {
                        case 35 :
                        case 36 : c = Key_S_F1; break;   /* F11 */
                        case 37 :
                        case 38 : c = Key_S_F2; break;   /* F12 */
                        case 39 :
                        case 40 : c = Key_S_F3; break;   /* F13 */
                        case 41 :
                        case 42 : c = Key_S_F4; break;   /* F14 */
                        case 43 :
                        case 44 : c = Key_S_F5; break;   /* F15 */
                        case 45 :
                        case 46 : c = Key_S_F6; break;   /* F16 */
                        case 47 :
                        case 48 : c = Key_S_F7; break;   /* F17 */
                        case 49 :
                        case 50 : c = Key_S_F8; break;   /* F18 */
                        case 51 :
                        case 52 : c = Key_S_F9; break;   /* F19 */
                        case 53 :
                        case 54 :
                        case 55 : c = Key_S_F10; break;  /* F20 */
                    }
                }
                if (keyStatus == 2) {             /* Ctrl F1 - F10 */
                    switch (MouCol) {
                        case 35 :
                        case 36 : c = Key_C_F1; break;   /* F21 */
                        case 37 :
                        case 38 : c = Key_C_F2; break;   /* F22 */
                        case 39 :
                        case 40 : c = Key_C_F3; break;   /* F23 */
                        case 41 :
                        case 42 : c = Key_C_F4; break;   /* F24 */
                        case 43 :
                        case 44 : c = Key_C_F5; break;   /* F25 */
                        case 45 :
                        case 46 : c = Key_C_F6; break;   /* F26 */
                        case 47 :
                        case 48 : c = Key_C_F7; break;   /* F27 */
                        case 49 :
                        case 50 : c = Key_C_F8; break;   /* F28 */
                        case 51 :
                        case 52 : c = Key_C_F9; break;   /* F29 */
                        case 53 :
                        case 54 :
                        case 55 : c = Key_C_F10; break;  /* F30 */
                    }
                }
                if (keyStatus == 3) {             /* Alt F1 - F10 */
                    switch (MouCol) {
                        case 35 :
                        case 36 : c = Key_A_F1; break;   /* F31 */
                        case 37 :
                        case 38 : c = Key_A_F2; break;   /* F32 */
                        case 39 :
                        case 40 : c = Key_A_F3; break;   /* F33 */
                        case 41 :
                        case 42 : c = Key_A_F4; break;   /* F34 */
                        case 43 :
                        case 44 : c = Key_A_F5; break;   /* F35 */
                        case 45 :
                        case 46 : c = Key_A_F6; break;   /* F36 */
                        case 47 :
                        case 48 : c = Key_A_F7; break;   /* F37 */
                        case 49 :
                        case 50 : c = Key_A_F8; break;   /* F38 */
                        case 51 :
                        case 52 : c = Key_A_F9; break;   /* F39 */
                        case 53 :
                        case 54 :
                        case 55 : c = Key_A_F10; break;  /* F40 */
                    }
                }
            }
        }
        if (combatMode == TRUE) {
            if (combatStatus == MONSTER) {
                if (MouCol == 39 && (MouRow > 0 && MouRow < VidDep - 1))
                    c = Key_Rgt;
                if (MouCol == 0 && (MouRow > 0 && MouRow < VidDep - 1))
                    c = Key_Lft;
                if (MouCol > 0 && MouCol < 39 && MouRow == 9)
                    c = Key_PlsG;
                if (MouCol > 61 && MouCol <= 79 && MouRow > 1 && MouRow < (VidDep - 1)) {
                    Print_Char(NORMAL, MONNUM);
                    NewSheet = 1;
                    charNum = MouRow - 2;
                    c = Key_Rgt;
                }
                if (MouCol > 40 && MouCol < 59 && MouRow > 1 && MouRow < (VidDep - 1)) {
                    if ((MouRow - 2) > (unsigned)monNum) {
                        Print_Char(NORMAL, MONNUM);
                        if (mData[MONNUM].Status != mData[MouRow - 3].Status)
                            NewSheet = 1;
                        monNum = MouRow - 3;
                        c = Key_Dwn;
                    }
                    if ((MouRow - 2) < (unsigned)monNum) {
                        Print_Char(NORMAL, MONNUM);
                        if (mData[MONNUM].Status != mData[MouRow - 1].Status)
                            NewSheet = 1;
                        monNum = MouRow - 1;
                        c = Key_Up;
                    }
                }
            }
            else {
                if (MouCol == 39 && (MouRow > 0 && MouRow < VidDep - 1))
                    c = Key_Rgt;
                if (MouCol == 0 && (MouRow > 0 && MouRow < VidDep - 1))
                    c = Key_Lft;
                if (MouCol > 0 && MouCol < 39) {
                    if (MouRow == 4) c = Key_PlsG;
                    if (MouRow == 13) c = Key_Equ;
                    if (MouRow == 14) c = Key_S_Equ;
                    if (MouRow == 15) c = Key_A_Equ;
                }
                if (MouCol > 40 && MouCol < 59 && MouRow > 1 && MouRow < (VidDep - 1)) {
                    Print_Char(NORMAL, CHARNUM);
                    monNum = MouRow - 2;
                    NewSheet = 1;
                    c = Key_Lft;
                }
                if (MouCol > 61 && MouCol <= 79 && MouRow > 1 && MouRow < (VidDep - 1)) {
                    if ((MouRow - 2) > (unsigned)charNum) {
                        Print_Char(NORMAL, CHARNUM);
                        if (ChrSta(CHARNUM) != ChrSta(MouRow - 3))
                            NewSheet = 1;
                        charNum = MouRow - 3;
                        c = Key_Dwn;
                    }
                    if ((MouRow - 2) < (unsigned)charNum) {
                        Print_Char(NORMAL, CHARNUM);
                        if (ChrSta(CHARNUM) != ChrSta(MouRow - 1))
                            NewSheet = 1;
                        charNum = MouRow - 1;
                        c = Key_Up;
                    }
                }
            }
        }
        else {
            if (MouCol < 39 && MouRow != 0) {
                if ((MouRow - 2) > (unsigned)charNum) {
                    Print_Char(NORMAL, CHARNUM);
                    if (ChrSta(CHARNUM) != ChrSta(MouRow - 3))
                        NewSheet = 1;
                    charNum = MouRow - 3;
                    c = Key_Dwn;
                }
                if ((MouRow - 2) < (unsigned)charNum) {
                    Print_Char(NORMAL, CHARNUM);
                    if (ChrSta(CHARNUM) != ChrSta(MouRow - 1))
                        NewSheet = 1;
                    charNum = MouRow - 1;
                    c = Key_Up;
                }
            }
            if (MouCol == 40 && (MouRow < (VidDep - 1) && MouRow > 0))
                c = Key_Lft;
            if (MouCol == 79 && (MouRow < (VidDep - 1) && MouRow > 0))
                c = Key_Rgt;
            if (MouCol > 40 && MouCol < 79) {
                if (MouRow ==  4) c = Key_PlsG;
                if (MouRow == 13) c = Key_Equ;
                if (MouRow == 14) c = Key_S_Equ;
                if (MouRow == 15) c = Key_A_Equ;
            }
        }
    }

    if (c == Key_M_ClkR) {
        c = Key_Esc;
        if (combatMode == TRUE) {
            if (combatStatus == MONSTER) {
                if (MouRow == 9)
                    if (MouCol > 0 && MouCol < 39)
                        c = Key_MinG;
            }
            else {
                if (MouCol > 0 && MouCol < 39) {
                    if (MouRow ==  4) c = Key_MinG;
                    if (MouRow == 13) c = Key_Min;
                    if (MouRow == 14) c = Key_S_Min;
                    if (MouRow == 15) c = Key_A_Min;
                }
            }
        }
        else {
            if (MouCol > 40 && MouCol < 79) {
                if (MouRow ==  4) c = Key_MinG;
                if (MouRow == 13) c = Key_Min;
                if (MouRow == 14) c = Key_S_Min;
                if (MouRow == 15) c = Key_A_Min;
            }
        }
    }
    return c;
}

