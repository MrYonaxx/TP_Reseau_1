// Client.cpp : Defines the entry point for the application.
//
#pragma once

#include <iostream>
#include <NetworkLib.h>


using namespace std;
using namespace uqac::networkLib;


int main(int argc, char** argv) //usage: -ip [IP] -port [PORT] -protocole [0=TCP;1=UDP]
{
	string username;
	string message;

	//Validate parameters
	if (argc != 6) {
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
	cin >> username;

	// Callbacks
	ConfigCallback callbacks;


	//Connection au serveur
	std::shared_ptr<Connection> connection = net->Connect(argv[1], (int)argv[3], (int)argv[5], callbacks);

	//Chat
	cout << "/exit pour quitter\n";
	while (true) {
		cin >> message;
		if (message == "/exit")
			break;
		message = "[", username, "]:" + message;
		connection->Send();
	}
	return 1;
}
