#include "GameObjects.h"

using namespace GameObjects;

void Camera::Components() {
	this->isOnceGameObject = true;
	AddComponent<Components::Camera>();
}

void Rectangle::Components() {
	auto* polygon = AddComponent<Components::PolygonRenderer>();
	polygon->AddVertex(5, 5);
	polygon->AddVertex(5, -5);
	polygon->AddVertex(-5, -5);
	polygon->AddVertex(-5, 5);
}
void Circle::Components() {
	auto* circle = AddComponent<Components::CircleRenderer>();
	circle->radius = 10.0f;
}
