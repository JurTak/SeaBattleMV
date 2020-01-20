//Test
std::string NTC(double Number,int Dev)
{
	char a[100];
	gcvt(Number,Dev,a);
	return a;
}
std::string NTC(int Number)
{
	char a[100];
	itoa(Number,a,10);
	return a;
}
#define CNTC(x) (char*)NTC(x).c_str()
#define CNTC2(x,y) (char*)NTC(x,y).c_str()

//////////////////////////////////////////////
// Global Variables
HINSTANCE	hInst;
HWND		hWnd,hWnd_Dlg,hWnd_Dlg_D;
int			iGameMenu_Number = 0;
UINT		uiGameMenu_ID;

//Menu
bool		bMainMenu = true;
bool		bShipSelection = false;
BYTE		iGameMode = 0;//0=Single Player , 1=Multiplayer
bool		bInGame = false;
bool		bWaitForClient = false;

//Network LAN
u_short PORT = 0x229E;
SOCKADDR_IN addr;
int addrlen;
SOCKET Server;
SOCKET Client;
SOCKET Connections[256];
std::string ConnectionIP;
typedef struct{char IP[16];bool Run;}FINDSERVERDATA;
FINDSERVERDATA FSDataIP[256];
bool Connecting_ON = false;
char iServerClient = 0;//1=Server , 2=Client
bool iServerConnected = false;
bool iClientConnected = false;
bool P2_inGame;
bool DataSendON = false;
std::string buffer;
UINT buffer_count = 0;

////////////////////////////////////////
//Game variables
char		iSelected_Ship = 0;
char		iShipRemains[4] = {1,2,3,4};
int			iParamA = 0;
int			iParamB = 0;
int			iMemParam = 0;
bool		iParamRotate = true;
char		iMyTurn = 0;
bool		iWinGame;
bool		iEndOfGame_HiheShip = true;

typedef struct
{
	struct SHIP{BYTE x,y,on;bool rotate;};
	SHIP ship1[4],ship2[3],ship3[2],ship4;
	BYTE ActiveTable[10][10];
	BYTE PlacedShipTable[10][10];
	void Null(void)
	{
		memset((char*)ActiveTable,0,sizeof(ActiveTable));
		memset((char*)PlacedShipTable,0,sizeof(PlacedShipTable));
		memset((char*)ship1,0,sizeof(ship1));
		memset((char*)ship2,0,sizeof(ship2));
		memset((char*)ship3,0,sizeof(ship3));
		ship4.x = ship4.y = ship4.on = 0;
		ship4.rotate = 0;
	}
	void ActiveTable_null(void)
	{
		memset((char*)ActiveTable,0,sizeof(ActiveTable));
	}
}PlayerTable;
PlayerTable P_Table[3];

//AI
typedef struct
{
	struct BOX{char x[3],y[3],on[3];};
	int x[2],y[2];
	BOX pos[4];//0=left , 1=right , 2=up , 3=down
	BYTE ship1_on[4],ship2_on[3],ship3_on[2],ship4_on;
	char hv;//1=horizontal , 2=vertical
	BYTE ActiveTable[10][10];
	bool FirstHitting;
	bool SmartTable;
	char big_ship,big_ship4destroyed,big_ship3destroyed;
	char difficulty;//0=Hard , 1=Medium , 2=Easy , 3=VeryEasy
}AIGLOBALVAR;
AIGLOBALVAR AI_var;

//////////////////////////////////////////////////
#define GM_MAINMENU_MAX 4
#define GM_MAINMENU_ID 3000

#define GM_MULTIPLAYER_MAX 3
#define GM_MULTIPLAYER_ID 3100

#define GM_SINGLEPLAYER_MAX 4
#define GM_SINGLEPLAYER_ID 3200

#define GM_JOIN_ID 3300

#define GM_EXIT_ID 3400

#define GM_PLAYAGAIN_ID 3500
