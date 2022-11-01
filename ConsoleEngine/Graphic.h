#ifndef ___GRAPHIC___
#define ___GRAPHIC___

#include "stdafx.h"
#include "Field.h"
#include "Debug.h"

class Graphic : public Field {
private:
	const COORD ZeroPos;

	const int BufferSize;
	bool m_Index;
	HANDLE* m_Screen;

	void ScreenFlipping();

	Graphic();

	static Graphic* m_Instance;

public:
	~Graphic();

	static Graphic& GetInstance();
	static void Release();
	
	void SetFontSize(Vector2<short> FontSize);

	void Merge(CHAR_INFO* Screen, Vector2<float> Pos, Vector2<int> ScreenSize);
	void Render(CHAR_INFO* Screen, const Vector2<int>& ScreenSize, const COORD& size, SMALL_RECT& rect);
};

#endif // !___GRAPHIC___
