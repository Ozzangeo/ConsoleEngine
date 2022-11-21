#ifndef ___DEBUG___
#define ___DEBUG___

#include "stdafx.h"

using namespace std;

class Debug {
	friend class ConsoleEngine;
private:
	static bool isDisableDebugging;
	static ofstream debug;
	static void Release();

public:
	static void Log(string log);
	static void DisableDebugging();
};

#endif // !___DEBUG___
	