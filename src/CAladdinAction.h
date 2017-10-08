#pragma once

//#include "Header.h"

class CAladdinAction
{
public:
	//CAladdinAction();
	//~CAladdinAction();

	virtual void Init() = 0;
	virtual void Release() = 0;

	virtual void Activities(STATE, DIRECTION) = 0;
};