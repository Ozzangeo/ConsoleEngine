#ifndef ___VECTOR___
#define ___VECTOR___

#define SIMD

#include "stdafx.h"

class Vector4 {
public:
	union {
		struct { float vecp[4]; };
		struct {
			float x, y, z, w;
		};
	};

	Vector4() : x(0), y(0), z(0), w(0) {}
	Vector4(float _x, float _y, float _z, float _w = 0) : x(_x), y(_y), z(_z), w(_w) {}
	Vector4(const __m128& vec) : x(vec.m128_f32[0]), y(vec.m128_f32[1]), z(vec.m128_f32[2]), w(vec.m128_f32[3]) {}
#if defined(SIMD) 
	Vector4 operator*(const float& ref) {
		__m128 my = _mm_load_ps(vecp);
		__m128 oth = _mm_set_ps1(ref);
		__m128 res = _mm_mul_ps(my, oth);	// 왜 안되지

		return res;
}
	Vector4 operator/(const float& ref) {
		__m128 my = _mm_load_ps(vecp);
		__m128 oth = _mm_set_ps1(ref);
		__m128 res = _mm_div_ps(my, oth);

		return res;
	}
	Vector4 operator+(const Vector4& ref) {
		__m128 my = _mm_load_ps(vecp);
		__m128 oth = _mm_load_ps(ref.vecp);
		__m128 res = _mm_add_ps(my, oth);

		return res;
	}
	Vector4 operator-(const Vector4& ref) {
		__m128 my = _mm_load_ps(vecp);
		__m128 oth = _mm_load_ps(ref.vecp);
		__m128 res = _mm_sub_ps(my, oth);

		return res;
	}

	Vector4& operator*=(const float ref) {
		__m128 my = _mm_load_ps(vecp);
		__m128 oth = _mm_set_ps1(ref);
		__m128 res = _mm_mul_ps(my, oth);
		
		*this = res;
		return *this;
	}
	Vector4& operator/=(const float& ref) {
		__m128 my = _mm_load_ps(vecp);
		__m128 oth = _mm_set_ps1(ref);
		__m128 res = _mm_div_ps(my, oth);

		*this = res;
		return *this;
	}
	Vector4& operator+=(const Vector4& ref) {
		__m128 my = _mm_load_ps(vecp);
		__m128 oth = _mm_load_ps(ref.vecp);
		__m128 res = _mm_add_ps(my, oth);

		*this = res;
		return *this;
	}
	Vector4& operator-=(const Vector4& ref) {
		__m128 my = _mm_load_ps(vecp);
		__m128 oth = _mm_load_ps(ref.vecp);
		__m128 res = _mm_sub_ps(my, oth);

		*this = res;
		return *this;
	}

	inline float size() const {
		__m128 my = _mm_load_ps(vecp);
		__m128 oth = _mm_set_ps1(2.0f);
		__m128 res = _mm_sqrt_ps(_mm_pow_ps(my, oth));

		return (res.m128_f32[0] + res.m128_f32[1] + res.m128_f32[2] + res.m128_f32[3]);
	}
	inline Vector4 normalization() const {
		const float SIZE = size();
		__m128 my = { _mm_load_ps(vecp) };
		__m128 oth = { _mm_set_ps1(SIZE) };
		__m128 res = { _mm_div_ps(my, oth) };

		return res;
	}
	inline float inner_product(const Vector4& ref) const {
		__m128 my = _mm_load_ps(vecp);
		__m128 oth = _mm_load_ps(ref.vecp);
		__m128 res = _mm_mul_ps(my, oth);

		return (res.m128_f32[0] + res.m128_f32[1] + res.m128_f32[2] + res.m128_f32[3]);
	}
	inline Vector4 vround() {
		__m128 my = _mm_load_ps(vecp);
		*this = _mm_round_ps(my, 1);
		return *this;
	}
#else
	Vector4 operator*(const float& ref) {
		return { this->x * ref, this->y * ref, this->z * ref, this->w * ref };
	}
	Vector4 operator/(const float& ref) {
		return { this->x / ref, this->y / ref, this->z / ref, this->z / ref };
	}
	Vector4 operator+(const Vector4& ref) {
		return { this->x + ref.x, this->y + ref.y, this->z + ref.z, this->w + ref.w };
	}
	Vector4 operator-(const Vector4& ref) {
		return { this->x - ref.x, this->y - ref.y, this->z - ref.z, this->w - ref.w };
	}

	Vector4& operator*=(const float ref) {
		this->x *= ref;
		this->y *= ref;
		this->z *= ref;
		this->w *= ref;

		return *this;
	}
	Vector4& operator/=(const float& ref) {
		this->x /= ref;
		this->y /= ref;
		this->z /= ref;
		this->w /= ref;

		return *this;
	}
	Vector4& operator+=(const Vector4& ref) {
		this->x += ref.x;
		this->y += ref.y;
		this->z += ref.z;
		this->w += ref.w;

		return *this;
	}
	Vector4& operator-=(const Vector4& ref) {
		this->x -= ref.x;
		this->y -= ref.y;
		this->z -= ref.z;
		this->w -= ref.w;

		return *this;
	}

	inline float size() const {
		return static_cast<float>(sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) + pow(this->w, 2)));
	}
	inline Vector4 normalization() const {
		const float SIZE = size();

		return { this->x / SIZE, this->y / SIZE, this->z / SIZE, this->w / SIZE };
	}
	inline float inner_product(const Vector4& ref) const {
		return (this->x * ref.x) + (this->y * ref.y) + (this->z * ref.z) + (this->w * ref.w);
	}
	inline Vector4 vround() {
		return (*this = { round(this->x), round(this->y), round(this->z), round(this->w) });
	}
#endif

	inline bool operator==(const Vector4& other) {
		return (this->x == other.x) && (this->y == other.y) && (this->z == other.z) && (this->w == other.w);
	}
	inline bool operator!=(const Vector4& other) {
		return (this->x != other.x) || (this->y != other.y) || (this->z != other.z) || (this->w != other.w);
	}

	inline Vector4 Set(float x, float y, float z, float w = 0) {
		return *this = { x, y, z, w };
	}
	template<typename T> inline T GetX() { return static_cast<T>(this->x); }
	template<typename T> inline T GetY() { return static_cast<T>(this->y); }
	template<typename T> inline T GetZ() { return static_cast<T>(this->z); }
	template<typename T> inline T GetW() { return static_cast<T>(this->w); }

	inline void Change(Vector4* other) {
		Vector4 Temp = *other;
		*other = *this;
		*this = Temp;
	}
};

#endif // !___VECTOR___




