#include <stdio.h>
#include <stdlib.h>
#include <d3l.h>

void main()
{
    int result;

    result = D3LCheckForMail();
    switch (result) {
        case 0  : printf("No mail waiting...\n");
                  break;
        case 1  : printf("\aYou have mail!\n");
                  break;
        default : printf("Error: Are you logged in?\n");
                  break;
    }
    exit(result);
}
