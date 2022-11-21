#ifndef _SCENES_
#define _SCENES_

#include "GameObjects.h"

enum Tags {
	Tag_TextBox
};

class TextBox : public Scene {
private:
	void GameObjects() override;
};

#endif // !_SCENES_

