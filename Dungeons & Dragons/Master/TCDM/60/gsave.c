/* []---------------------------------------------------------------------[] */
/* |             GSave.cpp: Save all Game information routines.            | */
/* |                                                                       | */
/* |               The GSave.cpp source code and concepts are              | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __GAMESAVE__

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

VOID Save_Characters(NOARG);

GBL VOID SaveCharacter(IntT savewhere);
GBL VOID Und2Spc(ChrP msg);
GBL VOID Spc2Und(ChrP msg);

GBL AtrT cMessage[4];
GBL AtrT cErrors[4];
GBL AtrT cAlt[4];
GBL IntT gaming_Time;
GBL IntT move_Rate;

VOID Save_Characters(NOARG)
{
    IntT j, k;
    IntT endSave = -1, lastBlock;
    FILE *gameout;
    ChrT string[40], saveFile[90];
	 WndT SaveWind;
	 ChrP YesNo[] = {"Yes", "No", NULL};

    /*
     * 1: see if there are any characters defined
     * 2: ask for the file to save to
     * 3: check to see if it exists and verify overwrite if it does
     * 4: get the 5 line information block to be saved
     * 5: save the information
     *  a: get number of character blocks
     *  b: build initial line
     *  c: save init line
     *  d: save info blocks
     *  e: build and save character blocks
     */

    for (j = 0; j < totalChars; j++)  /* find the LAST non-blank character */
        if (ChrSta(j) != BLANK)
            endSave = j;
    if (endSave >= 0) {
        SaveWind = Wopen(4, 9, 7, 41, BOX_DBL, cMessage[TCDM_WINDOW], cMessage[TCDM_WINDOW]);
            Fix_Shadow(SaveWind);
            Wputs(" What do you wish to call the\n");
            sprintf(Message, "' save file? [%s] '********", commandFile);
            k = KwGetFmt(saveFile, Message);
            if (k != ERR_NUL)
                endSave = -1;
            if (strlen(saveFile) == 0)
                strcpy(saveFile, commandFile);
            strcpy(commandFile, saveFile);
        WVclose(SaveWind);
    }
    if (endSave >= 0) {
        strcpy(Message, saveDir);
        strcat(Message, "\\");
        strcat(Message, saveFile);
        strcat(Message, ".Gam");
        if (access(Message, 00) == 0) {
            SaveWind = Wopen(3, 5, 6, 42, BOX_DBL, cErrors[TCDM_WINDOW], cErrors[TCDM_WINDOW]);
                Fix_Shadow(SaveWind);
                Wputs(" That file exists, do you wish\n");
                Wputs(" to overwrite it? ");
                k = SelTxt(1, 18, cErrors[TCDM_BARINPUT], YesNo, 0);
                if (k == ERR_ARG)
                    endSave = -1;
/*                if (k == 0)
                    ;  /* don't do anything, 0 means to overwrite the file */
                if (k == 1)
                    endSave = -1;
            WVclose(SaveWind);
        }
    }
    if (endSave >= 0) {
        SaveWind = WpopUp(CNT_VER, 5, combatMode == TRUE ? 0 : 40, 11, combatMode == TRUE ? 38 : 78, BOX_DBL, cMessage[TCDM_WINDOW], cMessage[TCDM_WINDOW]);
            Fix_Shadow(SaveWind);
            EntDef(cMessage[TCDM_WINDOW], cMessage[TCDM_WINDOW], 5);
                EntFld(0, 1, gameInfo[0], "***********************************", FLD_NUL, 1, FLD_CHG, NULL, 0);
                EntFld(1, 1, gameInfo[1], "***********************************", FLD_NUL, 2, FLD_CHG, NULL, 0);
                EntFld(2, 1, gameInfo[2], "***********************************", FLD_NUL, 3, FLD_CHG, NULL, 0);
                EntFld(3, 1, gameInfo[3], "***********************************", FLD_NUL, 4, FLD_CHG, NULL, 0);
                EntFld(4, 1, gameInfo[4], "***********************************", FLD_NUL, 5, FLD_CHG, NULL, 0);
            k = EntGet(1);
            if (k == ERR_ARG)
                endSave = -1;
        WVclose(SaveWind);
    }
    /*
     * 5: save the information
     *  a: get number of character blocks
     *  b: open the file for output
     *  c: build initial line
     *  d: save init line
     *  e: save info blocks
     *  f: build and save character blocks
     */
    if (endSave >= 0) {
        if ((gameout = fopen(Message, "w")) != NULL) {
            sprintf(string, "%d %3d %2d %d %2d %2d %4d %2d %2d %2d %2d\n",
                wStatus,
                WMDelay,
                move_Rate,
                gaming_Time,
                TctlMon,
                TctlDay,
                TctlYer,
                TctlHou,
                TctlMin,
                TctlMel,
                TctlRnd);
            fputs(string, gameout);
            for (j = 0; j < 5; j++) {
                fputs(gameInfo[j], gameout);
                fputc('\n', gameout);
            }
            for (j = 0; j <= endSave; j++)
                if (ChrSta(j) != BLANK && cData[j].Changed == YES) {
                    Spc2Und(ChrChr(j));
                    Spc2Und(ChrPer(j));
                    Spc2Und(ChrFil(j));
                    SaveCharacter(j);
                    Und2Spc(ChrChr(j));
                    Und2Spc(ChrPer(j));
                }
            lastBlock = endSave / 4 + 1;
            k = 0;
				for (j = 0; j < lastBlock; j++) {
					 strcpy(string, (ChrSta(k) == BLANK ? "[BLANK]" : ChrFil(k)));
					 k++;
					 strcat(string, " ");
					 strcat(string, (ChrSta(k) == BLANK ? "[BLANK]" : ChrFil(k)));
					 k++;
					 strcat(string, " ");
					 strcat(string, (ChrSta(k) == BLANK ? "[BLANK]" : ChrFil(k)));
					 k++;
					 strcat(string, " ");
					 strcat(string, (ChrSta(k) == BLANK ? "[BLANK]" : ChrFil(k)));
					 k++;
					 strcat(string, "\n");
					 fputs(string, gameout);
				}
				fclose(gameout);
        }
        MessageWindow(" Game Saved");
    }
    else 
        MessageWindow(" Unable to save file");
}

