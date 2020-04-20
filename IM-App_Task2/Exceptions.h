#pragma once
#include <exception>

using namespace std;
//Common Exceptions
class WINSOCKFoundException : public exception {
public:
	virtual const char* what() const throw() {
		return "Genric Error - The Winsock dll was not found!";
	}
};

class InvalidSocketException : public exception {
public:
	virtual const char* what() const throw() {
		return "Genric Error - Invalid Socket!";
	}
};

class SocketErrorException : public exception {
public:
	virtual const char* what() const throw() {
		return "Genric Error - Socket Error occurred!";
	}
};

class SendException : public exception {
public:
	virtual const char* what() const throw() {
		return "Genric Error - message failed to send!";
	}
};

//Client Exceptions
class ConnectException : public exception {
public:
	virtual const char* what() const throw() {
		return "Client error - failed to connect to the host server!";
	}
};

//Server Exceptions
class BindingException : public exception {
public:
	virtual const char* what() const throw() {
		return "Server error - failed to bind!";
	}
};

class SocketListenException : public exception {
public:
	virtual const char* what() const throw() {
		return "Server error - failed to listen on socket!";
	}
};

class ConnectionException : public exception {
public:
	virtual const char* what() const throw() {
		return "Server error - Issues when accepting connection!";
	}
};