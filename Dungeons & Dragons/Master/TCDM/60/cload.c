/* []---------------------------------------------------------------------[] */
/* |                  CLoad.cpp: Character Load Routines.                  | */
/* |                                                                       | */
/* |              The CLoad.cpp source code and concepts are               | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __CHARLOAD__

#include <stdio.h>
#include <string.h>
#include <TcxlDef.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID Load_Characters(IntT CommandLoad);
VOID LoadDialog(IntT LoadWho);
ChrP GetString(ChrP playerPath, ChrP label, ChrP keyword, ChrP data, IntT iteration);
VOID CTYP LoadClass(NOARG);
DwdT ResolveString(ChrP string, IntT check);

GBL VOID Verify_Character_Data(IntT charNum);

#define CHARFILELEN 296

GBL ChrP groups[];
GBL ChrP classWarrior[];
GBL ChrP classWizard[];
GBL ChrP classPriest[];
GBL ChrP classRogue[];
GBL ChrP classPsionicist[];
GBL ChrP warriorKits[];
GBL ChrP wizardKits[];
GBL ChrP priestKits[];
GBL ChrP thiefKits[];
GBL ChrP bardKits[];

VOID LoadDialog(IntT LoadWho) 
{
    LoadWho = LoadWho;

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³                                               ³
    ³ Save As: ..\Players\<player>                  ³
    ³                                               ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
}

VOID LoadCharacter(IntT LoadWho)
{
    FILE *charin;
    ChrT string[CHARFILELEN];

    strcpy(Message, savePDir);
    strcat(Message, "\\");
    strcat(Message, ChrFil(LoadWho));
    strcat(Message, ".CHA");
    if ((charin = fopen(Message, "r")) != NULL) {
        if (fgets(string, CHARFILELEN, charin) != NULL) {
            string[strlen(string) - 1] = '\0';
         /*                 nn xx xx 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 999 999 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 9999  x 999 9999 99 99 99 99 99 99 99 99 99 99 99 99 99 99  9 */
         /*                 nn Cn Pn Gr Gr Gr Lv Lv Lv Cl Cl Cl Kt Kt Kt Ra Al At Ap   AD AM St Sp SD SM Ht Hp HD HM AA St %% Dx %% Cn %% In %% Ws %% Ch %% Ps HP Hd A1 A2 A3 A4 A5 A6 LT LL Ex T1 T2 T3 T4 T5 T6 T7 T8 Age  Sx Hgt Wgt  Ey Sk Hc Hl Bc Bl F0 F1 F2 F3 F4 F5 F6 F7 Hn */
            sscanf(string, "%d %s %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d  %d  %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d   %d %c  %d   %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
                &ChrSta(LoadWho),
                ChrPer(LoadWho), 
                ChrChr(LoadWho), 
                &ClsRch(LoadWho, 0),
                &ClsRch(LoadWho, 1),
                &ClsRch(LoadWho, 2),
                &ClsLvl(LoadWho, 0),
                &ClsLvl(LoadWho, 1),
                &ClsLvl(LoadWho, 2),
                &ClsCls(LoadWho, 0),
                &ClsCls(LoadWho, 1),
                &ClsCls(LoadWho, 2),
                &ClsKit(LoadWho, 0),
                &ClsKit(LoadWho, 1),
                &ClsKit(LoadWho, 2),
                &ChrRac(LoadWho), 
                &ChrAli(LoadWho),
                &cData[LoadWho].AType, 
                &cData[LoadWho].APoints, 
                &cData[LoadWho].APtDown,
                &cData[LoadWho].AMagical,
                &cData[LoadWho].SType, 
                &cData[LoadWho].SPoints, 
                &cData[LoadWho].SPtDown,
                &cData[LoadWho].SMagical,
                &cData[LoadWho].HType, 
                &cData[LoadWho].HPoints, 
                &cData[LoadWho].HPtDown,
                &cData[LoadWho].HMagical,
                &cData[LoadWho].ACAdj, 
                &StaStr(LoadWho), 
                &StaStp(LoadWho), 
                &StaDex(LoadWho), 
                &StaDep(LoadWho), 
                &StaCon(LoadWho), 
                &StaCop(LoadWho), 
                &StaInt(LoadWho), 
                &StaInp(LoadWho), 
                &StaWis(LoadWho), 
                &StaWip(LoadWho), 
                &StaCha(LoadWho), 
                &StaChp(LoadWho), 
                &cData[LoadWho].Psionic, 
                &ChrHpt(LoadWho), 
                &ChrHpd(LoadWho), 
                &ChrPoi(LoadWho), 
                &ChrPet(LoadWho), 
                &ChrPar(LoadWho), 
                &ChrBth(LoadWho), 
                &ChrRsw(LoadWho), 
                &ChrSpl(LoadWho), 
                &LitTyp(LoadWho), 
                &LitLft(LoadWho), 
                &cData[LoadWho].Experience,
                &ThfPip(LoadWho),
                &ThfOlk(LoadWho),
                &ThfFrt(LoadWho),
                &ThfMsi(LoadWho),
                &ThfHis(LoadWho),
                &ThfHno(LoadWho),
                &ThfCwa(LoadWho),
                &ThfRla(LoadWho),
                &DscAge(LoadWho),
                &DscSex(LoadWho),
                &DscHgt(LoadWho),
                &DscWgt(LoadWho),
                &DscEye(LoadWho),
                &DscSkn(LoadWho),
                &DscHrc(LoadWho),
                &DscHrl(LoadWho),
                &DscBdc(LoadWho),
                &DscBdl(LoadWho),
                &DscGa0(LoadWho),
                &DscGa1(LoadWho),
                &DscGa2(LoadWho),
                &DscGa3(LoadWho),
                &DscGa4(LoadWho),
                &DscGa5(LoadWho),
                &DscGa6(LoadWho),
                &DscGa7(LoadWho),
                &DscHnd(LoadWho)
                );
        }
    fclose(charin);
    }
    else
          MessageWindow2(" ERROR: Unable to open:\n", Message);
}


// create functions that load a memory block for each.

VOID CTYP LoadClass(NOARG)
{
    ChrT temp[40];

    // open file, go to first label, put data from archtype into tempArchtype
    if (GetString("..\\Players\\Chad23.Ini", "[Class]", "Archtype", temp, 1) != NULL)
        ClsRch(CHARNUM, 0) = (IntT)ResolveString(temp, CL_ARCHTYPE);
    if (GetString("..\\Players\\Chad23.Ini", "[Class]", "Class", temp, 1) != NULL)
        ClsCls(CHARNUM, 0) = (IntT)ResolveString(temp, CL_CLASS);
    if (GetString("..\\Players\\Chad23.Ini", "[Class]", "Kit", temp, 1) != NULL)
        ClsKit(CHARNUM, 0) = (IntT)ResolveString(temp, CL_KIT);
    if (GetString("..\\Players\\Chad23.Ini", "[Class]", "Level", temp, 1) != NULL)
        ClsLvl(CHARNUM, 0) = (IntT)ResolveString(temp, CL_LEVEL);
}

ChrP GetString(ChrP playerPath, ChrP label, ChrP keyword, ChrP data, IntT iteration)
{
    FILE *input;
    ChrT temp[80];

    if ((input = fopen(playerPath, "r")) != NULL) {
        while (!feof(input)) {
            fgets(temp, 80, input);
            if (strcmp(temp, label) == 0)
                if (iteration == 0)
                    while (!feof(input)) {
                        fgets(temp, 80, input);
                        if (strncmp(keyword, temp, strlen(keyword)) == 0)
                            strcpy(data, temp + strlen(keyword) + 1);
                    }
                else
                    iteration--;
        }
        fclose(input);
    }

    return NULL;
}

DwdT ResolveString(ChrP string, IntT check)
{
    DwdT result = 0;
    IntT j = 0;

    switch (check) {
        case CL_ARCHTYPE    :
            while (groups[j] != NULL)
                if (strcmp(string, groups[j++]) == 0)
                    result = (DwdT)j - 1;
            break;

        case CL_CLASS       :
            switch (ClsRch(CHARNUM, 0)) {
                case WARRIOR    :
                    j = (DwdT)0;
                    while (classWarrior[j] != NULL)
                        if (strcmp(string, classWarrior[j++]) == 0)
                            result = (DwdT)j - 1;
                    break;

                case WIZARD     :
                    j = (DwdT)0;
                    while (classWizard[j] != NULL)
                        if (strcmp(string, classWizard[j++]) == 0)
                            result = (DwdT)j - 1;
                    break;

                case PRIEST     :
                    j = (DwdT)0;
                    while (classPriest[j] != NULL)
                        if (strcmp(string, classPriest[j++]) == 0)
                            result = (DwdT)j - 1;
                    break;

                case ROGUE      :
                    j = (DwdT)0;
                    while (classRogue[j] != NULL)
                        if (strcmp(string, classRogue[j++]) == 0)
                            result = (DwdT)j - 1;
                    break;

                case PSIONICIST :
                    j = (DwdT)0;
                    while (classPsionicist[j] != NULL)
                        if (strcmp(string, classPsionicist[j++]) == 0)
                            result = (DwdT)j - 1;
                    break;
            }
            break;

        case CL_KIT         :
            switch (ClsRch(CHARNUM, 0)) {
                case WARRIOR    :
                    j = (DwdT)0;
                    while (warriorKits[j] != NULL)
                        if (strcmp(string, warriorKits[j++]) == 0)
                            result = (DwdT)j - 1;
                    break;

                case WIZARD     :
                    j = (DwdT)0;
                    while (wizardKits[j] != NULL)
                        if (strcmp(string, wizardKits[j++]) == 0)
                            result = (DwdT)j - 1;
                    break;

                case PRIEST     :
                    j = (DwdT)0;
                    while (priestKits[j] != NULL)
                        if (strcmp(string, priestKits[j++]) == 0)
                            result = (DwdT)j - 1;
                    break;

                case ROGUE      :
                    j = (DwdT)0;
                    if (ClsCls(CHARNUM, 0) == 0)   // thief kits
                        while (thiefKits[j] != NULL)
                            if (strcmp(string, thiefKits[j++]) == 0)
                                result = (DwdT)j - 1;
                    if (ClsCls(CHARNUM, 0) == 1)   // bard kits
                        while (bardKits[j] != NULL)
                            if (strcmp(string, bardKits[j++]) == 0)
                                result = (DwdT)j - 1;
                    break;

                case PSIONICIST :
                    result = (DwdT)-1;
                    break;

            }
            break;

        case CL_LEVEL       :
            result = 0;
            break;

        case CL_EXPERIENCE  :
            result = 0;
            break;

        case CL_EXPMODIFIER :
            result = 0;
            break;
    }
    return result;
}

