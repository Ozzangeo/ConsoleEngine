#include "SceneManager.h"

bool SceneManager::m_isEnd = false;
SceneManager* SceneManager::m_Instance = nullptr;
SceneManager::~SceneManager() {
	if (m_nowScene)		{ m_nowScene->Release();		delete m_nowScene;	m_nowScene = nullptr; }
	if (m_deleteScenes)	{
		for (auto& item : *m_deleteScenes) {
			if (item) {
				item->Release();
				delete item;
				item = nullptr;
			}
		}

		delete m_deleteScenes;
		m_deleteScenes = nullptr;
	}
}
SceneManager& SceneManager::GetInstance() {
	if (!m_Instance) { m_Instance = new SceneManager; }
	return *m_Instance;
}

void SceneManager::Update() {
	m_nowScene->Update();
}
void SceneManager::Release() {
	if (m_Instance) { delete m_Instance; m_Instance = nullptr; }
	Debug::Log("[ SceneManager ] : Release");
}
Scene* SceneManager::GetNowScene() {
	return m_nowScene;
}
