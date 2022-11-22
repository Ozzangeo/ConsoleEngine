#ifndef _COMPONENTS_
#define _COMPONENTS_

#include "stdafx.h"
#include "GameObjects.h"
#include "Scenes.h"

using namespace std;
using namespace Components;

enum Tags {
	Tag_Camera,
	Tag_Server,
	Tag_NoteSpawner
};
/* DalmaMain */ #pragma region ...
class DownNote : public Component {
private:
	void Update() override;

public:
	float speed = 5.0f;
};
class AmladPlayer : public Component {
private:
/* Effect */ #pragma region ...
	enum EffectType {

	};
#pragma endregion

	class NoteInfo {
	public:
		NoteInfo(float time = 0.0f, int line = 0) : Time(time), Line(line) {}
		float Time;
		int Line;
		list<EffectType> Effects;
	};
	list<NoteInfo> Notes;

	float ExTime;

	void Update() override;

public:
	bool OpenAmlad(wstring path);
};
#pragma endregion

#endif // !_COMPONENTS_
