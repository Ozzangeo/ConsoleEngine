#include "Color.h"

Color::Color() {
	m_Info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(Handle::OUTPUT, &m_Info);
}
bool Color::SetColor(Rgb255 _RGB, int num) {
	if (0 > num || num > 16) { return false; }
	GetConsoleScreenBufferInfoEx(Handle::OUTPUT, &m_Info);

	/////////////////////////////////////////////////////////
	// ȣ���� ������ Bottom�� 1�� �پ��� ���׶����� ���� �ڵ�//
	//           ���� ���װ� �ذ�Ǿ��ٸ� ������ ��           //
	/////////////////////////////////////////////////////////
	m_Info.srWindow.Bottom += 1;
	/////////////////////////////////////////////////////////

	m_Info.ColorTable[num] = RGB(_RGB.r, _RGB.g, _RGB.b);

	SetConsoleScreenBufferInfoEx(Handle::OUTPUT, &m_Info);
	return true;
}