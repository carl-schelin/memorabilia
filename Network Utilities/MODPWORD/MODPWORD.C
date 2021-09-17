#include <stdio.h>
#include <string.h>
#include <d3l.h>
#include <cxlwin.h>

int main()
{
    char pword1[13] = {"1"};
    char pword2[13] = {"2"};
    int err = W_NOERROR;

    printf("Modify Password v1.1, Copyright 1990 by Carl Schelin, All Rights Reserved.\n");
    if (D3LIsLoggedIn() == 1) {
        wopen(9, 22, 15, 55, 1, WHITE|_BLUE, WHITE|_BLUE);
        wshadow(DGREY|_BLACK);
        while ((stricmp(pword1, pword2) != 0) && (err != W_ESCPRESS)) {
            wgotoxy(1, 1);
            err = winputsf(pword1, "'New Password '!P! ************");
            if (err != W_ESCPRESS) {
                wgotoxy(2, 1);
                err = winputsf(pword2, "'Verification '!P! ************");
            }
        }
        if (err != W_ESCPRESS) {
            err = D3LModPassword(pword1, 1);
            if (err == 0) {
                textattr(GREEN + ( BLUE << 4));
                wgotoxy(3, 1);
                wprintf("Password Changed...");
            }
            else {
                textattr(RED + ( BLUE << 4));
                wgotoxy(3, 1);
                wprintf("ERROR: Password Not Changed...");
            }
        }
        else {
            textattr(YELLOW + ( BLUE << 4));
            wgotoxy(3, 1);
            wprintf("Aborted Password Change...");
        }
        textattr(WHITE + ( BLUE << 4));
        wgotoxy(4, 1);
        wprintf("[Any Key to Continue...]");
        waitkey();
        wclose();
    }
    else {
        printf("\nPlease login first...\n");
        return 1;
    }
    return 0;
}
