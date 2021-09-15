#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include "NetBios\NetBios.H"

#define CB_NAME_TERMINATOR      0x80
#define GROUP_NAME                 2
#define UNIQUE_NAME                1

struct Ncb ZeroNcb;

#define DATAGRAM_MSG_SIZE sizeof(OutDatagram)

extern int Whose_Turn;
extern char PName[16][9];
extern unsigned char PNameNum[16];

/*  Level zero routines  */

/*  Flow:
      if (Add Conference Name) works
        if (Add User Name) works
          send "ready" to network
          send "ready" to other group users
          while (working)
            monitor datagrams
            send info to other group users
          send "done" to other group users
          wait for all commands to complete
          cancel incoming datagrams
          delete username
        delete conference name
*/

void IssueReceiveDatagramRequests()
{
	USGI i;

    for (i = 0; i < 5; i++) /*  max_ncbs = 5  */
        NetbiosReceiveDatagram(&InDatagramNcb[i], &InDatagram[i], sizeof(InDatagram[i]));
}

#define TARGET_NCB ((StartingNcb + index) % MAX_NCBS)

unsigned ServiceDatagramNcbs()
{
    static unsigned StartingNcb = 0;  /* must be static  */
           unsigned index = 0;

    while (InDatagramNcb[TARGET_NCB].NcbCmdCplt != COMMAND_PENDING) {
        NetbiosReceiveDatagram(&InDatagramNcb[TARGET_NCB], 
            &InDatagram[TARGET_NCB], sizeof(InDatagram[TARGET_NCB]));
		index++;
	}

	StartingNcb = TARGET_NCB;
    return StartingNcb;
}

void CancelReceiveDatagrams()
{
	USGI i;

    for (i = 0; i < 5; i++) {  /* max_ncbs = 5 */
        if (InDatagramNcb[i].NcbCmdCplt == COMMAND_PENDING)
            NetbiosCancelNcb(&InDatagramNcb[i]);
	}
}

/*
   -----[ SendMessage ]-------------------------------------------------
   If there is no data to send, return  
   Clear Sender's Name field
   Copy Sender's Name into field
   Clear Sender's Text field
   Copy text into field
   send datagram
   ---------------------------------------------------------------------
*/

void SendMessage(char *Message)
{
    unsigned Index;

    if (strlen(Message) == 0) return;

    for (Index = 0; Index < NAME_SIZE; Index++)
		OutDatagram.OriginName[Index] = '\x00';
    strncpy(OutDatagram.OriginName, PName[Whose_Turn], NAME_SIZE);

    for (Index = 0; Index < MAX_KEYBOARD_MSG; Index++)
        OutDatagram.Text[Index] = 'x\00';
    strncpy(OutDatagram.Text, Message, MAX_KEYBOARD_MSG);

    NetbiosSendDatagram(&OutDatagramNcb, &OutDatagram, DATAGRAM_MSG_SIZE);
}

/*  Level one routines  */

unsigned char AddConference(void)
{
    USGC Temp;

    Temp = NetbiosAddName(ConferenceName, GROUP_NAME);
    if (Temp == ILLEGAL_NAME_NUM)
        return FAILURE;
    else 
        return Temp;
}

void DeleteConference(void)
{
    NetbiosDeleteName(ConferenceName);
}

unsigned char AddUsername(void)
{
    USGC Temp;
    
    Temp = NetbiosAddName(PName[Whose_Turn], UNIQUE_NAME);
    if (Temp == ILLEGAL_NAME_NUM)
        return FAILURE;
    else 
        return Temp;
}

void DeleteUsername(void)
{
    NetbiosDeleteName(PName[Whose_Turn]);
}


/* ================ Level two routines ===================== */

void ClearNcb(struct Ncb *NcbPtr)
{
	int i;
	char *CharPtr = (char *) NcbPtr;

	for (i = 0; i < sizeof(ZeroNcb); i++)
		*CharPtr++ = '\x00';
}

USGC NetbiosAddName(char *Name, int NameType)
{
	struct Ncb AddNameNcb;

	NetbiosDeleteName(Name);

	ClearNcb(&AddNameNcb);

	if (NameType == UNIQUE_NAME)
		AddNameNcb.NcbCommand = NETBIOS_ADD_NAME;
	else
		AddNameNcb.NcbCommand = NETBIOS_ADD_GROUP_NAME;

	strncpy(AddNameNcb.NcbName, Name, strlen(Name));
	AddNameNcb.NcbName[15] = CB_NAME_TERMINATOR;

	NetbiosRequest(&AddNameNcb);

	if (!AddNameNcb.NcbRetCode)
		return AddNameNcb.NcbNum;
	else {
        NBErr = AddNameNcb.NcbRetCode;
		return ILLEGAL_NAME_NUM;
	}
}

void NetbiosDeleteName(char *Name)
{
	struct Ncb DeleteNameNcb;

	ClearNcb(&DeleteNameNcb);

	DeleteNameNcb.NcbCommand = NETBIOS_DELETE_NAME;

	strncpy(DeleteNameNcb.NcbName, Name, strlen(Name));
	DeleteNameNcb.NcbName[15] = CB_NAME_TERMINATOR;
	NetbiosRequest(&DeleteNameNcb);
}

void NetbiosSendDatagram(struct Ncb *NcbPtr, struct DgStruct *BufferPtrNear, unsigned BufferSize)
{
	struct DgStruct far *BufferPtrFar;

	while (NcbPtr->NcbCmdCplt == COMMAND_PENDING)
		;				/* spin here for completion! */

	ClearNcb(NcbPtr);

	NcbPtr->NcbCommand = NETBIOS_SEND_DATAGRAM + NO_WAIT;

	BufferPtrFar = (struct DgStruct far *) BufferPtrNear;

	NcbPtr->NcbBufferOffset = (char *) FP_OFF(BufferPtrFar);
	NcbPtr->NcbBufferSegment = (USGI) FP_SEG(BufferPtrFar);

	NcbPtr->NcbLength = DATAGRAM_MSG_SIZE;
    NcbPtr->NcbNum = PNameNum[Whose_Turn];

    strncpy(NcbPtr->NcbCallName, ConferenceName, NAME_SIZE);
	NcbPtr->NcbCallName[15] = CB_NAME_TERMINATOR;

	NetbiosRequest(NcbPtr);
}

void NetbiosReceiveDatagram(struct Ncb *NcbPtr, struct DgStruct *BufferPtrNear, unsigned BufferSize)
{
	struct DgStruct far *BufferPtrFar;

	ClearNcb(NcbPtr);
	NcbPtr->NcbCommand = NETBIOS_RECEIVE_DATAGRAM + NO_WAIT;

	BufferPtrFar = (struct DgStruct far *) BufferPtrNear;

	NcbPtr->NcbBufferOffset = (char *) FP_OFF(BufferPtrFar);
	NcbPtr->NcbBufferSegment = (USGI) FP_SEG(BufferPtrFar);

	NcbPtr->NcbLength = BufferSize;
	NcbPtr->NcbNum = ConferenceNameNum;

	NetbiosRequest(NcbPtr);
}

void NetbiosCancelNcb(struct Ncb *NcbPtrNear)
{
	struct Ncb CancelNcb;
	struct Ncb far *NcbPtrFar = (struct Ncb far *) NcbPtrNear;

	if (NcbPtrNear->NcbCmdCplt == COMMAND_PENDING) {

		ClearNcb(&CancelNcb);

		CancelNcb.NcbCommand = NETBIOS_CANCEL_WAIT_ONLY;

		CancelNcb.NcbBufferOffset = (char *) FP_OFF(NcbPtrFar);
		CancelNcb.NcbBufferSegment = (USGI) FP_SEG(NcbPtrFar);

		NetbiosRequest(&CancelNcb);
	}
}

void NetbiosRequest(struct Ncb *NcbPtrNear)
{
	union REGS InRegs, OutRegs;
    struct SREGS SegRegs;           /*  defined in dos.h       */
	struct Ncb far *NcbPtrFar = (struct Ncb far *) NcbPtrNear;

    NcbPtrNear->NcbLanaNum = 0;     /*  force to adapter zero  */

    segread(&SegRegs);              /*  init the segment regs  */

	SegRegs.es = FP_SEG(NcbPtrFar);
	InRegs.x.bx = FP_OFF(NcbPtrFar);
	int86x(NetbiosInt5C, &InRegs, &OutRegs, &SegRegs);
}

