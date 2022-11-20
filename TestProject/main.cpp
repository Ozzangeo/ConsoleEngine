#include "../ConsoleEngine/ConsoleEngine.h"

using namespace std;
using namespace chrono;
using namespace Components;

// 폴리곤 채우기 구현만 하면! 드디어 리듬게임 만들 수 있다! 그리고.. 그 이후 개발기간 3일.. 찌발
//

enum Tag {
	Poly
};

class Mover : public Component {
private:
	Vector3f* move;
	float speed = 150.0f;

	PolygonCollider* Collider = nullptr;
	PolygonRenderer* Renderer = nullptr;
	list<GameObject*> targets;

	void Awake() override {
		Collider = gameobject->AddComponent<PolygonCollider>();
		Renderer = gameobject->AddComponent<PolygonRenderer>();
		move = new Vector3f;
	}
	void Start() override {
		targets = scene->GetGameObjectList(Poly);
	}
	void Update() override {
		*move = 0.0f;

		if (Collider->isCollision(targets)) { Renderer->color = Color_LightRed; }
		else { Renderer->color = Color_SkyBlue; }

		if (keyboard.isKeyHold(KeyCode_W)) { *move += Vector3f(0, -speed, 0) * Time::GetDeltaTime(); }
		if (keyboard.isKeyHold(KeyCode_S)) { *move += Vector3f(0,  speed, 0) * Time::GetDeltaTime(); }
		if (keyboard.isKeyHold(KeyCode_A)) { *move += Vector3f(-speed, 0, 0) * Time::GetDeltaTime(); }
		if (keyboard.isKeyHold(KeyCode_D)) { *move += Vector3f( speed, 0, 0) * Time::GetDeltaTime(); }
		if (keyboard.isKeyDown(KeyCode_1)) { *gameobject->pos = Vector3f(15.0f, 15.0f, 0); }

		/*Collider->isCollisionVec(targets, Vector3f(0, -speed, 0) * Time::GetDeltaTime())
		Collider->isCollisionVec(targets, Vector3f(0, speed, 0) * Time::GetDeltaTime())
		Collider->isCollisionVec(targets, Vector3f(-speed, 0, 0) * Time::GetDeltaTime())
		Collider->isCollisionVec(targets, Vector3f(speed, 0, 0) * Time::GetDeltaTime())*/

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

		*AddGameObject<PolygonObject>(L"PolygonObjectTest", Poly)->scale = Vector3f(1.5, 2, 0);
		*AddGameObject<PolygonObject>(L"PolygonObjectTest", Poly)->pos = Vector3f(-30, -20, 0);
		auto* c = AddGameObject<PolygonObject>(L"PolygonObjectTest", Poly);
		*c->pos = Vector3f(50, 30, 0);
		c->SetRotate(0, 0, 45);

		auto* obj = AddGameObject<PolygonObject>(L"PolygonObjectTest2");
		obj->AddComponent<Mover>();
		obj->AddComponent<Rotator>();
		*obj->pos = Vector3f(15, 15, 5);
		*obj->scale = Vector3f(0.5f, 0.5f, 1);
		obj->GetComponent<PolygonRenderer>()->isFill = true;
	}
};

int main() {
	ConsoleEngine engine;

	engine.Run<TestScene>(L"Engine", 1000);

	ConsoleEngine::Release();

	return 0;
}