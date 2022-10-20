#ifndef ___CAMERA___
#define ___CAMERA___

#include "stdafx.h"
#include "Field2D.h"

class Camera2D {
private:
	Vector2 m_Pos;
	Vector3 m_ScreenSize;

	CHAR_INFO* m_Screen;
	CHAR_INFO* m_DefaultScreen;

	COORD m_size;
	SMALL_RECT m_rect;

	static Camera2D* m_Instance;

	Camera2D();

public:
	~Camera2D();

	static Camera2D* GetInstance();
	static const WORD DEFAULT_BACKGROUND;
	static const HANDLE HANDLE;
	static const COORD ZERO_POS;
	
	void Render();
	void Clear();

	void SetScreenSize(Vector3 Size);
	Vector2* GetPos();

	Camera2D operator=(const Camera2D& ref);
};

#endif // !___CAMERA___
