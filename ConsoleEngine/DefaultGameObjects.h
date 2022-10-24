#ifndef ___DEFAULTGAMEOBJECTS___
#define ___DEFAULTGAMEOBJECTS___

#include "stdafx.h"
#include "GameObject.h"
#include "DefaultComponents.h"
#include "Field2D.h"

namespace DefaultGameObjects {
	class Camera2D : public GameObject {
	private:
		void Components() override;
	public:
	};
}
#endif // !___DEFAULTGAMEOBJECTS___ 
