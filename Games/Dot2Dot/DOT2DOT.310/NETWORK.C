/* []---------------------------------------------------------------------[] */
/* |       Network.c: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |             The Network.c source code and concepts are                | */
/* |     Copyright (C) 1986-1996 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __NETWORK__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys\types.h>
#include <pctcp\types.h>
#include <pctcp\netinfo.h>
#include <pctcp\pctcp.h>
#include <pctcp\syscalls.h>
#include <pctcp\error.h>

#include "dot2dot.h"

extern int vec_search(void);
extern char *inet_ntoa(in_name);
extern in_name inet_addr(char *);

char *Messages[14] = {
    "100 Welcome to Dot2Dot v3.1 - Written by Carl Schelin",
    "110 Ready to receive",
    "111 Sorry, game full",
    "112 Sorry, not this time",
    "113 Sorry, only one player per site",
    "114 Ok, see you later",
    "115 Hey! Where'd you go?",
    "120 Here's the next turn",
    "121 Wait, someone else's turn",
    "122 Go ahead, send turn",
    "130 What's your name?",
    "200 ",                   /* Horizontal Line (passes matrix post number) */
    "201 ",                     /* Vertical Line (passes matrix post number) */
    "202 "               /* Hold onto your shorts - here comes the turn list */
};

void Gather_Stats(void)
{
    struct netinfo ni;

    net_info(-1, &ni);
    IPAddr = inet_ntoa(ni.ip_address);
    printf("%lu %s\n", ni.ip_address, IPAddr);
}

/*--- function InitCom ----------------------------------------------
 *
 *  Find the vector being used for the PC/TCP driver.
 *
 *  Returns: 0  -  If it was not found
 *           1  -  If the vector was found
 *
 */

int InitCom(void)
{
    int errormsg;

    errormsg = vec_search();
    if (_pctcp_int == 0) {
        return 0;
    }
    return 1 ;
}

