#include "Components.h"

void A::Update() {
	*move = Vector3f::ZERO;
	if (keyboard.isKeyDown(KeyCode_W)) {
		client->sendServer("W");
		*move += Vector3f(0, -speed, 0) * Time::GetDeltaTime();
	}
	if (keyboard.isKeyDown(KeyCode_S)) {
		client->sendServer("S");
		*move += Vector3f(0, speed, 0) * Time::GetDeltaTime();
	}
	if (keyboard.isKeyDown(KeyCode_A)) {
		client->sendServer("A");
		*move += Vector3f(-speed, 0, 0) * Time::GetDeltaTime();
	}
	if (keyboard.isKeyDown(KeyCode_D)) {
		client->sendServer("D");
		*move += Vector3f(speed, 0, 0) * Time::GetDeltaTime();
	}

	*gameobject->pos += *move;
}