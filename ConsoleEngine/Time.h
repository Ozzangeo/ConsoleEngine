#ifndef ___TIME___
#define ___TIME___

#include "stdafx.h"

class Time {
	friend class Engine;
private:
	static float DeltaTime;
	static float ExecutionTime;
public:
	static void Delay(float millisecond);
	static float GetDeltaTime();
	static float GetExecutionTime();
};

#endif // !___TIME___
