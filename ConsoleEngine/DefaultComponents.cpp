#include "DefaultComponents.h"

using namespace DefaultComponents;

void Camera::Awake() {
	COORD CameraSize = { 128, 72 };
	graphic.SetScreenSize(CameraSize);
	graphic.CameraPos = &gameobject->pos;
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
}
void PolygonRenderer::Update() {
	Vector4 beforePos;

	if (!isVisible || vertexs.size() == 0) { return; }
	else { beforePos = vertexs.front().second; }

	for (auto& item : vertexs) {
		if (item.second != beforePos) {
			// Line에 좌표 넣기 전에 행렬 연산을 해야할거같음
			graphic.Line(item.second + gameobject->pos, beforePos + gameobject->pos, gameobject->pos.z, color);
			beforePos = item.second;
		}
	}

	graphic.Line(vertexs.back().second + gameobject->pos, vertexs.front().second + gameobject->pos, gameobject->pos.z, color);
}
void PolygonRenderer::Remove() {
	vertexs.clear();
}
Vector4* PolygonRenderer::AddVertex(Vector4 vertex) {
	vertexs.push_back({ ++vertexCount, vertex });

	return GetVertex(vertexCount);
}
Vector4* PolygonRenderer::GetVertex(int index) {
	for (auto& item : vertexs) {
		if (item.first == index) { return &item.second; }
	}
	return nullptr;
}
void PolygonRenderer::RemoveVertex() {
	vertexs.pop_back();
	vertexCount--;
}

void SpriteRenderer::Awake() {
	gameobject->RemoveComponent<PolygonRenderer>();
	isVisible = true;
}
void SpriteRenderer::Update() {
	if (isVisible && sprite.sprite) {
		graphic.DrawSprite(gameobject->pos, sprite);
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
