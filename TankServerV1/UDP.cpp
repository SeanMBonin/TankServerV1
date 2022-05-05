#include "UDP.h"
#include <iostream>

UDP::UDP(int* time, BOOL* start)
{
	_timer = time;
	_start = start;

	_addrSizeP1 = sizeof(_addrP1);
	_addrSizeP2 = sizeof(_addrP2);
	_addrSizeChk = sizeof(_checkAddr);

	_iWSAStatus = WSAStartup(MAKEWORD(2, 2), &_wsaData);

	// what did we get?
	std::cout << _wsaData.szDescription << std::endl;

	// address family (TCP, UDP), datagram socket (UDP), 0 for default protocol
	//Steps to bind main socket
	_sock = socket(AF_INET, SOCK_DGRAM, 0);

	_addrRec.sin_family = AF_INET;

	_addrRec.sin_port = htons(49152);

	inet_pton(AF_INET, "64.72.1.247", &(_addrRec.sin_addr));
	//inet_pton(AF_INET, "192.168.24.194", &(_addrRec.sin_addr));

	_addressRec = (sockaddr*)&_addrRec;

	_sockErr = bind(_sock, _addressRec, sizeof(_addrRec));

	std::cout << "CHECK CHECK CHECK::: " << _addrRec.sin_addr.S_un.S_addr << std::endl;

	p1Con = false;
	p2Con = false;
}

UDP::~UDP()
{
	closesocket(_sock);
	WSACleanup();
}

BOOL UDP::lobby(int players, BOOL* run)
{
	int rdyPlayers = 0;
	char buff[5]{};
	BOOL p1Rdy = false, p2Rdy = false;

	while (*run)
	{
		int bytesRecv = recvfrom(_sock, _rdBuffer, _BUF_SIZE, 0, (sockaddr*)&_checkAddr, &_addrSizeChk);
		
		//This logic stays local for IP assignments
		
		if (_rdBuffer[0] == 'L' && _rdBuffer[1] == 5)
		{
			if (!p1Con)
			{
				_addrP1 = _checkAddr;				
				std::cout << "Player 1 Connected with IP: " << _addrP1.sin_addr.S_un.S_addr << std::endl;
				buff[0] = 'L';
				buff[1] = '1';
				sendto(_sock, buff, 3, 0, (sockaddr*)&_addrP1, _addrSizeP1);
				p1Con = true;
			}
			else if (!p2Con)
			{
				_addrP2 = _checkAddr;
				std::cout << "Player 2 Connected with IP: " << _addrP2.sin_addr.S_un.S_addr <<std::endl;
				buff[0] = 'L';
				buff[1] = '2';
				sendto(_sock, buff, 3, 0, (sockaddr*)&_addrP2, _addrSizeP2);
				p2Con = true;
			}
			else
			{
				std::cout << "Player connection rejected" << std::endl;
				buff[0] = 'L';
				buff[1] = 0x15;
				sendto(_sock, buff, 3, 0, (sockaddr*)&_addrP2, _addrSizeP2);
			}
		}

		if (_rdBuffer[0] == 'L' && _rdBuffer[1] == 'R')
		{
			if (_checkAddr.sin_addr.S_un.S_addr == _addrP1.sin_addr.S_un.S_addr)
			{
				p1Rdy = true;
				std::cout << "Player 1 Ready" << std::endl;
				buff[0] = 'L';
				buff[1] = 'R';
				buff[2] = '1';
				sendto(_sock, buff, 4, 0, (sockaddr*)&_addrP1, _addrSizeP1);
			}

			if (_checkAddr.sin_addr.S_un.S_addr == _addrP2.sin_addr.S_un.S_addr)
			{
				p2Rdy = true;
				std::cout << "Player 2 Ready" << std::endl;
				buff[0] = 'L';
				buff[1] = 'R';
				buff[2] = '2';
				sendto(_sock, buff, 4, 0, (sockaddr*)&_addrP2, _addrSizeP2);
			}
		}
		
		if (p1Rdy && p2Rdy)
		{
			if (init())
			{
				*_start = true;
				game();
			}
		}

	}
	return false;
}

BOOL UDP::init()
{
	SendRecLogic gameLogic;
	gameLogic.gameStart(_wrtBuffer);

	sendto(_sock, _wrtBuffer, _UPDSIZE, 0, (sockaddr*)&_addrP1, _addrSizeP1);
	sendto(_sock, _wrtBuffer, _UPDSIZE, 0, (sockaddr*)&_addrP2, _addrSizeP2);

	return true;
}

BOOL UDP::game()
{
	SendRecLogic gameLogic;
	//Timer not timed out, game still running
	while (*_timer > 0)
	{
		recvfrom(_sock, _rdBuffer, _BUF_SIZE, 0, (sockaddr*)&_checkAddr, &_addrSizeChk);

		if (_checkAddr.sin_addr.S_un.S_addr == _addrP1.sin_addr.S_un.S_addr)
		{
			// update function has all the logic
			gameLogic.receiveUpdate(1, _rdBuffer[0], _timer, _wrtBuffer);
		}

		if (_checkAddr.sin_addr.S_un.S_addr == _addrP2.sin_addr.S_un.S_addr)
		{
			gameLogic.receiveUpdate(2, _rdBuffer[0], _timer, _wrtBuffer);
		}

		sendto(_sock, _wrtBuffer, _UPDSIZE, 0, (sockaddr*)&_addrP1, _addrSizeP1);
		sendto(_sock, _wrtBuffer, _UPDSIZE, 0, (sockaddr*)&_addrP2, _addrSizeP2);
	}
	
	//Send the results to the players
	int sendSize = 0;
	sendSize = gameLogic.results(_wrtBuffer, 1);
	sendto(_sock, _wrtBuffer, sendSize, 0, (sockaddr*)&_addrP1, _addrSizeP1);

	sendSize = gameLogic.results(_wrtBuffer, 2);
	sendto(_sock, _wrtBuffer, sendSize, 0, (sockaddr*)&_addrP2, _addrSizeP2);
	

	return false;
}