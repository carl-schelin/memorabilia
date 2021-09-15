#include <stdio.h>
#include <conio.h>
#include <bios.h>
#include <dos.h>
#include <stdlib.h>

#include <TcxlKey.H>
#include <TcxlHdw.H>
#include <TcxlMem.H>
#include <TcxlVid.H>
#include <TcxlWin.H>

#include "status.h"

#define HIDE FALSE
#define SHOW TRUE

void vlInitialize(void);
VOID vlDisplayEMS(NOARG);

char cgMessage[80];

void main(void)
{
    unsigned int HdwType;

    int mid, vid, totalmemory, totmem;
    int exp1, exp2, exp3;
    int ext1, ext2, ext3;
    int std1, std2, std3;
/*    int color = 0;
    char type[15] = "Unknown";
    char video[50] = "Unknown";
    char memmap[3][51] = {
        { "°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°" },
        { "±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±" },
        { "²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²" }
    };
*/

    vlInitialize();

    /* initialize any variables for the display */
    switch (MachId()) {
        case IBMPC    : HdwType =  1; break;
        case IBMPCXT  : HdwType =  2; break;
        case IBMPCJR  : HdwType =  3; break;
        case IBMPCAT  : HdwType =  4; break;
        case IBMPCXT2 : HdwType =  5; break;
        case IBMPS30  : HdwType =  6; break;
        case IBMCONV  : HdwType =  7; break;
        case IBMPS80  : HdwType =  8; break;
        case SPERRYPC : HdwType =  9; break;
        case CPQPORT  : HdwType = 10; break;
        case CPQPLUS  : HdwType = 11; break;
        case HP110    : HdwType = 12; break;
        default       : HdwType =  0; break;
    }

    
    WpopUp(CNT_CNT, 3, 10, 18, 70, BOX_DBL, LCYAN|_BLUE, LGREEN|_BLUE);
        Wshadow(DGREY|_BLACK);

    sprintf(cgMessage, "Computer: %s", MachineType[HdwType]);
    Wprts(0, 1, YELLOW|_BLUE, cgMessage);

    sprintf(cgMessage, "Keyboard: %s %s %s %s", 
        (_KeySta()&KEY_NUM) ? "NUM" : "num", 
        (_KeySta()&KEY_CAP) ? "CAP" : "cap", 
        (_KeySta()&KEY_INS) ? "INS" : "ins", 
        (_KeySta()&KEY_SCR) ? "SCR" : "scr"
    );
    Wprts(1, 30, YELLOW|_BLUE, cgMessage);

    sprintf(cgMessage, "ROM BIOS: %s", BiosVer());
    Wprts(1, 1, YELLOW|_BLUE, cgMessage);

    sprintf(cgMessage, "DOS ver: %x.%x", _version&0xF, _version >> 4);
    Wprts(2, 1, YELLOW|_BLUE, cgMessage);

    if (MemDPMI) {
        sprintf(cgMessage, "DPMI ver: %x.%x", MemDver >> 8, MemDver&0xFF);
        Wprts(3, 1, YELLOW|_BLUE, cgMessage);
    }
/* virtual control program interface */
    if (MemVCPI) {
        sprintf(cgMessage, "VCPI ver: %x.%x", MemVver >> 8, MemVver&0xFF);
        Wprts(4, 1, YELLOW|_BLUE, cgMessage);
    }

    if (MemXMS) {
        sprintf(cgMessage, "XMS ver: %x.%x internal ver: %x.%x", MemXver >> 8, MemXver&0xFF, MemXint >> 8, MemXint&0xFF);
        Wprts(6, 1, YELLOW|_BLUE, cgMessage);
    }

    if (MemHMA) {
        sprintf(cgMessage, "HMA is in use, %d paragraphs free", MemHfre);
        Wprts(7, 1, YELLOW|_BLUE, cgMessage);
        sprintf(cgMessage, "%d is the largest free UMB", MemUfre);
        Wprts(8, 1, YELLOW|_BLUE, cgMessage);
        sprintf(cgMessage, "%d total XMS and %d is the largest free block", MemXtot, MemXlrg);
        Wprts(9, 1, YELLOW|_BLUE, cgMessage);
    }

    sprintf(cgMessage, "Total Memory %dk", biosmemory() + MemEtot * 16 + MemXtot);
    Wprts(10, 1, YELLOW|_BLUE, cgMessage);

    vlDisplayEMS();

/*        NumPages = EMSquery();
        NumPagesUsed = EMScount();
        EMSversion = MemEver;
        EMS*/
        


/*

    gotoxy(48, 6);
    cprintf("Mouse: %s", msinit() ? "Installed" : "None");

    gotoxy(47, 7);
    cprintf("Floppy: %d Drive%s", numflop(), ((numflop()==1) ? "" : "s"));

    gotoxy(14, 8);
    cprintf("Clock Board: %s", (clockcal() ? "Yes" : "No"));

    gotoxy(45, 8);
    cprintf("Parallel: %d Port%s", numpar(), ((numpar()==1) ? "" : "s"));

    gotoxy(16, 9);
    cprintf("Math Chip: %s", (mathchip() ? "Yes" : "No"));

    gotoxy(47, 9);
    cprintf("Serial: %d Port%s", numser(), ((numser()==1) ? "" : "s"));

    gotoxy(15, 10);
    cprintf("EMS Driver: %s", (emsexist() ? emsver() : "No"));

    gotoxy(49, 10);
    cprintf("Game: %s", (gameport() ? "Yes" : "Not Installed"));

    gotoxy(14, 11);
    cprintf("Video Board: %s", video);
    if (strcmp(vid, "Unknown") == 0) cprintf("; type %d", vid);

    totalmemory = biosmemory() + extmem() + expmem();
    gotoxy(13, 12);
    cprintf("Total Memory: %dk Installed", totalmemory);

    if (emsexist() != 0) {
        gotoxy(16, 13);
        cprintf("EMS Pages: %d (%dk)", emstotal(), emstotal() * 16);
        gotoxy(15, 14);
        cprintf("Free Pages: %d (%dk)", emsfree(), emsfree() * 16);
    }

    gotoxy(36, 16);
    cprintf("Memory Map");

    ext1 = extmem();
    exp1 = expmem();
    std1 = biosmemory();

    if (argc > 1) {
        std1 = atoi(argv[1]);
        ext1 = atoi(argv[2]);
        exp1 = atoi(argv[3]);
    }

    totmem = ext1 + exp1 + std1;

    std2 = 50 - ((float) std1 / (float) totmem * 100 / 2);
    ext2 = 50 - ((float) ext1 / (float) totmem * 100 / 2);
    exp2 = 50 - ((float) exp1 / (float) totmem * 100 / 2);
    std3 = 50 - std2;
    ext3 = 50 - ext2;
    exp3 = 50 - exp2;

    gotoxy(16, 17);
    cprintf("%s", memmap[0] + std2);
    cprintf("%s", memmap[1] + ext2);
    cprintf("%s", memmap[2] + exp2);

    gotoxy(std3 / 2 + 14, 18);
    cprintf("%3dK", std1);
    if (ext1 > 0) {
        gotoxy(ext3 / 2 + 12 + std3, 18);
        cprintf("%4dK Ext", ext1);
    }
    if (exp1 > 0) {
        gotoxy(exp3 / 2 + 12 + std3 + ext3, 18);
        cprintf("%4dK Exp", exp1);
    }

    if (color) 
        textattr(BLUE + (CYAN << 4));
    else
        textattr(BLACK + (LIGHTGRAY << 4));
    gotoxy(56, 13);
    cprintf("  Written by  ");
    gotoxy(56, 14);
    cprintf(" Carl Schelin ");

    gotoxy(1, 20);
*/
    getch();
}


VOID vlInitialize(NOARG)
{
    VposT ilStartDT, ilEndDT;

    TcxlInit();
    VposC(ilStartDT) = 0;
    VposC(ilEndDT) = VidWid - 1;
    VposR(ilStartDT) = 0;
    VposR(ilEndDT) = VidDep - 1;
    VfilBox(ilStartDT, ilEndDT, (ChrT)0xB0, (AtrT)WHITE|_RED);
}

VOID vlMainScreen(NOARG)
{
    Wopen(5, 15, 15, 50, BOX_DBL, LCYAN|_BLUE, CLYAN|_BLUE);
        Wshadow(DGREY|_BLACK);
        Wtitle("[ Status ]", TTL_LFT, YELLOW|_BLUE);
        


VOID vlDisplayEMS(NOARG)
{
    ChrP clMemoryBar = "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÝ";

    VcurHid(HIDE);
    Wborder(BOX_SNG);
    Wshadoff();
    Wopen(5, 15, 15, 41, BOX_DBL, LCYAN|_BLUE, LCYAN|_BLUE);
        Wshadow(DGREY|_BLACK);
        Wtitle("[ EMS ]", TTL_LFT, YELLOW|_BLUE);
        sprintf(cgMessage, "LIM/EMS Version: %x.%x", MemEver >> 4, MemEver&0xF);
        Wprts(0, 1, YELLOW|_BLUE, cgMessage);
        sprintf(cgMessage, "Total EMS Memory: %dk", MemEtot * 16);
        Wprts(1, 1, YELLOW|_BLUE, cgMessage);
        sprintf(cgMessage, "Total Available: %dk", MemEfre * 16);
        Wprts(2, 1, YELLOW|_BLUE, cgMessage);
        Wprts(3, 1, YELLOW|_BLUE, "Total Handles: 64");
        sprintf(cgMessage, "Handles In Use: %d", EMScount());
        Wprts(4, 1, YELLOW|_BLUE, cgMessage);
        sprintf(cgMessage, "Base Segment: %04XH", MemEseg);
        Wprts(5, 1, YELLOW|_BLUE, cgMessage);
        getch();
    Wclose();
    VcurHid(SHOW);
    Wborder(BOX_DBL);
    Wshadow(DGREY|_BLACK);
}

