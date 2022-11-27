#include "Matrix.h"

// [ Matrix4x4f ]
Matrix4x4f Matrix4x4f::operator+(const Matrix4x4f& ref) {
	return {
		_mm_add_ps(matp[0], ref.matp[0]),
		_mm_add_ps(matp[1], ref.matp[1]),
		_mm_add_ps(matp[2], ref.matp[2]),
		_mm_add_ps(matp[3], ref.matp[3])
	};
}
Matrix4x4f Matrix4x4f::operator-(const Matrix4x4f& ref) {
	return {
		_mm_sub_ps(matp[0], ref.matp[0]),
		_mm_sub_ps(matp[1], ref.matp[1]),
		_mm_sub_ps(matp[2], ref.matp[2]),
		_mm_sub_ps(matp[3], ref.matp[3])
	};
}
Matrix4x4f Matrix4x4f::operator*(const float& ref) {
	Vector3f vec(ref);

	return {
		_mm_mul_ps(matp[0], vec.vecp),
		_mm_mul_ps(matp[1], vec.vecp),
		_mm_mul_ps(matp[2], vec.vecp),
		_mm_mul_ps(matp[3], vec.vecp)
	};
}
Matrix4x4f Matrix4x4f::operator*(const Matrix4x4f& ref) {
	Matrix4x4f transpose(
		ref.f11, ref.f21, ref.f31, ref.f41,
		ref.f12, ref.f22, ref.f32, ref.f42,
		ref.f13, ref.f23, ref.f33, ref.f43,
		ref.f14, ref.f24, ref.f34, ref.f44);

#define	matDP(a, b) _mm_dp_ps(matp[a], transpose.matp[b], 0xFF).m128_f32[0]
	return {
		matDP(0, 0), matDP(0, 1), matDP(0, 2), matDP(0, 3),
		matDP(1, 0), matDP(1, 1), matDP(1, 2), matDP(1, 3),
		matDP(2, 0), matDP(2, 1), matDP(2, 2), matDP(2, 3),
		matDP(3, 0), matDP(3, 1), matDP(3, 2), matDP(3, 3)
	};
}

void* Matrix4x4f::operator new(const size_t size) {
	return _aligned_malloc(size, 16);
}
void* Matrix4x4f::operator new[](const size_t size) {
	return _aligned_malloc(size, 16);
}

void Matrix4x4f::operator delete(void* other) {
	_aligned_free(other);
}
void Matrix4x4f::operator delete[](void* other) {
	_aligned_free(other);
}

Vector3f operator*(const Vector3f& vec, const Matrix4x4f& mat) {
	Matrix4x4f transpose(
		mat.f11, mat.f21, mat.f31, mat.f41,
		mat.f12, mat.f22, mat.f32, mat.f42,
		mat.f13, mat.f23, mat.f33, mat.f43,
		mat.f14, mat.f24, mat.f34, mat.f44);
	
	return { _mm_dp_ps(vec.vecp, transpose.matp[0], 0xFF).m128_f32[0],
			 _mm_dp_ps(vec.vecp, transpose.matp[1], 0xFF).m128_f32[0],
			 _mm_dp_ps(vec.vecp, transpose.matp[2], 0xFF).m128_f32[0],
			 _mm_dp_ps(vec.vecp, transpose.matp[3], 0xFF).m128_f32[0] };
}
