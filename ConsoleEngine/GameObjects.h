#ifndef ___GAMEOBJECTS___
#define ___GAMEOBJECTS___

#include "stdafx.h"
#include "GameObject.h"
#include "Components.h"

namespace GameObjects {
	class Camera : public GameObject {
	private:
		void Components() override;
	public:
	};
}
#endif // !___GAMEOBJECTS___ 
