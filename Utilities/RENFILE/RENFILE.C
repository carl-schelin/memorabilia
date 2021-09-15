#include <stdio.h>
#include <dos.h>
#include <dir.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include <errno.h>

#define _A_ALLFILES ( \
    _A_NORMAL |       \
    _A_RDONLY |       \
    _A_HIDDEN |       \
    _A_SYSTEM |       \
    _A_VOLID |        \
    _A_SUBDIR |       \
    _A_ARCH           \
)

void renamefile(char *fileone, char *filetwo);

char masterpath[MAXPATH];
int dosubdir = 0;
int dorename = 0;
int quit = 0;

/*
 *
 * RenFile takes a filename and renames it to the passed new filename.
 *
 * The default settings are to search only the directory passed with the 
 * first filename and to ask before changing the file.
 *
 * Two switches allow subdirectory searching and turning off verification.
 *
 */

void main(int argc, char *argv[])
{
    int j, startlook = 0;

    printf("RENFILE 1.0 - Copyright 1995 by Carl Schelin - All Rights Reserved\n\n");
    if (argc < 3) {
        printf("Syntax Error:\n");
        printf("    RenFile [path]<oldfile> <newfile> [/s] [/y]\n\n");
        printf("    Where:\n");
        printf("        [path]    Is an optional path to start searching.\n");
        printf("        <oldfile> Is the old filename to search for.\n");
        printf("        <newfile> Is the new filename.\n");
        printf("        [/s]      Search subdirectories.\n");
        printf("        [/y]      Rename file without asking.\n");
    }
    else {
        for (j = 1; j <= argc; j++) {
            if (stricmp(argv[j], "/s") == 0)
                dosubdir = 1;
            if (stricmp(argv[j], "/y") == 0)
                dorename = 1;
        }
        strcpy(masterpath, argv[1]);
        for (j = strlen(masterpath); j > 0; j--) {
            if (masterpath[j] == '\\') {
                masterpath[j] = '\0';
                startlook = 1;
                break;
            }
            if (masterpath[j] == ':') {
                masterpath[j + 1] = '.';
                masterpath[j + 2] = '\0';
                startlook = -1;
                break;
            }
        }
        if (j == 0)
            masterpath[0] = NULL;
        renamefile(argv[1] + (strlen(masterpath) + startlook), argv[2]);
    }
}

void renamefile(char *fileone, char *filetwo)
{
    struct find_t ffblk;
    int done;
    int error;
    char path[MAXPATH];
    char lookfor[MAXPATH];
    char renameto[MAXPATH];
    char doit[MAXPATH];

    if (!quit) {
        lookfor[0] = NULL;
        if (masterpath[0] != NULL) {
            strcat(lookfor, masterpath);
            strcat(lookfor, "\\");
        }
        strcat(lookfor, "*.*");
        done = _dos_findfirst(lookfor, _A_ALLFILES, &ffblk);
        while (!done) {
            if (ffblk.name[0] != '.') {
                printf("%s:%s%s%s", fileone,
                    strlen(masterpath)>0 ? masterpath : "",
                    strlen(masterpath)>0 ? "\\" : "", ffblk.name);
                if (stricmp(fileone, ffblk.name) == 0) {
                    if (!dorename) {
                        printf(" [ynqa] ");
                        scanf("%s", &doit);
                        if (doit[0] == 'a' || doit[0] == 'A') {
                            doit[0] = 'y';
                            dorename = 1;
                        }
                    }
                    else {
                        doit[0] = 'y';
                        printf(" -> %s", filetwo);
                    }
                    if (doit[0] == 'q' || doit[0] == 'Q') {
                        quit = 1;
                        break;
                    }
                    if (doit[0] == 'y' || doit[0] == 'Y') {
                        strcpy(lookfor, masterpath);
                        strcpy(renameto, masterpath);
                        if (strlen(masterpath) > 0) {
                            strcat(lookfor, "\\");
                            strcat(lookfor, fileone);
                            strcat(renameto, "\\");
                            strcat(renameto, filetwo);
                        }
                        else {
                            strcpy(lookfor, fileone);
                            strcpy(renameto, filetwo);
                        }
                        error = rename(lookfor, renameto);
                        if (error != 0) {
                            if (errno == EACCES)
                                printf("%s already exists or %s is an invalid path\n", filetwo, masterpath);
                            if (errno == ENOENT)
                                printf("unable to find %s\n", lookfor);
                            if (errno == EXDEV)
                                printf("can't move to a different device\n");
                        }
                    }
                    printf("\n");
                }
                else 
                    printf("\n");
                if ((ffblk.attrib & _A_SUBDIR) && (dosubdir)) { /* found a subdir */
                    strcpy(path, masterpath);           /* backup masterpath */
                    if (strlen(masterpath) > 0) {
                        strcat(masterpath, "\\");       /* add backslashes   */
                        strcat(masterpath, ffblk.name); /* tack on new path  */
                    }
                    else
                        strcpy(masterpath, ffblk.name); /* add new path      */
                    renamefile(fileone, filetwo);       /* cyclic search     */
                    strcpy(masterpath, path);           /* restore backup    */
                    if (quit)
                        break;
                }
            }
            done = _dos_findnext(&ffblk);
        }
    }
}

