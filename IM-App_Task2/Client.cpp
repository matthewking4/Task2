#include "pch.h"
#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
#include "Client.h"


int Client::Main() {
	SOCKET clientSocket;
	int port = 55555;
	WSADATA wsaData;
	Client client;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		cout << "The Winsock dll not found!" << endl;
		return 0;
	}
	else {
		cout << "The Winsock dll found!" << endl;
		cout << "The status: " << wsaData.szSystemStatus << endl;
	}

	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "socket() is OK!" << endl;
	}

	DWORD threadId;
	sockaddr_in clientService;
	PARAMETERS params;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
		cout << "Client: connect() - Failed to connect." << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "You've connected to a host. Please enter a display name." << endl;
		cin >> client.name;
		params.socket = (LPVOID)clientSocket;
		params.inst = &client;
		params.sizeOf = sizeof(Client);

		CreateThread(NULL, 0, ThreadedSender<PARAMETERS>, &params, 0, &threadId);
	}



	int recvByteCount = 0;
	while (true) {
		Sleep(500);
		client.recvSocket<PARAMETERS>((SOCKET)params.socket, params, recvByteCount);
	}
	closesocket((SOCKET)params.socket);


	system("pause");
	WSACleanup();
	return 0;

}