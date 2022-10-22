#include "Engine.h"

using namespace std::chrono;

bool EngineScript::Awake() { return true; }

Engine* Engine::m_Instance = nullptr;
bool Engine::isNotDone = true;
Engine::Engine() : m_RunScript(nullptr), m_FPS(60),
m_Console_Font_Infoex() {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(Camera2D::OUTPUT_HANDLE, &info);


	// 스타일 설정
	LONG style = GetWindowLong(GetConsoleWindow(), GWL_STYLE);
	SetWindowLong(GetConsoleWindow(), GWL_STYLE, style & ~WS_SIZEBOX);

	// 마우스 입력 금지
	DWORD prevMode;
	GetConsoleMode(Camera2D::INPUT_HANDLE, &prevMode);
	SetConsoleMode(Camera2D::INPUT_HANDLE, prevMode & ~ENABLE_QUICK_EDIT_MODE);

	// 콘솔 커서 숨기기
	CONSOLE_CURSOR_INFO cursorInfo = { 1, false };
	SetConsoleCursorInfo(Camera2D::OUTPUT_HANDLE, &cursorInfo);
}
Engine::Engine(const Engine& other) : m_RunScript(nullptr), m_FPS(60),
m_Console_Font_Infoex() {}
Engine::~Engine() {
	if (m_RunScript) { delete m_RunScript; m_RunScript = nullptr; }
}

void Engine::Fixing() {
	while (isNotDone) {
		SetCurrentConsoleFontEx(Camera2D::OUTPUT_HANDLE, FALSE, &m_Console_Font_Infoex);
		m_Camera->SetScreen();
	}
}
void Engine::FontSetting(Vector2<SHORT> FontSize) {
	FontSize.vround();
	m_Console_Font_Infoex.dwFontSize = { FontSize.x, FontSize.y };
	m_Console_Font_Infoex.cbSize = sizeof(m_Console_Font_Infoex);
	m_Console_Font_Infoex.nFont = 0;
	m_Console_Font_Infoex.FontFamily = FF_DONTCARE;
	m_Console_Font_Infoex.FontWeight = FW_NORMAL;
	wcscpy_s(m_Console_Font_Infoex.FaceName, TEXT("Raster Fonts"));

	SetCurrentConsoleFontEx(Camera2D::OUTPUT_HANDLE, FALSE, &m_Console_Font_Infoex);
	m_Camera->SetScreen();
}

Engine* Engine::GetInstance() {
	if (!m_Instance) { m_Instance = new Engine; }
	return m_Instance;
}
void Engine::Release() {
	if (m_Instance) { delete m_Instance; m_Instance = nullptr; }
}

