#include "Field2D.h"

using namespace std;
using namespace chrono;

Field2D::Field2D() : m_FieldSize(128, 72, 1), RENDER_THREAD_COUNT(4) { Setting(); }
Field2D::~Field2D() {
	if (m_Layer) { delete[] m_Layer; m_Layer = nullptr; }
}

void Field2D::Clear() {
	for (int i = 0, d = static_cast<int>(m_CANVAS * m_FieldSize.z); i < d; i++) {
		if (!m_Layer[i].isStatic) { m_Layer[i].Color = Color_White; }
	}
}
void Field2D::Merge(Field2D* Field, CHAR_INFO* Screen, Vector2<int> Pos, Vector2<int> ScreenSize, float multiple, float Threads) {
	Vector3<float> Temp;
	int pos;
	int temp = static_cast<int>(ScreenSize.y * multiple);

	for (int d = 0; d < Field->m_FieldSize.z; d++) {
		Temp.z = d * static_cast<float>(Field->m_CANVAS);

		for (int y = temp, i = temp * ScreenSize.x; y < ScreenSize.y * (multiple + Threads); y++) {
			Temp.y = (y + Pos.y) * static_cast<float>(Field->m_FieldSize.x);

			for (int x = 0; x < ScreenSize.x; x++, i++) {
				Temp.x = static_cast<float>(Pos.x + x);

				if (0 > Temp.x || Temp.x >= Field->m_FieldSize.x) { continue; }
				pos = static_cast<int>(Temp.y + Temp.x);

				if (0 <= pos && pos < Field->m_CANVAS) {
					pos += static_cast<int>(Temp.z);
					if (Field->m_Layer[pos].Color != Color_NULL) {
						Screen[i].Attributes = Field->m_Layer[pos].Color;
					}
				}
			}
		}
	}
}
void Field2D::Render(CHAR_INFO* Screen, Vector2<float> Pos, Vector2<int> ScreenSize) {
	Pos = Pos + m_HalfFieldSize.toVector2<float>() - (ScreenSize.toVector2<float>() * 0.5f);
	Pos.vround();

	// 멀티 스레딩 출력
	for (float i = 0, Threads = 1.0f / RENDER_THREAD_COUNT; i < 1; i += Threads) {
		m_Futures.emplace_back(async(launch::async, Merge, this, Screen, Pos.toVector2<int>(), ScreenSize, i, Threads));
	}
	for (auto& f : m_Futures) { f.wait(); }
	m_Futures.clear();

	// 싱글 스레딩 출력
	/*Vector3<float> Temp;
	int pos = 0;
	for (int d = 0; d < m_FieldSize.z; d++) {
		Temp.z = d * static_cast<float>(m_CANVAS);

		for (int y = 0, i = 0; y < ScreenSize.y; y++) {
			Temp.y = (y + Pos.y) * m_FieldSize.x;

			for (int x = 0; x < ScreenSize.x; x++, i++) {
				Temp.x = Pos.x + x;

				if (0 > Temp.x || Temp.x >= m_FieldSize.x) { continue; }
				pos = static_cast<int>(Temp.y + Temp.x);

				if (0 <= pos && pos < m_CANVAS) {
					pos += static_cast<int>(Temp.z);
					if(m_Layer[pos].color != Color_NULL) { Screen[i].Attributes = m_Layer[pos].color; }
				}
			}
		}
	}*/
}

void Field2D::ReSize(Vector3<int> FieldSize) {
	m_FieldSize = FieldSize;
	m_HalfFieldSize = m_FieldSize.toVector2<int>() * 0.5f;
	if (m_Layer) { delete[] m_Layer; m_Layer = nullptr; }
	
	m_CANVAS = FieldSize.x * FieldSize.y;
	m_Layer = new Layer[m_FieldSize.z * m_CANVAS];
}
