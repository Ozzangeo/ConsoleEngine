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
	Tag_JudgmentLine,
	Tag_Perfect,
	Tag_Great,
	Tag_Miss,
	Tag_Line
};

enum ColorLayer {
	Back = 0,
	GBack,
	GWall,
	GButton,
	GButtonBack,
	GBottom,
	JPerfect = 11,
	JGreat,
	JMiss,
	CNote
};
class SpriteNum : public Component {
private:
	SpriteRenderer* renderer;
	Sprite nums[10];

	void Start() override;
public:
	void ChangeNum(int num);
};

/* DalmaMain */ #pragma region ...
class ChoiceComp : public Component {
private:
	SceneManager* manager;
	PolygonRenderer* renderer;
	int choice = 0;

	void Awake() override;
	void Update() override;
public:
	int max = 3;
};

#pragma endregion
/* Dalma */ #pragma region ...
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

	Vector3f* RGBcount = nullptr;
	Vector3f* RGBcountPlus = nullptr;
	void Awake() override;
	void Update() override;
	void Remove() override;

public:
	void GradationStart(Rgb255 start, Rgb255 end, float second, int Colornum);
};
class MoveCamera : public Component {
	GameObjects::Camera* camera = nullptr;
	bool isStart = false;

	float time = 0.0f;
	float maxTime = 0.0f;

	Vector3f* StartPos = nullptr;
	Vector3f* EndPos = nullptr;

	Vector3f* PosCount = nullptr;
	Vector3f* PosCountPlus = nullptr;

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
	bool isHit = false;

	static float bpm;
	static float bpm60;
	static float speed;
};
class NoteEffect : public Component {
private:
	bool isEnd = false;
	PolygonCollider* collider = nullptr;
	GameObject* target = nullptr;

	void Start() override;
	void Update() override;

public:
	void UpdateNow();

	list<EFunc> effects;
};
class NoteJudgment : public Component {
private:
	GameObject* objects[3];
	PolygonRenderer* renderer;

	PolygonCollider* collider;
	NoteDown* noteDown;

	void Start();
	void Update();

public:
	NoteEffect* noteEffect;
	KeyCode code;
};

class AmladPlayer : public Component {
private:
	SpriteNum* Nums[3];
	Audio* audio = nullptr;
	string artist;
	
	bool isStart = false;
	bool isReady = false;
	bool isEnd = false;

	chrono::system_clock::time_point start;

	queue<NoteInfo> Notes;
	float PlayTime = 0.0f;
	float ExTime = 0.0f;

	float multiplespeed = 6.0f;

	void Start() override;
	void Update() override;
	void Remove() override;

	void OutResult();

public:
	static wstring path;
	static int Perfect;
	static int Great;
	static int Miss;
	static int Combo;
	static int MaxCombo;

	bool OpenAmlad(wstring path);
	bool OpenAmlad();
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
	void Update();

public:
	static KeyCode code[4];
	EnumColor Color = Color_SkyBlue;
};

#pragma endregion
/* Dalma Result */ #pragma region ...
class Result : public Component {
private:
	SpriteNum* nums[3];

	bool isDone = false;

	float nowPerfect = 0.0f;
	float nowGreat = 0.0f;
	float nowMiss = 0.0f;
	float nowCombo = 0.0f;
	float nowAvg = 0.0f;

	string artist;
	float perfect;
	float great;
	float miss;
	float avg;
	float maxCombo;

	void Start() override;
	void Update() override;
};

#pragma endregion


#endif // !_COMPONENTS_
