#ifndef ___GAMEOBJECTS___
#define ___GAMEOBJECTS___

#include "stdafx.h"
#include "GameObject.h"
#include "Components.h"

namespace GameObjects {
	class Camera : public GameObject {
	private:
		void Components() final override;
	public:
	};
	class Rectangle : public GameObject {
	private:
		void Components() final override;
	};
	class Circle : public GameObject {
	private:
		void Components() final override;
	};
}
#endif // !___GAMEOBJECTS___ 
