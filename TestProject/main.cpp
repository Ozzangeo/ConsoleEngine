#include "../ConsoleEngine/Engine.h"
#include "../ConsoleEngine/Keyboard.h"
#include "../ConsoleEngine/Time.h"

using namespace std;
using namespace chrono;

class TestScript : public EngineScript {
private:
	Camera2D* m_Camera = Camera2D::GetInstance();
	Color* m_Color = Color::GetInstance();

	Vector2<float>* m_CameraPos = nullptr;
	int speed = 1;
	float r = 0;

	bool Awake() override {
		m_CameraPos = m_Camera->GetPos();
		return true;
	}
	bool Update() override {
		switch (Keyboard::isKey(KeyCode_ESC)) {
		case KeyType_DOWN: {
			return false;
		} break;
		}
		
		switch (Keyboard::isKey(KeyCode_LSHIFT))
		{
		case KeyType_HOLD: {
			speed = 100;
		} break;
		case KeyType_NON: {
			speed = 10;
		} break;
		}
		switch (Keyboard::isKey(KeyCode_D)) {
		case KeyType_HOLD: {
			m_CameraPos->x += speed * Time::GetDeltaTime();
		}
		}
		switch (Keyboard::isKey(KeyCode_A)) {
		case KeyType_HOLD: {
			m_CameraPos->x -= speed * Time::GetDeltaTime();
		}
		}
		switch (Keyboard::isKey(KeyCode_W)) {
		case KeyType_HOLD: {
			m_CameraPos->y -= speed * Time::GetDeltaTime();
		}
		}
		switch (Keyboard::isKey(KeyCode_S)) {
		case KeyType_HOLD: {
			m_CameraPos->y += speed * Time::GetDeltaTime();
		}
		}

		switch (Keyboard::isKey(KeyCode_LEFT)) {
		case KeyType_HOLD: {
			r -= Time::GetDeltaTime() * 150;
			if (255 >= r && r >= 0) { m_Color->SetColor({ static_cast<BYTE>(r), static_cast<BYTE>(r), 255 }, 0); }
		}
		}
		switch (Keyboard::isKey(KeyCode_RIGHT)) {
		case KeyType_HOLD: {
			r += Time::GetDeltaTime() * 150;
			if (255 >= r && r >= 0) { m_Color->SetColor({ static_cast<BYTE>(r), static_cast<BYTE>(r), 255 }, 0); }
		}
		}


		return true;
	}
	void Remove() override {}
};

int main() {
	Engine* engine = Engine::GetInstance();

	engine->FontSetting({ 1, 1 });
	engine->Run<TestScript, 1000>();

	return 0;
}