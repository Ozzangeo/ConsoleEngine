#include "Graphic.h"

Graphic* Graphic::m_Instance = nullptr;
void Graphic::ScreenFlipping() {
	SetConsoleActiveScreenBuffer(m_Screen[m_Index]);
	m_Index = !m_Index;
}

Graphic::Graphic() : BufferSize(2), ZeroPos({ 0, 0 }) {
	m_Screen = new HANDLE[BufferSize];
	CONSOLE_CURSOR_INFO cci = { 1, false };
	DWORD prevMode;

	m_Index = 0;

	for (int i = 0; i < 2; i++) {
		m_Screen[i] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		
		// 커서 보이기 여부
		SetConsoleCursorInfo(m_Screen[i], &cci);

		// 마우스 입력 금지
		GetConsoleMode(m_Screen[i], &prevMode);
		SetConsoleMode(m_Screen[i], prevMode & ~ENABLE_QUICK_EDIT_MODE);
	}
	SetFontSize({ 1, 1 });
}
Graphic::~Graphic() {
	if (m_Screen) { delete[] m_Screen; }
}

Graphic& Graphic::GetInstance() {
	if (!m_Instance) { m_Instance = new Graphic; }
	return *m_Instance;
}
void Graphic::Release() {
	if (m_Instance) { delete m_Instance; }
	Debug::Log("[ Graphic ] : Release");
}

void Graphic::SetFontSize(Vector2<short> FontSize) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.dwFontSize = { FontSize.x, FontSize.y };
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, TEXT("Raster Fonts"));

	for (int i = 0; i < 2; i++) {
		SetCurrentConsoleFontEx(m_Screen[i], FALSE, &cfi);
	}
}

void Graphic::Merge(CHAR_INFO* Screen, Vector2<float> Pos, Vector2<int> ScreenSize) {
	Pos = Pos + m_HalfFieldSize.toVector2<float>() - (ScreenSize.toVector2<float>() * 0.5f);
	Pos.vround();

	Vector3<float> Temp = { 0, 0, static_cast<float>(-m_CANVAS) };
	int pos = 0;
	for (int d = 0; d < m_FieldSize.z; d++) {
		Temp.z += static_cast<float>(m_CANVAS);

		for (int y = 0, i = 0; y < ScreenSize.y; y++) {
			Temp.y = (y + Pos.y) * m_FieldSize.x;

			for (int x = 0; x < ScreenSize.x; x++, i++) {
				Temp.x = Pos.x + x;

				if (0 > Temp.x || Temp.x >= m_FieldSize.x) { continue; }
				pos = static_cast<int>(Temp.y + Temp.x);

				if (0 <= pos && pos < m_CANVAS) {
					pos += static_cast<int>(Temp.z);
					if (m_Layer[pos].Color != Color_NULL) { Screen[i].Attributes = m_Layer[pos].Color; }
				}
			}
		}
	}
}
void Graphic::Render(CHAR_INFO* Screen, const Vector2<int>& ScreenSize, const COORD& size, SMALL_RECT& rect) {
	WriteConsoleOutput(m_Screen[m_Index], Screen, size, ZeroPos, &rect);

	ScreenFlipping();
}
