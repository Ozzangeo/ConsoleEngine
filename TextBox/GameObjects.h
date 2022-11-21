#ifndef _GAMEOBJECTS_
#define _GAMEOBJECTS_

#include "Components.h"

class Box : public GameObject {
private:
	void Components() override;
};

#endif // !_GAMEOBJECTS_