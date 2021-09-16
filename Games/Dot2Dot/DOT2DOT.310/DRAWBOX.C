/* []---------------------------------------------------------------------[] */
/* |      DrawPiece.c: Main calling routine and initialization code.       | */
/* |                                                                       | */
/* |            The DrawPiece.c source code and concepts are               | */
/* |     Copyright (C) 1986-1996 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __DRAWPIECE__

#include <stdio.h>
#include <graph.h>

#include "dot2dot.h"

void DrawPiece(int col, int row)
{
    _setlinestyle(0xFFFF);
    _setcolor(GRAY);
    _rectangle(_GBORDER, col, row, col + 23, row + 23);
    _setcolor(BRIGHTWHITE);
    _moveto(col + 1, row + 1);
    _lineto(col + 22, row + 1);
    _moveto(col + 1, row + 1);
    _lineto(col + 1, row + 22);
    _moveto(col, row + 24);
    _lineto(col + 24, row + 24);
    _moveto(col + 24, row);
    _lineto(col + 24, row + 24);
    DrawTexture(col + 7, row + 7, WHITE, BRIGHTWHITE);
}

void DrawTexture(int col, int row, short color1, short color2)
{
    int j, k;
    struct xycoord poly[4];

    _setcolor(color1);
    poly[0].xcoord = col     ; poly[0].ycoord = row     ;
    poly[1].xcoord = col + 10; poly[1].ycoord = row     ;
    poly[2].xcoord = col + 10; poly[2].ycoord = row + 10;
    poly[3].xcoord = col     ; poly[3].ycoord = row + 10;
    _polygon(_GFILLINTERIOR, poly, 4);
    _setcolor(BRIGHTWHITE);
    _moveto(col + 10, row + 1);
    _lineto(col + 10, row + 10);
    _moveto(col + 1, row + 10);
    _lineto(col + 10, row + 10);
    _setcolor(GRAY);
    _moveto(col, row);
    _lineto(col + 10, row);
    _moveto(col, row + 1);
    _lineto(col, row + 10);
    _setcolor(GRAY);
    for (j = 1; j < 8; j+=2)
        for (k = 1; k < 8; k+=2)
            _setpixel(k + col, j + row);
    _setcolor(color2);
    for (j = 2; j < 9; j+=4) {
        for (k = 2; k < 9; k+=2)
            _setpixel(k + col, j + row);
        for (k = 3; k < 8; k+=2)
            _setpixel(k + col, j + row + 2);
    }
}

void FillBox(int col, int row, short color)
{
    int j;

    _setcolor(color);
    for (j = 0; j < 5; j++)
        _rectangle(_GBORDER, col + j, row + j, col - j + 20, row - j + 20);
}

void DrawPost(int col, int row)
{
    _setcolor(BRIGHTWHITE);
    _moveto(col + 1, row);
    _lineto(col + 3, row);
    _moveto(col, row + 1);
    _lineto(col, row + 3);
    _setpixel(col + 2, row + 2);
    _setpixel(col + 1, row + 3);
    _setpixel(col + 4, row + 1);
    _setcolor(GRAY);
    _setpixel(col + 4, row + 2);
    _setpixel(col + 4, row + 3);
    _setpixel(col + 2, row + 4);
    _setpixel(col + 3, row + 4);
}

void DrawHorz(int col, int row)
{
    _setcolor(GRAY);
    _moveto(col     , row + 4);
    _lineto(col     , row    );        /* top shadow */
    _moveto(col +  1, row    );
    _lineto(col + 23, row    );        /* left shadow */
    _setcolor(BRIGHTWHITE);
    _moveto(col + 24, row    );
    _lineto(col + 24, row + 4);        /* bottom face */
    _moveto(col + 24, row + 4);
    _lineto(col +  1, row + 4);        /* right face */
    if (Blind) {
        _setcolor(BLACK);
        _rectangle(_GFILLINTERIOR, col + 1, row + 1, col + 23, row + 3);
    }
}

void DrawVert(int col, int row)
{
    _setcolor(GRAY);
    _moveto(col    , row + 23);
    _lineto(col    , row     );
    _moveto(col + 1, row     );
    _lineto(col + 4, row     );
    _setcolor(BRIGHTWHITE);
    _moveto(col + 4, row +  1);
    _lineto(col + 4, row + 24);
    _moveto(col + 4, row + 24);
    _lineto(col    , row + 24);
    if (Blind) {
        _setcolor(BLACK);
        _rectangle(_GFILLINTERIOR, col + 1, row + 1, col + 3, row + 23);
    }
}

