#ifndef _SCENES_
#define _SCENES_

#include "GameObjects.h"

enum Tag {
	Tag_Camera,
	Tag_Rectangle,
	Tag_Circle
};
class Dalma : public Scene {
private:
	void GameObjects() override;
};

#endif // !_SCENES_
