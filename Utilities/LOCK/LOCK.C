#include <cxlkey.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc > 1) {
        if (strcmpi(argv[1], "CAPON") == 0) capson();
        if (strcmpi(argv[1], "CAPOFF") == 0) capsoff();
        if (strcmpi(argv[1], "NUMON") == 0) numon();
        if (strcmpi(argv[1], "NUMOFF") == 0) numoff();
        if (strcmpi(argv[1], "ALLON") == 0) {
            capson();
            numon();
        }
        if (strcmpi(argv[1], "ALLOFF") == 0) {
            capsoff();
            numoff();
        }
    }
    return 0;
}