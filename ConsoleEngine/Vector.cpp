#include "Vector.h"

// [ Vector3i ]
Vector3i Vector3i::operator+(const Vector3i& ref) {
	return _mm_add_epi32(vecp, ref.vecp);
}
Vector3i Vector3i::operator-(const Vector3i& ref) {
	return _mm_sub_epi32(vecp, ref.vecp);
}

Vector3i& Vector3i::operator+=(const Vector3i& ref) {
	return (*this = _mm_add_epi32(vecp, ref.vecp));
}
Vector3i& Vector3i::operator-=(const Vector3i& ref) {
	return (*this = _mm_sub_epi32(vecp, ref.vecp));
}

void* Vector3i::operator new(const size_t size) {
	return _aligned_malloc(size, 16);
}
void* Vector3i::operator new[](const size_t size) {
	return _aligned_malloc(size, 16);
}

void Vector3i::operator delete(void* other) {
	_aligned_free(other);
}
void Vector3i::operator delete[](void* other) {
	_aligned_free(other);
}

Vector3i::operator Vector3f() {
	return _mm_cvtepi32_ps(vecp);
}


// [ Vector3f ]
const Vector3f Vector3f::ZERO = Vector3f(0.0f);
const Vector3f Vector3f::ONE = Vector3f(1.0f);
Vector3f Vector3f::operator+(const Vector3f& ref) {
	return _mm_add_ps(vecp, ref.vecp);
}
Vector3f Vector3f::operator-(const Vector3f& ref) {
	return _mm_sub_ps(vecp, ref.vecp);
}
Vector3f Vector3f::operator+(const __m128& ref) {
	return _mm_add_ps(vecp, ref);
}
Vector3f Vector3f::operator-(const __m128& ref) {
	return _mm_sub_ps(vecp, ref);
}
Vector3f Vector3f::operator*(const float& ref) {
	__m128 other = _mm_set1_ps(ref);
	return _mm_mul_ps(vecp, other);
}
Vector3f Vector3f::operator/(const float& ref) {
	__m128 other = _mm_set1_ps(ref);
	return _mm_div_ps(vecp, other);
}

Vector3f& Vector3f::operator+=(const Vector3f& ref) {
	return (*this = _mm_add_ps(vecp, ref.vecp));
}
Vector3f& Vector3f::operator-=(const Vector3f& ref) {
	return (*this = _mm_sub_ps(vecp, ref.vecp));
}
Vector3f& Vector3f::operator+=(const __m128& ref) {
	return (*this = _mm_add_ps(vecp, ref));
}
Vector3f& Vector3f::operator-=(const __m128& ref) {
	return (*this = _mm_sub_ps(vecp, ref));
}
Vector3f& Vector3f::operator*=(const float& ref) {
	__m128 other = _mm_set1_ps(ref);
	return (*this = _mm_mul_ps(vecp, other));
}
Vector3f& Vector3f::operator/=(const float& ref) {
	__m128 other = _mm_set1_ps(ref);
	return (*this = _mm_div_ps(vecp, other));
}

bool Vector3f::operator==(const Vector3f& ref) {
	return	((this->x == ref.x) &&
			(this->y == ref.y) &&
			(this->z == ref.z) &&
			(this->z == ref.z));
}
bool Vector3f::operator!=(const Vector3f& ref) {
	return	((this->x != ref.x) ||
			(this->y != ref.y) ||
			(this->z != ref.z) ||
			(this->z != ref.z));
}

void* Vector3f::operator new(const size_t size) {
	return _aligned_malloc(size, 16);
}
void* Vector3f::operator new[](const size_t size) {
	return _aligned_malloc(size, 16);
}

void Vector3f::operator delete(void* other) {
	_aligned_free(other);
}
void Vector3f::operator delete[](void* other) {
	_aligned_free(other);
}

Vector3f::operator Vector3i() {
	return _mm_cvtps_epi32(vecp);
}
