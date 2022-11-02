#ifndef ___DEFAULTCOMPONENTS___
#define ___DEFAULTCOMPONENTS___

#include "stdafx.h"
#include "Component.h"
#include "GameObject.h"
#include "Graphic.h"
#include "Color.h"

namespace DefaultComponents {
	class Camera : public Component {
	private:
		void Awake() override;
		void Update() override;
		void Remove() override;

	public:
		void SetCameraScale(COORD Scale);
		void SetCameraSize(COORD Size);
	};
}

#endif // !___DEFAULTCOMPONENTS___

