// NetworkLib.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets.

#pragma comment(lib, "Ws2_32.lib")

#include <iostream>

// TODO: Référencez ici les en-têtes supplémentaires nécessaires à votre programme.

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#include "Connection.h"
#include "ConnectionTCP.h"
#include "ConnectionUDP.h"

namespace uqac::networkLib
{
	class NetworkLib
	{

	private:
		SOCKET listeningSocket;
		SOCKET connectSocket;

	public:

		int Initialize();
		void Close();

		std::shared_ptr<Connection> Connect(std::string adressIP, int port, int protocol = 0);
		void Listen(std::string adressIP, int port, int protocol);


		// Pour les thread 
		void UpdateListen(Connection s);
	};

	/*struct Config {
		std::function OnConnect;
	};*/
}