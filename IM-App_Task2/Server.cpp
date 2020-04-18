#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
#include "Server.h"
#include "pch.h"
#include "stdafx.h"

int Server::Main() {
	SOCKADDR_STORAGE from;
	int retval, fromlen, socket_type;
	char servstr[NI_MAXSERV], hoststr[NI_MAXHOST];


	SOCKET serverSocket, acceptSocket;
	int port = 55555;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		//need to do error handling
		cout << "ERROR: The Winsock dll not found!" << endl;
		return 0;
	}
	else {
		//cout << "The Winsock dll found!" << endl;
		//cout << "The status: " << wsaData.szSystemStatus << endl;
	}

	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET) {
		//need to do error handling
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else {
		//cout << "socket() is OK!" << endl;
	}


	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if (::bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		//need to do error handling
		cout << "bind() failed: " << WSAGetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	else {
		//cout << "bind() is OK!" << endl;
	}

	if (listen(serverSocket, 1) == SOCKET_ERROR)
		cout << "listen(): Error listening on socket " << WSAGetLastError() << endl;
	else
		cout << "Waiting for a client to connect..." << endl;
	Server server;
	PARAMETERS params;

	DWORD threadId;
	acceptSocket = accept(serverSocket, NULL, NULL);
	if (acceptSocket == INVALID_SOCKET) {
		//need to do error handling
		cout << stderr << " accept failed: " << WSAGetLastError() << endl;
		return -1;
	}
	else {
		cout << "You've connected to a client. Please enter a display name." << endl;
		cin >> server.name;

		params.socket = (LPVOID)acceptSocket;
		params.inst = &server;
		params.sizeOf = sizeof(Server);
		params.name = server.name;

		CreateThread(NULL, 0, server.ServerThreadedSender, &params, 0, &threadId);
	}

	int recvByteCount = 0;
	while (true) {
		Sleep(500);
		server.recvSocket<PARAMETERS>((SOCKET)params.socket, params, recvByteCount);
	}
	closesocket((SOCKET)params.socket);

	system("pause");
	WSACleanup();


	return 0;
}