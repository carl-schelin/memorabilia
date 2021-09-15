#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#define ESC 0x1B

void main(int arg, char *argv[])
{
    char data[256], cls[4] = { 27, '[', '2', 'J'};
    char check[2], *cpoint;
    int loop;
    int temp = 0, tlines = 23, linesw = 0, j = 0, nonansi = 0;
    FILE *stream;

    if (arg == 3) tlines = atoi(argv[2]);
    if (arg == 1) {
        printf("Screen 2.0 - A BBS Utility Program by Carl Schelin.\n");
        printf("Copyright (C) 1988 by Carl Schelin\n");
        printf("\nTo Execute: SCREEN <FileName> [#Lines]\n");
        printf("\nWhere <FileName> = Text or ANSI file to Screen");
        printf("\nOptional [#Lines] = Number of lines on BBS Screen. [23]\n");
    }
    if (arg > 1) {
        if ((stream = fopen(argv[1], "r")) == NULL) {
            printf("\aFile not found!\n");
            exit(1);
        }
        else {
            printf("\n\n");
            for (j=1; j<32000; j++ ) {
                strcpy(data, "");
                cpoint = fgets(data, 256, stream);
                if ( j==1 && strcmp(data, cls)) nonansi=1;
                if (feof(stream)) {
                    printf("\n");
                    exit(0);
                }
                if (nonansi) gotoxy(1,23);
                printf("%s", data);
                if (nonansi) printf("\n\n");
                if (++temp == tlines && !linesw) {
                    temp = 0;
                    if (nonansi) gotoxy(1,22);
                    printf("%c[sMore: [Y], (N), or (NS)? ", 27);
                    cpoint = gets(check);
                    printf("%c[u%27s%c[u", 27, " ", 27);
                    cpoint = strupr(strdup(check));
                    if (!strcmp(cpoint,"N")) exit(0);
                    if (!strcmp(cpoint,"NS")) linesw = 1;
                }
            }
        }
        fclose(stream);
    }
}
