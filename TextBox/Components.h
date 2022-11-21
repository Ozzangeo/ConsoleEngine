#ifndef _COMPONENTS_
#define _COMPONENTS_

#include "stdafx.h"

using namespace std;
using namespace Components;

class Text : public Component {
private:
	Client* client;
	string Message;

	void Awake() override;
	void Start() override;
	void Update() override;
};

#endif // !_COMPONENTS_