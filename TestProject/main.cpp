#include "../ConsoleEngine/Engine2D.h"

using namespace std;
using namespace chrono;
using namespace DefaultGameObjects;

// Component �����ϱ�
class CameraMover : public Component {
private:
	Vector3<float>* Pos;
	float speed = 150.0f;
	BYTE byte = 0;

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
			if (byte > 0) { byte--; }
 		} break;
		}
		switch (keyboard.isKey(KeyCode_2))
		{
		case KeyType_HOLD: {
			if (byte < 255) { byte++; }
		} break;
		}
		color.SetColor({ byte, byte, byte }, 7);
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
		camera2D->pos = { 0, 4, 0 };
		auto* a = camera2D->GetComponent<DefaultComponents::Camera2D>();
		a->SetFieldSize({ 160, 90, 1 });
		a->SetScreenSize({ 256, 144 });

		AddGameObject<B>(L"Camera2");
	}
};

// hotspot ����ȭ ���̵��
// ����� ������� ����� �񵿱�ȭ ����� �Ѵ�?
// ������.. ���� ����� ������Ʈ���� ������ ����ϴ� ���߿� Screen�� �ٲ�ٸ�?

// Camera : Write..() �ʵ尡 256x144�� ��, �� 6ms ( hotspot )
// Field2D : Merge() �ʵ尡 160x90x20�� ��, �� 3ms
// �̿� : �� 1ms..
// ���� = 10ms

int main() {
	Engine2D engine({ 1, 1 });

	engine.Run<C>(L"Engine", 1000);

	Engine2D::Release();

	return 0;
}