/* []---------------------------------------------------------------------[] */
/* |       Main.cpp: Main calling routine and initialization code.         | */
/* |                                                                       | */
/* |              The Main.cpp source code and concepts are                | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __MAIN__

/*  Borland Headers  */
#include <conio.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>
#include <time.h>

#include <TcxlBox.H>                        /*  TCXL v5.52.06 by IDC  */
#include <TcxlCod.H>
#include <TcxlCur.H>
#include <TcxlDef.H>
#include <TcxlHlp.H>
#include <TcxlInp.H>
#include <TcxlKey.H>
#include <TcxlMou.H>
#include <TcxlStr.H>
#include <TcxlVid.H>
#include <TcxlWin.H>

/*  TCDM Headers  */
#pragma hdrstop
#include "..\include\tcdm.h"                /*  Global Header File  */

/*  Functions Defined within main.c  */
VOID Select_Input(NOARG);
VOID CTYP GetHelp(NOARG);
VOID CTYP IncrementTime(NOARG);
VOID CTYP MoveRight(NOARG);
VOID CTYP MoveLeft(NOARG);
VOID CTYP SubtractArmorPoints(NOARG);
VOID CTYP SubtractShieldPoints(NOARG);
VOID CTYP SubtractHelmetPoints(NOARG);
VOID CTYP AddArmorPoints(NOARG);
VOID CTYP AddShieldPoints(NOARG);
VOID CTYP AddHelmetPoints(NOARG);

/*  Functions used by main but defined elsewhere       Where?    */
GBL VOID Config_TCDM(NOARG);                       /*  Config    */
GBL VOID Screen_Setup(IntT DoLogo);                /*  Utility   */
GBL VOID Time_Keeping(IntT AddTime);               /*  Time      */
GBL VOID Print_Char(AtrT DrawMode, IntT Whom);     /*  Display   */
GBL VOID Update_Data(IntT whichOne);               /*  Display   */
GBL IntT Verify_Quit(NOARG);                       /*  Utility   */
GBL VOID Game_Setting(NOARG);                      /*  Time      */
GBL VOID CTYP Set_Time(NOARG);                     /*  Time      */
GBL VOID CTYP Set_Date(NOARG);                     /*  Time      */
GBL VOID Edit_Character(IntT Edit_Mode);           /*  New       */
GBL VOID Psionic_Data(NOARG);                      /*  Psionic   */
GBL VOID Activate_Light(NOARG);                    /*  Light     */
GBL VOID Adjust_Saving_Throws(NOARG);              /*  SThrow    */
GBL VOID Compose_Char_Data(IntT character);        /*  Utility   */
GBL VOID New_Character(NOARG);                     /*  New       */
GBL VOID Insert_Character(NOARG);                  /*  InsDel    */
GBL VOID Delete_Character(NOARG);                  /*  InsDel    */
GBL VOID Delete_All(NOARG);                        /*  InsDel    */
GBL VOID Insert_All(NOARG);                        /*  InsDel    */
GBL VOID Load_Monsters(IntT CommandLoad);          /*  mfileio   */
GBL VOID Load_Characters(IntT CommandLoad);        /*  cfileio   */
GBL VOID Save_Characters(NOARG);                   /*  cfileio   */
GBL VOID Load_Layout(IntT CommandLoad);            /*  lfileio   */
GBL VOID Save_Layout(NOARG);                       /*  lfileio   */
GBL VOID Edit_Layout(IntT Edit_Mode);              /*  layout    */
GBL VOID PrintKeyList(NOARG);                      /*  utility   */
GBL VOID Display_Thief_Skills(NOARG);              /*  thief     */
GBL VOID Display_Cleric_Skills(NOARG);             /*  cleric    */
GBL KeyT CheckLeftMouse(KeyT c);                   /*  chkmouse  */
GBL KeyT CheckMouse(KeyT c);                       /*  chkmouse  */
GBL VOID Adjust_Armor_Class(NOARG);                /*  aclass    */
GBL IntT Roll_Dice(IntT sides, IntT times);        /*  utility   */
GBL VOID Void_Character(NOARG);                    /*  insdel    */
GBL VOID SelectFont(ChrP fontFile);                /*  fontset   */
GBL VOID RestoreDefault(NOARG);                    /*  fontset   */
GBL VOID GetMode(NOARG);                           /*  fontset   */
GBL VOID Init_Char(IntT which);                    /*  swap      */
GBL VOID Init_Mons(IntT which);                    /*  swap      */
GBL VOID CTYP AddHitPoints(NOARG);                 /*  addhitpt  */
GBL VOID CTYP SubtractHitPoints(NOARG);            /*  subhitpt  */
GBL VOID Display_Desc(NOARG);                      /*  display   */
GBL VOID GenerateWeather(NOARG);                   /*  weather   */
GBL VOID MoveHome(NOARG);									/*  move		  */
GBL VOID MoveEnd(NOARG); 									/*  move		  */
GBL VOID MovePgUp(NOARG);									/*  move		  */
GBL VOID MovePgDn(NOARG);									/*  move		  */
GBL VOID MoveUp(NOARG);  									/*  move		  */
GBL VOID MoveDown(NOARG);									/*  move		  */
GBL VOID Edit_Monster(NOARG);                      /*  Edit monster */

GBL VOID getFilename(NOARG);

/*  Variables Initialized by main.c  */
IntT quitProgram = 1;
IntT loadLayout = NO;
IntT VidCWid = 0;
IntT VidCDep = 0;
IntT untilWM = 0;

/*  Variables Initialized externally  */
GBL AtrT cHelp[4];
GBL AtrT cAlt[4];
GBL AtrT cMessage[4];
GBL AtrT cMain[4];
GBL IntT SwapDos;
GBL WndT cWindow;
GBL WndT cHeader;
GBL WndT cStatus;
GBL WndT cPlayer;
GBL WndT cCombat;
GBL IntT functions;
GBL char assigned_Function[40][40];
GBL IntT function_Keys[40];
GBL IntT keyMode, keyStatus;

IntT population_Density = 1;
IntT self_Roll = 0;
IntT move_Rate = 12;

TidT CDC _TimCtrl = { 5629, 6, 10, 6, 0, 0, 0, NULL };

VOID main(IntT argc, ChrP argv[])
{
    IntT j, k, logo = TRUE, loadGam = FALSE, loadOut = FALSE, loadMon = FALSE;

    if (argc > 1)
        if (strncmp(argv[1], "?", 1) == 0) {
            puts("                 TCDM v6.0à - The Computerized Dungeon Master");
				puts("                    Copyright 1979 to 1997 by Carl Schelin");
            puts("                             All Rights Reserved\n");
            puts("Command Line Options:\n");
            puts("  /n            - Loads TCDM without the Logo screen appearing");
            puts("  /c:<filename> - Loads the Character file, <filename>.Cha      Not Implemented");
            puts("  /f:<filename> - Loads the Text Font file, <filename>.Fon");
            puts("  /l:<filename> - Loads the Game file, <filename>.Gam");
            puts("  /L:<filename> - Loads the Layout file, <filename>.Out");
            puts("  /m:<filename> - Loads the Monster file, <filename>.Mon");
            puts("  ?             - Prints this screen");
            exit(0);
        }
    puts("TCDM v6.0à - Copyright 1979-1997 by Carl Schelin, All rights reserved.");
    puts("Loading TCXL Windowing system...");
    TcxlInit();
    MouPush(MOU_CURS);
/*    GetMode();*/
    VidCWid = VidWid / 2;
    VidCDep = VidDep / 2;
    charsOnScreen = VidDep - 3;
	 if (charsOnScreen > CHARACTERS)
        charsOnScreen = CHARACTERS;
    totalChars = charsOnScreen * 2;
    if (totalChars > CHARACTERS)
        totalChars = CHARACTERS;
    randomize();
    for (j = 0; j < 100; j++)
        for (k = 0; k < 4; k++) 
            layoutLinks[j][k] = -1;
    for (j = 0; j < VOIDDATA; j++) {
        Init_Char(j);
        Init_Mons(j);
    }
    Config_TCDM();
    HlpDef("Tcdm.Hlp", Key_F1, cHelp[TCDM_WINDOW], cHelp[TCDM_WINDOW], cHelp[TCDM_WINDOW], cHelp[TCDM_DESELECT], cHelp[TCDM_BARINPUT], BOX_SPA|BOX_EXP, AddShadow);
    if (HlpWind(VidCDep - 10, VidCWid - 30, VidCDep + 10, VidCWid + 30, BOX_SPA) == ERR_ARG) {
        printf("HlpWind Error: TcxlErr returned %d", TcxlErr);
        exit(1);
    }
    if (argc > 1)
        for (j = 1; j < argc; j++) {
            if (strncmp(argv[j], "/n", 2) == 0 || strncmp(argv[j], "-n", 2) == 0)
                logo = FALSE;
            if (strncmp(argv[j], "/l:", 3) == 0 || strncmp(argv[j], "-l:", 3) == 0) {
                strcpy(commandFile, argv[j] + 3);
                loadGam = TRUE;
            }
            if (strncmp(argv[j], "/L:", 3) == 0 || strncmp(argv[j], "-L:", 3) == 0) {
                strcpy(layoutFile, argv[j] + 3);
					 loadOut = TRUE;
            }
            if (strncmp(argv[j], "/m:", 3) == 0 || strncmp(argv[j], "-m:", 3) == 0) {
                strcpy(monsterFile, argv[j] + 3);
                loadMon = TRUE;
            }
            if (strncmp(argv[j], "/f:", 3) == 0 || strncmp(argv[j], "-f:", 3) == 0) {
                strcpy(fontFile, argv[j] + 3);
                strcat(fontFile, ".Fon");
                BoxRV(BoxPtr(BOX_DBL)) = 0xB6;    /* Right Vertical    */
                BoxBH(BoxPtr(BOX_DBL)) = 0xD0;    /* Bottom Horizontal */
            }
        }
    SelectFont(fontFile);
    Screen_Setup(logo);
    if (loadGam == TRUE) {
        Load_Characters(TRUE);
        Time_Keeping(MAINTAIN);
    }
    if (loadMon == TRUE) {
        Load_Monsters(TRUE);
    }
    if (loadOut == TRUE) {
        Load_Layout(TRUE);
    }
    for (;;) {
        MSupdat(TRUE, 0, 0, VidDep - 1, VidWid - 1);
        HlpSet(HLP_MAIN);
        Select_Input();
		  if (quitProgram != 1) break;
    }
/*    RestoreDefault();*/
    WVclose(cWindow);
    WVclose(cHeader);
    WVclose(cStatus);
    WVclose(cPlayer);
    WVclose(cCombat);
    VcurHid(1);
}

VOID Select_Input(NOARG)
{
    KeyT c, d;
    IntT j, tempCharNum, tempMonNum;
    ChrT temp[40];

    for (;;) {
        if (kbhit()) {
            if (untilWM-- <= 0) {
                untilWM = 0;
                c = KeyGetc();
            }
            else {
                c = Key_Ent;
            }
            break;
        }
        MSstat();
		  if (MouLbtn == 0x0001) {
            c = Key_M_ClkL;
            if (combatMode == TRUE)
                if (combatStatus == MONSTER)
                    if (MouCol > 40 && MouCol < 59 && MouRow > 1 && MouRow < VidDep - 1) {
                        NewSheet = RePrint = FALSE;
                        Compose_Char_Data(MONNUM);
                        Print_Char(NORMAL, MONNUM);
                        if (MonSta(MONNUM) != MonSta(MouRow - 2 + monNumEx)) 
                            NewSheet = TRUE;
                        monNum = MouRow - 2;
                        RePrint = TRUE;
                        Compose_Char_Data(MONNUM);
                        MSupdat(FALSE, 0, 0, VidDep - 1, VidWid - 1);
                        Print_Char(REVERSE, MONNUM);
                        MSupdat(TRUE, 0, 0, VidDep - 1, VidWid - 1);
                        d = 1; 
                    }
                    else
                        d = 0;
                else
                    if (MouCol > 61 && MouCol < 80 && MouRow > 1 && MouRow < VidDep - 1) {
                        NewSheet = RePrint = FALSE;
                        Compose_Char_Data(CHARNUM);
                        Print_Char(NORMAL, CHARNUM);
                        if (ChrSta(CHARNUM) != ChrSta(MouRow - 2 + charNumEx))
                            NewSheet = TRUE;
                        charNum = MouRow - 2;
                        RePrint = TRUE;
								Compose_Char_Data(CHARNUM);
                        MSupdat(FALSE, 0, 0, VidDep - 1, VidWid - 1);
                        Print_Char(REVERSE, CHARNUM);
                        MSupdat(TRUE, 0, 0, VidDep - 1, VidWid - 1);
                        d = 1;
                    }
                    else
                        d = 0;
            while (MouLbtn == 0x0001) {
                MSstat();
                if (combatMode == TRUE) {
                    if (combatStatus == MONSTER) {
                        if (MouRbtn == 0x0001) {
                            d = 0;
                            MonAtk(MONNUM) = -1;
                            MSupdat(FALSE, 0, 0, VidDep - 1, VidWid - 1);
                            Compose_Char_Data(MONNUM);
                            Print_Char(REVERSE, MONNUM);
                            c = Key_BS;
                        }
                        if (d == 1) {
                            if (MouCol > 61 && MouCol < 80 && MouRow > 1 && MouRow < VidDep - 1) {
                                MonAtk(MONNUM) = MouRow - 2;
                                Compose_Char_Data(MONNUM);
                                MSupdat(FALSE, 0, 0, VidDep - 1, VidWid - 1);
                                Print_Char(REVERSE, MONNUM);
                                c = Key_BS;
                            }
                            else {
										  MSupdat(TRUE, 0, 0, VidDep - 1, VidWid - 1);
                            }
                        }
                    }
                    else {
                        if (MouRbtn == 0x0001) {
                            d = 0;
                            ChrAtk(CHARNUM) = -1;
                            Compose_Char_Data(CHARNUM);
                            MSupdat(FALSE, 0, 0, VidDep - 1, VidWid - 1);
                            Print_Char(REVERSE, CHARNUM);
                            c = Key_BS;
                        }
                        if (d == 1) {
                            if (MouCol > 40 && MouCol < 59 && MouRow > 1 && MouRow < VidDep - 1) {
                                ChrAtk(CHARNUM) = MouRow - 2;
                                Compose_Char_Data(CHARNUM);
                                MSupdat(FALSE, 0, 0, VidDep - 1, VidWid - 1);
                                Print_Char(REVERSE, CHARNUM);
                                c = Key_BS;
                            }
                            else {
                                MSupdat(TRUE, 0, 0, VidDep - 1, VidWid - 1);
                            }
                        }
                    }
                }
            }
            break;
		  }
        if (MouRbtn == 0x0001) {
            c = Key_M_ClkR;
            while (MouRbtn == 0x0001)
                MSstat();
            break;
        }
    }

    if (c == Key_M_ClkL) c = CheckMouse(c);
    if (c == Key_M_ClkR) c = CheckMouse(c);

    for (j = 0; j < functions; j++) {
        if (c == (unsigned)function_Keys[j]) {
            if (strnicmp(assigned_Function[j], "&&&", 3) == 0) {
                system(assigned_Function[j] + 3);
                Screen_Setup(0);
            }
            else {
                sprintf(temp, "%s", assigned_Function[j]);
                system(temp);
            }
            c = 32;
            MouShow();
        }
    }

    MSupdat(FALSE, 0, 0, VidDep - 1, VidWid - 1);
    switch (c) {
		  case Key_BS    :   /*  NI: Decrement time  */
            break;

        case Key_C_BS  :   /*  NI: Decrement x rounds  */
            break;

        case Key_Ent   :   /*  Increment time  */
            IncrementTime();
            break;

        case Key_C_Ent :   /*  Increment x rounds  */
            if (combatMode == TRUE)
                untilWM = WMDelay * 10;
            else
                untilWM = WMDelay;
            KquePut(Key_BS);
            break;

        case Key_PlsG  :   /*  Add one point to monster/character  */
            AddHitPoints();
            break;

        case Key_MinG  :   /*  Subtract one point from character/monster  */
            SubtractHitPoints();
            break;

        case Key_Min   :   /*  Subtract from armor  */
            SubtractArmorPoints();
            break;

        case Key_S_Min :   /*  Subtract from shield  */
            SubtractShieldPoints();
            break;

        case Key_A_Min :   /*  Subtract from helm  */
            SubtractHelmetPoints();
            break;

        case Key_Equ   :   /*  Add to armor  */
            AddArmorPoints();
            break;

        case Key_S_Equ :   /*  Add to shield  */
            AddShieldPoints();
            break;

        case Key_A_Equ :   /*  Add to helm  */
            AddHelmetPoints();
            break;

		  case Key_S_Home:   /*  Move to first character/monster on page  */
		  case Key_Home  :
				MoveHome();
				break;

		  case Key_S_End :   /*  Move to last character/monster on page  */
		  case Key_End   :
				MoveEnd();
				break;

		  case Key_S_Dwn :   /*  Move down one character/monster  */
		  case Key_Dwn   :
				MoveDown();
				break;

		  case Key_S_Up  :   /*  Move up one character/monster  */
		  case Key_Up    :
				MoveUp();
				break;

		  case Key_S_PgUp:   /*  If on second page, change to first page  */
		  case Key_PgUp  :
				MovePgUp();
				break;

		  case Key_S_PgDn:   /*  If on first page, change to second page  */
		  case Key_PgDn  :
				MovePgDn();
				break;

		  case Key_S_Rgt :   /*  If monster, move to character. If character,  */
		  case Key_Rgt   :   /*  move sheet right. If right, edit character.   */
				MoveRight();
				break;

		  case Key_S_Lft :   /*  If edit, esc. If esc, move sheet to left, if  */
		  case Key_Lft   :   /*  left, monster mode.                           */
				MoveLeft();
				break;

		  case Key_A_1   :   /*  Roll Random 2  */
				sprintf(Message, " Rolled a %d on a die 2", Roll_Dice(2, 1));
				MessageWindow(Message);
				break;

		  case Key_A_2   :   /*  Roll Random 3  */
				sprintf(Message, " Rolled a %d on a die 3", Roll_Dice(3, 1));
				MessageWindow(Message);
				break;

        case Key_A_3   :   /*  Roll Random 4  */
            sprintf(Message, " Rolled a %d on a die 4", Roll_Dice(4, 1));
            MessageWindow(Message);
            break;

        case Key_A_4   :   /*  Roll Random 6  */
            sprintf(Message, " Rolled a %d on a die 6", Roll_Dice(6, 1));
            MessageWindow(Message);
            break;

        case Key_A_5   :   /*  Roll Random 8  */
            sprintf(Message, " Rolled a %d on a die 8", Roll_Dice(8, 1));
            MessageWindow(Message);
            break;

        case Key_A_6   :   /*  Roll Random 10  */
            sprintf(Message, " Rolled a %d on a die 10", Roll_Dice(10, 1));
            MessageWindow(Message);
            break;

        case Key_A_7   :   /*  Roll Random 12  */
            sprintf(Message, " Rolled a %d on a die 12", Roll_Dice(12, 1));
            MessageWindow(Message);
            break;

        case Key_A_8   :   /*  Roll Random 20  */
            sprintf(Message, " Rolled a %d on a die 20", Roll_Dice(20, 1));
            MessageWindow(Message);
            break;

        case Key_A_9   :   /*  Roll Random 100  */
            sprintf(Message, " Rolled a %d%d on a die 100", Roll_Dice(10, 1) - 1, Roll_Dice(10, 1) - 1);
            MessageWindow(Message);
            break;

        case Key_A_0   :   /*  Roll three die 6  */
            sprintf(Message, " Rolled a %d with 3d6", Roll_Dice(6, 3));
            MessageWindow(Message);
            break;

        case Key_F1:
        case Key_S_Sls:   /*  If ?, display help screen  */
            GetHelp();
            break;

        case Key_C     :   /*  Redraw screen  */
            WVclose(cWindow);
            WVclose(cHeader);
            WVclose(cStatus);
            WVclose(cPlayer);
            WVclose(cCombat);
            NewSheet = RePrint = TRUE;
            Screen_Setup(0);
            break;

        case Key_D     :   /*  Load the current Command processor.  */
            WVclose(cWindow);
            WVclose(cHeader);
            WVclose(cStatus);
            WVclose(cPlayer);
            WVclose(cCombat);
            puts("\nType \"Exit\" to return to The Computerized Dungeon Master\n");
            VcurHid(1);
            system(getenv("COMSPEC"));
            VcurHid(0);
            Config_TCDM();
            charsOnScreen = VidDep - 3;
            if (charsOnScreen >= totalChars)
                charsOnScreen = totalChars - 1;
            Screen_Setup(0);
            break;

        case Key_L     :   /*  Load characters/monsters  */
            if (combatMode == TRUE && combatStatus == MONSTER)
                Load_Monsters(FALSE);
            else
                Load_Characters(FALSE);
            Time_Keeping(MAINTAIN);
            break;

        case Key_S_L   :   /*  Load a layout into memory  */
            Load_Layout(FALSE);
            break;

        case Key_S     :   /*  Save characters (monsters NI)  */
            if (combatMode == TRUE && combatStatus == MONSTER)
                MessageWindow(" Save the Monsters!");
            else
                Save_Characters();
            break;

        case Key_S_S   :   /*  Save a layout file  */
            Save_Layout();
            break;

        case Key_Q     :   /*  Exit TCDM  */
        case Key_Esc   :
            quitProgram = Verify_Quit();
            break;

        case Key_W     :   /*  Generate Weather Picture */
        case Key_S_W   :
            GenerateWeather();
            break;

        case Key_S_C   :   /*  If monster, display character sheet  */
            /*  if combat and monster                                      */
            /*    if already character mode, don't do anything             */
            /*    else                                                     */
            /*      clear, change to character and print sheet and data    */
            if (combatMode == TRUE)
                if (combatStatus == MONSTER) {
                    if (mData[MONNUM].DisplayMode == MONSTER) {
                        mData[MONNUM].DisplayMode = CHARACTER;
                        WclrWin(cAlt[TCDM_WINDOW]);
                        NewSheet = RePrint = TRUE;
                        Print_Char(NORMAL, MONNUM);
                    }
                }
                else {
                    if (cData[CHARNUM].DisplayMode == MONSTER) {
                        cData[CHARNUM].DisplayMode = CHARACTER;
                        WclrWin(cAlt[TCDM_WINDOW]);
                        NewSheet = RePrint = TRUE;
                        Print_Char(NORMAL, CHARNUM);
                    }
                }
            break;

        case Key_C_G   : 
            calcAge();
            DscHgt(CHARNUM) = heightChart(ChrRac(CHARNUM), DscSex(CHARNUM), 
                StaStr(CHARNUM), StaStp(CHARNUM));
            DscWgt(CHARNUM) = weightChart(ChrRac(CHARNUM), DscSex(CHARNUM), 
                StaStr(CHARNUM), StaStp(CHARNUM), DscHgt(CHARNUM));
            DscEye(CHARNUM) = colorEyes(ChrRac(CHARNUM));
            DscSkn(CHARNUM) = colorSkin(ChrRac(CHARNUM));
            DscHrc(CHARNUM) = hairColor(ChrRac(CHARNUM));
            DscHrl(CHARNUM) = hairLength(ChrRac(CHARNUM), DscSex(CHARNUM));
            DscBdc(CHARNUM) = hairColor(ChrRac(CHARNUM));
            DscBdl(CHARNUM) = beardLength(ChrRac(CHARNUM));
            calcFacialFeatures();
            break;

        case Key_A_M   : 
            getFilename();
            break;

        case Key_C_V   :
            Display_Desc();
            break;

        case Key_C_M   :   /*  If character, display monster sheet  */
            /*  if combat and monster                                      */
            /*    if already monster mode, don't do anything               */
            /*    else                                                     */
            /*      clear, change to monster and print sheet and data      */
            if (combatMode == TRUE)
                if (combatStatus == MONSTER) {
                    if (mData[MONNUM].DisplayMode == CHARACTER) {
                        mData[MONNUM].DisplayMode = MONSTER;
                        WclrWin(cAlt[TCDM_WINDOW]);
                        NewSheet = RePrint = TRUE;
                        Print_Char(NORMAL, MONNUM);
                    }
                }
                else {
                    if (cData[CHARNUM].DisplayMode == CHARACTER) {
                        cData[CHARNUM].DisplayMode = MONSTER;
                        WclrWin(cAlt[TCDM_WINDOW]);
                        NewSheet = RePrint = TRUE;
                        Print_Char(NORMAL, CHARNUM);
                    }
                }
            break;

        case Key_A_Z   :   /*  Edit game setting, dungeon or outdoors  */
            Game_Setting();
            break;

        /*  hit ctrl-rgt to attack a character:                    */
        /*    leave monster highlighted                            */
        /*    draw arrow each time                                 */
        /*    use normal highlight for each character until picked */
        /*      (by enter)                                         */

        case Key_C_Rgt : 
            if (combatMode == TRUE) {
                if (combatStatus == MONSTER) {
                    if (MonAtk(MONNUM) >= 0) { /* cancel attack on char */
                        MonAtk(MONNUM) = -1;
                        Compose_Char_Data(MONNUM);
                        Print_Char(REVERSE, MONNUM);
                    }
                    else {                     /* choose character to attack */
                        if (charNumEx > 0) {
                            if (monNumEx > 0) {
                                tempCharNum = MONNUM;
                            }
                            else {
                                tempCharNum = MONNUM - charNumEx;
                            }
                        }
                        else {
                            if (monNumEx > 0) {
                                tempCharNum = MONNUM - charNumEx;
                            }
                            else {
                                tempCharNum = MONNUM;
                            }
                        }
                        MonAtk(MONNUM) = tempCharNum;
                        Compose_Char_Data(MONNUM);
                        Print_Char(REVERSE, MONNUM);
                        for (;;) {
                            d = KeyGetc();
                            switch (d) {
                                case Key_End :
                                case Key_S_End :
                                    tempCharNum = charsOnScreen - 1 + monNumEx;
                                    break;

                                case Key_Home :
                                case Key_S_Home :
                                    tempCharNum = monNumEx;
                                    break;

                                case Key_Up :
                                case Key_S_Up :
                                    tempCharNum--;
                                    if (tempCharNum < (0 + monNumEx))
                                        tempCharNum = charsOnScreen - 1 + monNumEx;
                                    break;

                                case Key_Dwn :
                                case Key_S_Dwn :
                                    tempCharNum++;
                                    if (tempCharNum >= (charsOnScreen + monNumEx))
                                        tempCharNum = monNumEx;
                                    break;
                            }
                            MonAtk(MONNUM) = tempCharNum;
                            if (d == Key_Ent)
                                MonAtk(MONNUM) = tempCharNum;
                            if (d == Key_Esc)
                                MonAtk(MONNUM) = -1;
                            Compose_Char_Data(MONNUM);
                            Print_Char(REVERSE, MONNUM);
                            if (d == Key_Ent || d == Key_Esc)
                                break;
                        }
                    }
                }
            }
            break;

        /*  hit ctrl-lft to attack a monster:                      */
        /*    leave character highlighted                          */
        /*    draw arrow each time                                 */
        /*    use normal highlight for monsters                    */
        /*      include monster data                               */

        case Key_C_Lft : 
            if (combatMode == TRUE) {
                if (combatStatus == CHARACTER) {
                    if (ChrAtk(CHARNUM) >= 0) {
                        ChrAtk(CHARNUM) = -1;
                        Compose_Char_Data(CHARNUM);
                        Print_Char(REVERSE, CHARNUM);
                    }
                    else {
                        /* if monnumex > 0  (second page of monsters)
                             if charnumex > 0 (second page of chars)
                               tempmonnum = charnum
                             if charnumex == 0 (first page of chars)
                               tempmonnum = charnum - monnumex
                           if (monnumex == 0 (first page of monsters)
                             if (charnumex > 0) (second page of chars)
                               tempmonnum = charnum - monnumex
                             if (charnumex == 0) (first page of chars)
                               tempmonnum = charnum
                        */
                        if (monNumEx > 0) {
                            if (charNumEx > 0) {
                                tempMonNum = CHARNUM;
                            }
                            else {
                                tempMonNum = CHARNUM - monNumEx;
                            }
                        }
                        else {
                            if (charNumEx > 0) {
                                tempMonNum = CHARNUM - monNumEx;
                            }
                            else {
                                tempMonNum = CHARNUM;
                            }
                        }
                        ChrAtk(CHARNUM) = tempMonNum;
                        Compose_Char_Data(CHARNUM);
                        Print_Char(REVERSE, CHARNUM);
                        for (;;) {
                            d = KeyGetc();
                            switch (d) {
                                case Key_End :
                                case Key_S_End :
                                    tempMonNum = charsOnScreen - 1 + monNumEx;
                                    break;

                                case Key_Home :
                                case Key_S_Home :
                                    tempMonNum = monNumEx;
                                    break;

                                case Key_Up :
                                case Key_S_Up :
                                    tempMonNum--;
                                    if (tempMonNum < (0 + monNumEx))
                                        tempMonNum = charsOnScreen - 1 + monNumEx;
                                    break;

                                case Key_Dwn :
                                case Key_S_Dwn :
                                    tempMonNum++;
                                    if (tempMonNum >= (charsOnScreen + monNumEx))
                                        tempMonNum = monNumEx;
                                    break;
                            }
                            ChrAtk(CHARNUM) = tempMonNum;
                            if (d == Key_Ent)
                                ChrAtk(CHARNUM) = tempMonNum;
                            if (d == Key_Esc)
                                ChrAtk(CHARNUM) = -1;
                            Compose_Char_Data(CHARNUM);
                            Print_Char(REVERSE, CHARNUM);
                            if (d == Key_Ent || d == Key_Esc)
                                break;
                        }
                    }
                }
            }
            break;

        case Key_C_D   :   /*  Set Game Date  */
            Set_Date();
            break;

        case Key_C_L   :   /*  Edit layout or redisplay character  */
            if (loadLayout == YES) {
                loadLayout = NO;
                if (ChrSta(CHARNUM) != BLANK)
                    NewSheet = TRUE;
                Print_Char(REVERSE, CHARNUM);
            }
            else {
                loadLayout = YES;
                Edit_Layout(EDITING);
            }
            break;

        case Key_A_C   :   /*  Clear Experience Point Counter  */
            if (combatMode == TRUE) {
                if (combatStatus == CHARACTER) {
                    if (cData[CHARNUM].Experience > 0) {
                        cData[CHARNUM].Experience = 0;
                        Wactiv(cWindow);
                        Update_Data(EXPERIENCE);
                    }
                }
            }
            else {
                if (cData[CHARNUM].Experience > 0) {
                    cData[CHARNUM].Experience = 0;
                    Wactiv(cWindow);
                    Update_Data(EXPERIENCE);
                }
            }
            break;

        case Key_C_T   :   /*  Set Game Time  */
            Set_Time();
            break;

        case Key_A_I   :   /*  Restore all dead characters/monsters  */
            Insert_All();
            break;

        case Key_A_D   :   /*  Kill all alive characters/monsters  */
            Delete_All();
            break;

        case Key_A_V   :   /*  Clear character/monster from memory  */
            if (combatMode == TRUE) {
                if (MonSta(MONNUM) == ALIVE || MonSta(MONNUM) == DEAD) {
                    Void_Character();
                }
            }
            else {
                if (ChrSta(CHARNUM) == ALIVE || ChrSta(CHARNUM) == DEAD) {
                    Void_Character();
                }
            }
            break;

        case Key_S_F   :   /*  Load a font  */
            SelectFont("VGothic.Fon");
            break;

        case Key_S_D   :   /*  Reset font to standard mode  */
            RestoreDefault();
            break;

        case Key_F     :   /*  Turn on/off Fawning mode  */
            if (wStatus == 1) {
                MessageWindow(" I pray that I may serve you again, Master!");
                wStatus = 0;
            }
            else {
                MessageWindow(" A pleasure to be able to serve you again, Master!");
                wStatus = 1;
            }
            break;

        default     :
            if (combatMode == TRUE) {
                if (combatStatus == MONSTER) {
                    if (MonSta(MONNUM) == ALIVE) {
                        switch (c) {
                            case Key_Del :   /*  Delete character/monster  */
                                Delete_Character();
                                break;
                        }
                    }
                    else {
                        switch (c) {
                            case Key_Ins :   /*  Restore character/monster  */
                                Insert_Character();
                                break;
                        }
                    }
                }
            }
            else {
                if (ChrSta(CHARNUM) == ALIVE) {
                    switch (c) {
                        case Key_A_E :   /*  Edit current character  */
                            Edit_Character(EDITING);
                            cData[CHARNUM].Changed = YES;
                            break;

                        case Key_A_L :   /*  Edit character light source  */
                            Activate_Light();
                            cData[CHARNUM].Changed = YES;
                            break;

                        case Key_A_P :   /*  Display character PSIonics  */
                            if (cData[CHARNUM].Psionic == 'Y')
                                Psionic_Data();
                            for (j = 0; j < 3; j++) {
                                if (ClsRch(CHARNUM, j) == PRIEST)
                                    Display_Cleric_Skills();
                                if (ClsRch(CHARNUM, j) == WARRIOR && ClsCls(CHARNUM, j) == 2)
                                    Display_Cleric_Skills();
                            }
                            break;

                        case Key_A_R :   /*  Display character racial info  */
                            HlpSet(ChrRac(CHARNUM) + HLP_RACE + 1);
                            HlpGet();
                            HlpSet(HLP_MAIN);
                            break;

                        case Key_A_S :   /*  Edit Saving Throws  */
                            Adjust_Saving_Throws();
                            cData[CHARNUM].Changed = YES;
                            NewSheet = TRUE;
                            Print_Char(REVERSE, CHARNUM);
                            break;

                        case Key_A_T :   /*  Display Thieving skills */
                            for (j = 0; j < 3; j++)
                                if (ClsRch(CHARNUM, j) == ROGUE && ClsCls(CHARNUM, j) == 0)
                                    Display_Thief_Skills();
                            break;

                        case Key_Del :   /*  Delete character  */
                            Delete_Character();
                            break;

                    }
                }
                else {
                    switch (c) {
                        case Key_Ins :   /*  Restore character  */
                            Insert_Character();
                            break;

                        case Key_A_E :   /*  Edit character  */
                            if (ChrSta(CHARNUM) == DEAD)
                                Edit_Character(EDITING);
                            else
                                Edit_Character(CREATION);
                            break;

                        case Key_A_R :   /*  Display Racial Information  */
                            HlpSet(HLP_RACE);
                            HlpGet();
                            HlpSet(HLP_MAIN);
                            break;
                    }
                }
            }
        break;
    }
    VcurHid(0);
}

VOID CTYP GetHelp(NOARG)
{
    HlpSet(HLP_MAIN);
    HlpGet();
}

VOID CTYP IncrementTime(NOARG)
{
    Time_Keeping(INCREMENT);
    Wactiv(cWindow);
    Update_Data(LIGHT);
    if (Wandering_Monster == 1)
        untilWM = 0;
}

VOID CTYP MoveRight(NOARG)
{
    NewSheet = RePrint = FALSE;
    if (combatMode == TRUE) {
        if (combatStatus == CHARACTER) {
            Print_Char(NORMAL, CHARNUM); /* change to regular colors */
            Wactiv(cWindow);
            Wslide(1, 40);                 /* move window */
            combatMode = FALSE;
            combatStatus = CHARACTER;
            Print_Char(REVERSE, CHARNUM);   /* reprint character */
        }
        else {
            Print_Char(NORMAL, MONNUM);   /* clear mons info */
            combatStatus = CHARACTER;
            Wactiv(cWindow);             /* clean off screen */
            WclrWin(cAlt[TCDM_WINDOW]);
            NewSheet = RePrint = TRUE;
            Print_Char(REVERSE, CHARNUM);  /* reprint character */
        }
    }
    else
        if (loadLayout == YES)
            Edit_Layout(EDITING);
        else
            if (ChrSta(CHARNUM) != BLANK)
                Edit_Character(EDITING);
            else
                Edit_Character(CREATION);
}

VOID CTYP MoveLeft(NOARG)
{
    NewSheet = RePrint = FALSE;
    if (combatMode == TRUE) {
        if (combatStatus == CHARACTER) {
            Print_Char(NORMAL, CHARNUM);   /* clear character info */
            combatStatus = MONSTER;
            Wactiv(cWindow);               /* clean off screen */
            WclrWin(cAlt[TCDM_WINDOW]);
            NewSheet = RePrint = TRUE;
            Print_Char(REVERSE, MONNUM);     /* reprint monster */
		  }
		  else
				Edit_Monster();
	 }
	 else {
		  Print_Char(NORMAL, CHARNUM);      /* turn off bar */
		  Wactiv(cWindow);
		  Wslide(1, 0);                      /* move it */
        combatMode = TRUE;
        combatStatus = CHARACTER;
        Print_Char(REVERSE, CHARNUM);     /* new character info */
    }
}

VOID CTYP SubtractArmorPoints(NOARG)
{
    if (combatMode == TRUE) {
        if (combatStatus == CHARACTER) {
            if (cData[CHARNUM].APoints > cData[CHARNUM].APtDown) {
                cData[CHARNUM].APtDown++;
                Adjust_Armor_Class();
                if (cData[CHARNUM].AttackWho == -1) {
                    Wactiv(cWindow);
                    Update_Data(ARMORCLASS);
                    Update_Data(ARMOR);
                }
                Compose_Char_Data(CHARNUM);
                Print_Char(REVERSE, CHARNUM);
            }
        }
    }
    else {
        if (cData[CHARNUM].APoints > cData[CHARNUM].APtDown) {
            cData[CHARNUM].APtDown++;
            Adjust_Armor_Class();
            Wactiv(cWindow);
            Update_Data(ARMORCLASS);
            Update_Data(ARMOR);
        }
    }
}

VOID CTYP SubtractShieldPoints(NOARG)
{
    if (combatMode == TRUE) {
        if (combatStatus == CHARACTER) {
            if (cData[CHARNUM].SPoints > cData[CHARNUM].SPtDown) {
                cData[CHARNUM].SPtDown++;
                Adjust_Armor_Class();
                if (cData[CHARNUM].AttackWho == -1) {
                    Wactiv(cWindow);
                    Update_Data(ARMORCLASS);
                    Update_Data(SHIELD);
                }
                Compose_Char_Data(CHARNUM);
                Print_Char(REVERSE, CHARNUM);
            }
        }
    }
    else {
        if (cData[CHARNUM].SPoints > cData[CHARNUM].SPtDown) {
            cData[CHARNUM].SPtDown++;
            Adjust_Armor_Class();
            Wactiv(cWindow);
            Update_Data(ARMORCLASS);
            Update_Data(SHIELD);
        }
    }
}

VOID CTYP SubtractHelmetPoints(NOARG)
{
    if (combatMode == TRUE) {
        if (combatStatus == CHARACTER) {
            if (cData[CHARNUM].HPoints > cData[CHARNUM].HPtDown) {
                cData[CHARNUM].HPtDown++;
                Adjust_Armor_Class();
                if (cData[CHARNUM].AttackWho == -1) {
                    Wactiv(cWindow);
                    Update_Data(ARMORCLASS);
                    Update_Data(HELM);
                }
                Compose_Char_Data(CHARNUM);
                Print_Char(REVERSE, CHARNUM);
            }
        }
    }
    else {
        if (cData[CHARNUM].HPoints > cData[CHARNUM].HPtDown) {
            cData[CHARNUM].HPtDown++;
            Adjust_Armor_Class();
            Wactiv(cWindow);
            Update_Data(ARMORCLASS);
            Update_Data(HELM);
        }
    }
}

VOID CTYP AddArmorPoints(NOARG)
{
    if (combatMode == TRUE) {
        if (combatStatus == CHARACTER) {
            if (cData[CHARNUM].APtDown > 0) {
                cData[CHARNUM].APtDown--;
                Adjust_Armor_Class();
                if (cData[CHARNUM].AttackWho == -1) {
                    Wactiv(cWindow);
                    Update_Data(ARMORCLASS);
                    Update_Data(ARMOR);
                }
                Compose_Char_Data(CHARNUM);
                Print_Char(REVERSE, CHARNUM);
            }
        }
    }
    else {
        if (cData[CHARNUM].APtDown > 0) {
            cData[CHARNUM].APtDown--;
            Adjust_Armor_Class();
            Wactiv(cWindow);
            Update_Data(ARMORCLASS);
            Update_Data(ARMOR);
        }
    }
}

VOID CTYP AddShieldPoints(NOARG)
{
    if (combatMode == TRUE) {
        if (combatStatus == CHARACTER) {
            if (cData[CHARNUM].SPtDown > 0) {
                cData[CHARNUM].SPtDown--;
                Adjust_Armor_Class();
                if (cData[CHARNUM].AttackWho == -1) {
                    Wactiv(cWindow);
                    Update_Data(ARMORCLASS);
                    Update_Data(SHIELD);
                }
                Compose_Char_Data(CHARNUM);
                Print_Char(REVERSE, CHARNUM);
            }
        }
    }
    else {
        if (cData[CHARNUM].SPtDown > 0) {
            cData[CHARNUM].SPtDown--;
            Adjust_Armor_Class();
            Wactiv(cWindow);
            Update_Data(ARMORCLASS);
            Update_Data(SHIELD);
        }
    }
}

VOID CTYP AddHelmetPoints(NOARG)
{
    if (combatMode == TRUE) {
        if (combatStatus == CHARACTER) {
            if (cData[CHARNUM].HPtDown > 0) {
                cData[CHARNUM].HPtDown--;
                Adjust_Armor_Class();
                if (cData[CHARNUM].AttackWho == -1) {
                    Wactiv(cWindow);
                    Update_Data(ARMORCLASS);
                    Update_Data(HELM);
                }
                Compose_Char_Data(CHARNUM);
                Print_Char(REVERSE, CHARNUM);
            }
        }
    }
    else {
        if (cData[CHARNUM].HPtDown > 0) {
            cData[CHARNUM].HPtDown--;
            Adjust_Armor_Class();
            Wactiv(cWindow);
            Update_Data(ARMORCLASS);
            Update_Data(HELM);
        }
    }
}

