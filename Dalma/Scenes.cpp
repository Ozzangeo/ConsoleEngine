#include "Scenes.h"

void DalmaMain::GameObjects() {
	auto* camera = AddGameObject<GameObjects::Camera>(L"Camera", Tag_Camera);
	auto* cameracomp = camera->GetComponent<Components::Camera>();
	if (cameracomp) { cameracomp->SetCameraScale(8); }

	auto* rect = AddGameObject<GameObjects::Rectangle>(L"Rectangle", Tag_Rectangle);
	auto* circle = AddGameObject<GameObjects::Circle>(L"Circle", Tag_Circle);
	circle->AddComponent<Mover>();

	auto* server = AddGameObject<ServerObject>(L"Server", Tag_Server);
}