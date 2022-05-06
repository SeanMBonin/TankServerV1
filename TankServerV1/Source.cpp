#include <iostream>
#include <vector>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <string>

#include <thread>
#include <chrono>

#include "SendRecLogic.h"
#include "UDP.h"

const int BUF_SIZE = 64;

void timer(int* time, BOOL* start)
{
	while (!*start)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//Just waits until start is true
	}

	while (*time > 0)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << *time << std::endl;
		*time-= 1;

		if (*time <= 0)
		{
			std::cout << "Game Time Out!" << std::endl;
		}
	}
}

int main()
{
	int timeVal = 90;

	char buf[BUF_SIZE];
	bool loop = true, listen = false;
	BOOL run = true, start = false;

	std::thread timerTh(timer, &timeVal, &start);

	UDP udp(&timeVal, &start);
	udp.lobby(1, &run);

	timerTh.join();

	return 0;
}