#ifndef ___ENGINE___
#define ___ENGINE___

#include "stdafx.h"
#include "Script.h"
#include "Keyboard.h"
#include "Time.h"

using namespace std;
using namespace chrono;

class EngineScript : public Script {
	friend class Engine;
protected:
	Time itme;
	Keyboard itmea;

	bool Awake() override;
	bool Update() override = 0;
	void Remove() override = 0;
};

class Engine {
private:
	Engine();
	Engine(const Engine& other);

	float m_FPS;
	float m_MaxFPS;
	static Engine* m_Instance;

public:
	static Engine* GetInstance();
	static void Release();

	template<typename T, enable_if_t<is_base_of_v<EngineScript, T>, bool> = true> void Run();
	float SetFPS(float _FPS);
};
template<typename T, enable_if_t<is_base_of_v<EngineScript, T>, bool>>
inline void Engine::Run() {
	EngineScript* RunScript = new T;
	bool isNotDone = true;

	if (!RunScript->Awake()) { RunScript->Remove(); return; }

	while (isNotDone) {
		system_clock::time_point start = system_clock::now();
		/////////////Update/////////////

		isNotDone = RunScript->Update();

		////////////////////////////////
		Time::ExecutionTime = duration<float>(system_clock::now() - start).count() * 1000.0f;
		if (m_FPS > Time::ExecutionTime) { Time::Delay(m_FPS - Time::ExecutionTime); }
		Time::DeltaTime = duration<float>(system_clock::now() - start).count();
	}

	RunScript->Remove();
	if (RunScript) { delete RunScript; }
}
#endif // !___ENGINE___

