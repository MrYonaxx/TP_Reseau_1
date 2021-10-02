#include "Terminal.h"

using namespace std;

namespace uqac::networkLib
{

	ConnectionTCP Terminal::Accept(SOCKET ListenSocket)
	{
		// create socket
		SOCKET ClientSocket;
		ClientSocket = INVALID_SOCKET;

		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			cout << "Coulndt accept : ", WSAGetLastError();
			closesocket(ListenSocket);
			WSACleanup();
			return;
		}
		ConnectionTCP *connection = new ConnectionTCP();
		return *connection;
	}


}