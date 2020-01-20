bool recvall(SOCKET & _Connection,char * data,int totalbytes)
{
	int bytes = 0,max_cycle = 0;
	bool ON = true;
	while(bytes < totalbytes && ON && max_cycle++ < 1000)
	{
		int RC = recv(_Connection,data+bytes,totalbytes-bytes,0);
		if(RC == SOCKET_ERROR){ON = false;}else{bytes += RC;}
	}
	return ON;
}
bool sendall(SOCKET & _Connection,char * data,int totalbytes)
{
	int bytes = 0,max_cycle = 0;
	bool ON = true;
	while(bytes < totalbytes && ON && max_cycle++ < 1000)
	{
		int RC = send(_Connection,data+bytes,totalbytes-bytes,0);
		if(RC == SOCKET_ERROR){ON = false;}else{bytes += RC;}
	}
	return ON;
}
bool s_send(SOCKET & _Connection, const std::string & s)
{
	//n = htonl(n);//convert and send int to network
	//n = ntohl(n);//recive int from network and convert
	unsigned __int32 n = s.size();
	if(n == 0){return true;}
	n = htonl(n);
	if(!sendall(_Connection,(char*)&n,sizeof(unsigned __int32))){return false;}
	if(!sendall(_Connection,(char*)s.c_str(),s.size())){return false;}
	
	return true;
}
bool s_recv(SOCKET & _Connection, std::string & s)
{
	//n = htonl(n);//convert and send int to network
	//n = ntohl(n);//recive int from network and convert
	unsigned __int32 n = 0;
	n = htonl(n);
	if(!recvall(_Connection,(char*)&n,sizeof(unsigned __int32))){return false;}
	n = ntohl(n);
	if(n > 0)
	{
		s.resize(n);
		if(!recvall(_Connection,(char*)s.c_str(),n)){return false;}
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void LAN_SendDataToServerThread(int Action)
{
	bool Error = false;
	if(Action == 1)
	{
		if(!s_send(Client,buffer) || !s_send(Client,"S")){Error = true;}
	}
	else if(Action == 2)
	{
		if(!s_send(Client,buffer)){Error = true;}
	}
	if(Error)
	{
		shutdown(Client,SD_BOTH);
		closesocket(Client);
	}
	SendMessage(hWnd,WM_COMMAND,2020,0);//DataSendON = false;
}

bool LAN_SendDataToServer(int Action, int x, int y)
{
	if(!DataSendON)
	{
		DataSendON = true;
		if(Action == 1)
		{
			buffer = "T";
			buffer.resize(sizeof(PlayerTable)+1);
			memcpy((char*)buffer.c_str()+1,(char*)(&P_Table[0]),sizeof(PlayerTable));
		}
		else if(Action == 2)
		{
			buffer = "A"+NTC(x*10 + y);
		}
		CreateThread(0,0,(LPTHREAD_START_ROUTINE)LAN_SendDataToServerThread,(LPVOID)(Action),0,0);
		return true;
	}
	return false;
}

void LAN_ClientThread()
{
	std::string s;
	while(s_recv(Client,s))//Get Data From Server
	{
		while(DataSendON) Sleep(1);
		while(buffer_count) Sleep(1);
		if(s.substr(0,1) == "Q")
		{
			shutdown(Client,SD_BOTH);
			closesocket(Client);
			break;
		}
		else if(s.substr(0,1) == "R")
		{
			SendMessage(hWnd,WM_COMMAND,7899,MAKELPARAM(3, (s.substr(1,1)=="0"?0:1) ));
		}
		else if(s.substr(0,1) == "A")
		{
			SendMessage(hWnd,WM_COMMAND,7899,MAKELPARAM(4, atoi((char*)s.substr(1,3).c_str()) ));
		}
		else if(s.substr(0,1) == "H")
		{
			SendMessage(hWnd,WM_COMMAND,7899,MAKELPARAM(6, atoi((char*)s.substr(1,3).c_str()) ));
		}
		else if(s.substr(0,1) == "T")//Client Sent Table
		{
			buffer = s;
			buffer_count = s.size();
			SendMessage(hWnd,WM_COMMAND,7899,MAKELPARAM(1,1));//GetTable
		}
	}
	SendMessage(hWnd,WM_COMMAND,7880,0);//End of Network
	shutdown(Client,SD_BOTH);
	closesocket(Client);
}

///////////////////////////////////////////////////////////////
void LAN_ServerAction(LPARAM lParam)
{
	if(LOWORD(lParam) == 1)//Server Action
	{
		P_Table[2].Null();
		memcpy((char*)(&P_Table[2]),(char*)buffer.c_str()+1,sizeof(PlayerTable));
		GSM_Generate_PlacedShipTable(2);
		P_Table[2].ActiveTable_null();
		buffer_count = 0;
		if(HIWORD(lParam) == 1)
		{
			P_Table[0] = P_Table[2];
		}
	}
	else if(LOWORD(lParam) == 5)//Client Action >> Attack
	{
		int x,y;
		x = HIWORD(lParam)/10;
		y = HIWORD(lParam)%10;
		P_Table[1].ActiveTable[x][y] = 1;

		if(GSM_CheckCondition(1))
		{//enemy win
			iEndOfGame_HiheShip = false;
			iWinGame = false;
			iMyTurn = 2;
			GameMenu_Show(GM_EXIT_ID,2);
			GameMenu_MainMenu_Pos(true,750,530);
			LAN_SendDataToClient(3,x,y,1);
		}
		else
		{
			iMyTurn = 1;
			LAN_SendDataToClient(3,x,y,0);
		}
		
		RedrawTable(hWnd_Dlg,550+x*40,100+y*40);
		
		RedrawTable(hWnd_Dlg,100+(iParamB/100-1)*40,100+(iParamB%100-1)*40);
		
		if(iMyTurn == 2)//Redraw
		{
			InvalidateRect(hWnd_Dlg,0,true);//Refresh
		}
		else
		{
			RECT r;
			r.left = 550; r.right = 740;
			r.top = 515; r.bottom = 555;
			InvalidateRect(hWnd_Dlg,&r,true);//Refresh
		}
	}
	else if(LOWORD(lParam) == 2)//Server Action >> Client Press Start Game
	{
		P2_inGame = true;
	}
	else if(LOWORD(lParam) == 3)//Client Action
	{
		iMyTurn = HIWORD(lParam);
		InvalidateRect(hWnd_Dlg,0,true);//Refresh
	}
	else if(LOWORD(lParam) == 4 || LOWORD(lParam) == 6)//Client Action
	{
		int x,y;
		x = HIWORD(lParam)/100;
		y = (HIWORD(lParam)/10)%10;
		
		if(LOWORD(lParam) == 6)
		{
			P_Table[0].ActiveTable[x][y] = 1;
			RedrawTable(hWnd_Dlg,100+x*40,100+y*40);
			if(HIWORD(lParam)%10 == 1)
			{
				iEndOfGame_HiheShip = false;
				iWinGame = true;
				iMyTurn = 2;
				GameMenu_Show(GM_EXIT_ID,2);
				GameMenu_MainMenu_Pos(true,750,530);
			}
		}
		if(LOWORD(lParam) == 4)
		{
			P_Table[1].ActiveTable[x][y] = 1;
			if(HIWORD(lParam)%10 == 1)//lost
			{
				iEndOfGame_HiheShip = false;
				iWinGame = false;
				iMyTurn = 2;
				GameMenu_Show(GM_EXIT_ID,2);
				GameMenu_MainMenu_Pos(true,750,530);
			}
			else if(HIWORD(lParam)%10 == 2)//win
			{
				iEndOfGame_HiheShip = false;
				iWinGame = true;
				iMyTurn = 2;
				GameMenu_Show(GM_EXIT_ID,2);
				GameMenu_MainMenu_Pos(true,750,530);
			}
			else{iMyTurn = 1;}
		}
		
		RedrawTable(hWnd_Dlg,550+x*40,100+y*40);
		
		RedrawTable(hWnd_Dlg,100+(iParamB/100-1)*40,100+(iParamB%100-1)*40);
		
		if(iMyTurn == 2)//Redraw
		{
			InvalidateRect(hWnd_Dlg,0,true);//Refresh
		}
		else
		{
			RECT r;
			r.left = 550; r.right = 740;
			r.top = 515; r.bottom = 555;
			InvalidateRect(hWnd_Dlg,&r,true);//Refresh
		}
	}
}

void LAN_SendDataToClientThread(int num)
{
	bool Error = false;
	if(num == 0 || num == 1)
	{
		if(!s_send(Client,buffer)){Error = true;}
		if(!s_send(Client,"R"+NTC(num))){Error = true;}
	}
	else if(num == 2)
	{
		if(!s_send(Client,buffer)){Error = true;}
	}
	if(Error)
	{
		shutdown(Client,SD_BOTH);
		closesocket(Client);
		shutdown(Server,SD_BOTH);
		closesocket(Server);
	}
	SendMessage(hWnd,WM_COMMAND,2020,0);//DataSendON = false;
}

bool LAN_SendDataToClient(int Action, int x, int y, int Win_Lost_Continue)
{
	if(!DataSendON)
	{
		int num = 0;
		DataSendON = true;
		if(Action == 1)
		{
			buffer = "T";
			buffer.resize(sizeof(PlayerTable)+1);
			memcpy((char*)buffer.c_str()+1,(char*)(&P_Table[1]),sizeof(PlayerTable));
			
			iMyTurn = rand()%2;
			num = (iMyTurn?0:1);
		}
		else if(Action == 2)
		{
			num = 2;
			buffer = "A"+NTC(x*100 + y*10 + Win_Lost_Continue);
		}
		else if(Action == 3)
		{
			num = 2;
			buffer = "H"+NTC(x*100 + y*10 + Win_Lost_Continue);
		}
		CreateThread(0,0,(LPTHREAD_START_ROUTINE)LAN_SendDataToClientThread,(LPVOID)(num),0,0);
		return true;
	}
	return false;
}

void LAN_ServerThread()
{
	Client = accept(Server,(SOCKADDR*)&addr,&addrlen);
	
	if(Client != 0)
	{
		SendMessage(hWnd,WM_COMMAND,7881,0);//End of server
		std::string s;
		while(s_recv(Client,s))//recv from client
		{
			while(DataSendON) Sleep(1);
			while(buffer_count) Sleep(1);
			if(s.substr(0,1) == "Q")
			{
				shutdown(Client,SD_BOTH);
				closesocket(Client);
				shutdown(Server,SD_BOTH);
				closesocket(Server);
				break;
			}
			else if(s.substr(0,1) == "T")//Client Sent Table
			{
				buffer = s;
				buffer_count = s.size();
				SendMessage(hWnd,WM_COMMAND,7899,MAKELPARAM(1,0));//GetTable
			}
			else if(s.substr(0,1) == "S")//Client Press Start Game
			{
				SendMessage(hWnd,WM_COMMAND,7899,MAKELPARAM(2,0));
			}
			else if(s.substr(0,1) == "A")//Client Attack
			{
				SendMessage(hWnd,WM_COMMAND,7899,MAKELPARAM(5, atoi((char*)s.substr(1,2).c_str()) ));
			}
		}
	}
	SendMessage(hWnd,WM_COMMAND,7880,0);//End of server
	shutdown(Server,SD_BOTH);
	closesocket(Server);
}

void LAN_CancelNetwork()
{
	s_send(Client,"Q");
	
	shutdown(Server,SD_BOTH);
	closesocket(Server);
	
	shutdown(Client,SD_BOTH);
	closesocket(Client);
}

void LAN_StartNetwork()
{
	iEndOfGame_HiheShip = true;
	iGameMode = 1;
	iMyTurn = 3;
	bMainMenu = false;
	EnableWindow(GetDlgItem(hWnd_Dlg,GetMenuButtonID(GM_SINGLEPLAYER_ID,GM_SINGLEPLAYER_MAX,"Start Game")),false);//Disable Start Button
	GameMenu_Hide(GM_EXIT_ID,2);
	GameMenu_Hide(GM_MAINMENU_ID,GM_MAINMENU_MAX);
	GameMenu_Hide(GM_MULTIPLAYER_ID,GM_MULTIPLAYER_MAX);
	GameMenu_Show(GM_SINGLEPLAYER_ID,GM_SINGLEPLAYER_MAX);
	GameMenu_MainMenu_Pos(true,650,415);
	bShipSelection = true;
	P_Table[0].Null(); P_Table[1].Null();
	iSelected_Ship = iMemParam = 0;
	iParamRotate = true;
	for(int i = 0; i < 4; i++){iShipRemains[i] = i+1;}
	bInGame = false;
	InvalidateRect(hWnd_Dlg,0,true);//Refresh
}

void LAN_CreateGame()
{
	iServerClient = 1;
	
	if(!iServerConnected)
	{
		//Winsock Startup
		WSAData wsaData;
		WORD DllVersion = MAKEWORD(2,1);
		if(WSAStartup(DllVersion,&wsaData) == 0)
		{
			std::string IP;
			char szBuffer[1024] = {0};
			gethostname(szBuffer, sizeof(szBuffer));
			unsigned char IPi[4];
			
			struct hostent *host = gethostbyname(szBuffer);
			IPi[0] = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b1;
			IPi[1] = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b2;
			IPi[2] = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b3;
			IPi[3] = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b4;
			
			IP = NTC(IPi[0])+"."+NTC(IPi[1])+"."+NTC(IPi[2])+"."+NTC(IPi[3]);
			
			addrlen = sizeof(addr);
			addr.sin_addr.s_addr = inet_addr((char*)IP.c_str());
			addr.sin_port = htons(PORT);
			addr.sin_family = AF_INET;
			
			Server = socket(AF_INET,SOCK_STREAM,0);
			
			if(bind(Server,(SOCKADDR*)&addr,sizeof(addr)) != SOCKET_ERROR)
			{
				if(listen(Server,SOMAXCONN) != SOCKET_ERROR)
				{
					P2_inGame = false;
					bWaitForClient = iServerConnected = true;
					LAN_StartNetwork();
					CreateThread(0,0,(LPTHREAD_START_ROUTINE)LAN_ServerThread,0,0,0);
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LAN_ClientFindServerThread(int i)
{
	WORD find = 0;
	
	SOCKADDR_IN addr2;
	addr2.sin_addr.s_addr = inet_addr(FSDataIP[i].IP);
	addr2.sin_port = htons(PORT);
	addr2.sin_family = AF_INET;
	
	Connections[i] = socket(AF_INET,SOCK_STREAM,0);
	if(connect(Connections[i],(SOCKADDR*)&addr2,sizeof(addr2)) == 0)
	{//find
		find = 1;
		Client = Connections[i];
	}
	else
	{
		shutdown(Connections[i],SD_BOTH);
		closesocket(Connections[i]);
	}
	SendMessage(hWnd,WM_COMMAND,7878,MAKELPARAM(find,i));
}

void LAN_JoinGame()
{
	iServerClient = 2;
	if(!iClientConnected)
	{
		//Winsock Startup
		WSAData wsaData;
		WORD DllVersion = MAKEWORD(2,1);
		if(WSAStartup(DllVersion,&wsaData) == 0)
		{
			int i;
			char szBuffer[1024] = {0};
			gethostname(szBuffer, sizeof(szBuffer));
			unsigned char IPi[4];
			
			struct hostent *host = gethostbyname(szBuffer);
			IPi[0] = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b1;
			IPi[1] = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b2;
			IPi[2] = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b3;
			//IPi[3] = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b4;
			
			ConnectionIP = NTC(IPi[0])+"."+NTC(IPi[1])+"."+NTC(IPi[2])+".";
			
			/////////////////////////////////////////////////////////////
			iClientConnected = true;
			iGameMode = 1;
			bMainMenu = false;
			
			Connecting_ON = true;
			GameMenu_Hide(GM_MULTIPLAYER_ID,GM_MULTIPLAYER_MAX);
			EnableWindow(GetDlgItem(hWnd_Dlg,GM_JOIN_ID),true);
			GameMenu_Show(GM_JOIN_ID,1);
			GameMenu_MainMenu_Pos(true,500,300);
			//bShipSelection = true;
			
			P_Table[0].Null(); P_Table[1].Null();
			iSelected_Ship = iMemParam = 0;
			iParamRotate = true;
			bInGame = false;
			InvalidateRect(hWnd_Dlg,0,true);//Refresh
			
			for(i = 0; i < 256; i++)
			{
				FSDataIP[i].Run = true;
				strncpy(FSDataIP[i].IP,(char*)std::string(ConnectionIP+NTC(i)).c_str(),15);
				CreateThread(0,0,(LPTHREAD_START_ROUTINE)LAN_ClientFindServerThread,(LPVOID)(i),0,0);
			}
			SetTimer(hWnd,102,100,0);
		}
	}
}
void LAN_Join_Back()
{
	EnableWindow(GetDlgItem(hWnd_Dlg,GM_JOIN_ID),false);
	for(int i = 0; i < 256; i++)
	{
		shutdown(Connections[i],SD_BOTH);
		closesocket(Connections[i]);
	}
}

void LAN_ServerSearchingEnd(LPARAM lParam)
{
	if(LOWORD(lParam) == 1)
	{
		KillTimer(hWnd,102);
		for(int i = 0; i < 256; i++)
		{
			if(HIWORD(lParam) != i)
			{
				shutdown(Connections[i],SD_BOTH);
				closesocket(Connections[i]);
			}
		}
		Connecting_ON = false;
		GameMenu_Hide(GM_JOIN_ID,1);
		LAN_StartNetwork();
		InvalidateRect(hWnd_Dlg,0,true);//Refresh
		CreateThread(0,0,(LPTHREAD_START_ROUTINE)LAN_ClientThread,0,0,0);
	}
	else
	{
		FSDataIP[HIWORD(lParam)].Run = false;
	}
}

void LAN_ExitJoin()
{
	bool on = true;
	for(int i = 0; i < 256; i++){if(FSDataIP[i].Run){on = false;break;}}
	if(on)
	{
		Connecting_ON = false;
		GameMenu_Hide(GM_JOIN_ID,1);
		GameMenu_Show(GM_MAINMENU_ID,GM_MAINMENU_MAX);
		bMainMenu = true;
		bShipSelection = false;
		GameMenu_MainMenu_Pos(false,0,0);
		bInGame = false;
		iClientConnected = false;
		iGameMode = 0;
		InvalidateRect(hWnd_Dlg,0,true);//Refresh
		KillTimer(hWnd,102);
	}
}