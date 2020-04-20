#include "pch.h"
#include "Server.h"
#include "Client.h"
using namespace std;

int main() {
	int portNumb;
	string ipAddr;
	cout << "Welcome to a C++ Instant Messanger - created by Matthew King" << endl;
	cout << "You're able to lunch the server/client via the use of the Server bool flag within the PCH" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;

	cout << "Please input a desired port number (eg: 55555): ";
	cin >> portNumb;
	cout << "Please input a desired IP Address (eg: 127.0.0.1): ";
	cin >> ipAddr;


	try {
		if (SERVER) {
			cout << "----------------------------------Server Launching-------------------------------" << endl;
			Server server(portNumb, ipAddr);
			server.Connect();
		}
		else {
			cout << "----------------------------------Client Launching-------------------------------" << endl;
			Client client(portNumb, ipAddr);
			client.Connect();
		}
	}
	//error handling - avoids duplication in client & server
	//Log out an error an code - this could be used to assit debugging a production issue
	catch (WINSOCKFoundException& e) {
		cout << "Error(1): " << e.what() << endl;
	}
	catch (InvalidSocketException& e) {
		cout << "Error(2): " << e.what() << endl;

	}
	catch (SocketErrorException& e) {
		cout << "Error(3): " << e.what() << endl;

	}
	catch (ConnectException& e) {
		cout << "Error(4): " << e.what() << endl;

	}
	catch (SendException& e) {
		cout << "Error(5): " << e.what() << endl;

	}
	catch (BindingException& e) {
		cout << "Error(6): " << e.what() << endl;

	}
	catch (SocketListenException& e) {
		cout << "Error(7): " << e.what() << endl;

	}
	catch (ConnectionException& e) {
		cout << "Error(8): " << e.what() << endl;

	}
}
