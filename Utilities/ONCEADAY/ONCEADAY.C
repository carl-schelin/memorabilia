#include <alloc.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <stdio.h>
#include <process.h>
#include <stdlib.h>
#include <io.h>
#include <dos.h>

void main(int argc, char *argv[])
{
    int first_file;
    struct ftime *fptr;
    struct date *dateblk;

    fptr = malloc(sizeof(fptr));
    dateblk = malloc(sizeof(dateblk));

    if (argc < 2) {
        printf("Usage: OnceADay Verification_File\n");
        exit(2);
    }
    if ((first_file = open(argv[1], O_RDONLY, S_IREAD)) == -1) exit(2);

    if (getftime(first_file, fptr) == -1)
        printf("ERROR: code %d", errno);

    close(first_file);

    getdate(dateblk);

    if (fptr->ft_year  != (dateblk->da_year - 1980) ) exit(0);
    if (fptr->ft_month !=  dateblk->da_mon          ) exit(0);
    if (fptr->ft_day   !=  dateblk->da_day          ) exit(0);
    exit(1);
}
