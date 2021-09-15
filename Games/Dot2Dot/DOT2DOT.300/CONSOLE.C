/* []---------------------------------------------------------------------[] */
/* |       Console.c: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |              The Console.c source code and concepts are               | */
/* |     Copyright (C) 1986-1993 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __CONSOLE__

#include <stdio.h>
#include <graphics.h>

#include "dot2dot.h"
#include "mouse.h"

void Check_Console(int col, int row)
{
    int j;
    
    if (row >= Player[0].row && row <= Player[5].row + 24)
        for (j = 0; j < 6; j++)
            if (Verify_Range(Player[j].col,      Player[j].row, 
                             Player[j].col + 24, Player[j].row + 24, col, row))
                Get_Name(j);
    if (row >= NetRow) {
        if (row >= NetRow && row < NetRow + 10 && col >= NetCol && col < NetCol + textwidth(Netwrk) + 15) {
            Network = !Network;
            MouRemovePtr();
            CheckNetwork(Network);
            if (!Network) {
                CheckClient(FALSE);
                CheckServer(FALSE);
            }
            else {
                setcolor(BLUE);
                outtextxy(ConBCol + 23, ConERow - 58, Servr);
                setcolor(BLUE);
                outtextxy(ConBCol + 23, ConERow - 38, Clint);
            }
            MouDrawPtr();
        }
        if (Network) {
            if (row >= NetRow + 20 && row < NetRow + 30 && col >= NetCol && NetCol + textwidth(Servr) + 15) {
                Server = !Server;
                MouRemovePtr();
                CheckServer(Server);
                MouDrawPtr();
            }
            if (row >= NetRow + 40 && row < NetRow + 50 && col >= NetCol && NetCol + textwidth(Clint) + 15) {
                Client = !Client;
                MouRemovePtr();
                CheckClient(Client);
                MouDrawPtr();
            }
        }
    }
}

