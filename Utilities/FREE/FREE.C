/*    Free v2.0.10
 *
 *    Copyright 1990-1996 by Carl Schelin, All Rights Reserved.
 *    This code may be used as a learning tool, but you can't recompile
 *    it and say it's yours.
 *
 */
#include <conio.h>
#include <alloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <dir.h>
#include <io.h>
#include <TcxlHdw.H>
#ifdef GRAPHICS
#include <graphics.h>
#endif

#include "free.h"

int notready = 0;
int drive;

unsigned int biosequip(void);

#ifdef GRAPHICS
int monitor = 0;
int monitorega = 0;
int monitorvga = 0;
int g_driver = 0;
int g_mode = 0;
int bottom_limit = 350;
#endif

void main(int argc, char *argv[])
{
    struct dfree *freespc;
    char *directory;
    int help = 0, modify = 0;
    long avail, total;
    int floppies;
    int percent;
    char FullDrive[45], InUseDrive[45];

    if (argc > 0) {
        for (drive = 1; drive <= argc; drive++) {
            if ((stricmp(argv[drive], "/D") == 0) || (stricmp(argv[drive], "-D") == 0) || (stricmp(argv[drive], "D") == 0))
                switchinfo[DTEXT] = switchinfo[DTEXT] == '-' ? '+' : '-';
            if ((stricmp(argv[drive], "/F") == 0) || (stricmp(argv[drive], "-F") == 0) || (stricmp(argv[drive], "F") == 0))
                switchinfo[FLOPPY] = switchinfo[FLOPPY] == '-' ? '+' : '-';
            if ((stricmp(argv[drive], "/G") == 0) || (stricmp(argv[drive], "-G") == 0) || (stricmp(argv[drive], "G") == 0))
                switchinfo[GRAPHIC] = switchinfo[GRAPHIC] == '-' ? '+' : '-';
            if ((stricmp(argv[drive], "/H") == 0) || (stricmp(argv[drive], "-H") == 0) || (stricmp(argv[drive], "/?") == 0) || (stricmp(argv[drive], "-?") == 0) || (stricmp(argv[drive], "?") == 0))
                help = 1;
            if ((stricmp(argv[drive], "/I") == 0) || (stricmp(argv[drive], "-I") == 0) || (stricmp(argv[drive], "I") == 0))
                switchinfo[INFO] = switchinfo[INFO] == '-' ? '+' : '-';
            if ((stricmp(argv[drive], "/N") == 0) || (stricmp(argv[drive], "-N") == 0) || (stricmp(argv[drive], "N") == 0))
                switchinfo[NOHEX] = switchinfo[NOHEX] == '-' ? '+' : '-';
            if ((stricmp(argv[drive], "/R") == 0) || (stricmp(argv[drive], "-R") == 0) || (stricmp(argv[drive], "R") == 0))
                switchinfo[RESPOND] = switchinfo[RESPOND] == '-' ? '+' : '-';
            if ((stricmp(argv[drive], "/U") == 0) || (stricmp(argv[drive], "-U") == 0) || (stricmp(argv[drive], "U") == 0))
                modify = 1;
        }
        if (modify == 1) {
            modify_free();
            exit(0);
        }
    }

    printf("FREE "VERSION" - Copyright 1990-1996 by Carl Schelin - All Rights Reserved\n\n");

    if (help == 1) {
        printf("Help [/d /f /g /h /i /n /r /? ?]\n\n");
        printf("   /d   %c Display the drive assignments as full text rather than by letter.\n", switchinfo[DTEXT]);
        printf("   /f   %c Include Floppies A: and/or B:.\n", switchinfo[FLOPPY]);
        printf("   /g   %c Display usage in a bar graph format.\n", switchinfo[GRAPHIC]);
        printf("   /h/? - Displays above information.\n");
        printf("   /i   %c Display sector, cluster and usage information.\n", switchinfo[INFO]);
        printf("   /n   %c Do not display ? code information.\n", switchinfo[NOHEX]);
        printf("   /r   %c Do not display drives that don't respond.\n", switchinfo[RESPOND]);
        printf("   /u   - Modify Free.Exe's default switches and exit.\n");
        printf("\nFree is a Shareware Utility from Carl Schelin. New codes are added all the\n");
        printf("time. If you find a new code send the output of Free and system information\n");
        printf("to me at my home. After verification, I'll send the updated version back to\n");
        printf("you. To register, send $15.00 to:\n");
        printf("Carl Schelin, 3925 Penshurst Lane #101, Woodbridge, VA  22192\n");
        exit(1);
    }

    if (_osmajor < 3) {
        printf("Sorry, Free requires at least Dos version 3.0\n");
		exit(1);
	}

    if ((freespc = malloc(sizeof(freespc))) == NULL) {
        printf("Not enough memory to allocate freespc structure\n");
        exit(1);
    }

    TcxlCurOff();
    TcxlInit();

#ifdef GRAPHICS
    if (switchinfo[GRAPHIC] == '+') {
        initialization();
        if (g_driver > 0) {
            graphic_setup();
            init_screen();
        }
    }
#endif

    if ((directory = malloc(MAXDIR)) == NULL) {
        printf("Not enough memory to allocate directory\n");
        exit(1);
    }
    setvect(0x24, myhandler);
/*    floppies = ((biosequip() & 0xC0) >> 6) + 1;*/
    floppies = HdwDrv();
#ifdef GRAPHICS
    if (g_driver == 0)
#endif
        printf("Drive   Available      Total       ");
    if (switchinfo[DTEXT] == '+')
        printf("Drive Assignment\n");
    else
        if (switchinfo[INFO] == '+')
            printf("Usage  Cluster Size  Sector Size\n");
        else
            if (switchinfo[GRAPHIC] == '+') {
#ifdef GRAPHICS
                if (g_driver == 0)
#endif
                    printf("Approximate Usage Graphically Displayed\n");
            }
            else {
                printf("Current Directory\n");
            }
    for (drive = switchinfo[FLOPPY] == '+' ? 1 : 3; drive < 27; drive++) {
        notready = -1;
        if (drive == 2 && floppies == 1)
            drive++;
        getdfree(drive, freespc);
        if (notready == -1) {
            if (freespc->df_sclus != 0xFFFF) {
                getcurdir(drive, directory);
                avail = (long) freespc->df_bsec * (long) freespc->df_sclus * (long) freespc->df_avail;
                total = (long) freespc->df_bsec * (long) freespc->df_sclus * (long) freespc->df_total;
#ifdef GRAPHICS
                if (g_driver == 0)
#endif
                    printf("  %c:   %10ld   %10ld   ", drive + 64, avail, total);
                percent = 100 - (int)(avail / (total / 100));
                if (switchinfo[DTEXT] == '+')
                    printf("  %s\n", driveinfo[getpath(drive)] + 1, _osmajor, _osminor);
                else
                    if (switchinfo[INFO] == '+')
                        printf("%c %3d%%   %5u bytes%c %5u bytes\n", 
                          driveinfo[getpath(drive)][0], percent, 
                          freespc->df_bsec * freespc->df_sclus,
                          (freespc->df_bsec * freespc->df_sclus) > (6 * 1024) ? '!' : ' ',
                          freespc->df_bsec);
                    else 
                        if (switchinfo[GRAPHIC] == '+') {
#ifdef GRAPHICS
                            if (g_driver == 0) {
#endif
                                strcpy(FullDrive, "께께께께께께께께께께께께께께께께께께께께께께");
                                strcpy(InUseDrive, "같같같같같같같같같같같같같같같같같같같같같같");
                                percent = 44 * percent / 100;
                                FullDrive[percent] = '\0';
                                InUseDrive[44 - percent] = '\0';
                                printf("%c %s%s\n", driveinfo[getpath(drive)][0], FullDrive, InUseDrive);
#ifdef GRAPHICS
                            }
                            else {
                                print_graph(drive, 
                                    getpath(drive),
                                    (int)(total / 1048576L), 
                                    (int)((total - avail) / 1048576L)
                                );
                            }
#endif
                        }
                        else 
                            printf("%c %c:\\%s\n", driveinfo[getpath(drive)][0],
                              drive + 64, directory);
            }
        }
        else {
            if (switchinfo[RESPOND] == '-')
#ifdef GRAPHICS
                if (g_driver == 0)
#endif
                    printf("->%c<-\t\t\t\t   %sDrive not responding.\n", drive + 64, notready == NETDRIVE ? "Network " : "");
#ifdef GRAPHICS
                else
                    print_graph(drive, -1, 0, 0);
#endif
        }
    }
    drive = 0;
    free(freespc);
    free(directory);

#ifdef GRAPHICS
    if (g_driver > 0) {
        getch();
        textmode(C80);
/*        closegraph();*/
    }
#endif
}

#ifdef GRAPHICS
void initialization(void)
{
    /*  Initialize the Graphics Functions used by Borland C */
	detectgraph(&g_driver, &g_mode);
    switch (g_driver) {
        case EGA      :
                        bottom_limit = 350;
                        g_driver = EGA;
                        g_mode = EGAHI;
                        monitorega = 1;
                        monitor = 1;
                        break;

        case IBM8514  : 
        case VGA      : bottom_limit = 480;
                        g_driver = VGA;
                        g_mode = VGAHI;
                        monitorvga = 1;
                        monitor = 1;
                        break;

        default       : g_driver = 0;
                        monitor = 0;
                        break;
    }

    registerbgifont(small_font);
    registerbgidriver(EGAVGA_driver);
}
#endif

int getpath(int drive)
{
    union REGS r;
    struct SREGS s;
    int remote = 0;
    
    r.x.ax = 0x4409;
    r.x.bx = 0x0000 + drive;
    /* assuming near pointers: */
    segread(&s);
    s.es = s.ds;
    intdosx(&r,&r,&s);
    remote = UNKNOWN;
    if (r.x.dx == 0x0000) remote = NOINIT;      /*  !Init DEC PathWorks      */
    if (r.x.dx == 0x1001) remote = DECINIT;     /*  DEC PathWorks on 4.x     */
    if (r.x.dx == 0x0800) remote = VDISK;
    if (r.x.dx == 0x0802) remote = BERNOULLI;   /*  3.x Dos                  */
    if (r.x.dx == 0x0840) remote = LOCAL;       /*  3.x Dos                  */
    if (r.x.dx == 0x0842) remote = LOCAL40;     /*  4.x Dos                  */
    if (r.x.dx == 0x08c2) remote = LOCAL50;     /*  5.x Dos                  */
    if (r.x.dx == 0x1000) {
        if (_osmajor >= 5)
            remote = LANMAN50;                  /*  5.x Lanman Drive         */
        if (_osmajor == 3 && _osminor == 30)
            remote = BRIDGE;                    /*  Bridge drive on ps/2 ?   */
    }
    if (r.x.dx == 0x1756) remote = LANMAN;      /*  LAN Mgr and Share        */
    if (r.x.dx == 0x178e) remote = SHARE16;     /*  3+Share v1.6 on 3.31     */
    if (r.x.dx == 0x17f6) remote = PCLAN;       /*  IBM PC Lan               */
    if (r.x.dx == 0x17fb) remote = LANMAN33;    /*  3.3 Lan Manager v2.0     */
    if (r.x.dx == 0x19e8) remote = PATHWORKS;   /*  DEC Pathworks on 4.0     */
    if (r.x.dx == 0x2000) remote = ADJRAM;      /*  AdjRam from G.Cramblitt  */
    if (r.x.dx == 0x2800) remote = QUICKMEM;    /*  Intel Quickmem VDisk     */
    if (r.x.dx == 0x28C2) remote = ONTRACK;     /*  OnTrack Disk Manager     */
    if (r.x.dx == 0x4000) remote = XPANDISK;    /*  XPanDisk from PCMag      */
    if (r.x.dx == 0x4040) remote = BRIDGE40;    /*  Bridge drive on 4.x      */
    if (r.x.dx == 0x4042) remote = SYQUEST50;   /*  Syquest external on 5.x  */
    if (r.x.dx == 0x4800) remote = VGADISK;     /*  VgaDisk from T.Frandsen  */
    if (r.x.dx == 0x4840) remote = EXTERN;
/*  if (r.x.dx == 0x4840)
        if (checknetwork() == 0) remote = EXTERN;
                            else remote = BANYAN;
*/
    if (r.x.dx == 0x4842) {
        if (_osmajor == 4) remote = SYQUEST40;  /*  Syquest external on 4.x  */
        if (_osmajor == 5) remote = DUBLDISK;   /*  Double Disk v2.6 on 5.x  */
    }
    if (r.x.dx == 0x6000) remote = VDSKDD;      /*  VDiskDD from V.Lanin     */
    if (r.x.dx == 0x6842) remote = SCSI50;      /*  SCSI on Dos 5.x          */
    if (r.x.dx == 0x68C2) remote = IOMEGAZIP;   /*  Iomega Zip Drive         */
    if (r.x.dx == 0x8800) remote = SUBSTVDISK;  /*  Subst VDisk              */
    if (r.x.dx == 0x8802) remote = SUBSTBERN;   /*  Subst bernoulli          */
    if (r.x.dx == 0x8840) remote = SUBST;       /*  Subst for Dos 3.x        */
    if (r.x.dx == 0x8842) remote = SUBST40;     /*  Subst for Dos 4.x        */
    if (r.x.dx == 0x88c2) remote = SUBST50;     /*  Subst for Dos 5.x        */
    if (r.x.dx == 0xa000) remote = SUBSTADJRAM; /*  Subst AdjRam             */
    if (r.x.dx == 0xa800) remote = SUBSTQCKMEM; /*  Subst Intel QuickMem     */
    if (r.x.dx == 0xc000) remote = SUBSTXPDSK;  /*  Subst XpanDisk           */
    if (r.x.dx == 0xc042) remote = SUBSTSYQ50;  /*  Subst Syquest on Dos 5.x */
    if (r.x.dx == 0xc800) remote = SUBSTVGADSK; /*  Subst VGADisk            */
    if (r.x.dx == 0xc842) remote = SUBSTDDISK;  /*  Subst Double Disk on 5.x */
    if (r.x.dx == 0xd873) remote = PCNFS;       /*  PCNFS Lan software       */
    if (r.x.dx == 0xe000) remote = SUBSTVDD;    /*  Subst VDiskDD            */
    if (r.x.dx == 0xe842) remote = SUBSTSCSI50; /*  Subst for SCSI/5.x       */
    if (remote == UNKNOWN && switchinfo[NOHEX] == '-')
        printf(" %04x ", r.x.dx);
    return remote;
}

void interrupt myhandler(bp, di, si, ds, es, dx, cx, bx, ax, ip, cs, flags)
unsigned bp;
unsigned di;
unsigned si;
unsigned ds;
unsigned es;
unsigned dx;
unsigned cx;
unsigned bx;
unsigned ax;
unsigned ip;
unsigned cs;
unsigned flags;
{
    union REGS reg;
    struct SREGS sreg;

    bp = bp; /* just some assignments to prevent compile errors */
    di = di;
    si = si;
    ds = ds;
    es = es;
    dx = dx;
    cx = cx;
    bx = bx;
    ax = ax;
    ip = ip;
    cs = cs;
    flags = flags;

    notready = LOCDRIVE;

    reg.x.ax = 0x5900;
    reg.x.bx = 0x0000;
    /* assuming near pointers: */
    segread(&sreg);
    sreg.es = sreg.ds;
    intdosx(&reg,&reg,&sreg);
    if ((reg.x.cx >> 8) == 0x03)
        notready = NETDRIVE;

    ax = (ax & 0xFF00) + 3;
}

void modify_free(void)
{
    char pathname[MAXPATH];
    char testdata[20];
    long textlocation = 0xA16C; /* A16C */
    FILE *output;

    printf("Where is Free.Exe located? ");
    scanf("%s", pathname);
    if ((output = fopen(pathname, "r+b")) != NULL) {
        if (fseek(output, textlocation, SEEK_SET) == 0)
            if (fread(testdata, sizeof(char), strlen(switchinfo), output) == strlen(switchinfo)) {
                testdata[6] = '\0';
                if (strcmp(testdata, "[JAEL]") == 0) {
                    fseek(output, textlocation, SEEK_SET);
                    if (fwrite(switchinfo, sizeof(char), strlen(switchinfo), output) == strlen(switchinfo)) {
                        printf("Free.Exe modified!\n");
                        notready = 0;
                    }
                    else {
                        printf("Error writing to Free.Exe\n");
                        notready = 5;
                    }
                }
                else {
                    printf("Location of switch data is incorrect! Free.Exe may be modified!");
                    notready = 4;
                }
            }
            else {
                printf("Unable to read switch information from Free.Exe.");
                notready = 3;
            }
        else {
            printf("Unable to move to %l in Free.Exe. Exit without change.", textlocation);
            notready = 2;
        }
        fclose(output);
    }
    else {
        printf("Sorry, either Free.Exe is not located at %s,\n", pathname);
        printf("or there was a problem opening Free.Exe. Please verify it's\n");
        printf("location and try again.\n");
        notready = 1;
    }
}

#ifdef GRAPHICS
void graphic_setup(void)
{
    int g_error;

	initgraph(&g_driver, &g_mode, "");
    if ((g_error = graphresult()) < 0) {
		cprintf("initgraph error: %s.\n", grapherrormsg(g_error));
		exit(1);
	}
}

void init_screen(void)
{
	int j, twidth;
	char buffer[20];
	char *strptr;
    char *str_passed = {"Registered to Carl Schelin"};

    if ((strptr = malloc(20)) == NULL) {
        printf("Not enough memory to allocate strptr\n");
        exit(1);
    }

    setcolor(WHITE);
	setbkcolor((monitor==0 ? BLACK : BLUE));
	setusercharsize(2, 3, 1, 1);
	settextstyle(SMALL_FONT, HORIZ_DIR, 0);
	rectangle(3, 3, 637, (bottom_limit - 3));
	line( 3, bottom_limit - 33, 637, bottom_limit - 33);
	line(20, bottom_limit - 40, 630, bottom_limit - 40);
	line(24,  10,  24, bottom_limit - 40);
	for (j = (bottom_limit - 40); j > 5; j-=5) {
		if (j / 10 == (float) j / 10) {
			strptr = itoa((bottom_limit - 40) - j, buffer, 10);
			twidth = textwidth(strptr);
			outtextxy(18 - twidth, j - 5, strptr);
		}
		line( 19,   j,  24,   j);
	}
	setusercharsize(3, 2, 1, 1);
    outtextxy(630 - textwidth("FREE "VERSION), bottom_limit - 30, "FREE "VERSION);
    outtextxy(630 - textwidth(str_passed), bottom_limit - 20, str_passed);
	setusercharsize(1, 1, 1, 1);
	strptr = "Total Available Space";
	outtextxy(30, bottom_limit - 30, strptr);
	strptr = "Total Space in Use";
	outtextxy(30, bottom_limit - 18, strptr);
    setfillstyle(SOLID_FILL, (monitor==0 ? BLACK : RED));
	setcolor(WHITE);
	bar3d( 10, bottom_limit - 7, 20, (bottom_limit - 18), 6, 0);
    setfillstyle(SOLID_FILL, (monitor==0 ? BLACK : LIGHTMAGENTA));
	setcolor(WHITE);
	bar3d( 10, bottom_limit - 18, 20, (bottom_limit - 28), 6, 1);
    free(strptr);
}

void print_graph(int which, int drivetype, int total, int avail)
{
    int itotal, iavail, startloc, twidth = 0;
    char holding[20], message[100];
    char *totalptr, *availptr;

    itotal = (bottom_limit - 40) - total;
    iavail = (bottom_limit - 40) - avail;
    startloc = which * 23 + 2;
    if ((totalptr = malloc(20)) == NULL) {
        printf("Not enough memory to allocate %d of totalptr\n", which);
        exit(1);
    }
    if ((availptr = malloc(20)) == NULL) {
        printf("Not enough memory to allocate %d of availptr\n", which);
        exit(1);
    }
	settextstyle(SMALL_FONT, VERT_DIR, 0);
    if (itotal < 10) {
        totalptr = itoa(total, holding, 10);
        itotal = 10;
        twidth = textwidth(totalptr);
	}
    if (iavail < (twidth + 12)) {
        availptr = itoa(avail, holding, 10);
        iavail = twidth + 12;
	}
    setfillstyle(SOLID_FILL, (monitor==0 ? BLACK : RED));
	setcolor(WHITE);
    bar3d(startloc, iavail, startloc + 14, (bottom_limit - 40), 6, 0);
    if (avail > (bottom_limit - 50)) {
        setcolor((monitor==0 ? WHITE : WHITE));
        outtextxy(startloc + 1, iavail, availptr);
	}

    setfillstyle(SOLID_FILL, (monitor==0 ? BLACK : LIGHTMAGENTA));
	setcolor(WHITE);
    bar3d(startloc, itotal, startloc + 14, iavail, 6, 1);
    if (total > (bottom_limit - 40)) {
        setcolor((monitor==0 ? WHITE : YELLOW));
        outtextxy(startloc + 1, itotal, totalptr);
	}

    setcolor((monitor==0 ? WHITE : WHITE));
    sprintf(message, "%c: %s", which + 64, driveinfo[drivetype] +1);
    if (drivetype == -1)
        sprintf(message, "->%c<- %sDrive not responding.", which + 64, notready == NETDRIVE ? "Network " : "");
    twidth = textwidth(message);
    outtextxy(startloc + 1, (bottom_limit - 45) - twidth, message);
    free(totalptr);
    free(availptr);
}
#endif

