#ifndef ___SPRITE___
#define ___SPRITE___

#include "stdafx.h"
#include "Color.h"

using namespace std;

class Sprite {
public:
	Sprite();
	~Sprite();

	EnumColor* sprite;
	COORD size;

	bool LoadSprite(string filename);
};

#endif // !___SPRITE___

