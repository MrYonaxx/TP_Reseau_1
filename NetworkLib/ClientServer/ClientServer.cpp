// Client.cpp : Defines the entry point for the application.
//
#pragma once

#include <iostream>
#include "NetworkLib.h"
#include <string>
#include <vector>
#include "windows.h"

using namespace std;
using namespace uqac::networkLib;

vector<shared_ptr<Connection>> listConnection;

void MessageReceived(std::shared_ptr<Connection> newMsg) 
{
	std::cout << newMsg->msg;
	std::cout << '\n';
}
void ConnectionLost(std::shared_ptr<Connection> newMsg)
{
	std::cout << "Connection lost";

	// Handle things
	// Abort programm

}

// s'abonne à OnConnection
void AddConnection(shared_ptr<Connection> newConnection)
{
	std::cout << "Connection ajouté";
	listConnection.push_back(newConnection);
}

// s'abonne à OnDisconnection
void RemoveConnection(shared_ptr<Connection> newConnection)
{
	//listConnection.remove(newConnection);
}

// s'abonne à OnMsgReceived
void SendMessageAll(shared_ptr<Connection> message)
{
	if (message == nullptr)
		std::cout << "Aöe";

	std::cout << '\n';
	std::cout << message->msg;

	for (int i = 0; i < listConnection.size(); ++i)
	{
		if (listConnection[i] != message)
		{
			listConnection[i]->Send(message->msg);
		}
	}
}

int main(int argc, char** argv) //usage: -ip [IP] -port [PORT] -protocole [0=TCP;1=UDP]
{
	string answer;
	string username;
	string message;

	// Client ou Server
	cout << "Client(0) ou Server(1) ?";
	std::getline(std::cin, answer);

	if (answer == "0") {
		//Client
		// Default parameter
		int protocol = 0;
		int port = 8888;
		string ip = "127.0.0.1";

		//Validate parameters
		if (argc == 7)
		{
			char* p;
			long arg = strtol(argv[6], &p, 10);
			protocol = (int)arg;

			arg = strtol(argv[4], &p, 10);
			port = arg;

			ip = std::string(argv[2]);
			std::cout << ip;
			std::cout << "\n";
			std::cout << port;
			std::cout << "\n";
			std::cout << protocol;
			std::cout << "\n";
		}
		else if (argc > 1)
		{
			cout << "usage: -ip [IP] -port [PORT] -protocole [0=TCP;1=UDP]\n";
			return -1;
		}

		//Init Network Lib
		NetworkLib* net = new NetworkLib();
		int err = net->Initialize();
		if (err == -1) {
			cerr << "Failed to initialized";
			return -1;
		}


		cout << "Username ?\n";
		std::getline(std::cin, username);
		//cin >> username;

		// Callbacks
		ConfigCallback callbacks;
		callbacks.OnMsgReceived = MessageReceived;
		callbacks.OnDisconnection = ConnectionLost;

		//Connection au serveur
		std::shared_ptr<Connection> connection = net->Connect(ip, port, protocol, callbacks);
		if (connection == nullptr)
		{
			cout << "Argh\n";
			return -1;
		}

		//Chat
		cout << "/exit pour quitter\n";
		while (true) {
			std::getline(std::cin, message);
			//cin >> message;
			if (message == "/exit")
				break;
			message = "[" + username + "]:" + message;
			connection->Send(message.c_str());
			std::cout << message;
			std::cout << '\n';
		}
		return 1;
	}
	else if (answer == "1") {
		//Server
		string username;
		string message;

		// Default parameter
		int protocol = 0;
		int port = 8888;
		string ip = "127.0.0.1";

		//Validate parameters
		if (argc == 7)
		{
			char* p;
			long arg = strtol(argv[6], &p, 10);
			protocol = (int)arg;

			arg = strtol(argv[4], &p, 10);
			port = arg;

			ip = std::string(argv[2]);
			std::cout << ip;
			std::cout << "\n";
			std::cout << port;
			std::cout << "\n";
			std::cout << protocol;
			std::cout << "\n";
		}
		else if (argc > 1)
		{
			cout << "usage: -ip [IP] -port [PORT] -protocole [0=TCP;1=UDP]\n";
			return -1;
		}
		cout << "Hello CMake." << endl;

		uqac::networkLib::NetworkLib A;
		uqac::networkLib::ConfigCallback callbacks;
		A.Initialize();

		callbacks.OnConnection = AddConnection;
		callbacks.OnDisconnection = RemoveConnection;
		callbacks.OnMsgReceived = SendMessageAll;

		if (A.Listen(ip, port, protocol, callbacks) < 0)
			std::cout << "Oups";

		while (true)
		{
			Sleep(1);
		}

		A.Close();

		return 0;
	}
	else {
		return -1;
	}
}
