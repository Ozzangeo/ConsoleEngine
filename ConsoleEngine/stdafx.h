#ifndef ___STDAFX___
#define ___STDAFX___

#pragma comment(lib, "winmm.lib")

#include <iostream>
#include <fstream>

#include <cstdlib>
#include <string>
#include <atlstr.h>
#include <cmath>
#include <Windows.h>

#include <memory>
#include <chrono>
#include <typeinfo>

#include <mutex>
#include <thread>
#include <future>
#include <functional>
#include <condition_variable>

#include <vector>
#include <list>
#include <queue>

#include <mmsystem.h>
#include <Digitalv.h>
#include <mciapi.h>

#include <nmmintrin.h>

namespace Handle {
	const HANDLE OUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
	const HANDLE INPUT = GetStdHandle(STD_INPUT_HANDLE);
};

template<typename T>
void Swap(T* a, T* b) {
	T temp = *a;
	*a = *b;
	*b = temp;
}

#endif // !___STDAFX___
