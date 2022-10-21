#include "Field2D.h"

Field2D::Field2D() : m_FieldSize(512, 512, 5), m_CANVAS(262144), m_HalfFieldSize(256, 256),
	m_Layer(new Layer[1310720]) {

}
Field2D::Field2D(Vector3 FieldSize) : m_FieldSize(FieldSize), m_HalfFieldSize(FieldSize.toVector2() * 0.5f),
m_CANVAS(static_cast<int>(FieldSize.x* FieldSize.y)), m_Layer(new Layer[static_cast<size_t>(FieldSize.x * FieldSize.y)]) {

}
Field2D::~Field2D() {
	if (m_Layer) { delete[] m_Layer; }
}

void Field2D::Clear() {
	for (int i = 0, d = static_cast<int>(m_CANVAS * m_FieldSize.z); i < d; i++) {
		if(!m_Layer[i].isStatic) { m_Layer[i].color = Color_LightRed/*Layer::DEFAULT_COLOR*/; }
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
			Temp.y = (y + Pos.y) * ScreenSize.x;
			for (int x = 0; x < ScreenSize.x; x++, i++) {
				if (Pos.x + x > m_FieldSize.x * 0.5f) { continue; }
				// 이상해 이거
				pos = static_cast<int>(Temp.z + Temp.y + Pos.x + x);
				if (m_CANVAS > pos - Temp.z && pos - Temp.z >= 0) {
					if(m_Layer[pos].color != Layer::DEFAULT_COLOR) { Screen[i].Attributes = m_Layer[pos].color; }
				}
			}
		}

		/*for (int i = 0; i < ScreenSize.z; i++) {
			pos = static_cast<int>(Temp.z + i + Pos.x);

			if (pos >= 0 && m_Layer[pos].color != Layer::DEFAULT_COLOR) {
				Screen[i].Attributes = m_Layer[pos].color;
			}
		}*/
	}
}
