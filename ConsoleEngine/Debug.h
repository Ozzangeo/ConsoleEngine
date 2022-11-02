#ifndef ___DEBUG___
#define ___DEBUG___

#include "stdafx.h"

using namespace std;

class Debug {
	friend class Engine;
private:
	static ofstream debug;
	static void Release();

public:
	static void Log(string log);

};

#endif // !___DEBUG___
	