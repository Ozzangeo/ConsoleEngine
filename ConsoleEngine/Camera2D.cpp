#include "Camera2D.h"

Camera2D* Camera2D::m_Instance = nullptr;
const WORD Camera2D::DEFAULT_BACKGROUND = (Color_LightWhite << 4);
const HANDLE Camera2D::HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
const COORD Camera2D::ZERO_POS = { 0, 0 };

Camera2D::Camera2D() : m_Pos({ 0, 0 }), m_ScreenSize({ 100, 50, 5000 }),
	m_rect({ 0, 0, 100, 50 }), m_size({100, 50}),
	m_DefaultScreen(new CHAR_INFO[5000]), m_Screen(new CHAR_INFO[5000]) {

	system("mode con: cols=100 lines=50");

	for (int i = 0; i < m_ScreenSize.z; i++) {
		m_DefaultScreen[i] = { ' ', DEFAULT_BACKGROUND};
		m_Screen[i] = { ' ', DEFAULT_BACKGROUND};
	}
}
Camera2D::~Camera2D() {
	if (m_Screen) { delete[] m_Screen; }
	if (m_DefaultScreen) { delete[] m_DefaultScreen; }
}

Camera2D* Camera2D::GetInstance() {
	if (!m_Instance) { m_Instance = new Camera2D; }
	return m_Instance;
}

void Camera2D::Render() {
	WriteConsoleOutput(HANDLE, m_Screen, m_size, ZERO_POS, &m_rect);
	Clear();
}
void Camera2D::Clear() {
	m_Screen = m_DefaultScreen;
}

void Camera2D::SetScreenSize(Vector3 Size) {
	string System = "mode con: cols=" + to_string(Size.x) + " lines=" + to_string(Size.y);
	system(System.c_str());
	m_ScreenSize = Size;
}
Vector2* Camera2D::GetPos() {
	return &m_Pos;
}

Camera2D Camera2D::operator=(const Camera2D& ref) {
	return ref;
}
