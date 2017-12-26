#include "PlayerClimbHorizontalIdleState.h"
#include "Player.h"
#include "PlayerClimbHorizontalMoveState.h"
#include "PlayerClimbAttackState.h"
#include "PlayerFallState.h"
#include "PlayerClimbThrowState.h"

PlayerClimbHorizontalIdleState::PlayerClimbHorizontalIdleState()
{
}

PlayerClimbHorizontalIdleState::PlayerClimbHorizontalIdleState(Player * player, GameObject *horizontalBar) : PlayerState(player, PlayerState::StateName::ClimbHorizontalIde)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "ClimbHorizontalIde", ResourceManager::GetInstance()->GetTextureAladdin(), true, 1.8f));

	_player->SetAccelerationY(0);
	_player->SetVelocityY(0);

	//fix position when jump over height
	_horizontalBar = horizontalBar;
	_player->SetPositionY(_horizontalBar->GetBound().top + _player->GetHeight() / 2.0f);
}


PlayerClimbHorizontalIdleState::~PlayerClimbHorizontalIdleState()
{
}

void PlayerClimbHorizontalIdleState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	//change state
	if (_player->GetVelocity().x != 0)
	{
		_player->SetState(new PlayerClimbHorizontalMoveState(_player, _horizontalBar));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_X))
	{
		_player->SetState(new PlayerClimbAttackState(_player, _horizontalBar, PlayerState::StateName::ClimbHorizontalIde));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_Z))
	{
		_player->SetState(new PlayerClimbThrowState(_player, _horizontalBar, PlayerState::StateName::ClimbHorizontalIde));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_C))
	{
		//move player out of horizontal-bar (prevent loop idle->fall->idle)
		PlayerState *newState = new PlayerFallState(_player);
		_player->SetPositionY(_player->GetPosition().y + 20);
		_player->SetState(newState);
		return;
	}
}
