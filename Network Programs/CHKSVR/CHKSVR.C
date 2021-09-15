#include <stdio.h>
#include <string.h>
#include <d3l.h>

int main(int argc, char *argv[])
{
    char sbuf[4096], org_name[21], domain_name[21], server_name[60];
    int j = 0, total = -1, number_servers, logged_in = 0, error;

    D3LGetLoginFlag(&logged_in);
    if (logged_in == 0) {
        printf("Please Login First...\n");
        exit(1);
    }
    D3LGetOrgName(org_name);
    D3LGetDomainName(domain_name);
    if (argc > 1)
        strcpy(domain_name, argv[1]);
    printf("Checking: %s:%s\n\n", domain_name, org_name);
    D3LEnumServers(org_name, domain_name, "*", sbuf, 4096, &number_servers);
    for (j = 1; j <= number_servers; j++) {
        strcpy(server_name, sbuf + total + 1);
        total = strlen(sbuf);
        sbuf[total] = ' ';
        error = D3LCheckServer(server_name);
        if (error != 0)
            printf("ERROR: %d, %s is down!\n", error, server_name);
        else
            printf("%s is responding.\n", server_name);
    }
    return 0;
}
