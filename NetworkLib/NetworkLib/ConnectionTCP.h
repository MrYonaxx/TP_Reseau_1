#pragma once
#include <WinSock2.h>
#include "Connection.h"

namespace uqac::networkLib
{
	class ConnectionTCP : public Connection
	{
	public:
		ConnectionTCP();
		ConnectionTCP(SOCKET socket); // faudrait filer un pointeur
		~ConnectionTCP();

	public:
		int Send() override;
		int Receive() override;

	};
}

