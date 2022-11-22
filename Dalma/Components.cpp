#include "Components.h"

using namespace std;
using namespace Components;

void Mover::Awake() {
	move = new Vector3f;
}
void Mover::Start() {
	server = scene->GetGameObject(Tag_Server)->GetComponent<Server>();
}
void Mover::Update() {
	*move = Vector3f::ZERO;

	if (keyboard.isKeyHold(KeyCode_W)) { *move += Vector3f(0, -speed, 0) * Time::GetDeltaTime(); server->sendMsgAll("위"); }
	if (keyboard.isKeyHold(KeyCode_A)) { *move += Vector3f(-speed, 0, 0) * Time::GetDeltaTime(); server->sendMsgAll("왼쪽"); }
	if (keyboard.isKeyHold(KeyCode_S)) { *move += Vector3f(0,  speed, 0) * Time::GetDeltaTime(); server->sendMsgAll("아래"); }
	if (keyboard.isKeyHold(KeyCode_D)) { *move += Vector3f( speed, 0, 0) * Time::GetDeltaTime(); server->sendMsgAll("오른쪽"); }

	*gameobject->pos += *move;
}
void Mover::Remove() {
	delete move;
}

void DownNote::Update() {
	*gameobject->pos += Vector3f(0, speed, 0) * Time::GetDeltaTime();
	if (gameobject->pos->y >= 30) { scene->RemoveGameObject(this->gameobject); }
}
