#ifndef _COMPONENTS_
#define _COMPONENTS_

/*
자고 일어나서 할거
1. 노트 인식해서 판정 & 정확도
2. UI 대충 손보기
3. Dalma 메인 만들기
4. PPT 만들기
*/

#include "stdafx.h"
#include "GameObjects.h"
#include "Scenes.h"

using namespace std;
using namespace Components;

enum Tags {
	Tag_Camera,
	Tag_Server,
	Tag_NoteSpawner,
	Tag_Effector,
	Tag_Note,
	Tag_JudgmentLine
};

enum ColorLayer {
	Back = 0,
	GBack,
	GWall,
	GButton,
	GButtonBack,
	GBottom,
	CNote = 14
};

/* DalmaMain */ #pragma region ...
/* Effect */ #pragma region ...
enum EffectType {
	Set_BPM = 'b',
	Gradation = 'g',
	Set_Camera = 'c'
};

class EFunc {
public:
	EffectType EType;
	vector<float> EPara;

	EFunc(EffectType type, vector<float> para) : EType(type), EPara(para) {}
};
class GradationEffect : public Component {
private:
	bool isStart = false;

	float time = 0.0f;
	float maxTime = 0.0f;
	int num = 0;

	Rgb255 StartRGB;
	Rgb255 EndRGB;

	Vector3f* RGBcount;
	Vector3f* RGBcountPlus;
	void Awake() override;
	void Update() override;
	void Remove() override;

public:
	void GradationStart(Rgb255 start, Rgb255 end, float second, int Colornum);
};
class MoveCamera : public Component {
	GameObjects::Camera* camera;
	bool isStart = false;

	float time = 0.0f;
	float maxTime = 0.0f;

	Vector3f* StartPos;
	Vector3f* EndPos;

	Vector3f* PosCount;
	Vector3f* PosCountPlus;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Remove() override;
public:
	void CameraStart(Vector3f start, Vector3f end, float second);
};
#pragma endregion

class NoteInfo {
public:
	NoteInfo(float line = 0, float distance = 0.0f, float time = 0.0f) : Line(line), Distance(distance), Time(time) {}
	float Line;
	float Distance;
	float Time;
	list<EFunc> Effects;
};

class NoteDown : public Component {
private:
	void Update() override;

public:
	static float bpm;
	static float bpm60;
	static float speed;
};
class NoteEffect : public Component {
private:
	PolygonCollider* collider;
	GameObject* target;

	void Start() override;
	void Update() override;

public:
	list<EFunc> effects;
};
class NoteJudgment : public Component {
private:
	bool isHit = false;

	void Update() override;
};
class AmladPlayer : public Component {
private:
	Audio* audio = nullptr;
	Server* server = nullptr;
	string artist;

	bool isStart = false;
	bool isReady = false;

	queue<NoteInfo> Notes;
	float PlayTime = 0.0f;
	float ExTime = 0.0f;

	float multiplespeed = 6.0f;

	void Start() override;
	void Update() override;

public:
	bool OpenAmlad(wstring path);
};
class Filler : public Component {
private:
	void Awake() override;
	void Update() override;
	void Remove() override;

public:
	Vector3f* Start;
	Vector3f* End;
	EnumColor color = Color_White;
};
class GearButtonComp : public Component {
private:
	static KeyCode code[4];

	void Awake();
	void Update();

public:
	EnumColor Color = Color_SkyBlue;
};

#pragma endregion

#endif // !_COMPONENTS_
