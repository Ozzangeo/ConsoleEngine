#ifndef _SCENES_
#define _SCENES_

#include "GameObjects.h"

class DalmaMain : public Scene {
private:
	void GameObjects() override;
};
class DalmaList : public Scene {
private:
	void GameObjects() override;
};
class DalmaCredit : public Scene {
private:
	void GameObjects() override;
};
class Dalma : public Scene {
private:
	void GameObjects() override;
	void Work() override;
};
class DalmaResult : public Scene {
private:
	void GameObjects() override;
};

#endif // !_SCENES_
