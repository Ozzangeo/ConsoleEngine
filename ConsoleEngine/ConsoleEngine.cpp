#include "ConsoleEngine.h"

using namespace std::chrono;

ConsoleEngine::ConsoleEngine() : m_FPS(60), isDone(false) {
	// ��Ÿ�� ����
	LONG style = GetWindowLong(GetConsoleWindow(), GWL_STYLE);
	SetWindowLong(GetConsoleWindow(), GWL_STYLE, style & ~WS_SIZEBOX);

	// ���콺 �Է� ���� ( ������ �𸣰����� �ȵ� )
	DWORD prevMode;
	GetConsoleMode(Handle::OUTPUT, &prevMode);
	SetConsoleMode(Handle::OUTPUT, prevMode & ~ENABLE_QUICK_EDIT_MODE);
}
void ConsoleEngine::Release() {
	Keyboard::Release();
	Graphic::Release();
	Debug::Release();
}