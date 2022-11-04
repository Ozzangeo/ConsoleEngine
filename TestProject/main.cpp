#include "../ConsoleEngine/Engine.h"

using namespace std;
using namespace chrono;
using namespace DefaultComponents;

class Mover : public Component {
private:
	float speed = 150.0f;

	void Awake() override {}
	void Update() override {
		switch (keyboard.isKey(KeyCode_W)) {
		case KeyType_HOLD: {
			gameobject->pos.y -= Time::GetDeltaTime() * speed;
		} break;
		}
		switch (keyboard.isKey(KeyCode_S)) {
		case KeyType_HOLD: {
			gameobject->pos.y += Time::GetDeltaTime() * speed;
		} break;
		}
		switch (keyboard.isKey(KeyCode_A)) {
		case KeyType_HOLD: {
			gameobject->pos.x -= Time::GetDeltaTime() * speed;
		} break;
		}
		switch (keyboard.isKey(KeyCode_D)) {
		case KeyType_HOLD: {
			gameobject->pos.x += Time::GetDeltaTime() * speed;
		} break;
		}

		graphic.Line({ 0, 0, 0 }, { 10, 10, 0 }, Color_Green);
		graphic.Circle({ 0, 0, 0 }, Color_Red, 5, 0);
	}
	void Remove() override {}
};
class SpriteObject : public GameObject {
private:
	void Components() override {
		auto* sprite = AddComponent<SpriteRenderer>();
		sprite->LoadSprite("Sans");

		pos.x = 0;
		pos.z = 10;
	}
};
class PolygonObject : public GameObject {
private:
	void Components() override {
		auto* sprite = AddComponent<PolygonRenderer>();
		sprite->AddVertex({ -5, -5, 0 });
		sprite->AddVertex({ 0, 5, 0 });
		sprite->AddVertex({ 5, 0, 0 });
		sprite->color = Color_SkyBlue;

		pos.x = 10;
		this->pos.z = -5;
	}
};
class C : public Scene {
private:
	void GameObjects() override {
		auto* camera = AddGameObject<DefaultGameObjects::Camera>(L"Camera");
		camera->AddComponent<Mover>();

		auto* a = camera->GetComponent<Camera>();
		a->SetCameraSize({ 256, 144 });
		a->SetCameraScale({ 4, 4 });

		auto* obj = AddGameObject<SpriteObject>(L"SpriteObjectTest");
		obj->AddComponent<Mover>();
		AddGameObject<PolygonObject>(L"PolygonObjectTest");
	}
};

int main() {
	Engine engine;

	engine.Run<C>(L"Engine", 1000);

	Engine::Release();

	return 0;
}