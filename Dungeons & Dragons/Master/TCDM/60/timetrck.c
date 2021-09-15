/* []---------------------------------------------------------------------[] */
/* |           TimeTrck.cpp: Keep track of game date and time.             | */
/* |                                                                       | */
/* |            The TimeTrck.cpp source code and concepts are              | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __TIMETRACK__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <TcxlEnt.H>
#include <TcxlMnu.H>
#include <TcxlVid.H>
#include <TcxlWin.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID Time_Keeping(IntT AddTime);

GBL IntT Roll_Dice(IntT sides, IntT times);

IntT encounter[8][6] = {
    { 0, 1, 0, 1, 0, 1 },    /*  Plains     */
    { 0, 1, 1, 0, 1, 1 },    /*  Scrub      */
    { 0, 0, 1, 0, 1, 1 },    /*  Rough      */
    { 1, 1, 1, 1, 1, 1 },    /*  Forest     */
    { 0, 0, 1, 0, 1, 1 },    /*  Desert     */
    { 1, 0, 1, 0, 0, 0 },    /*  Hills      */
    { 0, 0, 1, 0, 1, 1 },    /*  Mountains  */
    { 1, 1, 1, 1, 1, 1 }     /*  Marsh      */
};

IntT Lost_Party = 9;
IntT time_Of_Day = 1;
IntT months_In_Year = 16;
IntT lost[8] = { 1, 3, 3, 7, 4, 2, 5, 6};
ChrP day_Periods[] = {
    "Night", "Predawn", "Morning", "Noon", "Aft-noon", "Evening"};
ChrT alarm[9];
IntT gaming_Time = 2;

GBL IntT terrain;
GBL IntT lSetting[2];
GBL IntT lMvrate[2];
GBL AtrT cMain[4];
GBL AtrT cCtrl[4];
GBL IntT population_Density;
GBL IntT NumberDays[16];
GBL IntT move_Rate;
GBL ChrT header[81];
GBL WndT cHeader, cStatus;

VOID Time_Keeping(IntT AddTime)
{
    IntT j;

    if (AddTime == INCREMENT) {
        if (gaming_Time == DUNGEONCRAWLING) {
            if (combatMode == 1)
                TctlRnd++;
            else {
                TctlRnd = 0;
                TctlMel++;
                for (j = 0; j < totalChars; j++) {
                    if (LitLft(j) > 0)
                        LitLft(j)--;
                    if (LitLft(j) == 0)
                        LitTyp(j) = 5;
                }
            }

            if (TctlRnd >= 10) {
                TctlMel++;
                TctlRnd = 0;
                for (j = 0; j < totalChars; j++) {
                    if (LitLft(j) > 0)
                        LitLft(j)--;
                    if (LitLft(j) == 0)
                        LitTyp(j) = 5;
                }
            }

            if (TctlMel >= move_Rate) {
                Wandering_Monster = 0;
                TctlMin += 10;
                TctlMel = 0;
            }
            if (TctlMin >= 60) {
                TctlHou++;
                time_Of_Day = TctlHou / 4;
                TctlMin = 0;
            }
            if ((TctlMin == 0 || TctlMin == 30) && TctlMel + TctlRnd == 0)
                Wandering_Monster = Roll_Dice(6, 1);
        }
        else {
            TctlMin = 0;
            TctlHou += 4;
            for (j = 0; j < totalChars; j++) {
                if (LitLft(j) > 0)
                    LitLft(j)--;
                if (LitLft(j) < 0) {
                    LitLft(j) = 0;
                    LitTyp(j) = 5;
                }
            }
            time_Of_Day = TctlHou / 4;
            if (encounter[terrain][time_Of_Day] == 1) 
                Wandering_Monster = Roll_Dice(population_Density, 1);
            if (time_Of_Day == PREDAWN) 
                Lost_Party = Roll_Dice(10, 1);
        }
        if (TctlHou >= 24) {
            TctlDay++;
            TctlHou = 0;
            time_Of_Day = 0;
        }
        if (TctlDay > NumberDays[TctlMon-1]) {
            TctlMon++;
            TctlDay = 1;
        }
        if (TctlMon > months_In_Year) {
            TctlYer++;
            TctlMon = 1;
        }
        if (strcmp(SysTime(1), alarm) >= 0) {
            alarm[0] = '\0';
    /*        printf("\a\a\a\a\a\a\a");  */
        }
    }
    sprintf(header,
        " %c TCDM v%d.%02d Time of Day: %-8s  Date: %02d-%02d-%04d      "
        "Time: %02d:%02d:%02d.%02d    ", 0xF0, TCDMVER >> 8 , TCDMVER & 0x00FF,
        day_Periods[time_Of_Day],
        TctlMon,
        TctlDay,
        TctlYer,
        TctlHou,
        TctlMin,
        TctlMel,
        TctlRnd
    );
    Wactiv(cHeader);
    Wprts(0, 0, cMain[TCDM_BARINPUT], header);
    if (gaming_Time == CAMPAIGNING)
        if (Lost_Party <= lost[terrain]) {
            Wactiv(cHeader);
            Wprts(0, 54, (AtrT)(cMain[TCDM_DESELECT] | _BLINK), "LOST");
        }
    if (Wandering_Monster == 1) {
        Wactiv(cHeader);
        Wprts(0, 77, (AtrT)(cMain[TCDM_DESELECT] | _BLINK), "WM");
    }
    sprintf(Message, "%8s", SysTime(2));
    Wactiv(cStatus);
    Wprts(0, VidWid - 9, cMain[TCDM_BARINPUT], Message);
}

