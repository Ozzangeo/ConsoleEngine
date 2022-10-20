#ifndef ___SCRIPT___
#define ___SCRIPT___

#include "stdafx.h"

class Script {
protected:
	virtual bool Awake() = 0;
	virtual bool Update() = 0;
	virtual void Remove() = 0;
};

#endif // !___SCRIPT___
