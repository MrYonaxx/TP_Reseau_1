// Server.cpp : Defines the entry point for the application.
//

//#include "Server.h"

#pragma once
#include <iostream>
#include <vector>
#include "NetworkLib/NetworkLib.h"
#include "windows.h" 

using namespace std;
using namespace uqac::networkLib;


vector<shared_ptr<Connection>> listConnection;


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
	string username;
	string message;

	// Default parameter
	int protocol = 0;
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
