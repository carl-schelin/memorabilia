/* []---------------------------------------------------------------------[] */
/* |        Button.c: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |              The Button.c source code and concepts are                | */
/* |     Copyright (C) 1986-1996 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __BUTTON__

#include <stdio.h>
#include <graph.h>

#include "dot2dot.h"
#include "mouse.h"

void Press_Button(int which_One)
{
    int which_Button = GameDepth - 45;

    if (Mouse) MouRemovePtr();
    if (which_One == 1) which_Button = GameDepth - 141;
    if (which_One == 2) which_Button = GameDepth - 109;
    if (which_One == 3) which_Button = GameDepth - 77;
    if (which_One == 4) which_Button = GameDepth - 45;
    /* remove darkgray, add white end position for former color */
    Draw_Pressed(499, which_Button, 609, which_Button + 20, GRAY, WHITE);
    Wait_For_Input();
    Draw_Release(499, which_Button, 609, which_Button + 20, GRAY, WHITE);
    if (Mouse) MouDrawPtr();
}

void Draw_Button(int tCol, int tRow, int bCol, int bRow, char *text, int tPos, int border, short sColor, short wColor, short tColor)
{
    int width;
    struct xycoord poly[4];

    _setlinestyle(0xFFFF);
    _setcolor(wColor);
    _rectangle(_GBORDER, tCol, tRow, bCol, bRow);
    poly[0].xcoord = tCol; poly[0].ycoord = tRow;
    poly[1].xcoord = bCol; poly[1].ycoord = tRow;
    poly[2].xcoord = bCol; poly[2].ycoord = bRow;
    poly[3].xcoord = tCol; poly[3].ycoord = bRow;
    _polygon(_GFILLINTERIOR, poly, 4);
    if (border == 0) 
        Draw_Release(tCol, tRow, bCol, bRow, sColor, wColor);
    else {
        Draw_Shadow(tCol, tRow, bCol, bRow, sColor);
        _setcolor(sColor);
        _setpixel(bCol + 1, bRow + 1);
    }
    _setcolor(tColor);
    width = _getgtextextent(text);
    _moveto(tCol + ((bCol - tCol - width) / 2), tPos);
    _outgtext(text);
    _setlinestyle(0xFFFF);
}

void Draw_Pressed(int tCol, int tRow, int bCol, int bRow, short bColor, short wColor)
{
    SaveBackground(tCol + 2, tRow + 2, bCol - 2, bRow - 2, BUTTON);
    RestoreBackground(tCol + 4, tRow + 3, BUTTON);
    _setcolor(wColor==WHITE ? WHITE : bColor);
    _moveto(tCol, bRow);
    _lineto(tCol, tRow);                 /*  Draw: บ            ณ   */
    _lineto(bCol, tRow);                 /*  Draw: ษออออออออออออธ   */
    _setcolor(wColor);
    _moveto(tCol, bRow);
    _lineto(bCol, bRow);                 /*  Draw: ิออออออออออออผ   */
    _lineto(bCol, tRow);                 /*  Draw: ณ            บ   */
}

void Draw_Release(int tCol, int tRow, int bCol, int bRow, short bColor, short wColor)
{
    SaveBackground(tCol + 4, tRow + 3, bCol -2 , bRow - 2, BUTTON);
    RestoreBackground(tCol + 2, tRow + 2, BUTTON);
    _setcolor(wColor==WHITE ? BRIGHTWHITE : wColor);
    _moveto(tCol, bRow);
    _lineto(tCol, tRow);               /*  Draw: บ            ณ  */
    _lineto(bCol, tRow);               /*  Draw: ษออออออออออออธ  */
    _setcolor(bColor);
    _moveto(tCol, bRow);
    _lineto(bCol, bRow);               /*  Draw: ิออออออออออออผ  */
    _lineto(bCol, tRow);               /*  Draw: ณ            บ  */
}

void Draw_Shadow(int tCol, int tRow, int bCol, int bRow, short bColor)
{
    int j;

    _setcolor(bColor);
    for (j = 1; j < 4; j++) {
        _moveto(tCol + 3, bRow + j);
        _lineto(bCol + j, bRow + j);
        _lineto(bCol + j, tRow + 3);
    }
}

