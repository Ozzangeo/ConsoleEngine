#include "../ConsoleEngine/Keyboard.h"
#include "../ConsoleEngine/Time.h"

using namespace std;
// 카메라 & 필드 구현 해야함

int main() {

	while (1) {
		switch (Keyboard::isKey(KeyCode_A))
		{
		case KeyType_DOWN: { cout << "Down\n"; } break;
		case KeyType_HOLD: { cout << "Hold" << Time::DeltaTime << "\n"; Sleep(100); } break;
		case KeyType_UP: { cout << "Up\n"; } break;
		}
	}

	return 0;
}