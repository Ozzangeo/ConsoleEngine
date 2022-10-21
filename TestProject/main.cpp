#include "../ConsoleEngine/Engine.h"
#include "../ConsoleEngine/Keyboard.h"
#include "../ConsoleEngine/Time.h"

using namespace std;
using namespace chrono;
// 카메라(성공) & 필드(레이어, 미완) 구현 해야함

class TestScript : public EngineScript {
private:
	Camera2D* m_Camera = Camera2D::GetInstance();
	Vector2* m_CameraPos = nullptr;

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

		switch (Keyboard::isKey(KeyCode_RIGHT)) {
		case KeyType_HOLD: {
			m_CameraPos->x += 100 * Time::GetDeltaTime();
		}
		}
		switch (Keyboard::isKey(KeyCode_LEFT)) {
		case KeyType_HOLD: {
			m_CameraPos->x -= 100 * Time::GetDeltaTime();
		}
		}
		switch (Keyboard::isKey(KeyCode_UP)) {
		case KeyType_HOLD: {
			m_CameraPos->y -= 100 * Time::GetDeltaTime();
		}
		}
		switch (Keyboard::isKey(KeyCode_DOWN)) {
		case KeyType_HOLD: {
			m_CameraPos->y += 100 * Time::GetDeltaTime();
		}
		}

		return true;
	}
	void Remove() override {}
};

int main() {
	Engine::GetInstance()->Run<TestScript, 60>();

	return 0;
}