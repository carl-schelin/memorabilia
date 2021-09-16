/* []---------------------------------------------------------------------[] */
/* |       Utility.c: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |              The Utility.c source code and concepts are               | */
/* |     Copyright (C) 1986-1996 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __UTILITY__

#include <malloc.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graph.h>

#include "dot2dot.h"
#include "mouse.h"

void Print_Message(char *Message)
{
    int lenMsg;
    int TxtBCol, TxtBRow, TxtECol, TxtERow;

    if (Mouse) 
        MouRemovePtr();
    lenMsg = _getgtextextent(Message);
    TxtBCol = (BrdWid - lenMsg) / 2 - BrdBCol;
    TxtBRow = GameDepth / 2 - 25;
    TxtECol = TxtBCol + lenMsg + 32;
    TxtERow = TxtBRow + 50;
    SaveBackground(TxtBCol, TxtBRow, TxtECol, TxtERow, BACKGROUND);
    Draw_Button(TxtBCol + 1, TxtBRow + 1, TxtECol - 3, TxtERow - 3, Message, TxtBRow + 17, 1, GRAY, BLUE, BRIGHTWHITE);
    Wait_For_It();
    if (Mouse)
        MouRemovePtr();
    RestoreBackground(TxtBCol, TxtBRow, BACKGROUND);
    if (Mouse) 
        MouDrawPtr();
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
    if (Blind && !Replay)
        _setbkcolor(Player[WhosUp].background);

    NewPlr = FALSE;
}

/*  TRUE  TRUE = Draw current player name offset by two in DARKGRAY   */
/*  TRUE FALSE = Draw current player name in player color             */
/* FALSE FALSE = Draw current player name in WHITE (not players turn) */

void Draw_Name(int player, int toggle, int shadow)
{
    short color = BRIGHTWHITE;
    short PlrSCol, PlrSRow;
    int offset = 0;

    if (toggle)
        color = Player[player].color;
    if (shadow) {  /* clear off old debris before writing new stuff */
        offset = 2;
        color = GRAY;
    }

    PlrSRow = Player[player].row + 7 + offset;
    if (player % 2)    /* if there is a remainder, block is on left side */
        PlrSCol = Player[player].col + 34 + offset;
    else
        PlrSCol = Player[player].col - _getgtextextent(Player[player].name) - 10 + offset;

    _setcolor(color);
    _moveto(PlrSCol, PlrSRow);
    _outgtext(Player[player].name);
}

void Update_Scores(void)
{
    char temp[5];
    int start;

    DrawPlayers(Player[WhosUp].col, Player[WhosUp].row, Player[WhosUp].color);
    itoa(Player[WhosUp].score, temp, 10);
    start = 13 - _getgtextextent(temp) / 2;
    if (Player[WhosUp].score == 0)  /* blank score sheet rather than print 0 */
        temp[0] = '\0';
    _setcolor(Player[WhosUp].color == YELLOW ? RED : BRIGHTWHITE);
    _moveto(Player[WhosUp].col + start, Player[WhosUp].row + 7);
    _outgtext(temp);
}

void Wait_For_It(void)
{
    unsigned pRow, pCol, buttonVal;

    if (Mouse) MouDrawPtr();
    for (;;) {
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
    long y;
    unsigned seed = (unsigned)time(NULL);

    for (j = 0; j < 6; j++)
        k += Player[j].score;

    if (k >= ((BrdWid / 28) * (BrdDep / 28))) {
        if (MouCCol < (unsigned)BrdECol)
            MouRemovePtr();
        for (j = 0; j < 400; j++) {
            z = rand() % 6;
            y = Player[z].background;
            z = Player[z].color;
            DrawTexture((rand() % (BrdWid / 28)) * 28 + BoxBCol + 11, 
                        (rand() % (BrdDep / 28)) * 28 + BoxBRow + 11, z, z);
            if (Blind)
                _setbkcolor(y);    /* swapping background color! */
        }

        for (z = k = j = 0; j < 6; j++)
            if (Player[j].score > k) {
                k = Player[j].score;
                z = j;
            }

        if (Blind)
            _setbkcolor(Player[z].background);
        for (j = BoxBCol; j < BoxECol - 28; j+=28)
            for (k = BoxBRow; k < BoxERow - 28; k+=28)
                DrawTexture(j + 11, k + 11, Player[z].color, Player[z].color);
        if (MouCCol < (unsigned)BrdECol)
            MouDrawPtr();
        GameOver = TRUE;
    }
}

void SaveBackground(int bcol, int brow, int ecol, int erow, int toggle)
{
    long size;

    size = _imagesize(bcol, brow, ecol, erow);
    if (toggle) {
        bckbuffer = halloc(size, 1);
        if (bckbuffer != NULL)
            _getimage(bcol, brow, ecol, erow, bckbuffer);
    }
    else {
        btnbuffer = halloc(size, 1);
        if (btnbuffer != NULL) 
            _getimage(bcol, brow, ecol, erow, btnbuffer);
    }
}

void RestoreBackground(int bcol, int brow, int toggle)
{
    if (toggle) {
        if (bckbuffer != NULL) {
            _putimage(bcol, brow, bckbuffer, _GPSET);
            hfree(bckbuffer);
        }
        else {
            Save_Game();
            Reset();
            Replay_Game();
        }
    }
    else {
        if (btnbuffer != NULL) {
            _putimage(bcol, brow, btnbuffer, _GPSET);
            hfree(btnbuffer);
        }
        else {
            Save_Game();
            Reset();
            Replay_Game();
        }
    }
}

void Display_Help(void)
{
    long size;

    if (Mouse)
        MouRemovePtr();
    size = _imagesize(0, 0, 639, 479);
    scrnbuffer = halloc(size, 1);
    if (scrnbuffer != NULL)
        _getimage(0, 0, 639, 479, scrnbuffer);
    _setbkcolor(_WHITE);
    if (Help && helpbuffer != NULL) {
        _putimage(0, 0, helpbuffer, _GPSET);
        Wait_For_It();
        if (Mouse)
            MouRemovePtr();
    }
    else {
        Introduction();
    }
    if (scrnbuffer != NULL) {
        _putimage(0, 0, scrnbuffer, _GPSET);
        hfree(scrnbuffer);
    }
    else {
        Save_Game();
        Reset();
        Replay_Game();
    }
    _setbkcolor(_BLACK);
    if (Mouse)
        MouDrawPtr();
    if (Blind)
        _setbkcolor(Player[WhosUp].background);
}

void Reset(void)
{
    if (Mouse)
        MouRemovePtr();
    Reset_Data();
    if (newscreen != NULL)
        _putimage(0, 0, newscreen, _GPSET);
    else {
        DrawMatrix();
        Replay = TRUE;
        for (WhosUp = 0; WhosUp < 6; WhosUp++) {
            Update_Scores();
            Get_Name(WhosUp);
        }
        WhosUp = -1;
        Replay = FALSE;
        SaveIndex = 0;
    }
    if (Mouse)
        MouDrawPtr();
}

