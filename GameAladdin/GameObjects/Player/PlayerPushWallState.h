#pragma once

#include "PlayerState.h"

class PlayerPushWallState :public PlayerState
{
public:
	PlayerPushWallState();
	PlayerPushWallState(Player* player);
	~PlayerPushWallState();

	void Update(float deltaTime);
};

