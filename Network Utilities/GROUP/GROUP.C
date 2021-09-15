#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <d3l.h>

void get_organizations(void);
void get_domains(void);
void get_groups(void);
void verify_membership(void);
int verify_and_retrieve(void);

char org_name[21];
char domain_name[21];
char group_name[21];

int main(int argc, char *argv[])
{
    printf("GROUP Name Verifier v1.1, Copyright (C) 1990, by Carl Schelin\n");
    if (verify_and_retrieve() != 0) exit(1);
    printf("Getting Members from the Name Service...\n");
    if (argc > 1) {
        strcpy(domain_name, argv[1]);
        get_groups();
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
        get_groups();
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
        verify_membership();
    }
}

void verify_membership()
{
    int j;
    int returned = 0, total = -1, usertype = 0;
    char mbuf[4096], member[60], username[50], temp[60];

    D3LEnumMembers(org_name, domain_name, group_name, mbuf, 4096, &returned);
    for (j = 1; j <= returned; j++) {
        strcpy(member, mbuf + total + 1);
        total = strlen(mbuf);
        mbuf[total] = ' ';
        if (D3LGetCHType(member, username, &usertype) != 0)
            printf("ERROR: \"%s\" in \"%s:%s:%s\" is invalid.\n", member, group_name, domain_name, org_name);
    }
}
