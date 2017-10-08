#pragma once

#include "Header.h"
#include "CAladdinAction.h"

class CAladdinStand :public CAladdinAction
{
public:
	CAladdinStand();
	~CAladdinStand();

	void Init();
	void Release();

	void Activities(STATE, DIRECTION);

private:

	CAnimationSprite*	_AspAladdin;
};