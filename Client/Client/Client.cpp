// Client.cpp : Defines the entry point for the application.
//
#pragma once

#include <iostream>
//#include <NetworkLib.h>
#include "NetworkLib/NetworkLib.h"
//#include "Connection.h"

using namespace std;
using namespace uqac::networkLib;

void MessageReceived(std::shared_ptr<Connection> newMsg) 
{
	std::cout << newMsg->msg;
}
void ConnectionLost(std::shared_ptr<Connection> newMsg)
{
	std::cout << "Connection lost";

	// Handle things
	//

}

int main(int argc, char** argv) //usage: -ip [IP] -port [PORT] -protocole [0=TCP;1=UDP]
{
	string username;
	string message;

	//Validate parameters
	/*if (argc != 6) {
		cout << "usage: -ip [IP] -port [PORT] -protocole [0=TCP;1=UDP]\n";
		return -1;
	}*/

	//Init Network Lib
	NetworkLib* net = new NetworkLib();
	int err = net->Initialize();
	if (err == -1) {
		cerr << "Failed to initialized";
		return -1;
	}
	

	cout << "Username ?\n";
	cin >> username;

	// Callbacks
	ConfigCallback callbacks;
	callbacks.OnMsgReceived = MessageReceived;
	callbacks.OnDisconnection = ConnectionLost;

	//Connection au serveur
	std::shared_ptr<Connection> connection = net->Connect("127.0.0.1", 8888, 1, callbacks);
	if (connection == nullptr)
	{
		cout << "Argh\n";
		return -1;
	}

	//Chat
	cout << "/exit pour quitter\n";
	while (true) {
		cin >> message;
		if (message == "/exit")
			break;
		message = "[", username, "]:" + message;
		connection->Send(message);
	}
	return 1;
}
