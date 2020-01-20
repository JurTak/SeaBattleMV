#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <windows.h>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <ctime>

#include "resource.h"
#include "GlobalVariables.h"
#include "Declaration.h"

//////////////////////////////////////////
// Declarations
ATOM MyRegisterClass(HINSTANCE hInstance, LPCSTR szWindowClass);
BOOL InitInstance(HINSTANCE, int, LPCSTR, LPCSTR);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MyDlg_Proc(HWND W, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MyDlg_Difficulty_Proc(HWND W, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;
	char className[] = "SEA_BATTLE_MV:GAME";
	hInst = hInstance;
	
	srand(time(0));
	MyRegisterClass(hInstance,className);
	if(!InitInstance(hInstance,nCmdShow,className,"Sea Battle MV")) {return 0;}
	
	while(GetMessage(&msg,NULL,0,0)) 
	{
		if(!TranslateAccelerator(msg.hwnd,NULL,&msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

#include "GameMenu.h"
#include "Graphics.h"
#include "GameSystemModel.h"
#include "LAN.h"

ATOM MyRegisterClass(HINSTANCE hInstance, LPCSTR szWindowClass)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_MY_ICON);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= (HICON)LoadImage(hInstance,MAKEINTRESOURCE(IDI_MY_ICON),IMAGE_ICON,16,16,LR_COPYFROMRESOURCE);
	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, LPCSTR szWindowClass, LPCSTR szTitle)
{
	hWnd = CreateWindowExA(0,szWindowClass,szTitle,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,0,CW_USEDEFAULT,0,NULL,0,hInstance,NULL);

	hWnd_Dlg = CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_MYDLG),hWnd,reinterpret_cast<DLGPROC>(MyDlg_Proc));
	ShowWindow(hWnd_Dlg,true);
	
	hWnd_Dlg_D = CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_DIFFICULTY),hWnd_Dlg,reinterpret_cast<DLGPROC>(MyDlg_Difficulty_Proc));
	ShowWindow(hWnd_Dlg_D,false);
	
	//Menu
	GameMenu_CreateMainMenu(GM_MAINMENU_ID,GM_MAINMENU_MAX,"Exit\0About...\0Multiplayer (LAN)\0Single Player");
	GameMenu_CreateMainMenu(GM_MULTIPLAYER_ID,GM_MULTIPLAYER_MAX,"Back\0Join\0Create Game");
	GameMenu_CreateMainMenu(GM_SINGLEPLAYER_ID,GM_SINGLEPLAYER_MAX,"Back\0Reset\0Random\0Start Game");
	GameMenu_CreateMainMenu(GM_EXIT_ID,2,"Exit Game\0Play Again");
	GameMenu_CreateMainMenu(GM_JOIN_ID,1,"Cancel");
	
	GameMenu_Show(GM_MAINMENU_ID,GM_MAINMENU_MAX);
	
	if(hWnd)
	{
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
		return TRUE;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_SIZE:
			DialogSizeByWindow(hWnd,hWnd_Dlg);
			if(bMainMenu){GameMenu_MainMenu_Pos(false,0,0);}
			break;

		case WM_COMMAND:
			if(LOWORD(wParam) == 7899)
			{
				LAN_ServerAction(lParam);
			}
			else if(LOWORD(wParam) == 7880)//Server Action >> Exit Network
			{
				SelectMenu_Multiplayer_ExitGame();
			}
			else if(LOWORD(wParam) == 7881)
			{
				iClientConnected = true;
				bWaitForClient = false;
				InvalidateRect(hWnd_Dlg,0,true);//Refresh
			}
			else if(LOWORD(wParam) == 7878)//Client Actions >> Server Searching End
			{
				LAN_ServerSearchingEnd(lParam);
			}
			else if(LOWORD(wParam) == 2020)
			{
				DataSendON = false;
			}
			break;

		case WM_TIMER:
			if(wParam == 101)
			{
				AI_ShipShot_Action();
				KillTimer(hWnd,101);
			}
			if(wParam == 102)//Exit Join
			{
				LAN_ExitJoin();
			}
			if(wParam == 103)
			{
				if(P2_inGame)
				{
					P2_inGame = false;
					LAN_SendDataToClient(1,0,0,0);//Generate turn and send to client
					P_Table[0] = P_Table[2];
					InvalidateRect(hWnd_Dlg,0,true);//Refresh
					KillTimer(hWnd,103);
				}
			}
			break;
			
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

LRESULT CALLBACK MyDlg_Proc(HWND W, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	switch (message)
	{
		case WM_INITDIALOG:
			return TRUE;

		case WM_COMMAND:
			/////////////////////////////////////////////////////////////////////////////
			//In Game
			if(LOWORD(wParam) == GM_EXIT_ID+1)//Play Again
			{
				if(iGameMode == 0)//Single Player
				{
					SelectMenu_SinglePlayer(W);
				}
				else//Multiplayer
				{
					LAN_StartNetwork();
				}
				break;
			}
			if(LOWORD(wParam) == GM_EXIT_ID)//Exit Game
			{
				if(iGameMode == 0)//Single Player
				{
					SelectMenu_SinglePlayer_ExitGame(W);
				}
				else//Multiplayer
				{
					LAN_CancelNetwork();
				}
				break;
			}
			/////////////////////////////////////////////////////////////////////////////
			//Single Player
			if(LOWORD(wParam) == GM_SINGLEPLAYER_ID+3)//Single Player >> Start Game
			{
				if(iGameMode == 0)//Single Player
				{
					SelectMenu_SinglePlayer_StartGame(W);
				}
				else//Multiplayer
				{
					SelectMenu_Multiplayer_StartGame(W);
				}
				break;
			}
			if(LOWORD(wParam) == GM_SINGLEPLAYER_ID+2)//Single Player >> Random
			{
				SelectMenu_SinglePlayer_Random(W);
				break;
			}
			if(LOWORD(wParam) == GM_SINGLEPLAYER_ID+1)//Single Player >> Reset
			{
				SelectMenu_SinglePlayer_Reset(W);
				break;
			}
			if(LOWORD(wParam) == GM_SINGLEPLAYER_ID)//Single Player >> Back
			{
				if(iGameMode == 0)//Single Player
				{
					SelectMenu_SinglePlayer_Back(W);
				}
				else//Multiplayer
				{
					LAN_CancelNetwork();
				}
				break;
			}
			/////////////////////////////////////////////////////////////////////////////
			//Multiplayer (LAN) >> Join
			if(LOWORD(wParam) == GM_JOIN_ID)//Multiplayer (LAN) >> Join >> Cancel
			{
				LAN_Join_Back();
				break;
			}
			/////////////////////////////////////////////////////////////////////////////
			//Multiplayer (LAN)
			if(LOWORD(wParam) == GM_MULTIPLAYER_ID+2)//Multiplayer (LAN) >> Create Game
			{
				LAN_CreateGame();
				break;
			}
			if(LOWORD(wParam) == GM_MULTIPLAYER_ID+1)//Multiplayer (LAN) >> Join
			{
				LAN_JoinGame();
				break;
			}
			if(LOWORD(wParam) == GM_MULTIPLAYER_ID)//Multiplayer (LAN) >> Back
			{
				GameMenu_Hide(GM_MULTIPLAYER_ID,GM_MULTIPLAYER_MAX);
				GameMenu_Show(GM_MAINMENU_ID,GM_MAINMENU_MAX);
				GameMenu_MainMenu_Pos(false,0,0);
				break;
			}
			/////////////////////////////////////////////////////////////////////////////
			//Main Menu
			if(LOWORD(wParam) == GM_MAINMENU_ID+3)//Single Player
			{
				SelectMenu_SinglePlayer(W);
				break;
			}
			if(LOWORD(wParam) == GM_MAINMENU_ID+2)//Multiplayer (LAN)
			{
				GameMenu_Hide(GM_MAINMENU_ID,GM_MAINMENU_MAX);
				GameMenu_Show(GM_MULTIPLAYER_ID,GM_MULTIPLAYER_MAX);
				GameMenu_MainMenu_Pos(false,0,0);
				break;
			}
			if(LOWORD(wParam) == GM_MAINMENU_ID+1)//About...
			{
				MSGBOXPARAMSA msgbox = {0};
				msgbox.cbSize = sizeof(MSGBOXPARAMSA);
				msgbox.hwndOwner = W;
				msgbox.hInstance = GetModuleHandle(NULL);
				msgbox.lpszText = "Sea Battle MV\nVersion 1.0.0.4\nCopyright (C) 2018, Jurij T.";
				msgbox.lpszCaption = "About...";
				msgbox.dwStyle = MB_OK | MB_SETFOREGROUND | MB_USERICON;
				msgbox.lpszIcon = MAKEINTRESOURCE(IDI_MY_ICON);
				MessageBoxIndirect(&msgbox);
				break;
			}
			if(LOWORD(wParam) == GM_MAINMENU_ID){DestroyWindow(hWnd);}
			break;

		case WM_MOUSEMOVE:
			if(bShipSelection || bInGame){GSM_ShipSelection(W,(bInGame?100:200),100,lParam);}
			break;

		case WM_LBUTTONUP:
			if(bShipSelection){GSM_ShipSelection_Action(200,100,lParam);}
			if(bInGame){GSM_ShipShot_Action(100,100);}
			break;

		case WM_RBUTTONUP:
			if(bShipSelection){GSM_ShipSel_Rotate(W);}
			break;

		case WM_PAINT:
			hDC = BeginPaint(W, &ps);
			if(bMainMenu)
			{
				//Font & Text
				RECT rt;
				GetClientRect(W, &rt);
				SetTextColor(hDC,RGB(10,100,160));
				
				HFONT hFontText = CreateFont(100,0,0,0,FW_BOLD,true,FALSE,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_SWISS,"Arial");
				HFONT hFont = (HFONT)SelectObject(hDC,hFontText);
				
				SetBkMode(hDC,TRANSPARENT);
				
				char Text[] = "Sea Battle MV";
				//TextOut(hDC,0,0,Text,strlen(Text));
				DrawText(hDC, Text, strlen(Text), &rt, DT_CENTER);
				
				DeleteObject(SelectObject(hDC,hFont));
			}
			else
			{
				GameMSG(hDC);
			}
			EndPaint(W, &ps);
			break;

		case WM_CTLCOLORDLG:
			return (LRESULT)CreateSolidBrush(RGB(255,255,255));
	}
    return FALSE;
}

LRESULT CALLBACK MyDlg_Difficulty_Proc(HWND W, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			{
				HFONT My_Font = CreateFont(20,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_SWISS,"Arial");
				SetWindowPos(W,NULL,880,353,0,0,SWP_NOSIZE);
				AI_var.difficulty = 0;
				SendMessage(GetDlgItem(W,IDC_STATIC1),WM_SETFONT,(WPARAM)My_Font,0);
				SendMessage(GetDlgItem(W,IDC_RADIO1),WM_SETFONT,(WPARAM)My_Font,0);
				SendMessage(GetDlgItem(W,IDC_RADIO2),WM_SETFONT,(WPARAM)My_Font,0);
				SendMessage(GetDlgItem(W,IDC_RADIO3),WM_SETFONT,(WPARAM)My_Font,0);
				SendMessage(GetDlgItem(W,IDC_RADIO4),WM_SETFONT,(WPARAM)My_Font,0);
				SendMessage(GetDlgItem(W,IDC_RADIO1),BM_SETCHECK,true,0);
			}
			return TRUE;

		case WM_COMMAND:
			if(LOWORD(wParam) == IDC_RADIO1) {AI_var.difficulty = 0;SetFocus(hWnd);break;}
			if(LOWORD(wParam) == IDC_RADIO2) {AI_var.difficulty = 1;SetFocus(hWnd);break;}
			if(LOWORD(wParam) == IDC_RADIO3) {AI_var.difficulty = 2;SetFocus(hWnd);break;}
			if(LOWORD(wParam) == IDC_RADIO4) {AI_var.difficulty = 3;SetFocus(hWnd);break;}
			break;
	}
    return FALSE;
}

