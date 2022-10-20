#include "Engine.h"

using namespace std::chrono;

bool EngineScript::Awake() { return true; }

Engine* Engine::m_Instance = nullptr;
Engine::Engine() : m_RunScript(nullptr), m_FPS(60) {}
Engine::Engine(const Engine& other) : m_RunScript(nullptr), m_FPS(60) {}
Engine::~Engine() {
	if (m_RunScript) { delete m_RunScript; m_RunScript = nullptr; }
}

Engine* Engine::GetInstance() {
	if (!m_Instance) { m_Instance = new Engine; }
	return m_Instance;
}
void Engine::Release() {
	if (m_Instance) { delete m_Instance; m_Instance = nullptr; }
}

