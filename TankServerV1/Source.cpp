#include <iostream>
#include <vector>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

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
	SOCKET sSnd, sRec;
	SOCKADDR_IN addrRec;
	SOCKADDR_IN addrSnd;
	int timeVal = 90;
	char wrtBuffer[64]{};
	char rdBuffer[64]{};

	int iWSAStatus;		// Windows Socket API Status
	WSADATA wsaData;

	int sockErrSnd;
	int sockErrRec;

	char buf[BUF_SIZE];
	bool loop = true, listen = false;

	iWSAStatus = WSAStartup(MAKEWORD(2, 2), &wsaData);

	// what did we get?
	std::cout << wsaData.szDescription << std::endl;

	// address family (TCP, UDP), datagram socket (UDP), 0 for default protocol
	sSnd = socket(AF_INET, SOCK_DGRAM, 0);
	sRec = socket(AF_INET, SOCK_DGRAM, 0);

	addrRec.sin_family = AF_INET;
	addrSnd.sin_family = AF_INET;

	addrRec.sin_port = htons(49152);
	addrSnd.sin_port = htons(49152);

	inet_pton(AF_INET, "64.72.2.69", &(addrRec.sin_addr));
	inet_pton(AF_INET, "64.72.2.54", &(addrSnd.sin_addr));

	sockaddr* addressRec = (sockaddr*)&addrRec;
	//sockaddr* addressSnd = (sockaddr*)&addrSnd;

	/*
	if (sSnd == INVALID_SOCKET || sRec == INVALID_SOCKET)
	{
		// see windows socket errors
		std::cout << "Error creating socket: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	} */

	// associate local address with a socket
	sockErrSnd = connect(sSnd, (sockaddr*)&addrSnd, sizeof(addrSnd));
	sockErrRec = bind(sRec, addressRec, sizeof(addrRec));

	/*
	if (sockErrSnd == SOCKET_ERROR || sockErrRec == SOCKET_ERROR)
	{
		closesocket(sSnd);
		closesocket(sRec);
		std::cout << "Error bind: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	}*/
	std::thread timerTh(timer, &timeVal);

	timerTh.join();
	loop = true;

	while (loop)
	{
		/*
		if (!listen)
		{
			std::cout << "Enter a message to send (or quit, or listen): ";
			std::cin.getline(buf, BUF_SIZE);

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(255, '\n');
			}

			send(sSnd, buf, strlen(buf) + 1, 0);

			if (sockErrSnd == SOCKET_ERROR)
			{
				closesocket(sSnd);
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
			int bytesRecv = recv(sRec, buf, BUF_SIZE, 0);

			std::cout << "recv " << bytesRecv << " bytes.  Msg: " << buf << std::endl;

			if (bytesRecv == SOCKET_ERROR)
			{
				closesocket(sRec);
				std::cout << "Error recv: " << WSAGetLastError() << std::endl;
				return 0;
			}

			if (!_stricmp(buf, "quit"))
			{
				loop = false;
			}
		} */
	}

	closesocket(sRec);
	closesocket(sSnd);
	WSACleanup();

	return 0;
}