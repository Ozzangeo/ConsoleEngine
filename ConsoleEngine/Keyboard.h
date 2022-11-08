#ifndef ___KEYBOARD___
#define ___KEYBOARD___

#include "stdafx.h"
#include "Debug.h"

enum KeyCode {
	KeyCode_BACK = 0x08,
	KeyCode_TAP = 0x09,
	KeyCode_ENTER = 0x0D,
	KeyCode_SHIFT = 0x10,
	KeyCode_CTRL = 0x11,
	KeyCode_ALT = 0x12,
	KeyCode_PAUSE = 0x13,
	KeyCode_CAPS = 0x14,
	KeyCode_ESC = 0x1B,
	KeyCode_SPACE = 0x20,
	KeyCode_PAGEUP = 0x21,
	KeyCode_PAGEDOWN = 0x22,
	KeyCode_HOME = 0x24,
	KeyCode_LEFT = 0x25,
	KeyCode_UP = 0x26,
	KeyCode_RIGHT = 0x27,
	KeyCode_DOWN = 0x28,
	KeyCode_SELECT = 0x29,
	KeyCode_PRINT = 0x2A,
	KeyCode_EXECUTE = 0x2B,
	KeyCode_PS = 0x2C,
	KeyCode_INS = 0x2D,
	KeyCode_DEL = 0x2E,
	KeyCode_HELP = 0x2F,

	KeyCode_0 = 0x30,
	KeyCode_1 = 0x31,
	KeyCode_2 = 0x32,
	KeyCode_3 = 0x33,
	KeyCode_4 = 0x34,
	KeyCode_5 = 0x35,
	KeyCode_6 = 0x36,
	KeyCode_7 = 0x37,
	KeyCode_8 = 0x38,
	KeyCode_9 = 0x39,

	KeyCode_A = 0x41,
	KeyCode_B = 0x42,
	KeyCode_C = 0x43,
	KeyCode_D = 0x44,
	KeyCode_E = 0x45,
	KeyCode_F = 0x46,
	KeyCode_G = 0x47,
	KeyCode_H = 0x48,
	KeyCode_I = 0x49,
	KeyCode_J = 0x4A,
	KeyCode_K = 0x4B,
	KeyCode_L = 0x4C,
	KeyCode_M = 0x4D,
	KeyCode_N = 0x4E,
	KeyCode_O = 0x4F,
	KeyCode_P = 0x50,
	KeyCode_Q = 0x51,
	KeyCode_R = 0x52,
	KeyCode_S = 0x53,
	KeyCode_T = 0x54,
	KeyCode_U = 0x55,
	KeyCode_V = 0x56,
	KeyCode_W = 0x57,
	KeyCode_X = 0x58,
	KeyCode_Y = 0x59,
	KeyCode_Z = 0x5A,

	KeyCode_LWIN = 0x5B,
	KeyCode_RWIN = 0x5C,
	KeyCode_SLEEP = 0x5F,
	KeyCode_NUMPAD_0 = 0x60,
	KeyCode_NUMPAD_1 = 0x61,
	KeyCode_NUMPAD_2 = 0x62,
	KeyCode_NUMPAD_3 = 0x63,
	KeyCode_NUMPAD_4 = 0x64,
	KeyCode_NUMPAD_5 = 0x65,
	KeyCode_NUMPAD_6 = 0x66,
	KeyCode_NUMPAD_7 = 0x67,
	KeyCode_NUMPAD_8 = 0x68,
	KeyCode_NUMPAD_9 = 0x69,
	KeyCode_NUMPAD_MUL = 0x6A,
	KeyCode_NUMPAD_ADD = 0x6B,
	KeyCode_SEP = 0x6C,
	KeyCode_NUMPAD_SUB = 0x6D,
	KeyCode_DEC = 0x6E,
	KeyCode_DIV = 0x6F,

	KeyCode_F1 = 0x70,
	KeyCode_F2 = 0x71,
	KeyCode_F3 = 0x72,
	KeyCode_F4 = 0x73,
	KeyCode_F5 = 0x74,
	KeyCode_F6 = 0x75,
	KeyCode_F7 = 0x76,
	KeyCode_F8 = 0x77,
	KeyCode_F9 = 0x78,
	KeyCode_F10 = 0x79,
	KeyCode_F11 = 0x7A,
	KeyCode_F12 = 0x7B,
	KeyCode_F13 = 0x7C,
	KeyCode_F14 = 0x7D,
	KeyCode_F15 = 0x7E,
	KeyCode_F16 = 0x7F,
	KeyCode_F17 = 0x80,
	KeyCode_F18 = 0x81,
	KeyCode_F19 = 0x82,
	KeyCode_F20 = 0x83,
	KeyCode_F21 = 0x84,
	KeyCode_F22 = 0x85,
	KeyCode_F23 = 0x86,
	KeyCode_F24 = 0x87,

	KeyCode_NLOCK = 0x88,
	KeyCode_SLOCK = 0x90,
	KeyCode_LSHIFT = 0xA0,
	KeyCode_RSHIFT = 0xA1,
	KeyCode_LCTRL = 0xA2,
	KeyCode_RCTRL = 0xA3,
	KeyCode_LALT = 0xA4,
	KeyCode_RALT = 0xA5
};
enum KeyType {
	KeyType_NON,
	KeyType_DOWN,
	KeyType_HOLD,
	KeyType_UP
};

// 키보드 현재 서로 다른 컴포에서 사용하면 다른 문제 있음
// 개선해야함
class Keyboard {
	friend class ConsoleEngine;
private:
	static bool* isHold;
	static KeyType* type;
	static void Update();
	static void Release();

public:
	static KeyType isKey(KeyCode code);
	
	// Keyboard Beta 기능들 ( 불완전함 )
	class Beta {
	public:
		static bool isKeyDown(KeyCode code);
		static bool isKeyHold(KeyCode code);
		static bool isKeyUp(KeyCode code);
	};
};

#endif // !___KEYBOARD___
