
#define ASYNC                    0x80       /* process NCB asynchronously   */
#define NCBNAMSZ                 0x10       /* max len of ncb name          */


/* ncb_post under OS/2 is a system semiphore handle. Under MS-DOS, this is
   the memory address of the routine to call when the async NCB completes   */
struct ncb {
    unsigned char  ncb_command;             /* command code & ASYNC if used */
    unsigned char  ncb_retcode;             /* ncb return code              */
    unsigned char  ncb_lcn;                 /* local session number         */
    unsigned char  ncb_num;                 /* number of the network name   */
    char far *     ncb_buffer;              /* points to message buffer     */
    unsigned short ncb_length;              /* size of message buffer       */
    char           ncb_callname[NCBNAMSZ];  /* padded remote name           */
    char           ncb_name[NCBNAMSZ];      /* padded local name            */
    unsigned char  ncb_rto;                 /* receive time-out count       */
    unsigned char  ncb_sto;                 /* send time-out count          */
    unsigned long  ncb_post;                /* async notification handle    */
    unsigned char  ncb_lana_num;            /* LAN adapter number           */
    unsigned char  ncb_cmd_cplt;            /* command complete code        */
    unsigned char  ncb_reserve[14];         /* reserved. Do not use         */
};

/*  ncb_command codes  */
#define NCBCALL                  0x10       /* Call                         */
#define NCBLISTEN                0x11       /* Listen                       */
#define NCBHANGUP                0x12       /* Hang up                      */
#define NCBSEND                  0x14       /* Send                         */
#define NCBRECV                  0x15       /* Receive                      */
#define NCBRECVANY               0x16       /* Receive Any                  */
#define NCBCHAINSEND             0x17       /* Chain Send                   */
#define NCBDGSEND                0x20       /* Send Datagram                */
#define NCBDGRECV                0x21       /* Receive Datagram             */
#define NCBDGSENDBC              0x22       /* Send Broadcast Datagram      */
#define NCBDGRECVBC              0x23       /* Receive Broadcast Datagram   */
#define NCBADDNAME               0x30       /* Add a Name                   */
#define NCBDELNAME               0x31       /* Delete a Name                */
#define NCBRESET                 0x32       /* Reset                        */
#define NCBASTAT                 0x33       /* Give Adapter Status          */
#define NCBSSTAT                 0x34       /* Give Session Status          */
#define NCBCANCEL                0x35       /* Cancel                       */
#define NCBADDGRNAME             0x36       /* Add Groupname                */
#define NCBUNLINK                0x70       /* Unlink                       */
#define NCBSENDNA                0x71       /* Send no Acknowledgment       */
#define NCBCHAINSENDNA           0x72       /* Chain Send no Acknowledgment */

/*  ncb_retcode return codes  */
#define NRC_GOODRET       0x00  /* Good Return                                      */
#define NRC_BUFLEN        0x01  /* Illegal Buffer Length Given                      */
#define NRC_BFULL         0x02  /* Buffers are full, no receive issued              */
#define NRC_ILLCMD        0x03  /* Illegal command was given                        */
#define NRC_CMDTMO        0x05  /* Command was timed out                            */
#define NRC_INCOMP        0x06  /* Message was incomplete; issue another command    */
#define NRC_BADDR         0x07  /* Illegal buffer address was given                 */
#define NRC_SNUMOUT       0x08  /* Session number is out of range                   */
#define NRC_NORES         0x09  /* No resource is available                         */
#define NRC_SCLOSED       0x0A  /* Session is closed                                */
#define NRC_CMDCAN        0x0B  /* Command is canceled                              */
#define NRC_DMAFAIL       0x0C  /* PC DMA failed                                    */
#define NRC_DUPNAME       0x0D  /* Duplicate name exists                            */
#define NRC_NAMTFUL       0x0E  /* Name table is full                               */
#define NRC_ACTSES        0x0F  /* No deletions; name has active sessions           */
#define NRC_INVALID       0x10  /* Name was not found or no valid name exists       */
#define NRC_LOCTFUL       0x11  /* Local session table is full                      */
#define NRC_REMTFUL       0x12  /* Remote session table is full                     */
#define NRC_ILLNN         0x13  /* Illegal name number was given                    */
#define NRC_NOCALL        0x14  /* No callname was given                            */
#define NRC_NOWILD        0x15  /* Cannot put * in NCB_NAME                         */
#define NRC_INUSE         0x16  /* Name already in use on remote adapter            */
#define NRC_NAMERR        0x17  /* Called name cannot equal name, number            */
#define NRC_SABORT        0x18  /* Session ended abnormally                         */
#define NRC_NAMCONF       0x19  /* Name conflict was detected                       */
#define NRC_IFBUSY        0x21  /* Interface is busy                                */
#define NRC_TOOMANY       0x22  /* Too many commands are outstanding; try later     */
#define NRC_BRIDGE        0x23  /* The NCB_BRIDGE field is not 00 or 01             */
#define NRC_CANOCCR       0x24  /* Command was completed while cancel was occurring */
#define NRC_RESNAME       0x25  /* Reserved name was specified                      */
#define NRC_CANCEL        0x26  /* Command not valid to cancel                      */
#define NRC_MULT          0x33  /* Multiple requests were made for the same session */
#define NRC_MAXAPPS       0x36  /* Maximum number of applications was exceeded      */
#define NRC_NORESOURCES   0x38  /* Requested resources are not available            */
#define NRC_SYSTEM        0x40  /* System error occurred                            */
#define NRC_ROM           0x41  /* ROM checksum failure occurred                    */
#define NRC_RAM           0x42  /* RAM test failure occurred                        */
#define NRC_DLF           0x43  /* Digital loopback failure occurred                */
#define NRC_ALF           0x44  /* Analog loopback failure occurred                 */
#define NRC_IFAIL         0x45  /* Interface failure occurred                       */
#define NRC_ADPTMALFN     0x50  /* Network adapter malfunctioned                    */
#define NRC_PENDING       0xFF  /* Asynchronous command is not yet finished         */


struct netbios_info_0 {
    char nb0_net_name[NETBIOS_NAME_LEN + 1];      /* name of the net driver */
};

struct netbios_info_1 {
    char            nb1_net_name[NETBIOS_NAME_LEN + 1];     /* network name */
    char            nb1_driver_name[DEVLEN + 1];  /* net device driver name */
    unsigned char   nb1_lana_num;            /* network adapter card number */
    char            nb1_pad_1;  /* aligns the next data structure on a word */
    unsigned short  nb1_driver_type;         /* device driver protocol type */
    unsigned short  nb1_net_status;          /* status of the device driver */
    unsigned long   nb1_net_bandwidth;   /* bits per second the lan handles */
    unsigned short  nb1_max_sess;                 /* max number of sessions */
    unsigned short  nb1_max_ncbs;         /* max number of NCBs outstanding */
    unsigned short  nb1_max_names;           /* max number of network names */
};

/* nb1_driver_type */
#define NB_TYPE_NCB           1    /* Network control block protocol */
#define NB_TYPE_MCB           2    /* Message control block protocol */

/* nb1_net_status */
#define NB_LAN_FLAGS_MASK    0x3FFF  /* bit mask isolates these LAN flags: */
#define NB_LAN_MANAGED       0x0001  /* The network is managed by the redirector */
#define NB_LAN_LOOPBACK      0x0002  /* The network is a loopback driver */
#define NB_LAN_SENDNOACK     0x0004  /* SendNoAck NCBs are supported */
#define NB_LAN_LMEXT         0x0008  /* Extended NCBs are supported */
#define NB_LAN_INTNCB        0x0010  /* NCB submission at interrupt time is supported */

#define NB_OPEN_MODE_MASK    0xC000  /* bit mask isolates the open mode: */
#define NB_OPEN_REGULAR      0x4000  /* NetBIOS opened in regular mode */
#define NB_OPEN_PRIVILEGED   0x8000  /* NetBIOS opened in privileged mode */
#define NB_OPEN_EXCLUSIVE    0xC000  /* NetBIOS opened in exclusive mode */


NetBiosClose (unsigned short  hDevName,             /* device driver handle */
              unsigned short  usReserved            /* reserved, must be 0  */
);

NetBiosEnum (const char far *      pszServer,     /* server to execute enum */
             short                 sLevel,        /* level of detail (0 or 1) */
             char far *            pbBuffer,      /* where store returned data */
             unsigned short        cbBuffer,      /* size of buffer */
             unsigned short far *  pcEntriesRead, /* number of entries */
             unsigned short far *  pcTotalAvail   /* total entries available */
);

NetBiosGetInfo (const char far *      pszServer,
                const char far *      pszNetBiosName,  /* asciiz network name */
                short                 sLevel,
                char far *            pbBuffer,
                unsigned short        cbBuffer,
                unsigned short far *  pcbTotalAvail
);

NetBiosOpen (char far *            pszDevName,  /* net name */
             char far *            pszReserved, /* reserved, must be 0 */
             unsigned short        usOpenOpt,   /* access mode */
             unsigned short far *  phDevName    /* device driver handle */
);

NetBiosSubmit (unsigned short    hDevName, /* device driver handle */
               unsigned short    usNcbOpt,  /* ncb chaining options */
               struct ncb far *  pNCB /* points to chained or unchaned NCB */
);

/* Netbios error codes */
#define NERR_Success                0  /* The function encounted no errors   */
#define ERROR_INVALID_FUNCTION      1  /* The function is invalid            */
#define ERROR_FILE_NOT_FOUND        2  /* The file was not found             */
#define ERROR_ACCESS_DENIED         5  /* The user doesn't have privileges   */
#define ERROR_INVALID_HANDLE        6  /* The handle specified is invalid    */
#define ERROR_NO_MORE_FILES        18  /* No more files available            */
#define ERROR_NOT_SUPPORTED        50  /* This network request not supported */
#define ERROR_BAD_NETPATH          53  /* The network path was not found     */
#define ERROR_NETWORK_ACESS_DENIED 65  /* Network access is denied           */
#define ERROR_INVALID_PARAMETER    87  /* The paremeter specified is invalid */
#define ERROR_INVALID_LEVEL       124  /* The level for information retrieval or setting is invalid */
#define ERROR_MORE_DATA           234  /* Additional data is available       */
#define NERR_NetNotStarted       2102  /* NETWKSTA driver is not installed   */
#define NERR_BufTooSmall         2123  /* The supplied buffer is too small   */
#define NERR_BadTransactConfig   2141  /* The server is not configured for this transaction; IPC$ is not shared */
#define NERR_InvalidComputer     2351  /* computername is invalid            */

