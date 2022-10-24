#include "Scene.h"

void Scene::Awake() {

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

