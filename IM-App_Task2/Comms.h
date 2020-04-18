#pragma once
#include <string>
#include <iostream>
#include "pch.h"
#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"

using namespace std;

template<typename B>
DWORD WINAPI ThreadSender(void* param) {
	B* params = (B*)param;
	SOCKET socket = (SOCKET)params->socket;
	int byteCount;
	while (true) {
		Sleep(500);
		comms.sendSocket((SOCKET)params->socket, params, byteCount)
	}
	closesocket(socket);
	return 0;
}



class Comms {
public:
	string hostName = "";
	string clientName = "";
	string message;

	template<typename T>
	void sendSocket(SOCKET socket, T params, int sendByteCount) {
		if (socket != INVALID_SOCKET) {
			sendByteCount = send(socket, (char *)params->inst, params->sizeOf, 0);
			if (sendByteCount == SOCKET_ERROR) {
				cout << "Server send error " << WSAGetLastError() << endl;
				closesocket(socket);
				return -1;
			}
			else {
				cin >> params->inst->message;
			}
		}
	}

	template<typename T>
	void recvSocket(SOCKET socket, T params, int recvByteCount) {
		if (socket != INVALID_SOCKET) {
			recvByteCount = recv(socket, (char *)params.inst, params.sizeOf, 0);
		if (recvByteCount == SOCKET_ERROR) {
			cout << "Server send error " << WSAGetLastError() << endl;
			closesocket(socket);
		}
		else {
			cout << "Last Message:  " << params.inst->message << endl;
		}
		}
	}
private:
};
