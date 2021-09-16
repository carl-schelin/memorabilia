/* []---------------------------------------------------------------------[] */
/* |        Player.c: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |              The Player.c source code and concepts are                | */
/* |     Copyright (C) 1986-1996 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __PLAYER__

#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <graph.h>

#include "dot2dot.h"
#include "mouse.h"

void Get_Name(int getWho)
{
    int PlrBCol, PlrBRow, PlrECol, PlrERow, j;

    if (Mouse) MouRemovePtr();

    /* clear off the old character space from the top to the bottom */
    PlrBRow = Player[getWho].row;
    if (getWho % 2)    /* if there is a remainder, block is on left side */
        PlrBCol = Player[getWho].col + 34;
    else
        PlrBCol = Player[getWho].col - 90;
    _setcolor(WHITE);
    for (j = 0; j < 13; j++)
        _rectangle(_GBORDER, PlrBCol, PlrBRow + j, PlrBCol + 80, PlrBRow + 24 - j);

    if (!Replay) {
        PlrBCol = BrdWid / 2 - 61 + BrdBCol;  /* 176 */
        PlrECol = PlrBCol + 123;              /* 299 */
        PlrBRow = BrdDep / 2 - 24 + BrdBRow;  /* 151 */
        PlrERow = PlrBRow + 48;               /* 199 */

        SaveBackground(PlrBCol - 1, PlrBRow - 1, PlrECol + 6, PlrERow + 6, BACKGROUND);
        Draw_Button(PlrBCol, PlrBRow, PlrECol, PlrERow, "Enter Name:", PlrBRow + 7, 1, GRAY, Player[getWho].color, Player[getWho].color==YELLOW ? GRAY : BRIGHTWHITE);
        DrawBox(PlrBCol + 19, PlrBRow + 26, PlrECol - 19, PlrERow - 10, WHITE, Player[getWho].color==YELLOW ? GRAY : BRIGHTWHITE);
        Edit_Field(PlrBCol + 20, PlrBRow + 27, WHITE, Player[getWho].color==YELLOW ? GRAY : BRIGHTWHITE, Player[getWho].name, 9);
        RestoreBackground(PlrBCol - 1, PlrBRow - 1, BACKGROUND);
    }
    if (strlen(Player[getWho].name) > 0)
        Player[getWho].playing = TRUE;
    else
        Player[getWho].playing = FALSE;
    if (WhosUp == -1)  /* if a new game */
        WhosUp = getWho;  /* the first player in, is it! */

    Draw_Name(getWho, TRUE, TRUE);  /* draw name shadow */
    if (WhosUp == getWho)
        Draw_Name(WhosUp, TRUE, FALSE);  /* draw name in color (your turn!) */
    else
        Draw_Name(getWho, FALSE, FALSE); /* draw name in white, not turn */
    sprintf(GameMoves[SaveIndex++], "%c%s", Player[getWho].colname, Player[getWho].name);
    if (!Player[getWho].playing && WhosUp == getWho) /* pointer should move */
        Next_Player();
    if (Mouse) MouDrawPtr();
    _setlinestyle(0xFFFF);
}

