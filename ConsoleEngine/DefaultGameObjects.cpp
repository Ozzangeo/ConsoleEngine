#include "DefaultGameObjects.h"

using namespace DefaultGameObjects;

void Camera::Components() {
	this->isOnceGameObject = true;
	AddComponent<DefaultComponents::Camera>();
}
