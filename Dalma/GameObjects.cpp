#include "GameObjects.h"

void ServerObject::Components() {

	auto* server = AddComponent<Server>();
	server->OpenServer(3197);
}
void Note::Components() {
	auto* note = AddComponent<DownNote>();
	note->speed = 20.0f;

	auto* polygon = AddComponent<Components::PolygonRenderer>();
	polygon->AddVertex(2, 0);
	polygon->AddVertex(-2, 0);
}

void NoteSpawner::Components() {
	auto* amlad = AddComponent<AmladPlayer>();
	amlad->OpenAmlad(L"TestMap");
}
