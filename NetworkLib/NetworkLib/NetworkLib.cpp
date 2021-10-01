// NetworkLib.cpp : définit le point d'entrée de l'application.
//

#include "NetworkLib.h"

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

	std::shared_ptr<Connection> NetworkLib::Connect(string adressIP, int port, int protocol = 0)
	{
		// On créer la socket en fonction du protocole
		SOCKET s = socket(AF_INET, SOCK_STREAM, protocol);
		if (s < 0) // error
		{
			return;
		}


		// Setup adresse serveur
		sockaddr_in info;
		info.sin_family = AF_INET;
		info.sin_port = htons(port);
		inet_pton(AF_INET, adressIP.c_str(), &info.sin_addr); // on set l'adresse ip


		// connection au server
		int connectionResult = connect(s, (sockaddr*)&info, sizeof(info));
		if (connectionResult < 0) // error
		{
			closesocket(s);
			Close();		
			return nullptr;
		}

		// On a réussi à se connecter donc on créer et on renvoit la connection 
		if (protocol == 0)
		{
			return make_shared<ConnectionTCP>(s);
		}
		return make_shared<ConnectionUDP>(s);

		// Lancer le thread
	}

	void NetworkLib::Listen(int port, int protocol = 0)
	{
		listeningSocket = socket(AF_INET, SOCK_STREAM, protocol);
		if (listeningSocket < 0) // error
		{
			return;
		}

		// Setup socket info
		sockaddr_in info;
		info.sin_family = AF_INET;
		info.sin_port = htons(port);
		info.sin_addr.S_un.S_addr = INADDR_ANY;

		bind(listeningSocket, (sockaddr*)&info, sizeof(info));
		listen(listeningSocket, SOMAXCONN);

		// Lancer le thread 
	}




	void NetworkLib::UpdateListenServer(Connection s)
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