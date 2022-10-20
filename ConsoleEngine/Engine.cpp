#include "Engine.h"

using namespace std::chrono;

bool EngineScript::Awake() { return true; }

Engine* Engine::m_Instance = nullptr;
Engine::Engine() : m_FPS(1000.0f / 60.0f), m_MaxFPS(60.0f) {}
Engine::Engine(const Engine& other) : m_FPS(1000.0f / 60.0f), m_MaxFPS(60.0f) {}

Engine* Engine::GetInstance() {
	if (!m_Instance) { m_Instance = new Engine; }

	return m_Instance;
}
void Engine::Release() {
	if (m_Instance) { delete m_Instance; }
}
float Engine::SetFPS(float _FPS) {
	m_MaxFPS = _FPS;
	return m_FPS = 1000.0f / m_MaxFPS;
}

