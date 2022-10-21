#ifndef ___FIELD2D___
#define ___FIELD2D___

#include "stdafx.h"
#include "Layer.h"

using namespace std;

class Field2D {
private:
	Layer* m_Layer;

	Vector3 m_FieldSize;
	Vector2 m_HalfFieldSize;
	int m_CANVAS;

public:
	Field2D();
	Field2D(Vector3 FieldSize);
	~Field2D();

	void Clear();
	void Render(CHAR_INFO* Screen, Vector2 Pos, Vector3 ScreenSize);
};

#endif // !___FIELD2D___

