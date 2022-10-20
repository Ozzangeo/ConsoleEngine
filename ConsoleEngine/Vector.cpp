#include "Vector.h"

// Vector2
const Vector2 Vector2::ZERO = { 0, 0 };
const Vector2 Vector2::ONE = { 1, 1 };

Vector2::operator int() {
	return (int)(round(this->x) + round(this->y));
}
Vector2 Vector2::vround() {
	return *this = { round(this->x), round(this->y) };
}

// Vector3
const Vector3 Vector3::ZERO = { 0, 0, 0 };
const Vector3 Vector3::ONE = { 1, 1, 1 };

Vector3 Vector3::operator*(const float& ref) {
	return { this->x * ref, this->y * ref, this->z * ref };
}
Vector3 Vector3::operator/(const float& ref) {
	return { this->x / ref, this->y / ref, this->z / ref };
}
Vector3 Vector3::operator+(const Vector3& ref) {
	return { this->x + ref.x, this->y + ref.y, this->z + ref.z };
}
Vector3 Vector3::operator-(const Vector3& ref) {
	return { this->x - ref.x, this->y - ref.y, this->z - ref.z };
}

Vector3& Vector3::operator*=(const float ref) {
	this->x *= ref;
	this->y *= ref;
	this->z *= ref;

	return *this;
}
Vector3& Vector3::operator/=(const float& ref) {
	this->x /= ref;
	this->y /= ref;
	this->z /= ref;

	return *this;
}
Vector3& Vector3::operator+=(const Vector3& ref) {
	this->x += ref.x;
	this->y += ref.y;
	this->z += ref.z;

	return *this;
}
Vector3& Vector3::operator-=(const Vector3& ref) {
	this->x -= ref.x;
	this->y -= ref.y;
	this->z -= ref.z;

	return *this;
}

bool Vector3::operator==(const Vector3& other) {
	return (this->x == other.x) && (this->y == other.y) && (this->z == other.z);
}
bool Vector3::operator!=(const Vector3& other) {
	return (this->x != other.x) || (this->y != other.y) || (this->z != other.z);
}

Vector3::operator int() {
	return (int)(round(this->x) + round(this->y) + round(this->z));
}
float Vector3::size() const {
	return (float)sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}
Vector3 Vector3::normalization() const {
	const float SIZE = size();
	return { this->x / SIZE, this->y / SIZE, this->z / SIZE };
}
float Vector3::inner_product(const Vector3& ref) const {
	return (this->x * ref.x) + (this->y * ref.y) + (this->z * ref.z);
}

Vector2 Vector3::toVector2() {
	return { this->x, this->y };
}

Vector3 Vector3::vround() {
	return *this = { round(this->x), round(this->y), round(this->z) };
}

