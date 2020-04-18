#include "pch.h"
#include "Server.h"
#include "Client.h"
#include "stdafx.h"
#include <windows.h>
#include <iostream>

#define SERVER false

using namespace std;

int main() {
	if (SERVER) {
		Server *server = new Server();
		server->Main();
	}
	else {
		Client *client = new Client();
		client->Main();
	}
}