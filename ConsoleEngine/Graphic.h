#ifndef ___GRAPHIC___
#define ___GRAPHIC___

#include "stdafx.h"
#include "Math.h"
#include "Matrix.h"
#include "Vector.h"
#include "Color.h"
#include "Debug.h"
#include "Sprite.h"

using namespace std;

namespace Components { class Camera; }

class Graphic {
	friend class ConsoleEngine;
	friend class Component;
	friend class Components::Camera;
private:
	Graphic();
	~Graphic();

	Vector3f* CameraPos;
	Vector3i* m_ScreenSize;
	Vector3f* m_HalfScreenSize;
	Vector3i* CameraRotate;

	COORD m_size;
	SMALL_RECT m_rect;

	CHAR_INFO* m_Screen;
	int* m_Depth;

	const WORD DEFAULT_BACKGROUND = Color_Black;
	const CHAR_INFO DEFAULT_SCREEN = { ' ', DEFAULT_BACKGROUND };
	const int DEFAULT_DEPTH = INT_MIN;
	const COORD ZERO_POS = { 0, 0 };

	static Graphic* m_Instance;

	void SetScreen();


	void Render();
	static void Release();
	static Graphic& GetInstance();

	inline void DrawCircle(const Vector3f& pos, const Vector3f& pos2, const Matrix4x4f& Trans, EnumColor& color);

	inline void Pixel(const   int& x, const   int& y, const   int& z, const Matrix4x4f& Trans, EnumColor& color);
	inline void Pixel(const float& x, const float& y, const float& z, const Matrix4x4f& Trans, EnumColor& color);
	inline void Pixel(const   int& x, const   int& y, const   int& z, EnumColor& color);
	inline void Pixel(const float& x, const float& y, const float& z, EnumColor& color);
	inline void Pixel(Vector3i& pos, EnumColor& color);
	inline void Pixel(Vector3f& pos, EnumColor& color);
	inline void Pixel(Vector3i& pos, EnumColor& color, bool* isFail);
	inline EnumColor GetPixel(Vector3i pos);

public:
	void Text(const Vector3i& pos, string text);

	// 기본 화면 조절 함수 ( 카메라 오브젝트 존재시, 가능한 카메라의 함수를 이용하길 추천 )
	inline void SetScreenScale(const COORD& Scale);
	void SetScreenSize(const COORD& Size);

	// 기본 Graphic 함수
	void Line		(Vector3i pos, const Vector3i& rotate, const Vector3f& scale, EnumColor color, Vector3i pos2 = 0);
	void Circle		(const Vector3f& pos, const Vector3i& rotate, const Vector3f& scale, EnumColor color, const float& radius, const int& curvature = 0);
	void DrawSprite	(const Vector3f& pos, const Vector3i& rotate, const Vector3f& scale, Sprite& sprite);
	void Mask		(Vector3i pos, EnumColor color);
	void Fill		(Vector3f pos, Vector3f pos2, EnumColor color);

	// Polygon Renderer 성능 최적화 용도
	void Line		(Vector3i pos, Vector3i pos2, const Matrix4x4f& Trans, EnumColor color);

	inline Matrix4x4f GetTranslate(const Vector3f& pos, const Vector3i& rotate, const Vector3f& scale);
	inline Matrix4x4f GetTranslate(const Vector3i& rotate, const Vector3f& scale);
	inline Matrix4x4f GetTranslate(const Vector3i& rotate);
	inline Matrix4x4f GetTranslate(const Vector3f& scale);
	inline Matrix4x4f GetTranslate();
};
inline void Graphic::DrawCircle(const Vector3f& pos, const Vector3f& pos2, const Matrix4x4f& Trans, EnumColor& color) {
	/*Pixel((pos.x + pos2.x), (pos.y + pos2.y), pos.z, Trans, color);
	Pixel((pos.x - pos2.x), (pos.y + pos2.y), pos.z, Trans, color);
	Pixel((pos.x + pos2.x), (pos.y - pos2.y), pos.z, Trans, color);
	Pixel((pos.x - pos2.x), (pos.y - pos2.y), pos.z, Trans, color);

	Pixel((pos.x + pos2.y), (pos.y + pos2.x), pos.z, Trans, color);
	Pixel((pos.x - pos2.y), (pos.y + pos2.x), pos.z, Trans, color);
	Pixel((pos.x + pos2.y), (pos.y - pos2.x), pos.z, Trans, color);
	Pixel((pos.x - pos2.y), (pos.y - pos2.x), pos.z, Trans, color);*/

	Pixel((pos.y + pos2.y), (-pos.x + pos2.x), pos.z, Trans, color);
	Pixel((pos.y + pos2.y), (-pos.x - pos2.x), pos.z, Trans, color);
	Pixel((pos.y - pos2.y), (-pos.x + pos2.x), pos.z, Trans, color);
	Pixel((pos.y - pos2.y), (-pos.x - pos2.x), pos.z, Trans, color);

	Pixel((pos.y + pos2.x), (-pos.x + pos2.y), pos.z, Trans, color);
	Pixel((pos.y + pos2.x), (-pos.x - pos2.y), pos.z, Trans, color);
	Pixel((pos.y - pos2.x), (-pos.x + pos2.y), pos.z, Trans, color);
	Pixel((pos.y - pos2.x), (-pos.x - pos2.y), pos.z, Trans, color);
}

/////////////////////////////////////////////////////////
#define PutPixel(Pos, color)							\
if (0 > Pos.y || m_ScreenSize->y <= Pos.y ||			\
	0 > Pos.x || m_ScreenSize->x <= Pos.x) { return; }	\
														\
int index = (Pos.y * m_ScreenSize->x) + Pos.x;			\
														\
if (m_Depth[index] < Pos.z) {							\
	m_Screen[index].Attributes = color;					\
	m_Depth[index] = Pos.z;								\
}														\
/////////////////////////////////////////////////////////

inline void Graphic::Pixel(const   int& x, const   int& y, const   int& z, const Matrix4x4f& Trans, EnumColor& color) {
	Vector3i Pos = Vector3i{ x, y, z } * Trans;

	PutPixel(Pos, color)
}
inline void Graphic::Pixel(const float& x, const float& y, const float& z, const Matrix4x4f& Trans, EnumColor& color) {
	Vector3i Pos = Vector3f{ x, y, z } * Trans;

	PutPixel(Pos, color)
}
inline void Graphic::Pixel(const   int& x, const   int& y, const int& z, EnumColor& color) {
	Vector3i Pos = Vector3i{ x, y, z };

	PutPixel(Pos, color)
}
inline void Graphic::Pixel(const float& x, const float& y, const float& z, EnumColor& color) {
	Vector3i Pos = Vector3f{ x, y, z };

	PutPixel(Pos, color)
}
inline void Graphic::Pixel(Vector3i& pos, EnumColor& color) {
	Vector3i Pos = pos;

	PutPixel(Pos, color)
}
inline void Graphic::Pixel(Vector3f& pos, EnumColor& color) {
	Vector3i Pos = pos;

	PutPixel(Pos, color)
}
inline void Graphic::Pixel(Vector3i& pos, EnumColor& color, bool* isFail) {
	Vector3i Pos = pos;

	if (0 > Pos.y || m_ScreenSize->y <= Pos.y ||
		0 > Pos.x || m_ScreenSize->x <= Pos.x) {
		*isFail = true;
		return;
	}

	int index = (Pos.y * m_ScreenSize->x) + Pos.x;

	if (m_Depth[index] < Pos.z) {
		m_Screen[index].Attributes = color;
		m_Depth[index] = Pos.z;
	}
}
inline EnumColor Graphic::GetPixel(Vector3i pos) {
	if (0 > pos.y || m_ScreenSize->y <= pos.y ||
		0 > pos.x || m_ScreenSize->x <= pos.x) { return Color_NULL; }

	return static_cast<EnumColor>(m_Screen[(pos.y * m_ScreenSize->x) + pos.x].Attributes);
}

inline Matrix4x4f Graphic::GetTranslate(const Vector3f& pos, const Vector3i& rotate, const Vector3f& scale) {
	return Math::GetScaleMatrix(scale) * Math::GetRotateMatrix(rotate) * Math::GetPosMatrix((*m_HalfScreenSize - *CameraPos) + pos);
}
inline Matrix4x4f Graphic::GetTranslate(const Vector3i& rotate, const Vector3f& scale) {
	return Math::GetScaleMatrix(scale) * Math::GetRotateMatrix(rotate) * Math::GetPosMatrix(*m_HalfScreenSize - *CameraPos);
}
inline Matrix4x4f Graphic::GetTranslate(const Vector3i& rotate) {
	return Math::GetRotateMatrix(rotate) * Math::GetPosMatrix(*m_HalfScreenSize - *CameraPos);
}
inline Matrix4x4f Graphic::GetTranslate(const Vector3f& scale) {
	return Math::GetScaleMatrix(scale) * Math::GetPosMatrix(*m_HalfScreenSize - *CameraPos);
}
inline Matrix4x4f Graphic::GetTranslate() {
	return Math::GetPosMatrix(*m_HalfScreenSize - *CameraPos);
}

#endif // !___GRAPHIC___
