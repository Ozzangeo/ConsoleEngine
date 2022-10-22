#include "Engine.h"

using namespace std::chrono;

bool EngineScript::Awake() { return true; }

Engine* Engine::m_Instance = nullptr;
Engine::Engine() : m_RunScript(nullptr), m_FPS(60), isNotDone(true),
m_Console_Font_Infoex() {}
Engine::Engine(const Engine& other) : m_RunScript(nullptr), m_FPS(60), isNotDone(true),
m_Console_Font_Infoex() {}
Engine::~Engine() {
	if (m_RunScript) { delete m_RunScript; m_RunScript = nullptr; }
}

void Engine::Fixing() {
	while (isNotDone) {
		SetCurrentConsoleFontEx(Camera2D::HANDLE, FALSE, &m_Console_Font_Infoex);
		m_Camera->SetScreen();
	}
}
void Engine::Setting(CONSOLE_FONT_INFOEX& ConsoleFontInfo) {
	m_Console_Font_Infoex =  ConsoleFontInfo;
	SetCurrentConsoleFontEx(Camera2D::HANDLE, FALSE, &m_Console_Font_Infoex);
	m_Camera->SetScreen();
}

Engine* Engine::GetInstance() {
	if (!m_Instance) { m_Instance = new Engine; }
	return m_Instance;
}
void Engine::Release() {
	if (m_Instance) { delete m_Instance; m_Instance = nullptr; }
}

