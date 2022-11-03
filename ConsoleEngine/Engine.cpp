#include "Engine.h"

using namespace std::chrono;

Engine::Engine() : m_FPS(60), isDone(false) {
	// ��Ÿ�� ����
	LONG style = GetWindowLong(GetConsoleWindow(), GWL_STYLE);
	SetWindowLong(GetConsoleWindow(), GWL_STYLE, style & ~WS_SIZEBOX);

	// ���콺 �Է� ���� ( ������ �𸣰����� �ȵ� )
	DWORD prevMode;
	GetConsoleMode(Handle::OUTPUT, &prevMode);
	SetConsoleMode(Handle::OUTPUT, prevMode & ~ENABLE_QUICK_EDIT_MODE);
}
void Engine::Release() {
	Keyboard::Release();
	Graphic::Release();
	Debug::Release();
}