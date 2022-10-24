#ifndef ___FIELD2D___
#define ___FIELD2D___

#include "stdafx.h"
#include "Layer.h"

using namespace std;

class Field2D {
private:
	const int RENDER_THREAD_COUNT;
	vector<future<void>> m_Futures;

	Layer* m_Layer = nullptr;

	Vector3<int> m_FieldSize;
	Vector2<int> m_HalfFieldSize;
	int m_CANVAS;
	
	// 생성자에 사용하는 함수
	void Setting();

public:
	Field2D(int RenderThreads = 4);
	Field2D(Vector3<int> Field, int RenderThreads = 4);
	
	~Field2D();

	void Clear();
	static void Merge(Field2D* Field, CHAR_INFO* Screen, Vector2<int> Pos, Vector2<int> ScreenSize, float multiple, float Threads);
	void Render(CHAR_INFO* Screen, Vector2<float> Pos, Vector2<int> ScreenSize);
};

inline void Field2D::Setting() {
	m_Futures.reserve(RENDER_THREAD_COUNT);

	m_CANVAS = m_FieldSize.x * m_FieldSize.y;
	m_HalfFieldSize = m_FieldSize.toVector2<int>() * 0.5f;
	m_Layer = new Layer[static_cast<size_t>(m_FieldSize.z * m_CANVAS)];
}

#endif // !___FIELD2D___

