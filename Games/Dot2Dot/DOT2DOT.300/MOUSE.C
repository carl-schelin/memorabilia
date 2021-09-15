#include <conio.h>
#include <dos.h>
#include "mouse.h"

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
    union REGS inregs, outregs;

    oldrow = oldcol = oldbut = 0;
    inregs.x.ax = 0x0000;
    int86(0x33, &inregs, &outregs);
    ax=outregs.x.ax;               /*  Save AX values    */
    numbuttons=outregs.x.bx;       /*  save # buttons    */
    buttonmask=0xffff;             /*  Make button mask  */
    buttonmask<<=numbuttons;
    buttonmask=~buttonmask;
    return ax;                     /*  Return orig. AX   */
}

/***** draws the mouse pointer ******************/
void MouDrawPtr(void)
{
    union REGS inregs, outregs;

    inregs.x.ax = 0x0001;
    int86(0x33, &inregs, &outregs);
}

/***** removes the mouse pointer ****************/
void MouRemovePtr(void)
{
    union REGS inregs, outregs;

    inregs.x.ax = 0x0002;
    int86(0x33, &inregs, &outregs);
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
    union REGS inregs, outregs;

    inregs.x.ax = 0x0003;
    int86(0x33, &inregs, &outregs);
    buttonval = outregs.x.bx;     /*  Store button status  */
    *row = outregs.x.dx;          /*  Save row & column  */
    *col = outregs.x.cx;
    buttonval &= buttonmask;  /*  Apply button mask  */
    *buttons = buttonval;
}

/***** sets mouse position *************************/
void MouSetPtrPos(unsigned row, unsigned col)
{
    union REGS inregs, outregs;

    inregs.x.ax = 0x0004;
    inregs.x.cx = col;
    inregs.x.dx = row;
    int86(0x33, &inregs, &outregs);
}

void MouPtr(int pointer)
{
    unsigned TransferPointer[] = {
        0xffdf,    /* **********.***** */
        0xffcf,    /* **********..**** */
        0x8007,    /* *............*** */
        0x8003,    /* *.............** */
        0x8001,    /* *..............* */
        0x8003,    /* *.............** */
        0x8007,    /* *............*** */
        0xfbcf,    /* *****.****..**** */
        0xf3df,    /* ****..****.***** */
        0xd001,    /* ***............* */
        0xc001,    /* **.............* */
        0x8001,    /* *..............* */
        0xc001,    /* **.............* */
        0xd001,    /* ***............* */
        0xf3ff,    /* ****..********** */
        0xfbff,    /* *****.********** */

        0x0000,    /* ................ */
        0x0000,    /* ................ */
        0x0010,    /* ...........*.... */
        0x3ff8,    /* ..***********... */
        0x3ffc,    /* ..************.. */
        0x3ff8,    /* ..***********... */
        0x0010,    /* ...........*.... */
        0x0000,    /* ................ */
        0x0000,    /* ................ */
        0x0800,    /* ....*........... */
        0x1ffc,    /* ...***********.. */
        0x3ffc,    /* ..************.. */
        0x1ffc,    /* ...***********.. */
        0x0800,    /* ....*........... */
        0x0000,    /* ................ */
        0x0000     /* ................ */
    };
    unsigned ArrowPointer[] = {
        0xffff,    /* **************** */
        0x3fff,    /* ..************** */
        0x1fff,    /* ...************* */
        0x0fff,    /* ....************ */
        0x07ff,    /* .....*********** */
        0x03ff,    /* ......********** */
        0x01ff,    /* .......********* */
        0x00ff,    /* ........******** */
        0x007f,    /* .........******* */
        0x003f,    /* ..........****** */
        0x03ff,    /* ......********** */
        0x31ff,    /* ..**...********* */
        0xf1ff,    /* ****...********* */
        0xf8ff,    /* *****...******** */
        0xf8ff,    /* *****...******** */
        0xfc7f,    /* ******...******* */

        0x0000,    /* ................ */
        0x0000,    /* ................ */
        0x4000,    /* .*.............. */
        0x6000,    /* .**............. */
        0x7000,    /* .***............ */
        0x7800,    /* .****........... */
        0x7c00,    /* .*****.......... */
        0x7e00,    /* .******......... */
        0x7f00,    /* .*******........ */
        0x7c00,    /* .*****.......... */
        0x4800,    /* .*..*........... */
        0x0400,    /* .....*.......... */
        0x0400,    /* .....*.......... */
        0x0200,    /* ......*......... */
        0x0200,    /* ......*......... */
        0x0000     /* ................ */
    };
    unsigned WaitPointer[] = {
        0xf83f,    /* *****.....****** */
        0xf83f,    /* *****.....****** */
        0xf83f,    /* *****.....****** */
        0xf83f,    /* *****.....****** */
        0xf83f,    /* *****.....****** */
        0xf01f,    /* ****.......***** */
        0xe00f,    /* ***.........**** */
        0xc007,    /* **...........*** */
        0xc103,    /* **.....*......** */
        0xc007,    /* **...........*** */
        0xe00f,    /* ***.........**** */
        0xf01f,    /* ****.......***** */
        0xf83f,    /* *****.....****** */
        0xf83f,    /* *****.....****** */
        0xf83f,    /* *****.....****** */
        0xf83f,    /* *****.....****** */

        0x0000,    /* ................ */
        0x0000,    /* ................ */
        0x0000,    /* ................ */
        0x0000,    /* ................ */
        0x0000,    /* ................ */
        0x07c0,    /* .....*****...... */
        0x0ee0,    /* ....***.***..... */
        0x1ef0,    /* ...****.****.... */
        0x1e10,    /* ...****...**.... */
        0x1ff0,    /* ...*********.... */
        0x0fe0,    /* ....*******..... */
        0x07c0,    /* .....*****...... */
        0x0000,    /* ................ */
        0x0000,    /* ................ */
        0x0000,    /* ................ */
        0x0000     /* ................ */
    };
    unsigned HourPointer[] = {
        0x0001,    /* ...............* */
        0x8003,    /* *.............** */
        0x9ff3,    /* *..*********..** */
        0x9ff3,    /* *..*********..** */
        0xcfe7,    /* **..*******..*** */
        0xe7cf,    /* ***..*****..**** */
        0xf39f,    /* ****..***..***** */
        0xf93f,    /* *****..*..****** */
        0xf39f,    /* ****..***..***** */
        0xe7cf,    /* ***..*****..**** */
        0xcfe7,    /* **..*******..*** */
        0x9ff3,    /* *..*********..** */
        0x9ff3,    /* *..*********..** */
        0x8003,    /* *.............** */
        0x0001,    /* ...............* */
        0x0000,    /* ................ */

        0xfffe,    /* ***************. */
        0x7ffc,    /* .*************.. */
        0x600c,    /* .**.........**.. */
        0x600c,    /* .**.........**.. */
        0x3018,    /* ..**.......**... */
        0x1830,    /* ...**.....**.... */
        0x0c60,    /* ....**...**..... */
        0x07c0,    /* .....*****...... */
        0x0c60,    /* ....**...**..... */
        0x1830,    /* ...**.....**.... */
        0x3018,    /* ..**.......**... */
        0x600c,    /* .**.........**.. */
        0x600c,    /* .**.........**.. */
        0x7ffc,    /* .*************.. */
        0xfffe,    /* ***************. */
        0x0000     /* ................ */
    };
    union REGS inregs, outregs;
    struct SREGS segregs;

    switch (pointer) {
        case 0 : segregs.es  = FP_SEG(TransferPointer);
                 inregs.x.dx = FP_OFF(TransferPointer);
                 inregs.x.bx = 7;
                 inregs.x.cx = 7;
                 break;

        case 1 : segregs.es  = FP_SEG(ArrowPointer);
                 inregs.x.dx = FP_OFF(ArrowPointer);
                 inregs.x.bx = 0;
                 inregs.x.cx = 0;
                 break;

        case 2 : segregs.es  = FP_SEG(WaitPointer);
                 inregs.x.dx = FP_OFF(WaitPointer);
                 inregs.x.bx = 8;
                 inregs.x.cx = 7;
                 break;

        case 3 : segregs.es  = FP_SEG(HourPointer);
                 inregs.x.dx = FP_OFF(HourPointer);
                 inregs.x.bx = 8;
                 inregs.x.cx = 7;
                 break;
    }
    inregs.x.ax = 0x0009;
    int86x(0x33, &inregs, &outregs, &segregs);
}

