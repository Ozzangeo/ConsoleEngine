#ifndef ___SCENEMANAGER___
#define ___SCENEMANAGER___

#include "stdafx.h"
#include "Scene.h"

class SceneManager {
private:
	Scene* nowScene = nullptr;
	SceneManager() {}
	SceneManager(const SceneManager& ref) {}

	static SceneManager* m_Instance;

public:
	~SceneManager();
	static SceneManager& GetInstance();
	
	void Update();
	static void Release();

	template<typename T, enable_if_t<is_base_of_v<Scene, T>, bool> = true>
	void ChangeScene();
	Scene* GetNowScene();
};

#endif // !___SCENEMANAGER___

template<typename T, enable_if_t<is_base_of_v<Scene, T>, bool>>
inline void SceneManager::ChangeScene() {
	if (nowScene) { nowScene->isEnd; }

	nowScene = new T;
	nowScene->Awake();
}
