#include "DefaultGameObjects.h"

using namespace DefaultGameObjects;

void Camera2D::Components() {
	this->isOnceGameObject = true;
	AddComponent<DefaultComponents::Camera2D>();
}
