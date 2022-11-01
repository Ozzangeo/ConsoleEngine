#include "DefaultComponents.h"

using namespace DefaultComponents;

void Camera::Awake() {
	SetCameraSize({ 128, 72 });
}
void Camera::Update() {
	/////////////////// Render ////////////////
	Vector2<int> CameraSize = m_CameraSize.toVector2<int>();

	graphic.Merge(m_Screen, gameobject->pos.toVector2<float>(), CameraSize);
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

void Camera::SetFieldSize(Vector3<int> Size) {
	graphic.ReSize(Size);
}
void Camera::SetCameraSize(Vector2<int> Size) {
	m_CameraSize = { Size.x, Size.y, Size.x * Size.y };
	m_HalfScreenSize = m_CameraSize.toVector2<int>() * 0.5f;
	
	m_rect = { 0, 0, static_cast<short>(m_CameraSize.x), static_cast<short>(m_CameraSize.y) };
	m_size = { static_cast<short>(m_CameraSize.x), static_cast<short>(m_CameraSize.y) };

	if (m_Screen) { delete[] m_Screen; m_Screen = nullptr; }
	m_Screen = new CHAR_INFO[static_cast<size_t>(m_CameraSize.z)];

	SetScreen();

	for (int i = 0; i < m_CameraSize.z; i++) { m_Screen[i] = { ' ', DEFAULT_BACKGROUND }; }
}
void Camera::SetScreen() {
	string System = "mode con: cols=" + to_string(m_CameraSize.x) + " lines=" + to_string(m_CameraSize.y);
	system(System.c_str());
}