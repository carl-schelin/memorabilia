#define LINT_ARGS

#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include "netbios.h"

#define CB_NAME_TERMINATOR      0x80
#define GROUP_NAME                 2
#define MAX_KEYBOARD_MSG          60
#define MAX_NCBS                   5
#define NAME_SIZE                 16
#define ESC                     0x1B
#define RETURN                  0x0D
#define UNIQUE_NAME                1

#if defined(LINT_ARGS)
extern  int main(void);
extern  void Participate(void);
extern	void IssueReceiveDatagramRequests(void);
extern	void ServiceDatagramNcbs(void);
extern	void ProcessReceivedDatagram(unsigned int Index);
extern	void CancelReceiveDatagrams(void);
extern	void InitializeKeyboardInputArea(void);
extern	void SetupInputLine(void);
extern	void ServiceKeyboard(void);
extern	void ApplyKeystroke(unsigned char Keystroke);
extern	void SendKeyboardMsg(char *Message);
extern	void EmitUserStatusMsg(char *AppendMsg);
extern	int AddConferenceName(void);
extern	void DeleteConferenceName(void);
extern	unsigned char AddUserName(void);
extern	void DeleteUserName(void);
extern	void ClearNcb(struct Ncb *NcbPtr);
extern	unsigned char NetbiosAddName(char *Name, int NameType);
extern	void NetbiosDeleteName(char *Name);
extern	void NetbiosSendDatagram(struct Ncb *NcbPtr,
			struct DgStruct *BufferPtrNear, unsigned int BufferSize);
extern	void NetbiosReceiveDatagram(struct Ncb *NcbPtr,
			struct DgStruct *BufferPtrNear, unsigned int BufferSize);
extern	void NetbiosCancelNcb(struct Ncb *NcbPtrNear);
extern	void NetbiosRequest(struct Ncb *NcbPtrNear);
extern	int EditArgs(int argc, char * *argv);
extern	void Explain(void);
extern	void ExitNow(void);
#endif

/*--------------------------------------------------------------------------*/

struct Ncb InDgNcb[MAX_NCBS], OutDatagramNcb;

struct DgStruct { 	char OriginName[NAME_SIZE];
					char Text[MAX_KEYBOARD_MSG];
		};

struct DgStruct OutDatagram, InDg[MAX_NCBS];

#define DATAGRAM_MSG_SIZE sizeof(OutDatagram)

char *ConferenceNamePtr = {"Dot2Dot"}, *UserNamePtr = {"Carl"};
USGC ConferenceNameNum, UserNameNum;

USGC NBErr;

/*--------------------------------------------------------------------------*/

int main(void)
{
    printf("copyright by someone\n");

	if (AddConferenceName()) {
		if (AddUserName()) {
			Participate();
            clrscr();
			printf("\n\nOnline program ending at user request...\n");
			CancelReceiveDatagrams();
			DeleteUserName();
		}
		DeleteConferenceName();
	}
	putchar('\n');

	return 0;
}

/*--------------------------------------------------------------------------*/

USGI Participating = TRUE;

char EnterAppend[] = " has joined the conference...\n";
char DepartAppend[] = " has left the conference...\n";

void Participate()
{
	printf("\n\n\n*-- Online as user ");
    printf("\"%s\" in conference \"%s\"...\n", UserNamePtr, ConferenceNamePtr);

	IssueReceiveDatagramRequests();

	EmitUserStatusMsg(EnterAppend);

	SetupInputLine();

	while(Participating) {
		ServiceDatagramNcbs();
		ServiceKeyboard();
	}

	EmitUserStatusMsg(DepartAppend);

	while (OutDatagramNcb.NcbCmdCplt == COMMAND_PENDING)
		;	/*  spin until complete  */

}

/*--------------------------------------------------------------------------*/

void IssueReceiveDatagramRequests()
{
	USGI i;

    for (i = 0; i < MAX_NCBS; i++) /*  max_ncbs = 5  */
		NetbiosReceiveDatagram(&InDgNcb[i], &InDg[i], sizeof(InDg[i]));
}

#define TARGET_NCB ((StartingNcb + index) % MAX_NCBS)

void ServiceDatagramNcbs()
{
	static USGI StartingNcb = 0;  /* must be static  */
		   USGI index = 0;

	while (InDgNcb[TARGET_NCB].NcbCmdCplt != COMMAND_PENDING) {
		ProcessReceivedDatagram(TARGET_NCB);
		NetbiosReceiveDatagram(&InDgNcb[TARGET_NCB], &InDg[TARGET_NCB],
			sizeof(InDg[TARGET_NCB]));
		index++;
	}

	StartingNcb = TARGET_NCB;
}

void ProcessReceivedDatagram(Index)
USGI Index;
{
	USGI i;

	if (!InDgNcb[Index].NcbRetCode) {
		printf("%s => %s", InDg[Index].OriginName, InDg[Index].Text);
	}
}

void CancelReceiveDatagrams()
{
	USGI i;

	for (i = 0; i < MAX_NCBS; i++) {
		if (InDgNcb[i].NcbCmdCplt == COMMAND_PENDING)
			NetbiosCancelNcb(&InDgNcb[i]);
	}
}

/*--------------------------------------------------------------------------*/

char *KeyboardInputPtr, KeyboardInput[MAX_KEYBOARD_MSG];
USGI KeyboardInputLength;

void InitializeKeyboardInputArea()
{
	int i;

	for (i = 1; i < MAX_KEYBOARD_MSG; i++)
		KeyboardInput[i] = '\x00';

	KeyboardInputPtr = KeyboardInput;

	KeyboardInputLength = 0;
}

void SetupInputLine()
{
	int i;

    gotoxy(0, 24);

	for (i = 1; i < 79; i++)
		putchar(' ');

    gotoxy(0, 24);

	printf("%s => ", UserNamePtr);

	InitializeKeyboardInputArea();
}

void ServiceKeyboard()
{
	USGC Keystroke;

	if (kbhit()) {
		switch (Keystroke = (USGC) getch()) {

			case 0x00 :			/* function key  */
				Keystroke = (USGC) getch();
				break;
			case 0x08 :
				if (KeyboardInputLength > 0) {
					printf("\x08 \x08");
					--KeyboardInputLength;
					*(--KeyboardInputPtr) = '\x00';
				}
				break;
			case ESC :			/* quit indicator */
				Participating = FALSE;
				break;
			case RETURN : 		/* send indicator */
				SendKeyboardMsg(KeyboardInput);
				break;
			default :
				ApplyKeystroke(Keystroke);
				break;
		}
	}
}

void ApplyKeystroke(Keystroke)
USGC Keystroke;
{
	if ((KeyboardInputLength+1) >= MAX_KEYBOARD_MSG) {
		putchar('\x07');
		return;
	}

	if ((Keystroke >= ' ') && (Keystroke < 128)) {
		KeyboardInputLength++;
		*(KeyboardInputPtr++) = (char) Keystroke;
		putchar(Keystroke);
		return;
	}
}

void SendKeyboardMsg(Message)
char *Message;
{
	USGI Index;

	if (KeyboardInputLength == 0)
		return;

	for (Index = 0; Index < NAME_SIZE; Index++)
		OutDatagram.OriginName[Index] = '\x00';

    strncpy(OutDatagram.OriginName, UserNamePtr, NAME_SIZE);

    for (Index = 0; Index < MAX_KEYBOARD_MSG; Index++)
        OutDatagram.Text[Index] = 'x\00';

	strncpy(OutDatagram.Text, Message, MAX_KEYBOARD_MSG);

	NetbiosSendDatagram(&OutDatagramNcb, &OutDatagram, DATAGRAM_MSG_SIZE);

	SetupInputLine();
}

/*--------------------------------------------------------------------------*/

char MONITOR[] = "MONITOR!\x07";

void EmitUserStatusMsg(AppendMsg)
char *AppendMsg;
{
	strncpy(OutDatagram.OriginName, MONITOR, strlen(MONITOR)+1);

	strncpy(OutDatagram.Text, UserNamePtr, strlen(UserNamePtr)+1);

	strncat(OutDatagram.Text, AppendMsg);

	NetbiosSendDatagram(&OutDatagramNcb, &OutDatagram, DATAGRAM_MSG_SIZE);
}

/*--------------------------------------------------------------------------*/
