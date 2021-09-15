/* []---------------------------------------------------------------------[] */
/* |        Replay.c: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |              The Replay.c source code and concepts are                | */
/* |     Copyright (C) 1986-1993 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __REPLAY__

#include <stdio.h>
#include <string.h>

#include "dot2dot.h"
#include "mouse.h"

void Replay_Game(void)
{
    FILE *input;
    char temp[60];
    int pCol, pRow, j;

    Replay = TRUE;
    if (SaveIndex == 0) {
        MouRemovePtr();
        if ((input = fopen("Dot2Dot.Dat", "r")) != NULL)
            while (!feof(input)) {
                fgets(temp, 59, input);
                temp[strlen(temp) - 1] = '\0';
                if (temp[0] == 's') {
                    sscanf(temp + 1, "%d %d", &pCol, &pRow);
                    Click_Something(pCol, pRow);
                    if (NewPlr)
                        Next_Player();
                }
                else
                    for (j = 0; j < 6; j++)
                        if (temp[0] == Player[j].colname) {
                            if (strlen(temp) > 1) /* there is a player name */
                                strcpy(Player[j].name, temp + 1);
                            else {
                                Player[j].name[0] = '\0';
                                if (WhosUp == j)
                                    Next_Player();
                            }
                            Get_Name(j);
                            break;
                        }
            }
        MouDrawPtr();
    }
    Replay = FALSE;
}

void Save_Game(void)
{
    FILE *output;
    int j;

    if ((output = fopen("Dot2Dot.Dat", "w")) != NULL) {
        for (j = 0; j < SaveIndex; j++)
            fprintf(output, "%s\n", GameMoves[j]);
        fclose(output);
    }
}

