/* []---------------------------------------------------------------------[] */
/* |             GLoad.cpp: Game information loading routines.             | */
/* |                                                                       | */
/* |              The GLoad.cpp source code and concepts are               | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __GAMELOAD__

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

VOID Load_Characters(IntT CommandLoad);
VOID Verify_Character_Data(IntT charNum);

GBL VOID LoadCharacter(IntT loadwhere);
GBL VOID Und2Spc(ChrP msg);
GBL VOID Compose_Char_Data(IntT character);
GBL VOID Print_Char(AtrT DrawMode, IntT Whom);
GBL VOID Print_Character_Sheet(NOARG);
GBL VOID Print_Character_Data(IntT cmNum);
GBL VOID SavingThrows(IntT character);
GBL IntT Roll_Dice(IntT sides, IntT times);

GBL AtrT cMessage[4];
GBL AtrT cErrors[4];
GBL AtrT cAlt[4];
GBL AtrT cMain[4];
GBL IntT gaming_Time;
GBL IntT move_Rate;
GBL WndT cWindow;

VOID Load_Characters(IntT CommandLoad)
{
    IntT j, k, l, startLoad = 0;
    FILE *gamein;
    ChrT string[40], temp[4][9];
	 WndT LoadWind, SLWind;
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
            if (ChrSta(j) != BLANK) {
                LoadWind = Wopen(3, 5, 6, 42, BOX_DBL, cErrors[TCDM_WINDOW], cErrors[TCDM_WINDOW]);
                    Fix_Shadow(LoadWind);
                    Wputs(" There is a party in memory, do you\n");
                    Wputs(" want to merge another party?");
                    k = SelTxt(1, 30, cErrors[TCDM_BARINPUT], YesNo, 0);
					 WVclose(LoadWind);
                if (k == ERR_ARG)
                    startLoad = -1;
/*                if (k == 0)
                    ;  /* don't do anything, 0 means to continue with merge */
                if (k == 1) {
                    /* Go through the existing party and blank them all out */
                    for (l = 0; l < totalChars; l++)
                        if (ChrSta(l) != BLANK) {
                            Resurrect_Character(VOIDDATA, l);
                            ChrSta(l) = BLANK;
                            Compose_Char_Data(l);
                            if (charNumEx > 0) {
                                if (l >= charsOnScreen)
                                    if (l == CHARNUM)
                                        Print_Char(REVERSE, l);
                                    else 
                                        Print_Char(NORMAL, l);
									 }
                            else {
                                if (l < charsOnScreen)
                                    if (l == CHARNUM) 
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
            LoadWind = Wopen(3, 5, 6, 47, BOX_DBL, cMessage[TCDM_WINDOW], cMessage[TCDM_WINDOW]);
                Fix_Shadow(LoadWind);
                Wputs(" Do you wish to start loading characters\n");
                Wputs(" at the current cursor position?");
					 k = SelTxt(1, 33, cMessage[TCDM_BARINPUT], YesNo, 0);
                if (k == ERR_ARG)
                    startLoad = -1;
                if (k == 0) 
                    startLoad = CHARNUM;
                if (k == 1) {
                    Wborder(BOX_SNG);
                    Wshadoff();
                    SLWind = Wopen(4, 9, 7, 38, BOX_DBL, cMessage[TCDM_WINDOW], cMessage[TCDM_WINDOW]);
                        Fix_Shadow(SLWind);
                        Wputs(" Where do you want to start\n");
                        k = KwGetFmt(Message, "' loading characters? '%%");
                        if (k == ERR_ARG)
                            startLoad = -1;
                        else
                            startLoad = atoi(Message);
                    WVclose(SLWind);
                    Fix_Shadow(LoadWind);
                    Wborder(BOX_DBL);
                }
            WVclose(LoadWind);
        }
    }
    if (startLoad > -1 && startLoad < totalChars) {
        SelDirOff();
        SelParOff();
        strcpy(Message, saveDir);
        strcat(Message, "\\*.Gam");
        if (CommandLoad == TRUE ? 1 : SelFile(3, 5, 10, 20, BOX_DBL, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW], cAlt[TCDM_BARINPUT], NO, Message, AddShadow) != NULL) {
            if (CommandLoad == TRUE)
                sprintf(SelNam, "%s\\%s.Gam", saveDir, commandFile);
            for (j = strlen(SelNam); j >= 0; j--)
                if (SelNam[j] == '\\') {
                    strcpy(commandFile, SelNam + j + 1);
                    commandFile[strlen(commandFile) - 4] = '\0';
                    break;
                }
            if ((gamein = fopen(SelNam, "r")) != NULL) {
                if (fgets(string, 40, gamein) != NULL) {
                    string[strlen(string) - 1] = '\0';
                    sscanf(string, "%d %d %d %d %d %d %d %d %d %d %d",
                        &wStatus,
                        &WMDelay,
                        &move_Rate,
                        &gaming_Time,
                        &TctlMon,
                        &TctlDay,
                        &TctlYer,
                        &TctlHou,
                        &TctlMin,
                        &TctlMel,
                        &TctlRnd
                    );
                }
                LoadWind = WpopUp(CNT_VER, 5, combatMode == TRUE ? 0 : 40, 11, combatMode == TRUE ? 38 : 78, BOX_DBL, cMessage[TCDM_WINDOW], cMessage[TCDM_WINDOW]);
                Wtitle(" Loading Characters ", TTL_CNT, (AtrT)(cMessage[TCDM_WINDOW] | _BLINK));
                Fix_Shadow(LoadWind);
                for (j = 0; j < 5; j++)
                    if (fgets(string, 40, gamein) != NULL) {
                        string[strlen(string) - 1] = '\0';
                        strcpy(gameInfo[j], string);
                        Wprtf((BytT)j, 1, cMessage[TCDM_WINDOW], gameInfo[j]);
                    }
                while (!feof(gamein)) {
                    if (fgets(string, 40, gamein) != NULL) {
                        string[strlen(string) - 1] = '\0';
                        sscanf(string, "%s %s %s %s", temp[0], temp[1], temp[2], temp[3]);
                        /* loop through all the temp[?] strings       */
                        /*   loop through all the status's            */
                        /*     if we find a blank character...        */
                        /*       check to see if temp[?] is blank     */
                        /*         if not, load characters            */
                        /*       break out of inside loop             */
                        /*   make start of loop same as ending place  */
                        for (l = 0; l < 4; l++) {
                            for (k = startLoad; k < totalChars; k++) {
                                if (ChrSta(k) == BLANK) {
                                    if (stricmp("[BLANK]", temp[l]) != 0) {
                                        /* save character */
                                        strcpy(ChrFil(k), temp[l]);
                                        LoadCharacter(k);
                                        Verify_Character_Data(k);
                                        Und2Spc(ChrChr(k));
                                        Und2Spc(ChrPer(k));
                                        SavingThrows(k);
                                        RePrint = 0;
                                        Compose_Char_Data(k);
                                        if (charNumEx > 0) {
                                            if (k >= charsOnScreen)
                                                if (k == CHARNUM)
                                                    Print_Char(REVERSE, k);
                                                else 
                                                    Print_Char(NORMAL, k);
                                        }
                                        else {
                                            if (k < charsOnScreen)
                                                if (k == CHARNUM) 
                                                    Print_Char(REVERSE, k);
                                                else
                                                    Print_Char(NORMAL, k);
                                        }
                                    }
                                    startLoad = k + 1;
                                    break;
                                }
                            }
                        }
                    }
                }
                fclose(gamein);
                Wactiv(LoadWind);
                Wtitle(" Press any key to continue ", TTL_CNT, cMessage[TCDM_WINDOW]);
                j = KeyGetc();
                WVclose(LoadWind);
                RePrint = NewSheet = 1;
                Print_Char(REVERSE, CHARNUM);
            }
            else {
                sprintf(Message, " Unable to find \"%s\\%s.gam\"", saveDir, commandFile);
                MessageWindow(Message);
                VcurHid(0);
            }
            SelFree();
        }
        else {
            MessageWindow(" Unable to find any .GAMe files.");
            VcurHid(0);
        }
    }
}

/*
 * This routine checks the various statistics to make sure they don't
 * exceed any of the internal variables (this way we aren't wandering
 * around with the pointers *crash* and we don't have strange statistics
 * showing up
 * it also makes any 'permanent' changes to the character.
 */

VOID Verify_Character_Data(IntT charData)
{
    IntT j, k;

    cData[charData].Changed = NO;
    /* make sure the character status is correct; DEAD ALIVE or BLANK */
    /* change to DEAD if invalid */
    if (ChrSta(charData) != DEAD)
        if (ChrSta(charData) != ALIVE)
            if (ChrSta(charData) != BLANK) {
                MessageWindow2(" Status field invalid.\n", " Character Data is corrupt!");
                ChrSta(charData) = DEAD;
            }
    /* verify that there is such a group -1 (none), 0, 1, 2, 3, or 4 */
    cData[charData].THAC0 = 20;
    for (j = 0; j < 3; j++) {
        if (ClsRch(charData, j) < -1 || ClsRch(charData, j) > 4) {
            sprintf(Message, " Group field %d is invalid\n", j);
            MessageWindow2(Message, " Assuming member of Warriors.");
            ClsRch(charData, j) = 0;
        }
        if (ClsLvl(charData, j) >= 0) {
            switch (ClsRch(charData, j)) {
                case PRIEST :
                    k = 20 - (ClsLvl(charData, j) - 1) / 3 * 2;
                    break;
                case ROGUE :
                    k = 20 - (ClsLvl(charData, j) - 1) / 2;
                    break;
                case WARRIOR :
                    k = 20 - (ClsLvl(charData, j) - 1);
                    break;
                case WIZARD :
                    k = 20 - (ClsLvl(charData, j) - 1) / 3;
                    break;
                case PSIONICIST :
                    k = 20 - (ClsLvl(charData, j) - 1) / 2;
                    break;
            }
            if (cData[charData].THAC0 > k)
                cData[charData].THAC0 = k;
        }
    }
}

