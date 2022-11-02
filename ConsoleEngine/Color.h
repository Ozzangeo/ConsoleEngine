#ifndef ___ConsoleColor___
#define ___ConsoleColor___

#include "stdafx.h"
#include "Vector.h"

enum EnumColor {
	Color_Black = 0,
	Color_Blue = 16,
	Color_Green = 32,
	Color_SkyBlue = 48,
	Color_Red = 64,
	Color_Perple = 80,
	Color_Yellow = 96,
	Color_White = 112,
	Color_LightBlack = 128,
	Color_LightBlue = 144,
	Color_LightGreen = 160,
	Color_LightSkyBlue = 176,
	Color_LightRed = 192,
	Color_LightPerple = 208,
	Color_LightYellow = 224,
	Color_LightWhite = 240,
	Color_NULL = 255
};
class Color {
private:
	CONSOLE_SCREEN_BUFFER_INFOEX m_Info;
public:
	Color();

	bool SetColor(Vector4 _RGB, int num);
	Vector4 GetColor(int num);
};

#endif // !___ConsoleColor___
