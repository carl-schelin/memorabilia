#include <conio.h>
#include <cxlvid.h>
#include <d3l.h>

void screen_setup(void);
int  verify_and_retrieve(void);


int CapClass;

char OrgName[59];
char UserName[59];

main()
{
    printf("Print Manager v1.0, Copyright (C) 1990 by Carl Schelin\n");
    if (verify_and_retrieve() == 0) {
        screen_setup();
    }
}


int verify_and_retrieve()
{
    int d3ltemp = 0;

    D3LGetLoginFlag(&d3ltemp);
    if (d3ltemp == 0) {
        printf("\nPlease login first...\n");
        return 1;
    }

    D3LGetCapabilityClass(&CapClass);
    if (CapClass != ADMINUSER) {
        printf("\nYou are not an Administrator...\n");
        return 1;
    }

    D3LGetLoginName(UserName);
    D3LGetOrgName(OrgName);
    return 0;
}

void screen_setup()
{
    box_(0, 0, 2, 79, 1, WHITE|_BLUE);
    fill_(1, 1, 1, 78, 32, WHITE|_BLUE);
    fill_(3, 0, 24, 79, 176, WHITE|_BLUE);
    textattr(WHITE + (BLUE << 4));
    gotoxy(2, 2);
    cprintf(" %s", UserName);
    gotoxy(73, 2);
    switch (CapClass) {
        case USER       : cprintf("  User");
                          break;
        case ADMINUSER  : cprintf(" Admin");
                          break;
        case SERVERUSER : cprintf("Server");
                          break;
    }
}

