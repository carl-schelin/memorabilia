#include <io.h>
#include <process.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
    if (argc == 2)
        if ((access(argv[1], 0)) == 0) 
            exit(0);
        else 
            exit(1);
    exit(2);
}
