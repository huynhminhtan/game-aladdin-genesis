#pragma once

#include "PlayerState.h"

class PlayerClimbThrowState : public PlayerState
{
private:
	bool _isCreatedAppleWeapon;
	GameObject *_ropeOrHorizontalBar;
	PlayerState::StateName _fromState;

	bool _checkPlussPosition;

public:
	PlayerClimbThrowState();
	PlayerClimbThrowState(Player* player, GameObject *ropeOrHorizontalBar, PlayerState::StateName fromState);
	~PlayerClimbThrowState();

	void Update(float deltaTime);
};

