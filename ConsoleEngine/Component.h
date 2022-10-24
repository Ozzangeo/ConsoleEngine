#ifndef ___COMPONENT___
#define ___COMPONENT___

#include "stdafx.h"
#include "Keyboard.h"
#include "Time.h"
#include "Color.h"

/* [ Component �⺻ ���� ]
* GameObject* gameobject
* Keyboard keyboard
* Color color
* Time time
*/
class Scene;
class GameObject;
class Component {
	friend class GameObject;
protected:
	Scene* scene = nullptr;
	GameObject* gameobject = nullptr;
	Keyboard keyboard;
	Color color;
	Time time;

	virtual void Awake() = 0;
	virtual void Update() = 0;
	virtual void Remove() = 0;

public:
	GameObject* GetGameObject();
};


#endif // !___COMPONENT___
