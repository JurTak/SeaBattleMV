//GameSystemModel.h
void GSM_Table_DeactiveRedraw(int X, int Y, int x, int y, char ship_size,bool Rotate, void (*func)(int,int,int,int));
void GSM_ShipSelection(HWND W, int TablePosX, int TablePosY, LPARAM lParam);
void GSM_TDR_DeactiveTable_P1(int X, int Y, int x, int y);
void GSM_TDR_Redraw(int X, int Y, int x, int y);
void GSM_ShipSelection_Action(int X, int Y, LPARAM lParam);
void GSM_ShipSel_Rotate(HWND W);
void GSM_RandomShip(int Player);
void GSM_Generate_PlacedShipTable(int Player);
void AI_Start();
void AI_SetBox(int x, int y);
bool AI_SetCoordinate_seek(int n, int & x, int & y);
void AI_SetCoordinate(int & x, int & y);
void AI_BegEndHit(int X, int Y, bool & b);
void GSM_TDR_DeactiveTable_AI(int X, int Y, int x, int y);
void AI_ReorientatedTable();
void AI_CheckReorientation();
void AI_ShipShot_Action();
bool GSM_CheckCondition(int Player);
void GSM_ShipShot_Action(int X, int Y);

//Graphics.h
void RedrawTable(HWND W, int x, int y, int sizX, int sizY);
void DrowRect(HDC hDC, int x, int y, int cx, int cy, COLORREF line, unsigned char dot1_solid0, COLORREF bg);
void SelectMenu_DrowBoxTable(HDC hDC, int x, int y);
void SelectMenu_Ship1(HDC hDC, int x, int y, int x_pos, int y_pos);
void SelectMenu_Ship2(HDC hDC, int x, int y, int x_pos, int y_pos, bool rotate);
void SelectMenu_Ship3(HDC hDC, int x, int y, int x_pos, int y_pos, bool rotate);
void SelectMenu_Ship4(HDC hDC, int x, int y, int x_pos, int y_pos, bool rotate);
void SelectMenu_MissedShot(HDC hDC, int x, int y, int x_pos, int y_pos);
void SelectMenu_HitShot(HDC hDC, int x, int y, int x_pos, int y_pos);
void SelectMenu_Table(HDC hDC);
void SelectMenu_ShipSelection_DrowTable(HDC hDC, int X, int Y);
void SelectMenu_InGame_DrowTable(HDC hDC, int X, int Y, const char * table_name, int Player, bool SelectON, bool hide_ship);
void GameMSG(HDC hDC);

//LAN.h
bool recvall(SOCKET & _Connection,char * data,int totalbytes);
bool sendall(SOCKET & _Connection,char * data,int totalbytes);
bool s_send(SOCKET & _Connection, const std::string & s);
bool s_recv(SOCKET & _Connection, std::string & s);
void LAN_SendDataToServerThread(int Action);
bool LAN_SendDataToServer(int Action, int x, int y);
void LAN_ClientThread();
void LAN_ServerAction(LPARAM lParam);
void LAN_SendDataToClientThread(int num);
bool LAN_SendDataToClient(int Action, int x, int y, int Win_Lost_Continue);
void LAN_ServerThread();
void LAN_CancelNetwork();
void LAN_StartNetwork();
void LAN_CreateGame();
void LAN_ClientFindServerThread(int i);
void LAN_JoinGame();
void LAN_Join_Back();
void LAN_ServerSearchingEnd(LPARAM lParam);
void LAN_ExitJoin();

//GameMenu.h
void DialogSizeByWindow(HWND Window, HWND Dialog);
void GameMenu_MainMenu_Pos(bool fixed_position, int X, int Y);
void GameMenu_CreateMainMenu(UINT ID, int n, const char * A);
void GameMenu_Hide(UINT ID, int n_number);
void GameMenu_Show(UINT ID, int n_number);
UINT GetMenuButtonID(UINT ID,UINT max,const char * button_name);
void SelectMenu_SinglePlayer(HWND W);
void SelectMenu_SinglePlayer_Back(HWND W);
void SelectMenu_SinglePlayer_Reset(HWND W);
void SelectMenu_SinglePlayer_Random(HWND W);
void SelectMenu_SinglePlayer_StartGame(HWND W);
void SelectMenu_Multiplayer_StartGame(HWND W);
void SelectMenu_Multiplayer_ExitGame();
void SelectMenu_SinglePlayer_ExitGame(HWND W);

