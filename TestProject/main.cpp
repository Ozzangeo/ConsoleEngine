#include "../ConsoleEngine/Engine.h"
#include "../ConsoleEngine/Keyboard.h"
#include "../ConsoleEngine/Time.h"

using namespace std;
using namespace chrono;
// 카메라 & 필드 구현 해야함

class TestScript : public EngineScript {
private:
	bool Update() override {
		switch (Keyboard::isKey(KeyCode_A)) {
		case KeyType_DOWN: {
			cout << "Down\n";
		} break;
		case KeyType_HOLD: {
			cout << "Hold " << (int)round(1.0f / Time::GetDeltaTime()) << "\n";
		} break;
		case KeyType_UP: {
			cout << "Up\n\n";
		} break;
		}
		switch (Keyboard::isKey(KeyCode_B)) {
		case KeyType_DOWN: {
			return false;
		} break;
		}

		return true;
	}
	void Remove() override {}
};

int main() {
	Engine* engine = Engine::GetInstance();

	engine->Run<TestScript>();

	Engine::Release();
	Keyboard::Release();

	return 0;
}