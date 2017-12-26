#pragma once
#pragma once

#include "PlayerState.h"

class PlayerUpState : public PlayerState
{
public:
	PlayerUpState();
	PlayerUpState(Player* player);
	~PlayerUpState();

	void Update(float deltaTime);
};

