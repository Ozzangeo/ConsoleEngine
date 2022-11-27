#ifndef ___STDAFX___
#define ___STDAFX___

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ws2_32.lib")

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

// 멀티스레딩 헤더들
#include <mutex>
#include <thread>

// 자료구조 헤더들
#include <vector>
#include <list>
#include <queue>

// 사운드 재생 헤더들
#include <mmsystem.h>
#include <Digitalv.h>
#include <mciapi.h>

// 서버 헤더들
#include <WS2tcpip.h>
#include <WinSock2.h>

// SIMD 헤더들
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
