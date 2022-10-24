#include "Engine.h"

using namespace std::chrono;

Engine::Engine(Camera2D* Camera) : m_Camera(Camera), m_FPS(60), isDone(false) { Setting({ 4, 4 }); }
Engine::Engine(Vector2<short> FontSize, Camera2D* Camera) : m_Camera(Camera), m_FPS(60), isDone(false) { Setting(FontSize); }

void Engine::FontSetting(Vector2<short> FontSize) {
	FontSize.vround();
	
	m_Console_Font_Infoex.dwFontSize = { FontSize.x, FontSize.y };
	SetCurrentConsoleFontEx(Handle::OUTPUT, FALSE, &m_Console_Font_Infoex);

	m_Camera->SetScreen();
}
void Engine::Run(wstring title, int Frame) {
	SetConsoleTitle(title.c_str());

	m_FPS = 1000.0f / Frame;

	isDone = false;

	#if ___DEBUG___
	ofstream Debug("Debug.txt");
	#endif
	while (!isDone) {
		system_clock::time_point start = system_clock::now();
		/////////////Update/////////////

		switch (Keyboard::isKey(KeyCode_ESC)) {
		case KeyType_DOWN: { isDone = true; } break;
		}

		m_Camera->Render();

		#if ___DEBUG___
		Debug << 1.0f / Time::GetDeltaTime() << '\n';
		#endif

		////////////////////////////////
		Time::ExecutionTime = duration<float>(system_clock::now() - start).count() * 1000.0f;
		if (m_FPS > Time::ExecutionTime) { Time::Delay(m_FPS - Time::ExecutionTime); }
		Time::DeltaTime = duration<float>(system_clock::now() - start).count();
	}

	#if ___DEBUG___
	Debug.close();
	#endif
}
void Engine::Release() {
	Keyboard::Release();
}