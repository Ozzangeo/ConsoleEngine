#ifndef ___COMPONENT___
#define ___COMPONENT___

#include "stdafx.h"
#include "Keyboard.h"
#include "Time.h"
#include "Color.h"
#include "Graphic.h"

class Scene;
class GameObject;
/* [ Component �⺻ ���� ]
* Scene* scene
* GameObject* gameobject
* Keyboard keyboard
* Graphic graphic
* Color color
* Time time
* 
* Awake - Start - Update - Remove
*/
class Component {
	friend class GameObject;
protected:
	Scene* scene = nullptr;
	GameObject* gameobject = nullptr;
	Graphic& graphic = Graphic::GetInstance();
	Keyboard keyboard;
	Color color;
	Time time;

	// ������Ʈ�� �߰��� �� �۵�
	virtual void Awake() {};
	
	// ���� ������Ʈ�� ��� �ε�Ǿ��� �� �۵�
	virtual void Start() {};

	// �� �����Ӹ��� �۵�
	virtual void Update() {};

	// ������Ʈ�� �����Ǿ��� �� �۵�
	virtual void Remove() {};

public:
	GameObject* GetGameObject();
};


#endif // !___COMPONENT___
