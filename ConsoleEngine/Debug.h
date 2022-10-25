#ifndef ___DEBUG___
#define ___DEBUG___

#include "stdafx.h"

using namespace std;

class Debug {
private:
	static ofstream debug;
public:
	static void Log(string log);

	static void Release();
};

#endif // !___DEBUG___
	