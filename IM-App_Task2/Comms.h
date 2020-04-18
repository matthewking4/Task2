#pragma once
#include <string>
#include <iostream>
#include "pch.h"
#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
#include <functional>

using namespace std;

class Comms {
public:
	string message = "";
	string lastSender = "";
	//template<typename B>
	//void sendSocket(SOCKET socket, B* params, int sendByteCount, std::function<void> callback) {
	//	if (socket != INVALID_SOCKET) {
	//		sendByteCount = send(socket, (char *)params->inst, params->sizeOf, 0);
	//		if (sendByteCount == SOCKET_ERROR) {
	//			cout << "Server send error " << WSAGetLastError() << endl;
	//			closesocket(socket);
	//		}
	//		else {
	//			callback(params->name);
	//		}
	//	}
	//}

	template<typename T>
	void recvSocket(SOCKET socket, T params, int recvByteCount) {
		if (socket != INVALID_SOCKET) {
			recvByteCount = recv(socket, (char *)params.inst, params.sizeOf, 0);
		if (recvByteCount == SOCKET_ERROR) {
			cout << "Server send error " << WSAGetLastError() << endl;
			closesocket(socket);
		}
		else {
			if (params.inst->message != "") {
				cout << params.inst->message << endl;

			}
		}
		}
	}
private:
};
