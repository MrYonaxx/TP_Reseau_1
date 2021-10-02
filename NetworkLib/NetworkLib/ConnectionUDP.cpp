#include "ConnectionUDP.h"

namespace uqac::networkLib 
{
	ConnectionUDP::ConnectionUDP()
	{

	}

	ConnectionUDP::~ConnectionUDP()
	{
		closesocket(s);
	}

	ConnectionUDP::ConnectionUDP(SOCKET s)
	{

	}

	int ConnectionUDP::Send()
	{
		return 0;
	}

	int ConnectionUDP::Receive()
	{
		return 0;
	}
}
