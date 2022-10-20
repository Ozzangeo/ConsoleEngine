#include "Layer.h"

const WORD Layer::DEFAULT_COLOR = 7;
Layer::Layer() {
	m_Size = { 200, 200, 40000 };

	color = new WORD[static_cast<int>(m_Size.z)];
	isStatic = new bool[static_cast<int>(m_Size.z)]{ false, };

	//Clear();
}
Layer::Layer(WORD* _color, bool* _isStatic) {
}
Layer::~Layer() {
	if (color) { delete[] color; }
	if (isStatic) { delete[] isStatic; }
}