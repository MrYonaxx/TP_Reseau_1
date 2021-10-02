#pragma once
#include <WinSock2.h>

namespace uqac::networkLib
{
	class Connection
	{
	
		protected:
			char buf[255];
			struct addrinfo* info;
	
		public:
			SOCKET s;
			virtual int Send();
			virtual int Receive();
	
	};
}

