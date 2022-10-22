#include "Camera2D.h"

Camera2D* Camera2D::m_Instance = nullptr;
const WORD Camera2D::DEFAULT_BACKGROUND = Color_LightWhite;
const HANDLE Camera2D::INPUT_HANDLE = GetStdHandle(STD_INPUT_HANDLE);
const HANDLE Camera2D::OUTPUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
const COORD Camera2D::ZERO_POS = { 0, 0 };

Camera2D::Camera2D() : m_Pos(0, 0), m_ScreenSize(512, 288, 0) {
	m_ScreenSize.z = m_ScreenSize.x * m_ScreenSize.y;
	m_HalfScreenSize = m_ScreenSize.toVector2<int>() * 0.5f;

	m_rect = { 0, 0, static_cast<short>(m_ScreenSize.x), static_cast<short>(m_ScreenSize.y) };
	m_size = { static_cast<short>(m_ScreenSize.x), static_cast<short>(m_ScreenSize.y) };

	m_Screen = new CHAR_INFO[static_cast<size_t>(m_ScreenSize.z)];

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
void Camera2D::Release() {
	if (m_Instance) { delete m_Instance; }
}
void Camera2D::Render() {
	m_Field.Render(m_Screen, m_Pos, m_ScreenSize.toVector2<int>());
	WriteConsoleOutput(OUTPUT_HANDLE, m_Screen, m_size, ZERO_POS, &m_rect);
	Clear();
}
void Camera2D::Clear() {
	for (int i = 0; i < m_ScreenSize.z; i++) {
		m_Screen[i].Attributes = DEFAULT_BACKGROUND;
	}
	m_Field.Clear();
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