#ifndef ___ENGINE___
#define ___ENGINE___

#include "stdafx.h"
#include "Scene.h"
#include "Keyboard.h"
#include "Color.h"
#include "Debug.h"
#include "Time.h"
#include "DefaultComponents.h"
#include "DefaultGameObjects.h"

using namespace std;
using namespace chrono;

class Engine2D {
private:
	float m_FPS;
	bool isDone;

	CONSOLE_FONT_INFOEX m_Console_Font_Infoex;

	// 생성자에 사용하는 함수
	void Setting(Vector2<short> FontSize);

public:
	Engine2D(Vector2<short> FontSize = { 4, 4 });

	void FontSetting(Vector2<short> FontSize);

	template<typename T, enable_if_t<is_base_of_v<Scene, T>, bool> = true>
	void Run(wstring title = L"Engine", int Frame = 60);

	static void Release();
};

inline void Engine2D::Setting(Vector2<short> FontSize) {
	// 스타일 설정
	LONG style = GetWindowLong(GetConsoleWindow(), GWL_STYLE);
	SetWindowLong(GetConsoleWindow(), GWL_STYLE, style & ~WS_SIZEBOX);

	// 마우스 입력 금지
	DWORD prevMode;
	GetConsoleMode(Handle::INPUT, &prevMode);
	SetConsoleMode(Handle::INPUT, prevMode & ~ENABLE_QUICK_EDIT_MODE);

	// 콘솔 커서 숨기기
	CONSOLE_CURSOR_INFO cursorInfo = { 1, false };
	SetConsoleCursorInfo(Handle::OUTPUT, &cursorInfo);

	// 폰트 사이즈 조절
	m_Console_Font_Infoex.dwFontSize = { FontSize.x, FontSize.y };
	m_Console_Font_Infoex.cbSize = sizeof(m_Console_Font_Infoex);
	m_Console_Font_Infoex.nFont = 0;
	m_Console_Font_Infoex.FontFamily = FF_DONTCARE;
	m_Console_Font_Infoex.FontWeight = FW_NORMAL;
	wcscpy_s(m_Console_Font_Infoex.FaceName, TEXT("Raster Fonts"));

	SetCurrentConsoleFontEx(Handle::OUTPUT, FALSE, &m_Console_Font_Infoex);
}
template<typename T, enable_if_t<is_base_of_v<Scene, T>, bool>>
inline void Engine2D::Run(wstring title, int Frame) {
	SetConsoleTitle(title.c_str());

	m_FPS = 1000.0f / Frame;

	isDone = false;

	Scene* Scene = new T;
	if (Scene) {
		Scene->Awake();
		Scene->GameObjects();
	}

	int fps = 0;
	float time = -1.0f;

	while (!isDone) {
		system_clock::time_point start = system_clock::now();
		/////////////Update/////////////

		switch (Keyboard::isKey(KeyCode_ESC)) { case KeyType_DOWN: { isDone = true; } break; }
	
		Scene->Update();
		
		// FPS Debug
		time += Time::DeltaTime;
		if (time >= 1.0f) {
			Debug::Log("[FPS] : " + to_string(fps));
			time -= 1.0f;
			fps = 0;
		}
		fps++;
		
		////////////////////////////////
		Time::ExecutionTime = duration<float>(system_clock::now() - start).count() * 1000.0f;
		if (m_FPS > Time::ExecutionTime) { /*Time::Delay(m_FPS - Time::ExecutionTime);*/ }
		Time::DeltaTime = duration<float>(system_clock::now() - start).count();
	}

	Scene->Release();
}
#endif // !___ENGINE___
