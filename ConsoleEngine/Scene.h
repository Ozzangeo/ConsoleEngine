#ifndef ___SCENE___
#define ___SCENE___

#include "stdafx.h"
#include "GameObject.h"

using namespace std;

class Scene {
	friend class ConsoleEngine;
private:
	list<GameObject*> m_GameObjects;

	void Awake();
	void Update();
	void Release();

protected:
	// 여기서 가끔씩 빨간줄(에러) 뜨는데 이거 정상입니다
	ConsoleEngine* Engine = nullptr;
	virtual void GameObjects() = 0;

public:
	template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool> = true> T*	 AddGameObject(wstring name, int tag = INT_MIN);

	GameObject* GetGameObject(wstring name);
	GameObject* GetGameObject(int tag);
	GameObject* GetGameObject(wstring name, int tag);
	template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool> = true>	T*	 GetGameObject();
	template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool> = true>	T*	 GetGameObject(wstring name);
	template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool> = true>	T*	 GetGameObject(int tag);
	template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool> = true>	T*	 GetGameObject(wstring name, int tag);

	list<GameObject*> GetGameObjectList(wstring name);
	list<GameObject*> GetGameObjectList(int tag);
	list<GameObject*> GetGameObjectList(wstring name, int tag);
	template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool> = true>	list<GameObject*> GetGameObjectList();
	template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool> = true>	list<GameObject*> GetGameObjectList(wstring name);
	template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool> = true>	list<GameObject*> GetGameObjectList(int tag);
	template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool> = true>	list<GameObject*> GetGameObjectList(wstring name, int tag);

	template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool> = true> bool RemoveGameObject();
	template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool> = true> bool RemoveGameObject(wstring name);
	template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool> = true> bool RemoveGameObject(int tag);
	template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool> = true> bool RemoveGameObject(wstring name, int tag);
};

template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool>> inline T* Scene::AddGameObject(wstring name, int tag) {
	GameObject* GameObject = GetGameObject<T>();
	if (GameObject && GameObject->isOnceGameObject) { return dynamic_cast<T*>(GameObject); }

	GameObject = new T;
	GameObject->name = name;
	GameObject->tag = tag;
	GameObject->scene = this;
	GameObject->Components();
	m_GameObjects.push_back(GameObject);

	return dynamic_cast<T*>(GameObject);
}

template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool>> inline T* Scene::GetGameObject() {
	for (auto& item : m_GameObjects) {
		if (typeid(*item) == typeid(T)) { return dynamic_cast<T*>(item); }
	}
	return nullptr;
}
template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool>> inline T* Scene::GetGameObject(wstring name) {
	for (auto& item : m_GameObjects) {
		if (typeid(*item) == typeid(T)) {
			if (item->name == name) { return dynamic_cast<T*>(item); }
		}
	}
	return nullptr;
}
template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool>> inline T* Scene::GetGameObject(int tag) {
	for (auto& item : m_GameObjects) {
		if (typeid(*item) == typeid(T)) {
			if (item->tag == tag) { return dynamic_cast<T*>(item); }
		}
	}
	return nullptr;
}
template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool>> inline T* Scene::GetGameObject(wstring name, int tag) {
	for (auto& item : m_GameObjects) {
		if (typeid(*item) == typeid(T)) {
			if (item->name == name && item->tag == tag) { return dynamic_cast<T*>(item); }
		}
	}
	return nullptr;
}

template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool>> inline list<GameObject*> Scene::GetGameObjectList() {
	list<GameObject*> objectList;

	for (auto& item : m_GameObjects) {
		if (typeid(*item) == typeid(T)) { objectList.push_back(item); }
	}

	return objectList;
}
template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool>> inline list<GameObject*> Scene::GetGameObjectList(wstring name) {
	list<GameObject*> objectList;

	for (auto& item : m_GameObjects) {
		if (typeid(*item) == typeid(T)) {
			if (item->name == name) { objectList.push_back(item); }
		}
	}

	return objectList;
}
template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool>> inline list<GameObject*> Scene::GetGameObjectList(int tag) {
	list<GameObject*> objectList;

	for (auto& item : m_GameObjects) {
		if (typeid(*item) == typeid(T)) {
			if (item->tag == tag) { objectList.push_back(item); }
		}
	}

	return objectList;
}
template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool>> inline list<GameObject*> Scene::GetGameObjectList(wstring name, int tag) {
	list<GameObject*> objectList;

	for (auto& item : m_GameObjects) {
		if (typeid(*item) == typeid(T)) {
			if (item->name == name && item->tag == tag) { objectList.push_back(item); }
		}
	}

	return objectList;
}

template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool>> inline bool Scene::RemoveGameObject() {
	list<T*> gameobjects = GetGameObject<T>();

	for (auto& RObject : gameobjects) {
		GameObject* RGameObject = dynamic_cast<GameObject*>(RObject);
		RGameObject->Remove();
		m_GameObjects.remove(RGameObject);

		delete RGameObject;
		RGameObject = nullptr;
	}

	return true;
}
template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool>> inline bool Scene::RemoveGameObject(wstring name) {
	list<T*> gameobjects = GetGameObject<T>(name);

	for (auto& RObject : gameobjects) {
		GameObject* RGameObject = dynamic_cast<GameObject*>(RObject);
		RGameObject->Remove();
		m_GameObjects.remove(RGameObject);

		delete RGameObject;
		RGameObject = nullptr;
	}

	return true;
}
template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool>> inline bool Scene::RemoveGameObject(int tag) {
	list<T*> gameobjects = GetGameObject<T>(tag);

	for (auto& RObject : gameobjects) {
		GameObject* RGameObject = dynamic_cast<GameObject*>(RObject);
		RGameObject->Remove();
		m_GameObjects.remove(RGameObject);

		delete RGameObject;
		RGameObject = nullptr;
	}

	return true;
}
template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool>> inline bool Scene::RemoveGameObject(wstring name, int tag) {
	list<T*> gameobjects = GetGameObject<T>(name, tag);

	for (auto& RObject : gameobjects) {
		GameObject* RGameObject = dynamic_cast<GameObject*>(RObject);
		RGameObject->Remove();
		m_GameObjects.remove(RGameObject);

		delete RGameObject;
		RGameObject = nullptr;
	}

	return true;
}

#endif // !___SCENE___
