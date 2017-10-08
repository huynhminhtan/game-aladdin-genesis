#pragma once

#include "Header.h"
#include "CAladdinStand.h"
#include "CAladdinWalk.h"

class CAladdin
{
public:
	CAladdin();
	~CAladdin();

	void Init();
	void Release();

	// void setAction
	//void SetActionCurrent(CAladdinAction*);

	// call Activities
	void Activities(STATE, DIRECTION);

private:

	//CAladdinAction* _ActionCurrent;

	CAladdinAction* _Action[2];			// at the point time, It is two.
};