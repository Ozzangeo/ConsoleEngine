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
	
	void SetFontSize(COORD FontSize);

	void Merge(CHAR_INFO* Screen, Vector4 Pos, Vector4 ScreenSize);
	void Render(CHAR_INFO* Screen, const Vector4& ScreenSize, const COORD& size, SMALL_RECT& rect);
};

#endif // !___GRAPHIC___
