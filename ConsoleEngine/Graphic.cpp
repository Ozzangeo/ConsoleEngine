#include "Graphic.h"

Graphic* Graphic::m_Instance = nullptr;
Graphic::Graphic() {
	CONSOLE_CURSOR_INFO cci = { 1, false };

	// 커서 보이기 여부
	SetConsoleCursorInfo(Handle::OUTPUT, &cci);
	SetScreenScale({ 1, 1 });
}
Graphic::~Graphic() {
#if defined(DEBUG_MODE)
	m_vDepth.resize(0);
	m_vScreen.resize(0);
#else
	if (m_Screen) { delete[] m_Screen; m_Screen = nullptr; }
	if (m_Depth) { delete[] m_Depth; m_Depth = nullptr; }
#endif
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

	size_t length = m_ScreenSize.GetZ<size_t>();

#if defined(DEBUG_MODE)
	m_vScreen.resize(0);
	m_vDepth.resize(0);

	m_vScreen.shrink_to_fit();
	m_vDepth.shrink_to_fit();

	m_vScreen.resize(length, DEFAULT_SCREEN);
	m_vDepth.resize(length, DEFAULT_DEPTH);
#else
	if (m_Screen) { delete[] m_Screen; m_Screen = nullptr; }
	if (m_Depth) { delete[] m_Depth; m_Depth = nullptr; }

	m_Screen = new CHAR_INFO[length];
	m_Depth = new int[length];

	// 초기화
	for (int i = 0; i < m_ScreenSize.z; i++) {
		m_Screen[i] = DEFAULT_SCREEN;
		m_Depth[i] = DEFAULT_DEPTH;
	}
#endif
	SetScreen();
}

void Graphic::Render() {
#if defined(DEBUG_MODE)
	/////////////////// Render ////////////////
	WriteConsoleOutput(Handle::OUTPUT, m_vScreen.data(), m_size, ZERO_POS, &m_rect);
	///////////////////////////////////////////

	/////////////////// Clear /////////////////
	for (int i = 0; i < m_ScreenSize.z; i++) {
		m_vScreen[i].Attributes = DEFAULT_BACKGROUND;
		m_vDepth[i] = DEFAULT_DEPTH;
	}
	///////////////////////////////////////////
#else
	/////////////////// Render ////////////////
	WriteConsoleOutput(Handle::OUTPUT, m_Screen, m_size, ZERO_POS, &m_rect);
	///////////////////////////////////////////

	/////////////////// Clear /////////////////
	for (int i = 0; i < m_ScreenSize.z; i++) {
		m_Screen[i].Attributes = DEFAULT_BACKGROUND;
		m_Depth[i] = DEFAULT_DEPTH;
	}
	///////////////////////////////////////////
#endif
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

	Temp.vround();
	if (0 > Temp.y || m_ScreenSize.y <= Temp.y ||
		0 > Temp.x || m_ScreenSize.x <= Temp.x) { return; }

	int index = static_cast<int>((Temp.y * m_ScreenSize.x) + Temp.x);
#if defined(DEBUG_MODE)
	m_vScreen.at(index).Attributes = color;
	m_vDepth .at(index) = static_cast<int>(pos.z);
#else
	m_Screen[index].Attributes = color;
	m_Depth [index] = static_cast<int>(pos.z);
#endif
}
void Graphic::Pixel(Vector4 pos, float depth, EnumColor color) {
	Vector4 Temp = { ((pos.x - CameraPos->x) + m_HalfScreenSize.x), ((pos.y - CameraPos->y) + m_HalfScreenSize.y), 0 };;

	Temp.vround();
	if (0 > Temp.y || m_ScreenSize.y <= Temp.y ||
		0 > Temp.x || m_ScreenSize.x <= Temp.x) {
		return;
	}

	int index = static_cast<int>((Temp.y * m_ScreenSize.x) + Temp.x);
#if defined(DEBUG_MODE)
	m_vScreen.at(index).Attributes = color;
	m_vDepth.at(index) = static_cast<int>(depth);
#else
	m_Screen[index].Attributes = color;
	m_Depth[index] = static_cast<int>(depth);
#endif
}
void Graphic::Fill(Vector4 pos, Vector4 pos2, EnumColor color) {
	if (pos.x > pos2.x) { Change<float>(&pos.x, &pos2.x); }
	if (pos.y > pos2.y) { Change<float>(&pos.y, &pos2.y); }

	Vector4 Temp;
	int index = 0;

	pos.x  += m_HalfScreenSize.x - CameraPos->x;
	pos2.x += m_HalfScreenSize.x - CameraPos->x;
	pos.y  += m_HalfScreenSize.y - CameraPos->y;
	pos2.y += m_HalfScreenSize.y - CameraPos->y;

	pos.vround();
	pos2.vround();

	for (int i = pos.GetY<int>(), id = pos2.GetY<int>(); i <= id; i++) {
		if (i < 0)				{ continue; }
		if (i >= m_ScreenSize.y) { return; }
		Temp.y = i * m_ScreenSize.x;

		for (int j = pos.GetX<int>(), jd = pos2.GetX<int>(); j <= jd; j++) {
			if (j < 0)				{ continue; }
			if (j >= m_ScreenSize.x) { break; }

			index = static_cast<int>(Temp.y + j);

#if defined(DEBUG_MODE)
			if (m_vDepth[index] < pos.z) {
				m_vDepth[index] = static_cast<int>(pos.z);
				m_vScreen[index].Attributes = color;
			}
#else
			if (m_Depth[index] < pos.z) {
				m_Depth[index] = static_cast<int>(pos.z);
				m_Screen[index].Attributes = color;
			}
#endif
		}
	}
}
void Graphic::Line(Vector4 pos, Vector4 pos2, EnumColor color) {
	pos.vround();
	pos2.vround();
	
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

	Pixel(pos, color);
	if (d.x >= d.y) {
		for (INT i = 0; i < d.x; i++) {
			pos.x += addr.X;

			counter += static_cast<int>(d.y);

			if (counter >= d.x) {
				pos.y += addr.Y;
				counter -= static_cast<int>(d.x);
			}
			Pixel(pos, color);
		}
	}
	else {
		for (INT i = 0; i < d.y; i++) {
			pos.y += addr.Y;

			counter += static_cast<int>(d.x);

			if (counter >= d.y) {
				pos.x += addr.X;
				counter -= static_cast<int>(d.y);
			}
			Pixel(pos, color);
		}
	}
}
void Graphic::Line(Vector4 pos, Vector4 pos2, float depth, EnumColor color) {
	pos.vround();
	pos2.vround();

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

	Pixel(pos, depth, color);
	if (d.x >= d.y) {
		for (INT i = 0; i < d.x; i++) {
			pos.x += addr.X;

			counter += static_cast<int>(d.y);

			if (counter >= d.x) {
				pos.y += addr.Y;
				counter -= static_cast<int>(d.x);
			}
			Pixel(pos, depth, color);
		}
	}
	else {
		for (INT i = 0; i < d.y; i++) {
			pos.y += addr.Y;

			counter += static_cast<int>(d.x);

			if (counter >= d.y) {
				pos.x += addr.X;
				counter -= static_cast<int>(d.y);
			}
			Pixel(pos, depth, color);
		}
	}
}
void Graphic::Circle(Vector4 pos, EnumColor color, INT radius, INT curvature) {
	pos.vround();

	Vector4 tp = { 0, static_cast<float>(radius), 0 };
	INT d = 3 - (2 * radius);

	if (tp.y >= tp.x) {
		DrawCircle(pos, tp, color);
	}

	while (tp.y >= tp.x) {
		tp.x++;

		if (d > 0) {
			tp.y--;
			d += static_cast<int>(4 * (tp.x - tp.y) + curvature);
		}
		else { d += static_cast<int>((4 * tp.x) + curvature); }

		DrawCircle(pos, tp, color);
	}
}

void Graphic::NotSafePixel(const Vector4& pos, const EnumColor& color) {
	int index = static_cast<int>((((pos.y - CameraPos->y) + m_HalfScreenSize.y) * m_ScreenSize.x) + ((pos.x - CameraPos->x) + m_HalfScreenSize.x));

#if defined(DEBUG_MODE)
	m_vScreen.at(index).Attributes = color;
	m_vDepth.at(index) = static_cast<int>(pos.z);
#else
	m_Screen[index].Attributes = color;
	m_Depth[index] = static_cast<int>(pos.z);
#endif
}
void Graphic::NotSafeFill(Vector4 pos, Vector4 pos2, EnumColor color) {
	Vector4 Temp;
	int index = 0;

	pos.x += m_HalfScreenSize.x - CameraPos->x;
	pos2.x += m_HalfScreenSize.x - CameraPos->x;
	pos.y += m_HalfScreenSize.y - CameraPos->y;
	pos2.y += m_HalfScreenSize.y - CameraPos->y;

	pos.vround();
	pos2.vround();

	for (int i = pos.GetY<int>(), id = pos2.GetY<int>(); i <= id; i++) {
		if (i < 0) { continue; }
		if (i >= m_ScreenSize.y) { return; }
		Temp.y = i * m_ScreenSize.x;

		for (int j = pos.GetX<int>(), jd = pos2.GetX<int>(); j <= jd; j++) {
			if (j < 0) { continue; }
			if (j >= m_ScreenSize.x) { break; }

			index = static_cast<int>(Temp.y + j);

#if defined(DEBUG_MODE)
			if (m_vDepth[index] < pos.z) {
				m_vDepth[index] = static_cast<int>(pos.z);
				m_vScreen[index].Attributes = color;
			}
#else
			if (m_Depth[index] < pos.z) {
				m_Depth[index] = static_cast<int>(pos.z);
				m_Screen[index].Attributes = color;
			}
#endif
		}
	}
}