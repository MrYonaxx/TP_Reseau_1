#pragma once

#include "Connection.h"
#include <stdio.h>
#include <WinSock2.h>

namespace uqac::networkLib
{
	class ConnectionUDP : public Connection
	{
	public:
		ConnectionUDP();
		ConnectionUDP(SOCKET s); // faudrait filer un pointeur
		~ConnectionUDP();

	public:
		int Send(int port);
		int Receive(int port);
	};
}

