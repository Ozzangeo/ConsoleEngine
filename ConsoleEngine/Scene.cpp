#include "Scene.h"

void Scene::Awake() {
	Color color;
	color.ResetColor();

	// 먼저 오브젝트들을 추가한 다음
	GameObjects();

	// 오브젝트들의 컴포넌트를 설정해준다.
	for (auto& GameObject : m_GameObjects) {
		GameObject->Start();
		GameObject->isStart = true;
	}
	
	// 모든 오브젝트들의 기본 컴포넌트의 설정을 해준다.
	for (auto& GameObject : m_GameObjects) { GameObject->Work(); }

	// GameObjects에서 추가된 기본 오브젝트들의 설정을 해준다.
	Work();

	isStart = true;
}
void Scene::Update() {
	for (auto& item : m_GameObjects) {
		item->Update();
	}

	for (auto& Remove : m_RemoveObjectList) {
		Remove->Remove();
		m_GameObjects.remove(Remove);

		delete Remove;
		Remove = nullptr;
	}
	m_RemoveObjectList.clear();

	if (isEnd) {
		system("cls");
		
		isDone = true;
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