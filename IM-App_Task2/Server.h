#pragma once
#include <iostream>
#include "Comms.h"
#include "pch.h"
#include <type_traits>

using namespace std;

class Server : public Comms {
public:
	Server() {
	};
	~Server() {
	};
	int Main();
	struct PARAMETERS
	{
		LPVOID socket;
		Server * inst;
		int sizeOf;
	};
private:
};