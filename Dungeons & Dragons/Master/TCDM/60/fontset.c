/* []---------------------------------------------------------------------[] */
/* |            FontSet.cpp: Modify the default screen font.               | */
/* |                                                                       | */
/* |            The FontSet.cpp source code and concepts are               | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __FONTSET__

#ifdef __TURBOC__

#include <alloc.h>
#include <dos.h>
#include <stdio.h>
#include <TcxlDef.H>

#pragma hdrstop
#include "..\Include\TCDM.H"

VOID SelectFont(ChrP fontFile);
VOID RestoreDefault(NOARG);
VOID GetMode(NOARG);

/**[ Select Font ]*************************************************

  Input: Character pointer to the font filename to be loaded
  Returns: None
  Description: At any time, load the default font passed to it by the 
    calling function.
  Pseudocode:
    allocate memory for the table
    if opening font file ok
      fill table from file
      close font file
      fill registers with data
      kick interrupt
    free allocated space
 ******************************************************************/

VOID SelectFont(ChrP fontFile)
{
    struct REGPACK registers;
    ChrT fullTable[256][16];
    FILE *input;
    IntT j, k;

    if ((input = fopen(fontFile, "rb")) != NULL) {
        for (j = 0; j < 256; j++)                    /*  open and fill array */
            for (k = 0; k < 16; k++) 
                fullTable[j][k] = fgetc(input);
        fclose(input);

/*  From Ralf Brown's Interrupt List
 *     Int 10
 *       AH = 11h
 *       The following functions will cause a mode set, completely resetting
 *       the video environment, but without clearing the video buffer
 *       AL = 00h: load user-specified patterns
 *       ES:BP -> user table
 *        CX    = count of patterns to store
 *        DX    = character offset into map 2 block
 *        BL    = block to load in map 2
 *        BH    = number of bytes per character pattern
 *
 *  Since BC++ supports REGPACK and intr() function, I can use C to call
 *  my graphic table
 */

        registers.r_es = ((long) fullTable) >> 16;
        registers.r_bp = ((long) fullTable) & 0xFFFF;
        registers.r_ax = 0x1100;
        registers.r_bx = 16 << 8;
        registers.r_cx = 256;
        registers.r_dx = 0;
        intr(0x10, &registers);
    }
}

/**[ Restore Default ]*********************************************

  Input: None
  Returns: None
  Description: Set mode
  Pseudocode:
    fill registers with data
    kick interrupt
 ******************************************************************/

VOID RestoreDefault(NOARG)
{
    union REGS inregs, outregs;

/*  From Ralf Brown's Interrupt List
 *     Int 10
 *       AH = 00h
 *       AL = mode
 */

    inregs.h.ah = 0;
    inregs.h.al = FntMod;
    int86(0x10, &inregs, &outregs);
}

/**[ Get Mode ]****************************************************

  Input: None
  Returns: None
  Description: Get the current mode.
  Pseudocode:
    fill registers with data
    kick interrupt
    assign mode to global variable FntMod
 ******************************************************************/

VOID GetMode(NOARG)
{
    union REGS inregs, outregs;

/*  From Ralf Brown's Interrupt List
 *     Int 10
 *        AH = 0Fh
 *     Return:
 *        AH = number of columns on screen
 *        AL = current video mode
 *        BH = current active display page
 */

    inregs.h.ah = 0;
    int86(0x10, &inregs, &outregs);
    FntMod = outregs.h.al;
}

#endif      /*  Only if TurboC/BorlandC is being used can we use this  */
