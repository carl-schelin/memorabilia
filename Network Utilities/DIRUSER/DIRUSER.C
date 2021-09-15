#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <d3l.h>
#include <cxlvid.h>
#include <cxlwin.h>

void display_data(void);
void get_aliases(void);
void get_domains(void);
void get_groups(void);
void get_memberships(void);
void get_organizations(void);
void please_wait(void);
int verify_and_retrieve(void);

char username[60];
char org_name[21];
char domain_name[21];
char group_name[21];
char groups[23][60];
char aliases[7][60];

int alias_number = 1;
int group_number = 1;
int alias_length = 0;
int group_length = 0;

int main(int argc, char *argv[])
{
    int j, *sptr, row, col;

    printf("List Properties v1.0, Copyright (C) 1990, by Carl Schelin\n");
    if (argc > 1) {
        strcpy(username, argv[1]);
        for (j = 2; j < argc; j++) {
            strcat(username, " ");
            strcat(username, argv[j]);
        }
    }
    else {
        D3LGetLoginName(username);
    }
    if (verify_and_retrieve() != 0) exit(1);
    printf("Getting Members from the Name Service...\n");
    readcur(&row, &col);
    hidecur();
    videoinit();
    sptr = ssave();
    please_wait();
    get_organizations();
    wclose();
    wclose();
    display_data();
    getch();
    wcloseall();
    srestore(sptr);
    gotoxy_(col + 1, row + 1);
    showcur();
    return 0;
}

int verify_and_retrieve()
{
    int d3ltemp = 0, usertype, error;

    D3LGetLoginFlag(&d3ltemp);
    if (d3ltemp == 0) {
        printf("\nPlease login first...\n");
        return 1;
    }

    error = D3LGetCHType(username, username, &usertype);
    if (error > 0) {
        printf("\nERROR: Name Service Returned an Error: User Not Found!\n");
        return 1;
    }
    if (usertype != TYPE_USER) {
        printf("\nNeeds to be a User...\n");
        return 1;
    }

    D3LGetOrgName(org_name);
    D3LGetDomainName(domain_name);
    return 0;
}

void please_wait()
{
    fill_(0, 0, 24, 79, '±', BLUE|_LGREY);
    wopen(1, 2, 3, 77, 5, RED|_LGREY, RED|_LGREY);
        wshadow(DGREY|_BLACK);
        wprints(1, 10, RED|_LGREY, "List Properties v1.0, Copyright (C) 1990, by Carl Schelin");
    wopen(19, 15, 22, 65, 5, YELLOW|_BLACK, YELLOW|_BLACK);
        wshadow(DGREY|_BLACK);
        wprints(1, 2, YELLOW|_BLACK, "DIRUSER lists all Memberships and retrieves all");
        wprints(2, 2, YELLOW|_BLACK, "Aliases from the Name Service and displays them");
    wopen(8, 20, 15, 60, 5, WHITE|_BLUE, WHITE|_BLUE);
        wshadow(DGREY|_BLACK);
        wprints(1, 13, BLINK|WHITE|_BLUE, "Please Wait...");
}

void get_organizations()
{
    char obuf[2048];
    int j = 0, total = -1, number_orgs;

    D3LEnumOrganizations("*", obuf, 2048, &number_orgs);
    for (j = 1; j <= number_orgs; j++) {
        strcpy(org_name, obuf + total + 1);
        total = strlen(obuf);
        obuf[total] = ' ';
        wprints(3, 1, WHITE|_BLUE, "Organization:                 ");
        wprints(3, 15, WHITE|_BLUE, org_name);
        get_domains();
    }
}

void get_domains()
{
    char dbuf[2048];
    int j = 0, total = -1, number_domains;

    D3LEnumDomains(org_name, "*", dbuf, 2048, &number_domains);
    for (j = 1; j <= number_domains; j++) {
        strcpy(domain_name, dbuf + total + 1);
        total = strlen(dbuf);
        dbuf[total] = ' ';
        wprints(4, 1, WHITE|_BLUE, "Domain:                    ");
        wprints(4, 9, WHITE|_BLUE, domain_name);
        get_groups();
        get_aliases();
    }
}

void get_groups()
{
    char gbuf[4096], temp[50];
    int j = 0, total = -1, number_groups = 0;

    D3LEnumGroups(org_name, domain_name, "*", gbuf, 4096, &number_groups);
    for (j = 1; j <= number_groups; j++) {
        strcpy(group_name, gbuf + total + 1);
        total = strlen(gbuf);
        gbuf[total] = ' ';
        wprints(5, 1, WHITE|_BLUE, "Checking Group:                         ");
        wprints(5, 17, WHITE|_BLUE, group_name);
        get_memberships();
    }
}

void get_memberships()
{
    int j, returned = 0, total = -1;
    char mbuf[4096], member[60];

    D3LEnumMembers(org_name, domain_name, group_name, mbuf, 4096, &returned);
    for (j = 1; j <= returned; j++) {
        strcpy(member, mbuf + total + 1);
        total = strlen(mbuf);
        mbuf[total] = ' ';
        wprints(6, 1, WHITE|_BLUE, "Checking Members:                       ");
        wprints(6, 19, WHITE|_BLUE, member);
        if (stricmp(username, member) == 0) {
            strcpy(groups[group_number], group_name);
            strcat(groups[group_number], ":");
            strcat(groups[group_number], domain_name);
            strcat(groups[group_number], ":");
            strcat(groups[group_number], org_name);
            if (group_length < strlen(groups[group_number]))
                group_length = strlen(groups[group_number]);
            group_number++;
            break;
        }
    }
}

void get_aliases()
{
    char abuf[4096], alias_name[60], user_name[60];
    int number_aliases, j = 0, total = -1, user_type;

    wprints(6, 1, WHITE|_BLUE, "                                        ");
    D3LEnumAlias(org_name, domain_name, "*", abuf, 4096, &number_aliases);
    for (j = 1; j <= number_aliases; j++) {
        strcpy(alias_name, abuf + total + 1);
        total = strlen(abuf);
        abuf[total] = ' ';
        strcat(alias_name, ":");
        strcat(alias_name, domain_name);
        strcat(alias_name, ":");
        strcat(alias_name, org_name);
        wprints(5, 1, WHITE|_BLUE, "Checking Aliases:                       ");
        wprints(5, 19, WHITE|_BLUE, alias_name);
        strcpy(user_name, "\0");
        D3LGetCHType(alias_name, user_name, &user_type);
        if (stricmp(username, user_name) == 0) {
            strcpy(aliases[alias_number], alias_name);
            if (alias_length < strlen(aliases[alias_number]))
                alias_length = strlen(aliases[alias_number]);
            alias_number++;
        }
    }
}

void display_data()
{
    int j, data_number = 1, data_length = 0;
    char temp[60];
    char userdata[20][60];

    wopen(5, 2, group_number + 5, group_length + 3, 5, WHITE|_CYAN, WHITE|_CYAN);
        wshadow(DGREY|_BLACK);
        for (j = 1; j < group_number; j++) 
            wprints(j, 1, WHITE|_CYAN, groups[j]);

    wopen(23 - alias_number, 25, 23, alias_length + 26, 5, WHITE|_GREEN, WHITE|_GREEN);
        wshadow(DGREY|_BLACK);
        for (j = 1; j < alias_number; j++)
            wprints(j, 1, WHITE|_GREEN, aliases[j]);

    strcpy(userdata[data_number], "Username:        ");
    strcat(userdata[data_number++], username);
    D3LGetEthAddr(temp);
    strcpy(userdata[data_number], "Station Address: ");
    strcat(userdata[data_number++], temp);
    D3LGetMailServer(username, temp);
    strcpy(userdata[data_number], "Mail Server:     ");
    strcat(userdata[data_number++], temp);
    D3LGetShareServer(username, temp);
    strcpy(userdata[data_number], "Share Server:    ");
    strcat(userdata[data_number++], temp);
    D3LGetHomeDir(username, temp);
    strcpy(userdata[data_number], "Home Directory:  ");
    strcat(userdata[data_number++], temp);

    for (j = 1; j < data_number; j++) 
        if (data_length < strlen(userdata[j]))
            data_length = strlen(userdata[j]);

    wopen(5, 74 - data_length, data_number + 5, 75, 5, WHITE|_RED, WHITE|_RED);
        wshadow(DGREY|_BLACK);
        for (j = 1; j < data_number; j++) 
            wprints(j, 1, WHITE|_RED, userdata[j]);
}
