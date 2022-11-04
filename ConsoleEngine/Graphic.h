#ifndef ___GRAPHIC___
#define ___GRAPHIC___

#include "stdafx.h"
#include "Vector.h"
#include "Color.h"
#include "Debug.h"

using namespace std;

namespace DefaultComponents { class Camera; }

class Graphic {
	friend class Engine;
	friend class Component;
	friend class DefaultComponents::Camera;
private:
	Graphic();
	~Graphic();

	Vector4* CameraPos;
	Vector4 m_ScreenSize;
	Vector4 m_HalfScreenSize;

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

	inline void DrawCircle(Vector4& pos, Vector4& pos2, EnumColor& color);

	void Render();
	static void Release();
	static Graphic& GetInstance();

public:
	void Pixel(Vector4 pos, EnumColor color);
	void Pixel(Vector4 pos, float depth, EnumColor color);
	void Fill(Vector4 pos, Vector4 pos2, EnumColor color);
	void Line(Vector4 pos, Vector4 pos2, EnumColor color);
	void Line(Vector4 pos, Vector4 pos2, const float& depth, EnumColor color);
	void Circle(Vector4 pos, EnumColor color, INT radius, INT curvature);
	void Sprite(Vector4 pos, COORD size, EnumColor* sprite);

	// NotSafe 시리즈 ( if문이 2개 생략되어 살짝 더 빠름 )
	void NotSafePixel(const Vector4& pos, const EnumColor& color);
	void NotSafeFill(Vector4 pos, Vector4 pos2, EnumColor color);
};

#endif // !___GRAPHIC___
