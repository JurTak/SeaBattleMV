void RedrawTable(HWND W, int x, int y, int sizX = 1, int sizY = 1)
{
	RECT rc;//GetClientRect(W, &rc);
	rc.left = x;
	rc.right = x + 1 + sizX*40;
	rc.top = y;
	rc.bottom = y + 1 + sizY*40;
	RedrawWindow(W,&rc,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_NOCHILDREN);
}

void DrowRect(HDC hDC, int x, int y, int cx, int cy, COLORREF line = 0, unsigned char dot1_solid0 = 0, COLORREF bg = -1)
{
	HPEN hBluePen = CreatePen((dot1_solid0?PS_DOT:PS_SOLID), 1, line);
	HPEN hPen = (HPEN)SelectObject(hDC, hBluePen);
	HBRUSH hPurpleBrush = ( bg == -1 ? (HBRUSH)GetStockObject(NULL_BRUSH) : CreateSolidBrush(bg) );
	HBRUSH hBrush = (HBRUSH)SelectObject(hDC, hPurpleBrush);
	
	Rectangle(hDC,x,y,x+cx,y+cy);
	
	SelectObject(hDC,hPen);
	DeleteObject(hBluePen);
	SelectObject(hDC, hBrush);
	DeleteObject(hPurpleBrush);
}

void SelectMenu_DrowBoxTable(HDC hDC, int x, int y)
{
	HPEN hBluePen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
	HPEN hPen = (HPEN)SelectObject(hDC, hBluePen);
	HBRUSH hPurpleBrush = (HBRUSH)GetStockObject(NULL_BRUSH);//CreateSolidBrush(RGB(230,240,252));
	HBRUSH hBrush = (HBRUSH)SelectObject(hDC, hPurpleBrush);
	
	int box_size = 40;
	int box_count = 10;
	
	int X,Y;
	X = x + 2 + box_count*box_size;
	Y = y + 2 + box_count*box_size;
	Rectangle(hDC,x,y,X,Y);
	
	/*for(int j = 0; j < box_count; j++)
	{
		for(int i = 0; i < box_count; i++)
		{
			X = x + 1 + box_size*i;
			Y = y + 1 + box_size*j;
			Rectangle(hDC,X,Y,X+box_size,Y+box_size);
		}
	}//*/
	
	SelectObject(hDC,hPen);
	DeleteObject(hBluePen);
	SelectObject(hDC, hBrush);
	DeleteObject(hPurpleBrush);
}

void SelectMenu_Ship1(HDC hDC, int x, int y, int x_pos, int y_pos)
{
	HPEN hBluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN hPen = (HPEN)SelectObject(hDC, hBluePen);
	HBRUSH hPurpleBrush = CreateSolidBrush(RGB(200, 150, 100));
	HBRUSH hBrush = (HBRUSH)SelectObject(hDC, hPurpleBrush);
	
	int X = x + 5 + (x_pos-1)*40;
	int Y = y + 4 + (y_pos-1)*40;
	
	Ellipse(hDC,X,Y+10,X+15,Y+25);
	Ellipse(hDC,X+17,Y+10,X+32,Y+25);
	Rectangle(hDC,X+7,Y+9,X+25,Y+26);
	Rectangle(hDC,X+12,Y+9,X+20,Y+26);
	
	SelectObject(hDC,hPen);
	DeleteObject(hBluePen);
	SelectObject(hDC, hBrush);
	DeleteObject(hPurpleBrush);
}

void SelectMenu_Ship2(HDC hDC, int x, int y, int x_pos, int y_pos, bool rotate)
{
	HPEN hBluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN hPen = (HPEN)SelectObject(hDC, hBluePen);
	HBRUSH hPurpleBrush = CreateSolidBrush(RGB(200, 150, 100));
	HBRUSH hBrush = (HBRUSH)SelectObject(hDC, hPurpleBrush);
	
	int X = x+1+10 + (x_pos-1)*40;
	int Y = y+1+10 + (y_pos-1)*40;
	
	Ellipse(hDC,X,Y,X+20,Y+20);
	Ellipse(hDC,X+(rotate?40:0),Y+(rotate?0:40),X+20+(rotate?40:0),Y+20+(rotate?0:40));
	Rectangle(hDC,X+(rotate?10:0),Y+(rotate?0:10),X+(rotate?50:20),Y+(rotate?20:50));
	Rectangle(hDC,X+(rotate?12:2),Y+(rotate?2:12),X+(rotate?48:18),Y+(rotate?18:48));

	SelectObject(hDC,hPen);
	DeleteObject(hBluePen);
	SelectObject(hDC, hBrush);
	DeleteObject(hPurpleBrush);

	HPEN hBluePen2 = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN hPen2 = (HPEN)SelectObject(hDC, hBluePen2);
	HBRUSH hPurpleBrush2 = CreateSolidBrush(RGB(240, 230, 170));	
	HBRUSH hBrush2 = (HBRUSH)SelectObject(hDC, hPurpleBrush2);
	
	Ellipse(hDC,X+(rotate?15:5),Y+(rotate?5:15),X+(rotate?25:15),Y+(rotate?15:25));
	Ellipse(hDC,X+(rotate?35:5),Y+(rotate?5:35),X+(rotate?45:15),Y+(rotate?15:45));
	
	SelectObject(hDC,hPen2);
	DeleteObject(hBluePen2);
	SelectObject(hDC, hBrush2);
	DeleteObject(hPurpleBrush2);
}

void SelectMenu_Ship3(HDC hDC, int x, int y, int x_pos, int y_pos, bool rotate)
{
	HPEN hBluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN hPen = (HPEN)SelectObject(hDC, hBluePen);
	HBRUSH hPurpleBrush = CreateSolidBrush(RGB(200, 150, 100));
	HBRUSH hBrush = (HBRUSH)SelectObject(hDC, hPurpleBrush);
	
	int X = x+8 + (x_pos-1)*40;
	int Y = y+8 + (y_pos-1)*40;
	
	Ellipse(hDC,X,Y,X+26,Y+26);
	Ellipse(hDC,X+(rotate?80:0),Y+(rotate?0:80),X+(rotate?106:26),Y+(rotate?26:106));
	Rectangle(hDC,X+(rotate?12:0),Y+(rotate?0:12),X+(rotate?94:26),Y+(rotate?26:94));
	Rectangle(hDC,X+(rotate?32:2),Y+(rotate?2:32),X+(rotate?92:24),Y+(rotate?24:92));

	SelectObject(hDC,hPen);
	DeleteObject(hBluePen);
	SelectObject(hDC, hBrush);
	DeleteObject(hPurpleBrush);

	HPEN hBluePen2 = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN hPen2 = (HPEN)SelectObject(hDC, hBluePen2);
	HBRUSH hPurpleBrush2 = CreateSolidBrush(RGB(240, 230, 170));	
	HBRUSH hBrush2 = (HBRUSH)SelectObject(hDC, hPurpleBrush2);
	
	Ellipse(hDC,X+(rotate?35:5),Y+(rotate?5:35),X+(rotate?50:20),Y+(rotate?20:50));
	Ellipse(hDC,X+(rotate?55:5),Y+(rotate?5:55),X+(rotate?70:20),Y+(rotate?20:70));
	Ellipse(hDC,X+(rotate?75:7),Y+(rotate?7:75),X+(rotate?86:18),Y+(rotate?18:86));
	
	SelectObject(hDC,hPen2);
	DeleteObject(hBluePen2);
	SelectObject(hDC, hBrush2);
	DeleteObject(hPurpleBrush2);

	HPEN hBluePen3 = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN hPen3 = (HPEN)SelectObject(hDC, hBluePen3);
	HBRUSH hPurpleBrush3 = CreateSolidBrush(RGB(190, 205, 190));	
	HBRUSH hBrush3 = (HBRUSH)SelectObject(hDC, hPurpleBrush3);
	
	Ellipse(hDC,X+(rotate?37:7),Y+(rotate?7:37),X+(rotate?48:18),Y+(rotate?18:48));
	Ellipse(hDC,X+(rotate?57:7),Y+(rotate?7:57),X+(rotate?68:18),Y+(rotate?18:68));
	Rectangle(hDC,X+(rotate?16:4),Y+(rotate?4:16),X+(rotate?28:22),Y+(rotate?22:28));
	
	SelectObject(hDC,hPen3);
	DeleteObject(hBluePen3);
	SelectObject(hDC, hBrush3);
	DeleteObject(hPurpleBrush3);
}

void SelectMenu_Ship4(HDC hDC, int x, int y, int x_pos, int y_pos, bool rotate)
{
	HPEN hBluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN hPen = (HPEN)SelectObject(hDC, hBluePen);
	HBRUSH hPurpleBrush = CreateSolidBrush(RGB(200, 150, 100));
	HBRUSH hBrush = (HBRUSH)SelectObject(hDC, hPurpleBrush);
	
	int X = x+6 + (x_pos-1)*40;
	int Y = y+6 + (y_pos-1)*40;
	
	Ellipse(hDC,X,Y,X+30,Y+30);
	Ellipse(hDC,X+(rotate?120:0),Y+(rotate?0:120),X+(rotate?150:30),Y+(rotate?30:150));
	Rectangle(hDC,X+(rotate?14:0),Y+(rotate?0:14),X+(rotate?136:30),Y+(rotate?30:136));
	Rectangle(hDC,X+(rotate?16:2),Y+(rotate?2:16),X+(rotate?40:28),Y+(rotate?28:40));
	Rectangle(hDC,X+(rotate?42:2),Y+(rotate?2:42),X+(rotate?134:28),Y+(rotate?28:134));

	SelectObject(hDC,hPen);
	DeleteObject(hBluePen);
	SelectObject(hDC, hBrush);
	DeleteObject(hPurpleBrush);

	HPEN hBluePen2 = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN hPen2 = (HPEN)SelectObject(hDC, hBluePen2);
	HBRUSH hPurpleBrush2 = CreateSolidBrush(RGB(240, 230, 170));	
	HBRUSH hBrush2 = (HBRUSH)SelectObject(hDC, hPurpleBrush2);
	
	Ellipse(hDC,X+(rotate?45:6),Y+(rotate?6:45),X+(rotate?63:24),Y+(rotate?24:63));
	Ellipse(hDC,X+(rotate?65:5),Y+(rotate?5:65),X+(rotate?85:25),Y+(rotate?25:85));
	Ellipse(hDC,X+(rotate?87:6),Y+(rotate?6:87),X+(rotate?105:24),Y+(rotate?24:105));
	Ellipse(hDC,X+(rotate?108:10),Y+(rotate?10:108),X+(rotate?118:20),Y+(rotate?20:118));
	
	SelectObject(hDC,hPen2);
	DeleteObject(hBluePen2);
	SelectObject(hDC, hBrush2);
	DeleteObject(hPurpleBrush2);

	HPEN hBluePen3 = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN hPen3 = (HPEN)SelectObject(hDC, hBluePen3);
	HBRUSH hPurpleBrush3 = CreateSolidBrush(RGB(190, 205, 190));	
	HBRUSH hBrush3 = (HBRUSH)SelectObject(hDC, hPurpleBrush3);
	
	Ellipse(hDC,X+(rotate?48:9),Y+(rotate?9:48),X+(rotate?60:21),Y+(rotate?21:60));
	Ellipse(hDC,X+(rotate?68:8),Y+(rotate?8:68),X+(rotate?82:22),Y+(rotate?22:82));
	Ellipse(hDC,X+(rotate?90:9),Y+(rotate?9:90),X+(rotate?102:21),Y+(rotate?21:102));
	Rectangle(hDC,X+(rotate?18:6),Y+(rotate?6:18),X+(rotate?32:24),Y+(rotate?24:32));
	Rectangle(hDC,X+(rotate?120:4),Y+(rotate?4:120),X+(rotate?132:10),Y+(rotate?10:132));
	Rectangle(hDC,X+(rotate?120:20),Y+(rotate?20:120),X+(rotate?132:26),Y+(rotate?26:132));
	Rectangle(hDC,X+(rotate?120:12),Y+(rotate?12:120),X+(rotate?132:18),Y+(rotate?18:132));
	
	SelectObject(hDC,hPen3);
	DeleteObject(hBluePen3);
	SelectObject(hDC, hBrush3);
	DeleteObject(hPurpleBrush3);
}

void SelectMenu_MissedShot(HDC hDC, int x, int y, int x_pos, int y_pos)
{
	HPEN hBluePen = CreatePen(PS_SOLID, 1, RGB(230-60, 240-60, 250-60));
	HPEN hPen = (HPEN)SelectObject(hDC, hBluePen);
	HBRUSH hPurpleBrush = (HBRUSH)GetStockObject(NULL_BRUSH);//CreateSolidBrush(RGB(200, 150, 100));
	HBRUSH hBrush = (HBRUSH)SelectObject(hDC, hPurpleBrush);
	
	int X = x + 1 + (x_pos-1)*40;
	int Y = y + 1 + (y_pos-1)*40;
	
	Ellipse(hDC,X+5,Y+5,X+35+1,Y+35+1);
	Ellipse(hDC,X+10,Y+10,X+30+1,Y+30+1);
	Ellipse(hDC,X+15,Y+15,X+25+1,Y+25+1);
	MoveToEx(hDC,X+2,Y+2,NULL); LineTo(hDC,X+38,Y+38);
	MoveToEx(hDC,X+38,Y+2,NULL); LineTo(hDC,X+2,Y+38);
	
	SelectObject(hDC,hPen);
	DeleteObject(hBluePen);
	SelectObject(hDC, hBrush);
	DeleteObject(hPurpleBrush);
}
void SelectMenu_HitShot(HDC hDC, int x, int y, int x_pos, int y_pos)
{
	int X = x + 1 + (x_pos-1)*40;
	int Y = y + 1 + (y_pos-1)*40;
	int i,n;
	COLORREF c;
	
	HPEN hBluePen = CreatePen(PS_SOLID, 1, RGB(165, 13, 9));
	HPEN hPen = (HPEN)SelectObject(hDC, hBluePen);
	HBRUSH hPurpleBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hBrush = (HBRUSH)SelectObject(hDC, hPurpleBrush);
	
	for(n = 0; n < 8; n+=2) Ellipse(hDC,X+8+n,Y+8+n,X+32+1-n,Y+32+1-n);
	
	SelectObject(hDC,hPen);
	DeleteObject(hBluePen);
	SelectObject(hDC, hBrush);
	DeleteObject(hPurpleBrush);
	
	for(i = 0; i < 3; i++)
	{
		if		(i == 0){n = 5;c = RGB(0, 0, 0);}
		else if (i == 1){n = 10;c = RGB(165, 13, 9);}
		else if (i == 2){n = 15;c = RGB(252, 243, 24);}
		
		HPEN hBluePen = CreatePen(PS_SOLID, 1, c);//RGB(252, 243, 24)
		HPEN hPen = (HPEN)SelectObject(hDC, hBluePen);
		HBRUSH hPurpleBrush = (HBRUSH)GetStockObject(NULL_BRUSH);//CreateSolidBrush(RGB(200, 150, 100));
		HBRUSH hBrush = (HBRUSH)SelectObject(hDC, hPurpleBrush);
		
		MoveToEx(hDC,X+n,Y+n,NULL); LineTo(hDC,X+40-n,Y+40-n);
		MoveToEx(hDC,X+40-n,Y+n,NULL); LineTo(hDC,X+n,Y+40-n);
		
		MoveToEx(hDC,X+20,Y+n+3,NULL); LineTo(hDC,X+20,Y+40-n-3);
		MoveToEx(hDC,X+n+3,Y+20,NULL); LineTo(hDC,X+40-n-3,Y+20);

		MoveToEx(hDC,X+20-7/(n/5),Y+n,NULL); LineTo(hDC,X+20+7/(n/5),Y+40-n);
		MoveToEx(hDC,X+20+7/(n/5),Y+n,NULL); LineTo(hDC,X+20-7/(n/5),Y+40-n);
		
		MoveToEx(hDC,X+n,Y+20-7/(n/5),NULL); LineTo(hDC,X+40-n,Y+20+7/(n/5));
		MoveToEx(hDC,X+n,Y+20+7/(n/5),NULL); LineTo(hDC,X+40-n,Y+20-7/(n/5));
		
		SelectObject(hDC,hPen);
		DeleteObject(hBluePen);
		SelectObject(hDC, hBrush);
		DeleteObject(hPurpleBrush);
	}
}

void SelectMenu_Table(HDC hDC)
{
	int X = 200;
	int Y = 100;
	
	RECT rt;rt.left = X+400;rt.right = X+500;
	SetTextColor(hDC,RGB(10,100,160));
				
	HFONT hFontText = CreateFont(30,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_SWISS,"Arial");
	HFONT hFont = (HFONT)SelectObject(hDC,hFontText);
				
	SetBkMode(hDC,TRANSPARENT);
				
	char S4[] = "  x"; *S4 = iShipRemains[0]+'0';
	char S3[] = "  x"; *S3 = iShipRemains[1]+'0';
	char S2[] = "  x"; *S2 = iShipRemains[2]+'0';
	char S1[] = "  x"; *S1 = iShipRemains[3]+'0';

	rt.top = Y+20; rt.bottom = Y+50;
	DrawText(hDC, S4, 3, &rt, DT_RIGHT);
	rt.top = Y+20+40; rt.bottom = Y+50+40;
	DrawText(hDC, S3, 3, &rt, DT_RIGHT);
	rt.top = Y+20+40*2; rt.bottom = Y+50+40*2;
	DrawText(hDC, S2, 3, &rt, DT_RIGHT);
	rt.top = Y+20+40*3; rt.bottom = Y+50+40*3;
	DrawText(hDC, S1, 3, &rt, DT_RIGHT);
				
	DeleteObject(SelectObject(hDC,hFont));
	
	SelectMenu_Ship4(hDC,X+505,Y+15,1,1,1);
	SelectMenu_Ship3(hDC,X+505,Y+15,1,2,1);
	SelectMenu_Ship2(hDC,X+505,Y+15,1,3,1);
	SelectMenu_Ship1(hDC,X+515,Y+15,1,4);
	
	HFONT hFontText2 = CreateFont(16,0,0,0,FW_NORMAL,false,FALSE,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_SWISS,"Arial");
	HFONT hFont2 = (HFONT)SelectObject(hDC,hFontText2);
	SetBkMode(hDC,TRANSPARENT);
	char Text[] = "Click right mouse button to rotate";
	TextOut(hDC,680,300,Text,strlen(Text));
	DeleteObject(SelectObject(hDC,hFont2));
}

void SelectMenu_ShipSelection_DrowTable(HDC hDC, int X, int Y)
{
	int x = X+1;
	int y = Y+1;
	int pos_x = iParamB/100;
	int pos_y = iParamB%100;
	int j,i,n;
	unsigned char k = 0;
	
	SelectMenu_DrowBoxTable(hDC,X,Y);
	
	for(j = 0; j < 10; j++)
	{
		for(i = 0; i < 10; i++)
		{
			n = 0;
			k = (pos_x == i+1 && pos_y == j+1) ? 255 : 0;
			if(P_Table[0].ActiveTable[i][j] == 1){k = 0;n = -20;}
			
			if(k){DrowRect(hDC,x+i*40,y+j*40,40,40,RGB(255, 255, 255));}
			DrowRect(hDC,x+i*40,y+j*40,40,40,RGB(0, 0, k),k,RGB(230+n,240+n,252+n));
		}
	}
	for(j = 0; j < 10; j++)
	{
		for(i = 0; i < 10; i++)
		{
			k = (pos_x == i+1 && pos_y == j+1) ? 255 : 0;
			if(P_Table[0].ActiveTable[i][j] == 1){k = 0;}
			
			//show selection ship
			if(k && iSelected_Ship == 4 && iShipRemains[3] > 0)
			{
				SelectMenu_Ship1(hDC,x-1,y-1,pos_x,pos_y);
			}
			else if(k && iSelected_Ship == 3 && iShipRemains[2] > 0)
			{
				if(iParamRotate)
				{
					if(pos_x <= 9 && pos_y <= 10 && P_Table[0].ActiveTable[i+1][j] == 0)
					{
						SelectMenu_Ship2(hDC,x-1,y-1,pos_x,pos_y,iParamRotate);
					}
				}
				else
				{
					if(pos_x <= 10 && pos_y <= 9 && P_Table[0].ActiveTable[i][j+1] == 0)
					{
						SelectMenu_Ship2(hDC,x-1,y-1,pos_x,pos_y,iParamRotate);
					}
				}
			}
			else if(k && iSelected_Ship == 2 && iShipRemains[1] > 0)
			{
				if(iParamRotate)
				{
					if(pos_x <= 8 && pos_y <= 10 && P_Table[0].ActiveTable[i+1][j] == 0 && 
													P_Table[0].ActiveTable[i+2][j] == 0)
					{
						SelectMenu_Ship3(hDC,x-1,y-1,pos_x,pos_y,iParamRotate);
					}
				}
				else
				{
					if(pos_x <= 10 && pos_y <= 8 && P_Table[0].ActiveTable[i][j+1] == 0 && 
													P_Table[0].ActiveTable[i][j+2] == 0)
					{
						SelectMenu_Ship3(hDC,x-1,y-1,pos_x,pos_y,iParamRotate);
					}
				}
			}
			else if(k && iSelected_Ship == 1 && iShipRemains[0] > 0)
			{
				if(iParamRotate)
				{
					if(pos_x <= 7 && pos_y <= 10 && P_Table[0].ActiveTable[i+1][j] == 0 && 
													P_Table[0].ActiveTable[i+2][j] == 0 && 
													P_Table[0].ActiveTable[i+3][j] == 0)
					{
						SelectMenu_Ship4(hDC,x-1,y-1,pos_x,pos_y,iParamRotate);
					}
				}
				else
				{
					if(pos_x <= 10 && pos_y <= 7 && P_Table[0].ActiveTable[i][j+1] == 0 && 
													P_Table[0].ActiveTable[i][j+2] == 0 && 
													P_Table[0].ActiveTable[i][j+3] == 0)
					{
						SelectMenu_Ship4(hDC,x-1,y-1,pos_x,pos_y,iParamRotate);
					}
				}
			}
		}
	}
	
	//show placed ship
	for(i = 0; i < 4; i++)//ship (size 1)
	{
		if(P_Table[0].ship1[i].on == 1)
		{
			SelectMenu_Ship1(hDC,x,y,P_Table[0].ship1[i].x,P_Table[0].ship1[i].y);
		}
	}
	for(i = 0; i < 3; i++)//ship (size 2)
	{
		if(P_Table[0].ship2[i].on == 1)
		{
			SelectMenu_Ship2(hDC,x,y,P_Table[0].ship2[i].x,P_Table[0].ship2[i].y,P_Table[0].ship2[i].rotate);
		}
	}
	for(i = 0; i < 2; i++)//ship (size 3)
	{
		if(P_Table[0].ship3[i].on == 1)
		{
			SelectMenu_Ship3(hDC,x,y,P_Table[0].ship3[i].x,P_Table[0].ship3[i].y,P_Table[0].ship3[i].rotate);
		}
	}
	if(P_Table[0].ship4.on == 1)//ship (size 4)
	{
		SelectMenu_Ship4(hDC,x,y,P_Table[0].ship4.x,P_Table[0].ship4.y,P_Table[0].ship4.rotate);
	}
	
	//Select Ship
	for(i = 0; i < 4; i++)
	{
		k = (pos_y == i+1) ? 0 : 255;
		j = (iSelected_Ship==i+1?200:0);
		
		DrowRect(hDC,x+505,y+15+40*i,160,40,RGB(255,255,255),false);
		DrowRect(hDC,x+505,y+15+40*i,160,40,RGB(k-j,k-j,255-j),!k);
	}
}

void SelectMenu_InGame_DrowTable(HDC hDC, int X, int Y, const char * table_name, int Player, bool SelectON, bool hide_ship)
{
	int x = X+1;
	int y = Y+1;
	int pos_x = iParamB/100;
	int pos_y = iParamB%100;
	int j,i,n;
	unsigned char k = 0;

	//Font & Text >> Table name
	SetTextColor(hDC,RGB(0,20,30));
	
	HFONT hFontText = CreateFont(20,0,0,0,FW_BOLD,true,FALSE,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_SWISS,"Arial");
	HFONT hFont = (HFONT)SelectObject(hDC,hFontText);
	
	SetBkMode(hDC,TRANSPARENT);
	
	TextOut(hDC,X+10,80,table_name,strlen(table_name));
	
	DeleteObject(SelectObject(hDC,hFont));
	
	//Bord
	SelectMenu_DrowBoxTable(hDC,X,Y);
	
	for(j = 0; j < 10; j++)
	{
		for(i = 0; i < 10; i++)
		{
			n = 0;
			if(SelectON && iMyTurn == 1){k = (pos_x == i+1 && pos_y == j+1) ? 255 : 0;}else{k = 0;}
			if(P_Table[Player].ActiveTable[i][j] == 1){k = 0;n = -20;}
			
			if(k){DrowRect(hDC,x+i*40,y+j*40,40,40,RGB(255, 255, 255));}
			DrowRect(hDC,x+i*40,y+j*40,40,40,RGB(0, 0, k),k,RGB(230+n,240+n,252+n));

			if(n){if(P_Table[Player].PlacedShipTable[i][j] == 0){SelectMenu_MissedShot(hDC,x-1,y-1,i+1,j+1);}}
		}
	}
	
	if(!hide_ship)//show placed ship
	{
		for(i = 0; i < 4; i++)//ship (size 1)
		{
			if(P_Table[Player].ship1[i].on == 1)
			{
				SelectMenu_Ship1(hDC,x,y,P_Table[Player].ship1[i].x,P_Table[Player].ship1[i].y);
			}
		}
		for(i = 0; i < 3; i++)//ship (size 2)
		{
			if(P_Table[Player].ship2[i].on == 1)
			{
				SelectMenu_Ship2(hDC,x,y,P_Table[Player].ship2[i].x,P_Table[Player].ship2[i].y,P_Table[Player].ship2[i].rotate);
			}
		}
		for(i = 0; i < 2; i++)//ship (size 3)
		{
			if(P_Table[Player].ship3[i].on == 1)
			{
				SelectMenu_Ship3(hDC,x,y,P_Table[Player].ship3[i].x,P_Table[Player].ship3[i].y,P_Table[Player].ship3[i].rotate);
			}
		}
		if(P_Table[Player].ship4.on == 1)//ship (size 4)
		{
			SelectMenu_Ship4(hDC,x,y,P_Table[Player].ship4.x,P_Table[Player].ship4.y,P_Table[Player].ship4.rotate);
		}
	}

	//Ship hit
	for(j = 0; j < 10; j++)
	{
		for(i = 0; i < 10; i++)
		{
			if(P_Table[Player].ActiveTable[i][j] == 1)
			{
				if(P_Table[Player].PlacedShipTable[i][j] == 1){SelectMenu_HitShot(hDC,x-1,y-1,i+1,j+1);}
			}
		}
	}
}


void GameMSG(HDC hDC)
{
	//Font & Text
	RECT rt;
	rt.top = 10;rt.bottom = 100;
	rt.left = 100; rt.right = 950;
	
	SetTextColor(hDC,RGB(10,100,160));
	
	HFONT hFontText = CreateFont(40,0,0,0,FW_BOLD,true,FALSE,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_SWISS,"Arial");
	HFONT hFont = (HFONT)SelectObject(hDC,hFontText);
	
	SetBkMode(hDC,TRANSPARENT);
	
	char Text[][100] = {"Single Player","Multiplayer","Wait for opponent"};
	
	if(bInGame) DrawText(hDC, Text[iGameMode], strlen(Text[iGameMode]), &rt, DT_CENTER);
	else TextOut(hDC,200,30,Text[iGameMode],strlen(Text[iGameMode]));
	
	DeleteObject(SelectObject(hDC,hFont));
	
	if(Connecting_ON)
	{
		SetTextColor(hDC,RGB(10,100,160));
		
		HFONT hFontText2 = CreateFont(60,0,0,0,FW_BOLD,true,FALSE,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_SWISS,"Arial");
		HFONT hFont2 = (HFONT)SelectObject(hDC,hFontText2);
		
		SetBkMode(hDC,TRANSPARENT);
		
		TextOut(hDC,350,210,"Connecting...",13);
		
		DeleteObject(SelectObject(hDC,hFont2));
	}
	if(bWaitForClient)
	{
		SetTextColor(hDC,RGB(60,130,90));
		
		HFONT hFontText2 = CreateFont(28,0,0,0,FW_BOLD,true,FALSE,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_SWISS,"Arial");
		HFONT hFont2 = (HFONT)SelectObject(hDC,hFontText2);
		
		SetBkMode(hDC,TRANSPARENT);
		
		TextOut(hDC,200,510,Text[2],strlen(Text[2]));
		
		DeleteObject(SelectObject(hDC,hFont2));
	}
	
	if(bInGame)
	{
		SelectMenu_InGame_DrowTable(hDC,100,100,"Opponent",0,true,iEndOfGame_HiheShip);
		SelectMenu_InGame_DrowTable(hDC,550,100,"You",1,false,false);

		SetTextColor(hDC,RGB(10,100,160));
		
		HFONT hFontText2 = CreateFont(20,8,0,0,FW_BOLD,false,FALSE,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_SWISS,"Arial");
		HFONT hFont2 = (HFONT)SelectObject(hDC,hFontText2);
		
		SetBkMode(hDC,TRANSPARENT);
		
		char Text2[][100] = {"Opponent's move","Your move"," ","Wait"};
		
		TextOut(hDC,560,525,Text2[(bWaitForClient?2:iMyTurn)],strlen(Text2[(bWaitForClient?2:iMyTurn)]));
		
		DeleteObject(SelectObject(hDC,hFont2));

		if(iMyTurn == 2)
		{
			SetTextColor(hDC, (iWinGame?RGB(10,200,10):RGB(200,10,10)) );
		
			HFONT hFontText3 = CreateFont(80,0,0,0,FW_BOLD,false,FALSE,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_SWISS,"Arial");
			HFONT hFont3 = (HFONT)SelectObject(hDC,hFontText3);
			
			SetBkMode(hDC,TRANSPARENT);
			
			int n = (iWinGame?0:1);
			char Text3[][100] = {"You Win!","You Lost!"};
			
			TextOut(hDC,120,500,Text3[n],strlen(Text3[n]));
			
			DeleteObject(SelectObject(hDC,hFont3));
		}
	}
	else if(bShipSelection)
	{
		SelectMenu_Table(hDC);
		SelectMenu_ShipSelection_DrowTable(hDC,200,100);
	}
}