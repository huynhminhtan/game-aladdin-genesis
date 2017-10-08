#pragma once

#include "Header.h"
#include "CAladdinAction.h"

class CAladdinWalk : public CAladdinAction
{
public:
	CAladdinWalk();
	~CAladdinWalk();

	void Init();
	void Release();

	void Activities(STATE, DIRECTION);

private:

	CAnimationSprite*	_AspAladdin;
};