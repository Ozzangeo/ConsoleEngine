#include "Vector.h"

// [ Vector4i ]
Vector4i Vector4i::operator+(const Vector4i& ref) {
	return _mm_add_epi32(vecp, ref.vecp);
}
Vector4i Vector4i::operator-(const Vector4i& ref) {
	return _mm_sub_epi32(vecp, ref.vecp);
}

Vector4i& Vector4i::operator+=(const Vector4i& ref) {
	return (*this = _mm_add_epi32(vecp, ref.vecp));
}
Vector4i& Vector4i::operator-=(const Vector4i& ref) {
	return (*this = _mm_sub_epi32(vecp, ref.vecp));
}

void* Vector4i::operator new(const size_t size) {
	return _aligned_malloc(size, 16);
}
void* Vector4i::operator new[](const size_t size) {
	return _aligned_malloc(size, 16);
}

void Vector4i::operator delete(void* other) {
	_aligned_free(other);
}
void Vector4i::operator delete[](void* other) {
	_aligned_free(other);
}

Vector4i::operator Vector4f() {
	return _mm_cvtepi32_ps(vecp);
}


// [ Vector4f ]
Vector4f Vector4f::operator+(const Vector4f& ref) {
	return _mm_add_ps(vecp, ref.vecp);
}
Vector4f Vector4f::operator-(const Vector4f& ref) {
	return _mm_sub_ps(vecp, ref.vecp);
}
Vector4f Vector4f::operator+(const __m128& ref) {
	return _mm_add_ps(vecp, ref);
}
Vector4f Vector4f::operator-(const __m128& ref) {
	return _mm_sub_ps(vecp, ref);
}
Vector4f Vector4f::operator*(const float& ref) {
	__m128 other = _mm_set1_ps(ref);
	return _mm_mul_ps(vecp, other);
}
Vector4f Vector4f::operator/(const float& ref) {
	__m128 other = _mm_set1_ps(ref);
	return _mm_div_ps(vecp, other);
}

Vector4f& Vector4f::operator+=(const Vector4f& ref) {
	return (*this = _mm_add_ps(vecp, ref.vecp));
}
Vector4f& Vector4f::operator-=(const Vector4f& ref) {
	return (*this = _mm_sub_ps(vecp, ref.vecp));
}
Vector4f& Vector4f::operator+=(const __m128& ref) {
	return (*this = _mm_add_ps(vecp, ref));
}
Vector4f& Vector4f::operator-=(const __m128& ref) {
	return (*this = _mm_sub_ps(vecp, ref));
}
Vector4f& Vector4f::operator*=(const float& ref) {
	__m128 other = _mm_set1_ps(ref);
	return (*this = _mm_mul_ps(vecp, other));
}
Vector4f& Vector4f::operator/=(const float& ref) {
	__m128 other = _mm_set1_ps(ref);
	return (*this = _mm_div_ps(vecp, other));
}

bool Vector4f::operator==(const Vector4f& ref) {
	return	((this->x == ref.x) &&
			(this->y == ref.y) &&
			(this->z == ref.z) &&
			(this->z == ref.z));
}
bool Vector4f::operator!=(const Vector4f& ref) {
	return	((this->x != ref.x) ||
			(this->y != ref.y) ||
			(this->z != ref.z) ||
			(this->z != ref.z));
}

void* Vector4f::operator new(const size_t size) {
	return _aligned_malloc(size, 16);
}
void* Vector4f::operator new[](const size_t size) {
	return _aligned_malloc(size, 16);
}

void Vector4f::operator delete(void* other) {
	_aligned_free(other);
}
void Vector4f::operator delete[](void* other) {
	_aligned_free(other);
}

Vector4f::operator Vector4i() {
	return _mm_cvtps_epi32(vecp);
}
