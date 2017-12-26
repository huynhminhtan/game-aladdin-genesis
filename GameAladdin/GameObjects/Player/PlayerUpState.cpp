#include "PlayerUpState.h"
#include "Player.h"
#include "PlayerCrouchAttackState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpState.h"

PlayerUpState::PlayerUpState()
{
}

PlayerUpState::PlayerUpState(Player * player) : PlayerState(player, PlayerState::StateName::Up)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Up", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.4f, false));
}


PlayerUpState::~PlayerUpState()
{
}

void PlayerUpState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	//change state
	if (!Input::GetInstance()->IsKeyPressed(DIK_UP))
	{
		//release key "down"->stand up (reverse animation)
		_animation->Reverse(true);

		//because current state is not loop->pause
		_animation->SetLoop(true);
		_animation->Play();
	}

	if (_animation->IsReverse() && _animation->IsBegin())
	{
		_player->SetState(new PlayerIdleState(_player));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_C))
	{
		_player->SetState(new PlayerJumpState(_player));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_X))
	{
		_player->SetState(new PlayerCrouchAttackState(_player));
		return;
	}
}
