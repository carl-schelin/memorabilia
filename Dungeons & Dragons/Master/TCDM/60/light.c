/* []---------------------------------------------------------------------[] */
/* |       Light.cpp: Keep track of each character's light source.         | */
/* |                                                                       | */
/* |              The Light.cpp source code and concepts are               | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __LIGHT__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <TcxlInp.H>
#include <TcxlMnu.H>
#include <TcxlSel.H>
#include <TcxlVid.H>
#include <TcxlWin.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID Activate_Light(NOARG);
VOID CTYP Adjust_Light_Time(NOARG);

GBL VOID Update_Data(IntT whichOne);

GBL IntT lLight[2];
GBL AtrT cAlt[4];
GBL WndT cWindow;

WndT LitWind;
IntT light_Times[6] = { 60, 90, 120, 150, 240, 0};
ChrP light_Types[] = {"Torch", "Tallow Candle", "Wax Candle", "Impure Oil", 
    "Pure Oil", "No Light", NULL};

VOID Activate_Light(NOARG)
{
    IntT j;

    LitWind = Wopen(lLight[0], lLight[1], lLight[0] + 7, lLight[1] + 25, 1, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW]);
        Fix_Shadow(LitWind);
        Wtitle(" Light Activation ", TTL_LFT, cAlt[TCDM_WINDOW]);
        for (j = 0; j < 6; j++) {
            if (LitTyp(CHARNUM) == j)
                Wprts((BytT)j,  4, cAlt[TCDM_WINDOW], light_Types[j]);
            else
                Wprts((BytT)j,  4, cAlt[TCDM_DESELECT], light_Types[j]);
            Wprtf((BytT)j, 18, cAlt[TCDM_WINDOW], "[%3d]", light_Times[j]);
        }
        MnuAct(6);
            MnuItm(0, 1, "1.", '1', 1, 0, Adjust_Light_Time, 0, HLP_LIGHT);
            MnuItm(1, 1, "2.", '2', 2, 0, Adjust_Light_Time, 0, HLP_LIGHT);
            MnuItm(2, 1, "3.", '3', 3, 0, Adjust_Light_Time, 0, HLP_LIGHT);
            MnuItm(3, 1, "4.", '4', 4, 0, Adjust_Light_Time, 0, HLP_LIGHT);
            MnuItm(4, 1, "5.", '5', 5, 0, Adjust_Light_Time, 0, HLP_LIGHT);
            MnuItm(5, 1, "6.", '6', 6, 0, Adjust_Light_Time, 0, HLP_LIGHT);
        MnuEnd(1, MNU_HOR|MNU_OMN, 2, 0, cAlt[TCDM_WINDOW], cAlt[TCDM_QUICK], cAlt[TCDM_DESELECT], cAlt[TCDM_BARINPUT]);
        MnuGet();
    WVclose(LitWind);
}

VOID CTYP Adjust_Light_Time(NOARG)
{
    ChrT Temp[47];
    IntT k;
	 WndT LModWind;
	 ChrP YesNo[] = {"Yes", "No", NULL};

    k = MctlTag - 1;
    if (k == LitTyp(CHARNUM) && k != 5) {
        Wshadoff();
        Wborder(BOX_SNG);
        LModWind = Wopen(lLight[0] + 2, lLight[1] + 4, lLight[0] + 6, lLight[1] + 52, 1, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW]);
            Fix_Shadow(LModWind);
            Wtitle(" Adjust Time ", TTL_LFT, cAlt[TCDM_WINDOW]);
            sprintf(Temp, "You have %d turns left in your %s.",
                LitLft(CHARNUM), light_Types[LitTyp(CHARNUM)]);
            Wprts(0, 1, cAlt[TCDM_WINDOW], Temp);
            Wprts(1, 1, cAlt[TCDM_WINDOW], "Modify Light?");
            k = SelTxt(1, 15, cAlt[TCDM_BARINPUT], YesNo, 0);
            if (k != ERR_ARG) 
                if (k == 0) {
                    VcurHid(1);
                    Wgotoxy(2, 1);
                    k = KwGetFmt(Temp, "'By how much? '9999");
                    if (k != -1) 
                        LitLft(CHARNUM) += atoi(Temp);
                    VcurHid(0);
                }
        WVclose(LModWind);
        Wborder(BOX_DBL);
        Fix_Shadow(LitWind);
    }
    else {
        Wprts((BytT)LitTyp(CHARNUM), 4, cAlt[TCDM_DESELECT], light_Types[LitTyp(CHARNUM)]);
        LitTyp(CHARNUM) = k;
        LitLft(CHARNUM) = light_Times[k];
        Wprts((BytT)LitTyp(CHARNUM), 4, cAlt[TCDM_WINDOW], light_Types[LitTyp(CHARNUM)]);
    }
    if (wStatus == 1)
        if (LitTyp(CHARNUM) == 5) 
            MessageWindow(" And there was great darkness upon the land.");
        else
            MessageWindow(" Let there be LIGHT!");
    Wactiv(cWindow);
    Update_Data(LIGHT);
}

