#include "Field.h"

using namespace std;
using namespace chrono;

Field::Field() : m_FieldSize(128, 72, 1) {
	m_CANVAS = m_FieldSize.x * m_FieldSize.y;
	m_HalfFieldSize = m_FieldSize.toVector2<int>() * 0.5f;
	m_Layer = new Layer[static_cast<size_t>(m_FieldSize.z) * static_cast<size_t>(m_CANVAS)];
}
Field::~Field() { if (m_Layer) { delete[] m_Layer; m_Layer = nullptr; } }

void Field::FieldClear() {
	for (int i = 0, d = static_cast<int>(m_CANVAS * m_FieldSize.z); i < d; i++) {
		if (!m_Layer[i].isStatic) { m_Layer[i].Color = Color_White; }
	}
}

void Field::ReSize(Vector3<int> FieldSize) {
	m_FieldSize = FieldSize;
	m_HalfFieldSize = m_FieldSize.toVector2<int>() * 0.5f;
	m_CANVAS = FieldSize.x * FieldSize.y;
	
	if (m_Layer) { delete[] m_Layer; m_Layer = nullptr; }
	m_Layer = new Layer[static_cast<size_t>(m_FieldSize.z) * static_cast<size_t>(m_CANVAS)];
}
