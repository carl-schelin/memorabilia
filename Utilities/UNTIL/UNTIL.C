#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <TcxlCur.H>
#include <TcxlWin.H>

IntT sleep(NOARG);
VOID buildsleep(NOARG);

ChrT clocksleep[9];
ChrT clockhold[9], clocknow[9];
ChrT timewait[9];
IntT Novell;
IntT startsleep = 30;
WndT ssaver;

VOID main(IntT argc, ChrP argv[])
{
    WndT clock, tick;
    ChrT timenow[40];
    ChrT inputfile[256], infile[_MAX_PATH], sleepin[40];
    IntT ch, j, k, help, tosleep;
    FILE *input;

    printf("Until v1.0, Copyright 1996 by Carl Schelin, All Rights Reserved\n");
    while (kbhit())
        ch = getch();
    strcpy(infile, "");
    strcpy(timewait, "");
    tosleep = 1;
    Novell = 0;
    help = 0;
    if (argc > 1) {
        for (j = 1; j < argc; j++) {
            for (k = 0; k < (IntT)strlen(argv[j]); k++) {
                if (argv[j][k] == ':') {
                    strcpy(timewait, argv[j]);
                    break;
                }
                if (argv[j][k] == '.') {
                    strcpy(infile, argv[j]);
                    break;
                }
            }
            if (stricmp(argv[j], "NOSLEEP") == 0)
                tosleep = 0;
            if (stricmp(argv[j], "NOVELL") == 0)
                Novell = 1;
            if (stricmp(argv[j], "/?") == 0)
                help = 1;
            if (stricmp(argv[j], "SHORT") == 0)
                startsleep = 5;
        }
    }
    else
        help = 1;
    if (help) {
        printf("\nSyntax: Until hh:mm:ss [filename.ext] [NOSLEEP] [NOVELL] [SHORT]\n");
        printf("\nWhere:\n");
        printf("    hh:mm:ss     - Zero padded military time to exit Until.\n");
        printf("    filename.ext - File containing text to display.\n");
        printf("    NOSLEEP      - Do not start screen saver.\n");
        printf("    NOVELL       - Use red block screen saver.\n");
        printf("    SHORT        - Start screen saver in 5 seconds not 30.\n");
        exit(2);
    }
    buildsleep();
    srand((unsigned)time(NULL));
    TcxlInit();
    CurHide();
    Wopen(0, 0, VidDep, VidWid, BOX_SPA, WHITE|_BLUE, WHITE|_BLUE);
    Wopen(1, 5, 3, VidWid - 6, BOX_DBL, WHITE|_GREEN, WHITE|_GREEN);
    WputCen("Until v1.0, Copyright 1996 by Carl Schelin, All Rights Reserved");
    Wshadow(DGREY|_BLACK);
    Wopen(VidDep - 5, 5, VidDep - 3, VidWid - 6, BOX_DBL, WHITE|_GREEN, WHITE|_GREEN);
    WputCen("Press any key to continue, <Esc> to stop and exit");
    Wshadow(DGREY|_BLACK);
    Wopen(6, VidWid / 2 - 19, 6, VidWid / 2 + 19, BOX_SPA, WHITE|_BLUE, WHITE|_BLUE);
    strcpy(timenow, "System will be restarted at: ");
    strcat(timenow, timewait);
    WputCen(timenow);
    clock = Wopen(VidDep - 7, VidWid / 2 - 19, VidDep - 7, VidWid / 2 + 19, BOX_SPA, WHITE|_BLUE, WHITE|_BLUE);
    strcpy(timenow, "The current time is: ");
    strcat(timenow, SysTime(1));
    WputCen(timenow);
    ssaver = Wopen(VidDep - 6, VidWid / 2 - 19, VidDep - 6, VidWid / 2 + 19, BOX_SPA, WHITE|_BLUE, WHITE|_BLUE);
    if (tosleep == 0)
        WputCen("Screen Saver off");
    else 
        WputCen(" Sleep in: 30 seconds ");
    tick = Wopen(VidDep / 2 - 4, VidWid / 2 - 19, VidDep / 2 + 4, VidWid / 2 + 19, BOX_SPA, WHITE|_BLUE, WHITE|_BLUE);
    if ((input = fopen(infile, "r")) != NULL) {
        for (j = 0; j < 9; j++) {
            fgets(inputfile, 256, input);
            if (!feof(input))
                Wputs(inputfile);
        }
        fclose(input);
    }
    strcpy(clockhold, SysTime(1));
    while ((strcmp(clocknow, timewait) != 0)) {
        strcpy(clocknow, SysTime(1));
        if (tosleep) {
            Wactiv(ssaver);
            strcpy(sleepin, " To sleep at ");
            strcat(sleepin, clocksleep);
            WputCen(sleepin);
            if (strcmp(clocknow, clocksleep) == 0) {
                if (sleep())
                    break;
                buildsleep();
            }
        }
        if (strcmp(clocknow, clockhold) != 0) {
            strcpy(clockhold, clocknow);
            Wactiv(clock);
            strcpy(timenow, "The current time is: ");
            strcat(timenow, SysTime(1));
            WputCen(timenow);
        }
        if (kbhit()) {
            ch = getch();
            break;
        }
    }
    Wclose(); /* text window             */
    Wclose(); /* time until screen saver */
    Wclose(); /* current time            */
    Wclose(); /* exit time               */
    Wclose(); /* press any key           */
    Wclose(); /* copyright by            */
    Wclose(); /* background window       */
    CurShow();
    if (ch == '\x1B')
        exit(1);
    exit(0);
}

IntT sleep(NOARG)
{
    IntT ch, j;
    IntT xcoor[10], ycoor[10];
    IntT startx, starty, endx, endy;
    ChrT string[11][2] = {
        " ", ".", ".", ".", "z", "z", "z", "Z", "Z", "Z"};
    ChrT novell[11][3] = {"  ", "°°", "°°", "°°", "±±", "±±", "²²", "²²", "ÛÛ", "ÛÛ", "ÛÛ"};
    IntT flagx[10], flagy[10];
    ChrT clkhold[12], clknow[12];
    IntT dowesleep;
    AtrT color;

    Wopen(0, 0, VidDep, VidWid, BOX_SPA, YELLOW|_BLACK, YELLOW|_BLACK);
    for (j = 0; j < 10; j++) {
        xcoor[j] = j;
        ycoor[j] = j;
        flagx[j] = 1;
        flagy[j] = 1;
        if (Novell)
            Wprts((BytT)xcoor[j], (BytT)ycoor[j], RED|_BLACK, novell[j]);
        else
            Wprts((BytT)xcoor[j], (BytT)ycoor[j], YELLOW|_BLACK, string[j]);
    }
    strcpy(clkhold, SysTime(0));
    clkhold[11] = '\0';
    dowesleep = 0;
    color = YELLOW;
    while (!kbhit()) {
        strcpy(clocknow, SysTime(1));
        if (strcmp(clocknow, timewait) == 0) {
            dowesleep = 1;
            break;
        }
        strcpy(clknow, SysTime(0));
        clknow[11] = '\0';
        if (strcmp(clknow, clkhold) != 0) {
            strcpy(clkhold, clknow);
            startx = starty = 0;
            endx = VidDep;
            endy = VidWid;
/*            if ((rand() % 100) == 1)
                if (flagx[9] == 0)
                    startx = xcoor[9] - 1;
                else
                    endx = xcoor[9] + 1;
            if ((rand() % 100) == 1)
                starty = endy = ycoor[9];*/
            if ((rand() % 100) == 1)
                color = (AtrT)(rand() % 7) + DGREY;
            for (j = 0; j < 10; j++) {
                if (flagx[j] == 1)
                    xcoor[j]++;
                if (flagx[j] == 0)
                    xcoor[j]--;
                if (flagy[j] == 1)
                    ycoor[j]++;
                if (flagy[j] == 0)
                    ycoor[j]--;
                if (xcoor[j] > endx-1) {
                    flagx[j] = 0;
                    xcoor[j] = endx-2;
                }
                if (xcoor[j] < 0) {
                    flagx[j] = 1;
                    xcoor[j] = startx + 1;
                }
                if (ycoor[j] > endy-1) {
                    flagy[j] = 0;
                    ycoor[j] = endy-2;
                }
                if (ycoor[j] < 0) {
                    flagy[j] = 1;
                    ycoor[j] = starty + 1;
                }
                if (Novell)
                    Wprts((BytT)xcoor[j], (BytT)ycoor[j], RED|_BLACK, novell[j]);
                else
                    Wprts((BytT)xcoor[j], (BytT)ycoor[j], color|_BLACK, string[j]);
            }
        }
    }
    Wclose();
    while (kbhit())
        ch = getch();
    return dowesleep;
}

VOID buildsleep(NOARG)
{
    ChrT clkhold[9];
    IntT sleephour, sleepmin, sleepsec;

    strcpy(clkhold, SysTime(1));
    sleepsec = atoi(clkhold + 6);
    clockhold[7] = '\0';
    sleepmin = atoi(clkhold + 3);
    clockhold[4] = '\0';
    sleephour =atoi(clkhold);
    sleepsec += startsleep;
    if (sleepsec > 60) {
        sleepmin++;
        sleepsec -= 60;
    }
    if (sleepmin > 60) {
        sleephour++;
        sleepmin -= 60;
    }
    sprintf(clocksleep, "%02d:%02d:%02d", sleephour, sleepmin, sleepsec);
}

