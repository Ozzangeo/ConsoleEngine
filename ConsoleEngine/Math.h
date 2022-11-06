#ifndef ___MATH___
#define ___MATH___

#include "stdafx.h"
#include "Debug.h"

class Math {
	friend class ConsoleEngine;
private:

	static void Release();
public:
	static const float PI;
	static const float* cosb;
	static const float* sinb;
	static const float* tanb;

};

#endif // !___MATH___


