#ifndef ___MATRIX___
#define ___MATRIX___

#include "stdafx.h"
#include "Vector.h"

class Matrix4x4 {
public:
	union {
		struct { __m128 matrix[4]; };
		struct { Vector4 vector[4]; };
	};
};
//Matrix4x4 Mul(const Matrix4x4& mat1, const Matrix4x4& mat2);

#endif // !___MATRIX___