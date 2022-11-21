#ifndef _COMPONENTS_
#define _COMPONENTS_

#include "stdafx.h"

using namespace std;
using namespace Components;

enum Tags {
	Tag_Camera,
	Tag_Rectangle,
	Tag_Circle,
	Tag_Server
};

class Mover : public Component {
private:
	Server* server;
	Vector3f* move;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Remove() override;

public:
	float speed = 50.0f;
};
class DownNote : public Component {
private:
	void Update() override;

public:
	float speed = 5.0f;
};

#endif // !_COMPONENTS_
