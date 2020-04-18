#pragma once
#include "Comms.h"
using namespace std;

class Server : public Comms {
public:
	Server(int portNumb, string ipAddr) : Comms(portNumb, ipAddr) {
	
	};
	int Connect();
private:
	string name;
	void connectionListen(SOCKET socket);
	int acceptConnection(SOCKET socket);
	static DWORD WINAPI ServerThreadedSender(void* param);

	struct PARAMETERS
	{
		LPVOID socket;
		Server* inst;
		int sizeOf;
		string name;
		int port;
		string ipAddr;
	};
};