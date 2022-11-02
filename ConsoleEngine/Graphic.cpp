#include "Graphic.h"

Graphic* Graphic::m_Instance = nullptr;
Graphic::Graphic() {
	CONSOLE_CURSOR_INFO cci = { 1, false };

	// 커서 보이기 여부
	SetConsoleCursorInfo(Handle::OUTPUT, &cci);
	SetScreenScale({ 1, 1 });
}
Graphic::~Graphic() {
	if (m_Screen) { delete[] m_Screen; m_Screen = nullptr; }
	if (m_Depth) { delete[] m_Depth; m_Depth = nullptr; }
}

Graphic& Graphic::GetInstance() {
	if (!m_Instance) { m_Instance = new Graphic; }
	return *m_Instance;
}
void Graphic::Release() {
	if (m_Instance) { delete m_Instance; }

	Debug::Log("[ Graphic ] : Release");
}

inline void Graphic::SetScreenScale(const COORD& Scale) {
	CONSOLE_FONT_INFOEX cfi{};
	cfi.dwFontSize = { Scale.X, Scale.Y };
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, TEXT("Raster Fonts"));

	SetCurrentConsoleFontEx(Handle::OUTPUT, FALSE, &cfi);
}
void Graphic::SetScreenSize(const COORD& Size) {
	m_ScreenSize = { static_cast<float>(Size.X), static_cast<float>(Size.Y), static_cast<float>(Size.X * Size.Y), 0 };
	m_HalfScreenSize = (m_ScreenSize * 0.5f).vround();

	m_rect = { 0, 0, Size.X, Size.Y };
	m_size = { Size.X, Size.Y };

	if (m_Screen) { delete[] m_Screen; m_Screen = nullptr; }
	if (m_Depth) { delete[] m_Depth; m_Depth = nullptr; }

	m_Screen = new CHAR_INFO[m_ScreenSize.GetZ<size_t>()];
	m_Depth = new int[m_ScreenSize.GetZ<size_t>()];

	// 초기화
	for (int i = 0; i < m_ScreenSize.z; i++) {
		m_Screen[i] = DEFAULT_SCREEN;
		m_Depth[i] = DEFAULT_DEPTH;
	}
	SetScreen();
}

void Graphic::Render() {
	/////////////////// Render ////////////////
	WriteConsoleOutput(Handle::OUTPUT, m_Screen, m_size, ZERO_POS, &m_rect);
	///////////////////////////////////////////

	/////////////////// Clear /////////////////
	for (int i = 0; i < m_ScreenSize.z; i++) {
		m_Screen[i].Attributes = DEFAULT_BACKGROUND;
		m_Depth[i] = DEFAULT_DEPTH;
	}
	///////////////////////////////////////////
}
void Graphic::SetScreen() {
	string System = "mode con: cols=" + to_string(m_ScreenSize.GetX<int>()) + " lines=" + to_string(m_ScreenSize.GetY<int>());
	system(System.c_str());
}

