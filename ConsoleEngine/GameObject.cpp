#include "GameObject.h"

GameObject::GameObject() {
	pos = new Vector4f(0.0f);
	scale = new Vector4f(1.0f);
	rotate = new Vector4i(0, 0, 90);
}
GameObject::~GameObject() {
	if (pos) { delete pos; pos = nullptr; }
	if (scale) { delete scale; scale = nullptr; }
	if (rotate) { delete rotate; rotate = nullptr; }
}

void GameObject::Update() {
	for (auto& item : m_Components) { item->Update(); }
}
void GameObject::Remove() {
	for (auto& item : m_Components) {
		item->Remove();
		if (item) { delete item; item = nullptr; }
	}
	m_Components.clear();
}

void GameObject::SetRotateX(float x) {
	while (x > 180)  { x -= 360; }
	while (x < -180) { x += 360; }

	rotate->x = static_cast<int>(round(x)) + 180;
}
void GameObject::SetRotateY(float y) {
	while (y > 180)  { y -= 360; }
	while (y < -180) { y += 360; }

	rotate->y = static_cast<int>(round(y)) + 180;
}
void GameObject::SetRotateZ(float z) {
	while (z > 180)  { z -= 360; }
	while (z < -180) { z += 360; }

	rotate->z = static_cast<int>(round(z)) + 180;
}
Vector4i GameObject::SetRotate(float x, float y, float z) {
	while (x > 180) { x -= 360; }
	while (x < -180) { x += 360; }

	while (y > 180) { y -= 360; }
	while (y < -180) { y += 360; }


	while (z > 180) { z -= 360; }
	while (z < -180) { z += 360; }

	return (*rotate = {
		static_cast<int>(round(x)) + 180,
		static_cast<int>(round(y)) + 180,
		static_cast<int>(round(z)) + 180 });
}

Vector4f GameObject::Reset() {
	*rotate = { 0, 0, 90 };
	return { 180, 180, -90 };
}

int GameObject::GetRotateX() { return rotate->x; }
int GameObject::GetRotateY() { return rotate->y; }
int GameObject::GetRotateZ() { return rotate->z; }
Vector4i GameObject::GetRotate() { return { rotate->x, rotate->y, rotate->z, 0 }; }