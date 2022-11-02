#include "Keyboard.h"

bool* Keyboard::isHold = new bool[256]{ false, };
KeyType Keyboard::isKey(KeyCode code) {
	bool Key = GetAsyncKeyState(code);

	if (Key && !isHold[code]) {
		isHold[code] = true;
		return KeyType_DOWN;
	}
	else if (Key && isHold[code]) { return KeyType_HOLD; }
	else if (!Key && isHold[code]) {
		isHold[code] = false;
		return KeyType_UP;
	}
	else { return KeyType_NON; }
}
void Keyboard::Release() {
	if (isHold) { delete[] isHold; isHold = nullptr; }
	Debug::Log("[ Keyboard ] : Release");
}

// Keyboard Beta 기능들 ( 불완전함 )
bool Keyboard::Beta::isKeyDown(KeyCode code)	{ return isKey(code) == KeyType_DOWN; }
bool Keyboard::Beta::isKeyHold(KeyCode code)	{ return isKey(code) == KeyType_HOLD; }
bool Keyboard::Beta::isKeyUp	(KeyCode code)	{ return isKey(code) == KeyType_UP	; }
