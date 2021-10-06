// Server.cpp : Defines the entry point for the application.
//

//#include "Server.h"

#pragma once
#include <iostream>
#include <vector>
#include "NetworkLib/NetworkLib.h"

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
	std::string copy = message->msg;
	std::cout << "%s" << copy;
	for (int i = 0; i < listConnection.size(); ++i)
	{
		if (listConnection[i] != message) 
		{
			listConnection[i]->Send("Hello");
		}
	}
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
	cout << "Hello CMake." << endl;

	uqac::networkLib::NetworkLib A;
	uqac::networkLib::ConfigCallback callbacks;
	A.Initialize();

	callbacks.OnConnection = AddConnection;
	callbacks.OnDisconnection = RemoveConnection;
	callbacks.OnMsgReceived = SendMessageAll;

	if (A.Listen("127.0.0.1", 8888, 1, callbacks) < 0)
		std::cout << "Oups";

	while (true)
	{

	}
	
	A.Close();

	return 0;
}
