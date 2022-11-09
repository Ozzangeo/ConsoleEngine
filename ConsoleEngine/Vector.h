#ifndef ___VECTOR___
#define ___VECTOR___

#define SIMD

#include "stdafx.h"

class alignas(16) Vector4f;
class alignas(16) Vector4i {
public:
	union {
		__m128i vecp;
		struct {
			int x;
			int y;
			int z;
			int w;
		};
	};

	Vector4i() : vecp(_mm_set1_epi32(0)) {}
	Vector4i(int set, int w = 0) : vecp(_mm_set_epi32(w, set, set, set)) {}
	Vector4i(__m128i other) : vecp(other) {}
	Vector4i(__m128 other) : vecp(_mm_cvtps_epi32(other)) {}
	Vector4i(int _x, int _y, int _z, int _w = 1) : vecp(_mm_set_epi32(_w, _z, _y, _x)) {}

	Vector4i operator+(const Vector4i& ref);
	Vector4i operator-(const Vector4i& ref);

	Vector4i& operator+=(const Vector4i& ref);
	Vector4i& operator-=(const Vector4i& ref);

	void* operator new(const size_t size);
	void* operator new[](const size_t size);

	void operator delete(void* other);
	void operator delete[](void* other);

	operator Vector4f();
};
class alignas(16) Vector4f {
public:
	union {
		__m128 vecp;
		struct {
			float x;
			float y;
			float z;
			float w;
		};
	};

	Vector4f() : vecp(_mm_set_ps1(0.0f)) {}
	Vector4f(float set) : vecp(_mm_set_ps1(set)) {}
	Vector4f(__m128 other) : vecp(other) {}
	Vector4f(__m128i other) : vecp(_mm_cvtepi32_ps(other)) {}
	Vector4f(float _x, float _y, float _z, float _w = 1.0f) : vecp(_mm_set_ps(_w, _z, _y, _x)) {}

	Vector4f operator+(const Vector4f& ref);
	Vector4f operator-(const Vector4f& ref);
	Vector4f operator+(const __m128& ref);
	Vector4f operator-(const __m128& ref);
	Vector4f operator*(const float& ref);
	Vector4f operator/(const float& ref);

	Vector4f& operator+=(const Vector4f& ref);
	Vector4f& operator-=(const Vector4f& ref);
	Vector4f& operator+=(const __m128& ref);
	Vector4f& operator-=(const __m128& ref);
	Vector4f& operator*=(const float& ref);
	Vector4f& operator/=(const float& ref);

	bool operator==(const Vector4f& ref);
	bool operator!=(const Vector4f& ref);

	void* operator new(const size_t size);
	void* operator new[](const size_t size);

	void operator delete(void* other);
	void operator delete[](void* other);

	inline Vector4f round();

	operator Vector4i();
};

inline Vector4f Vector4f::round() {
	return _mm_round_ps(vecp, 0);
}

#endif // !___VECTOR___




