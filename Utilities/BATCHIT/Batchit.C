#include <dir.h>
#include <dos.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FA_OS2DIREC 0x30

int main(int argc, char *argv[])
{
    struct ffblk ffblk;
    FILE *output;
    int done, j, k, count, result;
    unsigned int total;
    char mask[256], build[256], commandline[256], temp[256];
    char names[15][12];
    char *tempenvar, *comspecenvar;

    printf("BATCHIT v1.21 - Copyright 1994 by Carl Schelin - All Rights Reserved\n");
    if (strcmp(argv[1], "?") == 0 || strcmp(argv[1], "/?") == 0 || strcmp(argv[1], "-?") == 0) {
        printf("\nBATCHIT Syntax:\n");
        printf("   batchit [<batch filename> | NULL] [<command>...]\n\n");
        printf("   where:\n");
        printf("      <batch filename> - valid filename to contain the instructions\n");
        printf("   If the first parameter is NULL then [<commands>...] will be executed rather\n");
        printf("   than saved in a batch file\n\n");
        printf("      <command>...     - commands to be executed in new batch file\n");
        printf("   <command>... can have one of the following five special codes:\n"); 
        printf("      $G - This code replaces $G with \">\" in the command line\n");
        printf("      $L - This code replaces $L with \"<\" in the command line\n");
        printf("      $B - This code replaces $B with \"|\" in the command line\n");
        printf("      $_ - This code replaces $_ with <Enter> in the command line\n");
        printf("      $D - This code replaces $D with \"directory name\" in the command line\n");
        printf("             (NOTE: Limit to fifteen occurances of $D)\n\n");
        printf("   Example:\n");
        printf("      batchit winedit.bat copy j:\\$d\\win31\\win.ini $l $d.ini $g$g nul\n\n");
        printf("   which results in:\n");
        printf("      WINEDIT.BAT\n");
        printf("      copy j:\\ADMIN\\win31\\win.ini < ADMIN.ini >> nul\n");
        return 1;
    }
    if (argc > 2) {
        if (stricmp(argv[1], "NULL") != 0)
            if ((output = fopen(argv[1], "w+")) == NULL) {
                printf("ERROR: Unable to create \"%s\"\n", argv[2]);
                return 1;
            }

        mask[0] = '\0';   /* initialize the mask */
        count = 0;        /* how many times to print the directory name? */
        total = 0;        /* were there any hits? if not, print error */
        for (j = 0; j < 15; j++)
            names[j][0] = '\0';  /* initialize names variable */

        for (j = 2; j < argc - 1; j++) {
            strcat(mask, argv[j]);
            strcat(mask, " ");
        }
        strcat(mask, argv[argc - 1]);

        for (j = 0; j < strlen(mask); j++) {
            if (mask[j] == '$') {
                if (mask[j + 1] == 'd' || mask[j + 1] == 'D') {
                    mask[j] = '%';
                    mask[j + 1] = 's';
                    count++;
                }
                if (mask[j + 1] == 'l' || mask[j + 1] == 'L') {
                    for (k = j; k < strlen(mask) - 1; k++)
                        mask[k] = mask[k + 1];
                    mask[j] = '<';
                    mask[strlen(mask) - 1] = '\0';
                }
                if (mask[j + 1] == 'g' || mask[j + 1] == 'G') {
                    for (k = j; k < strlen(mask) - 1; k++)
                        mask[k] = mask[k + 1];
                    mask[j] = '>';
                    mask[strlen(mask) - 1] = '\0';
                }
                if (mask[j + 1] == 'b' || mask[j + 1] == 'B') {
                    for (k = j; k < strlen(mask) - 1; k++)
                        mask[k] = mask[k + 1];
                    mask[j] = '|';
                    mask[strlen(mask) - 1] = '\0';
                }
                if (mask[j + 1] == '_') {
                    for (k = j; k < strlen(mask) - 1; k++)
                        mask[k] = mask[k + 1];
                    mask[j] = '\n';
                    mask[strlen(mask) - 1] = '\0';
                }
            }
        }

        if (count > 15) {
            printf("WARNING: BatchIt is only able to process 15 occurances of $D\n");
            count = 15;
        }

        tempenvar = getenv("TEMP");
        comspecenvar = getenv("COMSPEC");
        done = findfirst("*.*", &ffblk, FA_DIREC);
        while (!done) {
            if (ffblk.ff_name[0] != '.') {
                if (ffblk.ff_attrib == FA_OS2DIREC || ffblk.ff_attrib == FA_DIREC) {
                    total++;
                    for (j = 0; j < count; j++)
                        strcpy(names[j], ffblk.ff_name);
                    sprintf(build, mask, names[0], names[1], names[2], names[3], names[4]);

                    if (stricmp(argv[1], "NULL") == 0) {
                        if (tempenvar != NULL)
                            sprintf(temp, "%s\\~batchit.bat", tempenvar);
                        else
                            strcpy(temp, "~batchit.bat");
                        if ((output = fopen(temp, "w+")) == NULL) {
                            printf("ERROR: Unable to create %s\n", temp);
                            return 1;
                        }
                        fprintf(output, "%s", build);
                        fclose(output);

                        if (comspecenvar != NULL) {
                            sprintf(commandline, "%s /c %s\n", comspecenvar, temp);
                            system(commandline);
                        }
                        result = unlink(temp);
                        if (result == -1) {
                            printf("ERROR: Unable to delete %s\n", temp);
                            return 1;
                        }
                    }
                    else
                        fprintf(output, "%s\n", build);
                }
            }
            done = findnext(&ffblk);
        }

        if (stricmp(argv[1], "NULL") == 0)
            fclose(output);
    }
    else {
        printf("ERROR: No parameters passed to BATCHIT!\n");
        return 1;
    }

    if (total == 0)
        printf("ERROR: No directories found!\n");
    return 0;
}

