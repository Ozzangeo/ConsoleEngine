#ifndef ___STDAFX___
#define ___STDAFX___

#include <iostream>
#include <fstream>

#include <cstdlib>
#include <string>
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

#include <xmmintrin.h>

namespace Handle {
	const HANDLE OUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
	const HANDLE INPUT = GetStdHandle(STD_INPUT_HANDLE);
};

#endif // !___STDAFX___
