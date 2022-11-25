#include "Graphic.h"

Graphic* Graphic::m_Instance = nullptr;
Graphic::Graphic() {
	CONSOLE_CURSOR_INFO cci = { 1, false };

	// 커서 보이기 여부
	SetConsoleCursorInfo(Handle::OUTPUT, &cci);
	SetScreenScale({ 1, 1 });

	m_ScreenSize = new Vector3i;
	m_HalfScreenSize = new Vector3f;
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
void Graphic::Text(const Vector3i& pos, string text) {
	int plus = 0;
	int Index = static_cast<int>(((pos.y + m_HalfScreenSize->y) * m_ScreenSize->x) + pos.x + m_HalfScreenSize->x);
	for (int i = 0, size = static_cast<int>(text.length()); i < size; i++) {
		m_Screen[Index + i + plus].Char.AsciiChar = text[i];
		if (text[i] >= 128) { plus++; }

		m_Screen[Index + i].Attributes = 15;
	}
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
	*m_HalfScreenSize = m_ScreenSize->operator Vector3f() * 0.5f;

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

// Extremely Fast Line Algorithm
void Graphic::Line(Vector3i pos, const Vector3i& rotate, const Vector3f& scale, EnumColor color, Vector3i pos2) {
	Matrix4x4f Trans = GetTranslate(rotate, scale);

	pos  = pos  * Trans;
	pos2 = pos2 * Trans;

	Vector3i len = { pos2.x - pos.x, pos2.y - pos.y, 0 };
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
void Graphic::Line(Vector3i pos, Vector3i pos2, const Matrix4x4f& Trans, EnumColor color) {
	pos  = pos  * Trans;
	pos2 = pos2 * Trans;
	
	Vector3i len = Vector3i{ pos2.x - pos.x, pos2.y - pos.y, 0 };
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
// Bresenham's Midpoint Circle Algorithm
void Graphic::Circle(const Vector3f& pos, const Vector3i& rotate, const Vector3f& scale, EnumColor color, const float& radius, const int& curvature) {
	Matrix4x4f Trans = GetTranslate(rotate);
	float radiusf = radius * scale.z;
	
	Vector3i TempPos = Vector3f{ 0, radiusf, 3 - (2 * radiusf) };

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
// No Algorithm
void Graphic::DrawSprite(const Vector3f& pos, const Vector3i& rotate, const Vector3f& scale, Sprite& sprite) {
	Matrix4x4f Trans = GetTranslate(rotate, scale);
	Vector3f Pos = pos;

	Pos.x -= (sprite.size.X * 0.5f);
	Pos.y -= (sprite.size.Y * 0.5f);
	Pos = Pos.round();

	int Height = 0;
	int SpriteIndex = 0;

	for (int i = 0; i < sprite.size.Y; i++) {
		Height = i * sprite.size.X;

		for (int j = 0; j < sprite.size.X; j++) {
			SpriteIndex = Height + j;

			if (sprite.sprite[SpriteIndex] == Color_NULL) { continue; }
			else { Pixel(Pos.x + j, Pos.y + i, Pos.z, Trans, sprite.sprite[SpriteIndex]); }
		}
	}
}
void Graphic::Fill(Vector3f pos, Vector3f pos2, EnumColor color) {
	Vector3f Trans = (*m_HalfScreenSize - *CameraPos);
	int Height = 0;
	int index = 0;

	Vector3i posi = pos + Trans;
	Vector3i pos2i = pos2 + Trans;

	if (posi.x > pos2i.x) {
		if (posi.y > pos2i.y) {
			for (int i = pos2i.y; i <= posi.y; i++) {
				if (i < 0) { continue; }
				if (i >= m_ScreenSize->y) { return; }
				Height = i * m_ScreenSize->x;

				for (int j = pos2i.x; j <= posi.x; j++) {
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
		else {
			for (int i = posi.y; i <= pos2i.y; i++) {
				if (i < 0) { continue; }
				if (i >= m_ScreenSize->y) { return; }
				Height = i * m_ScreenSize->x;

				for (int j = pos2i.x; j <= posi.x; j++) {
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
	}
	else {
		if (posi.y > pos2i.y) {
			for (int i = pos2i.y; i <= posi.y; i++) {
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
		else {
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
	}
}
void Graphic::Mask(Vector3i pos, EnumColor color) {
	bool isFail = false;
	EnumColor get = GetPixel(pos);
	if (get != color && get != Color_NULL) {
		Pixel(pos, color, &isFail);
		if (isFail) { return; }
	} else { return; }
	
	Mask(Vector3i(pos.x - 1, pos.y, pos.z, 1), color);
	Mask(Vector3i(pos.x + 1, pos.y, pos.z, 1), color);
	Mask(Vector3i(pos.x, pos.y - 1, pos.z, 1), color);
	Mask(Vector3i(pos.x, pos.y + 1, pos.z, 1), color);
}