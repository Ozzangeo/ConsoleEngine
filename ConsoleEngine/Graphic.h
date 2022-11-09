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

	Vector4f* CameraPos;
	Vector4i* m_ScreenSize;
	Vector4f* m_HalfScreenSize;
	Vector4i* CameraRotate;

	COORD m_size;
	SMALL_RECT m_rect;

	CHAR_INFO* m_Screen;
	int* m_Depth;

	const WORD DEFAULT_BACKGROUND = Color_Black;
	const CHAR_INFO DEFAULT_SCREEN = { ' ', DEFAULT_BACKGROUND };
	const int DEFAULT_DEPTH = -100;
	const COORD ZERO_POS = { 0, 0 };

	static Graphic* m_Instance;

	inline void SetScreenScale(const COORD& Scale);
	void SetScreenSize(const COORD& Size);
	void SetScreen();

	inline void DrawCircle(const Vector4f& pos, const Vector4f& pos2, const Matrix4x4f& Trans, EnumColor& color);

	void Render();
	static void Release();
	static Graphic& GetInstance();

	void Pixel(const   int& x, const   int& y, const   int& z, const Matrix4x4f& Trans, EnumColor& color);
	void Pixel(const float& x, const float& y, const float& z, const Matrix4x4f& Trans, EnumColor& color);
	void Pixel(const   int& x, const   int& y, const   int& z, EnumColor& color);
	void Pixel(const float& x, const float& y, const float& z, EnumColor& color);
	void Pixel(Vector4i& pos, EnumColor& color);
	void Pixel(Vector4f& pos, EnumColor& color);

public:
	void Fill(const float& x, const float& y, const float& z, EnumColor color, const float& x2 = 0, const float y2 = 0);
	void Fill(Vector4f& pos, Vector4f& pos2, EnumColor color);
	void Line		(const Vector4f& pos, const Vector4i& rotate, const Vector4f& scale, EnumColor color, Vector4f pos2 = 0);
	void Line		(Vector4i pos, Vector4i pos2, const Matrix4x4f& Trans, EnumColor color);
	void Circle		(const Vector4f& pos, const Vector4i& rotate, const Vector4f& scale, EnumColor color, const int& radius, const int& curvature = 0);
	void DrawSprite	(const Vector4f& pos, const Vector4i& rotate, const Vector4f& scale, Sprite& sprite);

	inline Matrix4x4f GetTranslate(const Vector4i& rotate, const Vector4f& scale);
};

#endif // !___GRAPHIC___
