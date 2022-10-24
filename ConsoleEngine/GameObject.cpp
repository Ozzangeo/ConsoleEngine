#include "GameObject.h"

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
