#ifndef ___GAMEOBJECT___
#define ___GAMEOBJECT___

#include "stdafx.h"
#include "Component.h"

using namespace std;

class Scene;
class GameObject {
	friend class Scene;
	friend class Components::Camera;
private:
	list<Component*> m_Components;

	void Update();
	void Remove();

	Vector4i* rotate;

protected:
	bool isOnceGameObject = false;
	virtual void Components() = 0;

public:
	GameObject();
	virtual ~GameObject();

	Scene* scene = nullptr;
	wstring name;

	Vector4f* pos;
	Vector4f* scale;

	void SetRotateX(float x);
	void SetRotateY(float y);
	void SetRotateZ(float z);
	Vector4i SetRotate(float x, float y, float z);

	Vector4f Reset();

	int GetRotateX();
	int GetRotateY();
	int GetRotateZ();
	Vector4i GetRotate();

	template<typename T, enable_if_t<is_base_of_v<Component, T>, bool> = true> T* AddComponent();
	template<typename T, enable_if_t<is_base_of_v<Component, T>, bool> = true> T* GetComponent();
	template<typename T, enable_if_t<is_base_of_v<Component, T>, bool> = true> bool RemoveComponent();
};

template<typename T, enable_if_t<is_base_of_v<Component, T>, bool>> inline T* GameObject::AddComponent() {
	Component* Component = GetComponent<T>();
	if (Component) { return dynamic_cast<T*>(Component); }

	Component = new T;
	Component->gameobject = this;
	Component->scene = this->scene;
	Component->Awake();
	m_Components.push_back(Component);

	return dynamic_cast<T*>(Component);
}
template<typename T, enable_if_t<is_base_of_v<Component, T>, bool>> inline T* GameObject::GetComponent() {
	for (auto& item : m_Components) {
		if (typeid(*item) == typeid(T)) { return dynamic_cast<T*>(item); }
	}

	return nullptr;
}
template<typename T, enable_if_t<is_base_of_v<Component, T>, bool>> inline bool GameObject::RemoveComponent() {
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
