#include "Components.h"

using namespace Components;

void Camera::Awake() {
	COORD CameraSize = { 128, 72 };
	graphic.SetScreenSize(CameraSize);
	graphic.CameraPos = gameobject->pos;
	graphic.CameraRotate = gameobject->rotate;
}
void Camera::Update() {
	graphic.Render();
}
void Camera::Remove() {
	
}
void Camera::SetCameraScale(COORD Scale) {
	graphic.SetScreenScale(Scale);
}
void Camera::SetCameraSize(COORD Size) {
	graphic.SetScreenSize(Size);
}

void PolygonRenderer::Awake() {
	gameobject->RemoveComponent<SpriteRenderer>();

	vertexCount = 0;
	color = Color_Black;
	isVisible = true;
	
	start = new Vector4f;
	end = new Vector4f;
	beforePos = new Vector4f;
}
void PolygonRenderer::Update() {

	if (!isVisible || vertexs.size() == 0) { return; }
	else { *beforePos = *vertexs.front().second; }

	Matrix4x4f Trans = Math::GetRotateMatrix(gameobject->GetRotate()) * Math::GetScaleMatrix(*gameobject->scale);

	for (auto& item : vertexs) {
		if (*item.second != *beforePos) {
			*start = (*item.second * Trans) + *gameobject->pos;
			*end   = ( *beforePos  * Trans) + *gameobject->pos;

			graphic.Line(*start, *end, color);

			*beforePos = *item.second;
		}
	}
	*start = (*vertexs. back().second * Trans) + *gameobject->pos;
	*end   = (*vertexs.front().second * Trans) + *gameobject->pos;

	graphic.Line(*start, *end, color);
}
void PolygonRenderer::Remove() {
	if (start) { delete start; start = nullptr; }
	if (end) { delete end; end = nullptr; }
	if (beforePos) { delete beforePos; beforePos = nullptr; }

	for (auto& item : vertexs) {
		if (item.second) { delete item.second; item.second = nullptr; }
	}
	vertexs.clear();
}
Vector4f* PolygonRenderer::AddVertex(float x, float y) {
	Vector4f* ver = new Vector4f(x, y, 0);
	vertexs.push_back({ ++vertexCount, ver });

	return GetVertex(vertexCount);
}
Vector4f* PolygonRenderer::GetVertex(int index) {
	for (auto& item : vertexs) {
		if (item.first == index) { return item.second; }
	}
	return nullptr;
}
void PolygonRenderer::RemoveVertex() {
	Vector4f* tempv = GetVertex(vertexCount);
	if (tempv) { delete tempv; tempv = nullptr; }
	vertexs.pop_back();
	vertexCount--;
}

void SpriteRenderer::Awake() {
	gameobject->RemoveComponent<PolygonRenderer>();
	isVisible = true;
}
void SpriteRenderer::Update() {
	if (isVisible && sprite.sprite) {
		graphic.DrawSprite(*gameobject->pos, gameobject->GetRotate(), *gameobject->scale, sprite);
	}
}
void SpriteRenderer::Remove() {}

void Animator::Awake() {
	spriterenderer = gameobject->AddComponent<SpriteRenderer>();
	
	time = 0.0f;
	index = 0;
}
void Animator::Update() {
#define animations animation.animations
	if (animations.empty()) { return; }

	if (time >= animations[index].first) {
		time -= animations[index].first;
		spriterenderer->sprite = animations[index].second;

		if (++index >= animations.size()) { index = 0; }
	}
	else {
		spriterenderer->sprite = animations[index].second;
		time += Time::GetDeltaTime();
	}
}
void Animator::Remove() {}
