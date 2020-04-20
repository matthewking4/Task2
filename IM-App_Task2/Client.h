#pragma once
#include "Comms.h"
using namespace std;


class Client : public Comms{
public:
	Client(int portNumb, string ipAddr) : Comms(portNumb, ipAddr) {
		// Required for inhertiance. 
	};
	int Connect();
private:
	string name;
	void establishConnection(SOCKET socket, sockaddr_in service);
	static DWORD WINAPI ClientThreadedSender(void* param);
	struct PARAMETERS
	{
		LPVOID socket;
		Client * inst;
		int sizeOf;
		string name;
		int port;
		string ipAddr;
		bool term;
	};
};
