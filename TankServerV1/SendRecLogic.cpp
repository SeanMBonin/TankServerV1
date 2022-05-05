#include "SendRecLogic.h"

BOOL SendRecLogic::posAdjust(char dir, int player)
{
	BOOL tankMove = true;
	Tank* adjTank = new Tank;
	if (player == 1)
	{
		adjTank = &p1Tank;
	}
	else
	{
		adjTank = &p2Tank;
	}

	switch (dir)
	{
	case 'w':
		if (adjTank->topLeft.Y > MINBOUND + 5)
		{
			adjTank->topLeft.Y -= 5;
			adjTank->botRight.Y -= 5;
		}
		else if (adjTank->topLeft.Y > MINBOUND)
		{
			adjTank->topLeft.Y = MINBOUND;
			adjTank->botRight.Y = MINBOUND + TANKSIZE;
		}
		else
		{
			delete adjTank;
			tankMove = false;
		}

		break;
		
	case 'a':
		if (adjTank->topLeft.X > MINBOUND + 5)
		{
			adjTank->topLeft.X -= 5;
			adjTank->botRight.X -= 5;
		}
		else if (adjTank->topLeft.Y > MINBOUND)
		{
			adjTank->topLeft.X = MINBOUND;
			adjTank->botRight.X = MINBOUND + TANKSIZE;
		}
		else
		{
			delete adjTank;
			tankMove = false;
		}

		break;

	case 's':
		if (adjTank->botRight.Y < MAXYBOUND - 5)
		{
			adjTank->topLeft.Y += 5;
			adjTank->botRight.Y += 5;
		}
		else if (adjTank->topLeft.Y < MAXYBOUND)
		{
			adjTank->topLeft.Y = MAXYBOUND + TANKSIZE;
			adjTank->botRight.Y = MAXYBOUND;
		}
		else
		{
			delete adjTank;
			tankMove = false;
		}

		break;

	case 'd':
		if (adjTank->botRight.X < MAXXBOUND - 5)
		{
			adjTank->topLeft.X += 5;
			adjTank->botRight.X += 5;
		}
		else if (adjTank->topLeft.X < MAXXBOUND)
		{
			adjTank->topLeft.X = MAXXBOUND + TANKSIZE;
			adjTank->botRight.X = MAXXBOUND;
		}
		else
		{
			delete adjTank;
			tankMove = false;
		}

		break;
	}

	delete adjTank;
	return tankMove;
}

BOOL SendRecLogic::shotAdjust(int player)
{
	Tank* adjTank = new Tank;
	Tank* collision = new Tank;

	if (player == 1)
	{
		adjTank = &p1Tank;
		collision = &p2Tank;
	}
	else
	{
		adjTank = &p2Tank;
		collision = &p1Tank;
	}

	switch (adjTank->shotDir)
	{
	case 'U':
		if (adjTank->shotLoc.Y >= MINBOUND)
		{
			adjTank->shotLoc.Y -= 5;
		}
		else
		{
			adjTank->shot = false;
			adjTank->shotLoc.Y = 0;
			adjTank->shotLoc.X = 0;
		}
		break;

	case 'L':
		if (adjTank->shotLoc.X >= MINBOUND)
		{
			adjTank->shotLoc.X -= 5;
		}
		else
		{
			adjTank->shot = false;
			adjTank->shotLoc.Y = 0;
			adjTank->shotLoc.X = 0;
		}
		break;

	case 'D':
		if (adjTank->shotLoc.Y <= MAXYBOUND)
		{
			adjTank->shotLoc.Y += 5;
		}
		else
		{
			adjTank->shot = false;
			adjTank->shotLoc.Y = 0;
			adjTank->shotLoc.X = 0;
		}
		break;

	case 'R':
		if (adjTank->shotLoc.X <= MAXXBOUND)
		{
			adjTank->shotLoc.X += 5;
		}
		else
		{
			adjTank->shot = false;
			adjTank->shotLoc.Y = 0;
			adjTank->shotLoc.X = 0;
		}
		break;
	}

	//The shot is within the enemy tanks collision zone
	if (adjTank->shotLoc.X >= collision->topLeft.X && adjTank->shotLoc.X <= collision->botRight.X
		&& adjTank->shotLoc.Y >= collision->topLeft.Y && adjTank->shotLoc.Y <= collision->botRight.Y)
	{
		adjTank->shot = false;
		adjTank->shotLoc.Y = 0;
		adjTank->shotLoc.X = 0;

		delete adjTank;
		delete collision;

		return true;
	}
	
	//no collision
	delete adjTank;
	delete collision;

	return false;
}

BOOL SendRecLogic::doFire(char dir, int player)
{
	Tank* adjTank = new Tank;
	if (player == 1)
	{
		adjTank = &p1Tank;
	}
	else
	{
		adjTank = &p2Tank;
	}

	adjTank->shot = true;

	//Depending on direction, place the shot in the middle and in front of tank
	switch (dir)
	{
	case 'U':
		adjTank->shotLoc.X = adjTank->topLeft.X + 25;
		adjTank->shotLoc.Y = adjTank->topLeft.Y - 1;
		break;

	case 'L':
		adjTank->shotLoc.X = adjTank->topLeft.X - 1;
		adjTank->shotLoc.Y = adjTank->topLeft.Y + 25;
		break;

	case 'D':
		adjTank->shotLoc.X = adjTank->topLeft.X + 25;
		adjTank->shotLoc.Y = adjTank->botRight.Y + 1;
		break;

	case 'R':
		adjTank->shotLoc.X = adjTank->botRight.X + 1;
		adjTank->shotLoc.Y = adjTank->topLeft.Y + 25;
		break;
	}
	delete adjTank;
	return true;
}

bool SendRecLogic::lobby()
{
	return false;
}

bool SendRecLogic::generateWalls()
{
	return false;
}

bool SendRecLogic::generateTanks(int player)
{
	Tank* adjTank = new Tank;

	if (player == 1)
	{
		p1Tank.topLeft.X = 200;
		p1Tank.topLeft.Y = 150;
		p1Tank.botRight.X = 200 + TANKSIZE;
		p1Tank.botRight.Y = 150 + TANKSIZE;
		p1Tank.facing = 'U';

		p2Points++;
	}
	else
	{
		p2Tank.topLeft.X = 600 - TANKSIZE;
		p2Tank.topLeft.Y = 450 - TANKSIZE;
		p2Tank.botRight.X = 600;
		p2Tank.botRight.Y = 450;
		p2Tank.facing = 'U';

		p1Points++;
	}


}

bool SendRecLogic::generateMines()
{
	return false;
}

bool SendRecLogic::gameStart(char buff[22])
{
	//For directions on what each wrtBuffer field is, refer to TankDoc.txt
	p1Tank.topLeft.X = 200;
	p1Tank.topLeft.Y = 150;
	p1Tank.botRight.X = 200 + TANKSIZE;
	p1Tank.botRight.Y = 150 + TANKSIZE;
	p1Tank.facing = 'U';

	p2Tank.topLeft.X = 600 - TANKSIZE;
	p2Tank.topLeft.Y = 450 - TANKSIZE;
	p2Tank.botRight.X = 600;
	p2Tank.botRight.Y = 450;
	p2Tank.facing = 'U';

	p1Points = 0;
	p2Points = 0;

	int time = 90;

	//push in all values that don't need to be modified
	buff[0] = 'P';
	buff[1] = '1';
	buff[6] = 'U';
	buff[7] = 'P';
	buff[8] = '2';
	buff[13] = 'U';
	buff[14] = 'T';
	buff[15] = time;
	buff[16] = 'S';
	buff[17] = '1';
	buff[18] = 0;
	buff[19] = '2';
	buff[20] = 0;
	buff[21] = 'F';
	buff[22] = 0;
	buff[23] = 0;
	buff[24] = 0;
	buff[25] = 0;
	buff[26] = 0;
	buff[27] = 0;
	buff[28] = 0;
	buff[29] = 0;
	
	BS pos;
	pos.s = p1Tank.topLeft.X;
	buff[2] = pos.b[1];
	buff[3] = pos.b[0];

	pos.s = p1Tank.topLeft.Y;
	buff[4] = pos.b[1];
	buff[5] = pos.b[0];

	pos.s = p2Tank.topLeft.X;
	buff[9] = pos.b[1];
	buff[10] = pos.b[0];

	pos.s = p2Tank.topLeft.Y;
	buff[11] = pos.b[1];
	buff[12] = pos.b[0];
	
	return true;
}

int SendRecLogic::results(char wrtBuffer[30], int player)
{
	if (player == 1)
	{
		if (p1Points > p2Points)
		{
			wrtBuffer[0] = 'R';
			wrtBuffer[1] = 'Y';
			wrtBuffer[2] = 'O';
			wrtBuffer[3] = 'U';
			wrtBuffer[4] = ' ';
			wrtBuffer[5] = 'W';
			wrtBuffer[6] = 'I';
			wrtBuffer[7] = 'N';
			wrtBuffer[8] = 0;
			return 9;
		}
		else
		{
			wrtBuffer[0] = 'R';
			wrtBuffer[1] = 'Y';
			wrtBuffer[2] = 'O';
			wrtBuffer[3] = 'U';
			wrtBuffer[4] = ' ';
			wrtBuffer[5] = 'L';
			wrtBuffer[6] = 'O';
			wrtBuffer[7] = 'S';
			wrtBuffer[8] = 'E';
			wrtBuffer[9] = 0;
			return 10;
		}
	}
	else
	{
		if (p2Points > p1Points)
		{
			wrtBuffer[0] = 'R';
			wrtBuffer[1] = 'Y';
			wrtBuffer[2] = 'O';
			wrtBuffer[3] = 'U';
			wrtBuffer[4] = ' ';
			wrtBuffer[5] = 'W';
			wrtBuffer[6] = 'I';
			wrtBuffer[7] = 'N';
			wrtBuffer[8] = 0;
			return 9;
		}
		else
		{
			wrtBuffer[0] = 'R';
			wrtBuffer[1] = 'Y';
			wrtBuffer[2] = 'O';
			wrtBuffer[3] = 'U';
			wrtBuffer[4] = ' ';
			wrtBuffer[5] = 'L';
			wrtBuffer[6] = 'O';
			wrtBuffer[7] = 'S';
			wrtBuffer[8] = 'E';
			wrtBuffer[9] = 0;
			return 10;
		}
	}
}

void SendRecLogic::receiveUpdate(int player, char dir, int* time, char wrtBuffer[30])
{
	//For directions on what each wrtBuffer field is, refer to TankDoc.txt
	if (dir == 'F')
	{
		if (player == 1)
		{
			if (!p1Tank.shot)
			{
				//do a fire
				doFire(p1Tank.facing, 1);
			}
		}
		else
		{
			if (!p2Tank.shot)
			{
				//do a fire
				doFire(p2Tank.facing, 2);
			}
		}
	}
	else
	{
		posAdjust(dir, player);
	}

		//If the shot from tank 1 collides with tank 2, respawn tank 2
		if (shotAdjust(1))
		{
			generateTanks(2);
		}

		if (shotAdjust(2))
		{
			generateTanks(1);
		}

		BS pos;
		pos.s = p1Tank.topLeft.X;
		wrtBuffer[2] = pos.b[1];
		wrtBuffer[3] = pos.b[0];

		pos.s = p1Tank.topLeft.Y;
		wrtBuffer[4] = pos.b[1];
		wrtBuffer[5] = pos.b[0];
		wrtBuffer[6] = p1Tank.facing;

		pos.s = p2Tank.topLeft.X;
		wrtBuffer[9] = pos.b[1];
		wrtBuffer[10] = pos.b[0];

		pos.s = p2Tank.topLeft.Y;
		wrtBuffer[11] = pos.b[1];
		wrtBuffer[12] = pos.b[0];
		wrtBuffer[13] = p2Tank.facing;

		wrtBuffer[15] = *time;
		wrtBuffer[18] = p1Points;
		wrtBuffer[20] = p2Points;
	
		if (p1Tank.shot)
		{
			pos.s = p1Tank.shotLoc.X;
			wrtBuffer[22] = pos.b[1];
			wrtBuffer[23] = pos.b[0];

			pos.s = p1Tank.shotLoc.Y;
			wrtBuffer[24] = pos.b[1];
			wrtBuffer[25] = pos.b[0];
		}
		else
		{
			for (int i = 22; i < 26; i++)
			{
				wrtBuffer[i] = 0;
			}
		}

		if (p2Tank.shot)
		{
			pos.s = p2Tank.shotLoc.X;
			wrtBuffer[26] = pos.b[1];
			wrtBuffer[27] = pos.b[0];

			pos.s = p2Tank.shotLoc.Y;
			wrtBuffer[28] = pos.b[1];
			wrtBuffer[29] = pos.b[0];
		}
		else
		{
			for (int i = 26; i < 30; i++)
			{
				wrtBuffer[i] = 0;
			}
		}

}