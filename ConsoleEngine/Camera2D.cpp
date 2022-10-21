#include "Camera2D.h"

Camera2D* Camera2D::m_Instance = nullptr;
const WORD Camera2D::DEFAULT_BACKGROUND = Color_LightWhite;
const HANDLE Camera2D::HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
const COORD Camera2D::ZERO_POS = { 0, 0 };

Camera2D::Camera2D() : m_Pos(0, 0), m_ScreenSize(128, 64, 8192), m_HalfScreenSize(64, 32),
	m_rect({ 0, 0, 128, 64 }), m_size({ 128, 64 }), m_Screen(new CHAR_INFO[8192]) {

	string System = "mode con: cols=" + to_string(static_cast<int>(m_ScreenSize.x)) + " lines=" + to_string(static_cast<int>(m_ScreenSize.y));
	system(System.c_str());

	for (int i = 0; i < m_ScreenSize.z; i++) { m_Screen[i] = { ' ', DEFAULT_BACKGROUND }; }
}
Camera2D::~Camera2D() {
	if (m_Screen) { delete[] m_Screen; }
}

Camera2D* Camera2D::GetInstance() {
	if (!m_Instance) { m_Instance = new Camera2D; }
	return m_Instance;
}

void Camera2D::Render() {
	m_Field.Render(m_Screen, m_Pos, m_ScreenSize);
	WriteConsoleOutput(HANDLE, m_Screen, m_size, ZERO_POS, &m_rect);
	Clear();
}
void Camera2D::Clear() {
	for (int i = 0; i < m_ScreenSize.z; i++) {
		m_Screen[i].Attributes = DEFAULT_BACKGROUND;
	}
	m_Field.Clear();
}

void Camera2D::SetScreenSize(Vector3 Size) {
	string System = "mode con: cols=" + to_string(static_cast<int>(Size.x)) + " lines=" + to_string(static_cast<int>(Size.y));
	system(System.c_str());
	m_ScreenSize = Size;
}
Vector2* Camera2D::GetPos() {
	return &m_Pos;
}

Camera2D Camera2D::operator=(const Camera2D& ref) {
	return ref;
}
