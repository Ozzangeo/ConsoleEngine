#include "../ConsoleEngine/Keyboard.h"
#include "../ConsoleEngine/Time.h"

using namespace std;
// ī�޶� & �ʵ� ���� �ؾ���

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