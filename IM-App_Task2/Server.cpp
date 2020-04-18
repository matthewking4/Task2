#include "Server.h"


int Server::Connect() {
	PARAMETERS params;
	sockaddr_in service;
	SOCKET serverSocket;

	int port = this->getPort();
	string addr = this->getAddr();

	this->DLLFinder();
	serverSocket = this->setupSocket();
	service = this->setupService(port, addr);

	if (::bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		cout << "bind() failed: " << WSAGetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}

	this->connectionListen(serverSocket);
	SOCKET acceptSocket = this->acceptConnection(serverSocket);

	cout << "You've connected to a client. Please enter a display name: ";
	cin >> this->name;

	params.socket = (LPVOID)acceptSocket;
	params.inst = this;
	params.sizeOf = sizeof(Server);
	params.name = this->name;
	params.port = port;
	params.ipAddr = addr;
	CreateThread(NULL, 0, this->ServerThreadedSender, &params, 0, 0);


	int recvByteCount = 0;
	while (true) {
		Sleep(500);
		this->recvSocket<PARAMETERS>((SOCKET)params.socket, params, recvByteCount);
	}

	return this->destroy((SOCKET)params.socket);
}


void Server::connectionListen(SOCKET socket)
{
	if (listen(socket, 1) == SOCKET_ERROR) {
		cout << "listen(): Error listening on socket " << WSAGetLastError() << endl;
	}
	else {
		cout << "Waiting for a client to connect..." << endl;
	}
}


int Server::acceptConnection(SOCKET socket)
{
	SOCKET accpt = accept(socket, NULL, NULL);
	if (accpt == INVALID_SOCKET) {
		cout << stderr << " accept failed: " << WSAGetLastError() << endl;
		return -1;
	}
	return accpt;
}


DWORD WINAPI Server::ServerThreadedSender(void * param)
{
	PARAMETERS* params = (PARAMETERS*)param;
	SOCKET socket = (SOCKET)params->socket;
	Server server(params->port, params->ipAddr);
	int sendByteCount = 0;
	while (true) {
		Sleep(500);
		sendByteCount = send(socket, (char *)&server, sizeof(Server), 0);
		if (sendByteCount == SOCKET_ERROR) {
			cout << "Server send error " << WSAGetLastError() << endl;
			closesocket(socket);
			return -1;
		}
		else {
			string msg;
			cin >> msg;
			server.message = params->name + ": " + msg;
		}
	}
	closesocket(socket);
	return 0;
};
