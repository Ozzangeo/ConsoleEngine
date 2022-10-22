#ifndef ___ENGINE___
#define ___ENGINE___

#include "stdafx.h"
#include "Script.h"
#include "Keyboard.h"
#include "Camera2D.h"
#include "Color.h"
#include "Field2D.h"
#include "ThreadPool.h"
#include "Time.h"

using namespace std;
using namespace chrono;

class EngineScript : public Script {
	friend class Engine;
protected:

	bool Awake() override;
	bool Update() override = 0;
	void Remove() override = 0;
};
class Engine {
private:
	Engine();
	Engine(const Engine& other);

	float m_FPS;

	ThreadPool* m_Thread = ThreadPool::GetInstance();
	Camera2D* m_Camera = Camera2D::GetInstance();
	Color* m_Color = Color::GetInstance();

	static bool isNotDone;
	static Engine* m_Instance;
	EngineScript* m_RunScript;

	CONSOLE_FONT_INFOEX m_Console_Font_Infoex;

public:
	~Engine();

	static Engine* GetInstance();

	void Fixing();
	void FontSetting(Vector2<SHORT> FontSize);
	static void Release();

	template<typename T, int Frame = 60, enable_if_t<is_base_of_v<EngineScript, T>, bool> = true>
	void Run(wstring title = L"Engine");
};

template<typename T, int Frame, enable_if_t<is_base_of_v<EngineScript, T>, bool>>
inline void Engine::Run(wstring title) {
	SetConsoleTitle(title.c_str());

	m_FPS = 1000.0f / Frame;

	m_RunScript = new T;
	isNotDone = true;

	m_Thread->EnqueueJob([&]() { Fixing(); });

	if (!m_RunScript->Awake()) { m_RunScript->Remove(); return; }

	ofstream out("Frame.txt");
	while (isNotDone) {
		system_clock::time_point start = system_clock::now();
		/////////////Update/////////////

		isNotDone = m_RunScript->Update();
		m_Camera->Render();

		out << 1.0f / Time::GetDeltaTime() << '\n';

		////////////////////////////////
		Time::ExecutionTime = duration<float>(system_clock::now() - start).count() * 1000.0f;
		if (m_FPS > Time::ExecutionTime) { Time::Delay(m_FPS - Time::ExecutionTime); }
		Time::DeltaTime = duration<float>(system_clock::now() - start).count();
	}
	out.close();

	m_RunScript->Remove();

	Engine::Release();
	Camera2D::Release();
	Keyboard::Release();
	Color::Release();
	ThreadPool::Release();
}

#endif // !___ENGINE___
