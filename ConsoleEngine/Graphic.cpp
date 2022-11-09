#include "Graphic.h"

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
	if (m_Screen) { delete[] m_Screen; m_Screen = nullptr; }\
	if (m_Depth) { delete[] m_Depth; m_Depth = nullptr; }
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

	m_rect = { 0, 0, Size.X, Size.Y };
	m_size = { Size.X, Size.Y };

	size_t length = m_ScreenSize->z;

	if (m_Screen) { delete[] m_Screen; m_Screen = nullptr; }
	if (m_Depth) { delete[] m_Depth; m_Depth = nullptr; }
	m_Screen = new CHAR_INFO[length]; 
	m_Depth = new int[length]; 
	for (int i = 0; i < m_ScreenSize->z; i++) {
		m_Screen[i] = DEFAULT_SCREEN;
		m_Depth[i] = DEFAULT_DEPTH;
	}

	SetScreen();
}

void Graphic::Render() {
	WriteConsoleOutput(Handle::OUTPUT, m_Screen, m_size, ZERO_POS, &m_rect);
	for (int i = 0; i < m_ScreenSize->z; i++) {
		m_Screen[i].Attributes = DEFAULT_BACKGROUND;
		m_Depth[i] = DEFAULT_DEPTH;
	}
}
void Graphic::SetScreen() {
	string System = "mode con: cols=" + to_string(m_ScreenSize->x) + " lines=" + to_string(m_ScreenSize->y);
	system(System.c_str());
}

inline void Graphic::DrawCircle(const Vector4f& pos, const Vector4f& pos2, const Matrix4x4f& Trans, EnumColor& color) {
	Pixel((pos.x + pos2.x), (pos.y + pos2.y), pos.z, Trans, color);
	Pixel((pos.x - pos2.x), (pos.y + pos2.y), pos.z, Trans, color);
	Pixel((pos.x + pos2.x), (pos.y - pos2.y), pos.z, Trans, color);
	Pixel((pos.x - pos2.x), (pos.y - pos2.y), pos.z, Trans, color);

	Pixel((pos.x + pos2.y), (pos.y + pos2.x), pos.z, Trans, color);
	Pixel((pos.x - pos2.y), (pos.y + pos2.x), pos.z, Trans, color);
	Pixel((pos.x + pos2.y), (pos.y - pos2.x), pos.z, Trans, color);
	Pixel((pos.x - pos2.y), (pos.y - pos2.x), pos.z, Trans, color);
}

// 언젠가 시간되면 Pixel 코드 정리하기
void Graphic::Pixel(const   int& x, const   int& y, const   int& z, const Matrix4x4f& Trans, EnumColor& color) {
	Vector4i Pos = Vector4i{ x, y, z } * Trans;
	
	if (0 > Pos.y || m_ScreenSize->y <= Pos.y ||
		0 > Pos.x || m_ScreenSize->x <= Pos.x) { return; }
	int index = (Pos.y * m_ScreenSize->x) + Pos.x;

	if (m_Depth[index] < Pos.z) {
		m_Screen[index].Attributes = color;
		m_Depth[index] = Pos.z;
	}
}
void Graphic::Pixel(const float& x, const float& y, const float& z, const Matrix4x4f& Trans, EnumColor& color) {
	Vector4i Pos = Vector4f{ x, y, z } * Trans;

	if (0 > Pos.y || m_ScreenSize->y <= Pos.y ||
		0 > Pos.x || m_ScreenSize->x <= Pos.x) { return; }
	int index = (Pos.y * m_ScreenSize->x) + Pos.x;

	if (m_Depth[index] < Pos.z) {
		m_Screen[index].Attributes = color;
		m_Depth[index] = Pos.z;
	}
}
void Graphic::Pixel(const   int& x, const   int& y,   const int& z, EnumColor& color) {
	Vector4i Pos = Vector4i{ x, y, z };

	if (0 > Pos.y || m_ScreenSize->y <= Pos.y ||
		0 > Pos.x || m_ScreenSize->x <= Pos.x) {
		return;
	}
	int index = (Pos.y * m_ScreenSize->x) + Pos.x;

	if (m_Depth[index] < Pos.z) {
		m_Screen[index].Attributes = color;
		m_Depth[index] = Pos.z;
	}
}
void Graphic::Pixel(const float& x, const float& y, const float& z, EnumColor& color) {
	Vector4i Pos = Vector4f{ x, y, z };

	if (0 > Pos.y || m_ScreenSize->y <= Pos.y ||
		0 > Pos.x || m_ScreenSize->x <= Pos.x) {
		return;
	}
	int index = (Pos.y * m_ScreenSize->x) + Pos.x;

	if (m_Depth[index] < Pos.z) {
		m_Screen[index].Attributes = color;
		m_Depth[index] = Pos.z;
	}
}
void Graphic::Pixel(Vector4i& pos, EnumColor& color) {
	Vector4i Pos = pos;
	
	if (0 > Pos.y || m_ScreenSize->y <= Pos.y ||
		0 > Pos.x || m_ScreenSize->x <= Pos.x) { return; }
	int index = (Pos.y * m_ScreenSize->x) + Pos.x;

	if (m_Depth[index] < Pos.z) {
		m_Screen[index].Attributes = color;
		m_Depth[index] = Pos.z;
	}
}
void Graphic::Pixel(Vector4f& pos, EnumColor& color) {
	Vector4i Pos = pos;

	if (0 > Pos.y || m_ScreenSize->y <= Pos.y ||
		0 > Pos.x || m_ScreenSize->x <= Pos.x) { return; }
	int index = (Pos.y * m_ScreenSize->x) + Pos.x;

	if (m_Depth[index] < Pos.z) {
		m_Screen[index].Attributes = color;
		m_Depth[index] = Pos.z;
	}
}

void Graphic::Fill(const float& x, const float& y, const float& z, EnumColor color, const float& x2, const float y2) {
	Vector4f pos = { x, y, z };
	Vector4f pos2 = { x2, y2, z };

	if (pos.x > pos2.x) { Swap<float>(&pos.x, &pos2.x); }
	if (pos.y > pos2.y) { Swap<float>(&pos.y, &pos2.y); }

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

			if (m_Depth[index] < posi.z) {
					m_Screen[index].Attributes = color;
					m_Depth[index] = posi.z;
			}
		}
	}
}
void Graphic::Fill(Vector4f& pos, Vector4f& pos2, EnumColor color) {
	if (pos.x > pos2.x) { Swap<float>(&pos.x, &pos2.x); }
	if (pos.y > pos2.y) { Swap<float>(&pos.y, &pos2.y); }

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

			if (m_Depth[index] < posi.z) {
				m_Screen[index].Attributes = color;
				m_Depth[index] = posi.z;
			}
		}
	}
}

// https://m.blog.naver.com/kch8246/220823909990
void Graphic::Line(const Vector4f& pos, const Vector4i& rotate, const Vector4f& scale, EnumColor color, Vector4f pos2) {
	Matrix4x4f Trans = GetTranslate(rotate, scale);
	int counter = 0;

	COORD addr = { 0, 0 };

	Vector4f posi = pos * Trans;
			 pos2 = pos2 * Trans;
	Vector4i d = Vector4f{ (pos2.x - posi.x), (pos2.x - posi.y), 0 };

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
void Graphic::Line(Vector4i pos, Vector4i pos2, const Matrix4x4f& Trans, EnumColor color) {
	pos = pos * Trans;
	pos2 = pos2 * Trans;
	
	Vector4i len = Vector4i{ pos2.x - pos.x, pos2.y - pos.y, 0 };
	bool isHeight = false;
	
	if (abs(len.y) > abs(len.x)) {
		Swap<int>(&len.x, &len.y);
		isHeight = true;
	}

	if (len.x == 0) { len.z = 0; }
	else { len.z = (len.y << 16) / len.x; }

	if (isHeight) {
		if (len.x > 0) {
			len.x += pos.y;
			// 0x8000 = 0.5
			for (int i = 0x8000 + (pos.x << 16); pos.y <= len.x; pos.y++) {
				Pixel(i >> 16, pos.y, pos.z, color);
				i += len.z;
			}
			return;
		}

		len.x += pos.y;
		for (int i = 0x8000 + (pos.x << 16); pos.y >= len.x; pos.y--) {
			Pixel(i >> 16, pos.y, pos.z, color);
			i -= len.z;
		}
		return;
	}

	if (len.x > 0) {
		len.x += pos.x;
		for (int i = 0x8000 + (pos.y << 16); pos.x <= len.x; pos.x++) {
			Pixel(pos.x, i >> 16, pos.z, color);
			i += len.z;
		}
		return;
	}

	len.x += pos.x;
	for (int i = 0x8000 + (pos.y << 16); pos.x >= len.x; pos.x--) {
		Pixel(pos.x, i >> 16, pos.z, color);
		i -= len.z;
	}
}
void Graphic::Circle(const Vector4f& pos, const Vector4i& rotate, const Vector4f& scale, EnumColor color, const int& radius, const int& curvature) {
	Matrix4x4f Trans = GetTranslate(rotate, scale);

	Vector4i TempPos = Vector4i{ 0, radius, 3 - (2 * radius) };

	if (TempPos.y >= TempPos.x) { DrawCircle(pos, TempPos, Trans, color); }

	while (TempPos.y >= TempPos.x) {
		TempPos.x++;

		if (TempPos.z > 0) {
			TempPos.y--;
			TempPos.z += 4 * (TempPos.x - TempPos.y) + curvature;
		}
		else { TempPos.z += (4 * TempPos.x) + curvature; }

		DrawCircle(pos, TempPos, Trans, color);
	}
}
void Graphic::DrawSprite(const Vector4f& pos, const Vector4i& rotate, const Vector4f& scale, Sprite& sprite) {
	Matrix4x4f Trans = GetTranslate(rotate, scale);
	Vector4f Pos = pos;

	Pos.x -= (sprite.size.X * 0.5f);
	Pos.y -= (sprite.size.Y * 0.5f);

	int Height = 0;
	int SpriteIndex = 0;

	for (int i = 0; i < sprite.size.Y; i++) {
		Height = i * sprite.size.X;

		for (int j = 0; j < sprite.size.X; j++) {
			SpriteIndex = Height + j;

			if (sprite.sprite[SpriteIndex] == Color_NULL) { continue; }
			else { Pixel(Pos.x + i, Pos.y + j, Pos.z, Trans, sprite.sprite[SpriteIndex]); }
		}
	}
}

inline Matrix4x4f Graphic::GetTranslate(const Vector4i& rotate, const Vector4f& scale) {
	return Math::GetScaleMatrix(scale) * Math::GetRotateMatrix(rotate) * Math::GetPosMatrix(*m_HalfScreenSize - *CameraPos);
}
