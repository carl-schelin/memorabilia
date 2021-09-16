/*
 *    Socket.C
 *
 *    Functions:
 *
 *         InitCom      - The "front door" to these routines. Inits the socket
 *                        to the NNTP server (running socket 119) and returns
 *                        an error if it can't be reached.
 *
 *         SetupSockets - Reads the IP Address from the configuration file and
 *                        tries to open the 119 socket with the NNTP server. If
 *                        there is an error, it is returned to InitCom after
 *                        printing an error message.
 *
 *         GetComLine   - Asks the NNTP server for a line of data. 
 *
 *         PutComLine   - Puts a line of data on the NNTP server
 *
 *         CloseCom     - Closes the connection between you and the NNTP 
 *                        server.
 */

#define __SOCKET__ 
#define _NEAR
#define _CDECL
#undef LINT_ARGS

#include <pctcp/types.h>
#include <pctcp/pctcp.h>
#include <pctcp/error.h>
#include <pctcp/options.h>
#include <pctcp/syscalls.h>
#include <memory.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include "Main.H"

#define DEBUGSIZE 200

long inet_addr(char *cp);
int  CommBuffIdx=COMBUFSIZE+1;
int  CharsInCommBuff=0;

struct addr outbound;
struct addr getfrom;
int NNTPSock;

/*--- function InitCom ----------------------------------------------
 *
 *  Open Socket to NNTP Server and print a dummy message.
 *
 *  Returns: 0  -  If there is an error
 *           1  -  If the socket was initialized ok.
 *
 */

int InitCom(void)
{
    int errormsg;

    errormsg = vec_search();
    if (_pctcp_int == 0) {
        MessageWindow(" Driver not loaded. Initialization error!", HLP_INITERR);
        return 0;
    }
    return 1 ;
}

/*-- function SetupSockets ------------------------------------------
 *
 *   Sets up the socket to the NNTP server.
 *
 *   Returns: 0  -  If there is an error.
 *            1  -  If the socket has been opened ok.
 */

int SetupSockets(char *HostIP, int Socket)
{
    long destaddr;

    destaddr = inet_addr(HostIP);

    /* Set up name structure */

    memcpy(&outbound.fhost, &destaddr, sizeof(outbound.fhost));  /* Who you gonna call? */
    outbound.lsocket = 0;                /* Local Socket. 0 means assign random number */
    outbound.fsocket = Socket;           /* NNTP Socket to contact         */
    outbound.protocol = 0;               /* Needed only if RAW_xxx is used */

    NNTPSock = net_connect(-1, STREAM, &outbound);  /* Make the call... Anyone home? */
   
    if (NNTPSock == -1) {
        sprintf(Message, " net_connect returned %d; neterrno=%d", NNTPSock, neterrno);
        MessageWindow(Message, HLP_NOCONNECT);
        switch (neterrno) {
            case NET_ERR_BADARG     :      /* 18 */
                strcpy(Message, " BADARG: The type argument is bad");
                break;
            case NET_ERR_INUSE      :      /*  1 */
                strcpy(Message, " INUSE: Address is in use");
                break;
            case NET_ERR_NOHOST     :      /*  7 */
                strcpy(Message, " NOHOST: A necessary field is 0");
                break;
            case NET_ERR_NODESC     :      /* 23 */
                strcpy(Message, " NODESC: Could not allocate a descriptor");
                break;
            case NET_ERR_NOMEM      :      /*  3 */
                strcpy(Message, " NOMEM: PC/TCP is out of resources");
                break;
            case NET_ERR_NOTNETCONN :      /*  4 */
                strcpy(Message, " NOTNETCONN: But I said that you said that I said ...");
                break;
            case NET_ERR_RESET      :      /* 20 */
                strcpy(Message, " RESET: They said NO!");
                break;
            case NET_ERR_TIMEOUT    :      /* 13 */
                strcpy(Message, " TIMEOUT: Hey! Wake up!");
                break;
            default                 : 
                sprintf(Message, " Abnormal Error %d. Got me!", neterrno);
                break;
        }
        MessageWindow(Message, HLP_REALERR);
        return FALSE;
    }
    return TRUE;
}

/*-- function GetComLine --------------------------------------------
 *
 *  Gets characters from the NNTP server.
 *
 *  Returns: -1  -  In case of error. This is because GetComLine could return
 *                  anything since we are passing back the pointer.
 *           data - The line read in from the NNTP server.
 */

char GetComLine()
{
    int bytesread;

    Message[0] = '\0';
    if (CommBuffIdx < CharsInCommBuff) {
    }
    else {
        bytesread = net_read(NNTPSock, CommBuff, COMBUFSIZE, &getfrom, NET_FLG_NONBLOCKING);

        if (!bytesread || (bytesread == (-1) && neterrno == NET_ERR_WOULD_BLOCK)) {
            return(WAITFORIT);
        } 
        else
            if (bytesread > 0) {
                CharsInCommBuff = bytesread;
                CommBuffIdx = 0;
            }
            else {
                sprintf(Message, " NNTPSock=%d  bytesread=%d  neterrno=%d problem in GetComLine", NNTPSock, bytesread, neterrno);
                MessageWindow(Message, HLP_NOCONNECT);
                ComState = ST_NONE;
                ErrState = ER_CANT;
                return(UNKERROR);
            }
    }
    return(CommBuff[CommBuffIdx++]);
}


/*-- function PutComLine --------------------------------------------
 *
 *  Send a line back to the NNTP server.
 *
 *  Input: line  -  points to the data to be passed to the NNTP server.
 *
 */

void PutComLine(char *line)
{
    net_write(NNTPSock, line, strlen(line), 0);
    net_write(NNTPSock, "\n", 1, 0);
}

/*-- function CloseCom ----------------------------------------------
 *
 *  Closes the connection to the NNTP server.
 *
 */

void CloseCom()
{
    net_release(NNTPSock);
}

