/* []---------------------------------------------------------------------[] */
/* |                   MLoad.cpp: Monster load routines.                   | */
/* |                                                                       | */
/* |              The MLoad.cpp source code and concepts are               | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __MONSLOAD__

#include <io.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TcxlDef.H>
#include <TcxlInp.H>
#include <TcxlCod.H>
#include <TcxlSel.H>
#include <TcxlEnt.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID Load_Monsters(IntT CommandLoad);
VOID Verify_Monster_Data(IntT monNum);

GBL VOID Compose_Char_Data(IntT character);
GBL VOID Print_Char(AtrT DrawMode, IntT Whom);
GBL IntT Roll_Dice(IntT sides, IntT times);

GBL AtrT cMessage[4];
GBL AtrT cErrors[4];
GBL AtrT cAlt[4];
GBL AtrT cMain[4];

#define MONFILELEN 303

VOID Load_Monsters(IntT CommandLoad)
{
    IntT j, k, l, startLoad = 0;
    FILE *monin;
    ChrT string[MONFILELEN];
	WndT LoadWind, LMWind;
	ChrP YesNo[] = {"Yes", "No", NULL};

    /*
     * are there characters now?
     * if yes, ask if want to merge
     * if no, load, check and fill until CHARACTERS + 1
     * if merge, ask if to start at current location
     * if yes, fill all BLANK slots until CHARACTERS + 1
     * if no, ask for starting location
     * load, check and fill until CHARACTERS + 1
     */

    if (CommandLoad == FALSE) {
        for (j = 0; j < totalChars; j++)
            if (mData[j].Status != BLANK) {
                LoadWind = Wopen(3, 5, 6, 44, BOX_DBL, cErrors[TCDM_WINDOW], cErrors[TCDM_WINDOW]);
                    Fix_Shadow(LoadWind);
                    Wputs(" There are monsters in memory, do you\n");
                    Wputs(" want to merge more monsters?");
                    k = SelTxt(1, 30, cErrors[TCDM_BARINPUT], YesNo, 0);
                WVclose(LoadWind);
                if (k == ERR_ARG)
                    startLoad = -1;
/*                if (k == 0)
                    ;  /* don't do anything, 0 means to continue with merge */
                if (k == 1) {
                    /* go through the existing list of monsters and blank them */
                    for (l = 0; l < totalChars; l++)
                        if (mData[l].Status != BLANK) {
                            Resurrect_Monster(VOIDDATA, l);
                            mData[l].Status = BLANK;
                            Compose_Char_Data(l);
                            if (monNumEx > 0) {
                                if (l >= charsOnScreen)
                                    if (l == MONNUM)
                                        Print_Char(REVERSE, l);
                                    else 
                                        Print_Char(NORMAL, l);
                            }
                            else {
                                if (l < charsOnScreen)
                                    if (l == MONNUM) 
                                        Print_Char(REVERSE, l);
                                    else
                                        Print_Char(NORMAL, l);
                            }
                        }
                    startLoad = 0;
                }
                break;
            }
        if (startLoad == 0) {
            LoadWind = Wopen(3, 5, 6, 45, BOX_DBL, cMessage[TCDM_WINDOW], cMessage[TCDM_WINDOW]);
                Fix_Shadow(LoadWind);
                Wputs(" Do you wish to start loading monsters\n");
                Wputs(" at the current cursor position?");
                k = SelTxt(1, 33, cMessage[TCDM_BARINPUT], YesNo, 0);
                if (k == ERR_ARG)
                    startLoad = -1;
                if (k == 0) 
                    startLoad = MONNUM;
                if (k == 1) {
                    Wborder(0);
                    Wshadoff();
                    LMWind = Wopen(4, 9, 7, 38, BOX_DBL, cMessage[TCDM_WINDOW], cMessage[TCDM_WINDOW]);
                        Fix_Shadow(LMWind);
                        Wputs(" Where do you want to start\n");
                        k = KwGetFmt(Message, "' loading monsters? '%%");
                        if (k == ERR_ARG)
                            startLoad = -1;
                        else
                            startLoad = atoi(Message);
                    WVclose(LMWind);
                    Fix_Shadow(LMWind);
                    Wborder(1);
                }
            WVclose(LoadWind);
        }
    }
    if (startLoad > -1 && startLoad < totalChars) {
        SelDirOff();
        SelParOff();
        strcpy(Message, saveMDir);
        strcat(Message, "\\*.Mon");
        if (CommandLoad == TRUE ? 1 : SelFile(3, 45, 10, 60, BOX_DBL, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW], cAlt[TCDM_BARINPUT], 0, Message, AddShadow) != NULL) {
            if (CommandLoad == TRUE) 
                sprintf(SelNam, "%s\\%s.Mon", saveDir, monsterFile);
            for (j = strlen(SelNam); j >= 0; j--)
                if (SelNam[j] == '\\') {
                    strcpy(monsterFile, SelNam + j + 1);
                    monsterFile[strlen(monsterFile) - 4] = '\0';
                    break;
                }
            if ((monin = fopen(SelNam, "r")) != NULL) {
                for (k = startLoad; k < totalChars; k++) {
                    if (mData[k].Status == BLANK) {
                        if (fgets(string, MONFILELEN, monin) == NULL)
                            break;
                        string[strlen(string) - 1] = '\0';
                        sscanf(string, "%2d", &j);
                        if (j != -2) {
                            sscanf(string, "%d %s %s %d %c %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %s %s %s %d %d %d %d %d %d %s", 
                                &mData[k].Status,
                                mData[k].Name,
                                mData[k].Race,
                                &mData[k].Alignment,
                                &mData[k].Size,
                                &mData[k].Movement[0],
                                &mData[k].Movement[1],
                                &mData[k].Movement[2],
                                &mData[k].Movement[3],
                                &mData[k].Movement[4],
                                &mData[k].Movement[5],
                                &mData[k].AClass[0],
                                &mData[k].AClass[1],
                                &mData[k].AClass[2],
                                &mData[k].HitPoints,
                                &mData[k].HPDown,
                                &mData[k].HitDice,
                                &mData[k].HDMods,
                                &mData[k].THAC0,
                                &mData[k].Damage[0],
                                &mData[k].Damage[1],
                                &mData[k].Damage[2],
                                &mData[k].Damage[3],
                                &mData[k].Damage[4],
                                &mData[k].Damage[5],
                                &mData[k].MagicResist,
                                mData[k].SpAttacks,
                                mData[k].SpDefense,
                                mData[k].Experience,
                                &mData[k].Treasure[0],
                                &mData[k].Treasure[1],
                                &mData[k].Treasure[2],
                                &mData[k].Treasure[3],
                                &mData[k].Treasure[4],
                                &mData[k].Treasure[5],
                                mData[k].Remarks
                            );
                            Verify_Monster_Data(k);
                            RePrint = 0;
                            Compose_Char_Data(k);
                            if (monNumEx > 0) {
                                if (k >= charsOnScreen)
                                    if (k == MONNUM)
                                        Print_Char(REVERSE, k);
                                    else
                                        Print_Char(NORMAL, k);
                            }
                            else {
                                if (k < charsOnScreen)
                                    if (k == MONNUM) 
                                        Print_Char(REVERSE, k);
                                    else
                                        Print_Char(NORMAL, k);
                            }
                        }
                    }
                }
                fclose(monin);
                RePrint = NewSheet = 1;
                Print_Char(REVERSE, MONNUM);
            }
            SelFree();
        }
        else
            MessageWindow(" Unable to find any .MONster files.");
    }
}

/*
 * This routine checks the various statistics to make sure they don't
 * exceed any of the internal variables (this way we aren't wandering
 * around with the pointers *crash* and we don't have strange statistics
 * showing up
 */

VOID Verify_Monster_Data(IntT monData)
{
    IntT j;

    if (mData[monData].HitPoints == -11)
        mData[monData].HitPoints = Roll_Dice(8, mData[monData].HitDice) + mData[monData].HDMods * mData[monData].HitDice;
    if (mData[monData].HitPoints == -12)
        mData[monData].HitPoints = Roll_Dice(1, (mData[monData].HitDice - mData[monData].HDMods)) + mData[monData].HitDice;
    for (j = 0; (size_t)j < strlen(mData[monData].Name); j++)
        if (mData[monData].Name[j] == '_')
            mData[monData].Name[j] = ' ';
    for (j = 0; (size_t)j < strlen(mData[monData].Race); j++)
        if (mData[monData].Race[j] == '_')
            mData[monData].Race[j] = ' ';
    for (j = 0; (size_t)j < strlen(mData[monData].SpAttacks); j++)
        if (mData[monData].SpAttacks[j] == '_')
            mData[monData].SpAttacks[j] = ' ';
    for (j = 0; (size_t)j < strlen(mData[monData].SpDefense); j++)
        if (mData[monData].SpDefense[j] == '_')
            mData[monData].SpDefense[j] = ' ';
    for (j = 0; (size_t)j < strlen(mData[monData].Experience); j++)
        if (mData[monData].Experience[j] == '_')
            mData[monData].Experience[j] = ' ';
    for (j = 0; (size_t)j < strlen(mData[monData].Remarks); j++)
        if (mData[monData].Remarks[j] == '_')
            mData[monData].Remarks[j] = ' ';
}

