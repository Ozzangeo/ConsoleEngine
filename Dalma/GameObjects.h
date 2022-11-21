#ifndef _GAMEOBJECTS_
#define _GAMEOBJECTS_

#include "Components.h"

using namespace std;
using namespace Components;

class ServerObject : public GameObject {
private:
	void Components() override;
};

#endif // !_GAMEOBJECTS_
