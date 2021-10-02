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

	int ConnectionUDP::Send(int port)
	{
		sockaddr_in info;
		int slen = sizeof(info);

		memset((char*)&info, 0, sizeof(info));
		info.sin_family = AF_INET;
		info.sin_port = htons(port);
		info.sin_addr.S_un.S_addr = INADDR_ANY;

        //send the message
        if (sendto(s, sendbuf, strlen(sendbuf), 0, (struct sockaddr*)&info, slen) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code : %d", WSAGetLastError());
            exit(EXIT_FAILURE);
        }
		return 0;
	}

	int ConnectionUDP::Receive(int port)
	{
		sockaddr_in info;
		int slen = sizeof(info);

		memset((char*)&info, 0, sizeof(info));
		info.sin_family = AF_INET;
		info.sin_port = htons(port);
		info.sin_addr.S_un.S_addr = INADDR_ANY;

		if (recvfrom(s, recvbuf, strlen(recvbuf), 0, (struct sockaddr*)&info, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		free(recvbuf);

		return 0;
	}

    
