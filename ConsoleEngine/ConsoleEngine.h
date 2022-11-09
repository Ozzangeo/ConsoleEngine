// PPT���� ������ ��
// 1. WriteConsoleOutput�� ����Ͽ� ���
// - ���� Dalma������ ���� ��� �ӵ� �� 258% ���
// - ������ ���� ǥ�� ����
// 
// 2. �ܼ��� ������ RGB�� �ٲ� �� ����
// - ���� �ִ� 16���� ǥ�� ����
// - ��ä�ο� ���� ǥ�� ����
// 
// 3. ���̾� �ý��� ���� ( 161 FPS -> 412 FPS )
// - ���� Dalma�������� ���̾ �������� �ð������� �������� ���Գ���
//   �̿� ȭ�� ũ�Ⱑ ũ�� Ŭ ���� �������� ������ �������� ���� �߻�
//   ������ �̷� ������ ���������ν� ������ ũ�� �����
// 
// 4. Component ������ ����Ͽ� Ȯ�强�� ����
// - ����ڰ� ������ �޾� Component�� GameObject�� ��ӹ����� �ٷιٷ� ����� �� ����
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