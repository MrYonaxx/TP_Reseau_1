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

	std::shared_ptr<Connection> NetworkLib::Connect(string adressIP, int port, int protocol)
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

		// Return la connection
		if (protocol == 0) {
			return make_shared<ConnectionTCP>(connectSocket);
		}
		return make_shared<ConnectionUDP>(connectSocket);
		
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

	void NetworkLib::UpdateListen(Connection s)
	{

		fd_set current_sockets;
		fd_set ready_sockets; // sert de copie de current socket

		// initiliase
		FD_ZERO(&current_sockets);
		// Ajoute listening aux sockets
		FD_SET(listeningSocket, &current_sockets);

		while (true)
		{
			ready_sockets = current_sockets;
			int socketCount = select(0, &ready_sockets, nullptr, nullptr, nullptr);
			if (socketCount < 0)
			{
				// error
				return;
			}

			// On parcourt les sockets ready
			for (int i = 0; i < socketCount; i++)
			{
				// Nouvelle connection
				if (FD_ISSET(listeningSocket, &ready_sockets))
				{
					// Le terminal fait ses trucs

					// On ajoute la nouvelle connection au set
					/*SOCKET client = accept(listeningTCP, nullptr, nullptr);
					FD_SET(client, &current_sockets);
					*/
				}
				else
				{
					// Connection fait ses trucs
					//recv();
				}
			}
		}
	}
}