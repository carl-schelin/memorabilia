#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <d3l.h>

int  Verify_Login(void);
void Get_Information(void);
void Search_Memory(void);

char Login_Name[59];
char Default_Domain[21];
char Default_Org[21];

int  Capability_Class = 0;
char Search_Code[60];
char Query[60];
int  Search_Space = 0;
int  DomLen = 0;
int  OrgLen = 0;
int  LogLen = 0;
int  Convert = 0;
char *CapClass[] = {"User", "Admin", "Server", "Default"};

void main(int argc, char *argv[])
{
    char temp[30];

    printf("CONVERT v1.2, Copyright (C) 1990 by Carl Schelin\n");
    if (Verify_Login() == 0) {
        Get_Information();
        if (argc > 0) {
            if (stricmp(argv[argc], CapClass[0]) == 0) Convert = 02;
            if (stricmp(argv[argc], CapClass[1]) == 0) Convert = 03;
            if (stricmp(argv[argc], CapClass[2]) == 0) Convert = 04;
            if (stricmp(argv[argc], CapClass[3]) == 0) Convert = Capability_Class;
        }
        Search_Memory();
    }
}

int Verify_Login()
{
    int d3ltemp = 0;

    D3LGetLoginFlag(&d3ltemp);
    if (d3ltemp == 0) {
        printf("\nPlease login first...\n");
        return 1;
    }
    return 0;
}

void Get_Information()
{
    D3LGetLoginName(Login_Name);
    D3LGetDomainName(Default_Domain);
    D3LGetOrgName(Default_Org);
    D3LGetCapClass(Login_Name, &Capability_Class);
    strcpy(Search_Code, Default_Domain);
    DomLen = strlen(Default_Domain);
    OrgLen = strlen(Default_Org);
    LogLen = strlen(Login_Name);
    Search_Space = DomLen + OrgLen + LogLen + 5;
}

void Search_Memory()
{
    int j, k, m, value = 0;

    Query[0] = '\0';
    for (j = 0; j < 32000; j++) {
        for (m = 0; m < 16; m++) {
            value = peekb(j, m);
            if (value == Search_Code[0]) {
                for (k = 0; k < Search_Space + 1; k++) {
                    value = peekb(j, k + m);
                    Query[k] = value;
                }
                Query[Search_Space] = '\0';
                if (strcmp(Default_Domain, Query) == 0 && 
                    strcmp(Default_Org, Query + (DomLen + 1)) == 0 && 
                    strcmp(Login_Name, Query + (DomLen + OrgLen + 2)) == 0) {

                    Search_Space += m;
                    if (Convert > 0)
                        pokeb(j, Search_Space, Convert);
                    if (Convert == 0) 
                        printf("Convert [User | Admin | Server | Default]\n");
                    value = peekb(j, Search_Space);
                    printf("Your code is %x [%s]\n", value, CapClass[value - 2]);
                }
                else {
                    Query[0] = '\0';
                }
                if (strlen(Query) > 0) break;
            }
        }
        if (strlen(Query) > 0) break;
    }
    if (strlen(Query) == 0) {
        printf("Sorry, I am unable to find your Capability Class in a search from 0x000 to 0x7D00.\n");
        printf("You must not have LGL in hi-memory or loaded on your ethernet board (3c505 LPO)\n");
    }
}
