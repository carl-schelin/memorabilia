/* []---------------------------------------------------------------------[] */
/* |                 CSave.cpp: Character Save Routines.                   | */
/* |                                                                       | */
/* |              The CSave.cpp source code and concepts are               | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __CHARSAVE__

#include <stdio.h>
#include <string.h>
#include <TcxlDef.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID SaveCharacter(IntT SaveWho);

#define CHARFILELEN 296

VOID SaveCharacter(IntT SaveWho)
{
    FILE *charout;
    ChrT string[CHARFILELEN];

    strcpy(Message, savePDir);
    strcat(Message, "\\");
    strcat(Message, ChrFil(SaveWho));
    strcat(Message, ".CHA");
    if ((charout = fopen(Message, "w")) != NULL) {
        sprintf(string, "%2d %-25s %-25s %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %3d %3d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %3d %3d %2d %2d %2d %2d %2d %2d %2d %2d %3d %2d %2d %2d %2d %2d %2d %2d %2d %4d %c %2d %3d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d", 
            ChrSta(SaveWho), 
            ChrPer(SaveWho), 
            ChrChr(SaveWho), 
            ClsRch(SaveWho, 0),
            ClsRch(SaveWho, 1),
            ClsRch(SaveWho, 2),
            ClsLvl(SaveWho, 0),
            ClsLvl(SaveWho, 1),
            ClsLvl(SaveWho, 2),
            ClsCls(SaveWho, 0),
            ClsCls(SaveWho, 1),
            ClsCls(SaveWho, 2),
            ClsKit(SaveWho, 0),
            ClsKit(SaveWho, 1),
            ClsKit(SaveWho, 2),
            ChrRac(SaveWho), 
            ChrAli(SaveWho), 
            cData[SaveWho].AType, 
            cData[SaveWho].APoints, 
            cData[SaveWho].APtDown,
            cData[SaveWho].AMagical,
            cData[SaveWho].SType, 
            cData[SaveWho].SPoints, 
            cData[SaveWho].SPtDown,
            cData[SaveWho].SMagical,
            cData[SaveWho].HType, 
            cData[SaveWho].HPoints, 
            cData[SaveWho].HPtDown,
            cData[SaveWho].HMagical,
            cData[SaveWho].ACAdj, 
            StaStr(SaveWho), 
            StaStp(SaveWho), 
            StaDex(SaveWho), 
            StaDep(SaveWho), 
            StaCon(SaveWho), 
            StaCop(SaveWho), 
            StaInt(SaveWho), 
            StaInp(SaveWho), 
            StaWis(SaveWho), 
            StaWip(SaveWho), 
            StaCha(SaveWho), 
            StaChp(SaveWho), 
            cData[SaveWho].Psionic, 
            ChrHpt(SaveWho), 
            ChrHpd(SaveWho), 
            ChrPoi(SaveWho), 
            ChrPet(SaveWho), 
            ChrPar(SaveWho), 
            ChrBth(SaveWho), 
            ChrRsw(SaveWho), 
            ChrSpl(SaveWho), 
            LitTyp(SaveWho), 
            LitLft(SaveWho), 
            cData[SaveWho].Experience,
            ThfPip(SaveWho),
            ThfOlk(SaveWho),
            ThfFrt(SaveWho),
            ThfMsi(SaveWho),
            ThfHis(SaveWho),
            ThfHno(SaveWho),
            ThfCwa(SaveWho),
            ThfRla(SaveWho),
            DscAge(SaveWho),
            DscSex(SaveWho),
            DscHgt(SaveWho),
            DscWgt(SaveWho),
            DscEye(SaveWho),
            DscSkn(SaveWho),
            DscHrc(SaveWho),
            DscHrl(SaveWho),
            DscBdc(SaveWho),
            DscBdl(SaveWho),
            DscGa0(SaveWho),
            DscGa1(SaveWho),
            DscGa2(SaveWho),
            DscGa3(SaveWho),
            DscGa4(SaveWho),
            DscGa5(SaveWho),
            DscGa6(SaveWho),
            DscGa7(SaveWho),
            DscHnd(SaveWho)
        );
        fputs(string, charout);
        fputs("\n-2 xxxxxxxxxxxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxx 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 999 999 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 999 999 99 99 99 99 99 99 99 99 999 99 99 99 99 99 99 99 99 9999 C 99 999 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99\n", charout);
        fputs("-2 Player Name               Character Name            Gr Gr Gr Lv Lv Lv Cl Cl Cl Kt Kt Kt Rc Al At Apt Apd Am St Sp Sd Sm Ht Hp Hd Hm Mm St S% Dx D% Cn C% In I% Ws W% Ch C% PS Hpt HpD Ps PD PP RS Br Sp Lt LL Exp T1 T2 T3 T4 T5 T6 T7 T8  Age S Ht Wgt Ec Sc Hc Hl Bc Bl F1 F2 F3 F4 F5 F6 F7 F8 Hn\n", charout);
        fclose(charout);
        cData[SaveWho].Changed = FALSE;
        sprintf(Message, " Saved %s", ChrPer(SaveWho));
        MessageWindow(Message);
    }
    else
        MessageWindow2(" ERROR: Unable to open:\n", Message);
}

