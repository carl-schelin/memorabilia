/* []---------------------------------------------------------------------[] */
/* |       FillBox.c: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |              The FillBox.c source code and concepts are               | */
/* |     Copyright (C) 1986-1996 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __FILLBOX__

#include <stdio.h>
#include <graph.h>

#include "dot2dot.h"
#include "mouse.h"

void Click_Something(int col, int row)
{
    int relrow = 0, relcol = 0;
    int postcol = 0, postrow = 0;

    if (WhosUp == -1) /* if game hasn't started yet, return to calling */
        return;

    relcol = col - BoxBCol;  /* relative col, divide by 28 */
    relrow = row - BoxBRow;  /* relative row... */

    if (relcol % 28 >= 0 && relcol % 28 < 4 && relrow % 28 > 3) {
        if (relcol % 28 == 1)
            postcol = col - 1;    /* one pixel before center line */
        if (relcol % 28 == 2)
            postcol = col - 2;    /* on the money */
        if (relcol % 28 == 3)
            postcol = col - 3;    /* one pixel after center line */
        postrow = row - relrow % 28 + 4;
        if (postrow + 24 < BrdERow)
            if (!Depressed(postcol, postrow, VERT))
                if (postcol > 0 && postrow > 0) {
                    sprintf(GameMoves[SaveIndex++], "201 %d %d", (col - BoxBCol) / 28, (row - BoxBCol) / 28);
                    NewPlr = TRUE;
                    MouRemovePtr();
                    DrawVert(postcol, postrow);
                    MouDrawPtr();
                    MouLUp = FALSE;
                    CheckFill(postcol, postrow, VERT);
                }
    }

    if (relrow % 28 >= 0 && relrow % 28 < 4 && relcol % 28 > 3) {
        if (relrow % 28 == 1)
            postrow = row - 1;    /* one pixel before center line */
        if (relrow % 28 == 2)
            postrow = row - 2;    /* on the money */
        if (relrow % 28 == 3)
            postrow = row - 3;    /* one pixel after center line */
        postcol = col - relcol % 28 + 4;
        if (postcol + 24 < BrdECol)
            if (!Depressed(postcol, postrow, HORZ))
                if (postcol > 0 && postrow > 0) {
                    sprintf(GameMoves[SaveIndex++], "200 %d %d", (col - BoxBCol) / 28, (row - BoxBCol) / 28);
                    NewPlr = TRUE;
                    MouRemovePtr();
                    DrawHorz(postcol, postrow);
                    MouDrawPtr();
                    MouLUp = FALSE;
                    CheckFill(postcol, postrow, HORZ);
                }
    }
}

int Depressed(int col, int row, int toggle)
{
    int yep = FALSE;

    MouRemovePtr(); /* just to make sure it's not picking up the mouse color */
    if (toggle) {
        if (_getpixel(col, row + 12) == GRAY && _getpixel(col + 4, row + 12) == BRIGHTWHITE)
            yep = TRUE;
    }
    else {
        if (_getpixel(col + 12, row) == GRAY && _getpixel(col + 12, row + 4) == BRIGHTWHITE)
            yep = TRUE;
    }
    MouDrawPtr();
    return yep;
}

void CheckFill(int col, int row, int toggle)
{
    if (toggle) {  /* vertical line to complete the box */
        if (
          Depressed(col - 24, row - 4, HORZ) && 
          Depressed(col - 28, row, VERT) && 
          Depressed(col - 24, row + 24, HORZ)) {
            MouRemovePtr();
            DrawTexture(col - 17, row + 7, Player[WhosUp].color, Player[WhosUp].color);
            FillBox(col - 22, row + 2, Player[WhosUp].color);
            MouDrawPtr();
            Player[WhosUp].score++;
            Update_Scores();
            NewPlr = FALSE;
        }
        if (
          Depressed(col + 4, row - 4, HORZ) &&
          Depressed(col + 28, row, VERT) &&
          Depressed(col + 4, row + 24, HORZ)) {
            MouRemovePtr();
            DrawTexture(col + 11, row + 7, Player[WhosUp].color, Player[WhosUp].color);
            FillBox(col + 6, row + 2, Player[WhosUp].color);
            MouDrawPtr();
            Player[WhosUp].score++;
            Update_Scores();
            NewPlr = FALSE;
        }
    }
    else {   /* horizontal line to complete box */
        if (
          Depressed(col - 4, row - 24, VERT) &&
          Depressed(col, row - 28, HORZ) &&
          Depressed(col + 24, row - 24, VERT)) {
            MouRemovePtr();
            DrawTexture(col + 7, row - 17, Player[WhosUp].color, Player[WhosUp].color);
            FillBox(col + 2, row - 22, Player[WhosUp].color);
            MouDrawPtr();
            Player[WhosUp].score++;
            Update_Scores();
            NewPlr = FALSE;
        }
        if (
          Depressed(col - 4, row + 4, VERT) &&
          Depressed(col, row + 28, HORZ) &&
          Depressed(col + 24, row + 4, VERT)) {
            MouRemovePtr();
            DrawTexture(col + 7, row + 11, Player[WhosUp].color, Player[WhosUp].color);
            FillBox(col + 2, row + 6, Player[WhosUp].color);
            MouDrawPtr();
            Player[WhosUp].score++;
            Update_Scores();
            NewPlr = FALSE;
        }
    }
}

void Hot_Finish(void)
{
    int relcol = 0, relrow = 0;
    int postcol = 0, postrow = 0;
    int number = 0;

    /* get the upper left post position and add four to get the first line */
    postcol = MouCCol - ((MouCCol - BoxBCol) % 28) + 4;
    postrow = MouCRow - ((MouCRow - BoxBRow) % 28);

    /*
       check to make sure three sides are drawn. adds one to a counter if it 
       is down. if it's not depressed, it keeps the col/row information to be 
       passed to the resolution routine but only if the counter is equal to 
       three
    */
    if (Depressed(postcol, postrow, HORZ)) {   /* check top of box */
        number++;
    }
    else {
        relcol = postcol + 1;
        relrow = postrow + 1;
    }
    if (Depressed(postcol + 24, postrow + 4, VERT)) {  /* check right side */
        number++;
    }
    else {
        relcol = postcol + 25;
        relrow = postrow + 5;
    }
    if (Depressed(postcol, postrow + 28, HORZ)) { /* check bottom of box */
        number++;
    }
    else {
        relcol = postcol + 1;
        relrow = postrow + 29;
    }
    if (Depressed(postcol - 4, postrow + 4, VERT)) { /* check left side */
        number++;
    }
    else {
        relcol = postcol - 3;
        relrow = postrow + 5;
    }
    if (number == 3)    /*  if ONLY! three are filled, depress and fill */
        Click_Something(relcol, relrow);
}

