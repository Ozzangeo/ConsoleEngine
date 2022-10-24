#ifndef ___SCENE___
#define ___SCENE___

#include "stdafx.h"
#include "Field2D.h"
#include "GameObject.h"

using namespace std;

class Scene {
	friend class Engine2D;
private:
	list<GameObject*> m_GameObjects;

	void Awake();
	void Update();
	void Release();

protected:
	virtual void GameObjects() = 0;

public:
	template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool> = true>
	T* AddGameObject(wstring name);
	template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool> = true>
	T* GetGameObject(wstring name);
	template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool> = true>
	bool RemoveGameObject(wstring name);
};

template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool>>
inline T* Scene::AddGameObject(wstring name) {
	GameObject* GameObject = GetGameObject<T>(name);
	if (GameObject) { return dynamic_cast<T*>(GameObject); }

	GameObject = new T;
	GameObject->name = name;
	GameObject->scene = this;
	GameObject->Components();
	m_GameObjects.push_back(GameObject);

	return dynamic_cast<T*>(GameObject);
}
template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool>>
inline T* Scene::GetGameObject(wstring name) {
	for (auto& item : m_GameObjects) {
		if (typeid(*item) == typeid(T)) {
			if (item->name == name || item->isOnceGameObject) { return dynamic_cast<T*>(item); }
		}
	}
	return nullptr;
}
template<typename T, enable_if_t<is_base_of_v<GameObject, T>, bool>>
inline bool Scene::RemoveGameObject(wstring name) {
	T* gameobject = GetGameObject<T>(name);
	if (!gameobject) { return false; }

	GameObject* RGameObject = dynamic_cast<GameObject*>(gameobject);
	RGameObject->Remove();
	m_GameObjects.remove(RGameObject);

	delete RGameObject;
	RGameObject = nullptr;

	return true;
}

#endif // !___SCENE___
