#include "../ConsoleEngine/Engine.h"

using namespace std;
using namespace chrono;
using namespace DefaultComponents;

class CameraMover : public Component {
private:
	Vector4* Pos = nullptr;
	float speed = 150.0f;

	void Awake() override {
		Pos = &scene->GetGameObject(L"Camera")->pos;
	}
	void Update() override {
		switch (keyboard.isKey(KeyCode_W)) {
		case KeyType_HOLD: {
			Pos->y -= Time::GetDeltaTime() * speed;
		} break;
		}
		switch (keyboard.isKey(KeyCode_S)) {
		case KeyType_HOLD: {
			Pos->y += Time::GetDeltaTime() * speed;
		} break;
		}
		switch (keyboard.isKey(KeyCode_A)) {
		case KeyType_HOLD: {
			Pos->x -= Time::GetDeltaTime() * speed;
		} break;
		}
		switch (keyboard.isKey(KeyCode_D)) {
		case KeyType_HOLD: {
			Pos->x += Time::GetDeltaTime() * speed;
		} break;
		}

		graphic.Line({ 0, 0, 0 }, { 10, 10, 0 }, Color_Green);
		graphic.Circle({ 0, 0, 0 }, Color_Red, 5, 0);
	}
	void Remove() override {

	}
};
class SpriteObject : public GameObject {
private:
	void Components() override {
		auto* sprite = AddComponent<SpriteRenderer>();
		sprite->AddVertex({ 0, -5, 0 });
		sprite->AddVertex({ 0, 5, 0 });
		sprite->AddVertex({ 5, 0, 0 });
	}
};
class C : public Scene {
private:
	void GameObjects() override {
		auto* camera = AddGameObject<DefaultGameObjects::Camera>(L"Camera");
		camera->AddComponent<CameraMover>();

		auto* a = camera->GetComponent<Camera>();
		a->SetCameraSize({ 256, 144 });
		a->SetCameraScale({ 4, 4 });

		AddGameObject<SpriteObject>(L"SpriteObjectTest");
	}
};

int main() {
	Engine engine;

	engine.Run<C>(L"Engine", 1000);

	Engine::Release();

	return 0;
}