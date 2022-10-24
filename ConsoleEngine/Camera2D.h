#ifndef ___CAMERA___
#define ___CAMERA___

#include "stdafx.h"
#include "Field2D.h"

class Camera2D {
private:
	Vector2<float> m_Pos;
	Vector3<int> m_ScreenSize;
	Vector2<int> m_HalfScreenSize;

	// WriteConsoleOutput에 쓰는 용도
	COORD m_size;
	SMALL_RECT m_rect;
	CHAR_INFO* m_Screen;

	Field2D* m_Field = nullptr;

	// 생성자에 사용하는 함수
	void Setting();

public:
	Camera2D(Field2D* Field);
	Camera2D(Vector2<int> Screen, Field2D* Field);
	~Camera2D();

	static const WORD DEFAULT_BACKGROUND;
	static const COORD ZERO_POS;
	
	void Render();
	void Clear();

	void SetScreenSize(Vector3<int> Size);
	void SetScreen();
	Vector2<float>* GetPos();
};

inline void Camera2D::Setting() {
	m_ScreenSize.z = m_ScreenSize.x * m_ScreenSize.y;
	m_HalfScreenSize = m_ScreenSize.toVector2<int>() * 0.5f;

	m_rect = { 0, 0, static_cast<short>(m_ScreenSize.x), static_cast<short>(m_ScreenSize.y) };
	m_size = { static_cast<short>(m_ScreenSize.x), static_cast<short>(m_ScreenSize.y) };

	m_Screen = new CHAR_INFO[static_cast<size_t>(m_ScreenSize.z)];

	string System = "mode con: cols=" + to_string(static_cast<int>(m_ScreenSize.x)) + " lines=" + to_string(static_cast<int>(m_ScreenSize.y));
	system(System.c_str());

	for (int i = 0; i < m_ScreenSize.z; i++) { m_Screen[i] = { ' ', DEFAULT_BACKGROUND }; }
}

#endif // !___CAMERA___
