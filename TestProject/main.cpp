#include "../ConsoleEngine/Engine.h"

using namespace std;
using namespace chrono;
using namespace DefaultGameObjects;

// Component 수정하기
class CameraMover : public Component {
private:
	Vector4* Pos = nullptr;
	float speed = 150.0f;
	float byte = 40;

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

		switch (keyboard.isKey(KeyCode_1))
		{
		case KeyType_HOLD: {
			if (byte > 0) { byte -= Time::GetDeltaTime() * 200.0f; }
 		} break;
		}
		switch (keyboard.isKey(KeyCode_2))
		{
		case KeyType_HOLD: {
			if (byte < 254) { byte += Time::GetDeltaTime() * 200.0f; }
		} break;
		}
		color.SetColor({ static_cast<BYTE>(byte), 10, 20 }, 7);
		graphic.Fill({ -10, byte, 0 }, { 10, 0, 0 }, Color_White);
		graphic.Line({ -10, byte, 1 }, { -30, 0, 0 }, Color_LightBlue);
		graphic.Circle({ 0, 0, 4 }, Color_LightGreen, byte, 0);
	}
	void Remove() override {

	}
};
class B : public GameObject {
private:
	void Components() override {
		AddComponent<CameraMover>();
	}
};
class C : public Scene {
private:
	void GameObjects() override {
		Camera* camera = AddGameObject<Camera>(L"Camera");
		camera->pos = { 0, 0, 0 };
		auto* a = camera->GetComponent<DefaultComponents::Camera>();
		a->SetCameraSize({ 256, 144 });
		a->SetCameraScale({ 4, 4 });

		AddGameObject<B>(L"Camera2");
	}
};

// 해야할거
// 그래픽 클래스에 여러 도형 함수 추가하기
// 딱히 이거말고 없는듯..?

int main() {
	Engine engine;

	engine.Run<C>(L"Engine", 1000);

	Engine::Release();

	return 0;
}