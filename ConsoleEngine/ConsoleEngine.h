// PPT에서 강조할 점
// 1. WriteConsoleOutput를 사용하여 출력
// - 이전 Dalma엔진에 비해 출력 속도 약 258% 상승
// - 빠르게 색상 표현 가능
// 
// 2. 콘솔의 색상을 RGB로 바꿀 수 있음
// - 동시 최대 16색상 표현 가능
// - 다채로운 색상 표현 가능
// 
// 3. 레이어 시스템 삭제 ( 161 FPS -> 412 FPS )
// - 이전 Dalma엔진에서 레이어가 합쳐지는 시간때문에 프레임이 낮게나옴
//   이에 화면 크기가 크면 클 수록 프레임이 곱절로 떨어지는 현상 발생
//   하지만 이런 과정을 생략함으로써 성능이 크게 상승함
// 
// 4. Component 패턴을 사용하여 확장성을 넓힘
// - 사용자가 엔진을 받아 Component와 GameObject만 상속받으면 바로바로 사용할 수 있음
//

#ifndef ___CONSOLEENGINE___
#define ___CONSOLEENGINE___

#include "stdafx.h"
#include "Scene.h"
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
	bool isDone;
	Scene* nowScene;

public:
	ConsoleEngine();

	template<typename T, enable_if_t<is_base_of_v<Scene, T>, bool> = true> void ChangeScene();
	template<typename T, enable_if_t<is_base_of_v<Scene, T>, bool> = true> void Run(wstring title = L"Engine", int Frame = 60);

	static void Release();
};
template<typename T, enable_if_t<is_base_of_v<Scene, T>, bool>> inline void ConsoleEngine::ChangeScene() {
	if(nowScene) {
		nowScene->Release();
		delete nowScene;
	}
	nowScene = new T;
	nowScene->Engine = this;
	
	nowScene->Awake();
}
template<typename T, enable_if_t<is_base_of_v<Scene, T>, bool>> inline void ConsoleEngine::Run(wstring title, int Frame) {
	SetConsoleTitle(title.c_str());

	m_FPS = 1000.0f / Frame;

	isDone = false;

	ChangeScene<T>();
	
	int fps = 0;
	float time = -1.0f;
	
	while (!isDone) {
		system_clock::time_point start = system_clock::now();
		/////////////Update/////////////
		
		Keyboard::Update();
		switch (Keyboard::isKey(KeyCode_ESC)) { case KeyType_DOWN: { isDone = true; } break; }

		nowScene->Update();
		
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
		if (m_FPS > Time::ExecutionTime) { /*Time::Delay(m_FPS - Time::ExecutionTime);*/ }
		Time::DeltaTime = duration<float>(system_clock::now() - start).count();
	}

	nowScene->Release();
}
#endif // !___CONSOLEENGINE___