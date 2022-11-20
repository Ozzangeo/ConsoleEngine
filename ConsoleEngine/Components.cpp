#include "Components.h"

using namespace Components;

// [ Camera Component ]
void Camera::Awake() {
	COORD CameraSize = { 128, 72 };
	graphic.SetScreenSize(CameraSize);
	graphic.CameraPos = gameobject->pos;
	graphic.CameraRotate = gameobject->rotate;
}
void Camera::Update() { graphic.Render(); }
void Camera::SetCameraScale	(COORD Scale) { graphic.SetScreenScale(Scale); }
void Camera::SetCameraSize	(COORD Size ) { graphic.SetScreenSize (Size ); }

// [ PolygonRenderer Component ]
void PolygonRenderer::Awake () {
	gameobject->RemoveComponent<SpriteRenderer>();
	vertices.reserve(32);
	edges.reserve(32);
	verticesRealPos.reserve(32);

	vertexCount = 0;
	color = Color_Black;
	isVisible = true;
	isFill = true;
	
	beforePos = new Vector3f;
}
void PolygonRenderer::Update() {
	isUpdateEdge = false;
	
	if (!isVisible || vertexCount <= 0) { return; }
	else { *beforePos = *vertices.front(); }

	Matrix4x4f Trans = graphic.GetTranslate(*gameobject->pos, gameobject->GetRotate(), *gameobject->scale);

	for (unsigned int i = 0; i < vertexCount; i++) {
		if (*vertices[i] != *beforePos) {
			graphic.Line(*vertices[i], *beforePos, Trans, color);

			*beforePos = *vertices[i];
		}
		*verticesRealPos[i] = *vertices[i] * Trans;
	}

	graphic.Line(*vertices[vertexCount - 1], *vertices[0], Trans, color);
}
void PolygonRenderer::Remove() {
	if (beforePos) { delete beforePos; beforePos = nullptr; }

	for (auto& item : vertices) {
		if (item) { delete item; item = nullptr; }
	}
	vertices.clear();
	edges.clear();
	verticesRealPos.clear();
}
Vector3f* PolygonRenderer::AddVertex(float x, float y) {
	Vector3f* ver = new Vector3f(x, y, 0);
	vertices	   .push_back(ver);
	verticesRealPos.push_back(new Vector3f);
	edges		   .push_back(new Vector3f);

	vertexCount++;

	return ver;
}
Vector3f* PolygonRenderer::GetVertex(unsigned int index) {
	return (index >= vertexCount) ? nullptr : vertices[index];
}
void PolygonRenderer::RemoveVertex() {
	if (vertexCount > 0) { 
		int index = --vertexCount;

		if (vertices	   [index]) { delete vertices		[index]; vertices		[index] = nullptr; }
		if (verticesRealPos[index]) { delete verticesRealPos[index]; verticesRealPos[index] = nullptr; }
		if (edges		   [index]) { delete edges			[index]; edges			[index] = nullptr; }

		vertices	   .pop_back();
		verticesRealPos.pop_back();
		edges		   .pop_back();
	}
}
const vector<Vector3f*>& PolygonRenderer::GetEdge() {
	if (isUpdateEdge) { return edges; }
	else {
		// 점이 두개 이상 있을 때
		if (vertexCount >= 2) {
			edgeCount = 0;

			for (unsigned int index = 1; index < vertexCount; index++) {
				*edges[index - 1] = *verticesRealPos[index] - *verticesRealPos[index - 1];
				edgeCount++;
			}

			*edges[edgeCount - 1] = (*verticesRealPos[0] - *verticesRealPos[vertexCount - 1]);
		}

		isUpdateEdge = true;
		return edges;
	}
}

// [ PolygonCollider ]
void PolygonCollider::projectPolygon(Vector3f& axis, PolygonRenderer& polygon, Vector3f* maxmin) {
#define minThis maxmin->x
#define maxThis maxmin->y

	float dp = axis.dotProduct(*polygon.verticesRealPos[0]);
	minThis = dp;
	maxThis = dp;

	for (unsigned int i = 0; i < polygon.vertexCount; i++) {
		dp = polygon.verticesRealPos[i]->dotProduct(axis);
			 if (dp < minThis) { minThis = dp; }
		else if (dp > maxThis) { maxThis = dp; }
	}
}
float PolygonCollider::distance(Vector3f& maxminA, Vector3f& maxminB) {
#define minA maxminA.x
#define maxA maxminA.y
#define minB maxminB.x
#define maxB maxminB.y

	return minA < minB ? minB - maxA : minA - maxB;
}
void PolygonCollider::Awake() {
	Polygon = gameobject->AddComponent<PolygonRenderer>();

}
bool PolygonCollider::isCollision(GameObject* object, float* Distance) {
	if (!object) { return false; }

	PolygonRenderer* poly = object->GetComponent<PolygonRenderer>();
	if (!poly || poly->vertexCount < 0) { return false; }

	Vector3f axis, edge;
	
	float dis = 0.0f;
	bool isCol = true;

	const vector<Vector3f*>& edgeThis = Polygon->GetEdge();
	const vector<Vector3f*>& edgeOther = poly->GetEdge();

	Vector3f This(0), Other(0);

	for (unsigned int edgeindex = 0, edgecount = Polygon->edgeCount + poly->edgeCount; edgeindex < edgecount; edgeindex++) {
		edge =
			edgeindex < Polygon->edgeCount ?
			*edgeThis[edgeindex] :
			*edgeOther[edgeindex - Polygon->edgeCount];

		axis = edge.product2D().normalize();

		projectPolygon(axis, *Polygon, &This);
		projectPolygon(axis, *poly, &Other);

		dis = distance(This, Other);
		if (dis > 0) { isCol = false; break; }
	}
	if (Distance) {
		if (isCol) { *Distance = dis; }
		else	   { *Distance = 0.0f; }
	}

	return isCol;
}
bool PolygonCollider::isCollision(GameObject* object, const Vector3f& velocity) {
	if (!object) { return false; }

	PolygonRenderer* poly = object->GetComponent<PolygonRenderer>();
	if (!poly || poly->vertexCount < 0) { return false; }

	Vector3f axis, edge;

	float velo = 0.0f;
	bool isCol = true;

	const vector<Vector3f*>& edgeThis = Polygon->GetEdge();
	const vector<Vector3f*>& edgeOther = poly->GetEdge();

	Vector3f This(0), Other(0);

	for (unsigned int edgeindex = 0, edgecount = Polygon->edgeCount + poly->edgeCount; edgeindex < edgecount; edgeindex++) {
		edge =
			edgeindex < Polygon->edgeCount ?
			*edgeThis[edgeindex] :
			*edgeOther[edgeindex - Polygon->edgeCount];

		axis = edge.product2D().normalize();


		projectPolygon(axis, *Polygon, &This);
		projectPolygon(axis, *poly, &Other);

		velo = axis.dotProduct(velocity);

		if (velo < 0) { This.x += velo; }
		else { This.y += velo; }

		if (distance(This, Other) > 0) { isCol = false; break; }
	}

	return isCol;
}
bool PolygonCollider::isCollision(list<GameObject*>& objects, float* Distance) {
	float dis = 0.0f;
	bool isCol = true;

	Vector3f axis, edge;
	Vector3f This(0), Other(0);
	for (auto& object : objects) {
		if (!object) { return false; }

		PolygonRenderer* poly = object->GetComponent<PolygonRenderer>();
		if (!poly || poly->vertexCount < 0) { return false; }

		const vector<Vector3f*>& edgeThis = Polygon->GetEdge();
		const vector<Vector3f*>& edgeOther = poly->GetEdge();

		isCol = true;

		for (unsigned int edgeindex = 0, edgecount = Polygon->edgeCount + poly->edgeCount; edgeindex < edgecount; edgeindex++) {
			edge =
				edgeindex < Polygon->edgeCount ?
				*edgeThis[edgeindex] :
				*edgeOther[edgeindex - Polygon->edgeCount];

			axis = edge.product2D().normalize();

			projectPolygon(axis, *Polygon, &This);
			projectPolygon(axis, *poly, &Other);

			dis = distance(This, Other);
			if (dis > 0) { isCol = false; break; }
		}

		if (Distance) {
			if (isCol) { *Distance = dis; return true; }
			else	   { *Distance = 0.0f; }
		}
	}
	
	return false;
}
bool PolygonCollider::isCollision(list<GameObject*>& objects, const Vector3f& velocity) {
	float velo = 0.0f;
	bool isCol = true;

	Vector3f axis, edge;
	Vector3f This(0), Other(0);

	for (auto& object : objects) {
		if (!object) { return false; }

		PolygonRenderer* poly = object->GetComponent<PolygonRenderer>();
		if (!poly || poly->vertexCount < 0) { return false; }

		isCol = true;

		const vector<Vector3f*>& edgeThis = Polygon->GetEdge();
		const vector<Vector3f*>& edgeOther = poly->GetEdge();

		for (unsigned int edgeindex = 0, edgecount = Polygon->edgeCount + poly->edgeCount; edgeindex < edgecount; edgeindex++) {
			edge =
				edgeindex < Polygon->edgeCount ?
				*edgeThis[edgeindex] :
				*edgeOther[edgeindex - Polygon->edgeCount];

			axis = edge.product2D().normalize();


			projectPolygon(axis, *Polygon, &This);
			projectPolygon(axis, *poly, &Other);

			velo = axis.dotProduct(velocity);

			if (velo < 0) { This.x += velo; }
			else { This.y += velo; }

			if (distance(This, Other) > 0) { isCol = false; break; }
		}

		if (isCol) { return true; }
	}

	return false;
}
Vector3f PolygonCollider::isCollisionVec(GameObject* object, const Vector3f& velocity) {
	if (!object) { return false; }

	PolygonRenderer* poly = object->GetComponent<PolygonRenderer>();
	if (!poly || poly->vertexCount < 0) { return false; }

	Vector3f axis, edge;

	float velo = 0.0f;
	bool isCol = true;

	const vector<Vector3f*>& edgeThis = Polygon->GetEdge();
	const vector<Vector3f*>& edgeOther = poly->GetEdge();

	Vector3f This(0), Other(0);

	for (unsigned int edgeindex = 0, edgecount = Polygon->edgeCount + poly->edgeCount; edgeindex < edgecount; edgeindex++) {
		edge =
			edgeindex < Polygon->edgeCount ?
			*edgeThis[edgeindex] :
			*edgeOther[edgeindex - Polygon->edgeCount];

		axis = edge.product2D().normalize();


		projectPolygon(axis, *Polygon, &This);
		projectPolygon(axis, *poly, &Other);

		velo = axis.dotProduct(velocity);

		if (velo < 0) { This.x += velo; }
		else { This.y += velo; }

		if (distance(This, Other) > 0) { isCol = false; break; }
	}

	if (isCol)	{ return Vector3f(0, 0, 0); }
	else		{ return velocity; }
}
Vector3f PolygonCollider::isCollisionVec(list<GameObject*>& objects, const Vector3f& velocity) {
	float velo = 0.0f;
	bool isCol = true;

	Vector3f axis, edge;
	Vector3f This(0), Other(0);

	for (auto& object : objects) {
		if (!object) { return false; }

		PolygonRenderer* poly = object->GetComponent<PolygonRenderer>();
		if (!poly || poly->vertexCount < 0) { return false; }

		isCol = true;

		const vector<Vector3f*>& edgeThis = Polygon->GetEdge();
		const vector<Vector3f*>& edgeOther = poly->GetEdge();

		for (unsigned int edgeindex = 0, edgecount = Polygon->edgeCount + poly->edgeCount; edgeindex < edgecount; edgeindex++) {
			edge =
				edgeindex < Polygon->edgeCount ?
				*edgeThis[edgeindex] :
				*edgeOther[edgeindex - Polygon->edgeCount];

			axis = edge.product2D().normalize();


			projectPolygon(axis, *Polygon, &This);
			projectPolygon(axis, *poly, &Other);

			velo = axis.dotProduct(velocity);

			if (velo < 0) { This.x += velo; }
			else { This.y += velo; }

			if (distance(This, Other) > 0) { isCol = false; break; }
		}

		if (isCol) { return Vector3f(0, 0, 0); }
	}

	return velocity;
}

// [ SpriteRenderer Component ]
void SpriteRenderer::Awake() {
	gameobject->RemoveComponent<PolygonRenderer>();
	isVisible = true;
}
void SpriteRenderer::Update() {
	if (isVisible && sprite.sprite) {
		graphic.DrawSprite(*gameobject->pos, gameobject->GetRotate(), *gameobject->scale, sprite);
	}
}

// [ Animator Component ]
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

// [ Audio Component ]
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
