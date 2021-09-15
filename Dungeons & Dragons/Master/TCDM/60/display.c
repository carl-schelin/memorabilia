/* []---------------------------------------------------------------------[] */
/* |     Display.cpp: Main screen code. Shows character information.       | */
/* |                                                                       | */
/* |             The Display.cpp source code and concepts are              | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __DISPLAY__

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <TcxlAtr.H>
#include <TcxlDef.H>
#include <TcxlInp.H>
#include <TcxlKey.H>
#include <TcxlSel.H>
#include <TcxlVid.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID Print_Char(AtrT DrawMode, IntT Whom);
VOID Attack_Line(AtrT DrawMode, IntT Whom);
VOID Print_Sheet(NOARG);
VOID Print_Data(NOARG);
VOID Update_Data(IntT whichOne);
VOID Print_Monster_Sheet(NOARG);
VOID Print_Character_Sheet(NOARG);
VOID Print_Monster_Data(IntT cmNum);
VOID Print_Character_Data(IntT cmNum);
VOID Display_Desc(NOARG);

GBL VOID Adjust_Armor_Class(NOARG);

ChrP groups[] = {"Warrior", "Wizard", "Priest", "Rogue", "Psionicist", NULL};
ChrP classWarrior[] = {"Fighter", "Paladin", "Ranger", NULL};
ChrP classWizard[] = {"Mage", "Abjurer", "Conjurer", "Diviner", "Enchanter",
	 "Illusionist", "Invoker", "Necromancer", "Transmuter", "Wild Mage",
    "Air Mage", "Earth Mage", "Fire Mage", "Water Mage", NULL};
ChrP classPriest[] = {"Cleric", "Agriculture", "Ancestors", "Animals", "Arts",
    "Birth, Children", "Community", "Competition", "Crafts", "Culture",
    "Darkness, Night", "Dawn", "Death", "Disease", "Divinity", "Druid",
    "Earth", "Elemental Forces", "Everything", "Evil", "Fate, Destiny",
    "Fertility", "Fire", "Fortune, Luck", "Good", "Guardianship", "Healing",
    "Hunting", "Justice, Revenge", "Life-Death-Rebirth Cycle", "Light",
    "Lightning", "Literature, Poetry", "Love", "Magic", "Marriage",
    "Messengers", "Metalwork", "Mischief, Trickery", "Moon", "Music, Dance",
    "Nature", "Oceans, Rivers", "Oracles, Prophecy", "Peace", "Prosperity",
    "Race", "Redemption", "Rulership, Kingship", "Seasons", "Sites",
    "Sky, Weather", "Strength", "Sun", "Thunder", "Time", "Trade",
    "Vegetation", "War", "Wind", "Wisdom", NULL};
ChrP classRogue[] = {"Thief", "Bard", NULL};
ChrP classPsionicist[] = {"Psionicist", NULL};

ChrP warriorKits[] = {"Amazon", "Barbarian", "Beast-Rider", "Berserker",
    "Cavalier", "Gladiator", "Myrmidon", "Noble Warrior", "Peasant Hero",
    "Pirate/Outlaw", "Samurai", "Savage", "Swashbuckler", "Wilderness Warrior",
    NULL};
ChrP wizardKits[] = {"Academican", "Amazon Sorceress", "Anagakok",
    "Militent Wizard", "Mystic", "Patrician", "Savage Wizard", "Witch",
    "Wu Jen", NULL};
ChrP priestKits[] = {"Amazon Priestess", "Barbarian/Berserker Priest",
    "Fighting Monk", "Nobleman Priest", "Outlaw Priest", "Pacifist Priest", 
    "Peasant Priest", "Prophet Priest", "Savage Priest", "Scholar Priest", 
    NULL};
ChrP thiefKits[] = {"Acrobat", "Adventurer", "Assassin", "Bandit", "Begger",
    "Bounty Hunter", "Buccaneer", "Burglar", "Cutpurse", "Fence",
    "Investigator", "Scout", "Smuggler", "Spy", "Swashbuckler", "Swindler",
	 "Thug", "Troubleshooter", NULL};

ChrP bardKits[] = {"True", "Blade", "Charlatan", "Gallant", "Gypsy", "Herald",
	 "Jester", "Jongleur", "Loremaster", "Meistersinger", "Riddlemaster",
	 "Skald", "Thespian", NULL};

ChrP race[] = {"Dwarf", "Elf", "Gnome", "Half-Elf", "Halfling", "Stout",
	 "Tallfellow", "Half-Orc", "Human", NULL};

ChrP alignment[] = {"Lawful Good", "Lawful Neutral", "Lawful Evil",
	 "Neutral Good", "True Neutral", "Neutral Evil",
	 "Chaotic Good", "Chaotic Neutral", "Chaotic Evil", NULL};

ChrP monstersize[] = {"T", "S", "M", "L", "H", "G", NULL};

ChrP flyingclass[] = {"A", "B", "C", "D", "E", NULL};

ChrP armorTypes[] = {"Full Field Plate", "Field Plate Armor", "Plate Armor",
	 "Banded Armor", "Splinted Armor", "Bronze Plate", "Elfin Chain Mail",
	 "Chain Mail", "Scale Mail", "Ring Mail", "Studded Leather", "Padded Armor",
	 "Leather Armor", "No Armor", NULL};

ChrP shieldTypes[] = {"Kite Shield", "Metal Shield", "Reinforced Wood",
	 "Wooden Shield", "Flora Shield", "Fauna Shield", "No Shield", NULL};

ChrP helmTypes[] = {"Great Helm", "Nasal Helm", "Metal Helm", "Mail Coif",
	 "Metal Cap", "Leather Cap", "No Helm", NULL};

ChrP descEye[] = {"Blue", "Bright Blue", "Bright Emerald", "Brown",
	 "Dark Gray", "Deep Blue Violet", "Golden", "Green", "Grey", "Jet Black",
	 "Light Blue", "Light Green", "Pink", "Silver Gray", "Changeable", NULL};
ChrP descSkin[] = {"Albino", "Pale", "Grey", "Fair", "Pale Green",
	 "Jaundiced", "White", "Normal", "Tanned", "Dark", "Ruddy", "Brown",
	 "Black", NULL};
ChrP descHair[] = {"Auburn", "Black", "Blond", "Blue-Black", "Brown",
	 "Copper", "Dark Brown", "Dark Grey", "Gray", "Honey Blond", "Light Blond",
	 "Light Brown", "Light Gray", "Metallic Gold", "Metal Silver", "Pale Green",
	 "Red", "Red Gold", "White", NULL};
ChrP descHLength[] = {"Bald", "Ear", "Waist", "Shoulder", "Past Waist", NULL};
ChrP descBLength[] = {"Shaved", "Whiskers", "1\"", "2\"", "3\"", "4\"",
	 "On Chest", "To Belt", NULL};
ChrP descFace[] = {"Large Ears", "Long-Lobed Ears", "Short-Lobed Ears",
	 "Small Ears", "Large Eyes", "Narrow Eyes", "Round Eyes",
	 "Eyes Close Together", "Eyes Far Apart", "Small Eyes", "Epicanthic Fold",
	 "Freckles", "High Forehead", "Narrow Face", "Pock Marked Face",
	 "Round Face", "Scar*", "Sharp Features", "Soft Features", "Upturned Brows",
	 "Curly Hair", "Straight Hair", "Full Lips", "Gaptoothed", "Hair Lip",
	 "Jutting Jaw","Large Mouth", "Large Teeth", "Overbite", "Small Mouth",
	 "Small Teeth", "Thin Lips", "Blunt Nose", "Broken Nose", "Large Nose",
	 "Narrow Nose", "Sharp Nose", "Small Nose", "Wide Nose", NULL};
ChrP descHand[] = {"Right", "Left", "Ambidextrious", NULL};

/*                    1  2  3  4  5  6  7  8  9 10 11 12 13 14  15  16  17  18  19  20  21  22  23  24  25 */
IntT dexterity[25] = {4, 4, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, -1, -2, -3, -4, -4, -5, -5, -5, -5, -6, -6};

struct monsScrn {
	 BytT mnRow;
	 BytT mnCol;
	 ChrP mnText;
} monsScreen[37] = {
	 { 0,  1, "Name:"                                  },
	 { 1,  0, "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" },
	 { 2,  1, "Alignment:"                             },
	 { 2, 30, "Size:"                                  },
	 { 3,  1, "Movement Rate:"                         },
	 { 3, 19, "'"                                      },
	 { 3, 22, "Fly:"                                   },
	 { 3, 30, "' MC:"                                  },
	 { 4,  1, "Swim:"                                  },
	 { 4, 10, "' Burrow:"                              },
	 { 4, 23, "' Web:"                                 },
	 { 4, 33, "'"                                      },
	 { 5,  0, "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" },
	 { 6,  1, "Base AC:"                               },
	 { 6, 14, "w/Armor:"                               },
	 { 6, 27, "Other:"                                 },
	 { 7,  1, "Hit Points:"                            },
	 { 7, 17, "(Down"                                  },
	 { 7, 26, ", Left"                                 },
	 { 7, 36, ")"                                      },
	 { 8,  1, "Hit Dice:"                              },
	 { 8, 15, "+"                                      },
	 { 8, 22, "To Hit AC 0:"                           },
	 { 9,  1, "Damage:"                                },
	 { 9, 29, "MR:"                                    },
	 { 9, 36, "%"                                      },
	 {10,  1, "SA:"                                    },
	 {11,  1, "SD:"                                    },
	 {12,  1, "EP:"                                    },
	 {13,  0, "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" },
	 {14,  5, "m"                                      },
	 {14, 11, "p"                                      },
	 {14, 18, "g"                                      },
	 {14, 24, "e"                                      },
	 {14, 30, "s"                                      },
	 {14, 36, "c"                                      },
	 {16,  0, "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" }
};

struct charScrn {
	 BytT chRow;
	 BytT chCol;
	 ChrP chText;
} charScreen[34] = {
	 { 0,  1, "Name:"                                  },
	 { 1,  0, "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" },
	 { 2,  1, "Hit Points:"                            },
	 { 2, 17, "(Down"                                  },
	 { 2, 26, ", Left"                                 },
	 { 2, 36, ")"                                      },
	 { 3,  1, "Alignment:"                             },
	 { 3, 31, "PSI:"                                   },
	 { 4,  1, "Race:"                                  },
	 { 5,  0, "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" },
	 { 9,  0, "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" },
	 {10,  1, "AC:"                                    },
	 {10, 10, "Rear:"                                  },
	 {10, 21, "Shieldless:"                            },
	 {11,  1, "Armor:"                                 },
	 {12,  1, "Shield:"                                },
	 {13,  1, "Helmet:"                                },
	 {14,  0, "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" },
	 {15,  1, "Poison:"                                },
	 {15, 17, "-"                                      },
	 {15, 21, "Pet/Poly:"                              },
	 {15, 34, "-"                                      },
	 {16,  1, "Para/DM:"                               },
	 {16, 17, "-"                                      },
	 {16, 21, "Breath:"                                },
	 {16, 34, "-"                                      },
	 {17,  1, "Rod/Sta/Wnd:"                           },
	 {17, 17, "-"                                      },
	 {17, 21, "Spell:"                                 },
	 {17, 34, "-"                                      },
	 {18,  0, "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" },
	 {19,  1, "Light:"                                 },
	 {19, 23, "Time Left:"                             },
	 {20,  1, "Experience:"                            }
};

GBL AtrT cAlt[4];
GBL AtrT cMain[4];
GBL ChrP light_Types[];
GBL IntT loadLayout;
GBL WndT cWindow, cHeader, cStatus, cPlayer, cCombat;

/* if in combat mode and attacking, either character or monster, print a
	line from the attacker to the defender.

	pChar = "³"
	loop j from 0 to totalchars
	  pChar = vertical
	  if attackwho = j pChar = lelbow
	  if whom = j pChar = relbow
	  if attackwho = j and whom = j pChar = horiz
	  print pChar
*/

VOID Print_Char(AtrT DrawMode, IntT Whom)
{
    ChrP pChar = "  ";
    IntT j;

    if (DrawMode == NORMAL) 
        DrawMode = cMain[TCDM_WINDOW];
    else
        DrawMode = cMain[TCDM_BARINPUT];
    if (ChrWnd(Whom) == 0) 
        ChrWnd(Whom) = cWindow;
    if (MonWnd(Whom) == 0) 
		  MonWnd(Whom) = cWindow;

    /* if true
         if character
           print character data
         else
           print monster data
       else
         print character data

		 if true
         if character
           if attacking > -1
             print monster data
           else
             print character data
         else
           if attacking > -1
             print character data
           else
             print monster data
       else
         print character data */

	 if (combatMode == TRUE) {
        if (combatStatus == CHARACTER) {
            Wactiv(cCombat);
            Wprts(MsInt((Whom - charNumEx + 1)), 22, (AtrT)DrawMode, cData[Whom].CombatMode);

            if (ChrAtk(Whom) >= 0 && (unsigned)DrawMode == cMain[TCDM_BARINPUT]) {
                Vprints(ChrAtk(Whom) + 2, 41, cMain[TCDM_WINDOW], mData[ChrAtk(Whom)].CombatMode);
                Vputs(Whom - charNumEx + 2, 61, "Ä", cMain[TCDM_WINDOW]);
                for (j = 0; j < totalChars; j++) {
                    if ((charNumEx > 0 && j >= charsOnScreen) || (charNumEx == 0 && j < charsOnScreen)) {
								pChar[0] = ' ';
                        pChar[1] = ' ';
                        if ((j > Whom && j < ChrAtk(Whom)) || (j > ChrAtk(Whom) && j < Whom))
                            pChar[1] = 0xB3; /* ³ */
                        if (ChrAtk(Whom) == j && Whom  > j) {
                            pChar[1] = 0xBF; /* ¿ */
                            pChar[0] = 0x11; /*  */
                        }
                        if (ChrAtk(Whom) == j && Whom <  j) {
                            pChar[1] = 0xD9; /* Ù */
                            pChar[0] = 0x11; /*  */
                        }
                        if (ChrAtk(Whom)  > j && Whom == j)
                            pChar[1] = 0xDA; /* Ú */
								if (ChrAtk(Whom) <  j && Whom == j)
                            pChar[1] = 0xC0; /* À */
                        if (ChrAtk(Whom) == j && Whom == j) {
                            pChar[1] = 0xC4; /* Ä */
                            pChar[0] = 0x11; /*  */
                        }
                        Vputs(j + 2 - charNumEx, 59, pChar, cMain[TCDM_WINDOW]);
                    }
                }
            }
				else {
                for (j = 0; j < totalChars; j++)
                    if ((charNumEx > 0 && j >= charsOnScreen) || (charNumEx == 0 && j < charsOnScreen))
                        Vputs(j + 2 + charNumEx, 59, "   ", cMain[TCDM_WINDOW]);
            }

        }
        else {
            Wactiv(cCombat);
            Wprts(MsInt((Whom - monNumEx + 1)), 1, DrawMode, mData[Whom].CombatMode);

            if (MonAtk(Whom) >= 0 && (unsigned)DrawMode == cMain[TCDM_BARINPUT]) {
                Vprints(MonAtk(Whom) + 2, 62, cMain[TCDM_WINDOW], cData[MonAtk(Whom)].CombatMode);
                Vputs(Whom - monNumEx + 2, 59, "Ä", cMain[TCDM_WINDOW]);
					 for (j = 0; j < totalChars; j++) {
                    if ((monNumEx > 0 && j >= charsOnScreen) || (monNumEx == 0 && j < charsOnScreen)) {
                        pChar[0] = ' ';
                        pChar[1] = ' ';
                        if ((j > Whom && j < MonAtk(Whom)) ||
                            (j > MonAtk(Whom) && j < Whom))
                            pChar[0] = 0xB3; /* ³ */
                        if (MonAtk(Whom) == j && Whom  > j) {
                            pChar[0] = 0xDA; /* Ú */
                            pChar[1] = 0x10; /*  */
								}
                        if (MonAtk(Whom) == j && Whom <  j) {
                            pChar[0] = 0xC0; /* À */
                            pChar[1] = 0x10; /*  */
                        }
                        if (MonAtk(Whom)  > j && Whom == j)
                            pChar[0] = 0xBF; /* ¿ */
                        if (MonAtk(Whom) <  j && Whom == j)
                            pChar[0] = 0xD9; /* Ù */
                        if (MonAtk(Whom) == j && Whom == j) {
                            pChar[0] = 0xC4; /* Ä */
                            pChar[1] = 0x10; /*  */
                        }
                        Vputs(j + 2 - monNumEx, 60, pChar, cMain[TCDM_WINDOW]);
						  }
                }
            }
            else {
                for (j = 0; j < totalChars; j++)
                    if ((monNumEx > 0 && j >= charsOnScreen) || (monNumEx == 0 && j < charsOnScreen))
                        Vputs(j + 2 + monNumEx, 59, "   ", cMain[TCDM_WINDOW]);
            }

        }
	 }
    else {
        Wactiv(cPlayer);
        Wprts(MsInt((Whom - charNumEx + 1)), 0, DrawMode, cData[Whom].NormalMode);
    }
    if (NewSheet == TRUE)
        Print_Sheet();
    if (RePrint == TRUE)
        Print_Data();
    NewSheet = 0;
}

/* 
   if combat and monster and display=monster and monster != blank print monster
	if combat and monster and display=character and character != blank print character
   if combat and character and display=monster and monster != blank print monster
   if combat and character and display=character and character != blank print character
*/
VOID Print_Sheet(NOARG)
{
    if (combatMode == TRUE) {
        if (combatStatus == MONSTER) {
            if (mData[MONNUM].DisplayMode == MONSTER) {
                Print_Monster_Sheet();
				}
            else {
                Print_Character_Sheet();
            }
        }
        else {
            if (cData[CHARNUM].DisplayMode == MONSTER) {
                Print_Monster_Sheet();
            }
            else {
                Print_Character_Sheet();
            }
        }
    }
	 else {
        Print_Character_Sheet();
    }
}

VOID Print_Data(NOARG)
{
    if (combatMode == TRUE) {
        if (combatStatus == MONSTER) {
            if (mData[MONNUM].DisplayMode == MONSTER) {
					 Print_Monster_Data(MONNUM);
            }
            else {
                Print_Character_Data(mData[MONNUM].AttackWho);
            }
        }
        else {
            if (cData[CHARNUM].DisplayMode == MONSTER) {
					 Print_Monster_Data(cData[CHARNUM].AttackWho);
            }
            else {
                Print_Character_Data(CHARNUM);
            }
        }
	 }
    else {
        Print_Character_Data(CHARNUM);
    }
}

VOID Print_Monster_Sheet(NOARG)
{
    IntT j;

	 Wactiv(cWindow);
    if (mData[MONNUM].Status == BLANK) {
        WclrWin(cAlt[TCDM_WINDOW]);
        if (loadLayout == YES)
            for (j = 0; (unsigned)j < VidDep - 4; j++)
                Wprts(MsByt(j), 0, cAlt[TCDM_WINDOW], layoutScreen[j]);
    }
    else {
		  for (j = 0; j < 37; j++)
            Wprts(monsScreen[j].mnRow, monsScreen[j].mnCol, cAlt[TCDM_WINDOW], monsScreen[j].mnText);
    }
}

VOID Print_Character_Sheet(NOARG)
{
    IntT j;

    Wactiv(cWindow);
    if (ChrSta(CHARNUM) == BLANK) {
        WclrWin(cAlt[TCDM_WINDOW]);
        if (loadLayout == YES)
				for (j = 0; (unsigned)j < VidDep - 4; j++)
                Wprts(MsByt(j), 0, cAlt[TCDM_WINDOW], layoutScreen[j]);
    }
	 else {
		  for (j = 0; j < 34; j++)
				Wprts(charScreen[j].chRow, charScreen[j].chCol, cAlt[TCDM_WINDOW], charScreen[j].chText);
	 }
}

VOID Print_Monster_Data(IntT cmNum)
{
	 if (MonSta(cmNum) != BLANK) {
		  Update_Data(CNAME);
		  Update_Data(ALIGNMENT);
		  Update_Data(SIZE);
		  Update_Data(MOVE);
		  Update_Data(FLY);
		  Update_Data(MOVECLASS);
		  Update_Data(SWIM);
		  Update_Data(BURROW);
		  Update_Data(WEB);
		  Update_Data(BASEAC);
		  Update_Data(WARMOR);
		  Update_Data(OTHER);
		  Update_Data(HITPOINTS);
		  Update_Data(HITDICE);
		  Update_Data(HITDICEADDS);
		  Update_Data(HITAC0);
		  Update_Data(DAMAGE);
		  Update_Data(MAGICADJ);
		  Update_Data(SPECIALATTACK);
		  Update_Data(SPECIALDEFENSE);
		  Update_Data(EXPERIENCE);
		  Update_Data(MITHRAL);
		  Update_Data(PLATINUM);
		  Update_Data(GOLD);
		  Update_Data(ELECTRUM);
		  Update_Data(SILVER);
		  Update_Data(COPPER);
		  Update_Data(REMARKS);
	 }
}

VOID Print_Character_Data(IntT cmNum)
{
	 if (ChrSta(cmNum) != BLANK) {
		  Wactiv(cWindow);
		  Update_Data(CNAME);
		  Update_Data(HITPOINTS);
		  Update_Data(ALIGNMENT);
		  Update_Data(PSIONIC);
		  Update_Data(RACE);
		  Update_Data(CLASS);
		  Update_Data(ARMORCLASS);
		  Update_Data(ARMOR);
		  Update_Data(SHIELD);
		  Update_Data(HELM);
		  Update_Data(SAVINGTHROWS);
		  Update_Data(LIGHT);
		  Update_Data(EXPERIENCE);
	 }
}

VOID Update_Data(IntT whichOne)
{
	 IntT j;
	 AtrT dataColor = 0;

	 if (combatMode == TRUE && combatStatus == MONSTER) {
		  if (mData[MONNUM].Status != BLANK) {
				Wactiv(cWindow);
				if (mData[MONNUM].Status == DEAD)
					 dataColor = cAlt[TCDM_DESELECT];
				else
					 dataColor = cAlt[TCDM_WINDOW];
				if (mData[MONNUM].Status == ALIVE && mData[MONNUM].HPDown >= mData[MONNUM].HitPoints)
					 dataColor = cAlt[TCDM_QUICK];
				switch (whichOne) {
					 case CNAME :
						  sprintf(Message, "%-25s", MonNam(MONNUM));
						  Wprts(0, 7, dataColor, Message);
						  break;
					 case ALIGNMENT :
						  sprintf(Message, "%-16s", alignment[MonAli(MONNUM)]);
						  Wprts( 2, 12, dataColor, Message);
						  break;
					 case SIZE :
						  sprintf(Message, "%c", MonSiz(MONNUM));
						  Wprts( 2, 36, dataColor, Message);
						  break;
					 case MOVE :
						  if (mData[MONNUM].Movement[0] == 99)
								sprintf(Message, "n/a");
						  else
								sprintf(Message, "%3d", mData[MONNUM].Movement[0]);
						  Wprts(3, 16, dataColor, Message);
						  break;
					 case FLY :
						  if (mData[MONNUM].Movement[1] == 99)
								sprintf(Message, "n/a");
						  else
								sprintf(Message, "%3d", mData[MONNUM].Movement[1]);
						  Wprts(3, 27, dataColor, Message);
						  break;
					 case MOVECLASS :
						  sprintf(Message, "%c", mData[MONNUM].Movement[2]);
						  Wprts(3, 36, dataColor, Message);
						  break;
					 case SWIM :
						  if (mData[MONNUM].Movement[3] == 99)
								sprintf(Message, "n/a");
						  else
								sprintf(Message, "%3d", mData[MONNUM].Movement[3]);
						  Wprts(4, 7, dataColor, Message);
						  break;
					 case BURROW :
						  if (mData[MONNUM].Movement[4] == 99)
								sprintf(Message, "n/a");
						  else
								sprintf(Message, "%3d", mData[MONNUM].Movement[4]);
						  Wprts(4, 20, dataColor, Message);
						  break;
					 case WEB :
						  if (mData[MONNUM].Movement[5] == 99)
								sprintf(Message, "n/a");
						  else
								sprintf(Message, "%3d", mData[MONNUM].Movement[5]);
						  Wprts(4, 30, dataColor, Message);
						  break;
					 case BASEAC :
						  if (mData[MONNUM].AClass[0] == 99)
								sprintf(Message, "n/a");
						  else
								sprintf(Message, "%3d", mData[MONNUM].AClass[0]);
						  Wprts(6, 10, dataColor, Message);
						  break;
					 case WARMOR :
						  if (mData[MONNUM].AClass[1] == 99)
								sprintf(Message, "n/a");
						  else
								sprintf(Message, "%3d", mData[MONNUM].AClass[1]);
						  Wprts(6, 23, dataColor, Message);
						  break;
					 case OTHER :
						  if (mData[MONNUM].AClass[2] == 99)
								sprintf(Message, "n/a");
						  else
								sprintf(Message, "%3d", mData[MONNUM].AClass[2]);
						  Wprts(6, 34, dataColor, Message);
						  break;
					 case HITPOINTS :
						  sprintf(Message, "%3d", mData[MONNUM].HitPoints);
						  Wprts(7, 13, dataColor, Message);
						  sprintf(Message, "%3d", mData[MONNUM].HPDown);
						  Wprts(7, 23, dataColor, Message);
						  sprintf(Message, "%4d", mData[MONNUM].HitPoints - mData[MONNUM].HPDown);
						  Wprts(7, 32, dataColor, Message);
						  break;
					 case HITDICE :
						  sprintf(Message, "%3d", MonHit(MONNUM));
						  Wprts(8, 11, dataColor, Message);
						  break;
					 case HITDICEADDS :
						  sprintf(Message, "%2d", MonHdm(MONNUM));
						  Wprts(8, 17, dataColor, Message);
						  break;
					 case HITAC0 :
						  sprintf(Message, "%2d", MonTht(MONNUM));
						  Wprts(8, 35, dataColor, Message);
						  break;
					 case DAMAGE :
						  sprintf(Message, "%d-%d/%d-%d/%d-%d", MonDam(MONNUM, 0),
							 MonDam(MONNUM, 1), MonDam(MONNUM, 2), MonDam(MONNUM, 3),
							 MonDam(MONNUM, 4), MonDam(MONNUM, 5));
						  Wprts(9, 9, dataColor, Message);
						  break;
					 case MAGICADJ :
						  if (MonMag(MONNUM) == 0)
								sprintf(Message, "nil");
						  else
								sprintf(Message, "%3d", MonMag(MONNUM));
						  Wprts(9, 33, dataColor, Message);
						  break;
					 case SPECIALATTACK :
						  sprintf(Message, "%-33s", MonSat(MONNUM));
						  Wprts(10, 5, dataColor, Message);
						  break;
					 case SPECIALDEFENSE :
						  sprintf(Message, "%-33s", MonSdf(MONNUM));
						  Wprts(11, 5, dataColor, Message);
						  break;
					 case EXPERIENCE :
						  sprintf(Message, "%-33s", mData[MONNUM].Experience);
						  Wprts(12, 5, dataColor, Message);
						  break;
					 case MITHRAL :
						  sprintf(Message, "%4d", MonMon(MONNUM, 0));
						  Wprts(14, 1, dataColor, Message);
						  break;
					 case PLATINUM :
						  sprintf(Message, "%4d", MonMon(MONNUM, 1));
						  Wprts(14, 7, dataColor, Message);
						  break;
					 case GOLD :
						  sprintf(Message, "%5d", MonMon(MONNUM, 2));
						  Wprts(14, 13, dataColor, Message);
						  break;
					 case ELECTRUM :
						  sprintf(Message, "%4d", MonMon(MONNUM, 3));
						  Wprts(14, 20, dataColor, Message);
						  break;
					 case SILVER :
						  sprintf(Message, "%4d", MonMon(MONNUM, 4));
						  Wprts(14, 26, dataColor, Message);
						  break;
					 case COPPER :
						  sprintf(Message, "%4d", MonMon(MONNUM, 5));
						  Wprts(14, 32, dataColor, Message);
						  break;
					 case REMARKS :
						  sprintf(Message, "%-35s", MonRem(MONNUM));
						  Wprts(15, 1, dataColor, Message);
						  break;
				}
		  }
	 }
	 else {
		  if (ChrSta(CHARNUM) != BLANK) {
				if (ChrSta(CHARNUM) == DEAD)
					 dataColor = cAlt[TCDM_DESELECT];
				else
					 dataColor = cAlt[TCDM_WINDOW];
				if (ChrSta(CHARNUM) == ALIVE && ChrHpd(CHARNUM) >= ChrHpt(CHARNUM))
					 dataColor = cAlt[TCDM_QUICK];
				switch (whichOne) {
					 case CNAME :
                    sprintf(Message, "%-25s", ChrChr(CHARNUM));
                    Wprts( 0,  7, dataColor, Message);
                    break;

					 case HITPOINTS :
                    sprintf(Message, "%3d", ChrHpt(CHARNUM));
                    Wprts( 2, 13, dataColor, Message);
                    sprintf(Message, "%3d", ChrHpd(CHARNUM));
                    Wprts( 2, 23, dataColor, Message);
                    sprintf(Message, "%4d", ChrHpt(CHARNUM) - ChrHpd(CHARNUM));
						  Wprts( 2, 32, dataColor, Message);
						  break;

					 case ALIGNMENT :
						  sprintf(Message, "%-16s", alignment[ChrAli(CHARNUM)]);
						  Wprts( 3, 12, dataColor, Message);
						  break;

                case PSIONIC :
                    sprintf(Message, "%c", cData[CHARNUM].Psionic);
                    Wprts( 3, 36, dataColor, Message);
						  break;

                case RACE :
                    sprintf(Message, "%-10s", race[ChrRac(CHARNUM)]);
                    Wprts( 4,  7, dataColor, Message);
                    break;

                case CLASS :
						  for (j = 0; j < 3; j++) {
                        sprintf(Message, "                                    ");
                        Wprts(MsByt(6 + j),  1, dataColor, Message);
                        if (cData[CHARNUM].Level[j] >= 0) {
                            switch (ClsRch(CHARNUM, j)) {
                                case WARRIOR :
                                    sprintf(Message, "%s %d %s", 
                                      groups[ClsRch(CHARNUM, j)], 
												  ClsLvl(CHARNUM, j),
                                      classWarrior[ClsCls(CHARNUM, j)]);
                                    break;

                                case WIZARD :
                                    sprintf(Message, "%s %d %s", 
                                      groups[ClsRch(CHARNUM, j)], 
                                      ClsLvl(CHARNUM, j), 
                                      classWizard[ClsCls(CHARNUM, j)]);
                                    break;
             
                                case PRIEST :
                                    sprintf(Message, "%s %d %s", 
                                      groups[ClsRch(CHARNUM, j)], 
                                      ClsLvl(CHARNUM, j), 
                                      classPriest[ClsCls(CHARNUM, j)]);
                                    break;
             
                                case ROGUE :
                                    sprintf(Message, "%s %d %s", 
                                      groups[ClsRch(CHARNUM, j)], 
                                      ClsLvl(CHARNUM, j), 
												  classRogue[ClsCls(CHARNUM, j)]);
                                    break;

                                case PSIONICIST : 
                                    sprintf(Message, "%s %d %s", 
                                      groups[ClsRch(CHARNUM, j)], 
                                      ClsLvl(CHARNUM, j), 
                                      classPsionicist[ClsCls(CHARNUM, j)]);
                                    break;
                            }
                            Wprts(MsByt(6 + j),  1, dataColor, Message);
                        }
                    }
                    break;

                case ARMORCLASS :
                    Adjust_Armor_Class();
                    j = cData[CHARNUM].AMagical + cData[CHARNUM].SMagical + cData[CHARNUM].HMagical;
                    sprintf(Message, "%3d", cData[CHARNUM].AClass - j);
                    Wprts(10,  5, dataColor, Message);
                    j -= cData[CHARNUM].SMagical;
                    sprintf(Message, "%3d", cData[CHARNUM].AClass + ((cData[CHARNUM].SPoints - cData[CHARNUM].SPtDown) > 0 ? 1 : 0) - dexterity[StaDex(CHARNUM) - 1] - j);
                    Wprts(10, 16, dataColor, Message);
                    sprintf(Message, "%3d", cData[CHARNUM].AClass + ((cData[CHARNUM].SPoints - cData[CHARNUM].SPtDown) > 0 ? 1 : 0) - j);
                    Wprts(10, 33, dataColor, Message);
                    break;

                case ARMOR :
                    sprintf(Message, "%-17s   %3d %3d", armorTypes[cData[CHARNUM].AType], 
                      cData[CHARNUM].APoints - cData[CHARNUM].APtDown, cData[CHARNUM].AMagical);
						  Wprts(11,  9, dataColor, Message);
                    break;

                case SHIELD :
                    sprintf(Message, "%-15s      %2d %3d", shieldTypes[cData[CHARNUM].SType], 
                      cData[CHARNUM].SPoints - cData[CHARNUM].SPtDown, cData[CHARNUM].SMagical);
                    Wprts(12,  9, dataColor, Message);
                    break;

                case HELM :
                    sprintf(Message, "%-11s          %2d %3d", helmTypes[cData[CHARNUM].HType], 
                      cData[CHARNUM].HPoints - cData[CHARNUM].HPtDown, cData[CHARNUM].HMagical);
                    Wprts(13,  9, dataColor, Message);
                    break;

                case SAVINGTHROWS :
                    sprintf(Message, "%2d", cData[CHARNUM].SThrows[0]);
                    Wprts(15, 14, dataColor, Message);
                    sprintf(Message, "%2d", ChrPoi(CHARNUM));
                    Wprts(15, 18, dataColor, Message);
						  sprintf(Message, "%2d", cData[CHARNUM].SThrows[3]);
                    Wprts(15, 31, dataColor, Message);
                    sprintf(Message, "%2d", ChrBth(CHARNUM));
                    Wprts(15, 35, dataColor, Message);
                    sprintf(Message, "%2d", cData[CHARNUM].SThrows[1]);
                    Wprts(16, 14, dataColor, Message);
                    sprintf(Message, "%2d", ChrPet(CHARNUM));
                    Wprts(16, 18, dataColor, Message);
                    sprintf(Message, "%2d", cData[CHARNUM].SThrows[4]);
                    Wprts(16, 31, dataColor, Message);
						  sprintf(Message, "%2d", ChrRsw(CHARNUM));
                    Wprts(16, 35, dataColor, Message);
                    sprintf(Message, "%2d", cData[CHARNUM].SThrows[2]);
                    Wprts(17, 14, dataColor, Message);
                    sprintf(Message, "%2d", ChrPar(CHARNUM));
                    Wprts(17, 18, dataColor, Message);
                    sprintf(Message, "%2d", cData[CHARNUM].SThrows[5]);
                    Wprts(17, 31, dataColor, Message);
                    sprintf(Message, "%2d", ChrSpl(CHARNUM));
                    Wprts(17, 35, dataColor, Message);
                    break;

                case LIGHT :
                    if (LitLft(CHARNUM) < 11 && LitLft(CHARNUM) > 0)
								dataColor = (unsigned)(dataColor | _BLINK);
						  sprintf(Message, "%-13s", light_Types[LitTyp(CHARNUM)]);
						  Wprts(19,  8, dataColor, Message);
						  sprintf(Message, "%3d", LitLft(CHARNUM));
						  Wprts(19, 34, dataColor, Message);
						  break;

					 case EXPERIENCE :
						  sprintf(Message, "%5d", cData[CHARNUM].Experience);
						  Wprts(20, 13, dataColor, Message);
                    break;
            }
        }
    }
}

VOID Display_Desc(NOARG)
{
    WndT dWindow;
    AtrT dataColor;
    IntT tmpBlt, tmpHbr;

    calcLiquorTolerance(&tmpBlt, &tmpHbr);

    if (ChrSta(CHARNUM) == BLANK)
        MessageWindow("No Character Defined");

    if (combatStatus == CHARACTER && ChrSta(CHARNUM) != BLANK) {
        if (combatMode == TRUE)
            dWindow = Wopen(2,  1, VidDep - 3, 40, BOX_SPA, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW]);
        else
				dWindow = Wopen(2, 41, VidDep - 3, 78, BOX_SPA, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW]);

        if (ChrSta(CHARNUM) == DEAD)
            dataColor = cAlt[TCDM_DESELECT];
        else
            dataColor = cAlt[TCDM_WINDOW];
        if (ChrSta(CHARNUM) == ALIVE && ChrHpd(CHARNUM) >= ChrHpt(CHARNUM))
            dataColor = cAlt[TCDM_QUICK];

        Wprts( 0,  1, cAlt[TCDM_WINDOW], "Age:");
        Wprts( 1,  1, cAlt[TCDM_WINDOW], "Sex:");
        Wprts( 2,  1, cAlt[TCDM_WINDOW], "Height:");
        Wprts( 3,  1, cAlt[TCDM_WINDOW], "Weight:");
        Wprts( 4,  1, cAlt[TCDM_WINDOW], "Eye Color:");
        Wprts( 5,  1, cAlt[TCDM_WINDOW], "Skin Color:");
        Wprts( 6,  1, cAlt[TCDM_WINDOW], "Hair Color:");
        Wprts( 7,  1, cAlt[TCDM_WINDOW], "Hair Length:");
        Wprts( 8,  1, cAlt[TCDM_WINDOW], "Beard Color:");
        Wprts( 9,  1, cAlt[TCDM_WINDOW], "Beard Length:");
        Wprts(10,  1, cAlt[TCDM_WINDOW], "Handedness:");
        Wprts(11,  1, cAlt[TCDM_WINDOW], "Base Liquor Tolerance:");
        Wprts(12,  1, cAlt[TCDM_WINDOW], "Hourly Burn Rate:");
        Wprts(13,  1, cAlt[TCDM_WINDOW], "General Appearance:");
        
		  sprintf(Message, "%d", DscAge(CHARNUM));
        Wprts( 0,  6, dataColor, Message);
        sprintf(Message, "%sale", DscSex(CHARNUM)=='M' ? "M" : "Fem");
        Wprts( 1,  6, dataColor, Message);
        sprintf(Message, "%d' %d\"", DscHgt(CHARNUM) / 12, DscHgt(CHARNUM) - (DscHgt(CHARNUM) / 12 * 12));
        Wprts( 2,  9, dataColor, Message);
        sprintf(Message, "%d", DscWgt(CHARNUM));
        Wprts( 3,  9, dataColor, Message);
        Wprts( 4, 12, dataColor, descEye[DscEye(CHARNUM)]);
        Wprts( 5, 13, dataColor, descSkin[DscSkn(CHARNUM)]);
        Wprts( 6, 13, dataColor, descHair[DscHrc(CHARNUM)]);
        Wprts( 7, 14, dataColor, descHLength[DscHrl(CHARNUM)]);
        if (DscSex(CHARNUM)=='M')
            Wprts( 8, 14, dataColor, descHair[DscBdc(CHARNUM)]);
        else
            Wprts( 8, 14, dataColor, "N/A");
        if (DscSex(CHARNUM)=='M')
            Wprts( 9, 15, dataColor, descBLength[DscBdl(CHARNUM)]);
        else
            Wprts( 9, 15, dataColor, "N/A");
        Wprts(10, 13, dataColor, descHand[DscHnd(CHARNUM)]);
        sprintf(Message, "%d", tmpBlt);
        Wprts(11, 24, dataColor, Message);
        sprintf(Message, "%d", tmpHbr);
		  Wprts(12, 19, dataColor, Message);
        if (DscGa0(CHARNUM) != -1)
            Wprts(14, 1, dataColor, descFace[DscGa0(CHARNUM)]);
        if (DscGa1(CHARNUM) != -1)
            Wprts(15, 1, dataColor, descFace[DscGa1(CHARNUM)]);
        if (DscGa2(CHARNUM) != -1)
            Wprts(16, 1, dataColor, descFace[DscGa2(CHARNUM)]);
        if (DscGa3(CHARNUM) != -1)
            Wprts(17, 1, dataColor, descFace[DscGa3(CHARNUM)]);
        if (DscGa4(CHARNUM) != -1)
            Wprts(18, 1, dataColor, descFace[DscGa4(CHARNUM)]);
        if (DscGa5(CHARNUM) != -1)
            Wprts(19, 1, dataColor, descFace[DscGa5(CHARNUM)]);
        if (DscGa6(CHARNUM) != -1)
            Wprts(20, 1, dataColor, descFace[DscGa6(CHARNUM)]);
        if (DscGa7(CHARNUM) != -1)
            Wprts(21, 1, dataColor, descFace[DscGa7(CHARNUM)]);

        KeyWait();
        
        Wactiv(dWindow);
        Wclose();
    }
}

