#include "PlayerRunJumpState.h"
#include "Player.h"
#include "PlayerRunFallState.h"
#include "PlayerJumpAttackState.h"
#include "PlayerJumpThrowState.h"


PlayerRunJumpState::PlayerRunJumpState()
{
}

PlayerRunJumpState::PlayerRunJumpState(Player * player) : PlayerState(player, PlayerState::StateName::RunJump)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "RunJump", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.8f));

	//TODO: fix jump continuously (Jump->Attack->Jump)
	if (_player->GetVelocity().y == 0)
		_player->SetVelocityY(-1 * _player->GetJumpRunForce());
	_player->SetAccelerationY(_player->GetMass());
}


PlayerRunJumpState::~PlayerRunJumpState()
{
}

void PlayerRunJumpState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (_player->GetVelocity().y > 0)
	{
		_player->SetState(new PlayerRunFallState(_player));
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
