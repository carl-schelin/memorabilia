#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <d3l.h>

void get_organizations(void);
void get_domains(void);
void get_users(void);
int verify_and_retrieve(void);

char spaces[9] = "        ";
char org_name[21];
char domain_name[21];

int main(int argc, char *argv[])
{
    printf("ADMIN Name Generator v1.1, Copyright (C) 1990 by Carl Schelin\n");
    if (verify_and_retrieve() != 0) exit(1);
    printf("Getting ADMIN users from Name Service...\n\n");
    if (argc > 1) {
        strcpy(domain_name, argv[1]);
        spaces[0] = '\0';
        get_users();
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

    D3LGetCapabilityClass(&d3ltemp);
    if (d3ltemp != ADMINUSER) {
        printf("\nYou are not an Administrator...\n");
        return 1;
    }

    D3LGetOrgName(org_name);
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
        printf("Organization Selected: %s                    \n", org_name);
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
        printf("    Domain Selected: %s                    \n", domain_name);
        get_users();
    }
}

void get_users()
{
    char ubuf[4096], username[25], temp[50];
    int j = 0, total = -1, capclass = 0, users = 0;

    D3LEnumUsers(org_name, domain_name, "*", ubuf, 4096, &users);
    for (j = 1; j <= users; j++) {
        strcpy(username, ubuf + total + 1);
        total = strlen(ubuf);
        ubuf[total] = ' ';
        strcpy(temp, username);
        strcat(temp, ":");
        strcat(temp, domain_name);
        strcat(temp, ":");
        strcat(temp, org_name);
        D3LGetCapClass(temp, &capclass);
        if (capclass == ADMINUSER)
            printf("%sADMIN - [%s]                     \n", spaces, temp);
    }
}
