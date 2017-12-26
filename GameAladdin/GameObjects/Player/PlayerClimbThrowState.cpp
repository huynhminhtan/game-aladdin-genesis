#include "PlayerClimbThrowState.h"
#include "Player.h"
#include "PlayerClimbVerticalState.h"
#include "PlayerClimbHorizontalIdleState.h"
#include "../Weapons/PlayerWeapons/AppleWeapon.h"
#include "../../GameComponents/SceneManager.h"

PlayerClimbThrowState::PlayerClimbThrowState()
{
}

PlayerClimbThrowState::PlayerClimbThrowState(Player * player, GameObject *ropeOrHorizontalBar, PlayerState::StateName fromState) : PlayerState(player, PlayerState::StateName::ClimbThrow)
{
	_ropeOrHorizontalBar = ropeOrHorizontalBar;
	_fromState = fromState;

	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "climb_throw", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.7f));

	_isCreatedAppleWeapon = false;

	_player->SetAccelerationY(0);
	_player->SetVelocityY(0);

	_player->AllowMoveLeft(false);
	_player->AllowMoveRight(false);

	//Sound::GetInstance()->Play("Low_Sword", 0, 1);
}


PlayerClimbThrowState::~PlayerClimbThrowState()
{
}

void PlayerClimbThrowState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (!_isCreatedAppleWeapon && _animation->GetCurrentIndex() == 4)//create appleWeapon
	{
		_isCreatedAppleWeapon = true;
		_player->SetNumAppleWeapon(_player->GetNumAppleWeapon() - 1);

		AppleWeapon *appleWeapon = new AppleWeapon();
		appleWeapon->SetPosition(_player->GetPosition().x, _player->GetPosition().y);

		//set left or right for velocityX
		appleWeapon->SetVelocityX(appleWeapon->GetVelocity().x * (_player->IsRight() ? 1 : -1));

		//add gameobject to update&draw list
		SceneManager::GetInstance()->GetCurrentScene()->AddGameObjectToWeaponList(appleWeapon);

		//add appleWeapon to QuadTree
		QuadTree::InsertDynamicObject(appleWeapon);
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
