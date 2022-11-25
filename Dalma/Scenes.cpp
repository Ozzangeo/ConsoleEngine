#include "Scenes.h"

void DalmaMain::GameObjects() {
	auto* camera = AddGameObject<GameObjects::Camera>(L"Camera", Tag_Camera);
	auto* camComp = camera->GetComponent<Components::Camera>();
	camComp->SetCameraScale(8, 16);
	camComp->SetCameraSize({ 128, 36 });

	// 나를 위해 와리 한판

	auto* sprite = AddGameObject<NoneObject>(L"Banner")->AddComponent<SpriteRenderer>();
	sprite->sprite.LoadSprite("Sprites/DalmaBanner");
	sprite->GetGameObject()->pos->y = -5;
	
	auto* arrow = AddGameObject<Arrow>(L"Arrow");
	arrow->pos->x = 5;
}
void Dalma::GameObjects() {
	AddGameObject<ServerObject>(L"Server", Tag_Server);
	AddGameObject<GameObjects::Camera>(L"Camera", Tag_Camera);
	AddGameObject<NoteSpawner>(L"Spawner", Tag_NoteSpawner);
	AddGameObject<NoneObject>(L"Effector", Tag_Effector);
	*AddGameObject<Num>(L"100")	->pos = Vector3f(-6, -20, 0);
	*AddGameObject<Num>(L"10")	->pos = Vector3f( 0, -20, 0);
	*AddGameObject<Num>(L"1")	->pos = Vector3f( 6, -20, 0);

	AddGameObject<Gear>(L"Gear");
}
void Dalma::Work() {
	Color color;

	//color.SetColor(, GButton); 얘는 원래 색상이 예뻐서 건들일 필요 없을듯
	color.SetColor({ 51, 51, 51 }, GButtonBack);
	color.SetColor({ 102, 102, 153 }, GBottom);
	color.SetColor({ 102, 255, 102 }, JPerfect);
	color.SetColor({ 255, 255, 153 }, JGreat);
	color.SetColor({ 255, 51, 51 }, JMiss);
	color.SetColor({ 255, 204, 255 }, CNote);

	auto* spawner = GetGameObject<NoteSpawner>(Tag_NoteSpawner);
	AmladPlayer::path = L"TestMap";
	spawner->GetComponent<AmladPlayer>()->OpenAmlad();

	auto* camera = GetGameObject<GameObjects::Camera>(Tag_Camera)->GetComponent<Components::Camera>();
	camera->SetCameraScale(8);
	camera->SetCameraSize({ 128, 72 });

	auto* jug = GetGameObject<JudgmentLine>(Tag_JudgmentLine);
}

void DalmaResult::GameObjects() {
	auto* camera = AddGameObject<GameObjects::Camera>(L"Camera");
	auto* camComp = camera->GetComponent<Components::Camera>();
	camComp->SetCameraScale(16, 32);
	camComp->SetCameraSize({ 64, 18 });

	auto* result = AddGameObject<NoneObject>(L"Result");
	auto* resComp = result->AddComponent<Result>();

	*AddGameObject<Num>(L"100")	->pos = Vector3f(14, -2, 0);
	*AddGameObject<Num>(L"10")	->pos = Vector3f(20, -2, 0);
	*AddGameObject<Num>(L"1")	->pos = Vector3f(26, -2, 0);
}

void DalmaList::GameObjects()
{
}

void DalmaCredit::GameObjects()
{
}
