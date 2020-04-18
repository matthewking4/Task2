#pragma once
#include <string>
#include <iostream>
#include "Comms.h"
#include "pch.h"

using namespace std;

class Server : public Comms {
public:
	Server() {
	};
	~Server() {
	};
	int Main();
	string name;
	struct PARAMETERS
	{
		LPVOID socket;
		Server* inst;
		int sizeOf;
		string name;
	};
	static DWORD WINAPI ServerThreadedSender(void* param) {
		PARAMETERS* params = (PARAMETERS*)param;
		SOCKET socket = (SOCKET)params->socket;
		Server server;
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
				server.message = params->name + ": " + msg ;
			}
		}
		closesocket(socket);
		return 0;
	};
private:
};