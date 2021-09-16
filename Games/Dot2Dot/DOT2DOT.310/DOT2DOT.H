/* []---------------------------------------------------------------------[] */
/* |       Dot2Dot.h: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |              The Dot2Dot.h source code and concepts are               | */
/* |     Copyright (C) 1986-1996 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#ifndef TRUE
#define FALSE            0
#define TRUE             !FALSE
#endif

#define PLUS             1
#define MINUS            2

#define TRANSFER         0
#define ARROW            1
#define WAIT             2
#define HOURGLASS        3

#define BLACK         0
#define BLUE          1
#define GREEN         2
#define CYAN          3
#define RED           4
#define MAGENTA       5
#define BROWN         6
#define WHITE         7
#define GRAY          8
#define LIGHTBLUE     9
#define LIGHTGREEN   10
#define LIGHTCYAN    11
#define LIGHTRED     12
#define LIGHTMAGENTA 13
#define YELLOW       14
#define BRIGHTWHITE  15

#define VERT TRUE
#define HORZ FALSE

#define BUTTON     FALSE
#define BACKGROUND TRUE

#define Key_S_A 0x41
#define Key_S_B 0x42
#define Key_S_C 0x43
#define Key_S_D 0x44
#define Key_S_E 0x45
#define Key_S_F 0x46
#define Key_S_G 0x47
#define Key_S_H 0x48
#define Key_S_I 0x49
#define Key_S_J 0x4A
#define Key_S_K 0x4B
#define Key_S_L 0x4C
#define Key_S_M 0x4D
#define Key_S_N 0x4E
#define Key_S_O 0x4F
#define Key_S_P 0x50
#define Key_S_Q 0x51
#define Key_S_R 0x52
#define Key_S_S 0x53
#define Key_S_T 0x54
#define Key_S_U 0x55
#define Key_S_V 0x56
#define Key_S_W 0x57
#define Key_S_X 0x58
#define Key_S_Y 0x59
#define Key_S_Z 0x5A

#define Key_A 0x61
#define Key_B 0x62
#define Key_C 0x63
#define Key_D 0x64
#define Key_E 0x65
#define Key_F 0x66
#define Key_G 0x67
#define Key_H 0x68
#define Key_I 0x69
#define Key_J 0x6A
#define Key_K 0x6B
#define Key_L 0x6C
#define Key_M 0x6D
#define Key_N 0x6E
#define Key_O 0x6F
#define Key_P 0x70
#define Key_Q 0x71
#define Key_R 0x72
#define Key_S 0x73
#define Key_T 0x74
#define Key_U 0x75
#define Key_V 0x76
#define Key_W 0x77
#define Key_X 0x78
#define Key_Y 0x79
#define Key_Z 0x7A

#define FAILURE FALSE

struct _Plr {
    char name[15];
    short color;
    long background;
    int score;
    int playing;
    int remote;
    char colname;
    int col;
    int row;
};

#ifdef __BUTTON__
void Press_Button(int which_One);
void Draw_Button(int tCol, int tRow, int bCol, int bRow, char *text, int tPos, int border, short sColor, short wColor, short tColor);
void Draw_Pressed(int tCol, int tRow, int bCol, int bRow, short bColor, short wColor);
void Draw_Release(int tCol, int tRow, int bCol, int bRow, short bColor, short wColor);
void Draw_Shadow(int tCol, int tRow, int bCol, int bRow, short bColor);
#else
extern void Press_Button(int which_One);
extern void Draw_Button(int tCol, int tRow, int bCol, int bRow, char *text, int tPos, int border, short sColor, short wColor, short tColor);
extern void Draw_Pressed(int tCol, int tRow, int bCol, int bRow, short bColor, short wColor);
extern void Draw_Release(int tCol, int tRow, int bCol, int bRow, short bColor, short wColor);
extern void Draw_Shadow(int tCol, int tRow, int bCol, int bRow, short bColor);
#endif

#ifdef __CONSOLE__
void Check_Console(int col, int row);
#else
extern void Check_Console(int col, int row);
#endif

#ifdef __DESKTOP__
void Desktop(void);
void DrawBoard(void);
void DrawMatrix(void);
void DrawConsole(void);
void DrawLogo(void);
void DrawButtons(void);
void DrawBorder(int scol, int srow, int ecol, int erow, short color1, short color2);
void DrawNetwork(void);
void DrawPlayers(int col, int row, short color);
void CheckNetwork(int toggle);
void CheckServer(int toggle);
void CheckClient(int toggle);
void EditClient(int toggle);
void CheckBox(int col, int row, int toggle);
void DrawBox(int bcol, int brow, int ecol, int erow, int fcolor, int bcolor);
void Lightning(int col, int row);
#else
extern void Desktop(void);
extern void DrawBoard(void);
extern void DrawMatrix(void);
extern void DrawConsole(void);
extern void DrawLogo(void);
extern void DrawButtons(void);
extern void DrawBorder(int scol, int srow, int ecol, int erow, short color1, short color2);
extern void DrawNetwork(void);
extern void DrawPlayers(int col, int row, short color);
extern void CheckNetwork(int toggle);
extern void CheckServer(int toggle);
extern void CheckClient(int toggle);
extern void EditClient(int toggle);
extern void CheckBox(int col, int row, int toggle);
extern void DrawBox(int bcol, int brow, int ecol, int erow, int fcolor, int bcolor);
extern void Lightning(int col, int row);
#endif

#ifdef __DRAWPIECE__
void DrawPiece(int col, int row);
void DrawTexture(int col, int row, short color1, short color2);
void FillBox(int col, int row, short color);
void DrawPost(int col, int row);
void DrawHorz(int col, int row);
void DrawVert(int col, int row);
#else
extern void DrawPiece(int col, int row);
extern void DrawTexture(int col, int row, short color1, short color2);
extern void FillBox(int col, int row, short color);
extern void DrawPost(int col, int row);
extern void DrawHorz(int col, int row);
extern void DrawVert(int col, int row);
#endif

#ifdef __EDITFLD__
void Edit_Field(int EdtBCol, int EdtBRow, int bcolor, int wcolor, char *hold, int maxlen);
#else
extern void Edit_Field(int EdtBCol, int EdtBRow, int bcolor, int wcolor, char *hold, int maxlen);
#endif

#ifdef __FILLBOX__
void Click_Something(int col, int row);
int Depressed(int col, int row, int toggle);
void CheckFill(int col, int row, int toggle);
void Hot_Finish(void);
#else
extern void Click_Something(int col, int row);
extern int Depressed(int col, int row, int toggle);
extern void CheckFill(int col, int row, int toggle);
extern void Hot_Finish(void);
#endif

#ifdef __INTRO__
void Initialize(void);
void Reset_Data(void);
void Introduction(void);
#else
extern void Initialize(void);
extern void Reset_Data(void);
extern void Introduction(void);
#endif

#ifdef __MAIN__
struct _Plr Player[6];
char *IPAddr = "888.888.888.888";
char GameMoves[600][18];
char *SmallFont = "t'BorlandTE'";
char _huge *bckbuffer;
char _huge *btnbuffer;
char _huge *scrnbuffer;
char _huge *helpbuffer;
char _huge *newscreen;
int Blind = FALSE;
int NetActive = FALSE;
int Mouse = TRUE;
int Replay = FALSE;
int Network = FALSE;
int Server = FALSE;
int Client = FALSE;
int SaveIndex = 0;
int GameWidth = 0;
int GameDepth = 0;
int NetCheck = TRUE;
int GameOver = FALSE;
int inpCh = 0;
int BrdWid;
int BrdDep;
int ConWid;
int ConDep;
unsigned int BrdBCol;
unsigned int BrdBRow;
unsigned int BrdECol;
unsigned int BrdERow;
unsigned int ConBCol;
unsigned int ConBRow;
unsigned int ConECol;
unsigned int ConERow;
int BoxBCol;
int BoxBRow;
int BoxECol;
int BoxERow;
int NetCol;
int NetRow;
unsigned int MouCCol = 0;
unsigned int MouCRow = 0;
unsigned int MouCBtn = 0;
int WhosUp;
int MouLUp = TRUE;
char Dot2Dot[4] = "Dot";
char Author[16] = "by Carl Schelin";
char Netwrk[8] = "Network";
char Clint[8] = "Client";
char Servr[8] = "Server";
int NewPlr = FALSE;
int Help = FALSE;
#else
extern struct _Plr Player[6];
extern char *IPAddr;
extern char GameMoves[600][18];
extern char *SmallFont;
extern char _huge *bckbuffer;
extern char _huge *btnbuffer;
extern char _huge *scrnbuffer;
extern char _huge *helpbuffer;
extern char _huge *newscreen;
extern int Blind;
extern int NetActive;
extern int Mouse;
extern int Replay;
extern int Network;
extern int Server;
extern int Client;
extern int SaveIndex;
extern int GameWidth;
extern int GameDepth;
extern int NetCheck;
extern int GameOver;
extern int inpCh;
extern int BrdWid;
extern int BrdDep;
extern int ConWid;
extern int ConDep;
extern int BrdBCol;
extern int BrdBRow;
extern int BrdECol;
extern int BrdERow;
extern int ConBCol;
extern int ConBRow;
extern int ConECol;
extern int ConERow;
extern int BoxBCol;
extern int BoxBRow;
extern int BoxECol;
extern int BoxERow;
extern int NetCol;
extern int NetRow;
extern unsigned int MouCCol;
extern unsigned int MouCRow;
extern unsigned int MouCBtn;
extern int WhosUp;
extern int MouLUp;
extern char Dot2Dot[4];
extern char Author[16];
extern char Netwrk[8];
extern char Clint[8];
extern char Servr[8];
extern int NewPlr;
int Help;
#endif

#ifdef __NETWORK__
void Gather_Stats(void);
int InitCom(void);
#else
extern void Gather_Stats(void);
extern int InitCom(void);
#endif

#ifdef __PLAYER__
void Get_Name(int getWho);
#else
extern void Get_Name(int getWho);
#endif

#ifdef __QDIALOG__
int Are_You_Sure(void);
void Push_Sure_Button(int which_One);
#else
extern int Are_You_Sure(void);
extern void Push_Sure_Button(int which_One);
#endif

#ifdef __REPLAY__
void Replay_Game(void);
void Save_Game(void);
#else
extern void Replay_Game(void);
extern void Save_Game(void);
#endif

#ifdef __UTILITY__
void Print_Message(char *Message);
void Next_Player(void);
void Draw_Name(int player, int toggle, int shadow);
void Update_Scores(void);
void Wait_For_It(void);
void Wait_For_Input(void);
void End_Game(void);
int Verify_Range(int tCol, int tRow, int bCol, int bRow, int pCol, int pRow);
void SaveBackground(int bcol, int brow, int ecol, int erow, int toggle);
void RestoreBackground(int bcol, int brow, int toggle);
void Display_Help(void);
void Reset(void);
#else
extern void Print_Message(char *Message);
extern void Next_Player(void);
extern void Draw_Name(int player, int toggle, int shadow);
extern void Update_Scores(void);
extern void Wait_For_It(void);
extern void Wait_For_Input(void);
extern void End_Game(void);
extern int Verify_Range(int tCol, int tRow, int bCol, int bRow, int pCol, int pRow);
extern void SaveBackground(int bcol, int brow, int ecol, int erow, int toggle);
extern void RestoreBackground(int bcol, int brow, int toggle);
extern void Display_Help(void);
extern void Reset(void);
#endif

