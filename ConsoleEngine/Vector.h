#ifndef ___VECTOR___
#define ___VECTOR___

#include "stdafx.h"

class __declspec(align(16)) Vector4 {
public:
	union { float x; float r; };
	union { float y; float g; };
	union { float z; float b; };
	union { float w; float a; };

	Vector4() : x(0), y(0), z(0), w(0) {}
	Vector4(float _x, float _y, float _z, float _w = 0) : x(_x), y(_y), z(_z), w(_w) {}

	Vector4 operator*(const float& ref) {
		return { this->x * ref, this->y * ref, this->z * ref, this->w * ref };
	}
	Vector4 operator/(const float& ref) {
		return { this->x / ref, this->y / ref, this->z / ref, this->w / ref };
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

	inline bool operator==(const Vector4& other) {
		return (this->x == other.x) && (this->y == other.y) && (this->z == other.z) && (this->w == other.w);
	}
	inline bool operator!=(const Vector4& other) {
		return (this->x != other.x) || (this->y != other.y) || (this->z != other.z) || (this->w != other.w);
	}

	inline float size() const {
		return static_cast<float>(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2)));
	}
	inline Vector4 normalization() const {
		const float SIZE = size();
		return { this->x / SIZE, this->y / SIZE, this->z / SIZE , this->w / SIZE };
	}
	inline float inner_product(const Vector4& ref) const {
		return (this->x * ref.x) + (this->y * ref.y) + (this->z * ref.z) + (this->w * ref.w);
	}

	inline Vector4 Set(float x, float y, float z, float w = 0) {
		return *this = { x, y, z, w };
	}
	template<typename T>
	inline T GetX() { return static_cast<T>(this->x); }
	template<typename T>
 	inline T GetY() { return static_cast<T>(this->y); }
	template<typename T>
	inline T GetZ() { return static_cast<T>(this->z); }
	template<typename T>
	inline T GetW() { return static_cast<T>(this->w); }
	inline Vector4 vround() {
		return *this = { round(this->x), round(this->y), round(this->z), round(this->w) };                  
	}

};

#endif // !___VECTOR___




