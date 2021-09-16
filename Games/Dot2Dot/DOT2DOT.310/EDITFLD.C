/* []---------------------------------------------------------------------[] */
/* |       EditFld.c: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |              The EditFld.c source code and concepts are               | */
/* |     Copyright (C) 1986-1996 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __EDITFLD__

#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <graph.h>

#include "dot2dot.h"
#include "mouse.h"

void Edit_Field(int EdtBCol, int EdtBRow, int bcolor, int wcolor, char *hold, int maxlen)
{
    int keepCount, inpCh, j;

    if (Mouse)
        MouRemovePtr();
    keepCount = strlen(hold);
    _setcolor(wcolor);
    _moveto(EdtBCol, EdtBRow);
    _outgtext(hold);
    _moveto(keepCount * 8 + EdtBCol, EdtBRow);
    for (;;) {
        inpCh = getch(); /* wait for a character */
        if (inpCh == 0) {
            inpCh = getch();
            inpCh = 0; /* ignore non characters */
        }
        if (inpCh == 8 && keepCount > 0) {  /* backspace */
            _setcolor(bcolor);
            keepCount--;
            _moveto(keepCount * 8 + EdtBCol + 1, EdtBRow);
            _lineto(keepCount * 8 + EdtBCol + 7, EdtBRow);
            for (j = EdtBRow + 1; j < EdtBRow + 10; j++) { /* draw lines to clear */
                _moveto(keepCount * 8 + EdtBCol    , j);
                _lineto(keepCount * 8 + EdtBCol + 8, j);
            }
            _moveto(keepCount * 8 + EdtBCol + 1, EdtBRow + 10);
            _lineto(keepCount * 8 + EdtBCol + 7, EdtBRow + 10);
            hold[keepCount] = '\0';
            _setcolor(wcolor);
        }
        if (inpCh == 13 || keepCount > maxlen) {  /* enter, all done */
            break;
        }
        if (!iscntrl(inpCh)) {  /* something else, put it in string */
            hold[keepCount++] = (char)inpCh;
            hold[keepCount] = '\0';
            _moveto(EdtBCol, EdtBRow);
            _outgtext(hold);
        }
    }
    if (Mouse)
        MouDrawPtr();
}

