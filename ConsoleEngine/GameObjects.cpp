#include "GameObjects.h"

using namespace GameObjects;

void Camera::Components() {
	this->isOnceGameObject = true;
	AddComponent<Components::Camera>();
}
