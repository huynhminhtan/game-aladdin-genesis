#pragma once

#include "PlayerState.h"

class PlayerDamageState : public PlayerState
{
public:
	PlayerDamageState();
	PlayerDamageState(Player* player);
	~PlayerDamageState();

	void Update(float deltaTime);
};

