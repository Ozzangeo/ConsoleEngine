#ifndef ___LAYER___
#define ___LAYER___

#include "stdafx.h"
#include "Vector.h"

using namespace std;

enum Color {
	Color_Black = 0,
	Color_Blue = 1,
	Color_Green = 2,
	Color_SkyBlue = 3,
	Color_Red = 4,
	Color_Perple = 5,
	Color_Yellow = 6,
	Color_White = 7,
	Color_LightBlack = 8,
	Color_LightBlue = 9,
	Color_LightGreen = 10,
	Color_LightSkyBlue = 11,
	Color_LightRed = 12,
	Color_LightPerple = 13,
	Color_LightYellow = 14,
	Color_LightWhite = 15
};

class Layer {
private:
	static Vector3 m_Size;

	WORD* color;
	bool* isStatic;
	Layer();
	Layer(WORD* _color, bool* _isStatic);

public:
	~Layer();

	static const WORD DEFAULT_COLOR;
};

#endif // !___LAYER___

