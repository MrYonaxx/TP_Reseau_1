#include "ConnectionUDP.h"

namespace uqac::networkLib
{
	ConnectionUDP::ConnectionUDP()
	{

	}

	ConnectionUDP::ConnectionUDP(SOCKET s, int port)
	{
		this->s = s;

		//sockaddr_in info;
		slen = sizeof(info);

		memset((char*)&info, 0, sizeof(info));
		info.sin_family = AF_INET;
		info.sin_port = htons(port);
		info.sin_addr.S_un.S_addr = INADDR_ANY;
	}

	ConnectionUDP::~ConnectionUDP()
	{
		closesocket(s);
	}



	int ConnectionUDP::Send(std::string message)
	{
		/*sockaddr_in info;
		int slen = sizeof(info);

		memset((char*)&info, 0, sizeof(info));
		info.sin_family = AF_INET;
		info.sin_port = htons(port);
		info.sin_addr.S_un.S_addr = INADDR_ANY;*/

		//send the message
		if (sendto(s, buf, strlen(buf), 0, (struct sockaddr*) &info, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		free(buf);

		return 0;
	}

	int ConnectionUDP::Receive()
	{
		/**sockaddr_in info;
		int slen = sizeof(info);

		memset((char*)&info, 0, sizeof(info));
		info.sin_family = AF_INET;
		info.sin_port = htons(port);
		info.sin_addr.S_un.S_addr = INADDR_ANY;*/
		int iResult = recvfrom(s, buf, strlen(buf), 0, (struct sockaddr*)&info, &slen);
		if (iResult == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		std::string message(buf, iResult);
		msg = message;
		//std::cout << "Hrm hrm hrm";
		//free(buf);
		//std::cout << "Hrm hrm";
		return 0;
	}


}