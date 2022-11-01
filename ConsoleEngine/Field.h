#ifndef ___FIELD___
#define ___FIELD___

#include "stdafx.h"
#include "Layer.h"

using namespace std;

class Field {
protected:
	Layer* m_Layer = nullptr;

	Vector3<int> m_FieldSize;
	Vector2<int> m_HalfFieldSize;
	int m_CANVAS;
	
public:
	Field();
	virtual ~Field();

	void FieldClear();
	void ReSize(Vector3<int> FieldSize);
};

#endif // !___FIELD___

