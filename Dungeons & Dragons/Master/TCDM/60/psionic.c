/* []---------------------------------------------------------------------[] */
/* |                  PSIonic.cpp: PSIonic ability code                    | */
/* |                                                                       | */
/* |             The PSIonic.cpp source code and concepts are              | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __PSIONIC__

#include <stdio.h>
#include <TcxlMnu.H>
#include <TcxlWin.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID Psionic_Data(NOARG);

GBL IntT lPsi[2];
GBL AtrT cAlt[4];

VOID Psionic_Data(NOARG)
{
    WndT PSIWind;

    PSIWind = Wopen(lPsi[0], lPsi[1], lPsi[0] + 5, lPsi[1] + 20, 1, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW]);
        Fix_Shadow(PSIWind);
        Wtitle(" Psionics ", TTL_LFT, cAlt[TCDM_WINDOW]);
        MnuAct(1);
            MnuItm(0, 1, "Psionics", 'P', 0, 0, NULL, 0, HLP_PSIONIC);
        MnuEnd(0, MNU_VER, 10, 1, cAlt[TCDM_WINDOW], cAlt[TCDM_QUICK], cAlt[TCDM_DESELECT], cAlt[TCDM_BARINPUT]);
        MnuGet();
    WVclose(PSIWind);
}

