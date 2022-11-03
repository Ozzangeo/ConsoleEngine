#include "Color.h"

Color::Color() {
	m_Info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(Handle::OUTPUT, &m_Info);
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