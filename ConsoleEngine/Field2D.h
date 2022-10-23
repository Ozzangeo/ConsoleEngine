#ifndef ___FIELD2D___
#define ___FIELD2D___

#include "stdafx.h"
#include "Layer.h"
#include "ThreadPool.h"

using namespace std;

class Field2D;
bool Merge(Field2D* Field, CHAR_INFO* Screen, Vector2<int> Pos, Vector2<int> ScreenSize, float multiple, float Threads);

class Field2D {
friend bool Merge(Field2D* Field, CHAR_INFO* Screen, Vector2<int> Pos, Vector2<int> ScreenSize, float multiple, float Threads);
private:
	ThreadPool* Thread = ThreadPool::GetInstance();

	Layer* m_Layer;
	ofstream ofs;

	Vector3<int> m_FieldSize;
	Vector2<int> m_HalfFieldSize;
	int m_CANVAS;


public:
	Field2D();
	~Field2D();

	void Clear();
	void Render(CHAR_INFO* Screen, Vector2<float> Pos, Vector2<int> ScreenSize);
};

#endif // !___FIELD2D___

