/* []---------------------------------------------------------------------[] */
/* |         Main.c: Main calling routine and initialization code.         | */
/* |                                                                       | */
/* |               The Main.c source code and concepts are                 | */
/* |     Copyright (C) 1986-1993 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __MAIN__

#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

#include <time.h>

#include "dot2dot.h"
#include "mouse.h"

void process(void);

int exiting = FALSE;
char Message[80];

int main(int argc, char **argv)
{
    puts("Dot2Dot v3.0 - Copyright 1986-1993 by Carl Schelin, All rights reserved.");
    setpalette(0, 0);
    Initialize();
    if (argc == 1)
        Introduction();
    Desktop();
    if (Mouse) {
        MouPtr(ARROW);
        MouDrawPtr();
    }
    while (!exiting) {
        process();
    }
    if (Mouse)
        MouRemovePtr();
    closegraph();
    return 0;
}

void process(void)
{
    int c;

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
        case Key_S_C : Introduction(); Desktop(); break;
        case Key_B   : Get_Name(0); break;
        case Key_M   : Get_Name(1); break;
        case Key_Y   : Get_Name(2); break;
        case Key_R   : Get_Name(3); break;
        case Key_G   : Get_Name(4); break;
        case Key_C   : Get_Name(5); break;
        case Key_S_R : Replay_Game(); break;
        case Key_S   :
        case Key_N   :
        case Key_S_N : 
            DrawMatrix();
            Reset_Data();
            Replay = TRUE;
            for (c = 0; c < 6; c++) {
                Get_Name(c);
                WhosUp = c;
                Update_Scores();
            }
            WhosUp = -1;
            Replay = FALSE;
            SaveIndex = 0;
            c = Key_N;
            break;
        case Key_S_S : Save_Game(); break;
        case Key_Q   :
        case Key_S_Q : if (Are_You_Sure()) exiting = TRUE; break;
    }
}

