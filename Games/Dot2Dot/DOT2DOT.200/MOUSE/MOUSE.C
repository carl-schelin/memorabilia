#include <conio.h>
#include <dos.h>
#include "mouse\mouse.h"

#define MOUSEINT 0x33
#define MouFunc(x) {_AX=(x);geninterrupt(MOUSEINT);}

static unsigned numbuttons = 0, buttonmask;
static unsigned oldrow, oldcol, oldbut;

/***** returns number of buttons ****************/
unsigned MouNumButtons(void)
{
    return numbuttons;
}

/***** initializes the mouse ********************/
unsigned MouOpen(void)
{
    unsigned ax;

    oldrow = oldcol = oldbut = 0;
    MouFunc(0);           /*  Reset mouse drvr  */
    ax=_AX;               /*  Save AX values    */
    numbuttons=_BX;       /*  save # buttons    */
    buttonmask=0xffff;    /*  Make button mask  */
    buttonmask<<=numbuttons;
    buttonmask=~buttonmask;
    return ax;            /*  Return orig. AX   */
}

/***** draws the mouse pointer ******************/
void MouDrawPtr(void)
{
    MouFunc(1);           /*  Unhide mouse      */
}

/***** removes the mouse pointer ****************/
void MouRemovePtr(void)
{
    MouFunc(2);           /*  Hide mouse        */
}

/***** waits for mouse event, and return ********/
void MouCharIn(unsigned *row, unsigned *col, unsigned *buttons)
{
    while (TRUE) {
        if (Mouse) MouReadEventInfo(row, col, buttons);
        if ((*row != oldrow) || (*col != oldcol) || (*buttons != oldbut) || 
          kbhit())
            break;
    }
    oldrow = *row;
    oldcol = *col;
    oldbut = *buttons;
}

/***** returns mouse position & button settings */
void MouReadEventInfo(unsigned *row, unsigned *col, unsigned *buttons)
{
    unsigned buttonval;

    MouFunc(3);      /*  Get pos & button state  */
    buttonval = _BX;     /*  Store button status  */
    *row = _DX;          /*  Save row & column  */
    *col = _CX;
    buttonval &= buttonmask;  /*  Apply button mask  */
    *buttons = buttonval;
}

/***** sets mouse position *************************/
void MouSetPtrPos(unsigned row, unsigned col)
{
    _DX = row;
    _CX = col;
    MouFunc(4);                  /*  Set position  */
}

