/* []---------------------------------------------------------------------[] */
/* |                DateTime.cpp: Set game date and time.                  | */
/* |                                                                       | */
/* |            The DateTime.cpp source code and concepts are              | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __DATETIME__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <TcxlEnt.H>
#include <TcxlMnu.H>
#include <TcxlVid.H>
#include <TcxlWin.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID CTYP Set_Time(NOARG);
VOID CTYP Set_Date(NOARG);
IntT CTYP ModifyDateTime(ChrP temp);

GBL VOID Time_Keeping(IntT AddTime);

ChrT move_Var[5];

GBL IntT lMvrate[2];
GBL AtrT cCtrl[4];
GBL IntT months_In_Year;
GBL IntT NumberDays[16];
GBL IntT move_Rate;

VOID CTYP Set_Time(NOARG)
{
    WndT TimeWind;

    TimeWind = Wopen(lMvrate[0], lMvrate[1], lMvrate[0] + 2, lMvrate[1] + 32, BOX_DBL, cCtrl[TCDM_WINDOW], cCtrl[TCDM_WINDOW]);
        Fix_Shadow(TimeWind);
        Wtitle(" Game Time ", TTL_LFT, cCtrl[TCDM_WINDOW]);
        VcurHid(1);
        EntDef(cCtrl[TCDM_WINDOW], cCtrl[TCDM_WINDOW], 4);
            EntFld(0,  1, move_Var, "'What is the time? '%%':  :  .  '", FLD_DEC, 1, FLD_INI, ModifyDateTime, HLP_TIME);
            EntFld(0, 22, move_Var, "%%",                                FLD_DEC, 2, FLD_INI, ModifyDateTime, HLP_TIME);
            EntFld(0, 25, move_Var, "%%",                                FLD_DEC, 3, FLD_INI, ModifyDateTime, HLP_TIME);
            EntFld(0, 28, move_Var, "%%",                                FLD_DEC, 4, FLD_INI, ModifyDateTime, HLP_TIME);
        EntGet(1);
        VcurHid(0);
    WVclose(TimeWind);
    Time_Keeping(MAINTAIN);
    if (wStatus == 1)
        MessageWindow(" The sun rises and sets on your command, Master!");
}

VOID CTYP Set_Date(NOARG)
{
    WndT DateWind;

    DateWind = Wopen(lMvrate[0], lMvrate[1], lMvrate[0] + 2, lMvrate[1] + 31, BOX_DBL, cCtrl[TCDM_WINDOW], cCtrl[TCDM_WINDOW]);
        Fix_Shadow(DateWind);
        Wtitle(" Game Date ", TTL_LFT, cCtrl[TCDM_WINDOW]);
        VcurHid(1);
        EntDef(cCtrl[TCDM_WINDOW], cCtrl[TCDM_WINDOW], 3);
            EntFld(0,  1, move_Var, "'What is the date? '%%'-  -    '", FLD_DEC, 5, FLD_INI, ModifyDateTime, HLP_DATE);
            EntFld(0, 22, move_Var, "%%",                               FLD_DEC, 6, FLD_INI, ModifyDateTime, HLP_DATE);
            EntFld(0, 25, move_Var, "%%%%",                             FLD_DEC, 7, FLD_INI, ModifyDateTime, HLP_DATE);
        EntGet(5);
        VcurHid(0);
    WVclose(DateWind);
    Time_Keeping(MAINTAIN);
    if (wStatus == 1)
        MessageWindow(" The sun rises and sets on your command, Master!");
}

IntT CTYP ModifyDateTime(ChrP temp)
{
    IntT ReturnVal = 0;

    switch(EctlTag) {
        case 1 : TctlHou = atoi(temp);
                 if (TctlHou > 24) 
                     ReturnVal = 1;
                 break;
        case 2 : TctlMin = atoi(temp);
                 if (TctlMin > 60)
                     ReturnVal = 1;
                 break;
        case 3 : TctlMel = atoi(temp);
                 if (TctlMel >= move_Rate)
                     ReturnVal = 1;
                 break;
        case 4 : TctlRnd = atoi(temp);
                 if (TctlRnd > 10)
                     ReturnVal = 1;
                 break;

                 /* Date Settings */

        case 5 : TctlMon = atoi(temp); /* month is used from 1 to number */
                 if (TctlMon > months_In_Year) /* checks are done from 0 to number -1 */
                     ReturnVal = 1;
                 break;
        case 6 : TctlDay = atoi(temp);
                 if (TctlDay > NumberDays[TctlMon-1]) 
                     ReturnVal = 1;
                 break;
        case 7 : TctlYer = atoi(temp);
                 break;
    }
    move_Var[0] = '\0';
    return ReturnVal;
}

