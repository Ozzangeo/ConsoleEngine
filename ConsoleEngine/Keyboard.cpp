#include "Keyboard.h"

bool* Keyboard::m_isHold = new bool[256]{ false, };
KeyType* Keyboard::m_type = new KeyType[256]{ KeyType_NON, };
KeyType Keyboard::isKey(KeyCode code) { return m_type[code]; }
void Keyboard::Update() {
	bool Key;
	for (int code = 0; code < 256; code++) {
		Key = GetAsyncKeyState(code);

		if (Key && !m_isHold[code]) {
			m_isHold[code] = true;
			m_type[code] = KeyType_DOWN;
		}
		else if (Key && m_isHold[code]) { m_type[code] = KeyType_HOLD; }
		else if (!Key && m_isHold[code]) {
			m_isHold[code] = false;
			m_type[code] = KeyType_UP;
		}
		else { m_type[code] = KeyType_NON; }
	}
}
void Keyboard::Release() {
	if (m_isHold) { delete[] m_isHold; m_isHold = nullptr; }
	Debug::Log("[ Keyboard ] : Release");
}

bool Keyboard::isKeyDown(KeyCode code)	{ return m_type[code] == KeyType_DOWN; }
bool Keyboard::isKeyHold(KeyCode code)	{ return m_type[code] == KeyType_HOLD; }
bool Keyboard::isKeyUp  (KeyCode code)	{ return m_type[code] == KeyType_UP  ; }
