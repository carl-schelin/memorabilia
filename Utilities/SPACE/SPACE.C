/*    Space v1.0
 *
 *    Copyright 1991 by Carl Schelin, All Rights Reserved.
 *    This code may be used as a learning tool, but you can't recompile
 *    it and say it's yours.
 *
 */

#include <alloc.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "v1.0"

void main(int argc, char *argv[])
{
    struct dfree *free;
    long avail, checked = 0L;
    int j, drive = -1;

    printf("SPACE "VERSION" - Copyright 1991 by Carl Schelin - All Rights Reserved\n\n");

    if (argc != 2) {
        if (argv[1][1] == ':')
            drive = argv[1][0] - 64;
        if (drive > 26)
            drive -= 32;
        checked = atol(argv[2]);
        if (checked == 0)
            drive = -1;
    }
    if (drive == -1) {
        printf("Syntax Error: \n\n");
        printf("    Space [d:] [amount]\n\n");
        printf("    Where:\n");
        printf("        [d:] is a valid drive\n");
        printf("        [amount] is the amount of required drive space needed\n");
        exit(3);
    }

    free = malloc(sizeof(free));
    getdfree(drive, free);
    if (free->df_sclus != 0xFFFF) {
        avail = (long) free->df_bsec * (long) free->df_sclus * (long) free->df_avail;
        if (avail >= checked)
            exit(0);
        else 
            exit(1);
    }
    exit(2);
}

