#pragma once
#include <string>
#include <iostream>
#include "Comms.h"
#include "pch.h"

using namespace std;

class Server : public Comms {
public:
	Server() {
	};
	~Server() {
	};
	int Main();
	string name;
	struct PARAMETERS
	{
		LPVOID socket;
		Server * inst;
		int sizeOf;
	};
private:
};