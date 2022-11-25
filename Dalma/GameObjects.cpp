#include "GameObjects.h"

/* Dalma */#pragma region ...

void ServerObject::Components() {

	auto* server = AddComponent<Server>();
	server->OpenServer(3197);
}
const float Note::Width = 3.0f;
void Note::Components() {
	AddComponent<NoteDown>();
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
	scene->AddGameObject<PerfectLine>(L"Perfect", Tag_Perfect);
	scene->AddGameObject<GreatLine>(L"Great", Tag_Great);
	scene->AddGameObject<MissLine>(L"Miss", Tag_Miss);
	*scene->AddGameObject<Line>(L"Line", Tag_Line)->pos = Vector3f(0, 15, 1);

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

void PerfectLine::Components() {
	float width = Note::Width * 4;
	auto* polygon = AddComponent<PolygonRenderer>();
	polygon->AddVertex(width + 2, length);
	polygon->AddVertex(-width - 2, length);
	polygon->AddVertex(-width - 2, -length);
	polygon->AddVertex(width + 2, -length);
	polygon->isVisible = false;
}
void PerfectLine::Work() {
	*pos = Vector3f(0, 20, 1);
}

void GreatLine::Components() {
	float width = Note::Width * 4;
	auto* polygon = AddComponent<PolygonRenderer>();
	polygon->AddVertex(width + 2, length);
	polygon->AddVertex(-width - 2, length);
	polygon->AddVertex(-width - 2, -length);
	polygon->AddVertex(width + 2, -length);
	polygon->isVisible = false;
}
void GreatLine::Work() {
	*pos = Vector3f(0, 20, 1);
}

void MissLine::Components() {
	float width = Note::Width * 4;
	auto* polygon = AddComponent<PolygonRenderer>();
	polygon->AddVertex(width + 2, length);
	polygon->AddVertex(-width - 2, length);
	polygon->AddVertex(-width - 2, -length);
	polygon->AddVertex(width + 2, -length);
	polygon->isVisible = false;
}
void MissLine::Work() {
	*pos = Vector3f(0, 20, 1);
}

void Line::Components() {
	auto* polygon = AddComponent<PolygonRenderer>();
	polygon->AddVertex(2, 0);
	polygon->AddVertex(-2, 0);
	polygon->color = Color_Blue;
}

#pragma endregion

void Num::Components() {
	AddComponent<SpriteNum>();
}

void Arrow::Components() {
	AddComponent<ChoiceComp>();
	auto* sprite = AddComponent<SpriteRenderer>();
	sprite->sprite.LoadSprite("Sprites/Arrow");
}
