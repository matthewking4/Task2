#pragma once
#include <string>
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
	string name;
	struct PARAMETERS
	{
		LPVOID socket;
		Client * inst;
		int sizeOf;
	};
private:
};
