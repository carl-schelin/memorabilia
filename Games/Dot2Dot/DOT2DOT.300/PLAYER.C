/* []---------------------------------------------------------------------[] */
/* |        Player.c: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |              The Player.c source code and concepts are                | */
/* |     Copyright (C) 1986-1993 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __PLAYER__

#include <alloc.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <graphics.h>

#include "dot2dot.h"
#include "mouse.h"

void Get_Name(int getWho)
{
    void *buffer;
    unsigned size;
    int inpCh, keepCount = 0, j;
    int PlrSRow, PlrSCol;
    char tempName[20];

    if (Mouse) MouRemovePtr();

    PlrSRow = Player[getWho].row + 9;
    if (getWho % 2)    /* if there is a remainder, block is on left side */
        PlrSCol = Player[getWho].col + 34;
    else
        PlrSCol = Player[getWho].col - 90;

    setcolor(LIGHTGRAY);
    for (j = 0; j < 6; j++)
        rectangle(PlrSCol, PlrSRow + j, PlrSCol + 80, PlrSRow + 6 + j);

    if (!Replay) {
        size = imagesize(175, 150, 305, 205);
        buffer = malloc(size);
        getimage(175, 150, 305, 205, buffer);
        Draw_Button(176, 151, 299, 199, "Enter Name:", 159, 1, DARKGRAY, Player[getWho].color, Player[getWho].color==YELLOW ? DARKGRAY : WHITE);
        setcolor(Player[getWho].color==YELLOW ? DARKGRAY : WHITE);
        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
        line(204, 177, 268, 177);
        for (j = 204; j < 269; j+=8) {
            putpixel(j, 178, Player[getWho].color==YELLOW ? DARKGRAY : WHITE);
            putpixel(j, 187, Player[getWho].color==YELLOW ? DARKGRAY : WHITE);
        }
        line(204, 188, 268, 188);
        setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
        while (TRUE) {
            inpCh = getch();
            if (inpCh == 0) {
                inpCh = getch();
                inpCh = 0;
            }
            if (inpCh == 8 && keepCount > 0) {
                setcolor(Player[getWho].color);
                keepCount--;
                for (j = 180; j < 186; j++)
                    line(keepCount * 8 + 204, j, keepCount * 8 + 212, j);
                tempName[keepCount] = '\0';
                setcolor(Player[getWho].color==YELLOW ? DARKGRAY : WHITE);
            }
            if (inpCh == 13 || keepCount > 7) {
                tempName[keepCount] = '\0';
                strcpy(Player[getWho].name, tempName);
                break;
            }
            if (isalpha(inpCh)) {
                tempName[keepCount++] = inpCh;
                tempName[keepCount] = '\0';
                outtextxy(205, 179, tempName);
            }
        }
        putimage(175, 150, buffer, COPY_PUT);
        free(buffer);
    }
    if (strlen(Player[getWho].name) > 0)
        Player[getWho].playing = TRUE;
    else
        Player[getWho].playing = FALSE;
    if (WhosUp == -1)
        WhosUp = getWho;

    Draw_Name(getWho, TRUE, TRUE);  /* draw name shadow */
    if (WhosUp == getWho)
        Draw_Name(WhosUp, TRUE, FALSE);  /* draw name in color (your turn!) */
    else
        Draw_Name(getWho, FALSE, FALSE); /* draw name in white, not turn */
    sprintf(GameMoves[SaveIndex++], "%c%s", Player[getWho].colname, Player[getWho].name);
    if (!Player[getWho].playing)
        Next_Player();
    if (Mouse) MouDrawPtr();
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
}

