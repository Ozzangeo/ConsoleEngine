#include "ConsoleEngine.h"

using namespace std::chrono;

ConsoleEngine::ConsoleEngine() : m_FPS(60), isDone(false) {
	// 스타일 설정
	LONG style = GetWindowLong(GetConsoleWindow(), GWL_STYLE);
	SetWindowLong(GetConsoleWindow(), GWL_STYLE, style & ~WS_SIZEBOX);

	// 마우스 입력 금지 ( 왠지는 모르겠지만 안됨 )
	DWORD prevMode;
	GetConsoleMode(Handle::OUTPUT, &prevMode);
	SetConsoleMode(Handle::OUTPUT, prevMode & ~ENABLE_QUICK_EDIT_MODE);
}
void ConsoleEngine::Release() {
	Keyboard::Release();
	Graphic::Release();
	Debug::Release();
}