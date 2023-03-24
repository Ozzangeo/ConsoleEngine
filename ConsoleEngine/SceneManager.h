#ifndef ___SCENEMANAGER___
#define ___SCENEMANAGER___

#include "stdafx.h"
#include "Scene.h"

// Singleton
class SceneManager {
private:
	static bool m_isEnd;

	Scene* m_nowScene = nullptr;
	list<Scene*>* m_deleteScenes = new list<Scene*>;

	SceneManager() {}
	SceneManager(const SceneManager& ref) {}

	static SceneManager* m_Instance;

public:
	~SceneManager();
	static SceneManager& GetInstance();
	
	void Update();
	static void Release();
	static void StopEngine();

	inline static bool isRunning();

	template<typename T, enable_if_t<is_base_of_v<Scene, T>, bool> = true>
	inline void ChangeScene();
	inline void ClearBeforeScenes();
	Scene* GetNowScene();
};

inline void SceneManager::StopEngine() { m_isEnd = true; }
inline bool SceneManager::isRunning() { return !m_isEnd; }

template<typename T, enable_if_t<is_base_of_v<Scene, T>, bool>>
inline void SceneManager::ChangeScene() {
	if (m_nowScene) { m_deleteScenes->push_back(m_nowScene); }
	
	m_nowScene = new T;
	m_nowScene->Awake();
}
inline void SceneManager::ClearBeforeScenes()
{
	for (auto& item : *m_deleteScenes) {
		if (item) {
			item->Release();
			delete item;
			item = nullptr;
		}

		system("cls");
	}
	m_deleteScenes->clear();
}

#endif // !___SCENEMANAGER___
