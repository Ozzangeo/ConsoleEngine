#include "Field2D.h"

Field2D::Field2D() : m_FieldSize(256, 256, 1) {
	m_CANVAS = static_cast<int>(m_FieldSize.x * m_FieldSize.y);
	m_HalfFieldSize = m_FieldSize.toVector2() * 0.5f;
	m_Layer = new Layer[static_cast<size_t>(m_FieldSize.z * m_CANVAS)];
}
Field2D::~Field2D() {
	if (m_Layer) { delete[] m_Layer; }
}
void Field2D::Clear() {
	for (int i = 0, d = static_cast<int>(m_CANVAS * m_FieldSize.z); i < d; i++) {
		if(!m_Layer[i].isStatic) { m_Layer[i].color = Layer::DEFAULT_COLOR; }
	}
}

void Field2D::Render(CHAR_INFO* Screen, Vector2 Pos, Vector3 ScreenSize) {
	Pos = Pos + m_HalfFieldSize - (ScreenSize.toVector2() * 0.5f);
	Pos.vround();

	Vector3 Temp;
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
					Screen[i].Attributes = m_Layer[pos].color;
				}
			}
		}
	}
}
