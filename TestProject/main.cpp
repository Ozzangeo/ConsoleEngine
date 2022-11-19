#include "../ConsoleEngine/ConsoleEngine.h"

using namespace std;
using namespace chrono;
using namespace Components;

class Mover : public Component {
private:
	Vector3f* move;
	float speed = 150.0f;
	PolygonCollider* Collider = nullptr;
	PolygonRenderer* Renderer = nullptr;
	GameObject* target = nullptr;

	void Awake() override {
		Collider = gameobject->AddComponent<PolygonCollider>();
		Renderer = gameobject->AddComponent<PolygonRenderer>();
		move = new Vector3f;
	}
	void Update() override {
		target = scene->GetGameObject(L"PolygonObjectTest");
		*move = 0.0f;

		if (Collider->isCollision(target)) { Renderer->color = Color_LightRed; }
		else { Renderer->color = Color_LightBlue; }

		if (keyboard.isKeyHold(KeyCode_W)) { *move += Vector3f(0, -speed, 0) * Time::GetDeltaTime(); }
		if (keyboard.isKeyHold(KeyCode_S)) { *move += Vector3f(0,  speed, 0) * Time::GetDeltaTime(); }
		if (keyboard.isKeyHold(KeyCode_A)) { *move += Vector3f(-speed, 0, 0) * Time::GetDeltaTime(); }
		if (keyboard.isKeyHold(KeyCode_D)) { *move += Vector3f( speed, 0, 0) * Time::GetDeltaTime(); }

		*gameobject->pos += *move;
	}
	void Remove() override {
		if (move) { delete move; move = nullptr; }
	}
};
class Rotator : public Component {
	Vector3f* rota = nullptr;
	float speed = 300.0f;

	void Awake() override {
		rota = new Vector3f(gameobject->Reset());
	}
	void Update() override {
		switch (keyboard.isKey(KeyCode_R)) {
		case KeyType_HOLD: {
			rota->x -= Time::GetDeltaTime() * speed;
			gameobject->SetRotateX(rota->x);
		} break;
		}
		switch (keyboard.isKey(KeyCode_T)) {
		case KeyType_HOLD: {
			rota->x += Time::GetDeltaTime() * speed;
			gameobject->SetRotateX(rota->x);
		} break;
		}

		switch (keyboard.isKey(KeyCode_F)) {
		case KeyType_HOLD: {
			rota->y -= Time::GetDeltaTime() * speed;
			gameobject->SetRotateY(rota->y);
		} break;
		}
		switch (keyboard.isKey(KeyCode_G)) {
		case KeyType_HOLD: {
			rota->y += Time::GetDeltaTime() * speed;
			gameobject->SetRotateY(rota->y);
		} break;
		}

		switch (keyboard.isKey(KeyCode_V)) {
		case KeyType_HOLD: {
			rota->z -= Time::GetDeltaTime() * speed;
			gameobject->SetRotateZ(rota->z);
		} break;
		}
		switch (keyboard.isKey(KeyCode_B)) {
		case KeyType_HOLD: {
			rota->z += Time::GetDeltaTime() * speed;
			gameobject->SetRotateZ(rota->z);
		} break;
		}

		switch (keyboard.isKey(KeyCode_Z))
		{
		case KeyType_DOWN: {
			*rota = gameobject->Reset();
		} break;
		}
	}
	void Remove() override {
		if (rota) { delete rota; rota = nullptr; }
	}
};

class SpriteObject : public GameObject {
private:
	void Components() override {
		auto* sprite = AddComponent<SpriteRenderer>();
		sprite->sprite.LoadSprite("Sans");

		auto* ani = AddComponent<Animator>();
		ani->animation.LoadAnimaition("Sans");
		
		*scale = Vector3f(2.5f);
	}
};
class PolygonObject : public GameObject {
private:
	void Components() override {
		auto* sprite = AddComponent<PolygonRenderer>();
		sprite->AddVertex(-5, -5);
		sprite->AddVertex(5, -5);
		sprite->AddVertex(5, 5);
		sprite->AddVertex(-5, 5);
		sprite->color = Color_SkyBlue;

		sprite->GetEdge();
	}
};

class TestScene : public Scene {
private:
	void GameObjects() final override {
		auto* camera = AddGameObject<GameObjects::Camera>(L"Camera");
		auto* a = camera->GetComponent<Camera>();
		a->SetCameraSize({ 256, 144 });
		a->SetCameraScale({ 4, 4 });

		AddGameObject<PolygonObject>(L"PolygonObjectTest");
		auto* obj = AddGameObject<PolygonObject>(L"PolygonObjectTest2");
		obj->AddComponent<Mover>();
		obj->AddComponent<Rotator>();
		*obj->pos = Vector3f(15, 15, 0);
		*obj->scale = Vector3f(0.5f, 0.5f, 1);
	}
};

int main() {
	ConsoleEngine engine;

	engine.Run<TestScene>(L"Engine", 1000);

	ConsoleEngine::Release();

	return 0;
}