#include "Engine.h"

using namespace std::chrono;

Engine::Engine() : m_FPS(60), isDone(false) {
	// 스타일 설정
	LONG style = GetWindowLong(GetConsoleWindow(), GWL_STYLE);
	SetWindowLong(GetConsoleWindow(), GWL_STYLE, style & ~WS_SIZEBOX);
}
void Engine::Release() {
	Keyboard::Release();
	Graphic::Release();
	Debug::Release();
}