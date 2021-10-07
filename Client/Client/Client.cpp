// Client.cpp : Defines the entry point for the application.
//
#pragma once

#include <iostream>
#include "NetworkLib/NetworkLib.h"
#include <string>

using namespace std;
using namespace uqac::networkLib;

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

int main(int argc, char** argv) //usage: -ip [IP] -port [PORT] -protocole [0=TCP;1=UDP]
{
	string username;
	string message;

	// Default parameter
	int protocol = 1;
	int port = 8888;
	string ip = "127.0.0.1";

	//Validate parameters
	if (argc == 6)
	{
		protocol = (int)argv[5];
		port = (int)argv[3];
		ip = argv[5];
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
