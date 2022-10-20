#ifndef ___FIELD2D___
#define ___FIELD2D___

#include "stdafx.h"

class Layer {
private:
	static short size;
public:
	WORD color;
	
	operator CHAR_INFO();
};

class Field2D {
private:
	Layer a;
public:

};

#endif // !___FIELD2D___
