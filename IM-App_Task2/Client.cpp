#include "Client.h"

int Client::Connect() {
	PARAMETERS params;
	sockaddr_in service;
	SOCKET clientSocket;

	int port = this->getPort();
	string addr = this->getAddr();

	this->DLLFinder();
	clientSocket = this->setupSocket();
	service = this->setupService(port, addr);
	this->establishConnection(clientSocket, service);

	cout << "You've connected to a client. Please enter a display name: ";
	cin >> this->name;

	
	params.socket = (LPVOID)clientSocket;
	params.inst = this;
	params.sizeOf = sizeof(Client);
	params.name = this->name;
	params.port = port;
	params.ipAddr = addr;
	CreateThread(NULL, 0, this->ClientThreadedSender, &params, 0, 0);
	
	int recvByteCount = 0;
	while (true) {
		Sleep(500);
		this->recvSocket<PARAMETERS>((SOCKET)params.socket, params, recvByteCount);
	}

	return this->destroy((SOCKET)params.socket);
}

int Client::establishConnection(SOCKET socket, sockaddr_in service)
{
	if (connect(socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		cout << "Client: connect() - Failed to connect." << endl;
		WSACleanup();
		return 0;
	}
	return 1;
}

DWORD WINAPI Client::ClientThreadedSender(void * param)
{
	PARAMETERS* params = (PARAMETERS*)param;
	SOCKET socket = (SOCKET)params->socket;
	Client client(params->port, params->ipAddr);
	string msg;
	int sendByteCount = 0;
	while (client.terminate == false) {
		Sleep(500);
		sendByteCount = send(socket, (char *)&client, sizeof(Client), 0);
		if (sendByteCount == SOCKET_ERROR) {
			cout << "Client send error " << WSAGetLastError() << endl;
			break;
		}
		else {
			cin >> msg;
			client.message = params->name + ": " + msg;
			if (msg == "QUIT") {
				client.terminate = true;
				exit(0);
			}
		}
	}
	closesocket(socket);
	return 0;
};
