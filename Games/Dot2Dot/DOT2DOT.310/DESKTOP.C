/* []---------------------------------------------------------------------[] */
/* |       DeskTop.c: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |              The DeskTop.c source code and concepts are               | */
/* |     Copyright (C) 1986-1996 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __DESKTOP__

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <graph.h>

#include "dot2dot.h"

void Desktop(void)
{
    int j;

    _setcolor(WHITE);
    for (j = 0; j < GameDepth / 2 + 1; j++)
        _rectangle(_GBORDER, j, j, GameWidth - j, GameDepth - j);
    _setbkcolor(_BLACK);
    DrawConsole();
    DrawBoard();
}

void DrawBoard(void)
{
    DrawBorder(BrdBCol, BrdBRow, BrdECol, BrdERow, MAGENTA, LIGHTMAGENTA);
    DrawMatrix();
}

void DrawMatrix(void)
{
    int j, k;
    char _huge *boxbuf;
    long size;

    _setcolor(WHITE);
    _rectangle(_GBORDER, BoxBCol, BoxBRow, BoxECol, BoxERow);
    DrawPiece(BoxBCol + 4, BoxBRow + 4);
    FillBox(BoxBCol + 6, BoxBRow + 6, WHITE);
    size = _imagesize(BoxBCol + 4, BoxBRow + 4, BoxBCol + 28, BoxBRow + 28);
    boxbuf = halloc(size, 1);
    if (boxbuf != NULL) 
        _getimage(BoxBCol + 4, BoxBRow + 4, BoxBCol + 28, BoxBRow + 28, boxbuf);

    for (j = BoxBCol; j < BrdECol; j+=28) {
        for (k = BoxBRow; k < BoxERow; k+=28) {
            DrawPost(j, k);
            if (j <= BrdECol - 28)
                if (boxbuf != NULL)
                    _putimage(j + 4, k + 4, boxbuf, _GPSET);
                else
                    DrawPiece(j + 4, k + 4);
        }
        DrawPost(j, k);
    }
    if (boxbuf != NULL)
        hfree(boxbuf);
}

void DrawConsole(void)
{
    DrawBorder(ConBCol, ConBRow, ConECol, ConERow, BLUE, LIGHTBLUE);
    DrawLogo();
    DrawButtons();
    DrawNetwork();
}

void DrawLogo(void)
{
    int j, k;

    _setcolor(BRIGHTWHITE);
    for (j = ConBCol + 2; j < ConECol - 2; j+=2)
        for (k = ConBRow + 2; k < ConBRow + 85; k+=2)
            _setpixel(j, k);
    /* draw the shadow first */
    _setcolor(GRAY);
    _setfont("t'Script'h30w20");
    _moveto(ConBCol + 12, ConBRow + 12);
    _outgtext(Dot2Dot);
    _moveto(ConECol - _getgtextextent(Dot2Dot) - 10, ConBRow + 42);
    _outgtext(Dot2Dot);
    _moveto(ConBCol + ConWid / 2 - _getgtextextent("2") / 2 + 2, ConBRow + 26);
    _outgtext("2");
    _setfont(SmallFont);
    _moveto(ConBCol + ConWid / 2 - _getgtextextent(Author) / 2 + 2, ConBRow + 74);
    _outgtext(Author);

    /* then draw the actual logo text */
    _setcolor(RED);
    _setfont("t'Script'h30w20");
    _moveto(ConBCol + 10, ConBRow + 10);
    _outgtext(Dot2Dot);
    _moveto(ConECol - _getgtextextent(Dot2Dot) - 12, ConBRow + 40);
    _outgtext(Dot2Dot);
    _setcolor(BRIGHTWHITE);
    _moveto(ConBCol + ConWid / 2 - _getgtextextent("2") / 2, ConBRow + 24);
    _outgtext("2");
    _setcolor(YELLOW);
    _setfont(SmallFont);
    _moveto(ConBCol + ConWid / 2 - _getgtextextent(Author) / 2, ConBRow + 72);
    _outgtext(Author);

    _setcolor(GRAY);
    _moveto(ConBCol + 2, ConBRow + 85);
    _lineto(ConECol - 2, ConBRow + 85);
    _setcolor(BRIGHTWHITE);
    _moveto(ConBCol + 2, ConBRow + 86);
    _lineto(ConECol - 2, ConBRow + 86);
}

void DrawButtons(void)
{
    int j;

        /*  now create the buttons  */
/*    Draw_Button(499, GameDepth -  45, 609, GameDepth -  25,    "Quit", GameDepth -  38, 0, GRAY, WHITE, RED);
    Draw_Button(499, GameDepth -  77, 609, GameDepth -  57,     "New", GameDepth -  70, 0, GRAY, WHITE, RED);
    Draw_Button(499, GameDepth - 109, 609, GameDepth -  89, "Partner", GameDepth - 102, 0, GRAY, WHITE, (Network) ? RED : GRAY);
    Draw_Button(499, GameDepth - 141, 609, GameDepth - 121, "Monitor", GameDepth - 134, 0, GRAY, WHITE, (Network) ? RED : GRAY);*/

        /*  setup the character squares  */
    for (j = 0; j < 6; j++)
        DrawPlayers(Player[j].col, Player[j].row, Player[j].color);
}

void DrawPlayers(int col, int row, short color)
{
    DrawPiece(col, row);
    FillBox(col + 2, row + 2, color);
    DrawTexture(col + 7, row + 7, color, color);
}

void DrawBorder(int scol, int srow, int ecol, int erow, short color1, short color2)
{
    _setcolor(color1);
    _rectangle(_GBORDER, scol, srow, ecol - 1, erow - 1);
    _setcolor(color2);
    _moveto(scol + 1, srow + 1);
    _lineto(ecol - 2, srow + 1);
    _moveto(scol + 1, srow + 2);
    _lineto(scol + 1, erow - 2);
    _moveto(ecol    , srow    );
    _lineto(ecol    , erow    );
    _moveto(scol + 1, erow    );
    _lineto(ecol    , erow    );
}

void DrawNetwork(void)
{
    int j, k;

    _setcolor(GRAY);
    _moveto(ConBCol + 2, ConERow - 87);
    _lineto(ConECol - 2, ConERow - 87);
    _setcolor(BRIGHTWHITE);
    _moveto(ConBCol + 2, ConERow - 86);
    _lineto(ConECol - 2, ConERow - 86);

    NetRow = ConERow - 80;
    NetCol = ConBCol + 8;
    for (j = ConBCol + 2; j < ConECol; j+=2)
        for (k = ConERow - 85; k < ConERow - 2; k+=2)
            _setpixel(j, k);
    /* draw the shadow first */
    Lightning(ConECol, ConERow);
    CheckNetwork(FALSE);
    CheckServer(FALSE);
    CheckClient(FALSE);
}   

void CheckNetwork(int toggle)
{
    _setfont(SmallFont);
    CheckBox(ConBCol + 8, ConERow - 80, toggle);
    _setcolor(NetActive ? BLUE : GRAY);
    _moveto(ConBCol + 23, ConERow - 80);
    _outgtext(Netwrk);
}

void CheckServer(int toggle)
{
    _setfont(SmallFont);
    CheckBox(ConBCol + 8, ConERow - 60, toggle);
    _setcolor(toggle ? BLUE : GRAY);
    _moveto(ConBCol + 23, ConERow - 60);
    _outgtext(Servr);
}

void CheckClient(int toggle)
{
    _setfont(SmallFont);
    CheckBox(ConBCol + 8, ConERow - 40, toggle);
    _setcolor(toggle ? BLUE : GRAY);
    _moveto(ConBCol + 23, ConERow - 40);
    _outgtext(Clint);
    EditClient(toggle);
}

void EditClient(int toggle)
{
    DrawBox(ConBCol + 8, ConERow - 20, ConECol - 8, ConERow - 8, WHITE, BLUE);
    _setfont(SmallFont);
    _setcolor(toggle ? BLUE : GRAY);
    _moveto(ConBCol + 11, ConERow - 19);
    _outgtext(IPAddr);
}

void CheckBox(int col, int row, int toggle)
{
    DrawBox(col, row, col + 10, row + 10, WHITE, BLUE);
    if (toggle) {
        _moveto(col, row);
        _lineto(col + 10, row + 10);
        _moveto(col + 10, row);
        _lineto(col, row + 10);
    }
}

void DrawBox(int bcol, int brow, int ecol, int erow, int fcolor, int bcolor)
{
    struct xycoord poly[4];

    _setcolor(fcolor);
    poly[0].xcoord = bcol; poly[0].ycoord = brow;
    poly[1].xcoord = ecol; poly[1].ycoord = brow;
    poly[2].xcoord = ecol; poly[2].ycoord = erow;
    poly[3].xcoord = bcol; poly[3].ycoord = erow;
    _polygon(_GFILLINTERIOR, poly, 4);
    _setcolor(bcolor);
    _rectangle(_GBORDER, bcol, brow, ecol, erow);
}

void Lightning(int col, int row)
{
    int j;
    struct xycoord poly[6] = {
        {24, 77},   /* Pair 1 */
        {44, 49},   /* Pair 2 */
        {37, 52},   /* Pair 3 */
        {51, 26},   /* Pair 4 */
        {29, 57},   /* Pair 5 */
        {37, 54}    /* Pair 6 */
    };

    _setcolor(GRAY);
    for (j = 0; j < 6; j++) {
        poly[j].xcoord = col - poly[j].xcoord;
        poly[j].ycoord = row - poly[j].ycoord;
    }
    _polygon(_GFILLINTERIOR, poly, 6);
    for (j = 0; j < 6; j++) {
        poly[j].xcoord--;
        poly[j].ycoord--;
    }
    _setcolor(YELLOW);
    _polygon(_GFILLINTERIOR, poly, 6);
}

