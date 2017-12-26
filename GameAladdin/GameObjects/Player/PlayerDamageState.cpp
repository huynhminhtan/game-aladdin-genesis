#include "PlayerDamageState.h"
#include "Player.h"
#include "PlayerIdleState.h"
#include "PlayerAttackState.h"
#include "PlayerJumpState.h"
#include "PlayerThrowState.h"
#include "PlayerCrouchIdleState.h"
#include "PlayerUpState.h"

PlayerDamageState::PlayerDamageState()
{
	//don't use
}

PlayerDamageState::PlayerDamageState(Player * player) : PlayerState(player, PlayerState::StateName::Damage)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Damage", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.5f, false));
}


PlayerDamageState::~PlayerDamageState()
{
}

void PlayerDamageState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (_animation->IsFinish())//change state
	{
		_player->SetState(new PlayerIdleState(_player));
		return;
	}

	//attack
	if (Input::GetInstance()->IsKeyPressed(DIK_X))
	{
		_player->SetState(new PlayerAttackState(_player));
		return;
	}

	//jump
	if (Input::GetInstance()->IsKeyPressed(DIK_C))
	{
		_player->SetState(new PlayerJumpState(_player));
		return;
	}

	//throw apple
	if (Input::GetInstance()->IsKeyPressed(DIK_Z) && _player->GetNumAppleWeapon() > 0)
	{
		_player->SetState(new PlayerThrowState(_player));
		return;
	}

	//idle
	if (Input::GetInstance()->IsKeyPressed(DIK_DOWN))
	{
		_player->SetState(new PlayerCrouchIdleState(_player));
		return;
	}

	//Up
	if (Input::GetInstance()->IsKeyPressed(DIK_UP))
	{
		_player->SetState(new PlayerUpState(_player));
		return;
	}
}
