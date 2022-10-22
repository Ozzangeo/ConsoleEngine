#ifndef ___VECTOR___
#define ___VECTOR___

#include "stdafx.h"

template<typename T>
class Vector2 {
public:
	T x;
	T y;

	Vector2() : x(0), y(0) {}
	Vector2(T _x, T _y) : x(_x), y(_y) {}

	Vector2<T> operator*(const float& ref) {
		return { static_cast<T>(this->x * ref), static_cast<T>(this->y * ref) };
	}
	Vector2<T> operator/(const float& ref) {
		return { this->x / ref, this->y / ref };
	}
	Vector2<T> operator+(const Vector2& ref) {
		return { this->x + ref.x, this->y + ref.y };
	}
	Vector2<T> operator-(const Vector2& ref) {
		return { this->x - ref.x, this->y - ref.y };
	}

	Vector2<T>& operator*=(const float ref) {
		this->x *= ref;
		this->y *= ref;

		return *this;
	}
	Vector2<T>& operator/=(const float& ref) {
		this->x /= ref;
		this->y /= ref;

		return *this;
	}
	Vector2<T>& operator+=(const Vector2& ref) {
		this->x += ref.x;
		this->y += ref.y;

		return *this;
	}
	Vector2<T>& operator-=(const Vector2& ref) {
		this->x -= ref.x;
		this->y -= ref.y;

		return *this;
	}

	operator int() {
		return (int)(round(this->x) + round(this->y));
	}

	template<typename T2>
	Vector2<T2> toVector2() {
		return { static_cast<T2>(this->x), static_cast<T2>(this->y) };
	}

	Vector2<T> vround() {
		return *this = { static_cast<T>(round(this->x)), static_cast<T>(round(this->y)) };
	}
};

template<typename T>
class Vector3 {
public:
	T x;
	T y;
	T z;

	Vector3() : x(0), y(0), z(0) {}
	Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

	Vector3<T> operator*(const float& ref) {
		return { this->x * ref, this->y * ref, this->z * ref };
	}
	Vector3<T> operator/(const float& ref) {
		return { this->x / ref, this->y / ref, this->z / ref };
	}
	Vector3<T> operator+(const Vector3<T>& ref) {
		return { this->x + ref.x, this->y + ref.y, this->z + ref.z };
	}
	Vector3<T> operator-(const Vector3<T>& ref) {
		return { this->x - ref.x, this->y - ref.y, this->z - ref.z };
	}

	Vector3<T>& operator*=(const float ref) {
		this->x *= ref;
		this->y *= ref;
		this->z *= ref;

		return *this;
	}
	Vector3<T>& operator/=(const float& ref) {
		this->x /= ref;
		this->y /= ref;
		this->z /= ref;

		return *this;
	}
	Vector3<T>& operator+=(const Vector3& ref) {
		this->x += ref.x;
		this->y += ref.y;
		this->z += ref.z;

		return *this;
	}
	Vector3<T>& operator-=(const Vector3& ref) {
		this->x -= ref.x;
		this->y -= ref.y;
		this->z -= ref.z;

		return *this;
	}

	bool operator==(const Vector3<T>& other) {
		return (this->x == other.x) && (this->y == other.y) && (this->z == other.z);
	}
	bool operator!=(const Vector3<T>& other) {
		return (this->x != other.x) || (this->y != other.y) || (this->z != other.z);
	}

	operator int() {
		return (int)(round(this->x) + round(this->y) + round(this->z));
	}

	float size() const {
		return (float)sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}
	Vector3<T> normalization() const {
		const float SIZE = size();
		return { this->x / SIZE, this->y / SIZE, this->z / SIZE };
	}
	float inner_product(const Vector3<T>& ref) const {
		return (this->x * ref.x) + (this->y * ref.y) + (this->z * ref.z);
	}

	template<typename T2>
	Vector2<T2> toVector2() {
		return { static_cast<T2>(this->x), static_cast<T2>(this->y) };
	}
	template<typename T2>
	Vector3<T2> toVector3() {
		return { static_cast<T2>(this->x), static_cast<T2>(this->y), static_cast<T2>(this->z)};
	}

	Vector3<T> vround() {
		return *this = { round(this->x), round(this->y), round(this->z) };
	}

};

#endif // !___VECTOR___




