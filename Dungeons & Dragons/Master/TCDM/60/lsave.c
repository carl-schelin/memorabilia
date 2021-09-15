/* []---------------------------------------------------------------------[] */
/* |                 LSave.cpp: Layout file save routines.                 | */
/* |                                                                       | */
/* |              The LSave.cpp source code and concepts are               | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __LAYSAVE__

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

VOID Save_Layout(NOARG);

GBL AtrT cErrors[4];
GBL AtrT cMessage[4];
GBL AtrT cAlt[4];

VOID Save_Layout(NOARG)
{
    IntT j, k;
    IntT endSave = 0;
    FILE *layout;
    ChrT saveFile[90];
	 WndT LayWind;
	 ChrP YesNo[] = {"Yes", "No", NULL};

    LayWind = Wopen(4, 9, 7, 41, BOX_DBL, cMessage[TCDM_WINDOW], cMessage[TCDM_WINDOW]);
        Fix_Shadow(LayWind);
        Wputs(" What do you wish to call the\n");
        sprintf(Message, "' save file? [%s] '********", layoutFile);
        k = KwGetFmt(saveFile, Message);
        if (k != ERR_NUL)
            endSave = -1;
        if (strlen(saveFile) == 0)
            strcpy(saveFile, layoutFile);
    WVclose(LayWind);
    if (endSave >= 0) {
        strcpy(Message, layoutDir);
        strcat(Message, "\\");
        strcat(Message, saveFile);
        strcat(Message, ".Out");
        if (access(Message, 00) == 0) {
            LayWind = Wopen(3, 5, 6, 42, BOX_DBL, cErrors[TCDM_WINDOW], cErrors[TCDM_WINDOW]);
                Fix_Shadow(LayWind);
                Wputs(" That file exists, do you wish\n");
                Wputs(" to overwrite it? ");
                k = SelTxt(1, 18, cErrors[TCDM_BARINPUT], YesNo, 0);
                if (k == ERR_ARG)
                    endSave = -1;
/*                if (k == 0)
                    ;  /* don't do anything, 0 means to overwrite the file */
                if (k == 1)
                    endSave = -1;
            WVclose(LayWind);
        }
    }
    /*
     * 5: save the information
     *  a: open the file for output
     *  b: save info blocks
     */
    if (endSave >= 0) {
        if ((layout = fopen(Message, "w")) != NULL) {
            for (j = 0; j < 50; j++) {
                layoutScreen[j][38] = '\0'; 
                sprintf(Message, "%s\n", layoutScreen[j]);
                fputs(Message, layout);
            }
            for (j = 0; j < 100; j++) {
                if (layoutLinks[j][0] != -1) {
                    sprintf(Message, "%d %d %d %d\n", layoutLinks[j][0], layoutLinks[j][1], layoutLinks[j][2], layoutLinks[j][3]);
                    fputs(Message, layout);
                }
            }
            fclose(layout);
        }
        MessageWindow(" Layout Saved");
    }
    else 
        MessageWindow(" Unable to save file");
}

