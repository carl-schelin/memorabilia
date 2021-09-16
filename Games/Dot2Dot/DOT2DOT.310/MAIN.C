/* []---------------------------------------------------------------------[] */
/* |         Main.c: Main calling routine and initialization code.         | */
/* |                                                                       | */
/* |               The Main.c source code and concepts are                 | */
/* |     Copyright (C) 1986-1996 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __MAIN__

#include <malloc.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <graph.h>

#include <time.h>

#include "dot2dot.h"
#include "mouse.h"

void process(void);

int exiting = FALSE;
char Message[80];

int main(int argc, char **argv)
{
    long size;
    int j;

    puts("Dot2Dot v3.1 - Copyright 1986-1996 by Carl Schelin, All rights reserved.");
    Initialize();
    for (j = 0; j <= argc; j++) {
        if (argv[j][0] == '?')
            Introduction();
        if (argv[j][0] == 'B')
            Blind = TRUE;
        if (argv[j][0] == 'b')
            Blind = TRUE;
    }
    Desktop();
    size = _imagesize(0, 0, 639, 479);
    newscreen = halloc(size, 1);
    if (newscreen != NULL)
        _getimage(0, 0, 639, 479, newscreen);
    if (Mouse) {
        MouPtr(ARROW);
        MouDrawPtr();
    }
    while (!exiting) {
        process();
    }
    if (Mouse)
        MouRemovePtr();
    if (newscreen != NULL)
        hfree(newscreen);
    _unregisterfonts();
    _setvideomode(_DEFAULTMODE);
    return 0;
}

void process(void)
{
    int c = 0;

    if (Mouse) {
        MouCharIn(&MouCRow, &MouCCol, &MouCBtn);
    }
    if (kbhit()) {
        c = getch();
        if (c == 0)
            c = getch();
    }
    
    if (MouLUp && LeftMouButton(MouCBtn)) {
        if (MouCCol > BrdBCol && MouCCol < BrdECol && MouCRow > BrdBRow && MouCRow < BrdERow)
            Click_Something(MouCCol, MouCRow);
        if (MouCCol > ConBCol && MouCCol < ConECol && MouCRow > ConBRow && MouCRow < ConERow)
            Check_Console(MouCCol, MouCRow);
    }
    if (RightMouButton(MouCBtn)) {
        if (MouCCol > BrdBCol && MouCCol < BrdECol && MouCRow > BrdBRow && MouCRow < BrdERow)
            Hot_Finish();
    }
    if (!LeftMouButton(MouCBtn))
        MouLUp = TRUE;

    if (NewPlr)
        Next_Player();

    if (!GameOver)
        End_Game();

    switch (c) {
        case Key_B   : Get_Name(0); Print_Message(Player[0].name); break;  /* Blue    */
        case Key_M   : Get_Name(1); Print_Message(Player[1].name); break;  /* Magenta */
        case Key_Y   : Get_Name(2); Print_Message(Player[2].name); break;  /* Yellow  */
        case Key_R   : Get_Name(3); Print_Message(Player[3].name); break;  /* Red     */
        case Key_G   : Get_Name(4); Print_Message(Player[4].name); break;  /* Green   */
        case Key_C   : Get_Name(5); Print_Message(Player[5].name); break;  /* Cyan    */
        case Key_S_R : Replay_Game(); break;
        case Key_H   :
        case Key_S_H : Display_Help(); break;
        case Key_S_B : 
            Save_Game();
            Blind = !Blind;
            Reset();
            Replay_Game();
            if (Blind)
                _setbkcolor(Player[WhosUp].background);
            else
                _setbkcolor(_BLACK);
            break;
        case Key_N   :
        case Key_S_N : Reset(); break;
        case Key_S_S : Save_Game(); break;
        case Key_Q   :
        case Key_S_Q : if (Are_You_Sure()) exiting = TRUE; break;
    }
}

