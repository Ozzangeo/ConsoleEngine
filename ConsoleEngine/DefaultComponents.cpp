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

void SpriteRenderer::Awake() {
	vertexCount = 0;
	color = Color_Black;
	isVisible = true;
}
void SpriteRenderer::Update() {
	Vector4 beforePos;

	if (!isVisible || vertexs.size() == 0) { return; }
	else { beforePos = vertexs.front().second; }

	for (auto& item : vertexs) {
		if (item.second != beforePos) {
			// Line�� ��ǥ �ֱ� ���� ��� ������ �ؾ��ҰŰ���
			graphic.Line(item.second, beforePos, color);
			beforePos = item.second;
		}
	}

	graphic.Line(vertexs.back().second, vertexs.front().second, color);
}
void SpriteRenderer::Remove() {
	vertexs.clear();
}
Vector4* SpriteRenderer::AddVertex(Vector4 vertex) {
	vertexs.push_back({ ++vertexCount, vertex });

	return GetVertex(vertexCount);
}
Vector4* SpriteRenderer::GetVertex(int index) {
	for (auto& item : vertexs) {
		if (item.first == index) { return &item.second; }
	}
	return nullptr;
}
void SpriteRenderer::RemoveVertex() {
	vertexs.pop_back();
	vertexCount--;
}