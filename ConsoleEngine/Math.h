#ifndef ___MATH___
#define ___MATH___

#include "stdafx.h"
#include "Vector.h"
#include "Matrix.h"
#include "Debug.h"

class Math {
	friend class ConsoleEngine;
private:

	static void Release();
public:
	static const float PI;
	static const float* cosb;
	static const float* sinb;
	static const float* tanb;

	inline static Matrix4x4f GetRotateMatrix(const Vector4i& rotate);
	inline static Matrix4x4f GetScaleMatrix(const Vector4f& scale);
    inline static Matrix4x4f GetPosMatrix(const Vector4f& pos);

    inline static Vector4i RotateAdd(Vector4i& one, const Vector4i& two);
    inline static Vector4i RotateSub(Vector4i& one, const Vector4i& two);
};

inline Matrix4x4f Math::GetRotateMatrix(const Vector4i& rotate) {
    return
        /*  Rotate X */ Matrix4x4f{
            1, 0, 0, 0,
            0, cosb[rotate.x], sinb[rotate.x], 0,
            0, -sinb[rotate.x], cosb[rotate.x], 0,
            0, 0, 0, 1 }
            /*  Rotate Y */ *Matrix4x4f{
                cosb[rotate.y], 0, -sinb[rotate.y], 0,
                0, 1, 0, 0,
                sinb[rotate.y], 0, cosb[rotate.y], 0,
                0, 0, 0, 1 }
                /*  Rotate Z */ *Matrix4x4f{
                    cosb[rotate.z], sinb[rotate.z], 0, 0,
                    -sinb[rotate.z], cosb[rotate.z], 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1 };
}
inline Matrix4x4f Math::GetScaleMatrix(const Vector4f& scale) {
    return
        /* Scale XYZ */ Matrix4x4f{
            scale.x, 0, 0, 0,
            0, scale.y, 0, 0,
            0, 0, scale.z, 0,
            0, 0, 0, 1
    };;
}
inline Matrix4x4f Math::GetPosMatrix(const Vector4f& pos) {
    return Matrix4x4f{
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        pos.x, pos.y, pos.z, 1
    };
}

inline Vector4i Math::RotateAdd(Vector4i& one, const Vector4i& two) {
    Vector4i res = one + two;

    while (res.x > 180) { res.x -= 360; }
    while (res.x < -180) { res.x += 360; }

    while (res.y > 180) { res.y -= 360; }
    while (res.y < -180) { res.y += 360; }

    while (res.z > 180) { res.z -= 360; }
    while (res.z < -180) { res.z += 360; }

    return res;
}
inline Vector4i Math::RotateSub(Vector4i& one, const Vector4i& two) {
    Vector4i res = one - two;

    while (res.x > 180) { res.x -= 360; }
    while (res.x < -180) { res.x += 360; }

    while (res.y > 180) { res.y -= 360; }
    while (res.y < -180) { res.y += 360; }

    while (res.z > 180) { res.z -= 360; }
    while (res.z < -180) { res.z += 360; }

    return res;
}

#endif // !___MATH___


