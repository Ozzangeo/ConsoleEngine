#include "../ConsoleEngine/Engine2D.h"

using namespace std;
using namespace chrono;
using namespace DefaultGameObjects;

// Component 수정하기
class CameraMover : public Component {
private:
	Vector3<float>* Pos;
	float speed = 150.0f;

	void Awake() override {

	}
	void Update() override {
		switch (keyboard.isKey((KeyCode)'w')) {
		case KeyType_DOWN: {
			Pos->y += Time::GetDeltaTime() * speed;
		} break;
		}
		switch (keyboard.isKey((KeyCode)'s')) {
		case KeyType_DOWN: {
			Pos->y -= Time::GetDeltaTime() * speed;
		} break;
		}
		switch (keyboard.isKey((KeyCode)'a')) {
		case KeyType_DOWN: {
			Pos->x -= Time::GetDeltaTime() * speed;
		} break;
		}
		switch (keyboard.isKey((KeyCode)'d')) {
		case KeyType_DOWN: {
			Pos->x += Time::GetDeltaTime() * speed;
		} break;
		}
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
		Camera2D* camera2D = AddGameObject<Camera2D>(L"Camera");
		camera2D->GetComponent<DefaultComponents::Camera2D>()->SetFieldSize({ 16, 9, 1 });
		AddGameObject<B>(L"Camera2");
	}
};

int main() {
	Engine2D engine({ 8, 8 });

	engine.Run<C>(L"Engine", 1000);

	Engine2D::Release();

	return 0;
}