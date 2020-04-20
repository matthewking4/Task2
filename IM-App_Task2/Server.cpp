#include "Server.h"


int Server::Connect() {
	PARAMETERS connectionParameters;
	sockaddr_in service;
	SOCKET serverSocket;

	int port = this->getPort();
	string addr = this->getAddr();
	this->WinsockSetup();
	serverSocket = this->socketSetup();
	service = this->setupService(port, addr);

	if (::bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		closesocket(serverSocket);
		WSACleanup();
		throw BindingException();
		return 0;
	}

	this->connectionListen(serverSocket);
	SOCKET acceptSocket = this->acceptConnection(serverSocket);

	cout << "You've connected to a client. Please enter a display name: ";
	cin >> this->name;

	connectionParameters.socket = (LPVOID)acceptSocket;
	connectionParameters.inst = this;
	connectionParameters.sizeOf = sizeof(Server);
	connectionParameters.name = this->name;
	connectionParameters.port = port;
	connectionParameters.ipAddr = addr;
	CreateThread(NULL, 0, this->ServerThreadedSender, &connectionParameters, 0, 0);


	int recvByteCount = 0;
	while (true) {
		Sleep(500);
		this->recvSocket<PARAMETERS>(connectionParameters, recvByteCount);
	}

	return this->destroy();
}


void Server::connectionListen(SOCKET socket)
{
	if (listen(socket, 1) == SOCKET_ERROR) {
		throw SocketListenException();
	}
	else {
		cout << "Waiting for a client to connect..." << endl;
	}
}


int Server::acceptConnection(SOCKET socket)
{
	SOCKET accpt = accept(socket, NULL, NULL);
	if (accpt == INVALID_SOCKET) {
		WSAGetLastError();
		throw ConnectionException();
		return -1;
	}
	return accpt;
}


DWORD WINAPI Server::ServerThreadedSender(void * parameters)
{
	PARAMETERS* params = (PARAMETERS*)parameters;
	SOCKET socket = (SOCKET)params->socket;
	Server server(params->port, params->ipAddr);
	int sendByteCount = 0;
	while (true) {
		Sleep(500);
		sendByteCount = send(socket, (char *)&server, sizeof(Server), 0);
		if (sendByteCount == SOCKET_ERROR) {
			WSAGetLastError();
			closesocket(socket);
			throw SendException();
		}
		else {
			string msg;
			cin >> msg;
			server.message = params->name + ": " + msg;
		}
	}
};
