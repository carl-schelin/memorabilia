/* []---------------------------------------------------------------------[] */
/* |       SubHitPt.cpp: All the Hit Point subtraction routines.           | */
/* |                                                                       | */
/* |            The Main.cpp source code and concepts are                  | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __SUBTRACTHITPOINT__

#include <stdio.h>
#include <TcxlWin.h>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID CTYP SubtractCombatPoints(NOARG);
VOID CTYP SubtractMonitorPoints(NOARG);
VOID CTYP SubtractCombatCharacterPoints(NOARG);
VOID CTYP SubtractCombatMonsterPoints(NOARG);
VOID CTYP SubtractCharacterHitPoints(IntT character);
VOID CTYP BlindSubtractCharacterHitPoints(IntT character);
VOID CTYP SubtractMonsterHitPoints(IntT monster);
VOID CTYP BlindSubtractMonsterHitPoints(IntT monster);

GBL VOID Print_Char(AtrT DrawMode, IntT Whom);
GBL VOID Update_Data(IntT whichOne);
GBL VOID Compose_Char_Data(IntT character);

GBL WndT cWindow;

/*  if 1, roll for 50%, if lower, roll for death and deselect */

VOID CTYP SubtractHitPoints(NOARG)
{
    if (combatMode == TRUE)
        SubtractCombatPoints();
    else
        SubtractMonitorPoints();
}

VOID CTYP SubtractCombatPoints(NOARG)
{
    if (combatStatus == CHARACTER)
        SubtractCombatCharacterPoints();
    else
        SubtractCombatMonsterPoints();
}

VOID CTYP SubtractMonitorPoints(NOARG)
{
    if (ChrSta(CHARNUM) != BLANK)
        SubtractCharacterHitPoints(CHARNUM);
}

VOID CTYP SubtractCombatCharacterPoints(NOARG)
{
    if (ChrAtk(CHARNUM) >= 0)
        if (MonSta(ChrAtk(CHARNUM)) != BLANK)
            BlindSubtractMonsterHitPoints(ChrAtk(CHARNUM));
    else
        if (ChrSta(CHARNUM) != BLANK)
            SubtractCharacterHitPoints(CHARNUM);
}

VOID CTYP SubtractCombatMonsterPoints(NOARG)
{
    if (MonAtk(MONNUM) >= 0)
        if (ChrSta(MonAtk(MONNUM)) != BLANK)
            BlindSubtractCharacterHitPoints(MonAtk(MONNUM));
    else
        if (MonSta(MONNUM) != BLANK)
            SubtractMonsterHitPoints(MONNUM);
}

VOID CTYP SubtractCharacterHitPoints(IntT character)
{
    /* if not blank
     *   if less than -10 hit points
     *     add one to hp down
     *     if at -10
     *       change to dead and reprint
     *     otherwise
     *       if at 0
     *         reprint at dying
     *       otherwise
     *         reprint only the hp score
     */
    if (ChrHpd(character) < ChrHpt(character) + 10) {
        ChrHpd(character)++;
        cData[character].Changed = YES;
        if (ChrHpd(character) == ChrHpt(character) + 10) {
            ChrSta(character) = DEAD;
            Compose_Char_Data(character);
            RePrint = TRUE;
            Print_Char(REVERSE, character);
        }
        else {
            if (ChrHpd(character) == ChrHpt(character)) {
                RePrint = TRUE;
                Print_Char(REVERSE, character);
            }
            else {
                Wactiv(cWindow);
                Update_Data(HITPOINTS);
            }
        }
    }
}

VOID CTYP BlindSubtractCharacterHitPoints(IntT character)
{
    if (ChrHpd(character) < ChrHpt(character) + 10) {
        ChrHpd(character)++;
        cData[character].Changed = YES;
        if (ChrHpd(character) == ChrHpt(character) + 10) {
            ChrSta(character) = DEAD;
            Compose_Char_Data(character);
            Print_Char(NORMAL, character);
        }
        else {
            if (ChrHpd(character) == ChrHpt(character))
                Print_Char(NORMAL, character);
        }
    }
}

VOID CTYP SubtractMonsterHitPoints(IntT monster)
{
    if (MonHpd(monster) < MonHpt(monster) + 10) {
        MonHpd(monster)++;
        if (MonHpd(monster) == MonHpt(monster) + 10) {
            MonSta(monster) = DEAD;
            Compose_Char_Data(monster);
            RePrint = TRUE;
            Print_Char(REVERSE, monster);
        }
        else {
            if (MonHpd(monster) == MonHpt(monster)) {
                RePrint = TRUE;
                Print_Char(REVERSE, monster);
            }
            else {
                Wactiv(cWindow);
                Update_Data(HITPOINTS);
            }
        }
    }
}

VOID CTYP BlindSubtractMonsterHitPoints(IntT monster)
{
    IntT j;

    if (MonHpd(monster) < MonHpt(monster) + 10) {
        MonHpd(monster)++;
        if (MonHpd(monster) == MonHpt(monster) + 10) {
            MonSta(monster) = DEAD;
            Compose_Char_Data(monster);
            Print_Char(NORMAL, monster);
        }
        else {
            if (MonHpd(monster) <= MonHpt(monster)) {
                j = 10;
                if (MonArm(monster, 0) != 99)
                    j = MonArm(monster, 0);
                if (MonArm(monster, 1) != 99)
                    j = MonArm(monster, 1);
                if (MonArm(monster, 2) != 99)
                    j = MonArm(monster, 2);
                cData[CHARNUM].Experience += 5 * (10 - j);
                Wactiv(cWindow);
                Update_Data(EXPERIENCE);
            }
            if (MonHpd(monster) == MonHpt(monster))
                Print_Char(NORMAL, monster);
        }
    }
}

