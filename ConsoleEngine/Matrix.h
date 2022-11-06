#ifndef ___MATRIX___
#define ___MATRIX___

#include "stdafx.h"
#include "Vector.h"

class alignas(16) Matrix4x4f {
public:
	union {
		__m128 matp[4];
		struct {
			float f11, f12, f13, f14;
			float f21, f22, f23, f24;
			float f31, f32, f33, f34;
			float f41, f42, f43, f44;
		};
	};

	Matrix4x4f() : matp{ _mm_set_ps1(0.0f), _mm_set_ps1(0.0f), _mm_set_ps1(0.0f), _mm_set_ps1(0.0f) } {}
	Matrix4x4f(float set) : matp{ _mm_set_ps1(set), _mm_set_ps1(set), _mm_set_ps1(set), _mm_set_ps1(set) } {}
	Matrix4x4f(__m128 vec1, __m128 vec2, __m128 vec3, __m128 vec4) : matp{ vec1, vec2, vec3, vec4 } {}
	Matrix4x4f(
		float _f11, float _f12, float _f13, float _f14,
		float _f21, float _f22, float _f23, float _f24,
		float _f31, float _f32, float _f33, float _f34,
		float _f41, float _f42, float _f43, float _f44) :
		matp{
		_mm_set_ps(_f14, _f13, _f12, _f11),
		_mm_set_ps(_f24, _f23, _f22, _f21),
		_mm_set_ps(_f34, _f33, _f32, _f31),
		_mm_set_ps(_f44, _f43, _f42, _f41) } {
	}

	Matrix4x4f operator+(const Matrix4x4f& ref);
	Matrix4x4f operator-(const Matrix4x4f& ref);
	Matrix4x4f operator*(const float& ref);
	Matrix4x4f operator*(const Matrix4x4f& ref);

	void* operator new(const size_t size);
	void* operator new[](const size_t size);

	void operator delete(void* other);
	void operator delete[](void* other);
};

Vector4f operator*(const Vector4f& vec, const Matrix4x4f& mat);

#endif // !___MATRIX___