/* []---------------------------------------------------------------------[] */
/* |       DrawBox.c: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |             The DrawBox.c source code and concepts are                | */
/* |     Copyright (C) 1986-1993 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __DRAWBOX__

#include <stdio.h>
#include <graphics.h>

#include "dot2dot.h"

void DrawBox(int col, int row)
{
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    setcolor(DARKGRAY);
    rectangle(col, row, col + 23, row + 23);
    setcolor(WHITE);
    line(col + 1, row + 1, col + 22, row + 1);
    line(col + 1, row + 1, col + 1, row + 22);
    line(col, row + 24, col + 24, row + 24);
    line(col + 24, row, col + 24, row + 24);
    DrawTexture(col + 7, row + 7, LIGHTGRAY, WHITE);
}

void DrawTexture(int col, int row, int color1, int color2)
{
    int j, k;
    int poly[8];

    setcolor(color1);
    setfillstyle(SOLID_FILL, color1);
    poly[0] = col     ; poly[1] = row     ;
    poly[2] = col + 10; poly[3] = row     ;
    poly[4] = col + 10; poly[5] = row + 10;
    poly[6] = col     ; poly[7] = row + 10;
    fillpoly(4, poly);
    setcolor(WHITE);
    line(col + 10, row + 1, col + 10, row + 10);
    line(col + 1, row + 10, col + 10, row + 10);
    setcolor(DARKGRAY);
    line(col, row, col + 10, row);
    line(col, row + 1, col, row + 10);
    for (j = 1; j < 8; j+=2)
        for (k = 1; k < 8; k+=2)
            putpixel(k + col, j + row, DARKGRAY);
    for (j = 2; j < 9; j+=4) {
        for (k = 2; k < 9; k+=2)
            putpixel(k + col, j + row, color2);
        for (k = 3; k < 8; k+=2)
            putpixel(k + col, j + row + 2, color2);
    }
}

void FillBox(int col, int row, int color)
{
    int j;

    setcolor(color);
    for (j = 0; j < 5; j++)
        rectangle(col + j, row + j, col - j + 20, row - j + 20);
}

void DrawPost(int col, int row)
{
    setcolor(WHITE);
    line(col + 1, row, col + 3, row);
    line(col, row + 1, col, row + 3);
    putpixel(col + 2, row + 2, WHITE);
    putpixel(col + 1, row + 3, WHITE);
    putpixel(col + 4, row + 1, WHITE);
    putpixel(col + 4, row + 2, DARKGRAY);
    putpixel(col + 4, row + 3, DARKGRAY);
    putpixel(col + 2, row + 4, DARKGRAY);
    putpixel(col + 3, row + 4, DARKGRAY);
}

void DrawHorz(int col, int row)
{
    setcolor(DARKGRAY);
    line(col, row + 4, col, row);                 /* top shadow */
    line(col + 1, row, col + 23, row);            /* left shadow */
    setcolor(WHITE);
    line(col + 24, row, col + 24, row + 4);       /* bottom face */
    line(col + 24, row + 4, col + 1, row + 4);    /* right face */
}

void DrawVert(int col, int row)
{
    setcolor(DARKGRAY);
    line(col, row + 23, col, row);
    line(col + 1, row, col + 4, row);
    setcolor(WHITE);
    line(col + 4, row + 1, col + 4, row + 24);
    line(col + 4, row + 24, col, row + 24);
}

