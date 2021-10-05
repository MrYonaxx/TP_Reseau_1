#pragma once
#include <WinSock2.h>
#include <iostream>

namespace uqac::networkLib
{
	class Connection
	{
	
		protected:
			char buf[255];
			struct addrinfo* info;
	
		public:
			SOCKET s;
			virtual int Send(std::string message);
			virtual int Receive();
	
	};
}

