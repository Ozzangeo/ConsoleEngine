#include "SceneManager.h"

bool SceneManager::isEnd = false;
SceneManager* SceneManager::m_Instance = nullptr;
SceneManager::~SceneManager() {
	if (nowScene)		{ nowScene->Release();		delete nowScene;	nowScene = nullptr; }
	if (beforeScene)	{ beforeScene->Release();	delete beforeScene; beforeScene = nullptr; }
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
