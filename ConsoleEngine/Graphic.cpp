#include "Graphic.h"

//#define DEBUG_MODE

#if defined(DEBUG_MODE)
#define PIXEL(index, color, z)	m_vScreen.at(index).Attributes = color;\
								m_vDepth.at(index) = z;
#define MEM_DELETE	m_vDepth.reserve(0);\
				m_vScreen.reserve(0);

#define SCREEN_SETTING(screen, depth)	m_vScreen.resize(0);\
										m_vDepth.resize(0);\
										m_vScreen.shrink_to_fit();\
										m_vDepth.shrink_to_fit();\
										m_vScreen.resize(length, screen);\
										m_vDepth.resize(length, depth);

#define RENDER(size, pos, rect)	WriteConsoleOutput(Handle::OUTPUT, m_vScreen.data(), size, pos, &rect);

#define CLEAR(z, back, depth)	for (int i = 0; i < z; i++) {\
									m_vScreen.at(i).Attributes = back;\
									m_vDepth.at(i) = depth;\
								}

#define FILL(index, color, z)	if (m_vDepth.at(index) < z) {\
									m_vScreen.at(index).Attributes = color;\
									m_Dvepth.at(index) = z;\
								}

#define SPRITE(index, spindex, z)	if (m_vDepth.at(index) < z) {\
										m_vDepth.at(index) = z;\
										m_vScreen.at(index).Attributes = sprite.sprite[spindex];\
									}
#else
#define PIXEL(index, color, z)	m_Screen[index].Attributes = color;\
								m_Depth[index] = z;

#define MEM_DELETE	if (m_Screen) { delete[] m_Screen; m_Screen = nullptr; }\
					if (m_Depth) { delete[] m_Depth; m_Depth = nullptr; }

#define SCREEN_SETTING(screen, depth)	if (m_Screen) { delete[] m_Screen; m_Screen = nullptr; }\
										if (m_Depth) { delete[] m_Depth; m_Depth = nullptr; }\
										m_Screen = new CHAR_INFO[length];\
										m_Depth = new int[length];\
										for (int i = 0; i < m_ScreenSize->z; i++) {\
											m_Screen[i] = screen;\
											m_Depth[i] = depth;\
										}

#define RENDER(size, pos, rect)	WriteConsoleOutput(Handle::OUTPUT, m_Screen, size, pos, &rect);

#define CLEAR(z, back, depth)	for (int i = 0; i < z; i++) {\
									m_Screen[i].Attributes = back;\
									m_Depth[i] = depth;\
								}

#define FILL(index, color, z)	if (m_Depth[index] < z) {\
									m_Screen[index].Attributes = color;\
									m_Depth[index] = z;\
								}

#define SPRITE(index, spindex, z)	if (m_Depth[index] < z) {\
										m_Depth[index] = z;\
										m_Screen[index].Attributes = sprite.sprite[spindex];\
									}
#endif

Graphic* Graphic::m_Instance = nullptr;
Graphic::Graphic() {
	CONSOLE_CURSOR_INFO cci = { 1, false };

	// 커서 보이기 여부
	SetConsoleCursorInfo(Handle::OUTPUT, &cci);
	SetScreenScale({ 1, 1 });

	m_ScreenSize = new Vector4i;
	m_HalfScreenSize = new Vector4f;
}
Graphic::~Graphic() {
	MEM_DELETE

	if (m_ScreenSize) { delete[] m_ScreenSize; m_ScreenSize = nullptr; }
	if (m_HalfScreenSize) { delete[] m_HalfScreenSize; m_HalfScreenSize = nullptr; }
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
	*m_ScreenSize = { Size.X, Size.Y, Size.X * Size.Y };
	*m_HalfScreenSize = m_ScreenSize->operator Vector4f() * 0.5f;

	if(CameraPos) { *CameraPos = { -m_HalfScreenSize->x, -m_HalfScreenSize->y, 0 }; }
	
	m_rect = { 0, 0, Size.X, Size.Y };
	m_size = { Size.X, Size.Y };

	size_t length = m_ScreenSize->z;

	SCREEN_SETTING(DEFAULT_SCREEN, DEFAULT_DEPTH)

	SetScreen();
}

void Graphic::Render() {
	RENDER(m_size, ZERO_POS, m_rect)
	CLEAR(m_ScreenSize->z, DEFAULT_BACKGROUND, DEFAULT_DEPTH)
}
void Graphic::SetScreen() {
	string System = "mode con: cols=" + to_string(m_ScreenSize->x) + " lines=" + to_string(m_ScreenSize->y);
	system(System.c_str());
}

inline void Graphic::DrawCircle(Vector4i& pos, Vector4i& pos2, EnumColor& color) {
	Pixel((pos.x + pos2.x), (pos.y + pos2.y), pos.z, color);
	Pixel((pos.x - pos2.x), (pos.y + pos2.y), pos.z, color);
	Pixel((pos.x + pos2.x), (pos.y - pos2.y), pos.z, color);
	Pixel((pos.x - pos2.x), (pos.y - pos2.y), pos.z, color);

	Pixel((pos.x + pos2.y), (pos.y + pos2.x), pos.z, color);
	Pixel((pos.x - pos2.y), (pos.y + pos2.x), pos.z, color);
	Pixel((pos.x + pos2.y), (pos.y - pos2.x), pos.z, color);
	Pixel((pos.x - pos2.y), (pos.y - pos2.x), pos.z, color);
}

// 언젠가 시간되면 Pixel 코드 정리하기
void Graphic::Pixel(const int& x, const int& y, const int& z, EnumColor& color) {
	Vector4i Pos = Vector4f{ (x - CameraPos->x), (y - CameraPos->y), static_cast<float>(z) };
	
	if (0 > Pos.y || m_ScreenSize->y <= Pos.y ||
		0 > Pos.x || m_ScreenSize->x <= Pos.x) {
		return;
	}
	int index = (Pos.y * m_ScreenSize->x) + Pos.x;

	if (m_Depth[index] < Pos.z) { PIXEL(index, color, Pos.z) }
}
void Graphic::Pixel(const float& x, const float& y, const float& z, EnumColor& color) {
	Vector4i Pos = Vector4f{ (x - CameraPos->x), (y - CameraPos->y), z };
	
	if (0 > Pos.y || m_ScreenSize->y <= Pos.y ||
		0 > Pos.x || m_ScreenSize->x <= Pos.x) {
		return;
	}
	int index = (Pos.y * m_ScreenSize->x) + Pos.x;

	if (m_Depth[index] < Pos.z) { PIXEL(index, color, Pos.z) }
}
void Graphic::Pixel(const Vector4i& pos, EnumColor& color) {
	Vector4i Pos = Vector4f{ (pos.x - CameraPos->x), (pos.y - CameraPos->y), static_cast<float>(pos.z) };
	
	if (0 > Pos.y || m_ScreenSize->y <= Pos.y ||
		0 > Pos.x || m_ScreenSize->x <= Pos.x) {
		return;
	}
	int index = (Pos.y * m_ScreenSize->x) + Pos.x;

	if (m_Depth[index] < Pos.z) { PIXEL(index, color, Pos.z) }
}
void Graphic::Pixel(const  Vector4f& pos, EnumColor& color) {
	Vector4i Pos = Vector4f{ (pos.x - CameraPos->x), (pos.y - CameraPos->y), pos.z };
	
	if (0 > Pos.y || m_ScreenSize->y <= Pos.y ||
		0 > Pos.x || m_ScreenSize->x <= Pos.x) {
		return;
	}
	int index = (Pos.y * m_ScreenSize->x) + Pos.x;

	if (m_Depth[index] < Pos.z) { PIXEL(index, color, Pos.z) }
}

void Graphic::Fill(const float& x, const float& y, const float& z, EnumColor color, const float& x2, const float y2) {
	Vector4f pos = { x, y, z };
	Vector4f pos2 = { x2, y2, z };

	if (pos.x > pos2.x) { Change<float>(&pos.x, &pos2.x); }
	if (pos.y > pos2.y) { Change<float>(&pos.y, &pos2.y); }

	int Height = 0;
	int index = 0;

	pos.x  -= CameraPos->x;
	pos2.x -= CameraPos->x;
	pos.y  -= CameraPos->y;
	pos2.y -= CameraPos->y;

	Vector4i posi = pos;
	Vector4i pos2i = pos2;

	for (int i = posi.y; i <= pos2i.y; i++) {
		if (i < 0) { continue; }
		if (i >= m_ScreenSize->y) { return; }
		Height = i * m_ScreenSize->x;

		for (int j = posi.x; j <= pos2i.x; j++) {
			if (j < 0) { continue; }
			if (j >= m_ScreenSize->x) { break; }

			index = Height + j;

			FILL(index, color, posi.z)
		}
	}
}
void Graphic::Fill(Vector4f& pos, Vector4f& pos2, EnumColor color) {
	if (pos.x > pos2.x) { Change<float>(&pos.x, &pos2.x); }
	if (pos.y > pos2.y) { Change<float>(&pos.y, &pos2.y); }

	int Height = 0;
	int index = 0;

	pos.x  -= CameraPos->x;
	pos2.x -= CameraPos->x;
	pos.y  -= CameraPos->y;
	pos2.y -= CameraPos->y;

	Vector4i posi = pos;
	Vector4i pos2i = pos2;

	for (int i = posi.y; i <= pos2i.y; i++) {
		if (i < 0)				{ continue; }
		if (i >= m_ScreenSize->y) { return; }
		Height = i * m_ScreenSize->x;

		for (int j = posi.x; j <= pos2i.x; j++) {
			if (j < 0)				{ continue; }
			if (j >= m_ScreenSize->x) { break; }

			index = Height + j;

			FILL(index, color, posi.z)
		}
	}
}
void Graphic::Line(const float& x, const float& y, const float& z, EnumColor color, const float& x2, const float& y2) {
	Vector4i posi  = Vector4f{ x , y , z };
	int counter = 0;

	COORD addr = { 0, 0 };
	Vector4i d = Vector4f{ (x2 - posi.x), (y2 - posi.y), 0 };

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

	Pixel(posi.x, posi.y, posi.z, color);
	if (d.x >= d.y) {
		for (int i = 0; i < d.x; i++) {
			posi.x += addr.X;

			counter += d.y;

			if (counter >= d.x) {
				posi.y += addr.Y;
				counter -= d.x;
			}
			Pixel(posi, color);
		}
	}
	else {
		for (INT i = 0; i < d.y; i++) {
			posi.y += addr.Y;

			counter += d.x;

			if (counter >= d.y) {
				posi.x += addr.X;
				counter -= d.y;
			}
			Pixel(posi, color);
		}
	}
}
void Graphic::Line(Vector4f& pos, Vector4f& pos2, EnumColor color) {
	Vector4i posi = pos;
	int counter = 0;

	COORD addr = { 0, 0 };
	Vector4i d = Vector4f{ (pos2.x - posi.x), (pos2.y - posi.y), 0 };

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

	Pixel(posi, color);
	if (d.x >= d.y) {
		for (int i = 0; i < d.x; i++) {
			posi.x += addr.X;

			counter += d.y;

			if (counter >= d.x) {
				posi.y += addr.Y;
				counter -= d.x;
			}
			Pixel(posi, color);
		}
	}
	else {
		for (int i = 0; i < d.y; i++) {
			posi.y += addr.Y;

			counter += d.x;

			if (counter >= d.y) {
				posi.x += addr.X;
				counter -= d.y;
			}
			Pixel(posi, color);
		}
	}
}
void Graphic::Circle(Vector4f& pos, EnumColor color, const int& radius, const int& curvature) {
	Vector4i posi = pos;

	Vector4i tp = { 0, radius, 3 - (2 * radius) };

	if (tp.y >= tp.x) { DrawCircle(posi, tp, color); }

	while (tp.y >= tp.x) {
		tp.x++;

		if (tp.z > 0) {
			tp.y--;
			tp.z += 4 * (tp.x - tp.y) + curvature;
		}
		else { tp.z += (4 * tp.x) + curvature; }

		DrawCircle(posi, tp, color);
	}
}
void Graphic::DrawSprite(Vector4f& pos, const Matrix4x4f& Trans, Sprite& sprite) {
	Vector4i Temp;
	int index = 0;
	int spindex = 0;
	
	Vector4f posf = pos;

	posf.x -= CameraPos->x + (sprite.size.X * 0.5f);
	posf.y -= CameraPos->y + (sprite.size.Y * 0.5f);

	Vector4i posi = posf;

	for (int i = 0; i < sprite.size.Y; i++) {
		Temp.y = posi.y + i;

		if (Temp.y < 0) { continue; }
		if (Temp.y >= m_ScreenSize->y) { return; }
		Temp.y = i * sprite.size.X;

		for (int j = 0; j < sprite.size.X; j++) {
			Temp.x = posi.x + j;
			spindex = Temp.y + j;

			if (Temp.x < 0 || sprite.sprite[spindex] == Color_NULL) { continue; }
			if (Temp.x >= m_ScreenSize->x) { break; }

			index = ((i + posi.y) * m_ScreenSize->x) + Temp.x;
			
			SPRITE(index, spindex, posi.z)
		}
	}
}

/*
Vector4i Temp;
	int index = 0;
	int spindex = 0;

	Vector4f posf = pos;

	posf.x -= CameraPos->x + (sprite.size.X * 0.5f);
	posf.y -= CameraPos->y + (sprite.size.Y * 0.5f);

	Vector4i posi = posf;

	for (int i = 0; i < sprite.size.Y; i++) {
		Temp.y = posi.y + i;

		if (Temp.y < 0) { continue; }
		if (Temp.y >= m_ScreenSize->y) { return; }
		Temp.y = i * sprite.size.X;

		for (int j = 0; j < sprite.size.X; j++) {
			Temp.x = posi.x + j;
			spindex = Temp.y + j;

			if (Temp.x < 0 || sprite.sprite[spindex] == Color_NULL) { continue; }
			if (Temp.x >= m_ScreenSize->x) { break; }

			index = ((i + posi.y) * m_ScreenSize->x) + Temp.x;

			SPRITE(index, spindex, posi.z)
		}
	}
*/