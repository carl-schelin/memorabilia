#include <alloc.h>
#include <conio.h>
#include <ctype.h>
#include <dos.h>
#include <fcntl.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys\stat.h>

#include "mouse\mouse.h"
#include "netbios\netbios.h"

#define MouFunc(n)       { _AX=n; geninterrupt(0x33); }
#define AUTHOR           "Carl Schelin"

#define PLUS             1
#define MINUS            2
#define NETWORK          0
#define ARROW            1
#define WATCH            2
#define HOURGLASS        3
#define PLAYER1          YELLOW
#define PLAYER2          BLUE
#define PLAYER3          GREEN
#define PLAYER4          RED

int  Are_You_Sure(void);
void Change_Turn(int Player1, int Player2, int Player3);
void Check_For_HFill(int, int);
void Check_For_VFill(int, int);
void Create_Screen(void);
void Draw_Button(int, int, int, int, char *, int, int, int, int, int);
void Draw_Dot_Matrix(void);
void Draw_Pressed(int, int, int, int, int, int);
void Draw_Release(int, int, int, int, int, int);
void Draw_Shadow(int, int, int, int, int);
void Get_Name(int getWho);
void Get_New_Matrix(void);
void Get_Partner(void);
void Initialize(int passVga, int passNetCheck);
void Initialize_Pointer(int WhichPointer);
void Introduction(void);
int  Marker(int, int);
void Press_Button(int);
void Press_Matrix_Button(int);
void Print_Coordinates(int, int);
void Print_Matrix(void);
void Print_Message(char *Message);
void Push_Small_Button(int);
void Push_Sure_Button(int);
void ReSize_Board(void);
void Swap_Names(void);
void Update_Scores(void);
int  Verify_Range(int, int, int, int, int, int);
void Wait_For_Input(void);
void Wait_For_It(void);
int huge DetectVGA16();

unsigned oCol = 0, oRow = 0;
char Message[80];
int Matrix_Size = 15;
int Mouse = TRUE;
int Whose_Turn = -1;
int PScore[16];
int inpCh = 0;
char PName[16][9];
char *mFilter = {"GHIKMOPQ"};
char *CName[] = {
    "        ", "        ", "        ", "        ", "        ", "        ",
    "        ", "        ", "        ", "        ", "        ", "        ",
    "        ", "        ", "        ", "        "
};
void *Board_Buffer, *KeyPoint;
int BoardHeight = 0;
unsigned char PNameNum[16];

/*  Storage of 450 moves and 50 overhead                          */
/*  Moves include:                                                */
/*    yXXXXXXXX modifies the YELLOW user                          */
/*    bXXXXXXXX modifies the BLUE user                            */
/*    gXXXXXXXX modifies the GREEN user                           */
/*    rXXXXXXXX modifies the RED user                             */
/*    s999 999  where 999 = column and 999 = row of area selected */
int Replay = FALSE;
int SaveIndex = 0;
unsigned int CurrentDg = 0, OldCurDg = 0;
char SavedMoves[500][11];  /* storage of saved moves 450 moves plus overhead */

int Network = FALSE;
char *ConferenceName = "Dot2Dot", *UserName = "         ";
unsigned char ConferenceNameNum = FAILURE, NBErr = FAILURE;

struct DgStruct OutDatagram, InDatagram[MAX_NCBS];
struct Ncb OutDatagramNcb, InDatagramNcb[MAX_NCBS];

void main(int argc, char **argv)
{
    unsigned pRow = 304, pCol = 490, buttonVal, backRow, backCol;
    int exiting = FALSE, passNetCheck = TRUE, passVga = FALSE;
    int with_Null = 0, j, incColor = 0;
    FILE *output;

    for (j = 0; j < argc; j++) {
        if (strncmp(argv[j], "/n", 2) == 0)
            passNetCheck = FALSE;
        if (strncmp(argv[j], "/v", 2) == 0)
            passVga = TRUE;
    }
    setpalette(0, incColor);
    Initialize(passVga, passNetCheck);
    Introduction();
    Create_Screen();
    Update_Scores();
    setactivepage(0);
    Initialize_Pointer(ARROW);
    while (!exiting) {
        if (Mouse) MouDrawPtr();
        if (Mouse) MouSetPtrPos(pRow, pCol);
        while (!exiting) {
            inpCh = 0;
            /*  if network is running
                  if network user's turn
                    wait until valid packet info arrives
                      get packet info
                    extract valid coords from packet
                    if valid mark screen with line
                  else
                    wait for input
                else
                  wait for input
            */
            if (Network) {
                if (Whose_Turn > -1 && strcmp(CName[Whose_Turn], PName[Whose_Turn]) == 0) {
                    Initialize_Pointer(NETWORK);
                    while (TRUE) {
                        while (strncmp(AUTHOR, InDatagram[CurrentDg].Text, strlen(AUTHOR)) != 0)
                            CurrentDg = ServiceDatagramNcbs();
                        printf("[%s][%d]%s -> %s%c", PName[PLAYER2], Whose_Turn, InDatagram[CurrentDg].OriginName, InDatagram[CurrentDg].Text, 0x0D);
                        if (InDatagram[CurrentDg].Text[strlen(AUTHOR)] == 's') {
                            sscanf(InDatagram[CurrentDg].Text + (strlen(AUTHOR) + 1), "%d %d", &backRow, &backCol);
                            if (Verify_Range(10, 10, 469, BoardHeight - 10, backRow, backCol)) {
                                sprintf(SavedMoves[SaveIndex++], "s%3d %3d", backRow, backCol);
                                Marker(backRow, backCol);
                                break;
                            }
                        }
                        if (kbhit()) break;
                    }
                    Initialize_Pointer(ARROW);
                }
                else {
                    MouCharIn(&pRow, &pCol, &buttonVal);
                }
            }
            else {
                MouCharIn(&pRow, &pCol, &buttonVal);
            }
            if (kbhit()) {
                inpCh = getch();
                if (inpCh == 0)
                    with_Null = getch();
                else
                    with_Null = 0;
                if (!Mouse) {
                    for (j = 0; j < 8; j++) 
                        if (with_Null == mFilter[j])
                            putimage(pRow - oRow, pCol - oCol, KeyPoint, XOR_PUT);
                }
                switch (with_Null) {
                    case 'G' : pRow-- ; pCol-- ; break;
                    case 'H' : pRow-=5;          break;
                    case 'I' : pRow-- ; pCol++ ; break;
                    case 'K' :          pCol-=5; break;
                    case 'M' :          pCol+=5; break;
                    case 'O' : pRow++ ; pCol-- ; break;
                    case 'P' : pRow+=5;          break;
                    case 'Q' : pRow++ ; pCol++ ; break;
                }
                switch (inpCh) {
                    case 's' : 
                        if ((output = fopen("Dot2Dot.Dat", "w")) != NULL) {
                            for (j = 0; j < SaveIndex; j++)
                                fprintf(output, "%s\n", SavedMoves[j]);
                            fclose(output);
                        }
                        break;

                    case 'S' :
                        Replay = TRUE;
                        if (SaveIndex == 0) {
                            if ((output = fopen("Dot2Dot.Dat", "r")) != NULL) {
                                while (!feof(output)) {
                                    fgets(SavedMoves[SaveIndex], 11, output);
                                    SavedMoves[SaveIndex][strlen(SavedMoves[SaveIndex]) - 1] = '\0';
                                    switch (SavedMoves[SaveIndex][0]) {
                                        case 's' :
                                            sscanf(SavedMoves[SaveIndex++] + 1, "%d %d", &pRow, &pCol);
                                            Marker(pRow, pCol);
                                            break;

                                        case 'y' :
                                            if (strlen(SavedMoves[SaveIndex]) > 1) 
                                                strcpy(PName[PLAYER1], SavedMoves[SaveIndex] + 1);
                                            else {
                                                PName[PLAYER1][0] = '\0';
                                                if (Whose_Turn == PLAYER1)
                                                    Change_Turn(PLAYER2, PLAYER3, PLAYER4);
                                            }
                                            Get_Name(PLAYER1);
                                            SaveIndex++;
                                            break;

                                        case 'b' :
                                            if (strlen(SavedMoves[SaveIndex]) > 1) 
                                                strcpy(PName[PLAYER2], SavedMoves[SaveIndex] + 1);
                                            else {
                                                PName[PLAYER2][0] = '\0';
                                                if (Whose_Turn == PLAYER2)
                                                    Change_Turn(PLAYER3, PLAYER4, PLAYER1);
                                            }
                                            Get_Name(PLAYER2);
                                            SaveIndex++;
                                            break;

                                        case 'g' :
                                            if (strlen(SavedMoves[SaveIndex]) > 1) 
                                                strcpy(PName[PLAYER3], SavedMoves[SaveIndex] + 1);
                                            else {
                                                PName[PLAYER3][0] = '\0';
                                                if (Whose_Turn == PLAYER3)
                                                    Change_Turn(PLAYER4, PLAYER1, PLAYER2);
                                            }
                                            Get_Name(PLAYER3);
                                            SaveIndex++;
                                            break;

                                        case 'r' :
                                            if (strlen(SavedMoves[SaveIndex]) > 1) 
                                                strcpy(PName[PLAYER4], SavedMoves[SaveIndex] + 1);
                                            else {
                                                PName[PLAYER4][0] = '\0';
                                                if (Whose_Turn == PLAYER4)
                                                    Change_Turn(PLAYER1, PLAYER2, PLAYER3);
                                            }
                                            Get_Name(PLAYER4);
                                            SaveIndex++;
                                            break;
                                    }
                                }
                            }
                        }
                        Replay = FALSE;
                        break;

                    case 'm' :
                    case 'M' : 
                        Press_Button(1);
                        Initialize_Pointer(WATCH);
                        if (Network)
                            Initialize_Pointer(NETWORK);
                        if (incColor > 0xFF)
                            incColor = 0;
                        /* setpalette(0, incColor++); */
                        inpCh = 0;
                        break;

                    case 'p' :
                    case 'P' : 
                        Press_Button(2);
                        Initialize_Pointer(ARROW);
                        if (Network)
                            Initialize_Pointer(ARROW);
                        Get_Partner();             /* part of {} later */
                        inpCh = 0;
                        break;

                    case 'n' :
                    case 'N' : 
                        Press_Button(3);
                        Initialize_Pointer(HOURGLASS);
                        if (Are_You_Sure() == 1) {
                            if (Mouse) MouRemovePtr();
                            putimage(14, 14, Board_Buffer, COPY_PUT);
                            putimage(14, 98, Board_Buffer, COPY_PUT);
                            putimage(14, 182, Board_Buffer, COPY_PUT);
                            if (Mouse) MouDrawPtr();
                            for (j = 0; j < 16; j++)
                                PScore[j] = 0;
                            Update_Scores();
                            Get_New_Matrix();
                            SaveIndex = 0;
                            if (Mouse) MouRemovePtr();
                            if (Matrix_Size != 15) ReSize_Board();
                            if (Mouse) MouDrawPtr();
                        }
                        inpCh = 0;
                        break;

                    case 'q' :
                    case 'Q' : 
                        Press_Button(4);
                        if (Are_You_Sure() == 1) {
                            exiting = TRUE;
                            free(Board_Buffer);
                        }
                        inpCh = 0;
                        break;

                    case 'y' :
                    case 'Y' : 
                        Get_Name(PLAYER1);
                        inpCh = 0;
                        break;

                    case 'b' :
                    case 'B' : 
                        Get_Name(PLAYER2); 
                        inpCh = 0; 
                        break;

                    case 'g' :
                    case 'G' : 
                        Get_Name(PLAYER3);
                        inpCh = 0;
                        break;

                    case 'r' :
                    case 'R' : 
                        Get_Name(PLAYER4); 
                        inpCh = 0; 
                        break;
                }
                
                if (Mouse) {
                    MouSetPtrPos(pRow, pCol);
                }
                else {
                    putimage(pRow - oRow, pCol - oCol, KeyPoint, XOR_PUT);
                }
            }
            else
                inpCh = 0;
            Print_Coordinates(pRow, pCol);
            if (LeftMouButton(buttonVal) || inpCh == 13) {
                if (Verify_Range(499, BoardHeight - 142, 609, BoardHeight - 122, pCol, pRow)) {
                    Press_Button(1);
                    if (Network) 
                        Initialize_Pointer(NETWORK);
                }
                if (Verify_Range(499, BoardHeight - 110, 609, BoardHeight - 90, pCol, pRow)) {
                    Press_Button(2);
                    if (Network) 
                        Initialize_Pointer(ARROW);
                        Get_Partner();                 /* part of {} later */
                }
                if (Verify_Range(499, BoardHeight - 78, 609, BoardHeight - 58, pCol, pRow)) {
                    Press_Button(3);
                    if (Are_You_Sure() == 1) {
                        if (Mouse) MouRemovePtr();
                        putimage(14, 14, Board_Buffer, COPY_PUT);
                        putimage(14, 98, Board_Buffer, COPY_PUT);
                        putimage(14, 182, Board_Buffer, COPY_PUT);
                        if (Mouse) MouDrawPtr();
                        for (j = 0; j < 16; j++)
                            PScore[j] = 0;
                        Update_Scores();
                        Get_New_Matrix();
                        SaveIndex = 0;
                        if (Mouse) MouRemovePtr();
                        if (Matrix_Size != 15) ReSize_Board();
                        if (Mouse) MouDrawPtr();
                    }
                }
                if (Verify_Range(499, BoardHeight - 45, 609, BoardHeight - 25, pCol, pRow)) {
                    Press_Button(4);
                    if (Are_You_Sure() == 1) {
                        exiting = TRUE;
                        free(Board_Buffer);
                    }
                }
                if (Verify_Range(583, 24, 603, 41, pCol, pRow)) {
                    Push_Small_Button(1);
                }
                if (Verify_Range(507, 50, 527, 67, pCol, pRow)) {
                    Push_Small_Button(2);
                }
                if (Verify_Range(578,  86, 610, 109, pCol, pRow)) {
                    Get_Name(PLAYER1);
                }
                if (Verify_Range(498, 116, 530, 139, pCol, pRow)) {
                    Get_Name(PLAYER2);
                }
                if (Verify_Range(578, 146, 610, 169, pCol, pRow)) {
                    Get_Name(PLAYER3);
                }
                if (Verify_Range(498, 176, 530, 199, pCol, pRow)) {
                    Get_Name(PLAYER4);
                }
                if (Verify_Range(23, 23, (Matrix_Size-1) * 30 + 30, (Matrix_Size-1) * 21 + 28, pCol, pRow)) {
                    if (Whose_Turn > -1) {
                        if (Marker(pRow, pCol) == TRUE) {
                            sprintf(SavedMoves[SaveIndex++], "s%3d %3d", pRow, pCol);
                            sprintf(Message, AUTHOR"s%3d %3d", pRow, pCol);
                            if (Network) SendMessage(Message);
                        }
                    }
                }
                if (Verify_Range(547, 34, 563, 55, pCol, pRow)) {
                    setvisualpage(1);
                    setbkcolor(LIGHTGRAY);
                    while(kbhit())
                        getch();
                    Wait_For_It();
                    setvisualpage(0);
                    setbkcolor(CYAN);
                }
            }
            if ((PScore[PLAYER1] + PScore[PLAYER2] + PScore[PLAYER3] + PScore[PLAYER4]) == (Matrix_Size * Matrix_Size)) {
                if (Mouse) MouRemovePtr();
                for (j = 0; j < 16; j++)
                    PScore[j] = 0;
                if (Mouse) MouDrawPtr();
            }
        }
        if (exiting) {
            closegraph();
            break;
        }
    }
    if (Mouse) {
        MouRemovePtr();
        if (!MouClose())
            printf("Unable to close mouse\n");
    }
    if (Network) {
        CancelReceiveDatagrams();
        for (j = 0; j < 16; j++) {
            if (PNameNum[j] != FAILURE) {
                printf("Removing %s from the Network\n", PName[j]);
                DeleteUsername();
                printf("%s removed.\n", PName[j]);
            }
        }
        printf("Removing Dot2Dot from the Network\n");
        DeleteConference();
        printf("Dot2Dot removed successfully\n");
    }
}

void Initialize(int passVga, int passNetCheck)
{
    int graphDriver = EGA, graphMode = EGAHI, j, errorcode;

    if (passVga) {
        graphDriver = VGA;
        graphMode = VGAHI;
    }
    registerbgifont(gothic_font);
    registerbgidriver(EGAVGA_driver);
    initgraph(&graphDriver, &graphMode, "");
    errorcode = graphresult();
    if (errorcode != grOk) {
        closegraph();
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        exit(1);
    }
    if (!MouOpen()) Mouse = FALSE;
    if (Mouse) Initialize_Pointer(ARROW);
    for (j = 0; j < 16; j++) PNameNum[j] = FAILURE;
    if (passNetCheck) {
        printf("Requesting Network Access for Dot2Dot\n");
        ConferenceNameNum = AddConference();
        if (ConferenceNameNum != FAILURE) {
            printf("We have at table entry on the Network. Thanks.\n");
            Network = TRUE;
        }
        else
            printf("Sorry about that. ERROR 0x%02x\n", NBErr);
    }
    if (Network) IssueReceiveDatagramRequests();
    for (j = 0; j < 16; j++) {
        PScore[j] = 0;
        PName[j][0] = '\0';
    }
    if (getmaxx() < 639) {
        closegraph();
        printf("Sorry, screen coordinates require 640 pixel wide screen.\n");
        exit(1);
    }
    BoardHeight = getmaxy();
}

int huge DetectVGA16()
{
    return 3;
}

void Initialize_Pointer(int WhichPointer)
{
    unsigned NetworkPointer[] = {
        0xffef,    /* ***********.**** */
        0xffe7,    /* ***********..*** */
        0xc003,    /* **............** */
        0xc001,    /* **.............* */
        0xc000,    /* **.............. */
        0xc001,    /* **.............* */
        0xc003,    /* **............** */
        0xf7e7,    /* ****.******..*** */
        0xe7ef,    /* ***..******.**** */
        0xc003,    /* **............** */
        0x8003,    /* *.............** */
        0x0003,    /* ..............** */
        0x8003,    /* *.............** */
        0xc003,    /* **............** */
        0xe7ff,    /* ***..*********** */
        0xf7ff,    /* ****.*********** */

        0x0000,    /* ................ */
        0x0000,    /* ................ */
        0x0008,    /* ............*... */
        0x1ffc,    /* ...***********.. */
        0x1ffe,    /* ...************. */
        0x1ffc,    /* ...***********.. */
        0x0008,    /* ............*... */
        0x0000,    /* ................ */
        0x0000,    /* ................ */
        0x1000,    /* ...*............ */
        0x3ff8,    /* ..***********... */
        0x7ff8,    /* .************... */
        0x3ff8,    /* ..***********... */
        0x1000,    /* ...*............ */
        0x0000,    /* ................ */
        0x0000     /* ................ */
    };
    unsigned ArrowPointer[] = {
        0xffff,    /* **************** */
        0x3fff,    /* ..************** */
        0x1fff,    /* ...************* */
        0x0fff,    /* ....************ */
        0x07ff,    /* .....*********** */
        0x03ff,    /* ......********** */
        0x01ff,    /* .......********* */
        0x00ff,    /* ........******** */
        0x007f,    /* .........******* */
        0x003f,    /* ..........****** */
        0x03ff,    /* ......********** */
        0x31ff,    /* ..**...********* */
        0xf1ff,    /* ****...********* */
        0xf8ff,    /* *****...******** */
        0xf8ff,    /* *****...******** */
        0xfc7f,    /* ******...******* */

        0x0000,    /* ................ */
        0x0000,    /* ................ */
        0x4000,    /* .*.............. */
        0x6000,    /* .**............. */
        0x7000,    /* .***............ */
        0x7800,    /* .****........... */
        0x7c00,    /* .*****.......... */
        0x7e00,    /* .******......... */
        0x7f00,    /* .*******........ */
        0x7c00,    /* .*****.......... */
        0x4800,    /* .*..*........... */
        0x0400,    /* .....*.......... */
        0x0400,    /* .....*.......... */
        0x0200,    /* ......*......... */
        0x0200,    /* ......*......... */
        0x0000     /* ................ */
    };
    unsigned WatchPointer[] = {
        0xf83f,    /* *****.....****** */
        0xf83f,    /* *****.....****** */
        0xf83f,    /* *****.....****** */
        0xf83f,    /* *****.....****** */
        0xf83f,    /* *****.....****** */
        0xf01f,    /* ****.......***** */
        0xe00f,    /* ***.........**** */
        0xc007,    /* **...........*** */
        0xc103,    /* **.....*......** */
        0xc007,    /* **...........*** */
        0xe00f,    /* ***.........**** */
        0xf01f,    /* ****.......***** */
        0xf83f,    /* *****.....****** */
        0xf83f,    /* *****.....****** */
        0xf83f,    /* *****.....****** */
        0xf83f,    /* *****.....****** */

        0x0000,    /* ................ */
        0x0000,    /* ................ */
        0x0000,    /* ................ */
        0x0000,    /* ................ */
        0x0000,    /* ................ */
        0x07c0,    /* .....*****...... */
        0x0ee0,    /* ....***.***..... */
        0x1ef0,    /* ...****.****.... */
        0x1e10,    /* ...****...**.... */
        0x1ff0,    /* ...*********.... */
        0x0fe0,    /* ....*******..... */
        0x07c0,    /* .....*****...... */
        0x0000,    /* ................ */
        0x0000,    /* ................ */
        0x0000,    /* ................ */
        0x0000     /* ................ */
    };
    unsigned HourPointer[] = {
        0xfffe,    /* **** **** **** ***. */
        0xfffe,    /* **** **** **** ***. */
        0xc006,    /* **.. .... .... .**. */
        0x7ffc,    /* .*** **** **** **.. */
        0x600c,    /* .**. .... .... **.. */
        0x600c,    /* .**. .... .... **.. */
        0x600c,    /* .**. .... .... **.. */
        0x600c,    /* .**. .... .... **.. */
        0x600c,    /* .**. .... .... **.. */
        0x3018,    /* ..** .... ...* *... */
        0x1830,    /* ...* *... ..** .... */
        0x0c60,    /* .... **.. .**. .... */
        0x06c0,    /* .... .**. **.. .... */
        0x07c0,    /* .... .*** **.. .... */
        0x06c0,    /* .... .**. **.. .... */
        0x0c60,    /* .... **.. .**. .... */
        0x1830,    /* ...* *... ..** .... */
        0x3018,    /* ..** .... ...* *... */
        0x600c,    /* .**. .... .... **.. */
        0x600c,    /* .**. .... .... **.. */
        0x600c,    /* .**. .... .... **.. */
        0x600c,    /* .**. .... .... **.. */
        0x600c,    /* .**. .... .... **.. */
        0x7ffc,    /* .*** **** **** **.. */
        0xc006,    /* **.. .... .... .**. */
        0xfffe,    /* **** **** **** ***. */
        0xfffe,    /* **** **** **** ***. */

        0x0001,    /* .... .... .... ...* */
        0x0001,    /* .... .... .... ...* */
        0x3ff9,    /* ..** **** **** *..* */
        0x8003,    /* *... .... .... ..** */
        0x9ff3,    /* *..* **** **** ..** */
        0x9ff3,    /* *..* **** **** ..** */
        0x9ff3,    /* *..* **** **** ..** */
        0x9ff3,    /* *..* **** **** ..** */
        0x9ff3,    /* *..* **** **** ..** */
        0xcfe7,    /* **.. **** ***. .*** */
        0xe7cf,    /* ***. .*** **.. **** */
        0xf39f,    /* **** ..** *..* **** */
        0xf93f,    /* **** *..* ..** **** */
        0xf93f,    /* **** *..* ..** **** */
        0xf93f,    /* **** *..* ..** **** */
        0xf39f,    /* **** ..** *..* **** */
        0xe7cf,    /* ***. .*** **.. **** */
        0xcfe7,    /* **.. **** ***. .*** */
        0x9ff3,    /* *..* **** **** ..** */
        0x9ff3,    /* *..* **** **** ..** */
        0x9ff3,    /* *..* **** **** ..** */
        0x9ff3,    /* *..* **** **** ..** */
        0x9ff3,    /* *..* **** **** ..** */
        0x8003,    /* *... .... .... ..** */
        0x3ff9,    /* ..** **** **** *..* */
        0x0001,    /* .... .... .... ...* */
        0x0001,    /* .... .... .... ...* */
    };

    switch (WhichPointer) {
        case NETWORK   : _ES=_DS;       /*  Point to CommunicationsPointer  */
                         _DX=(int)NetworkPointer;
                         _BX=7;         /*  Horizontal offset of hot spot  */
                         _CX=7;         /*  Vertical offset of hot spot  */
                         break;
 
        case ARROW     : _ES=_DS;       /*  Point to ArrowPointer  */
                         _DX=(int)ArrowPointer;
                         _BX=0;         /*  Horizontal offset of hot spot  */
                         _CX=0;         /*  Vertical offset of hot spot  */
                         break;
        case WATCH     : _ES=_DS;
                         _DX=(int)WatchPointer;
                         _BX=8;
                         _CX=7;
                         break;
        case HOURGLASS : _ES=_DS;
                         _DX=(int)HourPointer;
                         _BX=8;
                         _CX=7;
                         break;
    }
    if (Mouse) MouFunc(9);
}

void Introduction()
{
    setactivepage(1);
    setvisualpage(0);
    setbkcolor(LIGHTGRAY);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 0);
    setusercharsize(4, 1, 4, 1);
    setcolor(DARKGRAY);
    outtextxy(70, 40, "Dot");
    outtextxy(370, 145, "Dot");
    outtextxy(280, 95, "2");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setusercharsize(1, 1, 1, 1);
    setcolor(RED);
    outtextxy(15, 15, "Concept:  Each person draws a line,  either vertical or horizontal.  If that");
    outtextxy(15, 25, "person completes a box, he or she  draws another line.  Whoever has the most");
    outtextxy(15, 35, "completed boxes at the end of the game, wins.");
    outtextxy(15, 55, "History:  When I  was in  high school,  I played  this game.  It was  set up");
    outtextxy(15, 65, "quickly and easily,  needing only paper, pencil  and another player.  When I");
    outtextxy(15, 75, "discussed this  game with my daughter, she had  never heard of it.  I showed");
    outtextxy(15, 85, "it to her,  played a few games and  decided that I could  write it in Basic.");
    outtextxy(15, 95, "That was the first  version.  Now, I am working on  various projects related");
    outtextxy(15, 105, "with  Advanced  Dungeons & Dragons(tm) and  Local Area Networks and  decided");
    outtextxy(15, 115, "that this  is a  great program  to have  Netbios  support.  The  programming");
    outtextxy(15, 125, "concept is simple and it's easy to learn.");
    outtextxy(15, 145, "Information:  Using \"C Programmer's Guide to NETBIOS\" I am learning more and");
    outtextxy(15, 155, "more about Netbios.  I am extracting the  routines and structures and trying");
    outtextxy(15, 165, "to create a  workable library.  The idea is  to use it for Dot2Dot  and then");
    outtextxy(15, 175, "for my AD&D (tm) related utilities.");
    setcolor(WHITE);
    outtextxy(525, 340, "Wait...");
    setactivepage(0);
}

void Create_Screen()
{
    char bitPattern[9] = {0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55};
    char temp[20];
    int j;

    setactivepage(0);
    setvisualpage(1);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        /*  clear screen with the correct pattern  */
     
     setfillpattern(bitPattern, LIGHTGREEN); 
    floodfill(0, 0, LIGHTGREEN);
        /*  draw shadow for the button screen  */
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setcolor(LIGHTGRAY);
    line(481, BoardHeight - 13, 481, 12);
    line(481, 12, 626, 12);
    line(12, BoardHeight - 13, 12, 12);
    line(12, 12, 466, 12);
        /*  create the button screen border  */
    setcolor(BLUE);
    rectangle(479, 10, 629, BoardHeight - 10);
        /*  create the playing board border  */
    setcolor(MAGENTA);
    rectangle(10, 10, 469, BoardHeight - 10);
        /*  now create the buttons  */
    Draw_Button(499, BoardHeight -  45, 609, BoardHeight -  25,    "Quit", BoardHeight -  38, 0, DARKGRAY, LIGHTGRAY, RED);
    Draw_Button(499, BoardHeight -  77, 609, BoardHeight -  57,     "New", BoardHeight -  70, 0, DARKGRAY, LIGHTGRAY, RED);
    Draw_Button(499, BoardHeight - 109, 609, BoardHeight -  89, "Partner", BoardHeight - 102, 0, DARKGRAY, LIGHTGRAY, (Network) ? RED : DARKGRAY);
    Draw_Button(499, BoardHeight - 141, 609, BoardHeight - 121, "Monitor", BoardHeight - 134, 0, DARKGRAY, LIGHTGRAY, (Network) ? RED : DARKGRAY);
        /*  place the Dot 2 Dot logo  */
    setcolor(RED);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 0);
    outtextxy(490, 14, "Dot");
    outtextxy(575, 40, "Dot");
    setcolor(WHITE);
    outtextxy(547, 27, "2");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(497, 75, "by Carl Schelin");
    Draw_Button(583, 24, 603, 41, "", 585, 0, LIGHTGRAY, YELLOW, 0);
    Draw_Button(508, 50, 528, 67, "", 518, 0, DARKGRAY, BLUE, 0);
        /*  setup the character squares  */
    Draw_Button(579,  87, 609, 108, "", 120, 0, LIGHTGRAY, PLAYER1, 0);
    Draw_Button(499, 117, 529, 138, "", 150, 0, DARKGRAY, PLAYER2, 0);
    Draw_Button(579, 147, 609, 168, "", 180, 0, DARKGRAY, PLAYER3, 0);
    Draw_Button(499, 177, 529, 198, "", 210, 0, DARKGRAY, PLAYER4, 0);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
        /*  now let's see the whole schmeere  */
   Draw_Dot_Matrix();
    Board_Buffer = malloc(33522);
    getimage(14, 14, 467, 160, Board_Buffer);
        /*  wait for input at the intro screen  */
    setactivepage(1);
    setcolor(LIGHTGRAY);
    for (j = 340; j < 347; j++)
        line(525, j, 577, j);
    setcolor(WHITE);
    outtextxy(525, 340, "Press a key...");
    setactivepage(0);
    Wait_For_It();
    if (Mouse) MouRemovePtr();
    setvisualpage(0);
    setbkcolor(CYAN);
}

void Wait_For_It(void)
{
    unsigned pRow, pCol, buttonVal;

    if (Mouse) MouDrawPtr();
    while (TRUE) {
        if (Mouse) {
            MouCharIn(&pRow, &pCol, &buttonVal);
            if (LeftMouButton(buttonVal))
                break;
        }
        if (kbhit()) {
            getch();
            break;
        }
    }
}

void Change_Turn(int Player1, int Player2, int Player3)
{
    if (strlen(PName[Player1]) > 0) {
        Whose_Turn = Player1;
    }
    else {
        if (strlen(PName[Player2]) > 0) {
            Whose_Turn = Player2;
        }
        else {
            if (strlen(PName[Player3]) > 0) {
                Whose_Turn = Player3;
            }
            else {
                Whose_Turn = -1;
            }
        }
    }
    Swap_Names();
}

void Press_Button(int which_One)
{
    int which_Button = BoardHeight - 45;

    if (Mouse) MouRemovePtr();
    if (which_One == 1) which_Button = BoardHeight - 141;
    if (which_One == 2) which_Button = BoardHeight - 109;
    if (which_One == 3) which_Button = BoardHeight - 77;
    if (which_One == 4) which_Button = BoardHeight - 45;
    /* remove darkgray, add white end position for former color */
    Draw_Pressed(499, which_Button, 609, which_Button + 20, DARKGRAY, LIGHTGRAY);
    Wait_For_Input();
    Draw_Release(499, which_Button, 609, which_Button + 20, DARKGRAY, LIGHTGRAY);
    if (Mouse) MouDrawPtr();
}

void Push_Small_Button(int which_One)
{
    int leftSide, topSide;

    if (which_One == 1) {
        leftSide = 583;
        topSide = 24;
    }
    if (which_One == 2) {
        leftSide = 508;
        topSide = 50;
    }
    if (Mouse) MouRemovePtr();
    Draw_Pressed(leftSide, topSide, leftSide + 20, topSide + 17, 
        (topSide==24 ? LIGHTGRAY : DARKGRAY), (topSide==24 ? YELLOW : BLUE));
    Wait_For_Input();
    Draw_Release(leftSide, topSide, leftSide + 20, topSide + 17,
        (topSide==24 ? LIGHTGRAY : DARKGRAY), (topSide==24 ? YELLOW : BLUE));
    if (Mouse) MouDrawPtr();
}

void Draw_Dot_Matrix()
{
    int j, k, max;

    if (BoardHeight == 479)
        max = 21;
    else
        max = 15;
    setcolor(WHITE);
    for (j = 0; j < 15; j++) {
        for (k = 0; k < max; k++) {
            circle(j * 30 + 30, k * 21 + 28, 2);
            circle(j * 30 + 30, k * 21 + 28, 1);
            putpixel(j * 30 + 30, k * 21 + 28, WHITE);
        }
    }
}

int Marker(int bRow, int bCol)
{
    int mRow, mCol, dRow, dCol, retVal = FALSE;
    unsigned pRow, pCol, buttonVal;

    mRow = (bRow - 28) / 21;
    mCol = (bCol - 30) / 30;
    mRow = mRow * 21 + 28;
    mCol = mCol * 30 + 30;
    dCol = mCol - bCol;
    dRow = mRow - bRow;
    if (dCol > -3 && dCol < 3) bCol = mCol;
    if (dRow > -3 && dRow < 3) bRow = mRow;
    if (mRow == bRow || mCol == bCol) {
        if (Mouse) MouRemovePtr();
        setcolor(WHITE);
        setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
        if (mRow == bRow) {
            if (getpixel(mCol + 15, mRow) != WHITE) {
                if (mCol < (Matrix_Size-1) * 30 + 30) {
                    retVal = TRUE;
                    line(mCol, mRow, mCol + 30, mRow);
                    Check_For_VFill(mRow, mCol);
                }
            }
        }
        else {
            if (mCol == bCol) {
                if (getpixel(mCol, mRow + 10) != WHITE) {
                    if (mRow < (Matrix_Size-1) * 21 + 28) {
                        retVal = TRUE;
                        line(mCol, mRow, mCol, mRow + 21);
                        Check_For_HFill(mRow, mCol);
                    }
                }
            }
        }
        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
        Swap_Names();
        if (Mouse) MouDrawPtr();
        if (Mouse && !Replay) {
            MouCharIn(&pRow, &pCol, &buttonVal);
            while (LeftMouButton(buttonVal)) MouCharIn(&pRow, &pCol, &buttonVal);
        }
    }
    return retVal;
}

void Check_For_VFill(int bRow, int bCol)
{
    int colorSet, scored = 0, j, placeHolder;

    /* ÚÄ¿                             */
    /* ÀxÙ filling the box to the top  */

    if (getpixel(bCol + 3, bRow - 3) != PLAYER1 && 
        getpixel(bCol + 3, bRow - 3) != PLAYER2 &&
        getpixel(bCol + 3, bRow - 3) != PLAYER3 &&
        getpixel(bCol + 3, bRow - 3) != PLAYER4) {

        colorSet = getpixel(bCol + 15, bRow     ) +
                   getpixel(bCol + 30, bRow - 10) +
                   getpixel(bCol + 15, bRow - 21) +
                   getpixel(bCol     , bRow - 10);
        if (colorSet == WHITE * 4) {
            Draw_Button(bCol + 3, bRow - 18, bCol + 27, bRow - 3, "", bCol + 2,
                0, (Whose_Turn==YELLOW ? LIGHTGRAY : DARKGRAY), Whose_Turn, 0);
            PScore[Whose_Turn]++;
            scored = 1;
        }
    }

    /* Úx¿ filling the box to the bottom  */
    /* ÀÄÙ                                */

    if (getpixel(bCol + 3, bRow + 3) != PLAYER1 &&
        getpixel(bCol + 3, bRow + 3) != PLAYER2 &&
        getpixel(bCol + 3, bRow + 3) != PLAYER3 &&
        getpixel(bCol + 3, bRow + 3) != PLAYER4) {

        colorSet = getpixel(bCol + 15, bRow     ) +
                   getpixel(bCol + 30, bRow + 10) +
                   getpixel(bCol + 15, bRow + 21) +
                   getpixel(bCol     , bRow + 10);
        if (colorSet == WHITE * 4) {
            Draw_Button(bCol + 3, bRow + 3, bCol + 27, bRow + 18, "", bCol + 2,
                0, (Whose_Turn==YELLOW ? LIGHTGRAY : DARKGRAY), Whose_Turn, 0);
            PScore[Whose_Turn]++;
            scored = 1;
        }
    }
    if (!scored) {
        placeHolder = Whose_Turn;
        for (j = Whose_Turn + 1; j < 16; j++)
            if (strlen(PName[j]) > 0) {
                Whose_Turn = j;
                break;
            }
        if (placeHolder == Whose_Turn)
            for (j = 0; j <= Whose_Turn; j++)
                if (strlen(PName[j]) > 0) {
                    Whose_Turn = j;
                    break;
                }
    }
    else
        Update_Scores();
}

void Check_For_HFill(int bRow, int bCol)
{
    int colorSet, scored = 0, j, placeHolder;

    /*                               ÚÄÄ¿ */
    /*  filling the box to the right x  ³ */
    /*                               ÀÄÄÙ */

    if (getpixel(bCol + 3, bRow + 3) != PLAYER1 && 
        getpixel(bCol + 3, bRow + 3) != PLAYER2 &&
        getpixel(bCol + 3, bRow + 3) != PLAYER3 &&
        getpixel(bCol + 3, bRow + 3) != PLAYER4) {

        colorSet = getpixel(bCol     , bRow + 10) +
                   getpixel(bCol + 15, bRow + 21) +
                   getpixel(bCol + 30, bRow + 10) +
                   getpixel(bCol + 15, bRow     );
        if (colorSet == WHITE * 4) {
            Draw_Button(bCol + 3, bRow + 3, bCol + 27, bRow + 18, "", bCol + 2,
                0, (Whose_Turn==YELLOW ? LIGHTGRAY : DARKGRAY), Whose_Turn, 0);
            PScore[Whose_Turn]++;
            scored = 1;
        }
    }

    /* ÚÄÄ¿                              */
    /* ³  x filling the box to the left  */
    /* ÀÄÄÙ                              */

    if (getpixel(bCol - 3, bRow + 3) != PLAYER1 &&
        getpixel(bCol - 3, bRow + 3) != PLAYER2 &&
        getpixel(bCol - 3, bRow + 3) != PLAYER3 &&
        getpixel(bCol - 3, bRow + 3) != PLAYER4) {

        colorSet = getpixel(bCol     , bRow + 10) +
                   getpixel(bCol - 15, bRow + 21) +
                   getpixel(bCol - 30, bRow + 10) +
                   getpixel(bCol - 15, bRow     );
        if (colorSet == WHITE * 4) {
            Draw_Button(bCol - 27, bRow + 3, bCol - 3, bRow + 18, "", bCol + 2,
                0, (Whose_Turn==YELLOW ? LIGHTGRAY : DARKGRAY), Whose_Turn, 0);
            PScore[Whose_Turn]++;
            scored = 1;
        }
    }
    /* loop from current to end. if not found, go from beginning to current */
    if (!scored) {
        placeHolder = Whose_Turn;
        for (j = Whose_Turn + 1; j < 16; j++)
            if (strlen(PName[j]) > 0) {
                Whose_Turn = j;
                break;
            }
        if (placeHolder == Whose_Turn)
            for (j = 0; j <= Whose_Turn; j++)
                if (strlen(PName[j]) > 0) {
                    Whose_Turn = j;
                    break;
                }
    }
    else
        Update_Scores();
}

void Get_Name(int getWho)
{
    void *buffer;
    unsigned size, pRow, pCol, buttonVal;
    int inpCh, keepCount = 0, j;
    char tempName[20];

    if (Mouse) MouRemovePtr();

    if (Network)
        if (PNameNum[getWho] != FAILURE) {
            DeleteUsername();
            sprintf(Message, "%s removed from the Network", PName[getWho]);
            Print_Message(Message);
            PNameNum[getWho] = FAILURE;
        }
    size = imagesize(534, 194, 599, 203);
    buffer = malloc(size);
    switch(getWho) {
        case PLAYER1: 
            getimage(533, 194, 598, 203, buffer);
            putimage(501,  94, buffer, COPY_PUT);
            break;

        case PLAYER2 :
            getimage(534, 194, 599, 203, buffer);
            putimage(546, 124, buffer, COPY_PUT);
            break;

        case PLAYER3 : 
            getimage(533, 194, 598, 203, buffer);
            putimage(501, 154, buffer, COPY_PUT);
            break;

        case PLAYER4 : 
            getimage(534, 194, 599, 203, buffer);
            putimage(546, 184, buffer, COPY_PUT);
            break;
    }
    free(buffer);

    if (!Replay) {
        size = imagesize(175, 150, 305, 205);
        buffer = malloc(size);
        getimage(175, 150, 305, 205, buffer);
        Draw_Button(176, 151, 299, 199, "Enter Name:", 159, 1, DARKGRAY, getWho, getWho==YELLOW ? DARKGRAY : WHITE);
        setcolor(getWho==YELLOW ? DARKGRAY : WHITE);
        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
        line(204, 177, 268, 177);
        for (j = 204; j < 269; j+=8) {
            putpixel(j, 178, getWho==YELLOW ? DARKGRAY : WHITE);
            putpixel(j, 187, getWho==YELLOW ? DARKGRAY : WHITE);
        }
        line(204, 188, 268, 188);
        setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
        while (TRUE) {
            inpCh = getch();
            if (inpCh == 0) {
                inpCh = getch();
                inpCh = 0;
            }
            if (inpCh == 8 && keepCount > 0) {
                setcolor(getWho);
                keepCount--;
                for (j = 180; j < 186; j++)
                    line(keepCount * 8 + 204, j, keepCount * 8 + 212, j);
                tempName[keepCount] = '\0';
                setcolor(getWho==YELLOW ? DARKGRAY : WHITE);
            }
            if (inpCh == 13 || keepCount > 7) {
                tempName[keepCount] = '\0';
                strcpy(PName[getWho], tempName);
                break;
            }
            if (isalpha(inpCh)) {
                tempName[keepCount++] = inpCh;
                tempName[keepCount] = '\0';
                outtextxy(205, 179, tempName);
            }
        }
        putimage(175, 150, buffer, COPY_PUT);
        free(buffer);
    }
    if (Whose_Turn == -1)
        Whose_Turn = getWho;
    setcolor(DARKGRAY);
    switch (getWho) {
        case PLAYER1: outtextxy(504,  96, PName[PLAYER1]);break;
        case PLAYER2: outtextxy(549, 126, PName[PLAYER2]);break;
        case PLAYER3: outtextxy(504, 156, PName[PLAYER3]);break;
        case PLAYER4: outtextxy(549, 186, PName[PLAYER4]);break;
    }
    keepCount = Whose_Turn;
    Whose_Turn = getWho;
    Update_Scores();
    Whose_Turn = keepCount;
    Swap_Names();
    if (getWho == PLAYER1) keepCount = 'y';
    if (getWho == PLAYER2) keepCount = 'b';
    if (getWho == PLAYER3) keepCount = 'g';
    if (getWho == PLAYER4) keepCount = 'r';
    sprintf(SavedMoves[SaveIndex++], "%c%s", keepCount, PName[getWho]);
    if (strlen(PName[getWho]) == 0) {
        if (Whose_Turn == getWho) {
            switch (getWho) {
                case PLAYER1 : Change_Turn(PLAYER2, PLAYER3, PLAYER4); break;
                case PLAYER2 : Change_Turn(PLAYER3, PLAYER4, PLAYER1); break;
                case PLAYER3 : Change_Turn(PLAYER4, PLAYER1, PLAYER2); break;
                case PLAYER4 : Change_Turn(PLAYER1, PLAYER2, PLAYER3); break;
            }
        }
    }
    else 
        if (Network) {
            PNameNum[getWho] = AddUsername();
            if (PNameNum[getWho] == FAILURE) {
                DeleteConference();
            }
            else {
                sprintf(Message, AUTHOR"%s Ready", PName[getWho]);
                SendMessage(Message);
                sprintf(Message, "Network access granted to %s", PName[getWho]);
                Print_Message(Message);
            }
        }
    if (Mouse) MouDrawPtr();
}

void Update_Scores()
{
    char scores[10];
    int j;

        /*  clear all text areas  */
    setcolor(Whose_Turn);
    switch (Whose_Turn) {
        case PLAYER1 : 
            for (j = 93; j < 102; j++) 
                line(581, j, 607, j);  /*  clear text area  */
            if (PName[PLAYER1][0] != '\0') {
                setcolor(DARKGRAY);
                itoa(PScore[PLAYER1], scores, 10);
                outtextxy(581, 94, scores);
            }
            break;

        case PLAYER2 :
            for (j = 123; j < 132; j++) 
                line(501, j, 527, j);
            if (PName[PLAYER2][0] != '\0') {
                setcolor(WHITE);
                itoa(PScore[PLAYER2], scores, 10);
                outtextxy(501, 124, scores);
            }
            break;

        case PLAYER3 :
            for (j = 153; j < 162; j++) 
                line(581, j, 607, j);
            if (PName[PLAYER3][0] != '\0') {
                setcolor(WHITE);
                itoa(PScore[PLAYER3], scores, 10);
                outtextxy(581, 154, scores);
            }
            break;

        case PLAYER4 :
            for (j = 183; j < 192; j++) 
                line(501, j, 527, j);
            if (PName[PLAYER4][0] != '\0') {
                setcolor(WHITE);
                itoa(PScore[PLAYER4], scores, 10);  /*  convert and print  */
                outtextxy(501, 184, scores);    /*  another's score    */
            }
            break;
    }
}

void Swap_Names()
{
    setcolor(Whose_Turn);
    if (Whose_Turn == PLAYER1) {
        outtextxy(501,  94, PName[PLAYER1]);
        setcolor(LIGHTGRAY);
        outtextxy(546, 124, PName[PLAYER2]);
        outtextxy(501, 154, PName[PLAYER3]);
        outtextxy(546, 184, PName[PLAYER4]);
    }
    if (Whose_Turn == PLAYER2) {
        outtextxy(546, 124, PName[PLAYER2]);
        setcolor(LIGHTGRAY);
        outtextxy(501,  94, PName[PLAYER1]);
        outtextxy(501, 154, PName[PLAYER3]);
        outtextxy(546, 184, PName[PLAYER4]);
    }
    if (Whose_Turn == PLAYER3) {
        outtextxy(501, 154, PName[PLAYER3]);
        setcolor(LIGHTGRAY);
        outtextxy(501,  94, PName[PLAYER1]);
        outtextxy(546, 124, PName[PLAYER2]);
        outtextxy(546, 184, PName[PLAYER4]);
    }
    if (Whose_Turn == PLAYER4) {
        outtextxy(546, 184, PName[PLAYER4]);
        setcolor(LIGHTGRAY);
        outtextxy(501,  94, PName[PLAYER1]);
        outtextxy(546, 124, PName[PLAYER2]);
        outtextxy(501, 154, PName[PLAYER3]);
    }
}

int Are_You_Sure()
{
    void *buffer;
    unsigned size, pRow, pCol, buttonVal;
    int with_Null, ret_Val = 0, exiting = FALSE;

    if (Mouse) MouRemovePtr();
    size = imagesize(175, 150, 305, 205);
    buffer = malloc(size);
    getimage(175, 150, 305, 205, buffer);
    Draw_Button(176, 151, 299, 199, "Are you sure?", 159, 1, DARKGRAY, RED, WHITE);
    Draw_Button(187, 176, 232, 191, "Yes", 180, 0, DARKGRAY, LIGHTGRAY, RED);
    Draw_Button(242, 176, 287, 191, "No", 180, 0, DARKGRAY, LIGHTGRAY, RED);
    if (Mouse) MouDrawPtr();
    while (!exiting) {
        if (Mouse) MouCharIn(&pRow, &pCol, &buttonVal);
        if (kbhit()) {
            inpCh = getch();
            if (inpCh == 0)
                with_Null = getch();
            else
                with_Null = 0;
            switch (with_Null) {
                case 'G' : pRow-- ; pCol--;  break;
                case 'H' : pRow-=5;          break;
                case 'I' : pRow-- ; pCol++;  break;
                case 'K' :          pCol-=5; break;
                case 'M' :          pCol+=5; break;
                case 'O' : pRow++ ; pCol--;  break;
                case 'P' : pRow+=5;          break;
                case 'Q' : pRow++ ; pCol++;  break;
            }
            switch (inpCh) {
                case 'y' :
                case 'Y' : ret_Val = 1; exiting = TRUE; inpCh = 0; break;
                case 'n' :
                case 'N' : ret_Val = 0; exiting = TRUE; inpCh = 0; break;
            }
            if (Mouse) MouSetPtrPos(pRow, pCol);
        }
        else
            inpCh = 0;
        if (LeftMouButton(buttonVal) || inpCh == 13) {
            if (Verify_Range(187, 176, 232, 191, pCol, pRow)) {
                Push_Sure_Button(1);
                ret_Val = 1;
                exiting = TRUE;
            }                
            if (Verify_Range(242, 176, 287, 191, pCol, pRow)) {
                Push_Sure_Button(2);
                ret_Val = 0;
                exiting = TRUE;
            }
        }
    }
    if (Mouse) MouRemovePtr();
    putimage(175, 150, buffer, COPY_PUT);
    free(buffer);
    if (Mouse) MouDrawPtr();
    return ret_Val;
}

void Push_Sure_Button(int which_One)
{
    if (which_One == 1) {
        if (Mouse) MouRemovePtr();
        Draw_Pressed(187, 176, 232, 191, DARKGRAY, LIGHTGRAY);
        Wait_For_Input();
        Draw_Release(187, 176, 232, 191, DARKGRAY, LIGHTGRAY);
        if (Mouse) MouDrawPtr();
    }
    if (which_One == 2) {
        if (Mouse) MouRemovePtr();
        Draw_Pressed(242, 176, 287, 191, DARKGRAY, LIGHTGRAY);
        Wait_For_Input();
        Draw_Release(242, 176, 287, 191, DARKGRAY, LIGHTGRAY);
        if (Mouse) MouDrawPtr();
    }
}


/*
  -- [Draw_Button] --------------------------------------------


  -------------------------------------------------------------
*/

void Draw_Button(tCol, tRow, bCol, bRow, text, tPos, border, sColor, wColor, tColor)
int tCol;         /*  Column position for top left corner */
int tRow;         /*  Row position for top left corner */
int bCol;         /*  Column position for bottom right corner */
int bRow;         /*  Row position for bottom right corner */
char *text;       /*  Any text to be printed on the button */
int tPos;         /*  How far from top of button to print text */
int border;       /*  Draw shadow inside or outside */
int sColor;       /*  Button Shadow Color */
int wColor;       /*  Window Color */
int tColor;       /*  Text Color */
{
    int width;

    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setfillstyle(SOLID_FILL, wColor);
    setcolor(wColor);
    rectangle(tCol, tRow, bCol, bRow);
    floodfill(tCol + 2, tRow + 2, wColor);
    if (border == 0) 
        Draw_Release(tCol, tRow, bCol, bRow, sColor, wColor);
    else {
        Draw_Shadow(tCol, tRow, bCol, bRow, sColor);
        putpixel(bCol + 1, bRow + 1, sColor);
    }
    setcolor(tColor);
    width = textwidth(text);
    outtextxy(tCol + ((bCol - tCol - width) / 2), tPos, text);
}

void Draw_Pressed(int tCol, int tRow, int bCol, int bRow, int bColor, int wColor)
{
    void *buffer;
    unsigned size;

    size = imagesize(tCol + 2, tRow + 2, bCol - 2, bRow - 2);
    buffer = malloc(size);
    getimage(tCol + 2, tRow + 2, bCol - 2, bRow - 2, buffer);
    putimage(tCol + 4, tRow + 3, buffer, COPY_PUT);

    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setcolor(wColor==LIGHTGRAY ? LIGHTGRAY : bColor);
    line(tCol, bRow, tCol, tRow);     /*  Draw: º            ³   */
    line(tCol, tRow, bCol, tRow);     /*  Draw: ÉÍÍÍÍÍÍÍÍÍÍÍÍ¸   */
    setcolor(wColor);
    line(tCol, bRow, bCol, bRow);     /*  Draw: ÔÍÍÍÍÍÍÍÍÍÍÍÍ¼   */
    line(bCol, bRow, bCol, tRow);     /*  Draw: ³            º   */

    free(buffer);
}

void Draw_Release(int tCol, int tRow, int bCol, int bRow, int bColor, int wColor)
{
    void *buffer;
    unsigned size;

    size = imagesize(tCol + 4, tRow + 3, bCol - 2, bRow - 2);
    buffer = malloc(size);
    getimage(tCol + 4, tRow + 3, bCol - 2, bRow - 2, buffer);
    putimage(tCol + 2, tRow + 2, buffer, COPY_PUT);

    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setcolor(wColor==LIGHTGRAY ? WHITE : wColor);
    line(tCol, bRow, tCol, tRow);     /*  Draw: º            ³  */
    line(tCol, tRow, bCol, tRow);     /*  Draw: ÉÍÍÍÍÍÍÍÍÍÍÍÍ¸  */
    setcolor(bColor);
    line(tCol, bRow, bCol, bRow);     /*  Draw: ÔÍÍÍÍÍÍÍÍÍÍÍÍ¼  */
    /*  put dot in to make demarkation line straight  */
    putpixel(tCol, bRow - 1, wColor==LIGHTGRAY ? WHITE : wColor);
    line(bCol, bRow, bCol, tRow);     /*  Draw: ³            º  */
    putpixel(bCol - 1, tRow, wColor==LIGHTGRAY ? WHITE : wColor);

    free(buffer);
}

void Draw_Shadow(int tCol, int tRow, int bCol, int bRow, int bColor)
{
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setcolor(bColor);
    line(tCol + 3, bRow + 3, bCol + 3, bRow + 3);
    line(bCol + 3, bRow + 3, bCol + 3, tRow + 3);
}

int Verify_Range(int tCol, int tRow, int bCol, int bRow, int pCol, int pRow)
{
    if ( pCol >= tCol && pCol <= bCol && pRow >= tRow && pRow <= bRow )
        return 1;
    return 0;
}

void Wait_For_Input()
{
    unsigned pRow, pCol, buttonVal;

    if (Mouse) {
        MouDrawPtr();
        if (inpCh == 0) {
            MouCharIn(&pRow, &pCol, &buttonVal);
            while (LeftMouButton(buttonVal)) MouCharIn(&pRow, &pCol, &buttonVal);
        }
        MouRemovePtr();
    }
}

void ReSize_Board()
{
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setcolor(MAGENTA);
    rectangle(20, 20, (Matrix_Size - 1) * 30 + 39, (Matrix_Size - 1) * 21 + 37);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
}

void Print_Coordinates(int row, int col)
{
    char temp[10];
    void *buffer;
    unsigned size;

    setcolor(WHITE);
    size = imagesize(535, 193, 587, 199);
    buffer = malloc(size);
    getimage(535, 193, 587, 199, buffer);
    putimage(525, BoardHeight - 20, buffer, COPY_PUT);
    free(buffer);
    itoa(col, temp, 10);
    outtextxy(525, BoardHeight - 20, temp);
    itoa(row, temp, 10);
    outtextxy(555, BoardHeight - 20, temp);
}

void Get_New_Matrix()
{
    unsigned size, pRow, pCol, buttonVal;
    void *buffer, *charBuf;
    int exiting = FALSE, with_Null = 0;

    if (Mouse) MouRemovePtr();
    size = imagesize(165, 150, 313, 204);
    buffer = malloc(size);
    getimage(165, 150, 313, 204, buffer);
    Draw_Button(166, 151, 309, 199, "Number of Boxes?", 159, 1, DARKGRAY, MAGENTA, WHITE);
    Draw_Button(177, 176, 212, 191, "+", 180, 0, DARKGRAY, LIGHTGRAY, RED);
    Draw_Button(263, 176, 298, 191, "-", 180, 0, DARKGRAY, LIGHTGRAY, RED);
    size = imagesize(230, 178, 244, 188);
    charBuf = malloc(size);
    getimage(230, 178, 244, 188, charBuf);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 0);
    Print_Matrix();
    if (Mouse) MouDrawPtr();
    while (!exiting) {
        MouCharIn(&pRow, &pCol, &buttonVal);
        if (kbhit()) {
            inpCh = getch();
            if (inpCh == 0)
                with_Null = getch();
            else
                with_Null = 0;
            switch (with_Null) {
                case 'G' : pRow-- ; pCol--;  break;
                case 'H' : pRow-=5;          break;
                case 'I' : pRow-- ; pCol++;  break;
                case 'K' :          pCol-=5; break;
                case 'M' :          pCol+=5; break;
                case 'O' : pRow++;  pCol--;  break;
                case 'P' : pRow+=5;          break;
                case 'Q' : pRow++;  pCol++;  break;
            }
            switch (inpCh) {
                case 13  : with_Null = 13; inpCh = 13; break;
                case '-' : 
                    Press_Matrix_Button(MINUS);
                    Matrix_Size--;
                    inpCh = 13;
                    break;

                case '+' : 
                    Press_Matrix_Button(PLUS);
                    Matrix_Size++;
                    inpCh = 13;
                    break;
            }
            if (Mouse) MouSetPtrPos(pRow, pCol);
        }
        else
            inpCh = 0;
        if (LeftMouButton(buttonVal) || inpCh == 13) {
            if (Verify_Range(177, 176, 212, 191, pCol, pRow)) {
                Press_Matrix_Button(PLUS);
                Matrix_Size++;
            }
            if (Verify_Range(263, 176, 298, 191, pCol, pRow)) {
                Press_Matrix_Button(MINUS);
                Matrix_Size--;
            }
            if (Verify_Range(230, 178, 244, 188, pCol, pRow) || with_Null == 13) {
                exiting = TRUE;
            }
            if (Matrix_Size > 15) Matrix_Size = 15;
            if (Matrix_Size <  2) Matrix_Size =  2;
            putimage(230, 178, charBuf, COPY_PUT);
            Print_Matrix();
        }
    }
    if (Mouse) MouRemovePtr();
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 0);
    putimage(165, 150, buffer, COPY_PUT);
    free(buffer);
    free(charBuf);
    if (Mouse) MouDrawPtr();
}

/*
  -- [Press_Matrix_Button]-------------------------------------

  Input: Button to Press, PLUS or MINUS
  Returns: None
  Called From: Get_New_Matrix()
  Description: Displays the pressed button until the mouse button
    is released.  If no mouse, then it has no effect, it's released
    anyway.
  Pseudocode:
  
  -------------------------------------------------------------
*/

void Press_Matrix_Button(int which_One)
{
    if (Mouse) MouRemovePtr();
    if (which_One == 1) {
        Draw_Pressed(177, 176, 212, 191, DARKGRAY, LIGHTGRAY);
        Wait_For_Input();
        Draw_Release(177, 176, 212, 191, DARKGRAY, LIGHTGRAY);
    }
    if (which_One == 2) {
        Draw_Pressed(263, 176, 298, 191, DARKGRAY, LIGHTGRAY);
        Wait_For_Input();
        Draw_Release(263, 176, 298, 191, DARKGRAY, LIGHTGRAY);
    }
    if (Mouse) MouDrawPtr();
}


/*
  -- [Print_Matrix] -------------------------------------------

  Input: None
  Returns: None
  Called From: Get_New_Matrix()
  Description: Clears and prints a new number for the number of
    squares for a new game matrix.
  Pseudocode:
    if there is a mouse, turn mouse cursor off
    make text magenta
    clear text space
    make text yellow
    make sure text is correct size
    convert matrix size to a string
    print char to window
    put character size back to normal
    if there is a mouse, turn mouse cursor on
  
  -------------------------------------------------------------
*/

void Print_Matrix(void)
{
    char temp[10];
    int j;

    if (Mouse) MouRemovePtr();
    setcolor(MAGENTA);
    for (j = 181; j < 190; j++) line(230, j, 248, j);
    setcolor(YELLOW);
    setusercharsize(1, 2, 1, 2);
    itoa(Matrix_Size, temp, 10);
    outtextxy(230, 174, temp);
    setusercharsize(1, 1, 1, 1);
    if (Mouse) MouDrawPtr();
}

void Print_Message(char *Message)
{
    void *buffer;
    unsigned size;
    int lenMsg, startWindow;

    if (Mouse) MouRemovePtr();
    lenMsg = textwidth(Message);
    startWindow = (469 - lenMsg) / 2;
    size = imagesize(startWindow, 150, startWindow + lenMsg + 15, 173);
    buffer = malloc(size);
    getimage(startWindow, 150, startWindow + lenMsg + 15, 173, buffer);
    Draw_Button(startWindow + 1, 150 + 1, startWindow + lenMsg + 11, 169, Message, 157, 1, DARKGRAY, BLUE, WHITE);
    Wait_For_It();
    putimage(startWindow, 150, buffer, COPY_PUT);
    free(buffer);
    if (Mouse) MouDrawPtr();
}

/* normally 329 high by 459 wide with a 10x10 starting position */

void Get_Partner(void)
{
    void *buffer;
    unsigned size, pRow, pCol, buttonVal;
    int with_Null, ret_Val = 0, exiting = FALSE;

    if (Mouse) MouRemovePtr();
    size = imagesize(115, 126, 365, 226);
    buffer = malloc(size);
    getimage(115, 126, 365, 226, buffer);
    Draw_Button(116, 127, 361, 222, "Select your Partners", 135, 1, DARKGRAY, MAGENTA, WHITE);
    Draw_Button(150, 203, 215, 218, "Accept", 207, 0, DARKGRAY, LIGHTGRAY, RED);
    Draw_Button(262, 203, 327, 218, "Cancel", 207, 0, DARKGRAY, LIGHTGRAY, RED);
    if (Mouse) MouDrawPtr();
    while (!exiting) {
        if (Mouse) MouCharIn(&pRow, &pCol, &buttonVal);
        if (kbhit()) {
            inpCh = getch();
            if (inpCh == 0)
                with_Null = getch();
            else
                with_Null = 0;
            switch (with_Null) {
                case 'G' : pRow-- ; pCol--;  break;
                case 'H' : pRow-=5;          break;
                case 'I' : pRow-- ; pCol++;  break;
                case 'K' :          pCol-=5; break;
                case 'M' :          pCol+=5; break;
                case 'O' : pRow++ ; pCol--;  break;
                case 'P' : pRow+=5;          break;
                case 'Q' : pRow++ ; pCol++;  break;
            }
            switch (inpCh) {
                case 'a' :
                case 'A' : ret_Val = 1; exiting = TRUE; inpCh = 0; break;
                case 'c' :
                case 'C' : ret_Val = 0; exiting = TRUE; inpCh = 0; break;
            }
            if (Mouse) MouSetPtrPos(pRow, pCol);
        }
        else
            inpCh = 0;
        if (LeftMouButton(buttonVal) || inpCh == 13) {
            if (Verify_Range(150, 203, 215, 218, pCol, pRow)) {
                if (Mouse) MouRemovePtr();
                Draw_Pressed(150, 203, 215, 218, DARKGRAY, LIGHTGRAY);
                Wait_For_Input();
                Draw_Release(150, 203, 215, 218, DARKGRAY, LIGHTGRAY);
                if (Mouse) MouDrawPtr();
                ret_Val = 1;
                exiting = TRUE;
            }
            if (Verify_Range(262, 203, 327, 218, pCol, pRow)) {
                if (Mouse) MouRemovePtr();
                Draw_Pressed(262, 203, 327, 218, DARKGRAY, LIGHTGRAY);
                Wait_For_Input();
                Draw_Release(262, 203, 327, 218, DARKGRAY, LIGHTGRAY);
                if (Mouse) MouDrawPtr();
                ret_Val = 0;
                exiting = TRUE;
            }
        }
    }
    if (Mouse) MouRemovePtr();
    putimage(115, 126, buffer, COPY_PUT);
    free(buffer);
    if (Mouse) MouDrawPtr();
}

