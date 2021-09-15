#define __GDIALOG__

#include <stdio.h>
#include <TcxlWin.H>
#include <TcxlInp.H>

#pragma hdrstop
#include "..\Include\TCDM.H"

VOID getFilename(NOARG);
VOID showShadow(WndT bottom, WndT right, AtrT sColor, IntT bLength, IntT rLength);

VOID getFilename(NOARG)
{
	 WndT dialogDlg;
	 WndT gameDlg, playerDlg, noteDlg;
	 WndT playerBtn, pseudonymBtn, viewBtn;
	 WndT okBtn, cancelBtn;
	 WndT gameBtmSdw, playerBtmSdw, noteBtmSdw;
	 WndT gameRsdSdw, playerRsdSdw, noteRsdSdw;
	 IntT xCol, xRow;
	 AtrT dlgColor, fldColor, sdwColor;


	 xCol = VidWid / 2 - 30;
	 xRow = VidDep / 2 - 7;

	 dlgColor = WHITE|_RED;
	 fldColor = WHITE|_BLUE;
	 sdwColor = BLACK|_RED;

	 dialogDlg = Wopen(xRow, xCol, xRow + 14, xCol + 60, BOX_SPA,
		  dlgColor, dlgColor);
	 Wprts( 1, 2, dlgColor, "Game:");
	 Wprts( 3, 2, dlgColor, "Players:");
	 Wprts( 8, 2, dlgColor, "Note:");

	 gameDlg = Wopen(xRow + 1, xCol + 8, xRow + 1, xCol + 54, BOX_SPA,
		  fldColor, fldColor);
	 gameBtmSdw = Wopen(xRow + 2, xCol + 9, xRow + 2, xCol + 55, BOX_SPA,
		  fldColor, dlgColor);
	 gameRsdSdw = Wopen(xRow + 1, xCol + 55, xRow + 1, xCol + 55, BOX_SPA,
		  fldColor, dlgColor);
	 showShadow(gameBtmSdw, gameRsdSdw, sdwColor, (xCol + 56) - (xCol + 9), (xRow + 1) - (xRow + 1));

	 playerDlg = Wopen(xRow + 3, xCol + 11, xRow + 7, xCol + 24, BOX_SNG,
		  fldColor, fldColor);
	 playerBtmSdw = Wopen(xRow + 8, xCol + 12, xRow + 8, xCol + 25, BOX_SPA,
		  fldColor, dlgColor);
	 playerRsdSdw = Wopen(xRow + 3, xCol + 25, xRow + 7, xCol + 25, BOX_SPA,
		  fldColor, dlgColor);
	 showShadow(playerBtmSdw, playerRsdSdw, sdwColor, (xCol + 26) - (xCol + 12), (xRow + 8) - (xRow + 3));

	 noteDlg = Wopen(xRow + 9, xCol + 2, xRow + 13, xCol + 40, BOX_SNG,
		  fldColor, fldColor);
	 noteBtmSdw = Wopen(xRow + 14, xCol + 3, xRow + 14, xCol + 41, BOX_SPA,
		  fldColor, dlgColor);
	 noteRsdSdw = Wopen(xRow + 9, xCol + 41, xRow + 13, xCol + 41, BOX_SPA,
		  fldColor, dlgColor);
	 showShadow(noteBtmSdw, noteRsdSdw, sdwColor, (xCol + 42) - (xCol + 3), (xRow + 14) - (xRow + 9));

	 playerBtn = Wopen(xRow + 3, xCol + 43, xRow + 3, xCol + 58, BOX_SPA,
		  fldColor, fldColor);
	 Wprts(0, 0, fldColor, " <  Players   > ");

	 pseudonymBtn = Wopen(xRow + 5, xCol + 43, xRow + 5, xCol + 58, BOX_SPA,
		  fldColor, fldColor);
	 Wprts(0, 0, fldColor, " < Pseudonyms > ");

	 viewBtn = Wopen(xRow + 7, xCol + 43, xRow + 7, xCol + 58, BOX_SPA,
		  fldColor, fldColor);
	 Wprts(0, 0, fldColor, " <    View    > ");

	 okBtn = Wopen(xRow + 11, xCol + 43, xRow + 11, xCol + 58, BOX_SPA,
		  fldColor, fldColor);
	 Wprts(0, 0, fldColor, " ®     Ok     ¯ ");

	 cancelBtn = Wopen(xRow + 13, xCol + 43, xRow + 13, xCol + 58, BOX_SPA,
		  fldColor, fldColor);
	 Wprts(0, 0, fldColor, " <   Cancel   > ");

	 KeyWait();

    Wactiv(cancelBtn);
    Wclose();
    Wactiv(okBtn);
    Wclose();
    Wactiv(viewBtn);
    Wclose();
    Wactiv(pseudonymBtn);
    Wclose();
    Wactiv(playerBtn);
    Wclose();
    Wactiv(gameBtmSdw);
    Wclose();
	 Wactiv(gameRsdSdw);
    Wclose();
    Wactiv(noteDlg);
    Wclose();
    Wactiv(playerBtmSdw);
    Wclose();
    Wactiv(playerRsdSdw);
    Wclose();
    Wactiv(playerDlg);
    Wclose();
	 Wactiv(noteBtmSdw);
    Wclose();
    Wactiv(noteRsdSdw);
    Wclose();
    Wactiv(gameDlg);
    Wclose();
    Wactiv(dialogDlg);
    Wclose();
}

VOID showShadow(WndT bottom, WndT right, AtrT sColor, IntT bLength, IntT rLength)
{
    IntT j;

	 Wactiv(bottom);
	 for (j = 0; j < bLength; j++)
		  Wprts(0, j, sColor, "ß");

	 Wactiv(right);
	 Wprts(0, 0, sColor, "Ü");
	 if (rLength > 0)
		  for (j = 1; j < rLength; j++)
				Wprts(j, 0, sColor, "Û");
}

