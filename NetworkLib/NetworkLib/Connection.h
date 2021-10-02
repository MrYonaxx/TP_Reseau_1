#pragma once
#include <WinSock2.h>

namespace uqac::networkLib
{
	class Connection
	{
	
		protected:
			SOCKET s;
			char* buf;
	
		public:
			virtual int Send();
			virtual int Receive();
	
	};
}

