// NetworkLib.cpp : définit le point d'entrée de l'application.
//

#include "NetworkLib.h"

#include <thread>

using namespace std;

/*int main()
{
	cout << "Hello CMake." << endl;
	return 0;
}*/


namespace uqac::networkLib
{

	int NetworkLib::Initialize()
	{
		// Initialize winstock
		WSADATA wsData;
		WORD ver = MAKEWORD(2, 2);

		int wsOk = WSAStartup(ver, &wsData);
		if (wsOk != 0)
		{
			return -1;
		}

		return 1;
	}

	void NetworkLib::Close()
	{
		WSACleanup();
	}

	void NetworkLib::Connect(string adressIP, int port, int protocol)
	{
		connectSocket = INVALID_SOCKET;

		// Setup adresse serveur
		sockaddr_in info;
		info.sin_family = AF_INET6;
		info.sin_port = htons(port);
		inet_pton(AF_INET6, adressIP.c_str(), &info.sin_addr); // on set l'adresse ip	

		//Creation de la socket
		connectSocket = socket(info.sin_family, SOCK_STREAM, protocol == 0 ? IPPROTO_TCP : IPPROTO_UDP);
		if (connectSocket == INVALID_SOCKET) {
			WSACleanup();
			return;
		}

		//Connexion au serveur
		int iResult = connect(connectSocket, (sockaddr*)&info, sizeof(info));
		if (iResult == SOCKET_ERROR) {
			closesocket(connectSocket);
			connectSocket == INVALID_SOCKET;
		}
		//Maybe try to reconnect here  ? :)

		if (iResult == INVALID_SOCKET) {
			WSACleanup();
			return;
		}

		// Lancer le thread
		
	}

	void NetworkLib::Listen(string adressIP, int port, int protocol = 0)
	{
		// Setup adresse serveur
		sockaddr_in info;
		info.sin_family = AF_INET6;
		info.sin_port = htons(port);
		inet_pton(AF_INET6, adressIP.c_str(), &info.sin_addr); // on set l'adresse ip

		//Creation du socket
		listeningSocket = INVALID_SOCKET;
		listeningSocket = socket(info.sin_family, SOCK_STREAM, protocol == 0 ? IPPROTO_TCP : IPPROTO_UDP);
		if (listeningSocket == INVALID_SOCKET) {
			WSACleanup();
			return;
		}

		//Setup TCP Listening
		int iResult = bind(listeningSocket, (sockaddr*)&info, sizeof(info));
		if (iResult == SOCKET_ERROR) {
			closesocket(listeningSocket);
			WSACleanup();
			return;
		}
		
		//Listening
		if (listen(listeningSocket, 255) == SOCKET_ERROR) {
			closesocket(listeningSocket);
			WSACleanup();
			return;
		}

		// Lancer le thread 
	}

	void NetworkLib::ListenThread(SOCKET s)
	{
		fd_set readingSet;
		FD_ZERO(&readingSet);
		fd_set writingSet;
		FD_ZERO(&writingSet);

		u_long nonBlocking = 1;
		ioctlsocket(s, FIONBIO, &nonBlocking);
		while (true) {
			FD_SET(s, &readingSet);

			int ret = select(0, &readingSet, &writingSet, nullptr, nullptr);

			if (ret > 0) {
				if (FD_ISSET(s, &readingSet)) {
					///JE SAIS  PAS
				}
			}
		}
	}
}