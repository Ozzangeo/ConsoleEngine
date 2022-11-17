#include "GameObjects.h"

using namespace GameObjects;

void Camera::Components() {
	this->isOnceGameObject = true;
	AddComponent<Components::Camera>();
}

void Rectangle::Components() {
	auto* Polygon = AddComponent<Components::PolygonRenderer>();
	Polygon->AddVertex(5, 5);
	Polygon->AddVertex(5, -5);
	Polygon->AddVertex(-5, -5);
	Polygon->AddVertex(-5, 5);
}
