void GSM_Table_DeactiveRedraw(int X, int Y, int x, int y, char ship_size,bool Rotate, void (*func)(int,int,int,int))
{
	//X,Y : Table position
	//x,y : Selected slot position
	int i,_x,_y,size = 0;
	
	if		(ship_size == 1) size = 8;
	else if (ship_size == 2) size = 11;
	else if (ship_size == 3) size = 14;
	else if (ship_size == 4) size = 17;
	
	func(X,Y,x,y);
	
	for(i = 0; i < size; i++)
	{
		if		(i == 0){_x = x-1; _y = y;}
		else if (i == 1){_x = x+1; _y = y;}
		else if (i == 2){_x = x-1; _y = y-1;}
		else if (i == 3){_x = x+1; _y = y-1;}
		else if (i == 4){_x = x-1; _y = y+1;}
		else if (i == 5){_x = x+1; _y = y+1;}
		else if (i == 6){_x = x; _y = y-1;}
		else if (i == 7){_x = x; _y = y+1;}
		else if (Rotate)
		{
			if		(i ==  8){_x = x+2; _y = y;}
			else if (i ==  9){_x = x+2; _y = y-1;}
			else if (i == 10){_x = x+2; _y = y+1;}
			else if (i == 11){_x = x+3; _y = y;}
			else if (i == 12){_x = x+3; _y = y-1;}
			else if (i == 13){_x = x+3; _y = y+1;}
			else if (i == 14){_x = x+4; _y = y;}
			else if (i == 15){_x = x+4; _y = y-1;}
			else if (i == 16){_x = x+4; _y = y+1;}
		}
		else
		{
			if		(i ==  8){_x = x; _y = y+2;}
			else if (i ==  9){_x = x-1; _y = y+2;}
			else if (i == 10){_x = x+1; _y = y+2;}
			else if (i == 11){_x = x; _y = y+3;}
			else if (i == 12){_x = x-1; _y = y+3;}
			else if (i == 13){_x = x+1; _y = y+3;}
			else if (i == 14){_x = x; _y = y+4;}
			else if (i == 15){_x = x-1; _y = y+4;}
			else if (i == 16){_x = x+1; _y = y+4;}
		}
		if(_x >= 0 && _x < 10 && _y >= 0 && _y < 10)
		{
			func(X,Y,_x,_y);
		}
	}
}

void GSM_ShipSelection(HWND W, int TablePosX, int TablePosY, LPARAM lParam)
{
	int x = TablePosX+1;
	int y = TablePosY+1;
	int X = LOWORD(lParam);
	int Y = HIWORD(lParam);
	int pos_x = 0;
	int pos_y = 0;
	int n = (iSelected_Ship > 0 && iSelected_Ship < 4?5-iSelected_Ship:1);
	
	//Select Table
	if(X >= x && X < x+400 && Y >= y && Y < y+400)
	{
		pos_x = (X-x)/40 + 1;
		pos_y = (Y-y)/40 + 1;
		iParamA = 2;
		iParamB = pos_x*100 + pos_y;
	}
	else if(X >= x+505 && X < x+505+160 && Y >= y+15 && Y < y+15+160)//Select Ship
	{
		pos_y = (Y-y-15)/40 + 1;
		iParamA = 1;
		iParamB = pos_y;
	}
	else
	{
		iParamA = iParamB = 0;
	}
	
	//Redraw
	if(iParamB*10+iParamA != iMemParam && iMyTurn != 2)
	{
		//Select Ship
		if(!bInGame)
		{
			if(iMemParam%10 == 1)
			{
				RedrawTable(W,x+505+40 + ((iMemParam/10)/100-1)*40,y+15 + ((iMemParam/10)%100-1)*40,4);
			}
			if(iParamA == 1)
			{
				RedrawTable(W,x+505+40 + (pos_x-1)*40,y+15 + (pos_y-1)*40,4);
			}
		}
		
		//Place ship
		if( (iSelected_Ship == 1 && iShipRemains[0] == 0) ||
			(iSelected_Ship == 2 && iShipRemains[1] == 0) ||
			(iSelected_Ship == 3 && iShipRemains[2] == 0) )
		{
			n = 1;
		}
		else if(iParamRotate)
		{
			if(iSelected_Ship == 1)
			{
				if(pos_x == 8){n = 3;}else if(pos_x == 9){n = 2;}else if(pos_x == 10){n = 1;}
			}
			else if(iSelected_Ship == 2)
			{
				if(pos_x == 9){n = 2;}else if(pos_x == 10){n = 1;}
			}
			else if(iSelected_Ship == 3)
			{
				if(pos_x == 10){n = 1;}
			}
		}
		else
		{
			if(iSelected_Ship == 1)
			{
				if(pos_y == 8){n = 3;}
				else if(pos_y == 9){n = 2;}
				else if(pos_y == 10){n = 1;}
			}
			else if(iSelected_Ship == 2)
			{
				if(pos_y == 9){n = 2;}
				else if(pos_y == 10){n = 1;}
			}
			else if(iSelected_Ship == 3)
			{
				if(pos_y == 10){n = 1;}
			}
		}
		
		if(iMemParam%10 == 2)
		{
			RedrawTable(W,x + ((iMemParam/10)/100-1)*40,y + ((iMemParam/10)%100-1)*40,(iParamRotate?n:1),(!iParamRotate?n:1));
		}
		if(iParamA == 2)
		{
			RedrawTable(W,x + (pos_x-1)*40,y + (pos_y-1)*40,(iParamRotate?n:1),(!iParamRotate?n:1));
		}
		
		//Redraw All Table
		if(!bInGame)
		{
			HDC hDC = GetDC(W);//Begin
			for(int j = 0; j < 10; j++)
			{
				for(int i = 0; i < 10; i++)
				{
					if (P_Table[0].ActiveTable[i][j] == 0 && GetPixel(hDC,x+i*40+20,y+j*40+20) != RGB(230,240,252))
					{
						RedrawTable(W,x+i*40,y+j*40);
					}
				}
			}
			ReleaseDC(W, hDC);//end
		}
		
		iMemParam = iParamB*10+iParamA;
	}
}

void GSM_TDR_DeactiveTable_P1(int X, int Y, int x, int y)
{
	P_Table[0].ActiveTable[x][y] = 1;
}
void GSM_TDR_Redraw(int X, int Y, int x, int y)
{
	RedrawTable(hWnd_Dlg,X+x*40,Y+y*40);
}

void GSM_ShipSelection_Action(int X, int Y, LPARAM lParam)
{
	if(iParamA == 1)//select type of ship
	{
		if(iParamB > 0 && iParamB < 5)
		{
			iSelected_Ship = iParamB;
			RedrawTable(hWnd_Dlg,X+1+505,Y+1+15,4,4);
		}
	}
	else if(iParamA == 2)//place a ship on the table
	{
		if(iSelected_Ship == 4 && iShipRemains[3] > 0)//ship (size 1)
		{
			int x = iParamB/100 - 1;
			int y = iParamB%100 - 1;
			if(x >= 0 && x < 10 && y >= 0 && y < 10 && P_Table[0].ActiveTable[x][y] == 0)
			{
				//Ship Select
				iShipRemains[3]--;
				P_Table[0].ship1[iShipRemains[3]].x = x+1;
				P_Table[0].ship1[iShipRemains[3]].y = y+1;
				P_Table[0].ship1[iShipRemains[3]].on = 1;
				
				//Deactive Table
				GSM_Table_DeactiveRedraw(X,Y,x,y,1,0,GSM_TDR_DeactiveTable_P1);
				
				//Redraw
				GSM_Table_DeactiveRedraw(X,Y,x,y,1,0,GSM_TDR_Redraw);
			}
		}
		else if(iSelected_Ship == 3 && iShipRemains[2] > 0)//ship (size 2)
		{
			int i = 0;
			int x = iParamB/100 - 1;
			int y = iParamB%100 - 1;
			
			if(iParamRotate)
			{
				if(x+1 <= 9 && y+1 <= 10 && P_Table[0].ActiveTable[x+1][y] == 0) {i = 1;}
			}
			else
			{
				if(x+1 <= 10 && y+1 <= 9 && P_Table[0].ActiveTable[x][y+1] == 0) {i = 1;}
			}
			
			if(x >= 0 && x < 10 && y >= 0 && y < 10 && P_Table[0].ActiveTable[x][y] == 0 && i)
			{
				//Ship Select
				iShipRemains[2]--;
				P_Table[0].ship2[iShipRemains[2]].x = x+1;
				P_Table[0].ship2[iShipRemains[2]].y = y+1;
				P_Table[0].ship2[iShipRemains[2]].on = 1;
				P_Table[0].ship2[iShipRemains[2]].rotate = iParamRotate;

				//Deactive Table
				GSM_Table_DeactiveRedraw(X,Y,x,y,2,iParamRotate,GSM_TDR_DeactiveTable_P1);
				
				//Redraw
				GSM_Table_DeactiveRedraw(X,Y,x,y,2,iParamRotate,GSM_TDR_Redraw);
			}
		}
		else if(iSelected_Ship == 2 && iShipRemains[1] > 0)//ship (size 3)
		{
			int i = 0;
			int x = iParamB/100 - 1;
			int y = iParamB%100 - 1;
			
			if(iParamRotate)
			{
				if(x+1 <= 8 && y+1 <= 10 && P_Table[0].ActiveTable[x+1][y] == 0 
										 && P_Table[0].ActiveTable[x+2][y] == 0) {i = 1;}
			}
			else
			{
				if(x+1 <= 10 && y+1 <= 8 && P_Table[0].ActiveTable[x][y+1] == 0
										 && P_Table[0].ActiveTable[x][y+2] == 0) {i = 1;}
			}
			
			if(x >= 0 && x < 10 && y >= 0 && y < 10 && P_Table[0].ActiveTable[x][y] == 0 && i)
			{
				//Ship Select
				iShipRemains[1]--;
				P_Table[0].ship3[iShipRemains[1]].x = x+1;
				P_Table[0].ship3[iShipRemains[1]].y = y+1;
				P_Table[0].ship3[iShipRemains[1]].on = 1;
				P_Table[0].ship3[iShipRemains[1]].rotate = iParamRotate;

				//Deactive Table
				GSM_Table_DeactiveRedraw(X,Y,x,y,3,iParamRotate,GSM_TDR_DeactiveTable_P1);
				
				//Redraw
				GSM_Table_DeactiveRedraw(X,Y,x,y,3,iParamRotate,GSM_TDR_Redraw);
			}
		}
		else if(iSelected_Ship == 1 && iShipRemains[0] > 0)//ship (size 4)
		{
			int i = 0;
			int x = iParamB/100 - 1;
			int y = iParamB%100 - 1;
			
			if(iParamRotate)
			{
				if(x+1 <= 7 && y+1 <= 10 && P_Table[0].ActiveTable[x+1][y] == 0 
										 && P_Table[0].ActiveTable[x+2][y] == 0 
										 && P_Table[0].ActiveTable[x+3][y] == 0) {i = 1;}
			}
			else
			{
				if(x+1 <= 10 && y+1 <= 7 && P_Table[0].ActiveTable[x][y+1] == 0
										 && P_Table[0].ActiveTable[x][y+2] == 0
										 && P_Table[0].ActiveTable[x][y+3] == 0) {i = 1;}
			}
			
			if(x >= 0 && x < 10 && y >= 0 && y < 10 && P_Table[0].ActiveTable[x][y] == 0 && i)
			{
				//Ship Select
				iShipRemains[0]--;
				P_Table[0].ship4.x = x+1;
				P_Table[0].ship4.y = y+1;
				P_Table[0].ship4.on = 1;
				P_Table[0].ship4.rotate = iParamRotate;
				
				//Deactive Table
				GSM_Table_DeactiveRedraw(X,Y,x,y,4,iParamRotate,GSM_TDR_DeactiveTable_P1);
				
				//Redraw
				GSM_Table_DeactiveRedraw(X,Y,x,y,4,iParamRotate,GSM_TDR_Redraw);
			}
		}
		//Redraw
		RECT r;
		r.left = X+1+500-40; r.right = X+1+500;
		r.top = Y+1+15; r.bottom = Y+1+15+40*4;
		InvalidateRect(hWnd_Dlg,&r,true);//Refresh
		
		//Enable start
		if(iShipRemains[0] == 0 && iShipRemains[1] == 0 && iShipRemains[2] == 0 && iShipRemains[3] == 0)
		{
			EnableWindow(GetDlgItem(hWnd_Dlg,GetMenuButtonID(GM_SINGLEPLAYER_ID,GM_SINGLEPLAYER_MAX,"Start Game")),true);
		}
	}
}

void GSM_ShipSel_Rotate(HWND W)
{
	if( (iSelected_Ship == 3 && iShipRemains[2] > 0) ||
		(iSelected_Ship == 2 && iShipRemains[1] > 0) ||
		(iSelected_Ship == 1 && iShipRemains[0] > 0))
	{
		int x = iParamB/100 - 1;
		int y = iParamB%100 - 1;
		int n = 5-iSelected_Ship;
		iParamRotate = !iParamRotate;
		RedrawTable(W,200+x*40,100+y*40,n,n);
	}
}

void GSM_RandomShip(int Player)
{
	int n,i,j,x,y,X = 200,Y = 100;

	for(i = 0; i < 4; i++)
	{
		if(iShipRemains[3] <= 0) break;
		j = 0;
		x = rand()%10;
		y = rand()%10;
		
		do
		{
			if(x >= 0 && x < 10 && y >= 0 && y < 10 && P_Table[Player].ActiveTable[x][y] == 0)
			{
				//Ship Select
				iShipRemains[3]--;
				P_Table[Player].ship1[iShipRemains[3]].x = x+1;
				P_Table[Player].ship1[iShipRemains[3]].y = y+1;
				P_Table[Player].ship1[iShipRemains[3]].on = 1;
				
				//Deactive Table
				GSM_Table_DeactiveRedraw(X,Y,x,y,1,0,GSM_TDR_DeactiveTable_P1);
				break;
			}
			else
			{
				if(x < 9){x++;}else if(y < 9){y++;x = 0;}else{y = x = 0;}
			}
		}
		while(j < 1000);
	}

	for(i = 0; i < 3; i++)
	{
		if(iShipRemains[2] <= 0) break;
		j = 0;
		x = rand()%10;
		y = rand()%10;
		iParamRotate = (rand()%2?false:true);
		
		do
		{
			
			n = 0;
			if(iParamRotate)
			{
				if(x+1 <= 9 && y+1 <= 10 && P_Table[Player].ActiveTable[x+1][y] == 0) {n = 1;}
			}
			else
			{
				if(x+1 <= 10 && y+1 <= 9 && P_Table[Player].ActiveTable[x][y+1] == 0) {n = 1;}
			}
			
			if(x >= 0 && x < 10 && y >= 0 && y < 10 && P_Table[Player].ActiveTable[x][y] == 0 && n)
			{
				//Ship Select
				iShipRemains[2]--;
				P_Table[Player].ship2[iShipRemains[2]].x = x+1;
				P_Table[Player].ship2[iShipRemains[2]].y = y+1;
				P_Table[Player].ship2[iShipRemains[2]].on = 1;
				P_Table[Player].ship2[iShipRemains[2]].rotate = iParamRotate;

				//Deactive Table
				GSM_Table_DeactiveRedraw(X,Y,x,y,2,iParamRotate,GSM_TDR_DeactiveTable_P1);
				break;
			}
			else
			{
				if(x < 9){x++;}else if(y < 9){y++;x = 0;}else{y = x = 0;if(j++ > 0 && j%2 == 0){iParamRotate = !iParamRotate;}}
			}
		}
		while(j < 1000);
	}

	for(i = 0; i < 2; i++)
	{
		if(iShipRemains[1] <= 0) break;
		j = 0;
		x = rand()%10;
		y = rand()%10;
		iParamRotate = (rand()%2?false:true);
		
		do
		{
			n = 0;
			if(iParamRotate)
			{
				if(x+1 <= 8 && y+1 <= 10 && P_Table[Player].ActiveTable[x+1][y] == 0 
										 && P_Table[Player].ActiveTable[x+2][y] == 0) {n = 1;}
			}
			else
			{
				if(x+1 <= 10 && y+1 <= 8 && P_Table[Player].ActiveTable[x][y+1] == 0
										 && P_Table[Player].ActiveTable[x][y+2] == 0) {n = 1;}
			}
			
			if(x >= 0 && x < 10 && y >= 0 && y < 10 && P_Table[Player].ActiveTable[x][y] == 0 && n)
			{
				//Ship Select
				iShipRemains[1]--;
				P_Table[Player].ship3[iShipRemains[1]].x = x+1;
				P_Table[Player].ship3[iShipRemains[1]].y = y+1;
				P_Table[Player].ship3[iShipRemains[1]].on = 1;
				P_Table[Player].ship3[iShipRemains[1]].rotate = iParamRotate;

				//Deactive Table
				GSM_Table_DeactiveRedraw(X,Y,x,y,3,iParamRotate,GSM_TDR_DeactiveTable_P1);
				break;
			}
			else
			{
				if(x < 9){x++;}else if(y < 9){y++;x = 0;}else{y = x = 0;if(j++ > 0 && j%2 == 0){iParamRotate = !iParamRotate;}}
			}
		}
		while(j < 1000);
	}
	
	if(iShipRemains[0] > 0)
	{
		j = 0;
		x = rand()%10;
		y = rand()%10;
		iParamRotate = (rand()%2?false:true);
		
		do
		{
			n = 0;
			if(iParamRotate)
			{
				if(x+1 <= 7 && y+1 <= 10 && P_Table[Player].ActiveTable[x+1][y] == 0 
										 && P_Table[Player].ActiveTable[x+2][y] == 0 
										 && P_Table[Player].ActiveTable[x+3][y] == 0) {n = 1;}
			}
			else
			{
				if(x+1 <= 10 && y+1 <= 7 && P_Table[Player].ActiveTable[x][y+1] == 0
										 && P_Table[Player].ActiveTable[x][y+2] == 0
										 && P_Table[Player].ActiveTable[x][y+3] == 0) {n = 1;}
			}
			
			if(x >= 0 && x < 10 && y >= 0 && y < 10 && P_Table[Player].ActiveTable[x][y] == 0 && n)
			{
				//Ship Select
				iShipRemains[0]--;
				P_Table[Player].ship4.x = x+1;
				P_Table[Player].ship4.y = y+1;
				P_Table[Player].ship4.on = 1;
				P_Table[Player].ship4.rotate = iParamRotate;
				
				//Deactive Table
				GSM_Table_DeactiveRedraw(X,Y,x,y,4,iParamRotate,GSM_TDR_DeactiveTable_P1);
				break;
			}
			else
			{
				if(x < 9){x++;}else if(y < 9){y++;x = 0;}else{y = x = 0;if(j++ > 0 && j%2 == 0){iParamRotate = !iParamRotate;}}
			}
		}
		while(j < 1000);
	}
}

void GSM_Generate_PlacedShipTable(int Player)
{
	int i,x,y;
	for(i = 0; i < 4; i++)
	{
		x = P_Table[Player].ship1[i].x-1;
		y = P_Table[Player].ship1[i].y-1;
		P_Table[Player].PlacedShipTable[x][y] = 1;
	}
	for(i = 0; i < 3; i++)
	{
		x = P_Table[Player].ship2[i].x-1;
		y = P_Table[Player].ship2[i].y-1;
		P_Table[Player].PlacedShipTable[x][y] = 1;
		if(P_Table[Player].ship2[i].rotate)
		{
			P_Table[Player].PlacedShipTable[x+1][y] = 1;
		}
		else
		{
			P_Table[Player].PlacedShipTable[x][y+1] = 1;
		}
	}
	for(i = 0; i < 2; i++)
	{
		x = P_Table[Player].ship3[i].x-1;
		y = P_Table[Player].ship3[i].y-1;
		P_Table[Player].PlacedShipTable[x][y] = 1;
		if(P_Table[Player].ship3[i].rotate)
		{
			P_Table[Player].PlacedShipTable[x+1][y] = 1;
			P_Table[Player].PlacedShipTable[x+2][y] = 1;
		}
		else
		{
			P_Table[Player].PlacedShipTable[x][y+1] = 1;
			P_Table[Player].PlacedShipTable[x][y+2] = 1;
		}
	}
	x = P_Table[Player].ship4.x-1;
	y = P_Table[Player].ship4.y-1;
	P_Table[Player].PlacedShipTable[x][y] = 1;
	if(P_Table[Player].ship4.rotate)
	{
		P_Table[Player].PlacedShipTable[x+1][y] = 1;
		P_Table[Player].PlacedShipTable[x+2][y] = 1;
		P_Table[Player].PlacedShipTable[x+3][y] = 1;
	}
	else
	{
		P_Table[Player].PlacedShipTable[x][y+1] = 1;
		P_Table[Player].PlacedShipTable[x][y+2] = 1;
		P_Table[Player].PlacedShipTable[x][y+3] = 1;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//****************************************************************************************************//
////////////////////////////////////////////////////////////////////////////////////////////////////////

//AI
void AI_Start()
{
	memset((char*)AI_var.ActiveTable,0,sizeof(AI_var.ActiveTable));
	AI_var.FirstHitting = false;
	AI_var.SmartTable = true;
	AI_var.big_ship = 6;
	AI_var.ship4_on = 1;
	AI_var.ship3_on[0] = AI_var.ship3_on[1] = 1;
	AI_var.ship2_on[0] = AI_var.ship2_on[1] = AI_var.ship2_on[2] = 1;
	AI_var.ship1_on[0] = AI_var.ship1_on[1] = AI_var.ship1_on[2]= AI_var.ship1_on[3] = 1;
	AI_var.big_ship4destroyed = 1;
	AI_var.big_ship3destroyed = 2;
}
void AI_SetBox(int x, int y)
{
	int i,j,X,Y;
	AI_var.hv = 0;
	AI_var.x[0] = AI_var.x[1] = -1;
	memset((char*)AI_var.pos,0,sizeof(AI_var.pos));
	
	for(j = 0; j < 4; j++)
	{
		for(i = 0; i < 3; i++)
		{
			if		(j == 0){X = x-1-i;	Y = y;}
			else if (j == 1){X = x+1+i;	Y = y;}
			else if (j == 2){X = x;		Y = y-1-i;}
			else if (j == 3){X = x;		Y = y+1+i;}
			
			if(X >= 0 && X < 10 && Y >= 0 && Y < 10)
			{
				if(AI_var.ActiveTable[X][Y] == 0)
				{
					AI_var.pos[j].x[i] = X;
					AI_var.pos[j].y[i] = Y;
					AI_var.pos[j].on[i] = 1;
				}else{break;}
			}else{break;}
		}
	}
}
bool AI_SetCoordinate_seek(int n, int & x, int & y)
{
	bool ON = false,set = true,m = true;
	int i,j,X,Y;
	for(j = i = 0; i < 3; i++)
	{
		if(AI_var.pos[n].on[i])
		{
			X = AI_var.pos[n].x[i];
			Y = AI_var.pos[n].y[i];
			if(set) {x = X; y = Y; set = false;}
			AI_var.pos[n].on[i] = 0;
			
			if(P_Table[1].PlacedShipTable[X][Y] == 1 && m)
			{
				AI_var.hv = (n<2?1:2);
				if(i > 0)
				{
					AI_var.x[j] = AI_var.pos[n].x[i];
					AI_var.y[j] = AI_var.pos[n].y[i];
					j++;
				}
			}
			else if(m)
			{
				if(i > 0)
				{
					AI_var.x[j] = AI_var.pos[n].x[i];
					AI_var.y[j] = AI_var.pos[n].y[i];
					j++;
				}
				m = false;
			}
		}
		else{if(i == 0){ON = true;}break;}
	}
	return ON;
}
void AI_SetCoordinate(int & x, int & y)
{
	bool on = false;
	int n = rand()%4;
	if(AI_var.x[0] != -1)
	{
		x = AI_var.x[0];
		y = AI_var.y[0];
		AI_var.x[0] = -1;
	}
	else if(AI_var.x[1] != -1)
	{
		x = AI_var.x[1];
		y = AI_var.y[1];
		AI_var.x[1] = -1;
	}
	else
	{
		if(AI_var.hv)
		{
			if(AI_var.hv == 1)//1=horizontal
			{
				if(AI_SetCoordinate_seek(0,x,y))
				{
					if(AI_SetCoordinate_seek(1,x,y)){on = true;}
				}
			}
			else//2=vertical
			{
				
				if(AI_SetCoordinate_seek(2,x,y))
				{
					if(AI_SetCoordinate_seek(3,x,y)){on = true;}
				}
			}
		}
		else if(AI_SetCoordinate_seek(n,x,y))
		{
			if(AI_SetCoordinate_seek(0,x,y))
			{
				if(AI_SetCoordinate_seek(1,x,y))
				{
					if(AI_SetCoordinate_seek(2,x,y))
					{
						if(AI_SetCoordinate_seek(3,x,y)){on = true;}
					}
				}
			}
		}
	}
	if(on)
	{
		AI_var.FirstHitting = false;
	}
}
void AI_BegEndHit(int X, int Y, bool & b)
{
	if(X >= 0 && X < 10 && Y >= 0 && Y < 10)
	{
		if(P_Table[1].ActiveTable[X][Y] == 1){b = true;}
	}else{b = true;}
}
void GSM_TDR_DeactiveTable_AI(int X, int Y, int x, int y)
{
	AI_var.ActiveTable[x][y] = 1;
}
void AI_ReorientatedTable()
{
	int x,y,i;
	bool on,beg,end;
	
	if(AI_var.big_ship > 0 && AI_var.difficulty <= 1)
	{
		for(i = 0; i < 4 && AI_var.difficulty == 0; i++)
		{
			bool up = false,down = false,left = false,right = false;
			x = P_Table[1].ship1[i].x - 1;
			y = P_Table[1].ship1[i].y - 1;
			if(P_Table[1].PlacedShipTable[x][y] == 1 && AI_var.ActiveTable[x][y] == 1 && AI_var.ship1_on[i])
			{
				AI_BegEndHit(x,y-1,up);
				AI_BegEndHit(x,y+1,down);
				AI_BegEndHit(x-1,y,left);
				AI_BegEndHit(x+1,y,right);
				
				if(up && down && left && right)
				{
					GSM_Table_DeactiveRedraw(550,100,x,y,1,0,GSM_TDR_DeactiveTable_AI);
					AI_var.ship1_on[i] = 0;
				}
			}
		}
		
		for(i = 0; i < 3; i++)
		{
			x = P_Table[1].ship2[i].x - 1;
			y = P_Table[1].ship2[i].y - 1;
			if(P_Table[1].PlacedShipTable[x][y] == 1 && AI_var.ActiveTable[x][y] == 1 && AI_var.ship2_on[i])
			{
				beg = end = on = false;
				if(P_Table[1].ship2[i].rotate)
				{
					if(AI_var.big_ship4destroyed > 0 || AI_var.big_ship3destroyed > 0)
					{
						AI_BegEndHit(x-1,y,beg);
						AI_BegEndHit(x+2,y,end);
					}else{beg = end = true;}
					if (P_Table[1].PlacedShipTable[x+1][y] == 1 && AI_var.ActiveTable[x+1][y] == 1 && beg && end){on = true;}
				}
				else
				{
					if(AI_var.big_ship4destroyed > 0 || AI_var.big_ship3destroyed > 0)
					{
						AI_BegEndHit(x,y-1,beg);
						AI_BegEndHit(x,y+2,end);
					}else{beg = end = true;}
					if (P_Table[1].PlacedShipTable[x][y+1] == 1 && AI_var.ActiveTable[x][y+1] == 1 && beg && end){on = true;}
				}
				if(on)
				{
					GSM_Table_DeactiveRedraw(550,100,x,y,2,P_Table[1].ship2[i].rotate,GSM_TDR_DeactiveTable_AI);
					AI_var.ship2_on[i] = 0;
					AI_var.big_ship--;
				}
			}
		}
		
		for(i = 0; i < 2; i++)
		{
			x = P_Table[1].ship3[i].x - 1;
			y = P_Table[1].ship3[i].y - 1;
			if(P_Table[1].PlacedShipTable[x][y] == 1 && AI_var.ActiveTable[x][y] == 1 && AI_var.ship3_on[i])
			{
				beg = end = on = false;
				if(P_Table[1].ship3[i].rotate)
				{
					if(AI_var.big_ship4destroyed > 0)
					{
						AI_BegEndHit(x-1,y,beg);
						AI_BegEndHit(x+3,y,end);
					}else{beg = end = true;}
					if (P_Table[1].PlacedShipTable[x+1][y] == 1 && AI_var.ActiveTable[x+1][y] == 1 &&
						P_Table[1].PlacedShipTable[x+2][y] == 1 && AI_var.ActiveTable[x+2][y] == 1 && beg && end){on = true;}
				}
				else
				{
					if(AI_var.big_ship4destroyed > 0)
					{
						AI_BegEndHit(x,y-1,beg);
						AI_BegEndHit(x,y+3,end);
					}else{beg = end = true;}
					if (P_Table[1].PlacedShipTable[x][y+1] == 1 && AI_var.ActiveTable[x][y+1] == 1 &&
						P_Table[1].PlacedShipTable[x][y+2] == 1 && AI_var.ActiveTable[x][y+2] == 1 && beg && end){on = true;}
				}
				if(on)
				{
					GSM_Table_DeactiveRedraw(550,100,x,y,3,P_Table[1].ship3[i].rotate,GSM_TDR_DeactiveTable_AI);
					AI_var.ship3_on[i] = 0;
					AI_var.big_ship--;
					AI_var.big_ship3destroyed--;
				}
			}
		}
		
		x = P_Table[1].ship4.x - 1;
		y = P_Table[1].ship4.y - 1;
		if(P_Table[1].PlacedShipTable[x][y] == 1 && AI_var.ActiveTable[x][y] == 1 && AI_var.ship4_on)
		{
			on = false;
			if(P_Table[1].ship4.rotate)
			{
				if (P_Table[1].PlacedShipTable[x+1][y] == 1 && AI_var.ActiveTable[x+1][y] == 1 &&
					P_Table[1].PlacedShipTable[x+2][y] == 1 && AI_var.ActiveTable[x+2][y] == 1 &&
					P_Table[1].PlacedShipTable[x+3][y] == 1 && AI_var.ActiveTable[x+3][y] == 1){on = true;}
			}
			else
			{
				if (P_Table[1].PlacedShipTable[x][y+1] == 1 && AI_var.ActiveTable[x][y+1] == 1 &&
					P_Table[1].PlacedShipTable[x][y+2] == 1 && AI_var.ActiveTable[x][y+2] == 1 &&
					P_Table[1].PlacedShipTable[x][y+3] == 1 && AI_var.ActiveTable[x][y+3] == 1){on = true;}
			}
			if(on)
			{
				GSM_Table_DeactiveRedraw(550,100,x,y,4,P_Table[1].ship4.rotate,GSM_TDR_DeactiveTable_AI);
				AI_var.ship4_on = 0;
				AI_var.big_ship--;
				AI_var.big_ship4destroyed--;
			}
		}
	}
	else if(AI_var.difficulty == 0)
	{
		for(i = 0; i < 4; i++)
		{
			x = P_Table[1].ship1[i].x - 1;
			y = P_Table[1].ship1[i].y - 1;
			if(P_Table[1].PlacedShipTable[x][y] == 1 && AI_var.ActiveTable[x][y] == 1 && AI_var.ship1_on[i])
			{
				GSM_Table_DeactiveRedraw(550,100,x,y,1,0,GSM_TDR_DeactiveTable_AI);
				AI_var.ship1_on[i] = 0;
			}
		}
	}
}
void AI_CheckReorientation()
{
	bool on = true;
	int i,j;
	for(j = 0; j < 10 && on; j++)
	{
		for(i = 0; i < 10 && on; i++)
		{
			if(AI_var.ActiveTable[i][j] == 0){on = false;}
		}
	}
	if(on)
	{
		AI_var.SmartTable = false;
		memcpy((char*)AI_var.ActiveTable,(char*)P_Table[1].ActiveTable,sizeof(AI_var.ActiveTable));
	}
}

void AI_ShipShot_Action()
{
	int j = 0;
	int x = rand()%10;
	int y = rand()%10;
	
	//P_Table[0]=Enemy
	//P_Table[1]=You
	do
	{
		if(AI_var.FirstHitting && AI_var.SmartTable && AI_var.big_ship > 0)
		{
			AI_SetCoordinate(x,y);
		}
		if(x >= 0 && x < 10 && y >= 0 && y < 10 && AI_var.ActiveTable[x][y] == 0)
		{
			if(P_Table[1].PlacedShipTable[x][y] > 0 && AI_var.SmartTable && AI_var.big_ship > 0 && AI_var.difficulty < 3)
			{
				if(!AI_var.FirstHitting){AI_var.FirstHitting = true;AI_SetBox(x,y);}
			}
			
			//Deactive Table
			AI_var.ActiveTable[x][y] = 1;
			P_Table[1].ActiveTable[x][y] = 1;
			if(AI_var.SmartTable && AI_var.difficulty < 2){AI_ReorientatedTable();}
			
			//test
			//memcpy((char*)P_Table[1].ActiveTable,(char*)AI_var.ActiveTable,sizeof(AI_var.ActiveTable));
			//InvalidateRect(hWnd_Dlg,0,true);//Refresh
			//test.end
			
			//Redraw
			RedrawTable(hWnd_Dlg,550+x*40,100+y*40);

			//Check Condition
			if(GSM_CheckCondition(1))
			{//enemy win
				iEndOfGame_HiheShip = false;
				iWinGame = false;
				iMyTurn = 2;
				GameMenu_Show(GM_EXIT_ID,2);
				GameMenu_MainMenu_Pos(true,750,530);
			}
			else
			{
				iMyTurn = 1;
				if(AI_var.SmartTable){AI_CheckReorientation();}
			}
			break;
		}
		else
		{
			if(x < 9){x++;}else if(y < 9){y++;x = 0;}else{y = x = 0;}
		}
	}
	while(j++ < 1000);
	
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
		RedrawTable(hWnd_Dlg,100+x*40,100+y*40);

		x = iParamB/100 - 1;
		y = iParamB%100 - 1;
		RedrawTable(hWnd_Dlg,100+x*40,100+y*40);
	}
}
//AI.End.

bool GSM_CheckCondition(int Player)
{
	bool ON = true;
	int i,j;
	for(j = 0; j < 10; j++)
	{
		for(i = 0; i < 10; i++)
		{
			if(P_Table[Player].PlacedShipTable[i][j] >= 1)
			{
				if(P_Table[Player].ActiveTable[i][j] == 0)
				{
					ON = false;
					break;
				}
			}
		}
	}
	return ON;
}

void GSM_ShipShot_Action(int X, int Y)
{
	if(iParamA == 2 && iMyTurn == 1 && !bWaitForClient)//your shot
	{
		int x = iParamB/100 - 1;
		int y = iParamB%100 - 1;
		//P_Table[0]=Enemy
		//P_Table[1]=You
		if(iGameMode == 0)//Single Player
		{
			if(x >= 0 && x < 10 && y >= 0 && y < 10 && P_Table[0].ActiveTable[x][y] == 0)
			{
				//Deactive Table
				P_Table[0].ActiveTable[x][y] = 1;
				
				//Redraw
				RedrawTable(hWnd_Dlg,X+x*40,Y+y*40);

				//Check Condition
				if(GSM_CheckCondition(0))
				{//you win
					iEndOfGame_HiheShip = false;
					iWinGame = true;
					iMyTurn = 2;
					GameMenu_Show(GM_EXIT_ID,2);
					GameMenu_MainMenu_Pos(true,750,530);
				}
				else
				{
					iMyTurn = 0;
					SetTimer(hWnd,101,200,0);
				}
			}
		}
		else//Multiplayer
		{
			if(x >= 0 && x < 10 && y >= 0 && y < 10 && P_Table[0].ActiveTable[x][y] == 0)
			{
				if(iServerClient == 1)//Server
				{
					//Deactive Table
					P_Table[0].ActiveTable[x][y] = 1;
					
					//Redraw
					RedrawTable(hWnd_Dlg,X+x*40,Y+y*40);

					//Check Condition
					if(GSM_CheckCondition(0))
					{//you win
						iEndOfGame_HiheShip = false;
						iWinGame = true;
						iMyTurn = 2;
						GameMenu_Show(GM_EXIT_ID,2);
						GameMenu_MainMenu_Pos(true,750,530);
						LAN_SendDataToClient(2,x,y,1);
					}
					else if(GSM_CheckCondition(1))
					{//you lost
						iEndOfGame_HiheShip = false;
						iWinGame = false;
						iMyTurn = 2;
						GameMenu_Show(GM_EXIT_ID,2);
						GameMenu_MainMenu_Pos(true,750,530);
						LAN_SendDataToClient(2,x,y,2);
					}
					else
					{
						iMyTurn = 0;
						LAN_SendDataToClient(2,x,y,0);
					}
				}
				else if(iServerClient == 2)//Client
				{
					iMyTurn = 0;
					//Redraw
					RedrawTable(hWnd_Dlg,X+x*40,Y+y*40);
					
					LAN_SendDataToServer(2,x,y);
				}
			}
		}
		
		
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