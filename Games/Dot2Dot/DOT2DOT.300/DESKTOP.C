/* []---------------------------------------------------------------------[] */
/* |       DeskTop.c: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |              The DeskTop.c source code and concepts are               | */
/* |     Copyright (C) 1986-1993 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __DESKTOP__

#include <alloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

#include "dot2dot.h"

void Desktop(void)
{
    int j;

    setcolor(LIGHTGRAY);
    for (j = 0; j < BoardHeight / 2 + 1; j++)
        rectangle(j, j, BoardWidth - j, BoardHeight - j);
    setbkcolor(BLACK);
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
    void far *boxbuf;
    unsigned int size;

    setcolor(LIGHTGRAY);
    rectangle(BoxBCol, BoxBRow, BoxECol, BoxERow);
    DrawBox(BoxBCol + 4, BoxBRow + 4);
    FillBox(BoxBCol + 6, BoxBRow + 6, LIGHTGRAY);
    size = imagesize(BoxBCol + 4, BoxBRow + 4, BoxBCol + 28, BoxBRow + 28);
    if ((boxbuf = farmalloc(size)) == NULL) {
        closegraph();
        printf("Unable to allocate enough memory for %u bytes\n", size);
        exit(EXIT_FAILURE);
    }
    getimage(BoxBCol + 4, BoxBRow + 4, BoxBCol + 28, BoxBRow + 28, boxbuf);

    for (j = BoxBCol; j < BrdECol; j+=28) {
        for (k = BoxBRow; k < BoxERow; k+=28) {
            DrawPost(j, k);
            if (j <= BrdECol - 28)
                putimage(j + 4, k + 4, boxbuf, COPY_PUT);
        }
        DrawPost(j, k);
    }
    farfree(boxbuf);
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

    setcolor(WHITE);
    for (j = ConBCol + 2; j < ConECol - 2; j+=2)
        for (k = ConBRow + 2; k < ConBRow + 85; k+=2)
            putpixel(j, k, WHITE);
    /* draw the shadow first */
    setfillstyle(SOLID_FILL, DARKGRAY);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 0);
    setcolor(DARKGRAY);
    outtextxy(ConBCol + 12, ConBRow + 2, Dot2Dot);
    outtextxy(ConECol - textwidth(Dot2Dot) - 10, ConBRow + 32, Dot2Dot);
    outtextxy(ConBCol + ConWid / 2 - textwidth("2") / 2 + 2, ConBRow + 16, "2");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(ConBCol + ConWid / 2 - textwidth(Author) / 2 + 2, ConBRow + 75, Author);

    /* then draw the actual logo text */
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 0);
    setcolor(RED);
    outtextxy(ConBCol + 10, ConBRow, Dot2Dot);
    outtextxy(ConECol - textwidth(Dot2Dot) - 12, ConBRow + 30, Dot2Dot);
    setcolor(WHITE);
    outtextxy(ConBCol + ConWid / 2 - textwidth("2") / 2, ConBRow + 14, "2");
    setcolor(YELLOW);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(ConBCol + ConWid / 2 - textwidth(Author) / 2, ConBRow + 73, Author);

    setcolor(DARKGRAY);
    line(ConBCol + 2, ConBRow + 85, ConECol - 2, ConBRow + 85);
    setcolor(WHITE);
    line(ConBCol + 2, ConBRow + 86, ConECol - 2, ConBRow + 86);
}

void DrawButtons(void)
{
    int j;

        /*  now create the buttons  */
/*    Draw_Button(499, BoardHeight -  45, 609, BoardHeight -  25,    "Quit", BoardHeight -  38, 0, DARKGRAY, LIGHTGRAY, RED);
    Draw_Button(499, BoardHeight -  77, 609, BoardHeight -  57,     "New", BoardHeight -  70, 0, DARKGRAY, LIGHTGRAY, RED);
    Draw_Button(499, BoardHeight - 109, 609, BoardHeight -  89, "Partner", BoardHeight - 102, 0, DARKGRAY, LIGHTGRAY, (Network) ? RED : DARKGRAY);
    Draw_Button(499, BoardHeight - 141, 609, BoardHeight - 121, "Monitor", BoardHeight - 134, 0, DARKGRAY, LIGHTGRAY, (Network) ? RED : DARKGRAY);*/

        /*  setup the character squares  */
    for (j = 0; j < 6; j++)
        DrawPlayers(Player[j].col, Player[j].row, Player[j].color);
}

void DrawPlayers(int col, int row, int color)
{
    DrawBox(col, row);
    FillBox(col + 2, row + 2, color);
    DrawTexture(col + 7, row + 7, color, color);
}

void DrawBorder(int scol, int srow, int ecol, int erow, int color1, int color2)
{
    setcolor(color1);
    rectangle(scol, srow, ecol - 1, erow - 1);
    setcolor(color2);
    line(scol + 1, srow + 1, ecol - 2, srow + 1);
    line(scol + 1, srow + 2, scol + 1, erow - 2);
    line(ecol    , srow    , ecol    , erow    );
    line(scol + 1, erow    , ecol    , erow    );
}

void ReSize_Board(void)
{
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setcolor(MAGENTA);
/*    rectangle(20, 20, (Matrix_Size - 1) * 30 + 39, (Matrix_Size - 1) * 21 + 37);*/
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
}

void DrawNetwork(void)
{
    int j, k;

    setcolor(DARKGRAY);
    line(ConBCol + 2, ConERow - 87, ConECol - 2, ConERow - 87);
    setcolor(WHITE);
    line(ConBCol + 2, ConERow - 86, ConECol - 2, ConERow - 86);

    NetRow = ConERow - 80;
    NetCol = ConBCol + 8;
    for (j = ConBCol + 2; j < ConECol; j+=2)
        for (k = ConERow - 85; k < ConERow - 2; k+=2)
            putpixel(j, k, WHITE);
    /* draw the shadow first */
    Lightning(ConECol, ConERow);
    CheckNetwork(FALSE);
    CheckServer(FALSE);
    CheckClient(FALSE);
}   

void CheckNetwork(int toggle)
{
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 0);
    CheckBox(ConBCol + 8, ConERow - 80, toggle);
    setcolor(BLUE);
    outtextxy(ConBCol + 23, ConERow - 78, "Network");
}

void CheckServer(int toggle)
{
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 0);
    CheckBox(ConBCol + 8, ConERow - 60, toggle);
    setcolor(toggle ? BLUE : DARKGRAY);
    outtextxy(ConBCol + 23, ConERow - 58, "Server");
}

void CheckClient(int toggle)
{
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 0);
    CheckBox(ConBCol + 8, ConERow - 40, toggle);
    setcolor(toggle ? BLUE : DARKGRAY);
    outtextxy(ConBCol + 23, ConERow - 38, "Client");
    EditClient(toggle);
}

void EditClient(int toggle)
{
    int poly[9];

    setcolor(BLUE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    poly[0] = ConBCol + 8; poly[1] = ConERow - 20;
    poly[2] = ConECol - 8; poly[3] = ConERow - 20;
    poly[4] = ConECol - 8; poly[5] = ConERow -  8;
    poly[6] = ConBCol + 8; poly[7] = ConERow -  8;
    fillpoly(4, poly);
    rectangle(ConBCol + 8, ConERow - 20, ConECol - 8, ConERow - 8);
    setcolor(toggle ? BLUE : DARKGRAY);
    outtextxy(ConBCol + 11, ConERow - 17, "888.888.888.888");
}

void CheckBox(int col, int row, int toggle)
{
    int poly[9];

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    setcolor(BLUE);
    poly[0] = col     ; poly[1] = row     ;
    poly[2] = col + 10; poly[3] = row     ;
    poly[4] = col + 10; poly[5] = row + 10;
    poly[6] = col     ; poly[7] = row + 10;
    fillpoly(4, poly);
    rectangle(col, row, col + 10, row + 10);
    if (toggle) {
        line(col, row, col + 10, row + 10);
        line(col + 10, row, col, row + 10);
    }
}

void Lightning(int col, int row)
{
    int j;
    int poly[12] = {24, 77, 44, 49, 37, 52, 51, 26, 29, 57, 37, 54};
    /*              Pair 1/ Pair 2- Pair 3/ Pair 4 /Pair 5 -Pair 6 / */

    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, DARKGRAY);
    for (j = 0; j < 12; j+=2) {
        poly[j  ] = col - poly[j  ];
        poly[j+1] = row - poly[j+1];
    }
    fillpoly(6, poly);
    for (j = 0;j < 12; j++)
        poly[j]--;
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillpoly(6, poly);
}

