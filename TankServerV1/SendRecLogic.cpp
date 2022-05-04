#include "SendRecLogic.h"

BOOL SendRecLogic::posAdjust(unsigned char dir, int player)
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

bool SendRecLogic::lobby()
{
	return false;
}

bool SendRecLogic::generateWalls()
{
	return false;
}

bool SendRecLogic::generateTanks()
{
	return false;
}

bool SendRecLogic::generateMines()
{
	return false;
}

bool SendRecLogic::gameStart(char buff[22])
{
	p1Tank.topLeft.X = 200;
	p1Tank.topLeft.Y = 150;
	p1Tank.botRight.X = 200 + TANKSIZE;
	p1Tank.botRight.Y = 150 + TANKSIZE;

	p2Tank.topLeft.X = 600 - TANKSIZE;
	p2Tank.topLeft.Y = 450 - TANKSIZE;
	p2Tank.botRight.X = 600;
	p2Tank.botRight.Y = 450;

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

void SendRecLogic::sendUpdate()
{

}

void SendRecLogic::receiveUpdate(unsigned char p1Buffer[16], unsigned char p2Buffer[16], int time, unsigned char wrtBuffer[64])
{
	for (int i = 0; i < 16; i++)
	{
		if (p1Buffer[i] == 'M')
		{
			posAdjust(p1Buffer[i + 1], 1);
		}

		if (p2Buffer[i] == 'M')
		{
			posAdjust(p2Buffer[i + 1], 2);
		}



	}
}