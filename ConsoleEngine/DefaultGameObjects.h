#ifndef ___DEFAULTGAMEOBJECTS___
#define ___DEFAULTGAMEOBJECTS___

#include "stdafx.h"
#include "GameObject.h"
#include "DefaultComponents.h"

namespace DefaultGameObjects {
	class Camera : public GameObject {
	private:
		void Components() override;
	public:
	};
}
#endif // !___DEFAULTGAMEOBJECTS___ 
