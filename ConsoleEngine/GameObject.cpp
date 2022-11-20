#include "GameObject.h"

GameObject::GameObject() {
	name = L"";
	tag = INT_MIN;

	pos = new Vector3f(0.0f);
	scale = new Vector3f(1.0f);
	rotate = new Vector3i(0, 0, 90);
}
GameObject::~GameObject() {
	if (pos) { delete pos; pos = nullptr; }
	if (scale) { delete scale; scale = nullptr; }
	if (rotate) { delete rotate; rotate = nullptr; }
}

void GameObject::Start() {
	for (auto& Component : m_Components) { Component->Start(); }
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
