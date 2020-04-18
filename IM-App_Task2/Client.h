#pragma once
#include <string>
#include <iostream>
#include "Comms.h"
#include "pch.h"

using namespace std;


class Client : public Comms{
public:
	Client() {
	};
	~Client() {
	};
	int Main();
	string name;
	struct PARAMETERS
	{
		LPVOID socket;
		Client * inst;
		int sizeOf;
		string name;
	};

	static DWORD WINAPI ClientThreadedSender(void* param) {
		PARAMETERS* params = (PARAMETERS*)param;
		SOCKET socket = (SOCKET)params->socket;
		Client client;
		int sendByteCount = 0;
		while (true) {
			Sleep(500);
			sendByteCount = send(socket, (char *)&client, sizeof(Client), 0);
			if (sendByteCount == SOCKET_ERROR) {
				cout << "Server send error " << WSAGetLastError() << endl;
				closesocket(socket);
				return -1;
			}
			else {
				string msg;
				cin >> msg;
				client.message = params->name + ": " + msg;
			}
		}
		closesocket(socket);
		return 0;
	};
private:
};
