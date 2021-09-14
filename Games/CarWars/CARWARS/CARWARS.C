#include <conio.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>
#include <cxlvid.h>
#include <cxlwin.h>
#include <cxlstr.h>
#include <cxlmou.h>

extern void display(void);
extern void display_help(void);
extern void fixborder(void);
extern void get_armor(void);
extern void get_armorpoints(void);
extern void get_bodymods(void);
extern void get_chassis(void);
extern void get_chassistype(void);
extern void get_duel_class(void);
extern void get_equipment(void);
extern int  get_numbertires(void);
extern void get_powerplant(void);
extern void get_powerplantmods(void);
extern void get_suspension(void);
extern void get_tires(void);
extern void get_tiremods(void);
extern void get_vehicle(void);
extern void get_weapons(void);
extern void logo(void);
extern void menubar(void);
extern void screen_setup(void);
void select_input(void);
extern void setup(void);
extern void utility_menu(void);

char car_types[9][14] = {"Subcompact", "Compact", "Mid-Sized", "Sedan",
   "Luxury", "Station Wagon", "Pickup", "Camper", "Van" };

int car_stats[9][7] = {
   { 300,   1000,   2300,    7,    0,   11,    5},
   { 400,   1300,   3700,   10,    0,   13,    6},
   { 600,   1600,   4800,   13,    0,   16,    8},
   { 700,   1700,   5100,   16,    0,   18,    9},
   { 800,   1800,   5500,   19,    0,   20,   10},
   { 800,   1800,   5500,   14,    7,   20,   10},
   { 900,   2100,   6500,   13,   11,   22,   11},
   {1400,   2300,   6500,   17,    7,   30,   14},
   {1000,   2000,   6000,   24,    6,   30,   14}
};

char chassis_types[4][12] = {"Light","Standard","Heavy","Extra Heavy"};

float chassis_stats[4][2] = {
    { -0.1, -0.2},
    {  0.0,  0.0},
    {  0.1,  0.5},
    {  0.2,  1.0}
};

char suspension_types[4][9] = {"Light","Improved","Heavy","Off-Road"};

float suspension_stats[4][2] = {
    { 0.0, 1.0},
    { 1.0, 2.0},
    { 1.5, 3.0},
    { 5.0, 2.0}
};

char powerplant_types[6][12] = {"Small","Medium","Large","Super",
    "Sport","Thunder-Cat"};

int powerplant_stats[6][5] = {
    { 500,  3,   5,    500,   800},
    { 700,  4,   8,   1000,  1400},
    { 900,  5,  10,   2000,  2000},
    {1100,  6,  12,   3000,  2600},
    {1000,  6,  12,   6000,  3000},
    {2000,  8,  15,  12000,  6700}
};

char powerplant_token[5] = {' ', '+', 'x', '*', '\0'};

char powerplant_modtypes[5][19] = {"Normal", "Platinum Catalysts",
    "Superconductors", "Combination"};

float powerplant_modstats[5][2] = {
    { 1.0, 1.0 },
    { 1.2, 1.05},
    { 1.5, 1.1 },
    { 1.7, 1.15}
};

char tire_types[6][11] = {"Standard","Heavy-Duty","PR","Solid",
    "Plasticore"};

int tire_stats[6][3] = {
    {   50,   30,   4 },
    {  100,   40,   6 },
    {  200,   50,   9 },
    {  500,   75,  12 },
    { 1000,  150,  20 }
};

char armor_types[8][14] = {"Normal","Fire Proof","Laser Reflec","Lsr Rflec FP",
    "Radarproof","Radarproof FP","Metal","LR Metal"};

float armor_stats[8][2] = {
    { 1.00, 1.0},
    { 2.00, 1.0},
    { 1.10, 1.1},
    { 2.50, 1.1},
    { 4.00, 1.0},
    { 8.00, 1.0},
    { 2.50, 5.0},
    { 2.75, 5.0}
};

int choice[6] = { 8, 3, 2, 4, 3, 2};
int fireproof = 0;
int handlingclass = 0;
int maxload = 0;
int modify[2] = { 0, 0};
int monitor = 0;
int monitorega = 0;
int monitortype = 0;
int monitorvga = 0;
int numbertires = 0;
int offroad = 0;
int quitprogram = 0;
int radial = 0;
int steelbelted = 0;
int tires[7] = { 0, 0, 0, 4, 0, 0, 0};
int tires_needed = 4;
int totalspace = 0;
int totalweight = 0;

long armor = 250;
long maxcosts = 20000;
long totalprice = 0;

float caframepr = 1.0;
float caframewt = 1.0;
float streampr = 1.0;
float streamsp = 1.0;
float slopepr = 1.0;
float slopesp = 1.0;

void main(int argc)
{
    msinit();
    delay(0);
    monitortype = videoinit();
    if (monitortype == 4 || monitortype == 11) {
        monitorvga = 1;
        monitorega = 1;
    }
    if (monitortype == 2 || monitortype == 9) monitorega = 1;
    if (monitortype > 6 && argc == 1) monitor = 1;
    screen_setup();
    while (quitprogram == 0) select_input();
    wclose();
    textattr(LGREY + (BLACK << 4));
    clrscr();
    setlines(25);
    showcur();
}

void screen_setup()
{
    hidecur();
    textattr(WHITE + ( (monitor==0 ? BLACK : BLUE) << 4));
    clrscr();
    textattr( (monitor==0 ? BLACK + (LGREY << 4) : WHITE + (BLUE << 4) ) );
    gotoxy(1, 1);
    cprintf("                                                                                ");
    fill_(1, 0, 50, 79, '°', WHITE|(monitor==0 ? _BLACK : _BLUE));
    menubar();
    logo();
}

void menubar()
{
    textattr( (monitor==0 ? BLACK + (LGREY << 4) : WHITE + (BLUE << 4) ) );
    gotoxy(1, 1);
    cprintf(" Class %d Duel    ", (long)(maxcosts / 1000));
    gotoxy(18, 1);
    cprintf("HC: %2d", handlingclass);
    gotoxy(26, 1);
    cprintf("Powerplant - DP: %2d Factors: %4d", powerplant_stats[choice[3]][2], powerplant_stats[choice[3]][4]);
    gotoxy(62, 1);
    cprintf("Chassis: %d Wheeled", tires_needed);
}

void logo()
{
    int j = 0;

    wopen(5, 15, 20, 64, 1, WHITE|(monitor==0 ? _BLACK : _MAGENTA), WHITE|(monitor==0 ? _BLACK : _MAGENTA));
    fixborder();
    textattr(LBLUE + (BLACK << 4));
    wgotoxy(1, 3);
    cprintf("ÛÛ²²±±°°");
    wgotoxy(2, 3);
    cprintf("ÛÛ²");
    wgotoxy(3, 3);
    cprintf("ÛÛ²");
    wgotoxy(4, 3);
    cprintf("ÛÛ²");
    wgotoxy(5, 3);
    cprintf("ÛÛ²²±±°°");
    delay(250);
    textattr(WHITE + (BLACK << 4));
    wgotoxy(1, 9);
    cprintf("ÛÛ²²±±°°");
    wgotoxy(2, 9);
    cprintf("ÛÛ²");
    wgotoxy(3, 9);
    cprintf("ÛÛ²²±±°°");
    wgotoxy(4, 14);
    cprintf("±°°");
    wgotoxy(5, 9);
    cprintf("ÛÛ²²±±°°");
    textattr(WHITE + ( (monitor==0 ? BLACK : MAGENTA) << 4));
    wgotoxy(2, 24);
    cprintf("Computer Software");
    wgotoxy(4, 25);
    cprintf("by Carl Schelin");
    for (j = 0; j < 20; j++) {
        wgotoxy(3, 32);
        cprintf("|\b");
        delay(20);
        cprintf("\\\b");
        delay(20);
        cprintf("-\b");
        delay(20);
        cprintf("/");
        delay(20);
    }
    textattr((monitor==0 ? WHITE + (BLACK << 4) : YELLOW + (MAGENTA << 4) ) );
    wgotoxy(3, 31);
    cprintf("-*-");
    textattr(WHITE + ( (monitor==0 ? BLACK : MAGENTA) << 4));
    wgotoxy(8, 6);
    cprintf("CarWars Vehicular Generation Program");
}    

void select_input()
{
    int c;
    if ((c = getch()) == 0)
        c = getch() | 128;

    switch(c) {

            /*  Alt-Q or ESC will End CarWars  */

        case 144:
        case  27:
            quitprogram = c;
            break;

            /*  Alt-G selects Generate Vehicle  */

        case 162:
            display();
            break;

            /*  Alt-U selects Utility Menu  */

        case 150:
            utility_menu();
            break;

            /*  Alt-C selects Dueling Class Price  */

        case 174:
            get_duel_class();
            menubar();
            break;

            /*  F1 selects Help  */

        case 187:
            display_help();
            break;

        default:
            break;
    }
}

void display_help()
{
    wborder(0);
    wopen(4, 55, 9, 75, 1, (monitor==0 ? BLACK : BLUE) |_LGREY, (monitor==0 ? BLACK : BLUE)|_LGREY);
    fixborder();
    wprintf(" F1    - Help\n");
    wprintf(" Alt-G - Generate\n");
    wprintf(" Alt-U - Utilities\n");
    wprintf(" Alt-C - Max Costs");
    wgetc();
    wclose();
    wborder(1);
}

void utility_menu()
{
    int which = 0;

    wborder(0);
    wmenubeg(16, 23, 22, 36, 1, WHITE| (monitor==0 ? _BLACK : _RED),
      WHITE|(monitor==0 ? _BLACK : _RED), fixborder);
        wmenuitem(0, 0, "Color", 'C', 1, M_CLOSE, NULL, 0, 0);
        wmenuitem(1, 0, "Monochrome", 'M', 2, M_CLOSE, NULL, 0, 0);
        wmenuitem(2, 0, "25 Line", '2', 3, M_CLOSE, NULL, 0, 0);
        wmenuitem(3, 0, "43 Line", '4', 4, (monitorega==0 ? M_CLOSE|M_NOSEL : M_CLOSE), NULL, 0, 0);
        wmenuitem(4, 0, "50 Line", '5', 5, (monitorvga==0 ? M_CLOSE|M_NOSEL : M_CLOSE), NULL, 0, 0);
        wmenuend('V', M_VERT|M_OMNI, 12, 1, WHITE|(monitor==0 ? _BLACK : _RED),
      WHITE|(monitor==0 ? _BLACK : _RED), LGREY|(monitor==0 ? _BLACK : _RED),
      (monitor==0 ? BLACK : RED)|_LGREY);
    which = wmenuget();
    wborder(1);
    switch(which) {
        case 1:
            monitor = 1;
            screen_setup();
            break;
        case 2:
            monitor = 0;
            screen_setup();
            break;
        case 3:
            setlines(25);
            hidecur();
            break;
        case 4:
            setlines(43);
            hidecur();
            break;
        case 5:
            setlines(50);
            hidecur();
            break;
        default:
            break;
    }
}

void setup()
{
    int pricetemp = 0;
    int weighttemp = 0;
    int body_modprice = 0;
    int body_modweight = 0;
    int body_modspace = 0;
    int tireprice = 0;
    int tireweight = 0;
    int j = 0;


    /*  Initialize so we don't get erronous results  */

    totalprice = 0;
    totalweight = 0;
    totalspace = 0;

    /*  Make the text color match the other colors in the window  */

    textattr( (monitor==0 ? LGREY + (BLACK << 4) : WHITE + (GREEN << 4)) );

    /*  Figure the modified totals for body weight, price, and spaces when
        using the Carbon Aluminum frame, sloped or streamlined armor.  */

    body_modprice = car_stats[choice[0]][0] * caframepr * slopepr;
    body_modweight = car_stats[choice[0]][1] * caframewt;
    body_modspace = car_stats[choice[0]][3] * streamsp * slopesp;

    /*  Here's the first printout. Car Body prices and weights  */

    wgotoxy(0, 8);
    cprintf(": %14s  %5d   %4d   -- ", car_types[choice[0]], (int) (body_modprice * streampr), (int) body_modweight);
    maxload = car_stats[choice[0]][2];
    totalprice += body_modprice * streampr;
    totalweight += body_modweight;

    /*  Chassis modifications.  */

    pricetemp = (int)(body_modprice * chassis_stats[choice[1]][1]) + (tires_needed==6 ? 100 : 0);
    wgotoxy(1, 8);
    cprintf(": %14s  %5d    --    -- ", chassis_types[choice[1]], pricetemp);
    totalprice += pricetemp;
    maxload = car_stats[choice[0]][2] + (int)(maxload * chassis_stats[choice[1]][0]);

    /*  Suspension printout.  */

    pricetemp = (int)(body_modprice * suspension_stats[choice[2]][0]);
    wgotoxy(2, 11);
    cprintf(": %11s  %5d    --    -- ", suspension_types[choice[2]], pricetemp);
    totalprice += pricetemp;
    handlingclass = suspension_stats[choice[2]][1];
    if (choice[0] == 8) handlingclass -= 1;
    if (choice[0] == 0) handlingclass += 1;

    /*  Powerplant modifications  */

    wgotoxy(3, 0);
    cprintf("%c", powerplant_token[modify[0]]);
    pricetemp = powerplant_stats[choice[3]][3] * powerplant_modstats[modify[0]][0];
    wgotoxy(3, 11);
    cprintf(":%12s  %5d   %4d   %2d ", powerplant_types[choice[3]], pricetemp,
        powerplant_stats[choice[3]][0], powerplant_stats[choice[3]][1]);
    totalprice += pricetemp;
    totalweight += powerplant_stats[choice[3]][0];
    totalspace += powerplant_stats[choice[3]][1];

    /*  Tires and any modifications for them  */

    for (j = 0; j < 7; j++) {
        if (tires[j] > 0) {
            tireprice += tire_stats[j][0] * tires[j];
            tireweight += tire_stats[j][1] * tires[j];
        }
    }
    wgotoxy(4, 7);
    cprintf("(%d): %12s  %5d   %4d   -- ", tires[choice[4]], tire_types[choice[4]],
        tireprice, tireweight);
    totalprice += tireprice;
    totalweight += tireweight;

    /*  Armor and armor restrictions  */

    pricetemp = (int)(armor_stats[choice[5]][0] * car_stats[choice[0]][5]);
    weighttemp = (int)(armor_stats[choice[5]][1] * car_stats[choice[0]][6]);
    wgotoxy(5, 7);
    cprintf("%3ld:%13s %6ld  %5d   -- ", armor, armor_types[choice[5]], 
        armor * pricetemp, armor * weighttemp);
    totalprice += armor * pricetemp;
    totalweight += armor * weighttemp;

    /*  Change the colors so it looks different from the rest of the window  */

    textattr(monitor==0 ? WHITE + (BLACK << 4) : YELLOW + (GREEN << 4) );
    wgotoxy(8, 1);
    cprintf("Spaces: %2d  Load: %4d", totalspace, maxload);

    /*  Now print the totals.  */

    wgotoxy(8, 25);
    textattr( (monitor==0 ? LGREY + (BLACK << 4) : LCYAN + (GREEN << 4)) );
    if (totalprice > maxcosts)
        textattr( (monitor==0 ? WHITE + (BLACK << 4) : RED + (GREEN << 4)) + BLINK);
    cprintf("%6ld", totalprice);

    wgotoxy(8, 33);
    textattr( (monitor==0 ? LGREY + (BLACK << 4) : LCYAN + (GREEN << 4)) );
    if (totalweight > maxload)
        textattr( (monitor==0 ? WHITE + (BLACK << 4) : RED + (GREEN << 4)) + BLINK);
    cprintf("%5d", totalweight);

    wgotoxy(8, 41);
    textattr( (monitor==0 ? LGREY + (BLACK << 4) : LCYAN + (GREEN << 4)) );
    if (totalspace > body_modspace)
        textattr( (monitor==0 ? WHITE + (BLACK << 4) : RED + (GREEN << 4)) + BLINK);
    cprintf("%2d", totalspace);

    menubar();
}

void display()
{
    wborder(0);
    wopen(3, 3, 13, 48, 1, WHITE|(monitor==0 ? _BLACK : _GREEN), WHITE|(monitor==0 ? _BLACK : _GREEN));
    fixborder();
    setup();
    wmenubegc();
        wmenuitem(0, 1, "Vehicle", 'V', 0, 0, get_vehicle, 0, 0);
        wmenuitem(1, 1, "Chassis", 'C', 1, 0, get_chassis, 0, 0);
        wmenuitem(2, 1, "Suspension", 'S', 2, 0, get_suspension, 0, 0);
        wmenuitem(3, 1, "PowerPlant", 'P', 3, 0, get_powerplant, 0, 0);
        wmenuitem(4, 1, "Tires", 'T', 4, 0, get_tires, 0, 0);
        wmenuitem(5, 1, "Armor", 'A', 5, 0, get_armor, 0, 0);
        wmenuitem(6, 1, "Weapons", 'W', 6, 0, get_weapons, 0, 0);
        wmenuitem(7, 1, "Equipment", 'E', 7, 0, get_equipment, 0, 0);
    wmenuend(0, M_VERT|M_OMNI, 0, 0, WHITE|(monitor==0 ? _BLACK : _GREEN),
        WHITE|(monitor==0 ? _BLACK : _GREEN), LGREY|(monitor==0 ? _BLACK : _GREEN),
        BLACK|_LGREY);
    wmenuget();
    wborder(1);
    wclose();
}

void get_vehicle()
{
    int j = 0;

    wborder(0);
    wmenubeg(11, 58, 21, 74, 1, WHITE| (monitor==0 ? _BLACK : _RED), WHITE|(monitor==0 ? _BLACK : _RED), fixborder);
        for (j = 0; j < 9; j++)
            wmenuitem(j, 0, car_types[j], car_types[j][0], j, M_CLOSE, get_bodymods, 0, 0);
    wmenuend('V', M_VERT, 15, 1, WHITE|(monitor==0 ? _BLACK : _RED), 
        WHITE|(monitor==0 ? _BLACK : _RED), LGREY|(monitor==0 ? _BLACK : _RED),
        (monitor==0 ? BLACK : RED)|_LGREY);
    j = wmenuget();
    if (j != -1) choice[0] = j;
    wborder(1);
    setup();
}

void get_bodymods()
{
    int which = 0;
    char check[3][2];

    wborder(0);
    wopen(15, 20, 19, 46, 1, WHITE| (monitor==0 ? _BLACK : _RED), WHITE|(monitor==0 ? _BLACK : _RED));
    fixborder();
    winpbeg(WHITE|(monitor==0 ? _BLACK : _RED), WHITE|(monitor==0 ? _BLACK : _RED));
        winpdef(0, 0, check[0], "' Carbon-Aluminum Frame 'Y", 'U', 0, NULL, 0);
        winpdef(1, 0, check[1], "' Streamlining          'Y", 'U', 0, NULL, 0);
        winpdef(2, 0, check[2], "' Sloped                'Y", 'U', 0, NULL, 0);
    which = winpread();
    if (which == 0) {
        if ((which = strcmp(check[0], "Y")) == 0) {
            caframepr = 4.0;
            caframewt = 0.5;
        }
        else {
            caframepr = 1.0;
            caframewt = 1.0;
        }
        if ((which = strcmp(check[1], "Y")) == 0) {
            streampr = 1.5;
            streamsp = 1.1;
        }
        else {
            streampr = 1.0;
            streamsp = 1.0;
        }
        if ((which = strcmp(check[2], "Y")) == 0) {
            slopepr = 1.1;
            slopesp = 1.1;
            if (streamsp == 1.1) slopesp = 1.05;
        }
        else {
            slopepr = 1.0;
            slopesp = 1.0;
        }
    }
    wclose();
    wborder(1);
    hidecur();
}

void get_chassis()
{
    int j = 0;

    wborder(0);
    wopen(16, 23, 21, 37, 1, WHITE|(monitor==0 ? _BLACK : _RED), 
        WHITE|(monitor==0 ? _BLACK : _RED));
    fixborder();
    wmenubegc();
        for (j = 0; j < 4; j++)
            wmenuitem(j, 0, chassis_types[j], chassis_types[j][0], j, M_CLOSE, NULL, 0, 0);
    wmenuend('V', M_VERT, 13, 1, WHITE|(monitor==0 ? _BLACK : _RED), 
        WHITE|(monitor==0 ? _BLACK : _RED), LGREY|(monitor==0 ? _BLACK : _RED),
        (monitor==0 ? BLACK : RED)|_LGREY);
    j = wmenuget();
    if (j != -1) {
        choice[1] = j;
        get_chassistype();
        menubar();
    }
    wclose();
    wborder(1);
    setup();
}

void get_chassistype()
{
    int j = 0;

    if (choice[0] > 1)
        if (choice[1] == 3 && choice[0] > 5) {
            tires_needed = 6;
        }
        else {
            wborder(0);
            wmenubeg(16, 41, 19, 61, 1, WHITE| (monitor==0 ? _BLACK : _RED), WHITE|(monitor==0 ? _BLACK : _RED), fixborder);
                wmenuitem(0, 0, "4 Wheeled Chassis", '4', 0, M_CLOSE, NULL, 0, 0);
                wmenuitem(1, 0, "6 Wheeled Chassis", '6', 1, M_CLOSE, NULL, 0, 0);
            wmenuend(tires_needed, M_VERT, 19, 1, WHITE|(monitor==0 ? _BLACK : _RED), WHITE|(monitor==0 ? _BLACK : _RED), LGREY|(monitor==0 ? _BLACK : _RED), (monitor==0 ? BLACK : RED)|_LGREY);
            j = wmenuget();
            if (j != -1) tires_needed = (j==0 ? 4 : 6);
            wborder(1);
        }
}

void get_suspension()
{
    int j = 0;

    wborder(0);
    wmenubeg(16, 23, 21, 34, 1, WHITE| (monitor==0 ? _BLACK : _RED), WHITE|(monitor==0 ? _BLACK : _RED), fixborder);
        for (j = 0; j < 4; j++)
            wmenuitem(j, 0, suspension_types[j], suspension_types[j][0], j, M_CLOSE, NULL, 0, 0);
    wmenuend('V', M_VERT, 10, 1, WHITE|(monitor==0 ? _BLACK : _RED), 
        WHITE|(monitor==0 ? _BLACK : _RED), LGREY|(monitor==0 ? _BLACK : _RED),
        (monitor==0 ? BLACK : RED)|_LGREY);
    j = wmenuget();
    if (j != -1) choice[2] = j;
    wborder(1);
    setup();
}

void get_powerplant()
{
    int j = 0;

    wborder(0);
    wmenubeg(16, 23, 23, 37, 1, WHITE| (monitor==0 ? _BLACK : _RED), WHITE|(monitor==0 ? _BLACK : _RED), fixborder);
        for (j = 0; j < 6; j++)
            wmenuitem(j, 0, powerplant_types[j], powerplant_types[j][0], j, M_CLOSE, get_powerplantmods, 0, 0);
    wmenuend('V', M_VERT, 13, 1, WHITE|(monitor==0 ? _BLACK : _RED), 
        WHITE|(monitor==0 ? _BLACK : _RED), LGREY|(monitor==0 ? _BLACK : _RED),
        (monitor==0 ? BLACK : RED)|_LGREY);
    j = wmenuget();
    if (j != -1) choice[3] = j;
    wborder(1);
    setup();
}

void get_powerplantmods()
{
    int j = 0;

    wborder(0);
    wmenubeg(16, 43, 21, 64, 1, WHITE| (monitor==0 ? _BLACK : _RED), WHITE|(monitor==0 ? _BLACK : _RED), fixborder);
        for (j = 0; j < 4; j++)
            wmenuitem(j, 0, powerplant_modtypes[j], powerplant_modtypes[j][0], j, M_CLOSE, NULL, 0, 0);
    wmenuend('V', M_VERT, 20, 1, WHITE|(monitor==0 ? _BLACK : _RED), 
        WHITE|(monitor==0 ? _BLACK : _RED), LGREY|(monitor==0 ? _BLACK : _RED),
        (monitor==0 ? BLACK : RED)|_LGREY);
    j = wmenuget();
    if (j != -1) modify[0] = j;
    wborder(1);
}

void get_tires()
{
    int j = 0;

    wborder(0);
    wopen(16, 12, 22, 25, 1, WHITE| (monitor==0 ? _BLACK : _RED), WHITE|(monitor==0 ? _BLACK : _RED));
    fixborder();
    wmenubegc();
        for (j = 0; j < 5; j++)
            wmenuitem(j, 0, tire_types[j], tire_types[j][0], j, M_CLOSE, NULL, 0, 0);
    wmenuend('V', M_VERT, 12, 1, WHITE|(monitor==0 ? _BLACK : _RED), 
        WHITE|(monitor==0 ? _BLACK : _RED), LGREY|(monitor==0 ? _BLACK : _RED),
        (monitor==0 ? BLACK : RED)|_LGREY);
    j = wmenuget();
    if (j != -1) {
        choice[4] = j;
        tires[j] = get_numbertires();
    }
    wclose();
    wborder(1);
    setup();
}

int get_numbertires()
{
    int which = 0;
    char check[2];

    wborder(0);
    wopen(17, 30, 19, 44, 1, WHITE| (monitor==0 ? _BLACK : _RED), WHITE|(monitor==0 ? _BLACK : _RED));
    fixborder();
    winpbeg(WHITE|(monitor==0 ? _BLACK : _RED), WHITE|(monitor==0 ? _BLACK : _RED));
        winpdef(0, 0, check, "' How Many: '%", 0, 0, NULL, 0);
    which = winpread();
    if (which == 0 && atoi(check) >= 0) {
        which = atoi(check);
        if (which > 0 && choice[4] != 4) get_tiremods();
    }
    else
        which = 0;
    wclose();
    wborder(1);
    hidecur();
    return (which);
}

void get_tiremods()
{
    int which = 0;
    char check[4][2];

    wborder(0);
    wopen(17, 50, 22, 66, 1, WHITE| (monitor==0 ? _BLACK : _RED), WHITE|(monitor==0 ? _BLACK : _RED));
    fixborder();
    winpbeg(WHITE|(monitor==0 ? _BLACK : _RED), WHITE|(monitor==0 ? _BLACK : _RED));
        winpdef(0, 0, check[0], "' Steelbelted 'Y", 'U', 0, NULL, 0);
        winpdef(1, 0, check[1], "' Radial      'Y", 'U', 0, NULL, 0);
        winpdef(2, 0, check[2], "' Off-Road    'Y", 'U', 0, NULL, 0);
        winpdef(3, 0, check[3], "' Fireproof   'Y", 'U', 0, NULL, 0);
    which = winpread();
    if (which == 0) {
        if ((which = strcmp(check[0], "Y")) == 0) 
            steelbelted = 1;
        else
            steelbelted = 0;
        if ((which = strcmp(check[1], "Y")) == 0)
            radial = 1;
        else
            radial = 0;
        if ((which = strcmp(check[2], "Y")) == 0)
            offroad = 1;
        else
            offroad = 0;
        if ((which = strcmp(check[3], "Y")) == 0)
            fireproof = 1;
        else
            fireproof = 0;
    }
    wclose();
    wborder(1);
    hidecur();
}

void get_armor()
{
    int j = 0;
    int armorprice = 0;
    int armorweight = 0;
    char tempdata[8][26];

    for (j=0 ; j < 8; j++) {
        armorprice = (int)((maxcosts - totalprice) / (car_stats[choice[0]][5] * armor_stats[j][0]));
        armorweight = (int)((maxload - totalweight) / (car_stats[choice[0]][6] * armor_stats[j][1]));
        sprintf(tempdata[j], "(%3d) %s", (armorprice<armorweight ? armorweight : armorprice), armor_types[j]);
    }
    wborder(0);
    wopen(13, 23, 22, 46, 1, WHITE| (monitor==0 ? _BLACK : _RED), WHITE|(monitor==0 ? _BLACK : _RED));
    fixborder();
    wmenubegc();
        for (j = 0; j < 8; j++)
            wmenuitem(j, 0, tempdata[j], armor_types[j][0], j, M_CLOSE, NULL, 0, 0);
    wmenuend(armor_types[choice[5]][0], M_VERT, 20, 1, WHITE|(monitor==0 ? _BLACK : _RED), 
        WHITE|(monitor==0 ? _BLACK : _RED), LGREY|(monitor==0 ? _BLACK : _RED),
        (monitor==0 ? BLACK : RED)|_LGREY);
    j = wmenuget();
    if (j != -1) {
        choice[5] = j;
        get_armorpoints();
    }
    wclose();
    wborder(1);
    setup();
}

void get_armorpoints()
{
    int which = 0;
    char check[4];

    wborder(0);
    wopen(15, 45, 17, 60, 1, WHITE| (monitor==0 ? _BLACK : _RED), WHITE|(monitor==0 ? _BLACK : _RED));
    fixborder();
    winpbeg(WHITE|(monitor==0 ? _BLACK : _RED), WHITE|(monitor==0 ? _BLACK : _RED));
        winpdef(0, 0, check, "' Armor: '%%%%%", 0, 0, NULL, 0);
    which = winpread();
    if (which == 0 && atoi(check) >= 0) armor = atoi(check);
    wclose();
    wborder(1);
    hidecur();
}

void get_weapons()
{
    wopen(10, 20, 20, 60, 1, WHITE|_BLUE, WHITE|_BLUE);
    fixborder();
    wclose();
    setup();
}

void get_equipment()
{
    setup();
}

void get_duel_class()
{
    int which = 0;
    char check[7];

    wopen(15, 24, 17, 55, 1, WHITE| (monitor==0 ? _BLACK : _RED), WHITE|(monitor==0 ? _BLACK : _RED));
    fixborder();
    winpbeg(WHITE|(monitor==0 ? _BLACK : _RED), WHITE|(monitor==0 ? _BLACK : _RED));
        winpdef(0, 0, check, "' Maximum Vehicle Cost: '%%%%%%", 0, 0, NULL, 0);
    which = winpread();
    if (which == 0) maxcosts = atol(check);
    wclose();
    hidecur();
}

void fixborder()
{
    wshadow((monitor==0 ? LGREY : DGREY)|_BLACK);
}

