/* []---------------------------------------------------------------------[] */
/* |       QDialog.c: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |              The QDialog.c source code and concepts are               | */
/* |     Copyright (C) 1986-1996 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __QDIALOG__

#include <conio.h>
#include <stdio.h>
#include <graph.h>

#include "dot2dot.h"
#include "mouse.h"

unsigned int QueBCol, QueBRow, QueECol, QueERow;

int Are_You_Sure(void)
{
    unsigned pRow, pCol, buttonVal;
    int with_Null, ret_Val = 0, exiting = FALSE;

    QueBCol = 176;
    QueBRow = 151;
    QueECol = 299;
    QueERow = 199;
    if (Mouse)
        MouRemovePtr();
    SaveBackground(QueBCol - 1, QueBRow - 1, QueECol + 6, QueERow + 6, BACKGROUND);
    Draw_Button(QueBCol, QueBRow, QueECol, QueERow, "Are you sure?", QueBRow + 7, 1, GRAY, RED, BRIGHTWHITE);
    Draw_Button(QueBCol + 11, QueBRow + 25, QueBCol + 56, QueBRow + 40, "Yes", QueBRow + 27, 0, GRAY, WHITE, RED);
    Draw_Button(QueECol - 57, QueBRow + 25, QueECol - 12, QueBRow + 40,  "No", QueBRow + 27, 0, GRAY, WHITE, RED);
    if (Mouse) {
        MouDrawPtr();
        MouSetPtrPos(QueBRow + 36, QueBCol + 33);  /* position on Yes button */
    }
    while (!exiting) {
        if (Mouse) 
            MouCharIn(&pRow, &pCol, &buttonVal);
        if (kbhit()) {
            inpCh = getch();
            if (inpCh == 0)
                with_Null = getch();
            else
                with_Null = 0;
            switch (with_Null) {
                case 'K' :     /* Left  */
                    if (pCol == QueECol - 33)
                        pCol = QueBCol + 33;
                    break;
                case 'M' :     /* Right */
                    if (pCol == QueBCol + 33)
                        pCol = QueECol - 33;
                    break;
            }
            switch (inpCh) {
                case 'y' :
                case 'Y' : ret_Val = 1; exiting = TRUE; inpCh = 0; break;
                case 'n' :
                case 'N' : ret_Val = 0; exiting = TRUE; inpCh = 0; break;
            }
            if (Mouse) 
                MouSetPtrPos(pRow, pCol);
        }
        else
            inpCh = 0;  /* set to 0 just in case (no wild data) */
        if (LeftMouButton(buttonVal) || inpCh == 13) {
            if (Verify_Range(QueBCol + 11, QueBRow + 25, QueBCol + 56, QueBRow + 40, pCol, pRow)) {
                Push_Sure_Button(1);
                ret_Val = 1;
                exiting = TRUE;
            }                
            if (Verify_Range(QueECol - 57, QueBRow + 25, QueECol - 12, QueBRow + 40, pCol, pRow)) {
                Push_Sure_Button(2);
                ret_Val = 0;
                exiting = TRUE;
            }
        }
        if (inpCh == 27) {
            Push_Sure_Button(2);
            ret_Val = 0;
            exiting = TRUE;
        }
    }
    if (Mouse) 
        MouRemovePtr();
    RestoreBackground(QueBCol - 1, QueBRow - 1, BACKGROUND);
    if (Mouse)
        MouDrawPtr();
    return ret_Val;
}

void Push_Sure_Button(int which_One)
{
    if (which_One == 1) {
        if (Mouse) MouRemovePtr();
        Draw_Pressed(187, 176, 232, 191, GRAY, WHITE);
        Wait_For_Input();
        Draw_Release(187, 176, 232, 191, GRAY, WHITE);
        if (Mouse) MouDrawPtr();
    }
    if (which_One == 2) {
        if (Mouse) MouRemovePtr();
        Draw_Pressed(242, 176, 287, 191, GRAY, WHITE);
        Wait_For_Input();
        Draw_Release(242, 176, 287, 191, GRAY, WHITE);
        if (Mouse) MouDrawPtr();
    }
}

