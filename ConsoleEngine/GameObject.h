#ifndef ___GAMEOBJECT___
#define ___GAMEOBJECT___

#include "stdafx.h"
#include "Component.h"

using namespace std;

class Scene;
class GameObject {
	friend class Scene;
private:
	list<Component*> m_Components;

	void Update();
	void Remove();
protected:
	bool isOnceGameObject = false;
	virtual void Components() = 0;

public:
	Scene* scene = nullptr;
	wstring name;
	Vector3<float> pos = { 0, 0, 0 };

	template<typename T, enable_if_t<is_base_of_v<Component, T>, bool> = true>
	T* AddComponent();
	template<typename T, enable_if_t<is_base_of_v<Component, T>, bool> = true>
	T* GetComponent();
	template<typename T, enable_if_t<is_base_of_v<Component, T>, bool> = true>
	bool RemoveComponent();
};

template<typename T, enable_if_t<is_base_of_v<Component, T>, bool>>
inline T* GameObject::AddComponent() {
	Component* Component = GetComponent<T>();
	if (Component) { return dynamic_cast<T*>(Component); }

	Component = new T;
	Component->gameobject = this;
	Component->scene = this->scene;
	Component->Awake();
	m_Components.push_back(Component);

	return dynamic_cast<T*>(Component);
}
template<typename T, enable_if_t<is_base_of_v<Component, T>, bool>>
inline T* GameObject::GetComponent() {
	for (auto& item : m_Components) {
		if (typeid(*item) == typeid(T)) { return dynamic_cast<T*>(item); }
	}

	return nullptr;
}
template<typename T, enable_if_t<is_base_of_v<Component, T>, bool>>
inline bool GameObject::RemoveComponent() {
	T* component = GetComponent<T>();
	if (!component) { return false; }

	Component* RComponent = dynamic_cast<Component*>(component);
	RComponent->Remove();
	m_Components.remove(RComponent);
	delete RComponent;
	RComponent = nullptr;

	return true;
}

#endif // !___GAMEOBJECT___