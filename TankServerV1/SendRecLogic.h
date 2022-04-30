#ifndef SENDRECLOGIC_H
#define SENDRECLOGIC_H
#include "UDP.h"
#include <Windows.h>

struct Tank
{
	COORD topLeft;
	COORD botRight;
};

struct Wall
{
	COORD topLeft;
	COORD botRight;
};

struct Mine
{
	COORD loc;
	BOOL alive;
};

const int TANKSIZE = 50;
const int MINBOUND = 5;
const int MAXYBOUND = 595;
const int MAXXBOUND = 795;

class SendRecLogic
{
private:
	unsigned char p1Points;
	unsigned char p2Points;
	Tank p1Tank;
	Tank p2Tank;

	BOOL posAdjust(unsigned char dir, int player);

public:
	bool lobby();
	bool generateWalls();
	bool generateTanks();
	bool generateMines();
	bool gameStart();

	void sendUpdate();
	void receiveUpdate(unsigned char p1Buffer[16], unsigned char p2Buffer[16], int time, unsigned char wrtBuff[64]);
};

#endif