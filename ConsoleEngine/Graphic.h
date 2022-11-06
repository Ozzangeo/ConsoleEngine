#ifndef ___GRAPHIC___
#define ___GRAPHIC___

#include "stdafx.h"
#include "Vector.h"
#include "Color.h"
#include "Debug.h"
#include "Sprite.h"

using namespace std;

namespace DefaultComponents { class Camera; }

class Graphic {
	friend class ConsoleEngine;
	friend class Component;
	friend class DefaultComponents::Camera;
private:
	Graphic();
	~Graphic();

	Vector4f* CameraPos;
	Vector4i m_ScreenSize;
	Vector4f m_HalfScreenSize;

	COORD m_size;
	SMALL_RECT m_rect;

#if defined(DEBUG_MODE)
	vector<CHAR_INFO> m_vScreen;
	vector<int> m_vDepth;
#else
	CHAR_INFO* m_Screen;
	int* m_Depth;
#endif
	const WORD DEFAULT_BACKGROUND = Color_Black;
	const CHAR_INFO DEFAULT_SCREEN = { ' ', DEFAULT_BACKGROUND };
	const int DEFAULT_DEPTH = -100;
	const COORD ZERO_POS = { 0, 0 };

	static Graphic* m_Instance;

	inline void SetScreenScale(const COORD& Scale);
	void SetScreenSize(const COORD& Size);
	void SetScreen();

	inline void DrawCircle(Vector4f& pos, Vector4f& pos2, EnumColor& color);

	void Render();
	static void Release();
	static Graphic& GetInstance();

public:
	void Pixel(Vector4f& pos, EnumColor& color);
	void Pixel(Vector4f& pos, const float& depth, EnumColor& color);
	void Fill(Vector4f pos, Vector4f pos2, EnumColor color);
	void Line(Vector4f pos, Vector4f pos2, EnumColor color);
	void Line(Vector4f pos, Vector4f pos2, const float& depth, EnumColor color);
	void Circle(Vector4f pos, EnumColor color, INT radius, INT curvature);
	void DrawSprite(Vector4f pos, Sprite& sprite);
};

#endif // !___GRAPHIC___
