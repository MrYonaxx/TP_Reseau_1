#pragma once

#include "Connection.h"
#include <stdio.h>
#include <WinSock2.h>

namespace uqac::networkLib
{
	class ConnectionUDP : public Connection
	{
	private:
		sockaddr_in info;
		int slen;

	public:
		ConnectionUDP();
		ConnectionUDP(SOCKET s, sockaddr_in info); // faudrait filer un pointeur
		~ConnectionUDP();

	public:
		int Send(std::string message) override;
		int Receive() override;
	};
}

