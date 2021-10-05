// Server.cpp : Defines the entry point for the application.
//

//#include "Server.h"

#pragma once
#include <iostream>
#include <vector>
#include "../../NetworkLib/NetworkLib/NetworkLib.h"

using namespace std;
using namespace uqac::networkLib;


vector<shared_ptr<Connection>> listConnection;


// s'abonne à OnConnection
void AddConnection(shared_ptr<Connection> newConnection) 
{
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
	for (size_t i = 0; i < listConnection.size(); i++)
	{
		if (listConnection[i] != message) 
		{
			listConnection[i]->Send();
		}
	}
}

int main()
{
	cout << "Hello CMake." << endl;

	uqac::networkLib::NetworkLib A;
	uqac::networkLib::ConfigCallback callbacks;
	A.Initialize();

	callbacks.OnConnection = AddConnection;
	callbacks.OnDisconnection = RemoveConnection;
	callbacks.OnMsgReceived = SendMessageAll;

	if (A.Listen("127.0.0.1", 8888, 0, callbacks) < 0)
		std::cout << "Oups";

	while (true)
	{

	}
	
	A.Close();

	return 0;
}
