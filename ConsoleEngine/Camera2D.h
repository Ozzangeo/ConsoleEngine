#ifndef ___CAMERA___
#define ___CAMERA___

#include "stdafx.h"
#include "Field2D.h"

class Camera2D {
private:
	Camera2D();
	Camera2D(const Camera2D& other);

	Vector2<float> m_Pos;
	Vector3<int> m_ScreenSize;
	Vector2<int> m_HalfScreenSize;

	CHAR_INFO* m_Screen;

	COORD m_size;
	SMALL_RECT m_rect;

	Field2D m_Field;

	static Camera2D* m_Instance;

public:
	~Camera2D();

	static Camera2D* GetInstance();
	static void Release();

	static const WORD DEFAULT_BACKGROUND;
	static const HANDLE INPUT_HANDLE;
	static const HANDLE OUTPUT_HANDLE;
	static const COORD ZERO_POS;
	
	void Render();
	void Clear();

	void SetScreenSize(Vector3<int> Size);
	void SetScreen();
	Vector2<float>* GetPos();
};

#endif // !___CAMERA___
