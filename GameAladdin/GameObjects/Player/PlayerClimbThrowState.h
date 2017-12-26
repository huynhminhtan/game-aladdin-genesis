#pragma once

#include "PlayerState.h"

class PlayerClimbThrowState : public PlayerState
{
private:
	bool _isCreatedAppleWeapon;
	GameObject *_ropeOrHorizontalBar;
	PlayerState::StateName _fromState;
public:
	PlayerClimbThrowState();
	PlayerClimbThrowState(Player* player, GameObject *ropeOrHorizontalBar, PlayerState::StateName fromState);
	~PlayerClimbThrowState();

	void Update(float deltaTime);
};

