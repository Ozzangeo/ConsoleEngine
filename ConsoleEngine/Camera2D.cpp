#include "Camera2D.h"

const WORD Camera2D::DEFAULT_BACKGROUND = Color_Black;
const COORD Camera2D::ZERO_POS = { 0, 0 };

Camera2D::Camera2D(Field2D* Field) : m_Field(Field), m_Pos(0, 0), m_ScreenSize(128, 72, 0) { Setting(); }
Camera2D::Camera2D(Vector2<int> Screen, Field2D* Field) : m_Field(Field), m_Pos(0, 0), m_ScreenSize(Screen.x, Screen.y, 0) { Setting(); }
Camera2D::~Camera2D() {
	if (m_Screen) { delete[] m_Screen; m_Screen = nullptr; }
}
void Camera2D::Render() {
	m_Field->Render(m_Screen, m_Pos, m_ScreenSize.toVector2<int>());
	WriteConsoleOutput(Handle::OUTPUT, m_Screen, m_size, ZERO_POS, &m_rect);
	Clear();
}
void Camera2D::Clear() {
	for (int i = 0; i < m_ScreenSize.z; i++) {
		m_Screen[i].Attributes = DEFAULT_BACKGROUND;
	}
	m_Field->Clear();
}

void Camera2D::SetScreenSize(Vector3<int> Size) {
	string System = "mode con: cols=" + to_string(Size.x) + " lines=" + to_string(Size.y);
	system(System.c_str());
	m_ScreenSize = Size;
}
void Camera2D::SetScreen() {
	string System = "mode con: cols=" + to_string(m_ScreenSize.x) + " lines=" + to_string(m_ScreenSize.y);
	system(System.c_str());
}
Vector2<float>* Camera2D::GetPos() {
	return &m_Pos;
}