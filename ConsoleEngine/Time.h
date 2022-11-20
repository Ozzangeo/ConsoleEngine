#ifndef ___TIME___
#define ___TIME___

#include "stdafx.h"

class Time {
	friend class ConsoleEngine;
private:
	static float DeltaTime;
	static float ExecutionTime;
public:
	static void Delay(float millisecond);
	inline static float GetDeltaTime();
	inline static float GetExecutionTime();
};

inline float Time::GetDeltaTime() { return DeltaTime; }
inline float Time::GetExecutionTime() { return ExecutionTime; }

#endif // !___TIME___
