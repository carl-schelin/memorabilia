/* []---------------------------------------------------------------------[] */
/* |        AddHitPt.cpp: Add hit points to characters or monsters.        | */
/* |                                                                       | */
/* |             The AddHitPt.cpp source code and concepts are             | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __ADDHITPOINT__

#include <stdio.h>
#include <TcxlWin.h>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID CTYP AddCombatPoints(NOARG);
VOID CTYP AddMonitorPoints(NOARG);
VOID CTYP AddCombatCharacterPoints(NOARG);
VOID CTYP AddCombatMonsterPoints(NOARG);
VOID CTYP AddCharacterHitPoints(IntT character);
VOID CTYP BlindAddCharacterHitPoints(IntT character);
VOID CTYP AddMonsterHitPoints(IntT monster);
VOID CTYP BlindAddMonsterHitPoints(IntT monster);

GBL VOID Print_Char(AtrT DrawMode, IntT Whom);
GBL VOID Update_Data(IntT whichOne);
GBL VOID Compose_Char_Data(IntT character);

GBL WndT cWindow;

/*  if 0, roll for 50%, if lower, roll for death, if alive, restore */
/*  --------------------------------------------------------------- */
/*  combat mode = true                  */
/*    status = character                */
/*      attackwho > -1                  */
/*        attackwho.monster != blank    */
/*          add to monster hit points   */
/*      else                            */
/*        character != blank            */
/*          add to character hit points */
/*  else                                */
/*    add one to character              */


VOID CTYP AddHitPoints(NOARG)
{
	 if (combatMode == TRUE)
		  AddCombatPoints();
	 else
		  AddMonitorPoints();
}

VOID CTYP AddCombatPoints(NOARG)
{
	 if (combatStatus == CHARACTER)
		  AddCombatCharacterPoints();
	 else
		  AddCombatMonsterPoints();
}

VOID CTYP AddMonitorPoints(NOARG)
{
	 if (ChrSta(CHARNUM) != BLANK)
		  AddCharacterHitPoints(CHARNUM);
}

VOID CTYP AddCombatCharacterPoints(NOARG)
{
	 if (ChrAtk(CHARNUM) >= 0)
		  if (MonSta(ChrAtk(CHARNUM)) != BLANK)
				BlindAddMonsterHitPoints(ChrAtk(CHARNUM));
	 else
		  if (ChrSta(CHARNUM) != BLANK)
				AddCharacterHitPoints(CHARNUM);
}

VOID CTYP AddCombatMonsterPoints(NOARG)
{
	 if (MonAtk(MONNUM) >= 0)
		  if (ChrSta(MonAtk(MONNUM)) != BLANK)
				BlindAddCharacterHitPoints(MonAtk(MONNUM));
	 else
		  if (MonSta(MONNUM) != BLANK)
				AddMonsterHitPoints(MONNUM);
}

VOID CTYP AddCharacterHitPoints(IntT character)
{
	 if (ChrHpd(character) > 0) {
		  ChrHpd(character)--;
		  cData[character].Changed = YES;
		  if (ChrHpd(character) == ChrHpt(character) + 9) {
				ChrSta(character) = ALIVE;
				RePrint = TRUE;
				Compose_Char_Data(character);
				Print_Char(REVERSE, character);
		  }
		  else {
				if (ChrHpd(character) == ChrHpt(character) - 1) {
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

VOID CTYP BlindAddCharacterHitPoints(IntT character)
{
	 if (ChrHpd(character) > 0) {
		  ChrHpd(character)--;
		  cData[character].Changed = YES;
		  if (ChrHpd(character) == ChrHpt(character) + 9) {
				ChrSta(character) = ALIVE;
				Compose_Char_Data(character);
				Print_Char(NORMAL, character);
		  }
		  else
				if (ChrHpd(character) == ChrHpt(character) - 1)
					 Print_Char(NORMAL, character);
	 }
}

VOID CTYP AddMonsterHitPoints(IntT monster)
{
	 if (MonHpd(monster) > 0) {
        MonHpd(monster)--;
        if (MonHpd(monster) == MonHpt(monster) + 9) {
            MonSta(monster) = ALIVE;
            Compose_Char_Data(monster);
            RePrint = TRUE;
            Print_Char(REVERSE, monster);
        }
        else
            if (MonHpd(monster) == MonHpt(monster) - 1) {
                RePrint = TRUE;
					 Print_Char(REVERSE, monster);
            }
            else {
                Wactiv(cWindow);
                Update_Data(HITPOINTS);
            }
    }
}

VOID CTYP BlindAddMonsterHitPoints(IntT monster)
{
    if (MonHpd(monster) > 0) {
        MonHpd(monster)--;
		  if (MonHpd(monster) == MonHpt(monster) + 9) {
            MonSta(monster) = ALIVE;
            Compose_Char_Data(monster);
            Print_Char(NORMAL, monster);
        }
        else {
            if (MonHpd(monster) == MonHpt(monster) - 1)
                Print_Char(NORMAL, monster);
        }
    }
}

