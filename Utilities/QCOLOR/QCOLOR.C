#include <stdlib.h>
#include <tcxldef.h>
#include <tcxlvid.h>

void main(int argc)
{
    int ecode = 0;

    argc--;
    TcxlInit();
    if (VidHdw == V_NONE)     ecode = 0;

    if (VidHdw == V_MDA)      ecode = 1;
    if (VidHdw == V_EGAMONO)  ecode = 2;
    if (VidHdw == V_MCGAMONO) ecode = 3;
    if (VidHdw == V_VGAMONO)  ecode = 4;
    if (VidHdw == V_HGC)      ecode = 5;
    if (VidHdw == V_HGCPLUS)  ecode = 6;
    if (VidHdw == V_INCOLOR)  ecode = 7;

    if (VidHdw == V_CGA)      ecode = 8;
    if (VidHdw == V_EGA)      ecode = 9;
    if (VidHdw == V_MCGA)     ecode = 10;
    if (VidHdw == V_VGA)      ecode = 11;

    if ((argc) && ecode == 0) argc = 0;
    if ((argc) && ecode < 8) ecode = 1;
    if ((argc) && ecode > 7) ecode = 2;

    exit(ecode);
}

