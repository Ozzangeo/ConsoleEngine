#ifndef ___LAYER___
#define ___LAYER___

#include "stdafx.h"
#include "Color.h"
#include "Vector.h"

using namespace std;

class Layer {
private:
public:
	Layer();
	Layer(WORD _color, bool _isStatic);
	~Layer();
	
	WORD Color;
	bool isStatic;

	static const WORD DEFAULT_COLOR;
};

#endif // !___LAYER___

