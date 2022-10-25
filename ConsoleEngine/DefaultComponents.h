#ifndef ___DEFAULTCOMPONENTS___
#define ___DEFAULTCOMPONENTS___

#include "stdafx.h"
#include "Component.h"
#include "GameObject.h"
#include "Field2D.h"
#include "Color.h"

namespace DefaultComponents {
	class Camera2D : public Component {
	private:
		Vector3<int> m_ScreenSize;
		Vector2<int> m_HalfScreenSize;

		// WriteConsoleOutput에 쓰는 용도
		COORD m_size;
		SMALL_RECT m_rect;
		CHAR_INFO* m_Screen;

		Field2D m_Field;

		const WORD DEFAULT_BACKGROUND = Color_Black;
		const COORD ZERO_POS = { 0, 0 };

		void Awake() override;
		void Update() override;
		void Remove() override;
		
	public:
		void SetFieldSize(Vector3<int> Size);
		void SetScreenSize(Vector2<int> Size);
		void SetScreen();
	};
}

#endif // !___DEFAULTCOMPONENTS___

