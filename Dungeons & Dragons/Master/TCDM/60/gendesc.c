#define __DESCRIPTION__

#include <stdio.h>
#include <stdlib.h>
#include <TcxlDef.H>

#pragma hdrstop
#include "..\include\tcdm.h"

#define YOUNG_ADULT  0
#define MATURE       1
#define MIDDLE_AGE   2
#define OLD          3

IntT MaxStats[] = {25, 100, 25, 100, 25, 100, 25, 100, 25, 100, 25, 100};
IntT MinStats[] = { 0,   0,  0,   0,  0,   0,  0,   0,  0,   0,  0,   0};

GBL IntT Roll_Dice(IntT sides, IntT times);

VOID calcAge(NOARG)
{
    IntT j, fighter = -1, mage = -1, cleric = -1;
    IntT thief = -1, multiclass = 0;
    
    for (j = 0; j < 3; j++)
        if (ClsRch(CHARNUM, j) > -1)
            switch (ClsRch(CHARNUM, j)) {
                case WARRIOR : fighter = j; multiclass++; break;
                case WIZARD  : mage    = j; multiclass++; break;
                case PRIEST  : cleric  = j; multiclass++; break;
                case ROGUE   : thief   = j; multiclass++; break;
            }
    DscAge(CHARNUM) = 0;

    switch (ChrRac(CHARNUM)) {
        case DWARF    : 
            if (multiclass > 1)
                if (fighter > -1) 
                    DscAge(CHARNUM) += 40 + (20 * (ClsLvl(CHARNUM, fighter) + 1));
                if (thief > -1) 
                    DscAge(CHARNUM) += 75 + (18 * (ClsLvl(CHARNUM, thief) + 1));
            else {
                if (fighter > -1) 
                    DscAge(CHARNUM) = 40 + (Roll_Dice(4, 5) * (ClsLvl(CHARNUM, fighter) + 1));
                if (thief > -1) 
                    DscAge(CHARNUM) = 75 + (Roll_Dice(6, 3) * (ClsLvl(CHARNUM, thief) + 1));
            }
            if (DscAge(CHARNUM) <  61) 
                modifyAge(YOUNG_ADULT);
            if (DscAge(CHARNUM) >  60 && DscAge(CHARNUM) < 176) 
                modifyAge(MATURE);
            if (DscAge(CHARNUM) > 175 && DscAge(CHARNUM) < 276) 
                modifyAge(MIDDLE_AGE);
            if (DscAge(CHARNUM) > 275) 
                modifyAge(OLD);
            break;

        case ELF : 
            if (multiclass > 1) {
                if (fighter > -1)
                    DscAge(CHARNUM) += 130 + (30 * (ClsLvl(CHARNUM, fighter) + 1));
                if (mage > -1)
                    DscAge(CHARNUM) += 150 + (30 * (ClsLvl(CHARNUM, mage) + 1));
                if (thief > -1)
                    DscAge(CHARNUM) +=  50 + (30 * (ClsLvl(CHARNUM, thief) + 1));
            }
            else {
                if (fighter > -1)
                    DscAge(CHARNUM) += 130 + (Roll_Dice(6, 5) * (ClsLvl(CHARNUM, fighter) + 1));
                if (mage > -1)
                    DscAge(CHARNUM) += 150 + (Roll_Dice(6, 5) * (ClsLvl(CHARNUM, mage) + 1));
                if (thief > -1)
                    DscAge(CHARNUM) +=  50 + (Roll_Dice(6, 5) * (ClsLvl(CHARNUM, thief) + 1));
            }
            if (DscAge(CHARNUM) < 176)
                modifyAge(YOUNG_ADULT);
            if (DscAge(CHARNUM) > 175 && DscAge(CHARNUM) < 551)
                modifyAge(MATURE);
            if (DscAge(CHARNUM) > 550 && DscAge(CHARNUM) < 876)
                modifyAge(MIDDLE_AGE);
            if (DscAge(CHARNUM) > 875)
                modifyAge(OLD);
            break;

        case GNOME :
            if (multiclass > 1) {
                if (fighter > -1)
                    DscAge(CHARNUM) +=  80 + (20 * (ClsLvl(CHARNUM, fighter) + 1));
                if (mage > -1)
                    DscAge(CHARNUM) += 100 + (24 * (ClsLvl(CHARNUM, mage) + 1));
                if (thief > -1)
                    DscAge(CHARNUM) +=  80 + (20 * (ClsLvl(CHARNUM, thief) + 1));
            }
            else {
                if (fighter > -1)
                    DscAge(CHARNUM) +=  80 + (Roll_Dice(4, 5) * (ClsLvl(CHARNUM, fighter) + 1));
                if (mage > -1)
                    DscAge(CHARNUM) += 100 + (Roll_Dice(12, 2) * (ClsLvl(CHARNUM, mage) + 1));
                if (thief > -1)
                    DscAge(CHARNUM) +=  80 + (Roll_Dice(4, 5) * (ClsLvl(CHARNUM, thief) + 1));
            }
            if (DscAge(CHARNUM) < 91)
                modifyAge(YOUNG_ADULT);
            if (DscAge(CHARNUM) > 90 && DscAge(CHARNUM) < 301)
                modifyAge(MATURE);
            if (DscAge(CHARNUM) > 300 && DscAge(CHARNUM) < 451)
                modifyAge(MIDDLE_AGE);
            if (DscAge(CHARNUM) > 450)
                modifyAge(OLD);
            break;

        case HALF_ELF :
            if (multiclass > 1) {
                if (cleric > -1)
                    DscAge(CHARNUM) += 40 + ( 8 * (ClsLvl(CHARNUM, cleric) + 1));
                if (fighter > -1)
                    DscAge(CHARNUM) += 22 + (12 * (ClsLvl(CHARNUM, fighter) + 1));
                if (mage > -1)
                    DscAge(CHARNUM) += 30 + (16 * (ClsLvl(CHARNUM, mage) + 1));
                if (thief > -1)
                    DscAge(CHARNUM) += 22 + (24 * (ClsLvl(CHARNUM, thief) + 1));
            }
            else {
                if (cleric > -1)
                    DscAge(CHARNUM) += 40 + (Roll_Dice(4, 2) * (ClsLvl(CHARNUM, cleric) + 1));
                if (fighter > -1)
                    DscAge(CHARNUM) += 22 + (Roll_Dice(4, 3) * (ClsLvl(CHARNUM, fighter) + 1));
                if (mage > -1)
                    DscAge(CHARNUM) += 30 + (Roll_Dice(8, 2) * (ClsLvl(CHARNUM, mage) + 1));
                if (thief > -1)
                    DscAge(CHARNUM) += 22 + (Roll_Dice(8, 3) * (ClsLvl(CHARNUM, thief) + 1));
            }
            if (DscAge(CHARNUM) < 41)
                modifyAge(YOUNG_ADULT);
            if (DscAge(CHARNUM) > 40 && DscAge(CHARNUM) < 101)
                modifyAge(MATURE);
            if (DscAge(CHARNUM) > 100 && DscAge(CHARNUM) < 176)
                modifyAge(MIDDLE_AGE);
            if (DscAge(CHARNUM) > 175)
                modifyAge(OLD);
            break;

        case HALFLING :
        case STOUT :
        case TALLFELLOW :
            if (multiclass > 1)
                if (fighter > -1)
                    DscAge(CHARNUM) =  8 + (12 * (ClsLvl(CHARNUM, fighter) + 1));
                if (thief > -1)
                    DscAge(CHARNUM) = 36 + ( 8 * (ClsLvl(CHARNUM, thief) + 1));
            else {
                if (fighter > -1)
                    DscAge(CHARNUM) =  8 + (Roll_Dice(4, 3) * (ClsLvl(CHARNUM, fighter) + 1));
                if (thief > -1)
                    DscAge(CHARNUM) = 36 + (Roll_Dice(4, 2) * (ClsLvl(CHARNUM, thief) + 1));
            }
            if (DscAge(CHARNUM) < 34)
                modifyAge(YOUNG_ADULT);
            if (DscAge(CHARNUM) > 33 && DscAge(CHARNUM) < 69)
                modifyAge(MATURE);
            if (DscAge(CHARNUM) > 68 && DscAge(CHARNUM) < 102)
                modifyAge(MIDDLE_AGE);
            if (DscAge(CHARNUM) > 101)
                modifyAge(OLD);
            break;

        case HALF_ORC :
            if (multiclass > 1) {
                if (cleric > -1)
                    DscAge(CHARNUM) += 20 + (4 * (ClsLvl(CHARNUM, cleric) + 1));
                if (fighter > -1)
                    DscAge(CHARNUM) += 13 + (4 * (ClsLvl(CHARNUM, fighter) + 1));
                if (thief > -1)
                    DscAge(CHARNUM) += 20 + (8 * (ClsLvl(CHARNUM, thief) + 1));
            }
            else {
                if (cleric > -1)
                    DscAge(CHARNUM) = 20 + (Roll_Dice(4, 1) * (ClsLvl(CHARNUM, cleric) + 1));
                if (fighter > -1)
                    DscAge(CHARNUM) = 13 + (Roll_Dice(4, 1) * (ClsLvl(CHARNUM, fighter) + 1));
                if (thief > -1)
                    DscAge(CHARNUM) = 20 + (Roll_Dice(4, 2) * (ClsLvl(CHARNUM, thief) + 1));
            }
            if (DscAge(CHARNUM) < 16)
                modifyAge(YOUNG_ADULT);
            if (DscAge(CHARNUM) > 15 && DscAge(CHARNUM) < 31)
                modifyAge(MATURE);
            if (DscAge(CHARNUM) > 30 && DscAge(CHARNUM) < 46)
                modifyAge(MIDDLE_AGE);
            if (DscAge(CHARNUM) > 45)
                modifyAge(OLD);
            break;

        case HUMAN :
            for (j = 0; j < 3; j++) {
                switch (ClsRch(CHARNUM, j)) {
                    case PRIEST :
                        if (ClsCls(CHARNUM, j) == 0 || ClsCls(CHARNUM, j) == 15)
                            DscAge(CHARNUM) = 18 + (Roll_Dice(4, 1) * (ClsLvl(CHARNUM, cleric) + 1));
                        if (ClsKit(CHARNUM, j) == 2) 
                            DscAge(CHARNUM) = 21 + (Roll_Dice(4, 1) * (ClsLvl(CHARNUM, cleric) + 1));
                        break;
    
                    case WARRIOR :
                        if (ClsCls(CHARNUM, j) == 0)
                            DscAge(CHARNUM) = 15 + (Roll_Dice(4, 1) * (ClsLvl(CHARNUM, fighter) + 1));
                        if (ClsCls(CHARNUM, j) == 1)
                            DscAge(CHARNUM) = 20 + (Roll_Dice(4, 1) * (ClsLvl(CHARNUM, fighter) + 1));
                        if (ClsCls(CHARNUM, j) == 2)
                            DscAge(CHARNUM) = 17 + (Roll_Dice(4, 1) * (ClsLvl(CHARNUM, fighter) + 1));
                        break;
    
                    case WIZARD :
                        if (ClsCls(CHARNUM, j) == 0)
                            DscAge(CHARNUM) = 24 + (Roll_Dice(8, 2) * (ClsLvl(CHARNUM, mage) + 1));
                        if (ClsCls(CHARNUM, j) == 5)
                            DscAge(CHARNUM) = 30 + (Roll_Dice(6, 1) * (ClsLvl(CHARNUM, mage) + 1));
                        break;
    
                    case ROGUE :
                        if (ClsCls(CHARNUM, j) == 0)
                            if (ClsKit(CHARNUM, j) == 2)
                                DscAge(CHARNUM) = 20 + (Roll_Dice(4, 1) * (ClsLvl(CHARNUM, thief) + 1));
                            else
                                DscAge(CHARNUM) = 18 + (Roll_Dice(4, 1) * (ClsLvl(CHARNUM, thief) + 1));
                        if (ClsCls(CHARNUM, j) == 1)
                            DscAge(CHARNUM) = 20 + (Roll_Dice(4, 1) * (ClsLvl(CHARNUM, thief) + 1));
                        break;
                }
                if (DscAge(CHARNUM) < 21)
                    modifyAge(YOUNG_ADULT);
                if (DscAge(CHARNUM) > 20 && DscAge(CHARNUM) < 41)
                    modifyAge(MATURE);
                if (DscAge(CHARNUM) > 41 && DscAge(CHARNUM) < 61)
                    modifyAge(MIDDLE_AGE);
                if (DscAge(CHARNUM) > 60)
                    modifyAge(OLD);
            }
            break;
    }
    Maximize();
    Minimize();
}

VOID modifyAge(IntT modifier)
{
    switch (modifier) {
        case YOUNG_ADULT : StaCon(CHARNUM)++;
                           StaWis(CHARNUM)--;
                           break;
        case MATURE      : StaCon(CHARNUM)++;
                           StaStr(CHARNUM)++;
                           if (StaStr(CHARNUM) > 18) {
                               StaStr(CHARNUM) = 18;
                               StaStp(CHARNUM)++;
                           }
                           break;
        case MIDDLE_AGE  : StaInt(CHARNUM)++;
                           StaWis(CHARNUM)++;
                           break;
        case OLD         : StaWis(CHARNUM)+=2;
                           if (StaStp(CHARNUM) > 1)
                               StaStp(CHARNUM)-=2;
                           else 
                               if (StaStp(CHARNUM) > 0) {
                                   StaStp(CHARNUM) = 0;
                                   StaStr(CHARNUM)--;
                               }
                               else
                                   StaStr(CHARNUM)-=2;
                           StaDex(CHARNUM)--;
                           StaCon(CHARNUM)--;
                           break;
    }
}

IntT heightChart(BytT race, ChrT sex, BytT strength, BytT strmod)
{
    BytT maleMods[] = {48, 60, 42, 60, 42, 39, 45, 60, 60};
    BytT femaleMods[] = {46, 57, 40, 56, 40, 37, 43, 57, 55};
    BytT strengthMods[] = {-18, -15, -12, -9, -6, -3, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 3, 6, 9, 27, 30, 33, 36, 39, 42, 45};
    BytT strmodMods[] = {12, 15, 18, 21, 24};
    BytT variation = 3;
    IntT numberRolled = 0, rHeight;

    if (race == HUMAN)
        variation = 4;

    /* Assign initial height determined by sex and race */
    if (sex == 'M')
        rHeight = maleMods[race];
    else
        rHeight = femaleMods[race];

    /* Modify height by race */
    if (race == HALF_ELF)
        rHeight += Roll_Dice(6, 1);
    if (race == HALF_ORC)
        rHeight += Roll_Dice(6, 1);
    if (race == HUMAN)
        rHeight += Roll_Dice(6, 2);
    
    /* Calculate the height variance by race */
    numberRolled = Roll_Dice(1000, 1);
    if (numberRolled <   6                       ) rHeight -= (3 * variation) + Roll_Dice(variation, 1);
    if (numberRolled <  26  && numberRolled >   5) rHeight -= (2 * variation) + Roll_Dice(variation, 1);
    if (numberRolled < 151  && numberRolled >  25) rHeight -= (1 * variation) + Roll_Dice(variation, 1);
    if (numberRolled < 351  && numberRolled > 150) rHeight -=                   Roll_Dice(variation, 1);

    if (numberRolled < 851  && numberRolled > 650) rHeight +=                   Roll_Dice(variation, 1);
    if (numberRolled < 976  && numberRolled > 850) rHeight += (1 * variation) + Roll_Dice(variation, 1);
    if (numberRolled < 996  && numberRolled > 975) rHeight += (2 * variation) + Roll_Dice(variation, 1);
    if (                       numberRolled > 995) rHeight += (3 * variation) + Roll_Dice(variation, 1);

    /* Modifiy the height by the character's strength */
    if (strmod > 0) {
        if (strmod >  0 && strmod < 51)  rHeight += (strmodMods[0] * rHeight) / 100;
        if (strmod > 50 && strmod < 76)  rHeight += (strmodMods[1] * rHeight) / 100;
        if (strmod > 75 && strmod < 91)  rHeight += (strmodMods[2] * rHeight) / 100;
        if (strmod > 90 && strmod < 100) rHeight += (strmodMods[3] * rHeight) / 100;
        if (strmod == 100)               rHeight += (strmodMods[4] * rHeight) / 100;
    }
    else 
        rHeight += (strengthMods[strength] * rHeight) / 100;

    return rHeight;
}

IntT weightChart(BytT race, ChrT sex, BytT strength, BytT strmod, IntT height)
{
    IntT baseWeight[] = { 14,  15,  17,  18,  20,  22,  24,  26,  28,  30,  32,
           35,  37,  40,  43,  46,  49,  52,  55,  59,  62,  66,  70,  74,  78,
           82,  87,  92,  96, 101, 107, 112, 117, 123, 129, 135, 141, 148, 154,
          161, 168, 175, 183, 190, 198, 206, 214, 223, 232, 240, 250, 259, 268,
          278, 288, 299, 309, 320, 331, 342, 354, 366, 378, 390, 403, 415, 429,
          442, 456, 470, 484, 498, 513, 528, 544, 559, 575, 592, 608, 625};
    BytT raceMods[] = {190, 94, 190, 97, 150, 170, 130, 110, 100};
    BytT strengthMods[] = {-32, -28, -24, -20, -16, -12, -8, -4, 0, 0, 0, 0, 0,
        0, 4, 8, 12, 16, 20, 24, 44, 48, 52, 56, 60, 64};
    BytT strmodMods[] = {24, 28, 32, 36, 40};
    IntT numberRolled = 0, rWeight;
    BytT variation = 6;

    if (race == HUMAN) variation = 8;
    if (height > 110) height = 110;

    /* Get the base weight, adding one if the character is male */
    rWeight = baseWeight[height - (sex=='M' ? 31 : 30)];

    /* Modify the weight depending on the character race */
    rWeight = ((unsigned)(rWeight * raceMods[race])) / 100;

    /* Calculate the weight variance by race */
    numberRolled = Roll_Dice(1000, 1);
    if (numberRolled <   6                       ) rWeight -= (3 * variation) + Roll_Dice(variation, 1);
    if (numberRolled <  26  && numberRolled >   5) rWeight -= (2 * variation) + Roll_Dice(variation, 1);
    if (numberRolled < 151  && numberRolled >  25) rWeight -= (1 * variation) + Roll_Dice(variation, 1);
    if (numberRolled < 351  && numberRolled > 150) rWeight -=                   Roll_Dice(variation, 1);

    if (numberRolled < 851  && numberRolled > 650) rWeight +=                   Roll_Dice(variation, 1);
    if (numberRolled < 976  && numberRolled > 850) rWeight += (1 * variation) + Roll_Dice(variation, 1);
    if (numberRolled < 996  && numberRolled > 975) rWeight += (2 * variation) + Roll_Dice(variation, 1);
    if (                       numberRolled > 995) rWeight += (3 * variation) + Roll_Dice(variation, 1);

    /* Modify the weight by the character's strength */
    if (strmod > 0) {
        if (strmod >  0 && strmod < 51)  rWeight += (strmodMods[0] * rWeight) / 100;
        if (strmod > 50 && strmod < 76)  rWeight += (strmodMods[1] * rWeight) / 100;
        if (strmod > 75 && strmod < 91)  rWeight += (strmodMods[2] * rWeight) / 100;
        if (strmod > 90 && strmod < 100) rWeight += (strmodMods[3] * rWeight) / 100;
        if (strmod == 100)               rWeight += (strmodMods[4] * rWeight) / 100;
    }
    else 
        rWeight += (strengthMods[strength] * rWeight) / 100;

    return rWeight;
}

BytT colorEyes(BytT race)
{
    IntT eColor = -1;

    switch (race) {
        case DWARF      :
        case GNOME      :
            switch (Roll_Dice(10, 1)) {
                case 1  :
                case 2  :
                case 3  : eColor = EC_BLUE;  break;
                case 4  :
                case 5  :
                case 6  : eColor = EC_BROWN; break;
                case 7  :
                case 8  :
                case 9  : eColor = EC_GREY;  break;
                case 10 : 
                    switch (Roll_Dice(6, 1)) {
                        case 1 : eColor = EC_GOLDEN; break;
                        case 2 :
                        case 3 : eColor = EC_GREEN;  break;
                        case 4 :
                        case 5 :
                        case 6 : eColor = EC_JBLACK; break;
                    }
                    break;
            }
            break;
        case ELF        :
        case HALF_ELF   :
            switch (Roll_Dice(20, 1)) {
                case  1 :
                case  2 :
                case  3 :
                case  4 :
                    switch (Roll_Dice(6, 1)) {
                        case 1 : 
                        case 2 : eColor = EC_BBLUE;    break;
                        case 3 : eColor = EC_DBVIOLET; break;
                        case 4 : 
                        case 5 : eColor = EC_LBLUE;    break;
                        case 6 : eColor = EC_BLUE;     break;
                    }
                    break;
                case  5 :
                case  6 :
                case  7 :
                case  8 :
                case  9 :
                case 10 :
                    switch (Roll_Dice(6, 1)) {
                        case 1 : eColor = EC_JBLACK; break;
                        case 2 :
                        case 3 :
                        case 4 :
                        case 5 :
                        case 6 : eColor = EC_DGREY;  break;
                    }
                    break;
                case 11 :
                case 12 : eColor = EC_GOLDEN; break;
                case 13 :
                case 14 :
                case 15 :
                case 16 :
                case 17 :
                case 18 : 
                     switch (Roll_Dice(6, 1)) {
                        case 1 :
                        case 2 :
                        case 3 : eColor = EC_BEMERALD; break;
                        case 4 : 
                        case 5 : eColor = EC_LGREEN;   break;
                        case 6 : eColor = EC_GREEN;    break;
                    }
                    break;
                case 19 :
                case 20 : eColor = EC_SGREY; break;
            }
            break;
        case HALFLING   :
        case STOUT      :
        case TALLFELLOW :
            switch (Roll_Dice(12, 1)) {
                case  1 : 
                case  2 : 
                case  3 : 
                case  4 : 
                case  5 : 
                case  6 : eColor = EC_BLUE;  break;
                case  7 : 
                case  8 : 
                case  9 : eColor = EC_BROWN; break;
                case 10 : eColor = EC_GREEN; break;
                case 11 : 
                case 12 : eColor = EC_GREY;  break;
            }
            break;
        case HALF_ORC :
        case HUMAN    :
            switch (Roll_Dice(20, 1)) {
                case  1 : 
                case  2 : 
                case  3 : 
                case  4 : 
                case  5 : eColor = EC_BLUE; break;
                case  6 : 
                case  7 : 
                case  8 : 
                case  9 : 
                case 10 : eColor = EC_BROWN; break;
                case 11 : eColor = EC_DGREY; break;
                case 12 : eColor = EC_GOLDEN; break;
                case 13 : 
                case 14 : 
                case 15 : 
                case 16 : 
                case 17 : eColor = EC_GREEN; break;
                case 18 : eColor = EC_GREY; break;
                case 19 : eColor = EC_JBLACK; break;
                case 20 : eColor = EC_SGREY; break;
            }
            break;
    }
    return eColor;
}

BytT colorSkin(BytT race)
{
    IntT sColor = -1;

    switch (race) {
        case DWARF      :
        case GNOME      :
        case HALF_ORC   :
            switch (Roll_Dice(10, 1)) {
                case  1 : sColor = SC_GREY;   break;
                case  2 :
                case  3 :
                case  4 :
                case  5 :
                case  6 :
                case  7 : sColor = SC_TANNED; break;
                case  8 :
                case  9 :
                case 10 : sColor = SC_BROWN;  break;
            }
            break;
        case ELF :
            switch (Roll_Dice(20, 1)) {
                case  1 : 
                case  2 : 
                case  3 : 
                case  4 : 
                case  5 : 
                    switch (Roll_Dice(6, 1)) {
                        case 1 : sColor = SC_PGREEN; break;
                        case 2 :
                        case 3 :
                        case 4 :
                        case 5 :
                        case 6 : sColor = SC_PALE;   break;
                    }
                    break;
                case  6 : 
                case  7 : 
                case  8 : 
                case  9 : 
                case 10 : 
                case 11 : 
                case 12 : sColor = SC_FAIR; break;
                case 13 : 
                case 14 : 
                case 15 : 
                case 16 : 
                case 17 : sColor = SC_NORMAL; break;
                case 18 : 
                case 19 : 
                case 20 : sColor = SC_TANNED; break;
            }
            break;
        case HALF_ELF   :
        case HUMAN      :
            switch (Roll_Dice(20, 1)) {
                case  1 : sColor = SC_ALBINO; break;
                case  2 : sColor = SC_PALE; break;
                case  3 :
                case  4 : sColor = SC_JAUNDICED; break;
                case  5 :
                case  6 :
                case  7 :
                case  8 :
                case  9 : sColor = SC_WHITE; break;
                case 10 :
                case 11 :
                case 12 :
                case 13 : sColor = SC_TANNED; break;
                case 14 :
                case 15 :
                case 16 :
                case 17 :
                case 18 :
                case 19 : sColor = SC_RUDDY; break;
                case 20 : sColor = SC_BLACK; break;
            }
            break;
        case HALFLING   :
        case STOUT      :
        case TALLFELLOW :
            switch (Roll_Dice(6, 1)) {
                case 1 : sColor = SC_FAIR; break;
                case 2 :
                case 3 :
                case 4 :
                case 5 : sColor = SC_NORMAL; break;
                case 6 : sColor = SC_DARK; break;
            }
            break;
    }

    return sColor;
}

BytT hairLength(BytT race, ChrT sex)
{
    IntT hLength = -1;

    switch (race) {
        case DWARF :
        case GNOME :
            switch (Roll_Dice(10, 1)) {
                case  1 :
                case  2 : hLength = HL_BALD; break;
                case  3 :
                case  4 : hLength = HL_EAR; break;
                case  5 :
                case  6 :
                case  7 :
                case  8 : hLength = HL_SHOULDER; break;
                case  9 :
                case 10 : hLength = HL_WAIST; break;
            }
            break;
        case ELF :
            switch (Roll_Dice(10, 1)) {
                case  1 :
                case  2 : if (sex=='F') {hLength = HL_SHOULDER;       break;}
                case  3 : 
                case  4 : if (sex=='M') {hLength = HL_EAR;            break;}
                case  5 :
                case  6 :
                case  7 : if (sex=='F') {hLength = HL_WAIST;          break;}
                case  8 : 
                case  9 : if (sex=='M') {hLength = HL_SHOULDER;       break;}
                case 10 : hLength = (sex=='M' ? HL_WAIST : HL_PWAIST); break;
            }
            break;
        case HALF_ELF :
        case HALF_ORC :
        case HUMAN :
            switch (Roll_Dice(6, 1)) {
                case 1 : hLength = (sex=='M' ? HL_BALD : HL_EAR); break;
                case 2 :
                case 3 : hLength = (sex=='M' ? HL_EAR : HL_SHOULDER); break;
                case 4 :
                case 5 : hLength = (sex=='M' ? HL_SHOULDER : HL_WAIST); break;
                case 6 : hLength = (sex=='M' ? HL_WAIST : HL_PWAIST); break;
            }
            break;
        case HALFLING :
        case STOUT :
        case TALLFELLOW :
            switch (Roll_Dice(10, 1)) {
                case  1 : hLength = (sex=='M' ? HL_BALD : HL_WAIST); break;
                case  2 :
                case  3 :
                case  4 :
                case  5 :
                case  6 :
                case  7 :
                case  8 :
                case  9 :
                case 10 : hLength = (sex=='M' ? HL_EAR : HL_SHOULDER); break;
            }
            break;
    }

    return hLength;
}

BytT hairColor(BytT race)
{
    IntT hColor = -1;

    switch (race) {
        case DWARF :
        case GNOME :
            switch (Roll_Dice(20, 1)) {
                case  1 :
                case  2 :
                case  3 :
                case  4 : hColor = HC_BLACK; break;
                case  5 :
                case  6 :
                case  7 : hColor = HC_BLONDE; break;
                case  8 :
                case  9 :
                case 10 :
                case 11 :
                case 12 :
                case 13 : hColor = HC_BROWN; break;
                case 14 :
                case 15 :
                case 16 :
                case 17 : hColor = HC_GREY; break;
                case 18 : hColor = HC_RED; break;
                case 19 :
                case 20 : hColor = HC_WHITE; break;
            }
            break;
        case ELF :
        case HALF_ELF :
            switch (Roll_Dice(20, 1)) {
                case  1 :
                case  2 : hColor = HC_BBLACK; break;
                case  3 :
                case  4 : 
                    switch (Roll_Dice(6, 1)) {
                        case 1 : hColor = HC_DGREY; break;
                        case 2 : 
                        case 3 :
                        case 4 : 
                        case 5 : hColor = HC_LGREY; break;
                        case 6 : hColor = HC_GREY; break;
                    }
                    break;
                case  5 :
                case  6 :
                case  7 : 
                case  8 : hColor = HC_HBLONDE; break;
                case  9 :
                case 10 :
                case 11 :
                case 12 :
                case 13 : 
                case 14 : hColor = HC_LBLONDE; break;
                case 15 : hColor = HC_MGOLD; break;
                case 16 :
                case 17 : 
                case 18 : 
                    switch (Roll_Dice(6, 1)) {
                        case 1 : hColor = HC_AUBURN; break;
                        case 2 :
                        case 3 : hColor = HC_COPPER; break;
                        case 4 :
                        case 5 : hColor = HC_RGOLD; break;
                        case 6 : hColor = HC_RED; break;
                    }
                    break;
                case 19 :
                case 20 : 
                    switch (Roll_Dice(6, 1)) {
                        case 1 : hColor = HC_MSILVER; break;
                        case 2 :
                        case 3 :
                        case 4 :
                        case 5 : hColor = HC_WHITE; break;
                        case 6 : hColor = HC_PGREEN; break;
                    }
                    break;
            }
            break;
        case HALFLING :
        case STOUT :
        case TALLFELLOW :
            switch (Roll_Dice(12, 1)) {
                case  1 : hColor = HC_BLACK; break;
                case  2 : 
                case  3 : hColor = HC_BLONDE; break;
                case  4 : 
                case  5 : hColor = HC_DBROWN; break;
                case  6 : 
                case  7 : hColor = HC_GREY; break;
                case  8 : 
                case  9 : 
                case 10 : hColor = HC_LBROWN; break;
                case 11 : hColor = HC_RED; break;
                case 12 : hColor = HC_WHITE; break;
            }
            break;
        case HALF_ORC :
        case HUMAN :
            switch (Roll_Dice(20, 1)) {
                case  1 :
                case  2 :
                case  3 : hColor = HC_BLACK; break;
                case  4 :
                case  5 :
                case  6 : hColor = HC_BLONDE; break;
                case  7 :
                case  8 : hColor = HC_BBLACK; break;
                case  9 :
                case 10 :
                case 11 : hColor = HC_BROWN; break;
                case 12 :
                case 13 :
                case 14 : hColor = HC_GREY; break;
                case 15 :
                case 16 :
                case 17 : hColor = HC_RED; break;
                case 18 :
                case 19 :
                case 20 : hColor = HC_WHITE; break;
            }
            break;
    }

    return hColor;
}

BytT beardLength(BytT race)
{
    IntT bLength = BL_SHAVED;

    switch (race) {
        case DWARF : 
        case GNOME :
            switch (Roll_Dice(10, 1)) {
                case  1 : bLength = BL_3INCH; break;
                case  2 : bLength = BL_4INCH; break;
                case  3 :
                case  4 :
                case  5 :
                case  6 :
                case  7 :
                case  8 : bLength = BL_ONCHEST; break;
                case  9 :
                case 10 : bLength = BL_TOBELT; break;
            }
            break;
        case HALF_ELF :
        case HALF_ORC :
        case HUMAN    :
            if (Roll_Dice(100, 1) < 31)
                switch (Roll_Dice(10, 1)) {
                    case  1 : bLength = BL_SHAVED; break;
                    case  2 : bLength = BL_WHISKERS; break;
                    case  3 : bLength = BL_1INCH; break;
                    case  4 : bLength = BL_2INCH; break;
                    case  5 : bLength = BL_3INCH; break;
                    case  6 :
                    case  7 :
                    case  8 :
                    case  9 : bLength = BL_4INCH; break;
                    case 10 : bLength = BL_ONCHEST; break;
                }
            break;
    }

    return bLength;
}

VOID calcLiquorTolerance(IntP blt, IntP hbr)
{
    FltT frameFactor, burnMod;
    div_t divide;

    if (DscWgt(CHARNUM) + DscHgt(CHARNUM) > 0) {
        frameFactor = ((FltT)DscWgt(CHARNUM) / (FltT)DscHgt(CHARNUM) / 2.0);
        burnMod = (FltT)(2.0 - frameFactor);
        divide = div(StaStp(CHARNUM), 10);
        *blt = 
            (IntT)(
                ((FltT)StaCon(CHARNUM) + 2.0) * 
                ((FltT)StaStr(CHARNUM) + divide.quot) * 
                frameFactor
            )
        ;
        *hbr = (IntT)(((FltT)StaCon(CHARNUM)) * 1.5 * burnMod);
    }
    else
        MessageWindow(" Unable to generate BLT/HBR due to uninitialized Height/Weight");
}

VOID calcFacialFeatures(NOARG)
{
    IntT j;

    for (j = 0; j < 8; j++)
        cData[CHARNUM].GenAppear[j] = -1;

    switch(ChrRac(CHARNUM)) {
        case DWARF :
        case ELF :
            calcDwarfElf();
            break;

        case GNOME :
            calcGnome();
            break;

        case HALF_ELF :
        case HALF_ORC :
        case HUMAN :
            calcHalfelfHalforcHuman();
            break;

        case HALFLING :
        case STOUT :
        case TALLFELLOW :
            calcHalflingStoutTallfellow();

        default :
            break;
    }
}

VOID calcDwarfElf(NOARG)
{
    IntT dieRoll, numTimes;
    FlgT switches[9];
    IntT j;

    for (j = 0; j < 9; j++)
        switches[j] = FALSE;

    numTimes = Roll_Dice(2, 1);

    for (j = 0; j < numTimes; j++) {
        dieRoll = Roll_Dice(100, 1);
        if (dieRoll < 6) {
            cData[CHARNUM].GenAppear[j] = 1;
            if (!switches[0])
                switches[0] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 14) {
            cData[CHARNUM].GenAppear[j] = 2;
            if (!switches[0])
                switches[0] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 20) {
            cData[CHARNUM].GenAppear[j] = 4;
            if (!switches[1])
                switches[1] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 27) {
            cData[CHARNUM].GenAppear[j] = 9;
            if (!switches[1])
                switches[1] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 33) {
            cData[CHARNUM].GenAppear[j] = 16;
            dieRoll = 200;
        }
        if (dieRoll < 39) {
            cData[CHARNUM].GenAppear[j] = 17;
            if (!switches[2])
                switches[2] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 45) {
            cData[CHARNUM].GenAppear[j] = 18;
            if (!switches[2])
                switches[2] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 51) {
            cData[CHARNUM].GenAppear[j] = 19;
            if (!switches[6])
                switches[6] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 58) {
            cData[CHARNUM].GenAppear[j] = 20;
            if (!switches[7])
                switches[7] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 64) {
            cData[CHARNUM].GenAppear[j] = 23;
            if (!switches[8])
                switches[8] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 70) {
            cData[CHARNUM].GenAppear[j] = 27;
            if (!switches[3])
                switches[3] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 76) {
            cData[CHARNUM].GenAppear[j] = 30;
            if (!switches[3])
                switches[3] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 82) {
            cData[CHARNUM].GenAppear[j] = 34;
            if (!switches[4])
                switches[4] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 89) {
            cData[CHARNUM].GenAppear[j] = 35;
            if (!switches[5])
                switches[5] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 95) {
            cData[CHARNUM].GenAppear[j] = 37;
            if (!switches[4])
                switches[4] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 101) {
            cData[CHARNUM].GenAppear[j] = 1;
            if (!switches[5])
                switches[5] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
    }
}

VOID calcGnome(NOARG)
{
    IntT dieRoll, numTimes;
    FlgT switches[11];
    IntT j;

    for (j = 0; j < 11; j++)
        switches[j] = FALSE;

    numTimes = Roll_Dice(4, 1);

    for (j = 0; j < numTimes; j++) {
        dieRoll = Roll_Dice(100, 1);
        if (dieRoll < 5) {
            cData[CHARNUM].GenAppear[j] = 4;
            if (!switches[0])
                switches[0] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 16) {
            cData[CHARNUM].GenAppear[j] = 5;
            if (!switches[1])
                switches[1] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 21) {
            cData[CHARNUM].GenAppear[j] = 6;
            if (!switches[1])
                switches[1] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 27) {
            cData[CHARNUM].GenAppear[j] = 7;
            if (!switches[2])
                switches[2] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 32) {
            cData[CHARNUM].GenAppear[j] = 8;
            if (!switches[2])
                switches[2] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 37) {
            cData[CHARNUM].GenAppear[j] = 9;
            if (!switches[0])
                switches[0] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 42) {
            cData[CHARNUM].GenAppear[j] = 10;
            if (!switches[7])
                switches[7] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 48) {
            cData[CHARNUM].GenAppear[j] = 12;
            if (!switches[8])
                switches[8] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 53) {
            cData[CHARNUM].GenAppear[j] = 13;
            if (!switches[3])
                switches[3] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 58) {
            cData[CHARNUM].GenAppear[j] = 15;
            if (!switches[3])
                switches[3] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 63) {
            cData[CHARNUM].GenAppear[j] = 16;
            dieRoll = 200;
        }
        if (dieRoll < 68) {
            cData[CHARNUM].GenAppear[j] = 17;
            if (!switches[4])
                switches[4] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 74) {
            cData[CHARNUM].GenAppear[j] = 18;
            if (!switches[4])
                switches[4] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 80) {
            cData[CHARNUM].GenAppear[j] = 19;
            if (!switches[9])
                switches[9] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 85) {
            cData[CHARNUM].GenAppear[j] = 20;
            if (!switches[10])
                switches[10] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 90) {
            cData[CHARNUM].GenAppear[j] = 22;
            if (!switches[5])
                switches[5] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 95) {
            cData[CHARNUM].GenAppear[j] = 31;
            if (!switches[5])
                switches[5] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 99) {
            cData[CHARNUM].GenAppear[j] = 34;
            if (!switches[6])
                switches[6] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 101) {
            cData[CHARNUM].GenAppear[j] = 37;
            if (!switches[6])
                switches[6] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
    }
}

VOID calcHalfelfHalforcHuman(NOARG)
{
    IntT dieRoll, numTimes;
    FlgT switches[20];
    IntT j;

    for (j = 0; j < 20; j++)
        switches[j] = FALSE;

    numTimes = Roll_Dice(8, 1);

    for (j = 0; j < numTimes; j++) {
        dieRoll = Roll_Dice(100, 1);
        if (dieRoll < 4) {
            cData[CHARNUM].GenAppear[j] = 1;
            if (!switches[0])
                switches[0] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 7) {
            cData[CHARNUM].GenAppear[j] = 2;
            if (!switches[0])
                switches[0] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 11) {
            cData[CHARNUM].GenAppear[j] = 4;
            if (!switches[1])
                switches[1] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 14) {
            cData[CHARNUM].GenAppear[j] = 5;
            if (!switches[2])
                switches[2] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 17) {
            cData[CHARNUM].GenAppear[j] = 6;
            if (!switches[2])
                switches[2] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 20) {
            cData[CHARNUM].GenAppear[j] = 7;
            if (!switches[3])
                switches[3] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 23) {
            cData[CHARNUM].GenAppear[j] = 8;
            if (!switches[3])
                switches[3] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 26) {
            cData[CHARNUM].GenAppear[j] = 9;
            if (!switches[1])
                switches[1] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 29) {
            cData[CHARNUM].GenAppear[j] = 10;
            if (!switches[12])
                switches[12] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 32) {
            cData[CHARNUM].GenAppear[j] = 11;
            if (!switches[13])
                switches[13] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 35) {
            cData[CHARNUM].GenAppear[j] = 12;
            if (!switches[18])
                switches[18] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 38) {
            cData[CHARNUM].GenAppear[j] = 13;
            if (!switches[4])
                switches[4] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 41) {
            cData[CHARNUM].GenAppear[j] = 14;
            if (!switches[14])
                switches[14] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 44) {
            cData[CHARNUM].GenAppear[j] = 15;
            if (!switches[4])
                switches[4] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 46) {
            cData[CHARNUM].GenAppear[j] = 16;
            dieRoll = 200;
        }
        if (dieRoll < 50) {
            cData[CHARNUM].GenAppear[j] = 17;
            if (!switches[5])
                switches[5] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 53) {
            cData[CHARNUM].GenAppear[j] = 18;
            if (!switches[5])
                switches[5] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 57) {
            cData[CHARNUM].GenAppear[j] = 19;
            if (!switches[15])
                switches[15] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 60) {
            cData[CHARNUM].GenAppear[j] = 20;
            if (!switches[6])
                switches[6] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 64) {
            cData[CHARNUM].GenAppear[j] = 21;
            if (!switches[6])
                switches[6] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 67) {
            cData[CHARNUM].GenAppear[j] = 22;
            if (!switches[7])
                switches[7] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 71) {
            cData[CHARNUM].GenAppear[j] = 24;
            if (!switches[16])
                switches[16] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 75) {
            cData[CHARNUM].GenAppear[j] = 25;
            if (!switches[8])
                switches[8] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 78) {
            cData[CHARNUM].GenAppear[j] = 28;
            if (!switches[8])
                switches[8] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 81) {
            cData[CHARNUM].GenAppear[j] = 31;
            if (!switches[7])
                switches[7] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 84) {
            cData[CHARNUM].GenAppear[j] = 32;
            if (!switches[9])
                switches[9] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 87) {
            cData[CHARNUM].GenAppear[j] = 33;
            if (!switches[17])
                switches[17] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 90) {
            cData[CHARNUM].GenAppear[j] = 34;
            if (!switches[10])
                switches[10] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 93) {
            cData[CHARNUM].GenAppear[j] = 35;
            if (!switches[11])
                switches[11] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 96) {
            cData[CHARNUM].GenAppear[j] = 36;
            if (!switches[9])
                switches[9] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 99) {
            cData[CHARNUM].GenAppear[j] = 37;
            if (!switches[10])
                switches[10] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 101) {
            cData[CHARNUM].GenAppear[j] = 38;
            if (!switches[11])
                switches[11] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
    }
}

VOID calcHalflingStoutTallfellow(NOARG)
{
    IntT dieRoll, numTimes;
    FlgT switches[10];
    IntT j;

    for (j = 0; j < 10; j++)
        switches[j] = FALSE;

    numTimes = Roll_Dice(4, 1);

    for (j = 0; j < numTimes; j++) {
        dieRoll = Roll_Dice(100, 1);
        if (dieRoll < 6) {
            cData[CHARNUM].GenAppear[j] = 0;
            if (!switches[0])
                switches[0] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 11) {
            cData[CHARNUM].GenAppear[j] = 3;
            if (!switches[0])
                switches[0] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 16) {
            cData[CHARNUM].GenAppear[j] = 4;
            if (!switches[1])
                switches[1] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 22) {
            cData[CHARNUM].GenAppear[j] = 7;
            if (!switches[2])
                switches[2] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 27) {
            cData[CHARNUM].GenAppear[j] = 8;
            if (!switches[2])
                switches[2] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 33) {
            cData[CHARNUM].GenAppear[j] = 9;
            if (!switches[1])
                switches[1] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 38) {
            cData[CHARNUM].GenAppear[j] = 11;
            if (!switches[8])
                switches[8] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 44) {
            cData[CHARNUM].GenAppear[j] = 12;
            if (!switches[9])
                switches[9] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 49) {
            cData[CHARNUM].GenAppear[j] = 20;
            if (!switches[3])
                switches[3] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 55) {
            cData[CHARNUM].GenAppear[j] = 21;
            if (!switches[3])
                switches[3] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 61) {
            cData[CHARNUM].GenAppear[j] = 25;
            if (!switches[4])
                switches[4] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 66) {
            cData[CHARNUM].GenAppear[j] = 26;
            if (!switches[5])
                switches[5] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 71) {
            cData[CHARNUM].GenAppear[j] = 28;
            if (!switches[4])
                switches[4] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 78) {
            cData[CHARNUM].GenAppear[j] = 29;
            if (!switches[5])
                switches[5] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 84) {
            cData[CHARNUM].GenAppear[j] = 32;
            if (!switches[6])
                switches[6] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 90) {
            cData[CHARNUM].GenAppear[j] = 34;
            if (!switches[7])
                switches[7] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 96) {
            cData[CHARNUM].GenAppear[j] = 36;
            if (!switches[6])
                switches[6] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
        if (dieRoll < 101) {
            cData[CHARNUM].GenAppear[j] = 37;
            if (!switches[7])
                switches[7] = TRUE;
            else
                j--;
            dieRoll = 200;
        }
    }
}

#ifdef CARL
Def func SCAR_TABLE$(ARG)
TYPE=ROLL_IT(12,1)
LENGTH=ROLL_IT(8,2)
ARG$=S_LEN$(LENGTH)+" Scar "+SCAR$(TYPE)
Return ARG$
Func end

#endif
