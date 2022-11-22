#include "Scenes.h"

void DalmaMain::GameObjects() {
	auto* camera = AddGameObject<GameObjects::Camera>(L"Camera", Tag_Camera);
	auto* cameracomp = camera->GetComponent<Components::Camera>();
	if (cameracomp) { cameracomp->SetCameraScale(8); }

	auto* spawner = AddGameObject<NoteSpawner>(L"Spawner", Tag_NoteSpawner);

	auto* server = AddGameObject<ServerObject>(L"Server", Tag_Server);
}