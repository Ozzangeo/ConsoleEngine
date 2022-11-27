#ifndef ___ANIMATION___
#define ___ANIMATION___

#include "stdafx.h"
#include "Sprite.h"

using namespace std;

class Animation {
public:
	Animation();
	~Animation();

	//          time   sprite
	vector<pair<float, Sprite>> animations;

	bool LoadAnimaition(string filename);
};

#endif // !___ANIMATION___
