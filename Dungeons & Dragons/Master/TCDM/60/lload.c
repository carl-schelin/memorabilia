/* []---------------------------------------------------------------------[] */
/* |                    LLoad.cpp: Load layout routines.                   | */
/* |                                                                       | */
/* |              The LLoad.cpp source code and concepts are               | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __LAYLOAD__

#include <io.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <TcxlCod.H>
#include <TcxlEnt.H>
#include <TcxlInp.H>
#include <TcxlSel.H>
#include <TcxlWin.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID Load_Layout(IntT CommandLoad);

GBL AtrT cErrors[4];
GBL AtrT cMessage[4];
GBL AtrT cAlt[4];

VOID Load_Layout(IntT CommandLoad)
{
    IntT j, k, startLoad = 0;
    FILE *layin;
    ChrT string[40];
	 WndT LayWind;
	 ChrP YesNo[] = {"Yes", "No", NULL};

    /* is a layout already in memory? */
    /* if so, check to see if to overwrite it */
    /* ask if they want a blank one */
    /* if new one, ask for the filename to load */
    /* load file */
    if (CommandLoad == FALSE) {
        if (strlen(layoutScreen[0]) > 0) {
            LayWind = Wopen(3, 5, 6, 44, BOX_DBL, cErrors[TCDM_WINDOW], cErrors[TCDM_WINDOW]);
                Fix_Shadow(LayWind);
                Wputs(" There is a layout in memory, are you\n");
                Wputs(" sure you wish to replace it?");
                j = SelTxt(1, 30, cErrors[TCDM_BARINPUT], YesNo, 0);
            WVclose(LayWind);
            if (j == ERR_ARG || j == 1)
                startLoad = -1;
            if (j == 0) {
                for (k = 0; k < 50; k++)
                    layoutScreen[k][0] = '\0';
                for (j = 0; j < 100; j++) 
                    for (k = 0; k < 4; k++)
                        layoutLinks[j][k] = -1;
                startLoad = 0;
            }
        }
        if (startLoad == 0) {
            LayWind = Wopen(3, 5, 6, 29, BOX_DBL, cMessage[TCDM_WINDOW], cMessage[TCDM_WINDOW]);
                Fix_Shadow(LayWind);
                Wputs(" Do you want to load a\n");
                Wputs(" layout from disk?");
                j = SelTxt(1, 19, cMessage[TCDM_BARINPUT], YesNo, 0);
                if (j == ERR_ARG || j == 1)
                    startLoad = -1;
            WVclose(LayWind);
        }
    }
    if (startLoad > -1) {
        SelDirOff();
        SelParOff();
        strcpy(Message, layoutDir);
        strcat(Message, "\\*.Out");
        if (CommandLoad == TRUE ? 1 : SelFile(3, 5, 10, 20, BOX_DBL, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW], cAlt[TCDM_BARINPUT], 0, Message, AddShadow) != NULL) {
            if (CommandLoad == TRUE) 
                sprintf(SelNam, "%s\\%s.Out", layoutDir, layoutFile);
            for (j = strlen(SelNam); j >= 0; j--) 
                if (SelNam[j] == '\\') {
                    strcpy(layoutFile, SelNam + j + 1);
                    layoutFile[strlen(layoutFile) - 4] = '\0';
                    break;
                }
            if ((layin = fopen(SelNam, "r")) != NULL) {
                for (j = 0; j < 50; j++) {
                    if (fgets(string, 40, layin) != NULL) {
                        string[strlen(string) - 1] = '\0';
                        strcpy(layoutScreen[j], string);
                    }
                }
                for (j = 0; j < 100; j++) {
                    if (fgets(string, 11, layin) != NULL) {
                        string[strlen(string) -1] = '\0';
                        sscanf(string, "%d %d %d %d", &layoutLinks[j][0], &layoutLinks[j][1], &layoutLinks[j][2], &layoutLinks[j][3]);
                    }
                }
                fclose(layin);
            }
            else {
                sprintf(Message, " Unable to find \"%s\\%s.out\"", layoutDir, layoutFile);
                MessageWindow(Message);
            }
            SelFree();
        }
        else
            MessageWindow(" Unable to find any .OUT files.");
    }
}

