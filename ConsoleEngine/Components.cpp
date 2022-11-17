#include "Components.h"

using namespace Components;

// [ Camera Component ]
void Camera::Awake () {
	COORD CameraSize = { 128, 72 };
	graphic.SetScreenSize(CameraSize);
	graphic.CameraPos = gameobject->pos;
	graphic.CameraRotate = gameobject->rotate;
}
void Camera::Update() { graphic.Render(); }
void Camera::Remove() {}
void Camera::SetCameraScale	(COORD Scale) { graphic.SetScreenScale(Scale); }
void Camera::SetCameraSize	(COORD Size ) { graphic.SetScreenSize (Size ); }

// [ PolygonRenderer Component ]
void PolygonRenderer::Awake () {
	gameobject->RemoveComponent<SpriteRenderer>();
	vertexs.reserve(16);

	vertexCount = 0;
	color = Color_Black;
	isVisible = true;
	
	beforePos = new Vector3f;
}
void PolygonRenderer::Update() {
	if (!isVisible || vertexs.size() == 0) { return; }
	else { *beforePos = *vertexs.front().second; }

	Matrix4x4f Trans = graphic.GetTranslate(*gameobject->pos, gameobject->GetRotate(), *gameobject->scale);

	for (auto& item : vertexs) {
		if (*item.second != *beforePos) {
			graphic.Line(*item.second, *beforePos, Trans, color);

			*beforePos = *item.second;
		}
	}

	graphic.Line(*vertexs.back().second, *vertexs.front().second, Trans, color);
}
void PolygonRenderer::Remove() {
	if (beforePos) { delete beforePos; beforePos = nullptr; }

	for (auto& item : vertexs) {
		if (item.second) { delete item.second; item.second = nullptr; }
	}
	vertexs.clear();
}
Vector3f* PolygonRenderer::AddVertex(float x, float y) {
	Vector3f* ver = new Vector3f(x, y, 0);
	vertexs.push_back({ ++vertexCount, ver });

	return GetVertex(vertexCount);
}
Vector3f* PolygonRenderer::GetVertex(int index) {
	for (auto& item : vertexs) {
		if (item.first == index) { return item.second; }
	}
	return nullptr;
}
void PolygonRenderer::RemoveVertex() {
	Vector3f* tempv = GetVertex(vertexCount);
	if (tempv) { delete tempv; tempv = nullptr; }
	vertexs.pop_back();
	vertexCount--;
}

// [ SpriteRenderer Component ]
void SpriteRenderer::Awake () {
	gameobject->RemoveComponent<PolygonRenderer>();
	isVisible = true;
}
void SpriteRenderer::Update() {
	if (isVisible && sprite.sprite) {
		graphic.DrawSprite(*gameobject->pos, gameobject->GetRotate(), *gameobject->scale, sprite);
	}
}
void SpriteRenderer::Remove() {}

// [ Animator Component ]
void Animator::Awake () {
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

// [ Audio Component ]
void Audio::Awake () {}
void Audio::Update() {}
void Audio::Remove() {
	for (const SoundInfo Item : SoundList) {
		mciSendCommand(Item.ID, MCI_CLOSE, 0, NULL);
	}
	SoundList.clear();
}
void Audio::LoadAudio(CString path, SoundType Type) {
	switch (Type) {
	case MP3: { AudioType = "mpegvideo"; } break;
	case WAV: { AudioType = "waveaudio"; } break;
	case AVI: { AudioType = "avivideo"; } break;
	}

	mciOpen.lpstrDeviceType = AudioType;
	mciOpen.lpstrElementName = path;
	SoundInfo soundinfo;
	soundinfo.Sound = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpen);
	soundinfo.ID = mciOpen.wDeviceID;

	SoundList.push_back(soundinfo);
}
bool Audio::PlayAudio(UINT ID, bool isLoop) {
	for (SoundInfo Item : SoundList) {
		if (ID == Item.ID) {
			mciSendCommand(ID, MCI_SEEK, MCI_SEEK_TO_START, NULL);
			if (isLoop) { Item.Sound = mciSendCommand(ID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay); }
			else		{ Item.Sound = mciSendCommand(ID, MCI_PLAY, MCI_NOTIFY		   , (DWORD)(LPVOID)&mciPlay); }
			return true;
		}
	}
	return false;
}
void Audio::RePlayAudio(UINT ID) { mciSendCommand(ID, MCI_RESUME, 0, NULL); }
void Audio::PauseAudio (UINT ID) { mciSendCommand(ID, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay); }

// [ PolygonCollider ]
void PolygonCollider::Awake () {}	 
void PolygonCollider::Update() {
	isCol = false;

	for (auto& item : Polygons) {
		// 만약 충돌하지 않는다면
		if (true) { continue; }

		// 만약 충돌했다면
		if (false) { isCol = true; return; }
	}
}	 
void PolygonCollider::Remove() {}
bool PolygonCollider::isCollision() { return isCol; }

void PolygonCollider::AddPolygon	(PolygonRenderer* polygon)	{ Polygons.push_back(polygon); }
void PolygonCollider::RemovePolygon	(PolygonRenderer* polygon)	{ Polygons.remove	(polygon); }
