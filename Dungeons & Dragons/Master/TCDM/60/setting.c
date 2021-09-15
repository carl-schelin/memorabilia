/* []---------------------------------------------------------------------[] */
/* |               Setting.cpp: Keep track of game setting.                | */
/* |                                                                       | */
/* |             The Setting.cpp source code and concepts are              | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __SETTING__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <TcxlEnt.H>
#include <TcxlMnu.H>
#include <TcxlVid.H>
#include <TcxlWin.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID Game_Setting(NOARG);
VOID CTYP Campaign(NOARG);
VOID CTYP Population(NOARG);

IntT terrain = 0;
WndT SetWind, CampWind;

GBL IntT gaming_Time;
GBL IntT population_Density;
GBL AtrT cCtrl[4];
GBL IntT lSetting[2];

VOID Game_Setting(NOARG)
{
    IntT j;

    SetWind = Wopen(lSetting[0], lSetting[1], lSetting[0] + 3, lSetting[1] + 19, BOX_DBL, cCtrl[TCDM_WINDOW], cCtrl[TCDM_WINDOW]);
        Fix_Shadow(SetWind);
        Wtitle(" Gaming Setting ", TTL_LFT, cCtrl[TCDM_WINDOW]);
        MnuAct(2);
            MnuItm(0, 1, "Campaign Setting", 'C', 1, ITM_AFT, Campaign, 0, HLP_SETTING);
            MnuItm(1, 1, "Dungeon Crawling", 'D', 2, ITM_AFT,     NULL, 0, HLP_SETTING);
        MnuEnd(1, MNU_HOR|MNU_OMN, 16, 0, cCtrl[TCDM_WINDOW], cCtrl[TCDM_QUICK], cCtrl[TCDM_DESELECT], cCtrl[TCDM_BARINPUT]);
        j = MnuGet();
        if (j != -1)
            gaming_Time = j;
    WVclose(SetWind);
}

VOID CTYP Campaign(NOARG)
{
    IntT j;

    Wshadoff();
    Wborder(BOX_SNG);
    CampWind = Wopen(lSetting[0] + 2, lSetting[1] + 4, lSetting[0] + 7, lSetting[1] + 28, BOX_DBL, cCtrl[TCDM_WINDOW], cCtrl[TCDM_WINDOW]);
        Fix_Shadow(CampWind);
        Wtitle(" Campaign Setting ", TTL_LFT, cCtrl[TCDM_WINDOW]);
        MnuAct(8);
            MnuItm(0,  1, "Plain",     'P', 1, ITM_AFT, Population, 0, HLP_SETTING);
            MnuItm(1,  1, "Scrub",     'S', 2, ITM_AFT, Population, 0, HLP_SETTING);
            MnuItm(2,  1, "Rough",     'R', 3, ITM_AFT, Population, 0, HLP_SETTING);
            MnuItm(3,  1, "Forest",    'F', 4, ITM_AFT, Population, 0, HLP_SETTING);
            MnuItm(0, 12, "Desert",    'D', 5, ITM_AFT, Population, 0, HLP_SETTING);
            MnuItm(1, 12, "Hills",     'H', 6, ITM_AFT, Population, 0, HLP_SETTING);
            MnuItm(2, 12, "Mountains", 'M', 7, ITM_AFT, Population, 0, HLP_SETTING);
            MnuItm(3, 12, "Marsh",     'a', 8, ITM_AFT, Population, 0, HLP_SETTING);
        MnuEnd(1, MNU_HOR|MNU_OMN, 9, 0, cCtrl[TCDM_WINDOW], cCtrl[TCDM_QUICK], cCtrl[TCDM_DESELECT], cCtrl[TCDM_BARINPUT]);
        j = MnuGet();
        if (j != -1)
            terrain = j;
    WVclose(CampWind);
}

VOID CTYP Population(NOARG)
{
    IntT j;
    WndT PopWind;

    Wshadoff();
    Wborder(BOX_SNG);
    PopWind = Wopen(lSetting[0] + 4, lSetting[1] + 8, lSetting[0] + 8, lSetting[1] + 39, BOX_DBL, cCtrl[TCDM_WINDOW], cCtrl[TCDM_WINDOW]);
        Fix_Shadow(PopWind);
        Wtitle(" Area Population ", TTL_LFT, cCtrl[TCDM_WINDOW]);
        MnuAct(3);
            MnuItm(0, 1, "Relatively Dense",             'R', 1, ITM_AFT, NULL, 0, HLP_SETTING);
            MnuItm(1, 1, "Moderate to Sparse/Patrolled", 'M', 2, ITM_AFT, NULL, 0, HLP_SETTING);
            MnuItm(2, 1, "Uninhabited/Wilderness",       'U', 3, ITM_AFT, NULL, 0, HLP_SETTING);
        MnuEnd(1, MNU_HOR|MNU_OMN, 28, 0, cCtrl[TCDM_WINDOW], cCtrl[TCDM_QUICK], cCtrl[TCDM_DESELECT], cCtrl[TCDM_BARINPUT]);
        j = MnuGet();
        if (j != -1) {
            if (j == 1) population_Density = 10;
            if (j == 2) population_Density = 12;
            if (j == 3) population_Density = 20;
        }
    WVclose(PopWind);
}

