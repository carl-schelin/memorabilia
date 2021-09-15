#define TRUE	1
#define FALSE	0

#define FAILURE  0x00

#ifndef USGC
#define USGC	unsigned char
#endif

#ifndef USGI
#define USGI	unsigned
#endif

#ifndef USGL
#define USGL	unsigned long
#endif

#define MAX_NCBS         1
#define NAME_SIZE        16
#define MAX_KEYBOARD_MSG 60

#define NetbiosInt21FunctionCode	((USGC) 0x2A)
#define NetbiosInt5C				((USGC) 0x5C)

#define COMMAND_PENDING				((USGC) 0xFF)

#define Mcb Ncb

#define MAX_ADAPTER_NUMBER		  1
#define MAX_SESSION_COUNT		254
#define MAX_NAMES				254
#define MAX_COMMAND_COUNT       255

#define NO_WAIT						((USGC) 0x80)

#define NETBIOS_RESET_WAIT_ONLY		((USGC) 0x32)
#define NETBIOS_CANCEL_WAIT_ONLY	((USGC) 0x35)
#define NETBIOS_ADAPTER_STATUS		((USGC) 0x33)
#define NETBIOS_UNLINK_WAIT_ONLY	((USGC) 0x70)
#define NETBIOS_TRACE				((USGC) 0x79)

#define NETBIOS_ADD_NAME			((USGC) 0x30)
#define NETBIOS_ADD_GROUP_NAME		((USGC) 0x36)
#define NETBIOS_DELETE_NAME			((USGC) 0x31)
#define NETBIOS_FIND_NAME			((USGC) 0x78)

#define NETBIOS_CALL				((USGC) 0x10)
#define NETBIOS_LISTEN				((USGC) 0x11)
#define NETBIOS_HANG_UP				((USGC) 0x12)
#define NETBIOS_SEND				((USGC) 0x14)
#define NETBIOS_SEND_NO_ACK			((USGC) 0x71)
#define NETBIOS_CHAIN_SEND			((USGC) 0x17)
#define NETBIOS_CHAIN_SEND_NO_ACK	((USGC) 0x72)
#define NETBIOS_RECEIVE				((USGC) 0x15)
#define NETBIOS_RECEIVE_ANY			((USGC) 0x16)
#define NETBIOS_SESSION_STATUS		((USGC) 0x34)

#define NETBIOS_SEND_DATAGRAM		((USGC) 0x20)
#define NETBIOS_RECEIVE_DATAGRAM	((USGC) 0x21)
#define NETBIOS_SEND_BDATAGRAM		((USGC) 0x22)
#define NETBIOS_RECEIVE_BDATAGRAM	((USGC) 0x23)

#define NETBIOS_INVALID_COMMAND		((USGC) 0x7F)

/* LAN Adapter Types */

#define TOKEN_RING_ADAPTER ((USGC) 0xFF)
#define PC_NETWORK_ATAPTER ((USGC) 0xFE)

/* NETBIOS Version Numbers  */

#define VERSION_MASK ((USGC) 0x0F)

#define PARM_MASK ((USGC) 0xF0)
#define OLD_PARMS ((USGC) 0x10)
#define NEW_PARMS ((USGC) 0x20)

struct Ncb {
	USGC	NcbCommand;			/* command code */
	USGC	NcbRetCode;			/* return code */
	USGC	NcbLsn;				/* local session number */
	USGC	NcbNum;				/* Datagram ADD NAME table entry */

	char *	NcbBufferOffset;	/* I/O buffer offset */
	USGI	NcbBufferSegment;	/* I/O buffer segment */

	USGI	NcbLength;			/* length of data in I/O buffer */

	char	NcbCallName[16];	/* remote system name for CALL */
	char	NcbName[16];		/* local adapter network name */

	USGC	NcbRto;				/* receive timeouts in 1/2 second units */
	USGC	NcbSto;				/* send timeouts in 1/2 second units */

	char *	NcbPostRtnOffset;	/* offset of post routines */
	USGI	NcbPostRtnSegment;	/* segment of post routines */

	USGC	NcbLanaNum;			/* network adapter number to execute cmd */
	USGC	NcbCmdCplt;			/* 0xFF ==> command pending, else cmplted */

	char	NcbReservedArea[14]; /* work area for network card */
};

#define MIN_NAME_NUM		  2
#define MAX_NAME_NUM		254
#define ILLEGAL_NAME_NUM	  0

#define MIN_LSN			  1
#define MAX_LSN			254
#define ILLEGAL_LSN		  0

struct NameTableEntry {
	char EntryName[16];			/* symbolic network name */
	USGC EntryNameNum;			/* associated name number */
	USGC EntryNameStatus;		/* & with 0x0087 for status */
};

struct DlcStatus {
	/* +00 */	USGC PermanentNodeName[6];
	/* +06 */	USGC MajorVersionNumber;	/* low-order nibble only */
	/* +07 */	USGC AlwaysZero;
	/* +08 */	USGC LanAdapterType;
	/* +09 */	USGC MinorVersionNumber;
	/* +10 */	USGI ReportingPeriodMinutes;
	/* +12 */	USGI FrameRegectedReceiveCount;
	/* +14 */	USGI FrameRejectedXmitCount;
	/* +16 */	USGI I_FrameReceiveErrorCount;
	/* +18 */	USGI XmitAbortCount;
	/* +20 */	USGL SuccessfulFrameXmitCount;
	/* +24 */	USGL SuccessfulFrameRcvCount;
	/* +28 */	USGI I_FrameXmitErrorCount;
	/* +30 */	USGI RmtRqstBufferDepletionCount;
	/* +32 */	USGI ExpiredT1TimerCount;
	/* +34 */	USGI ExpiredTiTimerCount;
	/* +36 */	struct LocalTrAdapterStatus far * LocalExtStatPtr;
	/* +40 */	USGI FreeCommandBlocks;
	/* +42 */	USGI CurrentMaxNcbs;
	/* +44 */	USGI MaximumCommands;
	/* +46 */	USGI TransmitBufferDepletionCount;
	/* +48 */	USGI MaximumDatagramPacketSize;
	/* +50 */	USGI PendingSessionCount;
	/* +52 */	USGI MaxPendingSessionCount;
	/* +54 */	USGI MaximumSessions;
	/* +56 */	USGI MaximumSessionPacketSize;
	/* +58 */	USGI NameTableEntryCount;
	/* +60 */	struct NameTableEntry TableEntry[MAX_NAMES];
};

struct LocalTrAdapterStatus {
	/* +00 */	USGI DirInitBringUpErrorCode;
	/* +02 */	USGI DirOpenAdapterErrorCode;
	/* +04 */	USGI LatestRingStatus;
	/* +06 */	USGI LatestAdapterCheckReasonCode;
	/* +08 */	USGI LatestPcDetectedErrorCode;
	/* +10 */	USGC LatestOperationalErrorCode;
	/* +11 */	USGC LatestImplicitCcbReturnCode;
	/* +12 */	USGI AdapterLineErrors;
	/* +14 */	USGI AdapterInternalErrors;
	/* +16 */	USGI AdapterBurstErrors;
	/* +18 */	USGI AdapterAcError;
	/* +20 */	USGI AdapterAbortDelimiter;
	/* +22 */	USGI AdapterReserved1;
	/* +24 */	USGI AdapterLostFrame;
	/* +26 */	USGI AdapterReceiveCongestion;
	/* +28 */	USGI AdapterFrameCopiedErrors;
	/* +30 */	USGI AdapterFrequencyErrors;
	/* +32 */	USGI AdapterTokenErrors;
	/* +34 */	USGI AdapterReserved2;
	/* +36 */	USGI AdapterReserved3;
	/* +38 */	USGI AdapterReserved4;
};

struct LanaStatus {
	/* +00 */	USGC PermanentNodeName[6];
	/* +06 */	USGC ExternalJumperSetting;
	/* +07 */	USGC SelfTestResults;
	/* +08 */	USGC SoftwareVersionMajor;
	/* +09 */	USGC SoftwareVersionMinor;
	/* +10 */	USGI ReportingPeriodMinutes;
	/* +12 */	USGI CrcErrorCount;
	/* +14 */	USGI AlignmentErrors;
	/* +16 */	USGI CollisionCount;
	/* +18 */	USGI XmitAbortCount;
	/* +20 */	USGL SuccessfulXmits;
	/* +24 */	USGL SuccessfulRcvs;
	/* +28 */	USGI RetransmitCount;
	/* +30 */	USGI ResourceDepletionCount;
	/* +32 */	char ReservedArea1[8];
	/* +40 */	USGI FreeCommandBlocks;
	/* +42 */	USGI CurrentMaxNcbs;
	/* +44 */	USGI HwMaxCommandBlocks;
	/* +46 */	char ReservedArea2[4];
	/* +50 */	USGI PendingSessionCount;
	/* +52 */	USGI CurrentMaxPendingSessions;
	/* +54 */	USGI HwMaxSessionCount;
	/* +56 */	USGI MaximumPacketSize;
	/* +58 */	USGI NameTableEntryCount;
	/* +60 */	struct NameTableEntry TableEntry[16];
};

struct DateTimeStruct {
	USGI DateCX;
	USGI DateDX;
	USGI TimeCX;
	USGI TimeDX;
};

struct DgStruct {
    char OriginName[NAME_SIZE];
    char Text[MAX_KEYBOARD_MSG];
};

#define NB_ILLEGAL_BUFFER_LENGTH		0x01
#define NB_INVALID_COMMAND				0x03
#define NB_COMMAND_TIMED_OUT			0x05
#define NB_MESSAGE_INCOMPLETE			0x06
#define NB_NO_ACK_FAILURE				0x07
#define NB_ILLEGAL_LSN					0x08
#define NB_NO_RESOURCE_AVAILABLE		0x09
#define NB_SESSION_CLOSED				0x0A
#define NB_COMMAND_CANCELED				0x0B
#define NB_DUPLICATE_LOCAL_NAME			0x0D
#define NB_NAME_TABLE_FULL				0x0E
#define NB_NAME_HAS_ACTIVE_SESSIONS		0x0F

#define NB_LOCAL_SESSION_TABLE_FULL		0x11
#define NB_SESSION_OPEN_REJECTED		0x12
#define NB_ILLEGAL_NAME_NUMBER			0x13
#define NB_CANNOT_FIND_CALLED_NAME		0x14
#define NB_NAME_NOT_FOUND_OR_ILLEGAL	0x15
#define NB_NAME_USED_ON_RMT_ADAPTER		0x16
#define NB_NAME_DELETED					0x17
#define NB_SESSION_ENDED_ABNORMALLY		0x18
#define NB_NAME_CONFLICT_DETECTED		0x19
#define NB_INCOMPATIBLE_RMT_DEVICE		0x1A

#define NB_INTERFACE_BUSY				0x21
#define NB_TOO_MANY_COMMANDS_PENDING	0x22
#define NB_INVALID_ADAPTER_NUMBER		0x23
#define NB_CMD_COMPLETED_DURING_CANCEL	0x24
#define NB_RESERVED_NAME_SPECIFIED		0x25
#define NB_CMD_NOT_VALID_TO_CANCEL		0x26

#define NB_LANA_SYSTEM_ERROR			0x40
#define NB_LANA_REMOTE_HOT_CARRIER		0x41
#define NB_LANA_LOCAL_HOT_CARRIER		0x42
#define NB_LANA_NO_CARRIER_DETECTED		0x43
#define NB_UNUSUAL_NETWORK_CONDITION	0x44

#define NB_ADAPTER_MALFUNCTION			0x50

#define NB_COMMAND_PENDING				0xFF

#define MAX_SESSION_BUFFER_SIZE			8192

struct SessionMsg {
	USGL TextLength;
	char Text[MAX_SESSION_BUFFER_SIZE];
};

extern unsigned char NBErr;
extern unsigned int CurrentDg;

extern struct DgStruct OutDatagram, InDatagram[MAX_NCBS];
extern struct Ncb OutDatagramNcb, InDatagramNcb[MAX_NCBS];

extern char *ConferenceName, *UserName;
extern unsigned char ConferenceNameNum, UserNameNum;
/*---------------------*/
extern void IssueReceiveDatagramRequests();
extern unsigned ServiceDatagramNcbs();
extern void CancelReceiveDatagrams();
extern void SendMessage(char *Message);
/*--------------------*/
extern unsigned char AddConference(void);
extern void DeleteConference(void);
extern unsigned char AddUsername(void);
extern void DeleteUsername(void);
/*--------------------*/
extern void ClearNcb(struct Ncb *NcbPtr);
extern unsigned char NetbiosAddName(char *Name, int NameType);
extern void NetbiosDeleteName(char *Name);
extern void NetbiosSendDatagram(struct Ncb *NcbPtr, struct DgStruct *BufferPtrNear, unsigned BufferSize);
extern void NetbiosReceiveDatagram(struct Ncb *NcbPtr, struct DgStruct *BufferPtrNear, unsigned BufferSize);
extern void NetbiosCancelNcb(struct Ncb *NcbPtrNear);
/*--------------------*/
extern void NetbiosRequest(struct Ncb *NcbPtrNear);

