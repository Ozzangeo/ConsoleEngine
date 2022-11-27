#ifndef ___COMPONENT___
#define ___COMPONENT___

#include "stdafx.h"
#include "Keyboard.h"
#include "Time.h"
#include "Color.h"
#include "Graphic.h"

class Scene;
class GameObject;
/* [ Component 기본 변수 ]
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

	// 컴포넌트가 추가될 때 작동
	virtual void Awake() {};
	
	// 씬의 오브젝트가 모두 로드되었을 때 작동
	virtual void Start() {};

	// 매 프레임마다 작동
	virtual void Update() {};

	// 컴포넌트가 삭제되었을 때 작동
	virtual void Remove() {};

public:
	GameObject* GetGameObject();
};


#endif // !___COMPONENT___
