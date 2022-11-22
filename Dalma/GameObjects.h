#ifndef _GAMEOBJECTS_
#define _GAMEOBJECTS_

#include "Components.h"

using namespace std;
using namespace Components;
/* Dalma Main */ #pragma region ...
class ServerObject : public GameObject {
private:
	void Components() override;
};
class Note : public GameObject {
private:
	void Components() override;
};
class NoteSpawner : public GameObject {
private:
	void Components() override;
};
#pragma endregion

#endif // !_GAMEOBJECTS_
