#pragma once
#include <iostream>
#include "Comms.h"
#include "pch.h"

using namespace std;

class Client : public Comms{
public:
	Client() {
	};
	~Client() {
	};
	int Main();
	struct PARAMETERS
	{
		LPVOID socket;
		Client * inst;
		int sizeOf;
	};
private:
};
