#ifndef ___CONSOLEENGINE___
#define ___CONSOLEENGINE___

#include "stdafx.h"
#include "SceneManager.h"
#include "Keyboard.h"
#include "Color.h"
#include "Debug.h"
#include "Time.h"
#include "Math.h"
#include "Components.h"
#include "GameObjects.h"

using namespace std;
using namespace chrono;

class ConsoleEngine {
private:
	float m_FPS;
	SceneManager& UpdateScene = SceneManager::GetInstance();

public:
	// 엔진의 생성자
	ConsoleEngine();

	// 엔진 시작
	template<typename T, enable_if_t<is_base_of_v<Scene, T>, bool> = true> void Run(wstring title = L"Engine", int Frame = 60);

	// 엔진 종료
	static void Release();
};
template<typename T, enable_if_t<is_base_of_v<Scene, T>, bool>> inline void ConsoleEngine::Run(wstring title, int Frame) {
	SetConsoleTitle(title.c_str());

	m_FPS = 1000.0f / Frame;

	UpdateScene.ChangeScene<T>();

	int fps = 0;
	float time = -1.0f;
	
	while (SceneManager::isRunning()) {
		system_clock::time_point start = system_clock::now();
		/////////////Update/////////////
		
		// Input Update
		Keyboard::Update();
		
		// Scene Update
		UpdateScene.Update();
		
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
		if (m_FPS > Time::ExecutionTime) { Time::Delay(m_FPS - Time::ExecutionTime); }
		Time::DeltaTime = duration<float>(system_clock::now() - start).count();
	}
	UpdateScene.Release();
}

#endif // !___CONSOLEENGINE___