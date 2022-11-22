#include "SceneManager.h"

SceneManager* SceneManager::m_Instance = nullptr;
SceneManager::~SceneManager() {
	if (nowScene) { delete nowScene; nowScene = nullptr; }
}
SceneManager& SceneManager::GetInstance() {
	if (!m_Instance) { m_Instance = new SceneManager; }
	return *m_Instance;
}

void SceneManager::Update() {
	nowScene->Update();
}
void SceneManager::Release() {
	if (m_Instance) { delete m_Instance; m_Instance = nullptr; }
	Debug::Log("[ SceneManager ] : Release");
}
Scene* SceneManager::GetNowScene() {
	return nowScene;
}
