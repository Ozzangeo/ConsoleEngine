#include "GameObjects.h"

void ServerObject::Components() {

	auto* server = AddComponent<Server>();
	server->OpenServer(3197);
}
const float Note::Width = 3.0f;
void Note::Components() {
	AddComponent<DownNote>();
	AddComponent<Components::PolygonRenderer>();
	AddComponent<Components::PolygonCollider>();
}
void Note::Work() {
	auto* polygon = GetComponent<Components::PolygonRenderer>();
	polygon->AddVertex(Width, 1);
	polygon->AddVertex(-Width + 1, 1);
	polygon->AddVertex(-Width + 1, 0);
	polygon->AddVertex(Width, 0);
	polygon->color = Color_LightYellow;
}

void NoneObject::Components() {}
void NoteSpawner::Components() {
	auto* amlad = AddComponent<AmladPlayer>();
}
void Gear::Components() {
	scene->AddGameObject<GearBackground>(L"Backs");
	scene->AddGameObject<JudgmentLine>(L"Judgment", Tag_JudgmentLine);
	*scene->AddGameObject<GearWall>(L"Wall1")->pos = Vector3f(Note::Width * 5 + 1, 0, 5);
	*scene->AddGameObject<GearWall>(L"Wall2")->pos = Vector3f(-Note::Width * 5 - 1, 0, 5);
	scene->AddGameObject<GearButton>(L"GButton");
}
float* JudgmentLine::PosY = nullptr;
void JudgmentLine::Components() {
	float width = Note::Width * 4;
	auto* polygon = AddComponent<Components::PolygonRenderer>();
	polygon->AddVertex(width + 2, 0);
	polygon->AddVertex(-width - 2, 0);

	pos->y = 20;
	PosY = &pos->y;
}
void GearBackground::Components() {
	Color color;
	color.SetColor({ 100, 100, 100 }, GBack);

	float width = Note::Width * 4;
	auto* polygon = AddComponent<Components::PolygonRenderer>();
	polygon->AddVertex(width + 2, 35);
	polygon->AddVertex(-width - 2, 35);
	polygon->AddVertex(-width - 2, -36);
	polygon->AddVertex(width + 2, -36);
	polygon->color = Color_Blue;

	auto* fill = AddComponent<Filler>();
	*fill->Start = *polygon->GetVertex(3);
	*fill->End = *polygon->GetVertex(1);
	fill->color = polygon->color;

	*pos = Vector3f(0, 0, -10);
}
void GearWall::Components() {
	Color color;
	color.SetColor({ 51, 51, 102 }, GWall);

	float point = 1.0f;
	auto* polygon = AddComponent<Components::PolygonRenderer>();
	polygon->AddVertex(point, 35);
	polygon->AddVertex(-point, 35);
	polygon->AddVertex(-point, -36);
	polygon->AddVertex(point, -36);
	polygon->color = Color_Green;

	auto* fill = AddComponent<Filler>();
	*fill->Start = *polygon->GetVertex(3);
	*fill->End = *polygon->GetVertex(1);
	fill->color = polygon->color;
}
void GearButton::Components() {
	AddComponent<GearButtonComp>();
}
