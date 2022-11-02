#ifndef ___FIELD___
#define ___FIELD___

#include "stdafx.h"
#include "Layer.h"

using namespace std;

class Field {
protected:
	Layer* m_Layer = nullptr;

	Vector4 m_FieldSize;
	Vector4 m_HalfFieldSize;
	
public:
	Field();
	virtual ~Field();

	void FieldClear();
	void ReSize(COORD FieldSize, int Depth);
};

#endif // !___FIELD___

