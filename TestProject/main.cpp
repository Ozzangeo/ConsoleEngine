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
class Rotator2 : public Component {
	Vector4f* rota = nullptr;
	float speed = 300.0f;

	void Awake() override {
		rota = new Vector4f(gameobject->Reset());
	}
	void Update() override {
		switch (keyboard.isKey(KeyCode_Y)) {
		case KeyType_HOLD: {
			rota->x -= Time::GetDeltaTime() * speed;
			gameobject->SetRotateX(rota->x);
		} break;
		}
		switch (keyboard.isKey(KeyCode_U)) {
		case KeyType_HOLD: {
			rota->x += Time::GetDeltaTime() * speed;
			gameobject->SetRotateX(rota->x);
		} break;
		}

		switch (keyboard.isKey(KeyCode_H)) {
		case KeyType_HOLD: {
			rota->y -= Time::GetDeltaTime() * speed;
			gameobject->SetRotateY(rota->y);
		} break;
		}
		switch (keyboard.isKey(KeyCode_J)) {
		case KeyType_HOLD: {
			rota->y += Time::GetDeltaTime() * speed;
			gameobject->SetRotateY(rota->y);
		} break;
		}

		switch (keyboard.isKey(KeyCode_N)) {
		case KeyType_HOLD: {
			rota->z -= Time::GetDeltaTime() * speed;
			gameobject->SetRotateZ(rota->z);
		} break;
		}
		switch (keyboard.isKey(KeyCode_M)) {
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
class CircleRender : public Component {
private:
	float delta;

	void Awake() override {
		delta = 0;
	}
	void Update() override {
		graphic.Circle(*gameobject->pos, gameobject->GetRotate(), *gameobject->scale, Color_LightRed, 10, 0);
	}
	void Remove() override {

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

		auto* a = camera->GetComponent<Camera>();
		a->SetCameraSize({ 256, 144 });
		a->SetCameraScale({ 4, 4 });

		//AddGameObject<SpriteObject>(L"SpriteObjectTest");

		auto* obj = AddGameObject<PolygonObject>(L"PolygonObjectTest");
		obj->AddComponent<Rotator>();
		obj->AddComponent<CircleRender>();
		*obj->scale = { 4, 4, 1 };
	}
};

int main() {
	ConsoleEngine engine;

	engine.Run<TestScene>(L"Engine", 1000);

	ConsoleEngine::Release();

	return 0;
}