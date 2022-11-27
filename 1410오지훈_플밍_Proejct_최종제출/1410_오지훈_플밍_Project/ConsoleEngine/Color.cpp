#include "Color.h"

Color::Color() {
	m_Info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(Handle::OUTPUT, &m_Info);
}
bool Color::ResetColor() {
	GetConsoleScreenBufferInfoEx(Handle::OUTPUT, &m_Info);
	m_Info.srWindow.Bottom += 1;

	m_Info.ColorTable[0] = RGB(12, 12, 12);
	m_Info.ColorTable[1] = RGB(0, 55, 218);
	m_Info.ColorTable[2] = RGB(19, 161, 14);
	m_Info.ColorTable[3] = RGB(58, 150, 221);
	m_Info.ColorTable[4] = RGB(197, 15, 31);
	m_Info.ColorTable[5] = RGB(136, 23, 152);
	m_Info.ColorTable[6] = RGB(193, 156, 0);
	m_Info.ColorTable[7] = RGB(0, 0, 0);
	m_Info.ColorTable[8] = RGB(118, 118, 118);
	m_Info.ColorTable[9] = RGB(59, 120, 255);
	m_Info.ColorTable[10] = RGB(22, 198, 12);
	m_Info.ColorTable[11] = RGB(97, 214, 214);
	m_Info.ColorTable[12] = RGB(231, 72, 86);
	m_Info.ColorTable[13] = RGB(180, 0, 158);
	m_Info.ColorTable[14] = RGB(249, 241, 165);
	m_Info.ColorTable[15] = RGB(242, 242, 242);

	SetConsoleScreenBufferInfoEx(Handle::OUTPUT, &m_Info);
	return true;
}
bool Color::SetColor(Rgb255 _RGB, int num) {
	if (0 > num || num > 16) { return false; }
	GetConsoleScreenBufferInfoEx(Handle::OUTPUT, &m_Info);

	/////////////////////////////////////////////////////////
	// 호출할 때마다 Bottom이 1씩 줄어드는 버그때문에 적은 코드//
	//           만약 버그가 해결되었다면 삭제할 것           //
	/////////////////////////////////////////////////////////
	m_Info.srWindow.Bottom += 1;
	/////////////////////////////////////////////////////////

	m_Info.ColorTable[num] = RGB(_RGB.r, _RGB.g, _RGB.b);

	SetConsoleScreenBufferInfoEx(Handle::OUTPUT, &m_Info);
	return true;
}