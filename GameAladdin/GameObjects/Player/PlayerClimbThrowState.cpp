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

	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLPlayerClimbThrow(), "climb_throw", ResourceManager::GetInstance()->GetTexturePlayerClimbThrow(), true, 0.6f));

	_isCreatedAppleWeapon = false;

	_player->SetAccelerationY(0);
	_player->SetVelocityY(0);

	_player->AllowMoveLeft(false);
	_player->AllowMoveRight(false);

	_checkPlussPosition = true;

	//Sound::GetInstance()->Play("Low_Sword", 0, 1);
}


PlayerClimbThrowState::~PlayerClimbThrowState()
{
}

void PlayerClimbThrowState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (_checkPlussPosition )
	{
		if (_fromState == PlayerState::StateName::ClimbVertical)
		{
		  _player->SetPositionY(_player->GetPosition().y - 5);
		}
		
		if (_fromState == PlayerState::StateName::ClimbHorizontalIde)
		{
			/*if (_player->GetState()->GetAnimation()->GetCurrentIndex() == 3)
			{
				_player->SetPositionY(_player->GetPosition().y - 5);
			}*/
		}

		_checkPlussPosition = false;
	}

	if (!_isCreatedAppleWeapon && _animation->GetCurrentIndex() == 4)//create appleWeapon
	{
		_isCreatedAppleWeapon = true;
		_player->SetNumAppleWeapon(_player->GetNumAppleWeapon() - 1);

		_player->SetPositionY(_player->GetPosition().y + 10);
		AppleWeapon *appleWeapon = new AppleWeapon();
		if (_player->IsRight())
			appleWeapon->SetPosition(_player->GetPosition().x + 10, _player->GetPosition().y);
		else
			appleWeapon->SetPosition(_player->GetPosition().x - 10, _player->GetPosition().y);

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
