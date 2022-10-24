#ifndef ___ENGINE___
#define ___ENGINE___

#include "stdafx.h"
#include "Script.h"
#include "Keyboard.h"
#include "Camera2D.h"
#include "Color.h"
#include "Field2D.h"
#include "Time.h"

using namespace std;
using namespace chrono;

class Engine {
private:
	float m_FPS;

	Camera2D* m_Camera = nullptr;
	Color m_Color;

	bool isDone;

	CONSOLE_FONT_INFOEX m_Console_Font_Infoex;

	// �����ڿ� ����ϴ� �Լ�
	void Setting(Vector2<short> FontSize);

public:
	Engine(Camera2D* Camera);
	Engine(Vector2<short> FontSize, Camera2D* Camera);

	void FontSetting(Vector2<short> FontSize);
	void Run(wstring title = L"Engine", int Frame = 60);

	static void Release();
};

inline void Engine::Setting(Vector2<short> FontSize) {
	// ��Ÿ�� ����
	LONG style = GetWindowLong(GetConsoleWindow(), GWL_STYLE);
	SetWindowLong(GetConsoleWindow(), GWL_STYLE, style & ~WS_SIZEBOX);

	// ���콺 �Է� ����
	DWORD prevMode;
	GetConsoleMode(Handle::INPUT, &prevMode);
	SetConsoleMode(Handle::INPUT, prevMode & ~ENABLE_QUICK_EDIT_MODE);

	// �ܼ� Ŀ�� �����
	CONSOLE_CURSOR_INFO cursorInfo = { 1, false };
	SetConsoleCursorInfo(Handle::OUTPUT, &cursorInfo);

	// ��Ʈ ������ ����
	m_Console_Font_Infoex.dwFontSize = { FontSize.x, FontSize.y };
	m_Console_Font_Infoex.cbSize = sizeof(m_Console_Font_Infoex);
	m_Console_Font_Infoex.nFont = 0;
	m_Console_Font_Infoex.FontFamily = FF_DONTCARE;
	m_Console_Font_Infoex.FontWeight = FW_NORMAL;
	wcscpy_s(m_Console_Font_Infoex.FaceName, TEXT("Raster Fonts"));

	SetCurrentConsoleFontEx(Handle::OUTPUT, FALSE, &m_Console_Font_Infoex);
}

#endif // !___ENGINE___
