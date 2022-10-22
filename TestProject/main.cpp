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
	int speed = 1;

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
		return true;
	}
	void Remove() override {}
};


int main() {
	CONSOLE_FONT_INFOEX cfi{};
	cfi.dwFontSize = { 1, 1 };
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, TEXT("Raster Fonts"));

	Engine::GetInstance()->Setting(cfi);
	Engine::GetInstance()->Run<TestScript, 60>();

	return 0;
}