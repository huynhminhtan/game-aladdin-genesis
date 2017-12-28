#pragma once

#include "PlayerState.h"

class PlayerClimbAttackState : public PlayerState
{
private:
	PlayerState::StateName _fromState;
	GameObject *_ropeOrHorizontalBar;

	bool _checkPlussPosition;
public:
	PlayerClimbAttackState();
	PlayerClimbAttackState(Player* player, GameObject *ropeOrHorizontalBar, PlayerState::StateName fromState);
	~PlayerClimbAttackState();

	void Update(float deltaTime);
};

