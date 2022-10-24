#include "Color.h"

Color::Color() {
	m_Info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(Handle::OUTPUT, &m_Info);
}
bool Color::SetColor(Vector3<BYTE> _RGB, int num) {
	if (0 > num || num > 16) { return false; }
	GetConsoleScreenBufferInfoEx(Handle::OUTPUT, &m_Info);

	// ȣ���� ������ Bottom�� 1�� �پ��� ���׶����� ���� �ڵ�
	// ���� ���װ� �ذ�Ǿ��ٸ� ������ ��
	m_Info.srWindow.Bottom += 1;
	m_Info.ColorTable[num] = RGB(_RGB.x, _RGB.y, _RGB.z);

	SetConsoleScreenBufferInfoEx(Handle::OUTPUT, &m_Info);
	return true;
}

Vector3<DWORD> Color::GetColor(int num) {
	if (0 > num || num > 16) { return { 0, 0, 0 }; }
	return { m_Info.ColorTable[num] & 0x0000ff,
			 m_Info.ColorTable[num] & 0x00ff00,
			 m_Info.ColorTable[num] & 0xff0000 };
}
