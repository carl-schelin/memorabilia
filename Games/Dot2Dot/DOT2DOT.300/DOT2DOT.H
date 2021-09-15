/* []---------------------------------------------------------------------[] */
/* |       Dot2Dot.h: Main calling routine and initialization code.        | */
/* |                                                                       | */
/* |              The Dot2Dot.h source code and concepts are               | */
/* |     Copyright (C) 1986-1993 by Carl Schelin, All Rights Reserved.     | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define TRUE             1
#define FALSE            0

#define PLUS             1
#define MINUS            2

#define TRANSFER         0
#define ARROW            1
#define WAIT             2
#define HOURGLASS        3

#define PLAYER1          YELLOW
#define PLAYER2          BLUE
#define PLAYER3          MAGENTA
#define PLAYER4          RED

#define VERT TRUE
#define HORZ FALSE

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
    int color;
    int score;
    int playing;
    int remote;
    char colname;
    int col;
    int row;
};

#ifdef __BUTTON__
void Press_Button(int which_One);
void Draw_Button(int tCol, int tRow, int bCol, int bRow, char *text, int tPos, int border, int sColor, int wColor, int tColor);
void Draw_Pressed(int tCol, int tRow, int bCol, int bRow, int bColor, int wColor);
void Draw_Release(int tCol, int tRow, int bCol, int bRow, int bColor, int wColor);
void Draw_Shadow(int tCol, int tRow, int bCol, int bRow, int bColor);
#else
extern void Press_Button(int which_One);
extern void Draw_Button(int tCol, int tRow, int bCol, int bRow, char *text, int tPos, int border, int sColor, int wColor, int tColor);
extern void Draw_Pressed(int tCol, int tRow, int bCol, int bRow, int bColor, int wColor);
extern void Draw_Release(int tCol, int tRow, int bCol, int bRow, int bColor, int wColor);
extern void Draw_Shadow(int tCol, int tRow, int bCol, int bRow, int bColor);
#endif

#ifdef __MAIN__
struct _Plr Player[6];
char GameMoves[600][10];
int Mouse = TRUE;
int Replay = FALSE;
int Network = FALSE;
int Server = FALSE;
int Client = FALSE;
int SaveIndex = 0;
int BoardWidth = 0;
int BoardHeight = 0;
int NetCheck = 0;
int GameOver = FALSE;
int inpCh = 0;
int BrdWid;
int BrdDep;
int ConWid;
int ConDep;
int BrdBCol;
int BrdBRow;
int BrdECol;
int BrdERow;
int ConBCol;
int ConBRow;
int ConECol;
int ConERow;
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
#else
extern struct _Plr Player[6];
extern char GameMoves[600][10];
extern int Mouse;
extern int Replay;
extern int Network;
extern int Server;
extern int Client;
extern int SaveIndex;
extern int BoardWidth;
extern int BoardHeight;
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
#endif

#ifdef __DRAWBOX__
void DrawBox(int col, int row);
void DrawTexture(int col, int row, int color1, int color2);
void FillBox(int col, int row, int color);
void DrawPost(int col, int row);
void DrawHorz(int col, int row);
void DrawVert(int col, int row);
#else
extern void DrawBox(int col, int row);
extern void DrawTexture(int col, int row, int color1, int color2);
extern void FillBox(int col, int row, int color);
extern void DrawPost(int col, int row);
extern void DrawHorz(int col, int row);
extern void DrawVert(int col, int row);
#endif

#ifdef __CONSOLE__
void Check_Console(int col, int row);
#else
extern void Check_Console(int col, int row);
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

#ifdef __DESKTOP__
void Desktop(void);
void DrawBoard(void);
void DrawMatrix(void);
void DrawConsole(void);
void DrawLogo(void);
void DrawButtons(void);
void ResizeBoard(void);
void DrawBorder(int scol, int srow, int ecol, int erow, int color1, int color2);
void DrawNetwork(void);
void DrawPlayers(int col, int row, int color);
void CheckNetwork(int toggle);
void CheckServer(int toggle);
void CheckClient(int toggle);
void EditClient(int toggle);
void CheckBox(int col, int row, int toggle);
void Lightning(int col, int row);
#else
extern void Desktop(void);
extern void DrawBoard(void);
extern void DrawMatrix(void);
extern void DrawConsole(void);
extern void DrawLogo(void);
extern void DrawButtons(void);
extern void ResizeBoard(void);
extern void DrawBorder(int scol, int srow, int ecol, int erow, int color1, int color2);
extern void DrawNetwork(void);
extern void DrawPlayers(int col, int row, int color);
extern void CheckNetwork(int toggle);
extern void CheckServer(int toggle);
extern void CheckClient(int toggle);
extern void EditClient(int toggle);
extern void CheckBox(int col, int row, int toggle);
extern void Lightning(int col, int row);
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
#else
extern void Print_Message(char *Message);
extern void Next_Player(void);
extern void Draw_Name(int player, int toggle, int shadow);
extern void Update_Scores(void);
extern void Wait_For_It(void);
extern void Wait_For_Input(void);
extern void End_Game(void);
extern int Verify_Range(int tCol, int tRow, int bCol, int bRow, int pCol, int pRow);
#endif

#ifdef __QDIALOG__
int Are_You_Sure(void);
void Push_Sure_Button(int which_One);
#else
extern int Are_You_Sure(void);
extern void Push_Sure_Button(int which_One);
#endif

#ifdef __PLAYER__
void Get_Name(int getWho);
#else
extern void Get_Name(int getWho);
#endif

#ifdef __REPLAY__
void Replay_Game(void);
void Save_Game(void);
#else
extern void Replay_Game(void);
extern void Save_Game(void);
#endif

