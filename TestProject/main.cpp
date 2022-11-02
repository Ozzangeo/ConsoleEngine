#include "../ConsoleEngine/Engine.h"

using namespace std;
using namespace chrono;
using namespace DefaultGameObjects;

// Component �����ϱ�
class CameraMover : public Component {
private:
	Vector4* Pos = nullptr;
	float speed = 150.0f;
	BYTE byte = 40;

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
			if (byte < 255) { byte += Time::GetDeltaTime() * 200.0f; }
		} break;
		}
		color.SetColor({ byte, 10, 20 }, 7);
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

// �ؾ��Ұ�
// �׷��� Ŭ������ ���� ���� �Լ� �߰��ϱ�
// ���� �̰Ÿ��� ���µ�..?

int main() {
	Engine engine;

	engine.Run<C>(L"Engine", 1000);

	Engine::Release();

	return 0;
}