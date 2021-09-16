/* []---------------------------------------------------------------------[] */
/* |        Intro.c: Main calling routine and initialization code.         | */
/* |                                                                       | */
/* |              The Intro.c source code and concepts are                 | */
/* |     Copyright (C) 1986-1996 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __INTRO__

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graph.h>

#include "dot2dot.h"
#include "mouse.h"

#define INSTRUCT 41

void Initialize(void)
{
    struct videoconfig vc;

    if (!MouOpen())
        Mouse = FALSE;

    if (_registerfonts("BorTE.Fon") <= 0) {
        _outtext("BorTE.Fon must be in the current directory.");
        exit(EXIT_FAILURE);
    }
    if (_registerfonts("Script.Fon") <= 0) {
        _outtext("Script.Fon must be in the current directory.");
        exit(EXIT_FAILURE);
    }

    if (!_setvideomode(_VRES16COLOR))
        exit(EXIT_FAILURE);

    _getvideoconfig(&vc);

    GameWidth  = vc.numxpixels - 1;
    GameDepth = vc.numypixels - 1;

    if (NetCheck) {
        if (InitCom()) {
            NetActive = TRUE;
            Gather_Stats();
        }
    }

    if (Mouse)
        MouPtr(ARROW);

    if (GameWidth < 639 && GameDepth < 479) {
        _setvideomode(_DEFAULTMODE);
        printf("Sorry, Dot2Dot was written with standard VGA in mind.\n");
        exit(EXIT_FAILURE);
    }
    Reset_Data();
}

void Reset_Data(void)
{
    BrdBCol = 10;
    BrdBRow = 10;
    BrdECol = GameWidth - 170;
    BrdERow = GameDepth - 10;
    BrdWid  = BrdECol - BrdBCol;
    BrdDep  = BrdERow - BrdBRow;

    ConBCol = GameWidth - 160;
    ConBRow = 10;
    ConECol = GameWidth - 10;
    ConERow = GameDepth - 10;
    ConWid  = ConECol - ConBCol;
    ConDep  = BrdDep;

               /* 459 - 28 rem 28 / 2 + 10 = 29 */
    BoxBCol = (((BrdWid) % 28) / 2) + BrdBCol - 2;
    BoxBRow = (((BrdDep) % 28) / 2) + BrdBRow - 2;
    BoxECol = BrdWid / 28 * 28 + BoxBCol + 4;
    BoxERow = BrdDep / 28 * 28 + BoxBRow + 4;

    WhosUp = -1;  /* new game, no one's name is selected */
    SaveIndex = 0;
    GameOver = FALSE;

    Player[0].name[0] = '\0';
    Player[0].col = ConECol - 48;
    Player[0].row = ConBRow + 106;
    Player[0].color = BLUE;
    Player[0].background = _BLUE;
    Player[0].score = 0;
    Player[0].playing = FALSE;
    Player[0].remote = FALSE;
    Player[0].colname = 'b';

    Player[1].name[0] = '\0';
    Player[1].col = ConBCol + 20;
    Player[1].row = Player[0].row + 30;
    Player[1].color = MAGENTA;
    Player[1].background = _MAGENTA;
    Player[1].score = 0;
    Player[1].playing = FALSE;
    Player[1].remote = FALSE;
    Player[1].colname = 'm';

    Player[2].name[0] = '\0';
    Player[2].col = Player[0].col;
    Player[2].row = Player[1].row + 30;
    Player[2].color = YELLOW;
    Player[2].background = _YELLOW;
    Player[2].score = 0;
    Player[2].playing = FALSE;
    Player[2].remote = FALSE;
    Player[2].colname = 'y';

    Player[3].name[0] = '\0';
    Player[3].col = Player[1].col;
    Player[3].row = Player[2].row + 30;
    Player[3].color = RED;
    Player[3].background = _RED;
    Player[3].score = 0;
    Player[3].playing = FALSE;
    Player[3].remote = FALSE;
    Player[3].colname = 'r';

    Player[4].name[0] = '\0';
    Player[4].col = Player[0].col;
    Player[4].row = Player[3].row + 30;
    Player[4].color = GREEN;
    Player[4].background = _GREEN;
    Player[4].score = 0;
    Player[4].playing = FALSE;
    Player[4].remote = FALSE;
    Player[4].colname = 'g';

    Player[5].name[0] = '\0';
    Player[5].col = Player[1].col;
    Player[5].row = Player[4].row + 30;
    Player[5].color = CYAN;
    Player[5].background = _CYAN;
    Player[5].score = 0;
    Player[5].playing = FALSE;
    Player[5].remote = FALSE;
    Player[5].colname = 'c';

}

void Introduction(void)
{
    char *instruct[INSTRUCT] = {
        "Starting Dot2Dot: No moves can be made until a player has selected a color.",
        "  To select your color, use the mouse pointer and position it over one of the ",
        "  boxes (preferably a blank one) and press the left button. A dialog box is ",
        "  created to allow you to enter your name. You may type up to 8 characters.",
        "",
        "How to Play: Using the mouse pointer, press the left button and drag ",
        "  perpendicular between two posts, causing a line to be drawn. When you have ",
        "  four lines that complete a box, the box will be filled with your color and ",
        "  your score will increase by one. You may press the right mouse button while ",
        "  within a box with three sides completed and the fourth side will complete ",
        "  and the box will fill.",
        "",
        "Ending Dot2Dot: Whomever has the most squares at the end of Dot2Dot is the ",
        "  winner. You may press 'Q' to quit Dot2Dot at any time.",
        "",
        "About Dot2Dot: Dot2Dot is what I call the game. I don't recall that it ever ",
        "  had a real name. You would take a piece of paper and create a dot grid of ",
        "  any size on it. You and someone else would then alternately start drawing ",
        "  lines. If you completed a box, you put your initials in it and drew another ",
        "  line. The person who had the most boxes at the end won.",
        "",
        "History:",
        "  Block Buster v1.0 was written in Microsoft QuickBasic to demonstrate how to ",
        "    play to my oldest daughter. It used CGA and no mouse. You used the ",
        "    keyboard to move a crosshair around the grid.",
        "  Dot2Dot v2.0 was written using TurboC. I had the idea to have the game work ",
        "    across a network using NETBIOS. Using CB and _C Programmer's Guide to ",
        "    NETBIOS_ I tried to get it working. That didn't work well, but the game ",
        "    was written in C and used EGA.",
        "  Dot2Dot v3.0 was written using Borland C++ v3.1. I have been using TCP/IP ",
        "    and FTP's SDK and decided to rewrite it again. I have learned more about ",
        "    C and rewrote most of the 2.0 version and now have TCP/IP support using ",
        "    FTP's kernal. Now you should be able to play Dot2Dot from any point on ",
        "    the Globe where you are connected to the Internet.",
        "  Dot2Dot v3.1 was written using Microsoft C v6.0. I prefer to use Borland C++",
        "    but due to the price of getting the Borland libraries from FTP, I changed",
        "    to MSC.",
        "",
        "",
        "",
        "Dot2Dot is Copyright (C), 1986 - 1996 by Carl Schelin. All Rights Reserved."
    };
    int j;
    struct _fontinfo fi;
    long size;

    /*  Page 1 is the help screen. Draw the background logo and print the */
    /*  help text.  When done, flip to the other page for the completed   */
    /*  game board                                                        */
    _setbkcolor(_WHITE);
    _clearscreen(_GCLEARSCREEN);
    _setfont("t'Script'h60w40");
    _getfontinfo(&fi);
    _setcolor(GRAY);
    _moveto(70, 40);
    _outgtext(Dot2Dot);                           /* Dot 2 Dot logo */
    _moveto(GameWidth - 70 - _getgtextextent(Dot2Dot), GameDepth - 40 - fi.pixheight);
    _outgtext(Dot2Dot);
    _moveto((GameWidth / 2) - (_getgtextextent("2") / 2), (GameDepth / 2) - (fi.pixheight / 2));
    _outgtext("2");
    _setfont(SmallFont);
    _setcolor(RED);                                        /* red for help */
    for (j = 0; j < INSTRUCT; j++) {
        _moveto(15, (j*11)+15);
        _outgtext(instruct[j]);
    }
    _setcolor(BRIGHTWHITE);
    _moveto(GameWidth - _getgtextextent("Press any key when ready..."), GameDepth - 11);
    _outgtext("Press any key when ready...");
    Wait_For_It();
    if (Mouse)
        MouRemovePtr();
    size = _imagesize(0, 0, 639, 479);
    helpbuffer = halloc(size, 1);
    _getimage(0, 0, 639, 479, helpbuffer);
    Help = TRUE;
}

