#ifndef ___GRAPHIC___
#define ___GRAPHIC___

#include "stdafx.h"
#include "Vector.h"
#include "Color.h"
#include "Debug.h"

namespace DefaultComponents { class Camera; }

class Graphic {
	friend class Engine;
	friend class Component;
	friend class DefaultComponents::Camera;
private:
	Graphic();

	Vector4 m_ScreenSize;
	Vector4 m_HalfScreenSize;

	COORD m_size;
	SMALL_RECT m_rect;
	CHAR_INFO* m_Screen;
	int* m_Depth;

	const WORD DEFAULT_BACKGROUND = Color_LightWhite;
	const CHAR_INFO DEFAULT_SCREEN = { ' ', DEFAULT_BACKGROUND };
	const int DEFAULT_DEPTH = -100;
	const COORD ZERO_POS = { 0, 0 };

	static Graphic* m_Instance;

	inline void SetScreenScale(const COORD& Scale);
	void SetScreenSize(const COORD& Size);
	void SetScreen();

	void Render();
	static void Release();
	static Graphic& GetInstance();

public:
	~Graphic();
};

#endif // !___GRAPHIC___
