/* []---------------------------------------------------------------------[] */
/* |        Socket.c: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |              The Socket.c source code and concepts are                | */
/* |     Copyright (C) 1986-1993 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __SOCKET__

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

#include "socket.h"

#define LOWORD(l)               ((unsigned short)(l))
#define HIWORD(l)               ((unsigned short)((unsigned long)(l) >> 16))

int net_release(int nd)
{
    union REGS inregs, outregs;
    struct SREGS segregs;
    int returncode;

    inregs.h.ah = 0x08;
    inregs.x.bx = nd;

    returncode = int86x(0x61,&inregs,&outregs,&segregs);

    if (outregs.x.cflag) {
        NetError = outregs.h.al;
        returncode = -1;
    }

    return returncode;
}

/*

 Function           Check nd to see if it's a Network Descriptor.

 Syntax             int is_netnd(int nd);

 Prototype in       socket.h

 Remarks            Returns an error if nd is not a network descriptor, and no 
                    error otherwise.

 Return Value       0 if is a network descriptor.
                    -1 if an error occured

                    NetError contains
                      NET_ERR_NOTNETCONN

 See Also           net_getdesc

 Example            #include <stdio.h>
                    #include <socket.h>

                    void main(void)
                    {
                        int i;

                        for (i = 0; i < 32; i++)
                            if (is_netnd(i))
                                printf("%d is not a network descriptor\n", i);
                            else
                                printf("%d is a network descriptor\n", i);
                    }

*/

int is_netnd(int nd)
{
    union REGS inregs, outregs;
    struct SREGS segregs;
    int returncode;

    inregs.h.ah = 0x0d;
    inregs.x.bx = nd;

    returncode = int86x(0x61,&inregs,&outregs,&segregs);

    if (outregs.x.cflag) {
        NetError = outregs.h.al;
        returncode = -1;
    }

    return returncode;
}

int net_connect(int nd, int type, struct addr *addr)
{
    union REGS inregs, outregs;
    struct SREGS segregs;
    int returncode;

    inregs.h.ah = 0x13;
    inregs.x.bx = nd;
    segregs.ds  = HIWORD((char far *)(&addr));
    inregs.x.si = LOWORD((char far *)(&addr));
    inregs.x.dx = type;

    returncode = int86x(0x61,&inregs,&outregs,&segregs);

    if (outregs.x.cflag) {
        NetError = outregs.h.al;
        returncode = -1;
    }

    return returncode;
}


/*

 Function           

 Syntax             

 Prototype in       

 Remarks            

 Return Value       

 See Also           

 Example            

*/


/* releases nd and deallocates resources used by nd */

int net_abort(int nd)
{
    union REGS inregs, outregs;
    struct SREGS segregs;
    int returncode;

    inregs.h.ah = 0x19;
    inregs.x.bx = nd;

    returncode = int86x(0x61,&inregs,&outregs,&segregs);

    if (outregs.x.cflag) {
        NetError = outregs.h.al;
        returncode = -1;
    }

    return returncode;
}

int net_write(int nd, char *buf, unsigned len, unsigned flags)
{
    union REGS inregs, outregs;
    struct SREGS segregs;
    int returncode;

    inregs.h.ah = 0x1a;
    inregs.x.bx = nd;
    segregs.ds  = HIWORD((char far *)buf);
    inregs.x.si = LOWORD((char far *)buf);
    inregs.x.cx = len;
    inregs.x.dx = flags;

    returncode = int86x(0x61,&inregs,&outregs,&segregs);

    if (outregs.x.cflag) {
        NetError = outregs.h.al;
        returncode = -1;
    }

    return returncode;
}

int net_read(int nd, char *buf, unsigned len, struct addr *from, unsigned flags)
{
    union REGS inregs, outregs;
    struct SREGS segregs;
    int returncode;

    inregs.h.ah = 0x1b;
    inregs.x.bx = nd;
    segregs.ds  = HIWORD((char far *)buf);
    inregs.x.si = LOWORD((char far *)buf);
    inregs.x.cx = len;
    segregs.es  = HIWORD((char far *)(from));
    inregs.x.di = LOWORD((char far *)(from));
    inregs.x.dx = flags;

    returncode = int86x(0x61,&inregs,&outregs,&segregs);

    if (outregs.x.cflag) {
        NetError = outregs.h.al;
        returncode = -1;
    }

    return returncode;
}

int net_listen(int nd, int type, struct addr *addr) 
{
    union REGS inregs, outregs;
    struct SREGS segregs;
    int returncode;

    inregs.h.ah = 0x23;
    inregs.x.bx = nd;
    inregs.x.dx = type;
    segregs.ds  = HIWORD((char far *)addr);
    inregs.x.si = LOWORD((char far *)addr);

    returncode = int86x(0x61, &inregs, &outregs, &segregs);

    if (outregs.x.cflag) {
        NetError = outregs.h.al;
        returncode = -1;
    }

    return returncode;
}

unsigned long inet_addr(char *ipaddress)
{
    unsigned long target = 0L;
    char array[4][4];
    char *ptr;
    int j = 0, k = 0;

    ptr = ipaddress;
    while (*ptr != '\0') {
        if (*ptr == '.') {
            array[j++][k] = '\0';
            k = 0;
        }
        else {
            array[j][k++] = *ptr;
        }
        (*ptr)++;
    }

    target  = (unsigned long)(atoi(array[0]) * 1);
    target += (unsigned long)(atoi(array[1]) * 256);
    target += (unsigned long)(atoi(array[2]) * 65536L);
    target += (unsigned long)(atoi(array[3]) * 16777216L);

    return target;
}
#ifdef CARL
int vec_search(void)
{
    union REGS inregs, outregs;
    struct SREGS segregs;
    int returncode;
    int vector = 0, target = 0;

    inregs.h.ah = 0x23;
    inregs.x.bx = nd;
    inregs.x.dx = type;
    segregs.ds  = HIWORD((char far *)addr);
    inregs.x.si = LOWORD((char far *)addr);

    for (j = 0x60; j < 0x80; j++) {
        int86x(j, &inregs, &outregs, &segregs);
        if (

    if (outregs.x.cflag) {
        NetError = outregs.h.al;
        returncode = -1;
    }

    return returncode;
}
#endif
