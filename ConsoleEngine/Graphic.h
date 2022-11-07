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

	inline void DrawCircle(Vector4i& pos, Vector4i& pos2, EnumColor& color);

	void Render();
	static void Release();
	static Graphic& GetInstance();

public:
	void Pixel(const   int& x, const   int& y, const   int& z, EnumColor& color);
	void Pixel(const float& x, const float& y, const float& z, EnumColor& color);
	void Pixel(const float& x, const float& y, const float& z, EnumColor& color, Matrix4x4f& Trans);
	void Pixel(const Vector4i& pos, EnumColor& color);
	void Pixel(const Vector4f& pos, EnumColor& color);

	void Fill(const float& x, const float& y, const float& z, EnumColor color, const float& x2 = 0, const float y2 = 0);
	void Fill(Vector4f& pos, Vector4f& pos2, EnumColor color);
	void Line(const float& x, const float& y, const float& z, EnumColor color, const float& x2 = 0, const float& y2 = 0);
	void Line(Vector4f& pos, Vector4f& pos2, EnumColor color);
	void Circle(Vector4f& pos, EnumColor color, const int& radius, const int& curvature);
	void DrawSprite(Vector4f& pos, const Matrix4x4f& Trans, Sprite& sprite);
};

#endif // !___GRAPHIC___
