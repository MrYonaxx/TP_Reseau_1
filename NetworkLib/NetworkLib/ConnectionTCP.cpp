#include "ConnectionTCP.h"
#include <iostream>

namespace uqac::networkLib
{

	ConnectionTCP::ConnectionTCP()
	{
		// create socket
	}

	ConnectionTCP::ConnectionTCP(SOCKET socket)
	{
		s = socket;
	}

	ConnectionTCP::~ConnectionTCP()
	{
		closesocket(s);
	}


	int ConnectionTCP::Send()
	{
		int iResult = send(s, sendbuf, (int)strlen(sendbuf), 0);
		if (iResult == SOCKET_ERROR) {
			std::cout << "send failed : ", WSAGetLastError();
			closesocket(s);
			WSACleanup();
			return -1;
		}
		//cout << "Send !";
		return 1;
	}

	int ConnectionTCP::Receive()
	{
		return 0;
	}

}
