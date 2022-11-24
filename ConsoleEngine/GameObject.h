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
	list<Component*> m_RemoveConponentList;

	void Start();
	void Update();
	void Remove();

	Vector3i* rotate;

protected:
	bool isOnceGameObject = false;
	virtual void Components() = 0;
	virtual void Work() {};

public:
	bool isStart = false;

	GameObject();
	virtual ~GameObject();

	Scene* scene = nullptr;
	wstring name;
	int tag;

	Vector3f* pos;
	Vector3f* scale;

	inline void SetRotateX(float x);
	inline void SetRotateY(float y);
	inline void SetRotateZ(float z);
	inline Vector3i SetRotate(float x, float y, float z);

	inline Vector3f Reset();

	inline int GetRotateX();
	inline int GetRotateY();
	inline int GetRotateZ();
	inline Vector3i GetRotate();

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
	if (isStart) { Component->Start(); }
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

	m_RemoveConponentList.push_back(dynamic_cast<Component*>(component));

	return true;
}

inline void GameObject::SetRotateX(float x) {
	while (x > 180) { x -= 360; }
	while (x < -180) { x += 360; }

	rotate->x = static_cast<int>(round(x)) + 180;
}
inline void GameObject::SetRotateY(float y) {
	while (y > 180) { y -= 360; }
	while (y < -180) { y += 360; }

	rotate->y = static_cast<int>(round(y)) + 180;
}
inline void GameObject::SetRotateZ(float z) {
	while (z > 180) { z -= 360; }
	while (z < -180) { z += 360; }

	rotate->z = static_cast<int>(round(z)) + 180;
}
inline Vector3i GameObject::SetRotate(float x, float y, float z) {
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

inline Vector3f GameObject::Reset() {
	*rotate = { 0, 0, 90 };
	return { 180, 180, -90 };
}

inline int GameObject::GetRotateX() { return rotate->x; }
inline int GameObject::GetRotateY() { return rotate->y; }
inline int GameObject::GetRotateZ() { return rotate->z; }
inline Vector3i GameObject::GetRotate() { return { rotate->x, rotate->y, rotate->z, 0 }; }

#endif // !___GAMEOBJECT___
