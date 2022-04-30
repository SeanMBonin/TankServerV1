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

}

bool SendRecLogic::generateWalls()
{

}

bool SendRecLogic::generateTanks()
{

}

bool SendRecLogic::generateMines()
{

}

bool SendRecLogic::gameStart()
{

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