#include "Scene.h"

void Scene::Awake() {
	GameObjects();

	for (auto& GameObject : m_GameObjects) { GameObject->Start(); }
}
void Scene::Update() {
	for (auto& item : m_GameObjects) {
		item->Update();
	}
}
void Scene::Release() {
	for (auto& item : m_GameObjects) {
		item->Remove();
		if (item) { delete item; item = nullptr; }
	}
	m_GameObjects.clear();
}

GameObject* Scene::GetGameObject(wstring name) {
	for (auto& item : m_GameObjects) {
		if (item->name == name) { return item; }
	}
	return nullptr;
}
GameObject* Scene::GetGameObject(int tag) {
	for (auto& item : m_GameObjects) {
		if (item->tag == tag) { return item; }
	}
	return nullptr;
}
GameObject* Scene::GetGameObject(wstring name, int tag) {
	for (auto& item : m_GameObjects) {
		if (item->name == name && item->tag == tag) { return item; }
	}
	return nullptr;
}

list<GameObject*> Scene::GetGameObjectList(wstring name) {
	list<GameObject*> objectList;

	for (auto& item : m_GameObjects) {
		if (item->name == name) { objectList.push_back(item); }
	}

	return objectList;
}
list<GameObject*> Scene::GetGameObjectList(int tag) {
	list<GameObject*> objectList;

	for (auto& item : m_GameObjects) {
		if (item->tag == tag) { objectList.push_back(item); }
	}

	return objectList;
}
list<GameObject*> Scene::GetGameObjectList(wstring name, int tag) {
	list<GameObject*> objectList;

	for (auto& item : m_GameObjects) {
		if (item->name == name && item->tag == tag) { objectList.push_back(item); }
	}

	return objectList;
}