#include "../ConsoleEngine/ConsoleEngine.h"

using namespace std;
using namespace chrono;
using namespace Components;

// Prefab ¸¸µé±â

class Mover : public Component {
private:
	float speed = 150.0f;

	void Awake() override {}
	void Update() override {
		switch (keyboard.isKey(KeyCode_W)) {
		case KeyType_HOLD: { gameobject->pos->y -= Time::GetDeltaTime() * speed; } break;
		}
		switch (keyboard.isKey(KeyCode_S)) {
		case KeyType_HOLD: { gameobject->pos->y += Time::GetDeltaTime() * speed; } break;
		}
		switch (keyboard.isKey(KeyCode_A)) {
		case KeyType_HOLD: { gameobject->pos->x -= Time::GetDeltaTime() * speed; } break;
		}
		switch (keyboard.isKey(KeyCode_D)) {
		case KeyType_HOLD: { gameobject->pos->x += Time::GetDeltaTime() * speed; } break;
		}
	}
	void Remove() override {}
};
class Rotator : public Component {
	Vector4f* rota = nullptr;
	float speed = 300.0f;

	void Awake() override {
		rota = new Vector4f(gameobject->Reset());
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
		
		*scale = Vector4f(2.5f);
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
	}
};
class TestScene : public Scene {
private:
	void GameObjects() final override {
		auto* camera = AddGameObject<GameObjects::Camera>(L"Camera");
		camera->AddComponent<Mover>();
		camera->AddComponent<Rotator>();

		auto* a = camera->GetComponent<Camera>();
		a->SetCameraSize({ 512, 288 });
		a->SetCameraScale({ 1, 1 });

		auto* obj = AddGameObject<SpriteObject>(L"SpriteObjectTest");
		AddGameObject<PolygonObject>(L"PolygonObjectTest");
	}
};

int main() {
	ConsoleEngine engine;

	engine.Run<TestScene>(L"Engine", 1000);

	ConsoleEngine::Release();

	return 0;
}