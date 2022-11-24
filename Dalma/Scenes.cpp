#include "Scenes.h"

void DalmaMain::GameObjects() {
	AddGameObject<ServerObject>(L"Server", Tag_Server);
	AddGameObject<GameObjects::Camera>(L"Camera", Tag_Camera);
	AddGameObject<NoteSpawner>(L"Spawner", Tag_NoteSpawner);
	AddGameObject<NoneObject>(L"Effector", Tag_Effector);

	AddGameObject<Gear>(L"Gear");
}

void DalmaMain::Work() {
	auto* spawner = GetGameObject<NoteSpawner>(Tag_NoteSpawner);
	spawner->GetComponent<AmladPlayer>()->OpenAmlad(L"TestMap");

	auto* camera = GetGameObject<GameObjects::Camera>(Tag_Camera)->GetComponent<Components::Camera>();
	camera->SetCameraScale(8);

	auto* jug = GetGameObject<JudgmentLine>(Tag_JudgmentLine);
}
