/* []---------------------------------------------------------------------[] */
/* |                Random.cpp: Random Die Rolling Routines.               | */
/* |                                                                       | */
/* |              The Random.cpp source code and concepts are              | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __RANDOM__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TcxlInP.H>
#include <TcxlWin.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

IntT Roll_Dice(IntT sides, IntT times);
IntT Roll_100(NOARG);

GBL IntT self_Roll;
GBL IntT lStdq[2];
GBL AtrT cTcdm[4];

IntT Roll_Dice(IntT sides, IntT times)
{
    IntT j, result = 0;
    ChrT left[3], temp[30];
    WndT RandWind;

    for (j = 0; j < times; j++)
        if (sides == 100) 
            result += Roll_100();
        else
            result += random(sides) + 1;
    if ((self_Roll == 1) && (sides < 100)) {
        RandWind = Wopen(lStdq[0], lStdq[1], lStdq[0] + 3, lStdq[1] + 50, BOX_DBL, cTcdm[TCDM_WINDOW], cTcdm[TCDM_WINDOW]);
            Fix_Shadow(RandWind);
            sprintf(temp, "Roll a %d sider, %d time%s...", sides, times, times < 2 ? " " : "s ");
            Wprts(0, 1, cTcdm[TCDM_WINDOW], temp);
            Wgotoxy(1, 1);
            if (KwGetFmt(left, "'Result of the die roll (ESC to pass): '%%%") != W_ESCPRESS)
                result = atoi(left);
        WVclose(RandWind);
    }
    return result;
}

IntT Roll_100(NOARG)
{
    IntT result;
    ChrT left[3], temp[30];

    itoa(Roll_Dice(10, 1) - 1, temp, 10);
    strcpy(left, temp);
    itoa(Roll_Dice(10, 1) - 1, temp, 10);
    strcat(left, temp);
    result = atoi(left);
    if (result == 0) result = 100;
    return result;
}

