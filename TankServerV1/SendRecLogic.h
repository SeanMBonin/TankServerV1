#ifndef SENDRECLOGIC_H
#define SENDRECLOGIC_H
#include "UDP.h"
#include <Windows.h>

union BS
{
	char b[2];
	short s;
};

struct Tank
{
	COORD topLeft;
	COORD botRight;
	char facing;
	char shotDir;
	BOOL shot;
	COORD shotLoc;
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

	BOOL posAdjust(char dir, int player);
	BOOL shotAdjust(int player);
	BOOL doFire(char dir, int player);

public:
	bool lobby();
	bool generateWalls();
	bool generateTanks(int player);
	bool generateMines();
	bool gameStart(char buff[22]);

	int results(char wrtBuffer[30], int player);
	void receiveUpdate(int player, char dir, int* time, char wrtBuff[30]);
};

#endif