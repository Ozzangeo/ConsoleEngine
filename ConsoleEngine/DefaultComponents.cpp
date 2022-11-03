#include "DefaultComponents.h"

using namespace DefaultComponents;

void Camera::Awake() {
	COORD CameraSize = { 128, 72 };
	graphic.SetScreenSize(CameraSize);
	graphic.CameraPos = &gameobject->pos;
}
void Camera::Update() {
	graphic.Render();
}
void Camera::Remove() {
	
}

void Camera::SetCameraScale(COORD Scale) {
	graphic.SetScreenScale(Scale);
}
void Camera::SetCameraSize(COORD Size) {
	graphic.SetScreenSize(Size);
}
