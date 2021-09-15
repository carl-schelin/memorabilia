/* []---------------------------------------------------------------------[] */
/* |        Intro.c: Main calling routine and initialization code.         | */
/* |                                                                       | */
/* |              The Intro.c source code and concepts are                 | */
/* |     Copyright (C) 1986-1993 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __INTRO__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>

#include "dot2dot.h"
#include "mouse.h"

void Initialize(void)
{
    int graphDriver = VGA, graphMode = VGAHI;
    int errorcode;

    if (!MouOpen())
        Mouse = FALSE;

    registerbgifont(gothic_font);
    registerbgidriver(EGAVGA_driver);

    initgraph(&graphDriver, &graphMode, "");
    errorcode = graphresult();
    if (errorcode != grOk) {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        exit(EXIT_FAILURE);
    }

    if (NetCheck) {
    }

    if (Mouse)
        MouPtr(ARROW);
    if (Network)
        ;

    if (getmaxx() < 639 && getmaxy() < 479) {
        closegraph();
        printf("Sorry, Dot2Dot was written with standard VGA in mind.\n");
        exit(EXIT_FAILURE);
    }
    Reset_Data();
}

void Reset_Data(void)
{
    BoardWidth  = getmaxx();
    BoardHeight = getmaxy();

    BrdBCol = 10;
    BrdBRow = 10;
    BrdECol = BoardWidth - 170;
    BrdERow = BoardHeight - 10;
    BrdWid  = BrdECol - BrdBCol;
    BrdDep  = BrdERow - BrdBRow;

    ConBCol = BoardWidth - 160;
    ConBRow = 10;
    ConECol = BoardWidth - 10;
    ConERow = BoardHeight - 10;
    ConWid  = ConECol - ConBCol;
    ConDep  = BrdDep;

    BoxBCol = (((BrdWid - 28) % 28) / 2) + BrdBCol;
    BoxBRow = (((BrdDep - 28) % 28) / 2) + BrdBRow;
    BoxECol = BrdECol - BoxBCol;
    BoxERow = BrdERow - BoxBRow;

    WhosUp = -1;  /* new game, no one's name is selected */
    SaveIndex = 0;
    GameOver = FALSE;

    Player[0].name[0] = '\0';
    Player[0].col = ConECol - 48;
    Player[0].row = ConBRow + 106;
    Player[0].color = BLUE;
    Player[0].score = 0;
    Player[0].playing = FALSE;
    Player[0].remote = FALSE;
    Player[0].colname = 'b';

    Player[1].name[0] = '\0';
    Player[1].col = ConBCol + 20;
    Player[1].row = Player[0].row + 30;
    Player[1].color = MAGENTA;
    Player[1].score = 0;
    Player[1].playing = FALSE;
    Player[1].remote = FALSE;
    Player[1].colname = 'm';

    Player[2].name[0] = '\0';
    Player[2].col = Player[0].col;
    Player[2].row = Player[1].row + 30;
    Player[2].color = YELLOW;
    Player[2].score = 0;
    Player[2].playing = FALSE;
    Player[2].remote = FALSE;
    Player[2].colname = 'y';

    Player[3].name[0] = '\0';
    Player[3].col = Player[1].col;
    Player[3].row = Player[2].row + 30;
    Player[3].color = RED;
    Player[3].score = 0;
    Player[3].playing = FALSE;
    Player[3].remote = FALSE;
    Player[3].colname = 'r';

    Player[4].name[0] = '\0';
    Player[4].col = Player[0].col;
    Player[4].row = Player[3].row + 30;
    Player[4].color = GREEN;
    Player[4].score = 0;
    Player[4].playing = FALSE;
    Player[4].remote = FALSE;
    Player[4].colname = 'g';

    Player[5].name[0] = '\0';
    Player[5].col = Player[1].col;
    Player[5].row = Player[4].row + 30;
    Player[5].color = CYAN;
    Player[5].score = 0;
    Player[5].playing = FALSE;
    Player[5].remote = FALSE;
    Player[5].colname = 'c';

}

void Introduction(void)
{
    /*  Page 1 is the help screen. Draw the background logo and print the */
    /*  help text.  When done, flip to the other page for the completed   */
    /*  game board                                                        */
    setbkcolor(LIGHTGRAY);
    cleardevice();
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 0);             /* I LIKE gothic */
    setusercharsize(4, 1, 4, 1);                        /* BIG characters */
    setcolor(DARKGRAY);
    outtextxy(70, 40, Dot2Dot);                           /* Dot 2 Dot logo */
    outtextxy(BoardWidth - 70 - textwidth(Dot2Dot), BoardHeight - 40 - textheight(Dot2Dot), Dot2Dot);
    outtextxy((BoardWidth / 2) - (textwidth("2") / 2), (BoardHeight / 2) - (textheight("2") / 2), "2");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setusercharsize(1, 1, 1, 1);
    setcolor(RED);                                        /* red for help */
    outtextxy(15,  15, "Starting Dot2Dot: No moves can be made until a player has selected a color.");
    outtextxy(15,  25, "  To select your color, use the mouse pointer and position it over one of the ");
    outtextxy(15,  35, "  boxes (preferably a blank one) and press the left button. A dialog box is ");
    outtextxy(15,  45, "  created to allow your to enter your name. You may type up to 8 characters.");
    outtextxy(15,  65, "How to Play: Using the mouse pointer, press the left button and drag ");
    outtextxy(15,  75, "  perpendicular between two posts, causing a line to be drawn. When you have ");
    outtextxy(15,  85, "  four lines that complete a box, the box will be filled with your color and ");
    outtextxy(15,  95, "  your score will increase by one. You may press the right mouse button while ");
    outtextxy(15, 105, "  within a box with three sides completed and the fourth side will complete ");
    outtextxy(15, 115, "  and the box will fill.");
    outtextxy(15, 135, "Ending Dot2Dot: Whomever has the most squares at the end of Dot2Dot is the ");
    outtextxy(15, 145, "  winner. You may press 'Q' to quit Dot2Dot at any time.");
    outtextxy(15, 165, "About Dot2Dot: Dot2Dot is what I call the game. I don't recall that it ever ");
    outtextxy(15, 175, "  had a real name. You would take a piece of paper and create a dot grid of ");
    outtextxy(15, 185, "  any size on it. You and someone else would then alternately start drawing ");
    outtextxy(15, 195, "  lines. If you completed a box, you put your initials in it and drew another ");
    outtextxy(15, 205, "  line. The person who had the most boxes at the end won.");
    outtextxy(15, 225, "History:");
    outtextxy(15, 235, "  Block Buster v1.0 was written in Microsoft QuickBasic to demonstrate how to ");
    outtextxy(15, 245, "    play to my oldest daughter. It used CGA and no mouse. You used the");
    outtextxy(15, 255, "    keyboard to move a crosshair around the grid.");
    outtextxy(15, 275, "  Dot2Dot v2.0 was written using TurboC. I had the idea to have the game work ");
    outtextxy(15, 285, "    across a network using NETBIOS. Using CB and _C Programmer's Guide to ");
    outtextxy(15, 295, "    NETBIOS_ I tried to get it working. That didn't work well, but the game ");
    outtextxy(15, 305, "    was written in C and used EGA.");
    outtextxy(15, 325, "  Dot2Dot v3.0 was written using Borland C++ v3.1. I have been using TCP/IP ");
    outtextxy(15, 335, "    and FTP's SDK and decided to rewrite it again. I have learned more about ");
    outtextxy(15, 345, "    C and rewrote most of the 2.0 version and now have TCP/IP support using ");
    outtextxy(15, 355, "    FTP's kernal. Now you should be able to play Dot2Dot from any point on ");
    outtextxy(15, 365, "    the Globe where you are connected to the Internet.");
    outtextxy(15, BoardHeight - 25, "Dot2Dot is Copyright (C), 1986 - 1993 by Carl Schelin. All Rights Reserved.");
    setcolor(WHITE);
    outtextxy(525, BoardHeight - 10, "Press any key when ready...");
    Wait_For_It();
    if (Mouse)
        MouRemovePtr();
}

