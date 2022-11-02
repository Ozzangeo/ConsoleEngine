#include "DefaultComponents.h"

using namespace DefaultComponents;

void Camera::Awake() {
	SetCameraSize({ 128, 72 });
}
void Camera::Update() {
	/////////////////// Render ////////////////
	Vector4 CameraSize = m_CameraSize;

	graphic.Merge(m_Screen, gameobject->pos, CameraSize);
	graphic.Render(m_Screen, CameraSize, m_size, m_rect);
	///////////////////////////////////////////

	/////////////////// Clear /////////////////
	for (int i = 0; i < m_CameraSize.z; i++) {
		m_Screen[i].Attributes = DEFAULT_BACKGROUND;
	}
	graphic.FieldClear();
	///////////////////////////////////////////
}
void Camera::Remove() {
	if (m_Screen) { delete[] m_Screen; m_Screen = nullptr; }
}

void Camera::SetFieldSize(COORD Size, int Depth) {
	graphic.ReSize(Size, Depth);
}
void Camera::SetCameraSize(COORD Size) {
	m_CameraSize = { static_cast<float>(Size.X), static_cast<float>(Size.Y), static_cast<float>(Size.X * Size.Y), 0 };
	m_HalfScreenSize = (m_CameraSize * 0.5f).vround();
	
	m_rect = { 0, 0, m_CameraSize.GetX<short>(), m_CameraSize.GetY<short>() };
	m_size = { m_CameraSize.GetX<short>(), m_CameraSize.GetY<short>() };

	if (m_Screen) { delete[] m_Screen; m_Screen = nullptr; }
	m_Screen = new CHAR_INFO[m_CameraSize.GetZ<size_t>()];

	SetScreen();

	for (int i = 0, d = m_CameraSize.GetZ<int>(); i < d; i++) { m_Screen[i] = { ' ', DEFAULT_BACKGROUND }; }
}
void Camera::SetScreen() {
	string System = "mode con: cols=" + to_string(m_CameraSize.GetX<int>()) + " lines=" + to_string(m_CameraSize.GetY<int>());
	system(System.c_str());
}