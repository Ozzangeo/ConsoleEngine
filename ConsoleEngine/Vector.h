#ifndef ___VECTOR___
#define ___VECTOR___

#include "stdafx.h"

class Vector2 {
public:
	float x;
	float y;

	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(float _x, float _y) : x(_x), y(_y) {}

	static const Vector2 ZERO;
	static const Vector2 ONE;

	Vector2 operator*(const float& ref) {
		return { this->x * ref, this->y * ref };
	}
	Vector2 operator/(const float& ref) {
		return { this->x / ref, this->y / ref };
	}
	Vector2 operator+(const Vector2& ref) {
		return { this->x + ref.x, this->y + ref.y };
	}
	Vector2 operator-(const Vector2& ref) {
		return { this->x - ref.x, this->y - ref.y };
	}

	Vector2& operator*=(const float ref) {
		this->x *= ref;
		this->y *= ref;

		return *this;
	}
	Vector2& operator/=(const float& ref) {
		this->x /= ref;
		this->y /= ref;

		return *this;
	}
	Vector2& operator+=(const Vector2& ref) {
		this->x += ref.x;
		this->y += ref.y;

		return *this;
	}
	Vector2& operator-=(const Vector2& ref) {
		this->x -= ref.x;
		this->y -= ref.y;

		return *this;
	}

	operator int();

	Vector2 vround();
};
class Vector3 {
public:
	float x;
	float y;
	float z;

	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	static const Vector3 ZERO;
	static const Vector3 ONE;

	Vector3 operator*(const float& ref);
	Vector3 operator/(const float& ref);
	Vector3 operator+(const Vector3& ref);
	Vector3 operator-(const Vector3& ref);

	Vector3& operator*=(const float ref);
	Vector3& operator/=(const float& ref);
	Vector3& operator+=(const Vector3& ref);
	Vector3& operator-=(const Vector3& ref);

	bool operator==(const Vector3& other);
	bool operator!=(const Vector3& other);

	operator int();

	float size() const;
	Vector3 normalization() const;
	float inner_product(const Vector3& ref) const;

	Vector2 toVector2();
	Vector3 vround();
};

#endif // !___VECTOR___




