#ifndef ___VECTOR___
#define ___VECTOR___

#include "stdafx.h"

template<typename T>
class Vector2 {
public:
	union { T x; T r; };
	union { T y; T g; };

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
	inline Vector2<T2> toVector2() {
		return { static_cast<T2>(this->x), static_cast<T2>(this->y) };
	}
	inline Vector2<T> vround() {
		return *this = { static_cast<T>(round(this->x)), static_cast<T>(round(this->y)) };
	}
};

template<typename T>
class Vector3 {
public:
	union { T x; T r; };
	union { T y; T g; };
	union { T z; T b; };

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

	inline float size() const {
		return (float)sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}
	inline Vector3<T> normalization() const {
		const float SIZE = size();
		return { this->x / SIZE, this->y / SIZE, this->z / SIZE };
	}
	inline float inner_product(const Vector3<T>& ref) const {
		return (this->x * ref.x) + (this->y * ref.y) + (this->z * ref.z);
	}

	template<typename T2>
	inline Vector2<T2> toVector2() {
		return { static_cast<T2>(this->x), static_cast<T2>(this->y) };
	}
	template<typename T2>
	inline Vector3<T2> toVector3() {
		return { static_cast<T2>(this->x), static_cast<T2>(this->y), static_cast<T2>(this->z)};
	}
	inline Vector3<T> vround() {
		return *this = { round(this->x), round(this->y), round(this->z) };
	}

};

template<typename T>
class Vector4 {
public:
	union { T x; T r; };
	union { T y; T g; };
	union { T z; T b; };
	union { T w; T a; };

	Vector4() : x(0), y(0), z(0), w(0) {}
	Vector4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}

	Vector4<T> operator*(const float& ref) {
		return { this->x * ref, this->y * ref, this->z * ref, this->w * ref };
	}
	Vector4<T> operator/(const float& ref) {
		return { this->x / ref, this->y / ref, this->z / ref, this->w / ref };
	}
	Vector4<T> operator+(const Vector4<T>& ref) {
		return { this->x + ref.x, this->y + ref.y, this->z + ref.z, this->w + ref.w };
	}
	Vector4<T> operator-(const Vector4<T>& ref) {
		return { this->x - ref.x, this->y - ref.y, this->z - ref.z, this->w - ref.w };
	}

	Vector4<T>& operator*=(const float ref) {
		this->x *= ref;
		this->y *= ref;
		this->z *= ref;
		this->w *= ref;

		return *this;
	}
	Vector4<T>& operator/=(const float& ref) {
		this->x /= ref;
		this->y /= ref;
		this->z /= ref;
		this->w /= ref;

		return *this;
	}
	Vector4<T>& operator+=(const Vector4& ref) {
		this->x += ref.x;
		this->y += ref.y;
		this->z += ref.z;
		this->w += ref.w;

		return *this;
	}
	Vector4<T>& operator-=(const Vector4& ref) {
		this->x -= ref.x;
		this->y -= ref.y;
		this->z -= ref.z;
		this->w -= ref.w;

		return *this;
	}

	bool operator==(const Vector4<T>& other) {
		return (this->x == other.x) && (this->y == other.y) && (this->z == other.z) && (this->w == other.w);
	}
	bool operator!=(const Vector4<T>& other) {
		return (this->x != other.x) || (this->y != other.y) || (this->z != other.z) || (this->w != other.w);
	}

	operator int() {
		return static_cast<int>(round(this->x) + round(this->y) + round(this->z) + round(this->w));
	}

	inline float size() const {
		return static_cast<float>(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2)));
	}
	inline Vector4<T> normalization() const {
		const float SIZE = size();
		return { this->x / SIZE, this->y / SIZE, this->z / SIZE , this->w / SIZE };
	}
	inline float inner_product(const Vector4<T>& ref) const {
		return (this->x * ref.x) + (this->y * ref.y) + (this->z * ref.z) + (this->w * ref.w);
	}

	template<typename T2>
	inline Vector2<T2> toVector2() {
		return { static_cast<T2>(this->x), static_cast<T2>(this->y) };
	}
	template<typename T2>
	inline Vector3<T2> toVector3() {
		return { static_cast<T2>(this->x), static_cast<T2>(this->y), static_cast<T2>(this->z) };
	}
	template<typename T2>
	inline Vector4<T2> toVector4() {
		return { static_cast<T2>(this->x), static_cast<T2>(this->y), static_cast<T2>(this->z), static_cast<T2>(this->w)};
	}
	inline Vector3<T> vround() {
		return *this = { round(this->x), round(this->y), round(this->z), round(this->w) };
	}

};

#endif // !___VECTOR___




