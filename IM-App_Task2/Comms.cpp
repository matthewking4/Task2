#include "Comms.h"

void Comms::setPort(int portNumb)
{
	port = portNumb;
}

int Comms::getPort()
{
	return port;
}

void Comms::setAddr(string ipAddr)
{
	ip = ipAddr;
}

string Comms::getAddr()
{
	return ip;
}

int Comms::DLLFinder()
{
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
		return 1;
		//cout << "The Winsock dll found!" << endl;
		//cout << "The status: " << wsaData.szSystemStatus << endl;
	}
}


SOCKET Comms::setupSocket()
{
	SOCKET soc = INVALID_SOCKET;
	soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (soc == INVALID_SOCKET) {
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "socket() is OK!" << endl;
		return soc;
	}
}

sockaddr_in Comms::setupService(int port, string ipAddr)
{
	std::wstring ipstr = std::wstring(ipAddr.begin(), ipAddr.end());
	const wchar_t* ipcstr = ipstr.c_str();

	sockaddr_in s;
	s.sin_family = AF_INET;
	InetPton(AF_INET, ipcstr, &s.sin_addr.s_addr);
	s.sin_port = htons(port);
	return s;
}

int Comms::destroy(SOCKET socket)
{
	closesocket(socket);
	WSACleanup();
	return 0;
}