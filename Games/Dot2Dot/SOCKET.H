
struct addr {
    unsigned long fhost;       /* foreign host ip -> uns long number */
    unsigned      fsocket;     /* foreign host socket                */
    unsigned      lsocket;     /* local socket name                  */
    unsigned char protocol;    /*                                    */
};

#ifdef __SOCKET__
int NetError;                  /* global error number holder         */
#else
extern int NetError;
#endif

#define RAW_NET     1
#define RAW_IP      2
#define DGRAM       3
#define STREAM      4
#define RAW_ICMP    5


#define NET_FLG_OOB           0x0001  /* out of band data               */
#define NET_FLG_PEEK          0x0002  /* don't dequeue data             */
#define NET_FLG_DRAIN         0x0004  /* don't copy data                */
#define NET_FLG_DONTROUTE     0x0008  /* reserved                       */
#define NET_FLG_PUSH          0x0010  /* reserved                       */
#define NET_FLG_DONTTRUNCATE  0x0020  /* Don't truncate oversized dgram */
#define NET_FLG_NONBLOCKING   0x0040  /* don't block                    */
#define NET_FLG_BROADCAST     0x0080  /* broadcast data                 */

#define NET_NOERR                    0
#define NET_ERR_INUSE                1
#define NET_DOS_ERR                  2
#define NET_ERR_NOMEM                3
#define NET_ERR_NOTNETCONN           4
#define NET_ERR_ILLEGALOP            5
#define NET_ERR_BADPKT               6
#define NET_ERR_NOHOST               7
#define NET_ERR_CANTOPEN             8
#define NET_ERR_NET_UNREACHABLE      9
#define NET_ERR_HOST_UNREACHABLE    10
#define NET_ERR_PROT_UNREACHABLE    11
#define NET_ERR_PORT_UNREACHABLE    12
#define NET_ERR_TIMEOUT             13
#define NET_ERR_HOSTUNKNOWN         14
#define NET_ERR_NOSERVERS           15
#define NET_ERR_SERVER_ERR          16
#define NET_ERR_BADFORMAT           17
#define NET_ERR_BADARG              18
#define NET_ERR_EOF                 19
#define NET_ERR_RESET               20
#define NET_ERR_WOULD_BLOCK         21
#define NET_ERR_UNBOUND             22
#define NET_ERR_NODESC              23
#define NET_ERR_BADSYSCALL          24
#define NET_ERR_CANTBROADCAST       25
#define NET_ERR_NOTESTAB            26
#define NET_ERR_REENTRY             27
#define NET_ERR_ICMPMSG             28  /* Other ICMP */

