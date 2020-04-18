#include "pch.h"
#include "Server.h"
#include "Client.h"
#define SERVER true
using namespace std;



/*


*/
int main() {
	int portNumb;
	string ipAddr;
	cout << "Welcome to a C++ Instant Messanger - created by Matthew King" << endl;
	cout << "Please input a desired port number (eg: 55555): ";
	cin >> portNumb;
	cout << "Please input a desired IP Address (eg: 127.0.0.1): ";
	cin >> ipAddr;

	if (SERVER) {
		Server server(portNumb, ipAddr);
		server.Connect();
	}
	else {
		Client client(portNumb, ipAddr);
		client.Connect();
	}
}
