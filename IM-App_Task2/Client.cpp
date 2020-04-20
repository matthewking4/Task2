#include "Client.h"

int Client::Connect() {
	PARAMETERS connectionParameters;
	sockaddr_in service;
	SOCKET clientSocket;

	int port = this->getPort();
	string addr = this->getAddr();
	this->WinsockSetup();
	clientSocket = this->socketSetup();
	service = this->setupService(port, addr);
	this->establishConnection(clientSocket, service);

	cout << "You've connected to a host. Please enter a display name: ";
	cin >> this->name;


	connectionParameters.port = port;
	connectionParameters.ipAddr = addr;
	connectionParameters.socket = (LPVOID)clientSocket;
	connectionParameters.inst = this;
	connectionParameters.sizeOf = sizeof(Client);
	connectionParameters.name = this->name;

	CreateThread(NULL, 0, this->ClientThreadedSender, &connectionParameters, 0, 0);
	
	int recvByteCount = 0;
	while (true) {
		Sleep(500);
		this->recvSocket<PARAMETERS>(connectionParameters, recvByteCount);
	}

	return this->destroy();
}

void Client::establishConnection(SOCKET socket, sockaddr_in service)
{
	if (connect(socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		WSACleanup();
		throw ConnectException();
	}
}

DWORD WINAPI Client::ClientThreadedSender(void * parameters)
{
	PARAMETERS* params = (PARAMETERS*)parameters;
	SOCKET socket = (SOCKET)params->socket;
	Client client(params->port, params->ipAddr);
	string msg;
	int sendByteCount = 0;
	while (true) {
		Sleep(500);
		sendByteCount = send(socket, (char *)&client, sizeof(Client), 0);
		if (socket != INVALID_SOCKET) {
			if (sendByteCount == SOCKET_ERROR) {
				WSAGetLastError();
				closesocket(socket);
				throw SendException();
			}
			else {
				cin >> msg;
				client.message = params->name + ": " + msg;
				if (msg == "QUIT") {
					exit(0);
				}
			}
		}
		else {
			throw InvalidSocketException();
		}
	}
};
