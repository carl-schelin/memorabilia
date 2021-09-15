/* []---------------------------------------------------------------------[] */
/* |             Utility.cpp: Several miscellaneous routines.              | */
/* |                                                                       | */
/* |             The Utility.cpp source code and concepts are              | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __UTILITY__

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <TcxlAtr.H>
#include <TcxlCod.H>
#include <TcxlDef.H>
#include <TcxlInp.H>
#include <TcxlKey.H>
#include <TcxlSel.H>
#include <TcxlVid.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

GBL VOID Print_Char(AtrT DrawMode, IntT Whom);
GBL VOID Attack_Line(AtrT DrawMode, IntT Whom);

IntT Verify_Quit(NOARG);
VOID Compose_Char_Data(IntT character);
VOID Und2Spc(ChrP msg);
VOID Spc2Und(ChrP msg);

GBL IntT dexterity[25];
GBL IntT self_Roll;
GBL IntT lStdq[2];
GBL AtrT cAlt[4];
GBL AtrT cMain[4];
GBL AtrT cErrors[4];
GBL AtrT cTcdm[4];
GBL AtrT cMessage[4];
GBL IntT VidCWid;
GBL IntT VidCDep;
GBL ChrT header[81];
GBL IntT MaxStats[12];
GBL IntT MinStats[12];

IntT Verify_Quit(NOARG)
{
    IntT j;
	 WndT QuitWind;
	 ChrP YesNo[] = {"Yes", "No", NULL};

    QuitWind = Wopen(lStdq[0], lStdq[1], lStdq[0] + 4, lStdq[1] + 26, BOX_DBL, cErrors[TCDM_WINDOW], cErrors[TCDM_WINDOW]);
        Fix_Shadow(QuitWind);
        Wtitle(" Quit Game ", TTL_LFT, cErrors[TCDM_WINDOW]);
        Wprts(1, 1, cErrors[TCDM_WINDOW], "Quit! Are you sure?");
        j = SelTxt(1, 21, cErrors[TCDM_BARINPUT], YesNo, 0);
        if (j == ERR_ARG)
            j = 1;
    WVclose(QuitWind);
    return j;
}

VOID Fix_Shadow(WndT CloseWind)
{
    WndT Active;

    Active = Whandle();
    Wactiv(CloseWind);
    Wshadow(DGREY|_BLACK);
    Wactiv(Active);
}                                       

VOID CTYP AddShadow(NOARG)
{
    Fix_Shadow(Whandle());
}

VOID Compose_Char_Data(IntT character)
{
    ChrT temp[15];
    IntT tempTHAC0;

    if (combatMode == TRUE) {
        if (combatStatus == MONSTER) {
            if (mData[character].Status == ALIVE) {
                strcpy(temp, mData[character].Race);
                if (MonAtk(character) > -1) {
                    tempTHAC0 = mData[character].THAC0;
                    temp[11] = '\0';
                    sprintf(mData[character].CombatMode, "%-12s %2d/%2d", temp, 
                      tempTHAC0 - cData[MonAtk(character)].AClass,
                      tempTHAC0 - 10 - dexterity[StaDex(MonAtk(character)) - 1]);
                }
                else {
                    temp[14] = '\0';
                    sprintf(mData[character].CombatMode, "%-15s %2d", temp, 
                      mData[character].THAC0);
                }
            }
            else {
                strcpy(mData[character].CombatMode, "                  ");
            }
        }
        else {
            if (ChrSta(character) == ALIVE) {
                strcpy(Message, ChrPer(character));
                if (ChrAtk(character) > -1) {
                    tempTHAC0 = cData[character].THAC0;
                    Message[11] = '\0';
                    sprintf(cData[character].CombatMode, "%-12s %2d/%2d", Message,
                      tempTHAC0 - mData[ChrAtk(character)].AClass[1],
                      tempTHAC0 - mData[ChrAtk(character)].AClass[0]);
                }
                else {
                    Message[14] = '\0';
                    sprintf(cData[character].CombatMode, "%-15s %2d",
                      Message, cData[character].THAC0);
                }
            }
            else {
                strcpy(cData[character].CombatMode, "                  ");
            }
        }
    }
    else {
        if (ChrSta(character) == ALIVE) {
            strcpy(Message, ChrPer(character));
            Message[13] = '\0';
            sprintf(cData[character].NormalMode, 
              "%2d %-14s %2d%3s %2d %2d %2d %2d %2d ",
              character, Message, StaStr(character), 
              StaStp(character) > 0 ? itoa(StaStp(character), temp, 10) : " ",
              StaDex(character), StaCon(character), StaInt(character), 
              StaWis(character), StaCha(character));
            strcpy(Message, ChrPer(character));
            if (ChrAtk(character) > -1) {
                tempTHAC0 = cData[character].THAC0;
                Message[11] = '\0';
                sprintf(cData[character].CombatMode, "%-12s %2d/%2d", Message,
                  tempTHAC0 - mData[ChrAtk(character)].AClass[1],
                  tempTHAC0 - mData[ChrAtk(character)].AClass[0]);
            }
            else {
                Message[14] = '\0';
                sprintf(cData[character].CombatMode, "%-15s %2d",
                  Message, cData[character].THAC0);
            }
        }
        else {
            sprintf(cData[character].NormalMode, "                                       ");
            strcpy(cData[character].CombatMode, "                  ");
        }
    }
}

/*-- function MessageWindow -----------------------------------------
 *
 * Opens a window and Vprints a line of text. Then waits for a keypress
 * to continue.
 *
 * Input: msg  -  Message to be printed in the window.
 *
 */

VOID MessageWindow(ChrP msg)
{
    WndT MsgWind;

    VcurHid(0);
    MsgWind = Wopen(VidCDep - 1, VidCWid - (strlen(msg) / 2 + 2),
          VidCDep + 1, VidCWid + (strlen(msg) / 2 + 1),
          BOX_DBL, cMessage[TCDM_WINDOW], cMessage[TCDM_WINDOW]);
        Fix_Shadow(MsgWind);
        Wputs(msg);
        KeyTime(27);
    WVclose(MsgWind);
    VcurHid(1);
}

VOID MessageWindow2(ChrP msg1, ChrP msg2)
{
    IntT lenOString = 0;
    WndT MsgWind;

    lenOString = strlen(msg1);
    if (strlen(msg2) > (size_t)lenOString)
        lenOString = strlen(msg2);
    VcurHid(0);
    MsgWind = Wopen(VidCDep - 1, VidCWid - (lenOString / 2 + 2),
          VidCDep + 2, VidCWid + (lenOString / 2 + 1),
          BOX_DBL, cMessage[TCDM_WINDOW], cMessage[TCDM_WINDOW]);
        Fix_Shadow(MsgWind);
        Wputs(msg1);
        Wputs(msg2);
        KeyTime(27);
    WVclose(MsgWind);
    VcurHid(1);
}

VOID Und2Spc(ChrP msg)
{
    IntT j;

    for (j = 0; (unsigned)j < strlen(msg); j++)
        if (msg[j] == '_')
            msg[j] = ' ';
}

VOID Spc2Und(ChrP msg)
{
    IntT j;

    for (j = 0; (unsigned)j < strlen(msg); j++)
        if (msg[j] == ' ')
            msg[j] = '_';
}

VOID Maximize(NOARG)
{
    IntT j;

    for (j = 0; j < 12; j+=2)
        if (cData[CHARNUM].Stats[j] > MaxStats[j])
            cData[CHARNUM].Stats[j] = MaxStats[j];
    if (StaStr(CHARNUM) != 18)
        StaStp(CHARNUM) = 0;
}

VOID Minimize(NOARG)
{
    IntT j;

    for (j = 0; j < 12; j+=2)
        if (cData[CHARNUM].Stats[j] < MinStats[j])
            cData[CHARNUM].Stats[j] = MinStats[j];
}

