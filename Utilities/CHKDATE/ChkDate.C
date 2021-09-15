#include <alloc.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <stdio.h>
#include <process.h>
#include <stdlib.h>
#include <io.h>

void main(int argc, char *argv[])
{
    int first_file, last_file;
    struct ftime *fptr;
    struct ftime *lptr;

    fptr = malloc(sizeof(fptr));
    lptr = malloc(sizeof(lptr));

    if (argc < 2) {
        printf("Usage: ChkDate Old_File New_File\n");
        exit(2);
    }
    if ((first_file = open(argv[1], O_RDONLY, S_IREAD)) == -1) exit(3);
    if (( last_file = open(argv[2], O_RDONLY, S_IREAD)) == -1) exit(3);

    if (getftime(first_file, fptr) == -1)
        printf("ERROR: code %d", errno);
    if (getftime( last_file, lptr) == -1)
        printf("ERROR: code %d", errno);

    close(first_file);
    close( last_file);

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      * *  Check the date and time to see if FPTR is older than LPTR    * *
      * *  Check.Bat = 03-20-90 06:35a : TCConfig.TC = 03-15-90 10:27p  * *
      * *  If Check.Bat is older than TCConfig.TC, return errorlevel 1  * *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    if (    fptr->ft_year  != lptr->ft_year ) 
        if (fptr->ft_year  <  lptr->ft_year ) exit(1); else exit(0);
    if (    fptr->ft_month != lptr->ft_month) 
        if (fptr->ft_month <  lptr->ft_month) exit(1); else exit(0);
    if (    fptr->ft_day   != lptr->ft_day  ) 
        if (fptr->ft_day   <  lptr->ft_day  ) exit(1); else exit(0);
    if (    fptr->ft_hour  != lptr->ft_hour ) 
        if (fptr->ft_hour  <  lptr->ft_hour ) exit(1); else exit(0);
    if (    fptr->ft_min   != lptr->ft_min  ) 
        if (fptr->ft_min   <  lptr->ft_min  ) exit(1); else exit(0);
    if (    fptr->ft_tsec  != lptr->ft_tsec ) 
        if (fptr->ft_tsec  <  lptr->ft_tsec ) exit(1); else exit(0);
    exit(0);
}

