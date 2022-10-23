#include "Color.h"

Color* Color::m_Instance = nullptr;
Color::Color() {
	m_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	m_Info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(m_handle, &m_Info);
}

Color* Color::GetInstance() {
	if (!m_Instance) { m_Instance = new Color; }
	return m_Instance;
}
void Color::Release() {
	if (m_Instance) { delete m_Instance; }
}

bool Color::SetColor(Vector3<BYTE> _RGB, int num) {
	if (0 > num || num > 16) { return false; }
	GetConsoleScreenBufferInfoEx(m_handle, &m_Info);

	// 호출할 때마다 Bottom이 1씩 줄어드는 버그때문에 적은 코드
	// 만약 버그가 해결되었다면 삭제할 것
	m_Info.srWindow.Bottom += 1;
	m_Info.ColorTable[num] = RGB(_RGB.x, _RGB.y, _RGB.z);

	SetConsoleScreenBufferInfoEx(m_handle, &m_Info);
	return true;
}

Vector3<DWORD> Color::GetColor(int num) {
	if (0 > num || num > 16) { return { 0, 0, 0 }; }
	return { m_Info.ColorTable[num] & 0x0000ff,
			 m_Info.ColorTable[num] & 0x00ff00,
			 m_Info.ColorTable[num] & 0xff0000 };
}
