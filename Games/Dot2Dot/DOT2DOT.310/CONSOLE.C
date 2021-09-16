/* []---------------------------------------------------------------------[] */
/* |       Console.c: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |              The Console.c source code and concepts are               | */
/* |     Copyright (C) 1986-1996 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __CONSOLE__

#include <stdio.h>
#include <graph.h>

#include "dot2dot.h"
#include "mouse.h"

void Check_Console(int col, int row)
{
    int j;

    if (Verify_Range(ConBCol + 66, ConBRow + 26, ConECol - 66, ConBRow + 46, col, row))
        Display_Help();
    if (row >= Player[0].row && row <= Player[5].row + 24)
        for (j = 0; j < 6; j++)
            if (Verify_Range(Player[j].col,      Player[j].row, 
                             Player[j].col + 24, Player[j].row + 24, col, row))
                Get_Name(j);
    if (row >= NetRow && NetActive) {    /* if we're not in the net box, don't even check */
        if (Verify_Range(NetCol, NetRow, NetCol + _getgtextextent(Netwrk) + 15, NetRow + 10, col, row)) {
            Network = !Network;
            MouRemovePtr();
            CheckNetwork(Network);
            if (!Network) {
                CheckClient(FALSE);
                CheckServer(FALSE);
            }
            else {
                if (Server) {
                    CheckServer(TRUE);
                }
                else {
                    _setcolor(BLUE);
                    _moveto(ConBCol + 23, ConERow - 60);
                    _outgtext(Servr);
                }
                if (Client) {
                    CheckClient(TRUE);
                }
                else {
                    _setcolor(BLUE);
                    _moveto(ConBCol + 23, ConERow - 40);
                    _outgtext(Clint);
                }
            }
            MouDrawPtr();
        }
        if (Network) {
            if (Verify_Range(NetCol, NetRow + 20, NetCol + _getgtextextent(Servr) + 15, NetRow + 30, col, row)) {
                Server = !Server;
                MouRemovePtr();
                CheckServer(Server);
                if (Server && Client) {
                    Client = FALSE;
                    CheckClient(Client);
                }
                MouDrawPtr();
            }
            if (Verify_Range(NetCol, NetRow + 40, NetCol + _getgtextextent(Clint) + 15, NetRow + 50, col, row)) {
                Client = !Client;
                MouRemovePtr();
                CheckClient(Client);
                if (Server && Client) {
                    Server = FALSE;
                    CheckServer(Server);
                }
                MouDrawPtr();
            }
            if (Verify_Range(ConBCol + 8, ConERow - 20, ConECol - 8, ConERow - 8, col, row)) {
                if (!Client) {
                    Client = TRUE;
                    CheckClient(Client);
                }
                if (Server) {
                    Server = FALSE;
                    CheckServer(Server);
                }
                Edit_Field(ConBCol + 11, ConERow - 19, WHITE, BLUE, IPAddr, 15);
            }
        }
    }
}

