#include "PlayerClimbAttackState.h"
#include "Player.h"
#include "PlayerClimbVerticalState.h"
#include "PlayerClimbHorizontalIdleState.h"
#include "../../GameComponents/Sound.h"

PlayerClimbAttackState::PlayerClimbAttackState()
{
}

PlayerClimbAttackState::PlayerClimbAttackState(Player * player, GameObject *ropeOrHorizontalBar, PlayerState::StateName fromState) : PlayerState(player, PlayerState::StateName::ClimbAttack)
{
	_ropeOrHorizontalBar = ropeOrHorizontalBar;
	_fromState = fromState;

	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLClimbAttack(), "climb_attack", ResourceManager::GetInstance()->GetTextureClimbAttack(), true, 0.5f));

	_player->SetAccelerationY(0);
	_player->SetVelocityY(0);

	_player->AllowMoveLeft(false);
	_player->AllowMoveRight(false);

	_checkPlussPosition = true;

	Sound::GetInstance()->Play("Low_Sword", 0, 1);

}


PlayerClimbAttackState::~PlayerClimbAttackState()
{
}

void PlayerClimbAttackState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);


	if (_checkPlussPosition &&
		_fromState == PlayerState::StateName::ClimbHorizontalIde)
	{
		_player->SetPositionY(_player->GetPosition().y - 7);

		_checkPlussPosition = false;
	}

	if (_animation->IsFinish())//change state
	{
		if (_fromState == PlayerState::StateName::ClimbVertical)
			_player->SetState(new PlayerClimbVerticalState(_player, _ropeOrHorizontalBar));
		else if (_fromState == PlayerState::StateName::ClimbHorizontalIde)
			_player->SetState(new PlayerClimbHorizontalIdleState(_player, _ropeOrHorizontalBar), false);
		return;
	}
}
