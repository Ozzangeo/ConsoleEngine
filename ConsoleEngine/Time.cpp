#include "Time.h"

using namespace std::chrono;

float Time::DeltaTime = 1.0f;
float Time::ExecutionTime = 1.0f;

void Time::Delay(float millisecond) {
	system_clock::time_point start = system_clock::now();
	millisecond *= 0.001f;

	while (duration<float>(system_clock::now() - start).count() < millisecond);
}

float Time::GetDeltaTime() { return DeltaTime; }
float Time::GetExecutionTime() { return ExecutionTime; }
