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

inline void Graphic::DrawCircle(Vector4& pos, Vector4& pos2, EnumColor& color) {
	Pixel({ pos.x + pos2.x, pos.y + pos2.y, pos.z }, color);
	Pixel({ pos.x - pos2.x, pos.y + pos2.y, pos.z }, color);
	Pixel({ pos.x + pos2.x, pos.y - pos2.y, pos.z }, color);
	Pixel({ pos.x - pos2.x, pos.y - pos2.y, pos.z }, color);
		
	Pixel({ pos.x + pos2.y, pos.y + pos2.x, pos.z }, color);
	Pixel({ pos.x - pos2.y, pos.y + pos2.x, pos.z }, color);
	Pixel({ pos.x + pos2.y, pos.y - pos2.x, pos.z }, color);
	Pixel({ pos.x - pos2.y, pos.y - pos2.x, pos.z }, color);
}

void Graphic::Pixel(Vector4 pos, EnumColor color) {
	Vector4 Temp = { ((pos.x - CameraPos->x) + m_HalfScreenSize.x), ((pos.y - CameraPos->y) + m_HalfScreenSize.y), 0 };;

	// 뭔가 걸러내는데에서 문제있는듯
	if (0 > Temp.y || m_ScreenSize.y <= Temp.y ||
		0 > Temp.x || m_ScreenSize.x <= Temp.x) { return; }

	Temp.vround();
	int index = static_cast<int>((Temp.y * m_ScreenSize.x) + Temp.x);

	m_Screen[index].Attributes = color;
	m_Depth [index] = static_cast<int>(pos.z);
}
void Graphic::Fill(Vector4 pos, Vector4 pos2, EnumColor color) {
	pos.vround();
	pos2.vround();

	if (pos.x > pos2.x) { Change<float>(&pos.x, &pos2.x); }
	if (pos.y > pos2.y) { Change<float>(&pos.y, &pos2.y); }

	Vector4 Temp;
	int index = 0;

	pos.x  += m_HalfScreenSize.x - CameraPos->x;
	pos2.x += m_HalfScreenSize.x - CameraPos->x;
	pos.y  += m_HalfScreenSize.y - CameraPos->y;
	pos2.y += m_HalfScreenSize.y - CameraPos->y;

	for (int i = pos.GetY<int>(), id = pos2.GetY<int>(); i <= id; i++) {
		if (i < 0)				{ continue; }
		if (i >= m_ScreenSize.y) { return; }
		Temp.y = i * m_ScreenSize.x;

		for (int j = pos.GetX<int>(), jd = pos2.GetX<int>(); j <= jd; j++) {
			if (j < 0)				{ continue; }
			if (j >= m_ScreenSize.x) { break; }

			index = static_cast<int>(Temp.y + j);

			if (m_Depth[index] < pos.z) {
				m_Depth[index] = static_cast<int>(pos.z);
				m_Screen[index].Attributes = color;
			}
		}
	}
}
void Graphic::Line(Vector4 pos, Vector4 pos2, EnumColor color) {
	INT counter = 0;

	COORD addr = { 0, 0 };
	Vector4 d = { (pos2.x - pos.x), (pos2.y - pos.y), pos.z };

	if (d.x < 0) {
		addr.X = -1;
		d.x = -d.x;
	}
	else { addr.X = 1; }

	if (d.y < 0) {
		addr.Y = -1;
		d.y = -d.y;
	}
	else { addr.Y = 1; }

	if (d.x >= d.y) {
		for (INT i = 0; i < d.x; i++) {
			pos.x += addr.X;

			counter += d.y;

			if (counter >= d.x) {
				pos.y += addr.Y;
				counter -= d.x;
			}
			Pixel(pos, color);
		}
	}
	else {
		for (INT i = 0; i < d.y; i++) {
			pos.y += addr.Y;

			counter += d.x;

			if (counter >= d.y) {
				pos.x += addr.X;
				counter -= d.y;
			}
			Pixel(pos, color);
		}
	}
}
void Graphic::Circle(Vector4 pos, EnumColor color, INT radius, INT curvature) {
	Vector4 tp = { 0, static_cast<float>(radius), 0 };
	INT d = 3 - (2 * radius);

	if (tp.y >= tp.x) {
		DrawCircle(pos, tp, color);
	}

	while (tp.y >= tp.x) {
		tp.x++;

		if (d > 0) {
			tp.y--;
			d += 4 * (tp.x - tp.y) + curvature;
		}
		else { d += (4 * tp.x) + curvature; }

		DrawCircle(pos, tp, color);
	}
}
