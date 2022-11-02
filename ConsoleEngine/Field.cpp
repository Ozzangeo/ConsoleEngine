#include "Field.h"

using namespace std;
using namespace chrono;

Field::Field() : m_FieldSize(128, 72, 1, 128 * 72 * 1) {
	m_FieldSize.vround();
	m_HalfFieldSize = (m_FieldSize * 0.5f).vround();
	m_Layer = new Layer[m_FieldSize.GetW<size_t>()];
}
Field::~Field() { if (m_Layer) { delete[] m_Layer; m_Layer = nullptr; } }

void Field::FieldClear() {
	for (int i = 0, d = static_cast<int>(m_FieldSize.w); i < d; i++) {
		if (!m_Layer[i].isStatic) { m_Layer[i].Color = Color_White; }
	}
}

void Field::ReSize(COORD FieldSize, int Depth) {
	m_FieldSize = { static_cast<float>(FieldSize.X), static_cast<float>(FieldSize.Y), static_cast<float>(Depth),
				    static_cast<float>(FieldSize.X * FieldSize.Y * Depth) };
	m_HalfFieldSize = (m_FieldSize * 0.5f).vround();

	if (m_Layer) { delete[] m_Layer; m_Layer = nullptr; }
	m_Layer = new Layer[static_cast<size_t>(m_FieldSize.w)];
}
