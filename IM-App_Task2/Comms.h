#pragma once
#include "pch.h"
#include "stdafx.h"
#include <string>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Exceptions.h"
using namespace std;

class Comms {
public:
	Comms(int portNumb, string ipAddr){
		this->setPort(portNumb);
		this->setAddr(ipAddr);
	}
	~Comms() {

	}
	string message = "";
	bool terminate = false;
	
	//Getters
	virtual int getPort();
	virtual string getAddr();

	//Intilisation Methods
	virtual void WinsockSetup();
	virtual SOCKET socketSetup();
	virtual sockaddr_in setupService(int port, string ipAddr);

	//Templated receiving socket
	template<typename T>
	void recvSocket(T parameters, int recvByteCount);

	//Shared Teardown
	virtual int destroy();

private:
	//Setters
	void setPort(int portNumb);
	void setAddr(string ipAddr);

	int port;
	string ip;
};

template<typename T>
inline void Comms::recvSocket(T parameters, int recvByteCount) {
	SOCKET socket = (SOCKET)parameters.socket;
	if (socket != INVALID_SOCKET) {
		recvByteCount = recv(socket, (char *)parameters.inst, parameters.sizeOf, 0);
		if (recvByteCount == SOCKET_ERROR) {
			 WSAGetLastError()
			closesocket(socket);
			throw SocketErrorException();
			exit(0);
		}
		else {
			if (parameters.inst->message != "") {
				cout << parameters.inst->message << endl;

			}
		}
	}
}