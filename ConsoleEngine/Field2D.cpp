#include "Field2D.h"

Field2D::Field2D() : m_FieldSize(1024, 1024, 1) {
	m_CANVAS = m_FieldSize.x * m_FieldSize.y;
	m_HalfFieldSize = m_FieldSize.toVector2<int>() * 0.5f;
	m_Layer = new Layer[static_cast<size_t>(m_FieldSize.z * m_CANVAS)];
}
Field2D::~Field2D() {
	if (m_Layer) { delete[] m_Layer; }
}

void Field2D::Clear() {
	for (int i = 0, d = static_cast<int>(m_CANVAS * m_FieldSize.z); i < d; i++) {
		if(!m_Layer[i].isStatic) { m_Layer[i].color = Color_Black; }
	}
}
bool Merge(Field2D* Field, CHAR_INFO* Screen, Vector2<int> Pos, Vector2<int> ScreenSize) {
	Vector3<float> Temp;
	int pos = 0;

	// 뭔가 여기서 멀티스레딩이 이상하다 
	// 위치 공식을 자고 일어나서 다시 세워야할듯
	for (int d = 0; d < Field->m_FieldSize.z; d++) {
		Temp.z = d * static_cast<float>(Field->m_CANVAS);

		for (int y = 0, i = (Pos.y * ScreenSize.x); y < ScreenSize.y; y++) {
			Temp.y = (y + Pos.y) * static_cast<float>(Field->m_FieldSize.x);

			for (int x = 0; x < ScreenSize.x; x++, i++) {
				Temp.x = static_cast<float>(Pos.x + x);

				if (0 > Temp.x || Temp.x >= Field->m_FieldSize.x) { continue; }
				pos = static_cast<int>(Temp.y + Temp.x);

				if (0 <= pos && pos < Field->m_CANVAS) {
					pos += static_cast<int>(Temp.z);
					if (Field->m_Layer[pos].color != Color_NULL) { Screen[i].Attributes = Field->m_Layer[pos].color; }
				}
			}
		}
	}
	
	return true;
}
void Field2D::Render(CHAR_INFO* Screen, Vector2<float> Pos, Vector2<int> ScreenSize) {
	Pos = Pos + m_HalfFieldSize.toVector2<float>() - (ScreenSize.toVector2<float>() * 0.5f);
	Pos.vround();
	
	vector<future<bool>> futures;
	for (float i = 0; i < ScreenSize.y; i += ScreenSize.y * 0.25f) {
		Pos.y += i;
		Vector2<int> pos = Pos.toVector2<int>();
		futures.emplace_back(Thread->EmplaceJobAndGetFutrue(Merge, this, Screen, pos, Vector2<int>{ ScreenSize.x, static_cast<int>(ScreenSize.y * 0.25f) }));
	}

	for (auto& f : futures) {
		f.wait();
	}

	/*
	Vector3<float> Temp;
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
