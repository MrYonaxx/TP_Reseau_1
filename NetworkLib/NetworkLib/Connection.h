#pragma once
#include <WinSock2.h>

namespace uqac::networkLib
{
	class Connection
	{
	
		protected:
			char* buf;
	
		public:
			SOCKET s;
			virtual int Send();
			virtual int Receive();
	
	};
}

