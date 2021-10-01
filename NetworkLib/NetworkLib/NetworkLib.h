﻿// NetworkLib.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets.

#pragma once

#include <iostream>

// TODO: Référencez ici les en-têtes supplémentaires nécessaires à votre programme.

#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Connection.h"
#include "ConnectionTCP.h"
#include "ConnectionUDP.h"

namespace uqac::networkLib
{
	class NetworkLib
	{

	private:
		SOCKET listeningSocket;

	public:

		int Initialize();
		void Close();

		std::shared_ptr<Connection> Connect(string adressIP, int port, int protocol = 0);
		void Listen(int port, int protocol = 0);


		// Pour les thread 
		void UpdateListenServer(Connection s);
	};

	/*struct Config {
		std::function OnConnect;
	};*/
}