/* []---------------------------------------------------------------------[] */
/* |    Move.cpp: Keyboard movement routines while in the main loop.       | */
/* |                                                                       | */
/* |              The Move.cpp source code and concepts are                | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __MOVE__

#include <TcxlVid.H>

#pragma hdrstop
#include "..\Include\TCDM.H"

VOID MoveHome(NOARG);
VOID MoveEnd(NOARG);
VOID MovePgUp(NOARG);
VOID MovePgDn(NOARG);
VOID MoveUp(NOARG);
VOID MoveDown(NOARG);

GBL VOID Print_Char(AtrT DrawMode, IntT Whom);
GBL VOID Compose_Char_Data(IntT character);

VOID MoveHome(NOARG)
{
	/*  if current alive/dead and next blank, newscreen */
	/*  if current blank and next alive/dead, newscreen */
	RePrint = NewSheet = FALSE;
	if (combatMode == TRUE && combatStatus == MONSTER) {
		Print_Char(NORMAL, MONNUM);
		if (MonSta(MONNUM) != MonSta(monNumEx))
			NewSheet = TRUE;
		monNum = 0;
		RePrint = TRUE;
		Print_Char(REVERSE, MONNUM);
	}
	else {
		Print_Char(NORMAL, CHARNUM);
		if (ChrSta(CHARNUM) != ChrSta(charNumEx))
			NewSheet = TRUE;
		charNum = 0;
		RePrint = TRUE;
		Print_Char(REVERSE, CHARNUM);
	}
}

VOID MoveEnd(NOARG)
{
	IntT hold;

	NewSheet = RePrint = FALSE;
	if (combatMode == TRUE && combatStatus == MONSTER) {
		Print_Char(NORMAL, MONNUM);
		hold = MONNUM;
		monNum = charsOnScreen - 1;
		if (MONNUM > totalChars)
			monNum = totalChars - charsOnScreen;
		if (MonSta(MONNUM) != MonSta(hold))
			NewSheet = TRUE;
		RePrint = TRUE;
		Print_Char(REVERSE, MONNUM);
	}
	else {
		Print_Char(NORMAL, CHARNUM);
		hold = CHARNUM;
		charNum = charsOnScreen - 1;
		if (CHARNUM > totalChars)
			charNum = totalChars - charsOnScreen;
		if (ChrSta(CHARNUM) != ChrSta(hold))
			NewSheet = TRUE;
		RePrint = TRUE;
		Print_Char(REVERSE, CHARNUM);
	}
}

VOID MovePgUp(NOARG)
{
	IntT hold;
	IntT j;

	NewSheet = RePrint = FALSE;
	if (combatMode == TRUE && combatStatus == MONSTER) {
		if (monNumEx > 0) {
			hold = MONNUM;
			monNumEx = 0;
			for (j = 0; j < charsOnScreen; j++) {
				if (j + monNumEx <= totalChars) {
					Compose_Char_Data(j + monNumEx);
					Print_Char(NORMAL, j + monNumEx);
				}
			}
			NewSheet = RePrint = TRUE;
			Print_Char(REVERSE, MONNUM);
		}
	}
	else {
		if (charNumEx > 0) {
		hold = CHARNUM;
		charNumEx = 0;
		for (j = 0; j < charsOnScreen; j++) {
			if (j + charNumEx <= totalChars) {
				Compose_Char_Data(j + charNumEx);
				Print_Char(NORMAL, j + charNumEx);
			}
		}
		if (ChrSta(CHARNUM) != ChrSta(hold))
			NewSheet = TRUE;
		RePrint = TRUE;
		Print_Char(REVERSE, CHARNUM);
		}
	}
}

VOID MovePgDn(NOARG)
{
	IntT hold;
	IntT j;

	NewSheet = RePrint = FALSE;
	/* make sure we don't try to go to a second page if there is only
		enough space for CHARACTERS number of characters.
	*/
	if (VidDep - 3 <= CHARACTERS)
		if (combatMode == TRUE && combatStatus == MONSTER) {
			if (monNumEx == 0) {
				hold = MONNUM;
				monNumEx = charsOnScreen;
				for (j = 0; j < charsOnScreen; j++) {
					if (j + monNumEx <= totalChars) {
						Compose_Char_Data(j + monNumEx);
						Print_Char(NORMAL, j + monNumEx);
					}  /* fix here for not enough blank lines in 43 */
				}
				NewSheet = RePrint = TRUE;
				Print_Char(REVERSE, MONNUM);
			}
		}
		else {
			if (charNumEx == 0) {
				hold = CHARNUM;
				charNumEx = charsOnScreen;
				for (j = 0; j < charsOnScreen; j++) {
					if (j + charNumEx <= totalChars) {
						Compose_Char_Data(j + charNumEx);
						Print_Char(NORMAL, j + charNumEx);
					}
				}
				if (ChrSta(CHARNUM) != ChrSta(hold))
					NewSheet = TRUE;
				RePrint = TRUE;
				Print_Char(REVERSE, CHARNUM);
			}
		}
}

VOID MoveUp(NOARG)
{
	IntT hold;

	NewSheet = RePrint = FALSE;
	if (combatMode == TRUE && combatStatus == MONSTER) {
		 Print_Char(NORMAL, MONNUM);
		 hold = MONNUM;
		 if (--monNum < 0) {
			  monNum = charsOnScreen - 1;
			  if (MONNUM > totalChars)
					monNum = totalChars - charsOnScreen;
		 }
		 if (MonSta(MONNUM) != MonSta(hold))
			  NewSheet = TRUE;
		 RePrint = TRUE;
		 Print_Char(REVERSE, MONNUM);
	}
	else {
		 Print_Char(NORMAL, CHARNUM);
		 hold = CHARNUM;
		 if (--charNum < 0) {
			  charNum = charsOnScreen - 1;
			  if (CHARNUM > totalChars)
					charNum = totalChars - charsOnScreen;
		 }
		 if (ChrSta(CHARNUM) != ChrSta(hold))
			  NewSheet = TRUE;
		 RePrint = TRUE;
		 Print_Char(REVERSE, CHARNUM);
	}
}

VOID MoveDown(NOARG)
{
	IntT hold;

	NewSheet = RePrint = FALSE;
	if (combatMode == TRUE && combatStatus == MONSTER) {
		 Print_Char(NORMAL, MONNUM);
		 hold = MONNUM;
		 if ((++monNum >= charsOnScreen) || (MONNUM > totalChars))
			  monNum = 0;
		 if (MonSta(MONNUM) != MonSta(hold))
			  NewSheet = TRUE;
		 RePrint = TRUE;
		 Print_Char(REVERSE, MONNUM);
	}
	else {
		 Print_Char(NORMAL, CHARNUM);
		 hold = CHARNUM;
		 if ((++charNum >= charsOnScreen) || (CHARNUM > totalChars))
			  charNum = 0;
		 if (ChrSta(CHARNUM) != ChrSta(hold))
			  NewSheet = TRUE;
		 RePrint = TRUE;
		 Print_Char(REVERSE, CHARNUM);
	}
}

