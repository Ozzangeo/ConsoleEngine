#ifndef _GAMEOBJECTS_
#define _GAMEOBJECTS_

#include "Components.h"

using namespace std;
using namespace Components;

/* Dalma Main */ #pragma region ...
class NoneObject : public GameObject {
private:
	void Components() override;
};
class Note : public GameObject {
private:
	void Components() override;
	void Work() override;

public:
	const static float Width;
};
class NoteSpawner : public GameObject {
private:
	void Components() override;
};
class Gear : public GameObject {
private:
	void Components() override;
};
class GearBackground : public GameObject {
private:
	void Components() override;
};
class GearWall : public GameObject {
private:
	void Components() override;
};
class GearButton : public GameObject {
private:
	void Components() override;
};
class JudgmentLine : public GameObject {
private:
	void Components() override;
public:
	static float* PosY;
};
class ServerObject : public GameObject {
private:
	void Components() override;
};

#pragma endregion

#endif // !_GAMEOBJECTS_
