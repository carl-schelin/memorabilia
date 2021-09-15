/* []---------------------------------------------------------------------[] */
/* |                Config.cpp: Load and parse Config.dm.                  | */
/* |                                                                       | */
/* |             The Config.cpp source code and concepts are               | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __CONFIG__

#include <stdio.h>
#include <string.h>
#include <TcxlCod.H>
#include <TcxlVid.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID Config_TCDM(NOARG);

/*  define box locations  */
/*  then define the default color selection  */

IntT lSetting[2] = {5, 20};
IntT lMvrate[2] =  {5, 20};
IntT lLight[2] =   {6, 20};
IntT lAst[2] =     {5, 20};
IntT lPsi[2] =     {5, 20};
IntT lExist[2] =   {3, 20};
IntT lStdq[2] =    {10, 10};

/*   colors equals   window/text,     bar/input,     deselected,   highlighted */
/* --------------- ---------------- -------------- -------------- -------------*/
AtrT cHelp[4]    = {WHITE|_RED,      WHITE|_BLUE,     RED|_LGREY, YELLOW|_RED};
AtrT cMessage[4] = {WHITE|_BLUE,       RED|_LGREY,  LGREY|_BLUE, MAGENTA|_BLUE};
AtrT cErrors[4]  = {WHITE|_RED,       BLUE|_LGREY,  LGREY|_RED,   YELLOW|_RED};
AtrT cAlt[4]     = {WHITE|_GREEN,    BLACK|_LGREY,  LGREY|_GREEN,    RED|_GREEN};
AtrT cCtrl[4]    = {WHITE|_MAGENTA,  WHITE|_BLUE,   LGREY|_MAGENTA, CYAN|_MAGENTA};
AtrT cTcdm[4]    = {WHITE|_CYAN,     WHITE|_BLACK,  LGREY|_CYAN,     RED|_CYAN};
AtrT cMain[4]    = {WHITE|_BLACK,     BLUE|_LGREY,  WHITE|_BLUE,  YELLOW|_BLACK};

IntT functions = 0;
ChrT assigned_Function[40][40];
IntT function_Keys[40];

VOID Config_TCDM(NOARG)
{
    FILE *config;
    ChrT adjustment[60];
    ChrT keyword[20];
    ChrT temp[80];
    IntT j = 0;
    ChrP fkeys[] = { 
         "F1",  "F2",  "F3",  "F4",  "F5", 
         "F6",  "F7",  "F8",  "F9", "F10", 
        "F11", "F12", "F13", "F14", "F15", 
        "F16", "F17", "F18", "F19", "F20",
        "F21", "F22", "F23", "F24", "F25", 
        "F26", "F27", "F28", "F29", "F30",
        "F31", "F32", "F33", "F34", "F35", 
        "F36", "F37", "F38", "F39", "F40"
    };

    /* access config.dm. if it doesn't exist, check the full path */
    /* of the original program call (check argv[0] for program name */
    if ((config = fopen("config.dm", "r")) != NULL) {
        while(fgets(temp, 80, config) != NULL) {

            if (strnicmp("/*", temp, 2) != 0) {

                j = 0;

                strncpy(keyword, temp, 20);
                keyword[strcspn(keyword, "=")] = '\0';
                strcpy(adjustment, temp + strcspn(temp, "=") + 1);
                adjustment[strlen(adjustment) - 1] = '\0';

                if (stricmp("savedir", keyword) == 0)
                    sscanf(adjustment, "%s", saveDir);

                if (stricmp("chardir", keyword) == 0)
                    sscanf(adjustment, "%s", savePDir);

                if (stricmp("monsterdir", keyword) == 0)
                    sscanf(adjustment, "%s", saveMDir);

                if (stricmp("layoutdir", keyword) == 0)
                    sscanf(adjustment, "%s", layoutDir);

                if (stricmp("wmdelay", keyword) == 0)
                    sscanf(adjustment, "%d", &WMDelay);

                if (stricmp("adjustsavingthrow", keyword) == 0)
                    sscanf(adjustment, "%hd %hd", &lAst[0], &lAst[1]);
    
                if (stricmp("newcharacter", keyword) == 0)
                    sscanf(adjustment, "%hd %hd", &lExist[0], &lExist[1]);
    
                if (stricmp("light", keyword) == 0) 
                    sscanf(adjustment, "%hd %hd", &lLight[0], &lLight[1]);
    
                if (stricmp("movement", keyword) == 0) 
                    sscanf(adjustment, "%hd %hd", &lMvrate[0], &lMvrate[1]);

                if (stricmp("setting", keyword) == 0) 
                    sscanf(adjustment, "%hd %hd", &lSetting[0], &lSetting[1]);

                if (stricmp("psionic", keyword) == 0) 
                    sscanf(adjustment, "%hd %hd", &lPsi[0], &lPsi[1]);

                if (stricmp("status", keyword) == 0)
                    sscanf(adjustment, "%d", &wStatus);

                for (j = 0; j < 10; j++)
                    if (stricmp(fkeys[j], keyword) == 0) {
                        function_Keys[functions] = j * 0x100 + Key_F1;
                        strcpy(assigned_Function[functions++], adjustment);
                        break;
                    }

                for (j = 10; j < 40; j++) 
                    if (stricmp(fkeys[j], keyword) == 0) {
                        function_Keys[functions] = j * 0x100 + Key_S_F1;
                        strcpy(assigned_Function[functions++], adjustment);
                        break;
                    }

            }
        }
        fclose(config);
    }
    else {
        MessageWindow("ERROR: Config.DM is unavailable.");
    }
}

