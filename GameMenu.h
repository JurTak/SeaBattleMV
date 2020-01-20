void DialogSizeByWindow(HWND Window, HWND Dialog)
{
	RECT rc;GetClientRect(Window,&rc);
	SetWindowPos(Dialog,NULL,0,0,rc.right,rc.bottom,0);
}

void GameMenu_MainMenu_Pos(bool fixed_position, int X, int Y)
{
	if(iGameMenu_Number > 0)
	{
		RECT r;
		GetClientRect(hWnd_Dlg,&r);
		int n = iGameMenu_Number;
		UINT ID = uiGameMenu_ID;
		
		for(int i = 0,x,y; i < n; i++)
		{
			if(fixed_position)
			{
				x = X;
				y = Y;
			}
			else
			{
				x = (r.right-200)/2;
				y = r.bottom >= 360 ? (r.bottom-30)/2 : (360-30)/2;
			}
			
			SetWindowPos(GetDlgItem(hWnd_Dlg,ID+i),NULL,x,y - 40*i + 20*(n-1),0,0,SWP_NOSIZE);
		}
	}
}

void GameMenu_CreateMainMenu(UINT ID, int n, const char * A)
{
	HFONT My_Font = CreateFont(20,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_SWISS,"Arial");
	for(int i = 0,k = 0; i < n; i++)
	{
		SendMessage(
			CreateWindowExA(0,"BUTTON",A+k,WS_CHILD|WS_TABSTOP,0,0,200,30,hWnd_Dlg,(HMENU)(ID+i),hInst,0)
				,WM_SETFONT,(WPARAM)My_Font,0);
		k += strlen(A+k)+1;
	}
}

void GameMenu_Hide(UINT ID, int n_number)
{
	iGameMenu_Number = 0;
	for(int i = 0; i < n_number; i++) {ShowWindow(GetDlgItem(hWnd_Dlg,ID+i),false);}
}

void GameMenu_Show(UINT ID, int n_number)
{
	uiGameMenu_ID = ID;
	iGameMenu_Number = n_number;
	for(int i = 0; i < n_number; i++) {ShowWindow(GetDlgItem(hWnd_Dlg,ID+i),true);}
}

UINT GetMenuButtonID(UINT ID,UINT max,const char * button_name)
{
	HWND W;
	std::string s;
	for(int i = 0,L; i < max; i++)
	{
		W = GetDlgItem(hWnd_Dlg,ID+i);
		L = GetWindowTextLength(W)+1;
		s.resize(L);
		GetWindowText(W,(char*)s.c_str(),L);
		if(!stricmp(button_name,(char*)s.c_str()))
		{
			ID = ID+i;
			break;
		}
		else{s = "";}
	}
	return ID;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Select Menu
void SelectMenu_SinglePlayer(HWND W)
{
	iEndOfGame_HiheShip = true;
	iMyTurn = iGameMode = 0;
	EnableWindow(GetDlgItem(W,GetMenuButtonID(GM_SINGLEPLAYER_ID,GM_SINGLEPLAYER_MAX,"Start Game")),false);//Disable Start Button
	bMainMenu = false;
	GameMenu_Hide(GM_EXIT_ID,2);
	GameMenu_Hide(GM_MAINMENU_ID,GM_MAINMENU_MAX);
	GameMenu_Show(GM_SINGLEPLAYER_ID,GM_SINGLEPLAYER_MAX);
	GameMenu_MainMenu_Pos(true,650,415);
	bShipSelection = true;
	P_Table[0].Null(); P_Table[1].Null();
	iSelected_Ship = iMemParam = 0;
	iParamRotate = true;
	for(int i = 0; i < 4; i++){iShipRemains[i] = i+1;}
	bInGame = false;
	ShowWindow(hWnd_Dlg_D,true);//AI Difficulty
	InvalidateRect(W,0,true);//Refresh
}
void SelectMenu_SinglePlayer_Back(HWND W)
{
	ShowWindow(hWnd_Dlg_D,false);//AI Difficulty
	GameMenu_Hide(GM_SINGLEPLAYER_ID,GM_SINGLEPLAYER_MAX);
	GameMenu_Show(GM_MAINMENU_ID,GM_MAINMENU_MAX);
	bMainMenu = true;
	bShipSelection = false;
	GameMenu_MainMenu_Pos(false,0,0);
	bInGame = false;
	InvalidateRect(W,0,true);//Refresh
}
void SelectMenu_SinglePlayer_Reset(HWND W)
{
	EnableWindow(GetDlgItem(W,GetMenuButtonID(GM_SINGLEPLAYER_ID,GM_SINGLEPLAYER_MAX,"Start Game")),false);//Disable Start Button
	iSelected_Ship = iMemParam = 0;
	iParamRotate = true;
	for(int i = 0; i < 4; i++){iShipRemains[i] = i+1;}
	P_Table[0].Null(); P_Table[1].Null();
	InvalidateRect(W,0,true);//Refresh
}
void SelectMenu_SinglePlayer_Random(HWND W)
{
	if(iShipRemains[0] == 0 && iShipRemains[1] == 0 && iShipRemains[2] == 0 && iShipRemains[3] == 0)
	{
		for(int i = 0; i < 4; i++){iShipRemains[i] = i+1;}
		P_Table[0].Null();
	}
	GSM_RandomShip(0);
	while(iShipRemains[0] != 0 || iShipRemains[1] != 0 || iShipRemains[2] != 0 || iShipRemains[3] != 0)
	{
		for(int i = 0; i < 4; i++){iShipRemains[i] = i+1;}
		P_Table[0].Null();
		GSM_RandomShip(0);
	}
	
	if(!bInGame)
	{
		//Redraw
		int X = 200,Y = 100;
		RECT r;
		r.left = X+1+500-40; r.right = X+1+500;
		r.top = Y+1+15; r.bottom = Y+1+15+40*4;
		InvalidateRect(hWnd_Dlg,&r,true);//Refresh

		RedrawTable(hWnd_Dlg,X,Y,10,10);

		//Enable start
		if(iShipRemains[0] == 0 && iShipRemains[1] == 0 && iShipRemains[2] == 0 && iShipRemains[3] == 0)
		{
			EnableWindow(GetDlgItem(hWnd_Dlg,GetMenuButtonID(GM_SINGLEPLAYER_ID,GM_SINGLEPLAYER_MAX,"Start Game")),true);
		}
	}
}
void SelectMenu_SinglePlayer_StartGame(HWND W)
{
	ShowWindow(hWnd_Dlg_D,false);//AI Difficulty
	iEndOfGame_HiheShip = true;
	P_Table[1] = P_Table[0];
	for(int i = 0; i < 4; i++){iShipRemains[i] = i+1;}
	P_Table[0].Null();
	GSM_RandomShip(0);
	while(iShipRemains[0] != 0 || iShipRemains[1] != 0 || iShipRemains[2] != 0 || iShipRemains[3] != 0)
	{
		for(int i = 0; i < 4; i++){iShipRemains[i] = i+1;}
		P_Table[0].Null();
		GSM_RandomShip(0);
	}
	
	GSM_Generate_PlacedShipTable(0);
	GSM_Generate_PlacedShipTable(1);
	P_Table[0].ActiveTable_null();
	P_Table[1].ActiveTable_null();
	
	AI_Start();
	
	iMyTurn = 1;
	
	bInGame = true;
	bShipSelection = false;
	iSelected_Ship = 0;
	GameMenu_Hide(GM_SINGLEPLAYER_ID,GM_SINGLEPLAYER_MAX);
	GameMenu_Show(GM_EXIT_ID,1);
	GameMenu_MainMenu_Pos(true,750,520);
	InvalidateRect(W,0,true);//Refresh
}

void SelectMenu_Multiplayer_StartGame(HWND W)
{
	iEndOfGame_HiheShip = true;
	if(iServerClient == 2)//Client
	{
		if(!LAN_SendDataToServer(1,0,0))
		{
			return;
		}
	}
	P_Table[1] = P_Table[0];
	P_Table[0].Null();
	GSM_Generate_PlacedShipTable(1);
	P_Table[1].ActiveTable_null();
	iMyTurn = 3;
	bInGame = true;
	bShipSelection = false;
	iSelected_Ship = 0;
	GameMenu_Hide(GM_SINGLEPLAYER_ID,GM_SINGLEPLAYER_MAX);
	GameMenu_Show(GM_EXIT_ID,1);
	GameMenu_MainMenu_Pos(true,750,520);
	InvalidateRect(W,0,true);//Refresh
	
	if(iServerClient == 1)//Server
	{
		SetTimer(hWnd,103,10,0);
	}
}

void SelectMenu_Multiplayer_ExitGame()
{
	bShipSelection = false;
	iSelected_Ship = 0;
	iGameMode = 0;
	iServerClient = 0;
	bWaitForClient = iClientConnected = iServerConnected = false;
	GameMenu_Hide(GM_SINGLEPLAYER_ID,GM_SINGLEPLAYER_MAX);
	GameMenu_Hide(GM_EXIT_ID,2);
	SelectMenu_SinglePlayer_Back(hWnd_Dlg);
}

void SelectMenu_SinglePlayer_ExitGame(HWND W)
{
	GameMenu_Hide(GM_EXIT_ID,2);
	SelectMenu_SinglePlayer_Back(W);
}