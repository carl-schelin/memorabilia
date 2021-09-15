#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <d3l.h>

int verify_and_retrieve(void);
void get_aliases(void);
void get_domains(void);
void get_organizations(void);

int badonly = 0;
char org_name[21];
char domain_name[21];

int main(int argc, char *argv[])
{
    printf("ALIAS Name Generator v1.1, Copyright (C) 1990, by Carl Schelin\n");
    if (verify_and_retrieve() != 0) exit(1);
    printf("Getting Aliases from the Name Service...\n");
    if (argc > 1) {
        if (strcmp(argv[1], "&") == 0) {
            badonly = 1;
            if (argc > 2)
                strcpy(argv[1], argv[2]);
            else
                argc = 1;
        }
    }

    if (argc > 1) {
        strcpy(domain_name, argv[1]);
        get_aliases();
    }
    else
        get_organizations();
    return 0;
}

int verify_and_retrieve()
{
    int d3ltemp = 0;

    D3LGetLoginFlag(&d3ltemp);
    if (d3ltemp == 0) {
        printf("\nPlease login first...\n");
        return 1;
    }

    D3LGetOrgName(org_name);
    D3LGetDomainName(domain_name);
    return 0;
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
        get_aliases();
    }
}

void get_aliases()
{
    int j, error;
    int returned = 0, usertype = 0, total = -1;
    char mbuf[2048], alias_name[21], username[50], temp[60];

    D3LEnumAlias(org_name, domain_name, "*", mbuf, 2048, &returned);
    for (j = 1; j <= returned; j++) {
        strcpy(alias_name, mbuf + total + 1);
        total = strlen(mbuf);
        mbuf[total] = ' ';
        strcpy(temp, alias_name);
        strcat(temp, ":");
        strcat(temp, domain_name);
        strcat(temp, ":");
        strcat(temp, org_name);
        error = D3LGetCHType(temp, username, &usertype);
        if (error != 0) strcpy(username, "*** ERROR: Alias Not Found!");
        if (badonly == 0)
            printf("%33s - %-34s\n", temp, username);
        else 
            if (error != 0)
                printf("%33s - %-34s\n", temp, username);
    }
}
