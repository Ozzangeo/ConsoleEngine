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

#ifndef ___ENGINE___
#define ___ENGINE___

#include "stdafx.h"
#include "Scene.h"
#include "Keyboard.h"
#include "Color.h"
#include "Debug.h"
#include "Time.h"
#include "DefaultComponents.h"
#include "DefaultGameObjects.h"

using namespace std;
using namespace chrono;

class Engine {
private:
	float m_FPS;
	bool isDone;

public:
	Engine();

	template<typename T, enable_if_t<is_base_of_v<Scene, T>, bool> = true>
	void Run(wstring title = L"Engine", int Frame = 60);

	static void Release();
};
template<typename T, enable_if_t<is_base_of_v<Scene, T>, bool>>
inline void Engine::Run(wstring title, int Frame) {
	SetConsoleTitle(title.c_str());

	m_FPS = 1000.0f / Frame;

	isDone = false;

	Scene* Scene = new T;
	if (Scene) {
		Scene->Awake();
		Scene->GameObjects();
	}

	int fps = 0;
	float time = -1.0f;

	while (!isDone) {
		system_clock::time_point start = system_clock::now();
		/////////////Update/////////////

		switch (Keyboard::isKey(KeyCode_ESC)) { case KeyType_DOWN: { isDone = true; } break; }
	
		Scene->Update();
		
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

	Scene->Release();
}
#endif // !___ENGINE___