#include <iostream>
#include <vector>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <string>

#include <thread>
#include <chrono>

#include "SendRecLogic.h"
#include "UDP.h"

const int BUF_SIZE = 64;

void timer(int time)
{

	while (time > 0)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << timer << std::endl;
		time--;

		if (time < 0)
		{
			std::cout << "Blast OFF!" << std::endl;
		}
	}
}

int main()
{

	int timeVal = 90;

	char buf[BUF_SIZE];
	bool loop = true, listen = false;
	BOOL run = true;

	UDP udp;
	udp.lobby(1, &run);

	//timerTh.join();
	//loop = true;
	//listen = false;
	//listen = true;

	/*
	while (loop)
	{
		
		if (!listen)
		{
			std::cout << "Enter a message to send (or quit, or listen): ";
			std::cin.getline(buf, BUF_SIZE);

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(255, '\n');
			}
			
			//send(sock, buf, strlen(buf) + 1, 0);
			sendto(sock, buf, strlen(buf) + 1, 0, (sockaddr*)&addrP1, sizeof(addrP1));
			sendto(sock, buf, strlen(buf) + 1, 0, (sockaddr*)&addrP2, sizeof(addrP2));

/*			if (sockErrSnd == SOCKET_ERROR)
			{
				closesocket(sock);
				WSACleanup();
				std::cout << "Error connecting: " << WSAGetLastError() << std::endl;
				return 1;
			}

			if (!_stricmp(buf, "quit"))
			{
				loop = false;
			}

			if (!_stricmp(buf, "listen"))
			{
				listen = true;
			}
		}

		else
		{
			int bytesRecv = recvfrom(sock, buf, BUF_SIZE, 0, (sockaddr*)&checkAddr, &addrSize);

			if (checkAddr.sin_addr.S_un.S_addr == addrP1.sin_addr.S_un.S_addr)
			{
				std::cout << "recv " << bytesRecv << " bytes.  Msg: " << buf << std::endl;
			}

			if (checkAddr.sin_addr.S_un.S_addr == addrP2.sin_addr.S_un.S_addr)
			{
				std::cout << "recv " << bytesRecv << " bytes.  Msg: " << buf << std::endl;
			}
			
			if (bytesRecv == SOCKET_ERROR)
			{
				closesocket(sock);
				std::cout << "Error recv: " << WSAGetLastError() << std::endl;
				return 0;
			}

			if (!_stricmp(buf, "quit"))
			{
				loop = false;
			}
		} 
	}*/

	//closesocket(sRec);
	//closesocket(sSnd);

	return 0;
}