#ifndef _COMPONENTS_
#define _COMPONENTS_

#include "stdafx.h"

class A : public Component {
private:
	Components::Client* client;
	float speed = 50.0f;
	Vector3f* move;

	void Awake() override { move = new Vector3f; }
	void Start() override {
		client = gameobject->AddComponent<Components::Client>();
		client->JoinServer("192.168.219.105", 8080);
	}
	void Update() override;
	void Remove() override { delete move; }
};


#endif // !_COMPONENTS_
