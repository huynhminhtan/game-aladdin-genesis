#include "PlayerRunFallState.h"
#include "Player.h"
#include "PlayerRunState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpState.h"
#include "PlayerJumpAttackState.h"
#include "PlayerJumpThrowState.h"
#include "PlayerClimbHorizontalIdleState.h"
#include "PlayerClimbVerticalState.h"
#include "PlayerSpringState.h"


PlayerRunFallState::PlayerRunFallState()
{
	//don't use
}

PlayerRunFallState::PlayerRunFallState(Player * player) : PlayerState(player, PlayerState::StateName::RunFall)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "RunFall", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.8f));

	_player->SetAccelerationY(_player->GetMass());
}


PlayerRunFallState::~PlayerRunFallState()
{
}

void PlayerRunFallState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (_player->IsGround())//change state
	{
		if (_player->GetVelocity().x == 0)
			_player->SetState(new PlayerIdleState(_player));
		else
			_player->SetState(new PlayerRunState(_player));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_S))
	{
		_player->SetState(new PlayerJumpAttackState(_player));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_A) && _player->GetNumAppleWeapon() > 0)
	{
		_player->SetState(new PlayerJumpThrowState(_player));
		return;
	}
}

void PlayerRunFallState::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	PlayerState::OnCollision(target, side);

	if (target->GetTag() == GameObject::GameObjectType::Rope)
	{
		float diffX = abs(target->GetPosition().x - _player->GetPosition().x);
		if (diffX < 18 && _player->GetBound().bottom <= target->GetBound().bottom && _player->GetBound().top >= target->GetBound().top)
		{
			_player->SetState(new PlayerClimbVerticalState(_player, target));
		}
	}

	if (target->GetTag() == GameObject::GameObjectType::HorizontalBar)
	{
		float diffTop = abs(target->GetBound().top - _player->GetBound().top);
		if (diffTop < 18
			&& _player->GetPosition().x >= target->GetBound().left
			&& _player->GetPosition().x <= target->GetBound().right)
			_player->SetState(new PlayerClimbHorizontalIdleState(_player, target), false);
	}

	if (target->GetTag() == GameObject::GameObjectType::Springboard)
	{
		float diffY = abs(target->GetPosition().y - _player->GetBound().bottom);//ko dung GetBound, ma lay positionY cua target vi target nam xieng
		if (diffY < 18)
		{
			_player->SetState(new PlayerSpringState(_player));
		}
	}

	if (target->GetTag() == GameObject::GameObjectType::Camels
		&& (side == GameCollision::SideCollisions::Bottom
			|| side == GameCollision::SideCollisions::BottomLeft
			|| side == GameCollision::SideCollisions::BottomRight))
	{
		_player->SetVelocityY(-1 * _player->GetJumpForce());
		_player->SetState(new PlayerJumpState(_player));
		return;
	}
}
