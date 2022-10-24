#include "Engine2D.h"

using namespace std::chrono;

Engine2D::Engine2D(Vector2<short> FontSize) : m_FPS(60), isDone(false) { Setting(FontSize); }

void Engine2D::FontSetting(Vector2<short> FontSize) {
	FontSize.vround();
	
	m_Console_Font_Infoex.dwFontSize = { FontSize.x, FontSize.y };
	SetCurrentConsoleFontEx(Handle::OUTPUT, FALSE, &m_Console_Font_Infoex);
}
void Engine2D::Release() {
	Keyboard::Release();
}