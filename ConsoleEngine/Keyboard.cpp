#include "Keyboard.h"

bool* Keyboard::isHold = new bool[256]{ false, };
KeyType* Keyboard::type = new KeyType[256]{ KeyType_NON, };
KeyType Keyboard::isKey(KeyCode code) {
	return type[code];
}
void Keyboard::Update() {
	bool Key;
	for (int code = 0; code < 256; code++) {
		Key = GetAsyncKeyState(code);

		if (Key && !isHold[code]) {
			isHold[code] = true;
			type[code] = KeyType_DOWN;
		}
		else if (Key && isHold[code]) { type[code] = KeyType_HOLD; }
		else if (!Key && isHold[code]) {
			isHold[code] = false;
			type[code] = KeyType_UP;
		}
		else { type[code] = KeyType_NON; }
	}
}
void Keyboard::Release() {
	if (isHold) { delete[] isHold; isHold = nullptr; }
	Debug::Log("[ Keyboard ] : Release");
}

// Keyboard Beta 기능들 ( 불완전함 )
bool Keyboard::Beta::isKeyDown(KeyCode code)	{ return isKey(code) == KeyType_DOWN; }
bool Keyboard::Beta::isKeyHold(KeyCode code)	{ return isKey(code) == KeyType_HOLD; }
bool Keyboard::Beta::isKeyUp  (KeyCode code)	{ return isKey(code) == KeyType_UP	; }
