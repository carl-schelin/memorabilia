/* []---------------------------------------------------------------------[] */
/* |   Swap.cpp: Monster/Character Swapping and Initialization Routines.   | */
/* |                                                                       | */
/* |             The Swap.cpp source code and concepts are                 | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __SWAP__

#include <stdio.h>
#include <string.h>
#include <TcxlDef.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID Init_Char(IntT which);
VOID Init_Mons(IntT which);

GBL WndT cWindow;

VOID Resurrect_Character(IntT From, IntT ToWhom)
{
    IntT j;
    
    for (j = 0; j < 6; j++) {
        if (j < 6)
            cData[ToWhom].SThrows[j] = cData[From].SThrows[j];
        if (j < 3) {
            ClsRch(ToWhom, j) = ClsRch(From, j);
            ClsLvl(ToWhom, j) = ClsLvl(From, j);
            ClsCls(ToWhom, j) = ClsCls(From, j);
            ClsKit(ToWhom, j) = ClsKit(From, j);
        }
    }
    ChrWnd(ToWhom)        = ChrWnd(From);
    ChrSta(ToWhom)        = ChrSta(From);
    cData[ToWhom].Changed = cData[From].Changed;
    strcpy(ChrFil(ToWhom),  ChrFil(From));
    strcpy(ChrPer(ToWhom),  ChrPer(From));
    strcpy(ChrChr(ToWhom),  ChrChr(From));
    ChrRac(ToWhom)        = ChrRac(From);
    ChrAli(ToWhom)        = ChrAli(From);

    cData[ToWhom].AClass    = cData[From].AClass;
    cData[ToWhom].AType     = cData[From].AType;
    cData[ToWhom].APoints   = cData[From].APoints;
    cData[ToWhom].APtDown   = cData[From].APtDown;
    cData[ToWhom].AMagical  = cData[From].AMagical;
    cData[ToWhom].SType     = cData[From].SType;
    cData[ToWhom].SPoints   = cData[From].SPoints;
    cData[ToWhom].SPtDown   = cData[From].SPtDown;
    cData[ToWhom].SMagical  = cData[From].SMagical;
    cData[ToWhom].HType     = cData[From].HType;
    cData[ToWhom].HPoints   = cData[From].HPoints;
    cData[ToWhom].HPtDown   = cData[From].HPtDown;
    cData[ToWhom].HMagical  = cData[From].HMagical;
    cData[ToWhom].ACAdj     = cData[From].ACAdj;
    cData[ToWhom].THAC0     = cData[From].THAC0;

    cData[ToWhom].Psionic     = cData[From].Psionic;
    ChrHpt(ToWhom)            = ChrHpt(From);
    ChrHpd(ToWhom)            = ChrHpd(From);
    LitTyp(ToWhom)            = LitTyp(From);
    LitLft(ToWhom)            = LitLft(From);
    strcpy(cData[ToWhom].NormalMode, cData[From].NormalMode);
    strcpy(cData[ToWhom].CombatMode, cData[From].CombatMode);
    cData[ToWhom].AttackWho   = cData[From].AttackWho;
    cData[ToWhom].DisplayMode = cData[From].DisplayMode;
    cData[ToWhom].Experience  = cData[From].Experience;
    DscAge(ToWhom)        = DscAge(From);
    DscSex(ToWhom)        = DscSex(From);
    DscHgt(ToWhom)        = DscHgt(From);
    DscWgt(ToWhom)        = DscWgt(From);
    DscEye(ToWhom)        = DscEye(From);
    DscSkn(ToWhom)        = DscSkn(From);
    DscHrc(ToWhom)        = DscHrc(From);
    DscHrl(ToWhom)        = DscHrl(From);
    DscBdc(ToWhom)        = DscBdc(From);
    DscBdl(ToWhom)        = DscBdl(From);
    DscHnd(ToWhom)        = DscHnd(From);
    DscGa0(ToWhom)        = DscGa0(From);
    DscGa1(ToWhom)        = DscGa1(From);
    DscGa2(ToWhom)        = DscGa2(From);
    DscGa3(ToWhom)        = DscGa3(From);
    DscGa4(ToWhom)        = DscGa4(From);
    DscGa5(ToWhom)        = DscGa5(From);
    DscGa6(ToWhom)        = DscGa6(From);
    DscGa7(ToWhom)        = DscGa7(From);
    StaStr(ToWhom)        = StaStr(From);
    StaStp(ToWhom)        = StaStp(From);
    StaDex(ToWhom)        = StaDex(From);
    StaDep(ToWhom)        = StaDep(From);
    StaCon(ToWhom)        = StaCon(From);
    StaCop(ToWhom)        = StaCop(From);
    StaInt(ToWhom)        = StaInt(From);
    StaInp(ToWhom)        = StaInp(From);
    StaWis(ToWhom)        = StaWis(From);
    StaWip(ToWhom)        = StaWip(From);
    StaCha(ToWhom)        = StaCha(From);
    StaChp(ToWhom)        = StaChp(From);
    ThfPip(ToWhom)        = ThfPip(From);
    ThfOlk(ToWhom)        = ThfOlk(From);
    ThfFrt(ToWhom)        = ThfFrt(From);
    ThfMsi(ToWhom)        = ThfMsi(From);
    ThfHis(ToWhom)        = ThfHis(From);
    ThfHno(ToWhom)        = ThfHno(From);
    ThfCwa(ToWhom)        = ThfCwa(From);
    ThfRla(ToWhom)        = ThfRla(From);
    ChrPoi(ToWhom)        = ChrPoi(From);
    ChrPet(ToWhom)        = ChrPet(From);
    ChrPar(ToWhom)        = ChrPar(From);
    ChrBth(ToWhom)        = ChrBth(From);
    ChrRsw(ToWhom)        = ChrRsw(From);
    ChrSpl(ToWhom)        = ChrSpl(From);
}

VOID Resurrect_Monster(IntT From, IntT ToWhom)
{
    IntT j;

    for (j = 0; j < 6; j++) {
        if (j < 6) {
            mData[ToWhom].Movement[j] = mData[From].Movement[j];
            mData[ToWhom].Damage[j] = mData[From].Damage[j];
            mData[ToWhom].Treasure[j] = mData[From].Treasure[j];
        }
        if (j < 3) 
            mData[ToWhom].AClass[j] = mData[From].AClass[j];
    }
    MonWnd(ToWhom) = MonWnd(From);
	 mData[ToWhom].Status = mData[From].Status;
	 mData[ToWhom].Changed = mData[From].Changed;
    strcpy(mData[ToWhom].Name, mData[From].Name);
    strcpy(mData[ToWhom].Race, mData[From].Race);
    mData[ToWhom].Alignment = mData[From].Alignment;
    mData[ToWhom].Size = mData[From].Size;
    mData[ToWhom].HitPoints = mData[From].HitPoints;
    mData[ToWhom].HPDown = mData[From].HPDown;
    mData[ToWhom].HitDice = mData[From].HitDice;
    mData[ToWhom].HDMods = mData[From].HDMods;
    mData[ToWhom].THAC0 = mData[From].THAC0;
    mData[ToWhom].MagicResist = mData[From].MagicResist;
    strcpy(mData[ToWhom].SpAttacks, mData[From].SpAttacks);
    strcpy(mData[ToWhom].SpDefense, mData[From].SpDefense);
    strcpy(mData[ToWhom].Experience, mData[From].Experience);
    strcpy(mData[ToWhom].Remarks, mData[From].Remarks);
    strcpy(mData[ToWhom].CombatMode, mData[From].CombatMode);
    mData[ToWhom].AttackWho = mData[From].AttackWho;
    mData[ToWhom].DisplayMode = mData[From].DisplayMode;
}

VOID Init_Char(IntT which)
{
    IntT j;

	 for (j = 0; j < 6; j++) {
		  if (j < 6)
				cData[which].SThrows[j] = 0;
		  if (j < 3) {
				ClsRch(which, j) = -1;
				ClsLvl(which, j) = -1;
				ClsCls(which, j) = -1;
				ClsKit(which, j) = -1;
		  }
	 }
	 ChrWnd(which) = cWindow;
	 ChrSta(which) = BLANK;
	 cData[which].Changed          = NO;
	 strcpy(ChrFil(which), "NUL");
	 strcpy(ChrPer(which), "Blank");
	 strcpy(ChrChr(which), "Blank");
	 ChrRac(which) = 0;
	 ChrAli(which) = 0;

	 cData[which].AClass           = 10;
	 cData[which].AType            = 13;
	 cData[which].APoints          = 0;
	 cData[which].APtDown          = 0;
    cData[which].AMagical         = 0;
    cData[which].SType            = 6;
    cData[which].SPoints          = 0;
    cData[which].SPtDown          = 0;
    cData[which].SMagical         = 0;
    cData[which].HType            = 6;
    cData[which].HPoints          = 0;
    cData[which].HPtDown          = 0;
    cData[which].HMagical         = 0;
    cData[which].ACAdj            = 0;
    cData[which].THAC0            = 20;

    StaStr(which) = 12;
    StaStp(which) = 0;
    StaDex(which) = 12;
	 StaDep(which) = 0;
    StaCon(which) = 12;
    StaCop(which) = 0;
    StaInt(which) = 12;
    StaInp(which) = 0;
    StaWis(which) = 12;
    StaWip(which) = 0;
    StaCha(which) = 12;
    StaChp(which) = 0;

    ChrPoi(which) = 0;
    ChrPet(which) = 0;
    ChrPar(which) = 0;
    ChrBth(which) = 0;
    ChrRsw(which) = 0;
    ChrSpl(which) = 0;

    cData[which].Psionic          = 'N';
    ChrHpt(which)                 = 1;
    ChrHpd(which)                 = 0;
    LitTyp(which)                 = 5;
    LitLft(which)                 = 0;
    strcpy(cData[which].NormalMode, "");
    strcpy(cData[which].CombatMode, "");
	 cData[which].AttackWho        = -1;
    cData[which].DisplayMode      = CHARACTER;
    cData[which].Experience       = 0;
    DscAge(which) = 0;
    DscSex(which) = 'M';
    DscHgt(which) = 0;
    DscWgt(which) = 0;
    DscEye(which) = 0;
    DscSkn(which) = 0;
    DscHrc(which) = 0;
    DscHrl(which) = 0;
    DscBdc(which) = 0;
    DscBdl(which) = 0;
    DscGa0(which) = -1;
    DscGa1(which) = -1;
    DscGa2(which) = -1;
    DscGa3(which) = -1;
    DscGa4(which) = -1;
    DscGa5(which) = -1;
    DscGa6(which) = -1;
    DscGa7(which) = -1;
    DscHnd(which) = 0;
    StaStr(which) = 12;
    StaStp(which) = 0;
	 StaDex(which) = 12;
    StaDep(which) = 0;
    StaCon(which) = 12;
    StaCop(which) = 0;
    StaInt(which) = 12;
    StaInp(which) = 0;
    StaWis(which) = 12;
    StaWip(which) = 0;
    StaCha(which) = 12;
    StaChp(which) = 0;
    ThfPip(which) = 0;
    ThfOlk(which) = 0;
    ThfFrt(which) = 0;
    ThfMsi(which) = 0;
    ThfHis(which) = 0;
    ThfHno(which) = 0;
    ThfCwa(which) = 0;
    ThfRla(which) = 0;
    ChrPoi(which) = 0;
    ChrPet(which) = 0;
    ChrPar(which) = 0;
    ChrBth(which) = 0;
    ChrRsw(which) = 0;
    ChrSpl(which) = 0;
}

VOID Init_Mons(IntT which)
{
	 IntT j;

	 for (j = 0; j < 6; j++) {
		  if (j < 6) {
				mData[which].Movement[j] = -1;
				mData[which].Damage[j]   = 0;
				mData[which].Treasure[j] = 0;
		  }
		  if (j < 3)
				mData[which].AClass[j]   = 10;
	 }
	 MonWnd(which) = cWindow;
	 mData[which].Status           = BLANK;
	 mData[which].Changed          = NO;
	 strcpy(mData[which].Race,       "Blank");
	 strcpy(mData[which].Name,       "Blank");
	 mData[which].Alignment        = 0;
	 mData[which].Size             = 'M';
	 mData[which].HitPoints        = 1;
	 mData[which].HPDown           = 0;
	 mData[which].HitDice          = 1;
	 mData[which].HDMods           = 0;
	 mData[which].THAC0            = 20;
    mData[which].MagicResist      = 0;
    strcpy(mData[which].SpAttacks,  "");
    strcpy(mData[which].SpDefense,  "");
    strcpy(mData[which].Experience, "");
    strcpy(mData[which].Remarks,    "");
    strcpy(mData[which].CombatMode, "");
    mData[which].AttackWho        = -1;
    mData[which].DisplayMode      = MONSTER;
}

