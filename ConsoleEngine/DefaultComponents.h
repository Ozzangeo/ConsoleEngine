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
		Vector4 m_CameraSize;
		Vector4 m_HalfScreenSize;

		// WriteConsoleOutput에 쓰는 용도
		COORD m_size;
		SMALL_RECT m_rect;
		CHAR_INFO* m_Screen;

		const WORD DEFAULT_BACKGROUND = Color_Black;
		const COORD ZERO_POS = { 0, 0 };

		void Awake() override;
		void Update() override;
		void Remove() override;
		
	public:
		void SetFieldSize(COORD Size, int Depth);
		void SetCameraSize(COORD Size);
		void SetScreen();
	};
}

#endif // !___DEFAULTCOMPONENTS___

