#ifndef UDP_H
#define UDP_H

#include <WinSock2.h>
#include <ws2tcpip.h>
#include "SendRecLogic.h"
#include <Windows.h>

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

class UDP
{
private:
	//The socket and receiving address
	SOCKET _sock;
	SOCKADDR_IN _addrRec;
	SendRecLogic _srl;

	//Empty addresses for both players and a check address + sizes
	SOCKADDR_IN _addrP1;
	int _addrSizeP1;
	SOCKADDR_IN _addrP2;
	int _addrSizeP2;
	SOCKADDR_IN _checkAddr;
	int _addrSizeChk;

	int _iWSAStatus;		// Windows Socket API Status
	WSADATA _wsaData;
	int _sockErr;
	sockaddr* _addressRec;

	const int _BUF_SIZE = 64;
	const int _UPDSIZE = 22;
	char _wrtBuffer[64]{};
	char _rdBuffer[64]{};

	BOOL p1Con, p2Con;

public:
	UDP();
	~UDP();
	BOOL lobby(int players, BOOL* run); //will allow me to test with 1 or 2 clients
	BOOL init(); //Simple game setup logic
	BOOL game(); //Send and receive routine for the actual game
	

};

#endif