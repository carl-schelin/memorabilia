/* []---------------------------------------------------------------------[] */
/* |        Button.c: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |              The Button.c source code and concepts are                | */
/* |     Copyright (C) 1986-1993 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __BUTTON__

#include <alloc.h>
#include <stdio.h>
#include <graphics.h>

#include "dot2dot.h"
#include "mouse.h"

void Press_Button(int which_One)
{
    int which_Button = BoardHeight - 45;

    if (Mouse) MouRemovePtr();
    if (which_One == 1) which_Button = BoardHeight - 141;
    if (which_One == 2) which_Button = BoardHeight - 109;
    if (which_One == 3) which_Button = BoardHeight - 77;
    if (which_One == 4) which_Button = BoardHeight - 45;
    /* remove darkgray, add white end position for former color */
    Draw_Pressed(499, which_Button, 609, which_Button + 20, DARKGRAY, LIGHTGRAY);
    Wait_For_Input();
    Draw_Release(499, which_Button, 609, which_Button + 20, DARKGRAY, LIGHTGRAY);
    if (Mouse) MouDrawPtr();
}

void Draw_Button(tCol, tRow, bCol, bRow, text, tPos, border, sColor, wColor, tColor)
int tCol;         /*  Column position for top left corner */
int tRow;         /*  Row position for top left corner */
int bCol;         /*  Column position for bottom right corner */
int bRow;         /*  Row position for bottom right corner */
char *text;       /*  Any text to be printed on the button */
int tPos;         /*  How far from top of button to print text */
int border;       /*  Draw shadow inside or outside */
int sColor;       /*  Button Shadow Color */
int wColor;       /*  Window Color */
int tColor;       /*  Text Color */
{
    int width;
    int poly[9];


    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setfillstyle(SOLID_FILL, wColor);
    setcolor(wColor);
    rectangle(tCol, tRow, bCol, bRow);
    poly[0] = tCol; poly[1] = tRow;
    poly[2] = bCol; poly[3] = tRow;
    poly[4] = bCol; poly[5] = bRow;
    poly[6] = tCol; poly[7] = bRow;
    fillpoly(4, poly);
    if (border == 0) 
        Draw_Release(tCol, tRow, bCol, bRow, sColor, wColor);
    else {
        Draw_Shadow(tCol, tRow, bCol, bRow, sColor);
        putpixel(bCol + 1, bRow + 1, sColor);
    }
    setcolor(tColor);
    width = textwidth(text);
    outtextxy(tCol + ((bCol - tCol - width) / 2), tPos, text);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
}

void Draw_Pressed(int tCol, int tRow, int bCol, int bRow, int bColor, int wColor)
{
    void *buffer;
    unsigned size;

    size = imagesize(tCol + 2, tRow + 2, bCol - 2, bRow - 2);
    buffer = malloc(size);
    getimage(tCol + 2, tRow + 2, bCol - 2, bRow - 2, buffer);
    putimage(tCol + 4, tRow + 3, buffer, COPY_PUT);

    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setcolor(wColor==LIGHTGRAY ? LIGHTGRAY : bColor);
    line(tCol, bRow, tCol, tRow);     /*  Draw: บ            ณ   */
    line(tCol, tRow, bCol, tRow);     /*  Draw: ษออออออออออออธ   */
    setcolor(wColor);
    line(tCol, bRow, bCol, bRow);     /*  Draw: ิออออออออออออผ   */
    line(bCol, bRow, bCol, tRow);     /*  Draw: ณ            บ   */

    free(buffer);
}

void Draw_Release(int tCol, int tRow, int bCol, int bRow, int bColor, int wColor)
{
    void *buffer;
    unsigned size;

    size = imagesize(tCol + 4, tRow + 3, bCol - 2, bRow - 2);
    buffer = malloc(size);
    getimage(tCol + 4, tRow + 3, bCol - 2, bRow - 2, buffer);
    putimage(tCol + 2, tRow + 2, buffer, COPY_PUT);

    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setcolor(wColor==LIGHTGRAY ? WHITE : wColor);
    line(tCol, bRow, tCol, tRow);     /*  Draw: บ            ณ  */
    line(tCol, tRow, bCol, tRow);     /*  Draw: ษออออออออออออธ  */
    setcolor(bColor);
    line(tCol, bRow, bCol, bRow);     /*  Draw: ิออออออออออออผ  */
    /*  put dot in to make demarkation line straight  */
    putpixel(tCol, bRow - 1, wColor==LIGHTGRAY ? WHITE : wColor);
    line(bCol, bRow, bCol, tRow);     /*  Draw: ณ            บ  */
    putpixel(bCol - 1, tRow, wColor==LIGHTGRAY ? WHITE : wColor);

    free(buffer);
}

void Draw_Shadow(int tCol, int tRow, int bCol, int bRow, int bColor)
{
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setcolor(bColor);
    line(tCol + 3, bRow + 3, bCol + 3, bRow + 3);
    line(bCol + 3, bRow + 3, bCol + 3, tRow + 3);
}

