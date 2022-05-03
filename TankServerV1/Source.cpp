#include <iostream>
#include <vector>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <string>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <thread>
#include <chrono>

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

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
	SOCKET sock;
	SOCKADDR_IN addrP1;
	SOCKADDR_IN addrP2;
	SOCKADDR_IN addrRec;
	SOCKADDR_IN checkAddr;
	int addrSize = sizeof(checkAddr);

	int timeVal = 90;
	char wrtBuffer[64]{};
	char rdBuffer[64]{};

	int iWSAStatus;		// Windows Socket API Status
	WSADATA wsaData;

	int sockErr;

	char buf[BUF_SIZE];
	bool loop = true, listen = false;

	iWSAStatus = WSAStartup(MAKEWORD(2, 2), &wsaData);

	// what did we get?
	std::cout << wsaData.szDescription << std::endl;

	// address family (TCP, UDP), datagram socket (UDP), 0 for default protocol
	//main socket
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	addrP1.sin_family = AF_INET;
	addrP2.sin_family = AF_INET;
	addrRec.sin_family = AF_INET;

	addrP1.sin_port = htons(49152);
	addrP2.sin_port = htons(49152);
	addrRec.sin_port = htons(49152);

	inet_pton(AF_INET, "64.72.1.168", &(addrP1.sin_addr));
	inet_pton(AF_INET, "64.72.2.119", &(addrP2.sin_addr));
	inet_pton(AF_INET, "64.72.1.247", &(addrRec.sin_addr));

	
	//sockaddr* addressP1 = (sockaddr*)&addrP1;
	//sockaddr* addressP2 = (sockaddr*)&addrP2;
	//sockaddr* addressSnd = (sockaddr*)&addrSnd;
	sockaddr* addressRec = (sockaddr*)&addrRec;

	/*
	if (sSnd == INVALID_SOCKET || sRec == INVALID_SOCKET)
	{
		// see windows socket errors
		std::cout << "Error creating socket: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	} */

	// associate local address with a socket

	sockErr = bind(sock, addressRec, sizeof(addrRec));
	//sockErrSnd = connect(sSnd, (sockaddr*)&addrSnd, sizeof(addrSnd));
	
	//sockErrSnd = connect(sSnd, (sockaddr*)&addrSnd, sizeof(addrSnd));
	//sockErrRec = bind(sRec, addressRec, sizeof(addrRec));

	/*
	if (sockErrSnd == SOCKET_ERROR || sockErrRec == SOCKET_ERROR)
	{
		closesocket(sSnd);
		closesocket(sRec);
		std::cout << "Error bind: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	}*/
	//std::thread timerTh(timer, &timeVal);

	//timerTh.join();
	loop = true;
	//listen = false;
	listen = true;

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
			}*/

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
	}

	//closesocket(sRec);
	//closesocket(sSnd);
	closesocket(sock);
	WSACleanup();

	return 0;
}