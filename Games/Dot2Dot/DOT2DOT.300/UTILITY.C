/* []---------------------------------------------------------------------[] */
/* |       Utility.c: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |              The Utility.c source code and concepts are               | */
/* |     Copyright (C) 1986-1993 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __UTILITY__

#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>

#include "dot2dot.h"
#include "mouse.h"

void Print_Message(char *Message)
{
    void *buffer;
    unsigned size;
    int lenMsg, startWindow;

    if (Mouse) MouRemovePtr();
    lenMsg = textwidth(Message);
    startWindow = (469 - lenMsg) / 2;
    size = imagesize(startWindow, 150, startWindow + lenMsg + 15, 173);
    buffer = malloc(size);
    getimage(startWindow, 150, startWindow + lenMsg + 15, 173, buffer);
    Draw_Button(startWindow + 1, 150 + 1, startWindow + lenMsg + 11, 169, Message, 157, 1, DARKGRAY, BLUE, WHITE);
    Wait_For_It();
    putimage(startWindow, 150, buffer, COPY_PUT);
    free(buffer);
    if (Mouse) MouDrawPtr();
}

void Next_Player(void)
{
    int j;

    if (WhosUp == -1)
        return;

    Draw_Name(WhosUp, FALSE, FALSE);  /* FALSE turns it white */

    for (j = WhosUp + 1; j < 6; j++)
        if (Player[j].playing == TRUE) {
            WhosUp = j;
            break;
        }

    if (j == 6) /* if loop completed, start from beginning */
        for (j = 0; j < WhosUp + 1; j++)
            if (Player[j].playing == TRUE)
                WhosUp = j;

    Draw_Name(WhosUp, TRUE, FALSE);

    NewPlr = FALSE;
}

/*  TRUE  TRUE = Draw current player name offset by two in DARKGRAY   */
/*  TRUE FALSE = Draw current player name in player color             */
/* FALSE FALSE = Draw current player name in WHITE (not players turn) */

void Draw_Name(int player, int toggle, int shadow)
{
    int color = WHITE;
    int PlrSCol, PlrSRow;
    int offset = 0;

    if (toggle)
        color = Player[player].color;
    if (shadow) {  /* clear off old debris before writing new stuff */
        offset = 2;
        color = DARKGRAY;
    }

    PlrSRow = Player[player].row + 9 + offset;
    if (player % 2)    /* if there is a remainder, block is on left side */
        PlrSCol = Player[player].col + 34 + offset;
    else
        PlrSCol = Player[player].col - textwidth(Player[player].name) - 10 + offset;

    setcolor(color);
    outtextxy(PlrSCol, PlrSRow, Player[player].name);
}

void Update_Scores(void)
{
    char temp[5];
    int start;

    DrawPlayers(Player[WhosUp].col, Player[WhosUp].row, Player[WhosUp].color);
    itoa(Player[WhosUp].score, temp, 10);
    start = 13 - textwidth(temp) / 2;
    if (Player[WhosUp].score == 0)  /* blank score sheet rather than print 0 */
        temp[0] = '\0';
    setcolor(Player[WhosUp].color == YELLOW ? RED : WHITE);
    outtextxy(Player[WhosUp].col + start, Player[WhosUp].row + 9, temp);
}

void Wait_For_It(void)
{
    unsigned pRow, pCol, buttonVal;

    if (Mouse) MouDrawPtr();
    while (TRUE) {
        if (Mouse) {
            MouCharIn(&pRow, &pCol, &buttonVal);
            if (LeftMouButton(buttonVal))
                break;
        }
        if (kbhit()) {
            getch();
            break;
        }
    }
}

int Verify_Range(int tCol, int tRow, int bCol, int bRow, int pCol, int pRow)
{
    if ( pCol >= tCol && pCol <= bCol && pRow >= tRow && pRow <= bRow )
        return 1;
    return 0;
}

void Wait_For_Input(void)
{
    unsigned pRow, pCol, buttonVal;

    if (Mouse) {
        MouDrawPtr();
        if (inpCh == 0) {
            MouCharIn(&pRow, &pCol, &buttonVal);
            while (LeftMouButton(buttonVal)) MouCharIn(&pRow, &pCol, &buttonVal);
        }
        MouRemovePtr();
    }
}

void End_Game(void)
{
    int j, k = 0, z = 0;

    for (j = 0; j < 6; j++)
        k += Player[j].score;

    if (k >= ((BrdWid / 28) * (BrdDep / 28))) {
        if (MouCCol < BrdECol)
            MouRemovePtr();
        randomize();
        for (j = 0; j < 400; j++) {
            z = Player[random(6)].color;
            DrawTexture(random(BrdWid / 28) * 28 + BoxBCol + 11, 
                        random(BrdDep / 28) * 28 + BoxBRow + 11, z, z);
        }

        for (z = k = j = 0; j < 6; j++)
            if (Player[j].score > k) {
                k = Player[j].score;
                z = j;
            }

        for (j = BoxBCol; j < BoxECol; j+=28)
            for (k = BoxBRow; k < BoxERow; k+=28)
                DrawTexture(j + 11, k + 11, Player[z].color, Player[z].color);
        if (MouCCol < BrdECol)
            MouDrawPtr();
        GameOver = TRUE;
    }
}

