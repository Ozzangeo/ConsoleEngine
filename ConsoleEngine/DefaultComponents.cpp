#include "DefaultComponents.h"

using namespace DefaultComponents;

void Camera2D::Awake() {
	SetScreenSize({ 128, 72 });
}
void Camera2D::Update() {
	/////////////////// Render ////////////////
	m_Field.Render(m_Screen, gameobject->pos.toVector2<float>(), m_ScreenSize.toVector2<int>());
	WriteConsoleOutput(Handle::OUTPUT, m_Screen, m_size, ZERO_POS, &m_rect);
	///////////////////////////////////////////

	/////////////////// Clear /////////////////
	for (int i = 0; i < m_ScreenSize.z; i++) {
		m_Screen[i].Attributes = DEFAULT_BACKGROUND;
	}
	m_Field.Clear();
	///////////////////////////////////////////
}
void Camera2D::Remove() {
	if (m_Screen) { delete[] m_Screen; m_Screen = nullptr; }
}

void Camera2D::SetFieldSize(Vector3<int> Size) {
	m_Field.ReSize(Size);
}
void Camera2D::SetScreenSize(Vector2<int> Size) {
	m_ScreenSize = { Size.x, Size.y, Size.x * Size.y };
	m_HalfScreenSize = m_ScreenSize.toVector2<int>() * 0.5f;
	
	m_rect = { 0, 0, static_cast<short>(m_ScreenSize.x), static_cast<short>(m_ScreenSize.y) };
	m_size = { static_cast<short>(m_ScreenSize.x), static_cast<short>(m_ScreenSize.y) };

	if (m_Screen) { delete[] m_Screen; m_Screen = nullptr; }
	m_Screen = new CHAR_INFO[static_cast<size_t>(m_ScreenSize.z)];

	SetScreen();

	for (int i = 0; i < m_ScreenSize.z; i++) { m_Screen[i] = { ' ', DEFAULT_BACKGROUND }; }
}
void Camera2D::SetScreen() {
	string System = "mode con: cols=" + to_string(m_ScreenSize.x) + " lines=" + to_string(m_ScreenSize.y);
	system(System.c_str());
}