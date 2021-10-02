// NetworkLib.cpp : définit le point d'entrée de l'application.
//

#include "NetworkLib.h"

//using namespace std; // à cause de ça la fonction bind des socket se confond avec le bind des std::function



int main()
{
	std::cout << "Hello CMake." << std::endl;
	uqac::networkLib::NetworkLib A;
	uqac::networkLib::ConfigCallback callbacks;
	A.Initialize();

	// TEST SERVER
	/* 
	// Listen en AF_INET6 ne fonctionne pas
	if(A.Listen("127.0.0.1", 8888, 0, callbacks) < 0)
		std::cout << "Oups";
	*/

	A.Close();

	return 0;
}


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

	// Arrête WSA et le thread si ce dernier est actif
	void NetworkLib::Close()
	{
		threadRunning = false;
		if(threadNetwork.joinable())
			threadNetwork.join();
		WSACleanup();
	}


	std::shared_ptr<Connection> NetworkLib::Connect(std::string adressIP, int port, int protocol, ConfigCallback callbacks)
	{
		SOCKET connectSocket = INVALID_SOCKET;

		// Setup adresse serveur
		sockaddr_in info;
		info.sin_family = AF_INET6;
		info.sin_port = htons(port);
		inet_pton(AF_INET6, adressIP.c_str(), &info.sin_addr); // on set l'adresse ip	

		//Creation de la socket
		connectSocket = socket(info.sin_family, SOCK_STREAM, protocol == 0 ? IPPROTO_TCP : IPPROTO_UDP);
		if (connectSocket == INVALID_SOCKET) {
			WSACleanup();
			return nullptr;
		}

		//Connexion au serveur
		int iResult = connect(connectSocket, (sockaddr*)&info, sizeof(info));
		if (iResult == SOCKET_ERROR) {
			closesocket(connectSocket);
			connectSocket = INVALID_SOCKET;
		}
		//Maybe try to reconnect here  ? :)

		if (iResult == INVALID_SOCKET) {
			WSACleanup();
			return nullptr;
		}

		// Créer la connection
		std::shared_ptr<Connection> connection;
		if (protocol == 0)
			connection = std::make_shared<ConnectionTCP>(connectSocket);
		else
			connection = std::make_shared<ConnectionUDP>(connectSocket);

		// Lance le thread
		threadRunning = true;
		threadNetwork = std::thread(&NetworkLib::UpdateListen, this, NULL, connection, callbacks);

		// Return la connection
		return connection;
		
	}


	// Créer un listening socket et lance le thread si bien initialisé
	int NetworkLib::Listen(std::string adressIP, int port, int protocol, ConfigCallback callbacks)
	{
		// Setup adresse serveur
		sockaddr_in info;
		info.sin_family = AF_INET6;
		info.sin_port = htons(port);
		inet_pton(AF_INET6, adressIP.c_str(), &info.sin_addr); // on set l'adresse ip

		//Creation du socket
		SOCKET listeningSocket = INVALID_SOCKET;
		listeningSocket = socket(info.sin_family, SOCK_STREAM, protocol == 0 ? IPPROTO_TCP : IPPROTO_UDP);
		if (listeningSocket == INVALID_SOCKET) 
		{
			std::cout << "Can't initialize listening socket.";
			WSACleanup();
			return -1;
		}

		//Setup TCP Listening
		int iResult = bind(listeningSocket, (sockaddr*)&info, sizeof(info));
		if (iResult == SOCKET_ERROR) 
		{
			std::cout << "Can't bind listening socket.";
			closesocket(listeningSocket);
			WSACleanup();
			return -1;
		}
		
		//Listening (only for TCP)
		if (listen(listeningSocket, 255) == SOCKET_ERROR) 
		{
			std::cout << "Can't listen.";
			closesocket(listeningSocket);
			WSACleanup();
			return -1;
		}

		// Lancer le thread 
		threadRunning = true;
		threadNetwork = std::thread(&NetworkLib::UpdateListen, this, listeningSocket, nullptr, callbacks);
		return 1;

	}

	void NetworkLib::UpdateListen(SOCKET listeningSocket, std::shared_ptr<Connection> defaultReceive, ConfigCallback callbacks)
	{

		std::vector<std::shared_ptr<Connection>> listReceive;

		fd_set current_sockets;
		fd_set reading_sockets; // sert de copie de current socket

		// initialise
		FD_ZERO(&current_sockets);

		// Ajoute listening aux sockets
		if (listeningSocket != NULL) 
		{
			FD_SET(listeningSocket, &current_sockets);
		}
		// Ajoute le default receive à la liste
		if (defaultReceive != nullptr) 
		{
			listReceive.push_back(defaultReceive);
			FD_SET(defaultReceive->s, &current_sockets);
		}

		while (threadRunning)
		{
			reading_sockets = current_sockets;
			int socketCount = select(0, &reading_sockets, nullptr, nullptr, nullptr);
			if (socketCount < 0)
			{
				// error
				return;
			}

			// On check si on a une connection
			if (FD_ISSET(listeningSocket, &reading_sockets))
			{
				// Le terminal fait ses trucs
				std::shared_ptr<Connection> newConnection = terminal.Accept(listeningSocket);
				// On ajoute la nouvelle connection au set
				FD_SET(newConnection->s, &current_sockets);
				listReceive.push_back(newConnection);
				callbacks.OnConnection(newConnection);
			}

			// On parcourt la liste de connection
			for (size_t i = listReceive.size()-1; i >= 0; i--)
			{
				if (FD_ISSET(listReceive[i]->s, &reading_sockets))
				{
					if (listReceive[i]->Receive() < 0)
					{
						// Deconnexion
						FD_CLR(listReceive[i]->s, &current_sockets);
						callbacks.OnDisconnection(listReceive[i]);
						listReceive.erase((listReceive.begin() + i));
					}
					else 
					{
						callbacks.OnMsgReceived(listReceive[i]);
					}
				}
			}

		}

	}
}