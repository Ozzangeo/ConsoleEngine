#ifndef ___VECTOR___
#define ___VECTOR___

#define SIMD

#include "stdafx.h"

class alignas(16) Vector3f;
class alignas(16) Vector3i {
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

	Vector3i() : vecp(_mm_set1_epi32(1)) {}
	Vector3i(int set, int w = 1) : vecp(_mm_set_epi32(w, set, set, set)) {}
	Vector3i(__m128i other) : vecp(other) {}
	Vector3i(__m128 other) : vecp(_mm_cvtps_epi32(other)) {}
	Vector3i(int _x, int _y, int _z, int _w = 1) : vecp(_mm_set_epi32(_w, _z, _y, _x)) {}

	Vector3i operator+(const Vector3i& ref);
	Vector3i operator-(const Vector3i& ref);

	Vector3i& operator+=(const Vector3i& ref);
	Vector3i& operator-=(const Vector3i& ref);

	void* operator new(const size_t size);
	void* operator new[](const size_t size);

	void operator delete(void* other);
	void operator delete[](void* other);

	operator Vector3f();
};
class alignas(16) Vector3f {
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

	Vector3f() : vecp(_mm_set_ps1(1.0f)) {}
	Vector3f(float set) : vecp(_mm_set_ps1(set)) {}
	Vector3f(__m128 other) : vecp(other) {}
	Vector3f(__m128i other) : vecp(_mm_cvtepi32_ps(other)) {}
	Vector3f(float _x, float _y, float _z, float _w = 1.0f) : vecp(_mm_set_ps(_w, _z, _y, _x)) {}

	Vector3f operator+(const Vector3f& ref);
	Vector3f operator-(const Vector3f& ref);
	Vector3f operator+(const __m128& ref);
	Vector3f operator-(const __m128& ref);
	Vector3f operator*(const float& ref);
	Vector3f operator/(const float& ref);

	Vector3f& operator+=(const Vector3f& ref);
	Vector3f& operator-=(const Vector3f& ref);
	Vector3f& operator+=(const __m128& ref);
	Vector3f& operator-=(const __m128& ref);
	Vector3f& operator*=(const float& ref);
	Vector3f& operator/=(const float& ref);

	bool operator==(const Vector3f& ref);
	bool operator!=(const Vector3f& ref);

	void* operator new(const size_t size);
	void* operator new[](const size_t size);

	void operator delete(void* other);
	void operator delete[](void* other);

	inline Vector3f product2D();
	inline float dotProduct(const Vector3f& ref);
	inline float size();
	inline Vector3f normalize();
	inline Vector3f round();

	operator Vector3i();
};

inline Vector3f Vector3f::product2D() {
	return { -y, x, z, 0 };
}
inline float Vector3f::dotProduct(const Vector3f& ref) {
	Vector3f res = _mm_mul_ps(this->vecp, ref.vecp);
	return res.x + res.y + res.z;
}
inline float Vector3f::size() {
	Vector3f size = _mm_sqrt_ps(_mm_pow_ps(this->vecp, _mm_set_ps1(2)));

	return size.x + size.y + size.z;
}
inline Vector3f Vector3f::normalize() {
	return _mm_div_ps(this->vecp, _mm_set_ps1(size()));
}
inline Vector3f Vector3f::round() {
	return _mm_round_ps(vecp, 0);
}

#endif // !___VECTOR___
