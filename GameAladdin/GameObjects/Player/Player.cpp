﻿#include "Player.h"
#include "PlayerFallState.h"
#include "PlayerDeathState.h"
#include "PlayerDamageState.h"
#include "../../GameComponents/SceneManager.h"
#include "../Enemies/Enemy.h"
#include "../Weapons/Weapon.h"
#include "../../GameComponents/Sound.h"
#include "../../Scenes/JafarScene.h"

int Player::_timesPlay = 3;
int Player::_score = 0;

int Player::GetTimesPlay()
{
	return _timesPlay;
}

int Player::GetScore()
{
	return _score;
}

Player::Player() :GameObject(GameObject::GameObjectType::Players, true)
{
	Reset();
	_numAppleWeapon = NUM_APPLE_WEAPON;
}

Player::~Player()
{
	delete _state;
	_state = NULL;
}

void Player::Reset()
{
	_mass = PLAYER_MASS;
	_speed = PLAYER_SPEED;
	_jumpForce = PLAYER_JUMP_FORCE;
	_jumpRunForce = PLAYER_JUMP_RUN_FORCE;

	_isRight = true;
	_isGround = false;
	_allowMoveLeft = _allowMoveRight = true;

	_collidedWithCoalDuration = 0;

	_health = HEATH_PLAYER;
	_damage = DAMAGE_OF_PLAYER;

	_deltaTime = 0.166f;

	_allowStairsBellow = false;
	_allowStairsTop = false;
	_totalFrameStrairs = 0;


	_state = new PlayerFallState(this);
}

void Player::Update(float deltaTime)
{
	_deltaTime = deltaTime;

	if (_isGround && _velocity.y > 0)
	{
		_acceleration.y = 0;
		_velocity.y = 0;
	}

	//face to right or left
	if (_input->IsKeyPressed(DIK_LEFT) && _health > 0)
		_isRight = false;
	else if (_input->IsKeyPressed(DIK_RIGHT) && _health > 0)
		_isRight = true;

	//move
	if (_input->IsKeyPressed(DIK_LEFT) && _allowMoveLeft && _health > 0)
		_velocity.x = -1 * _speed;
	else if (_input->IsKeyPressed(DIK_RIGHT) && _allowMoveRight && _health > 0)
		_velocity.x = _speed;
	else
		_velocity.x = 0;

	GameObject::Update(deltaTime);
	if (_state != NULL)
		_state->Update(deltaTime);

}

void Player::Draw(Camera * camera)
{
	Animation *animation = _state->GetAnimation();
	if (animation != NULL)
		animation->Draw(camera);

	//debug
	/*
	D3DXVECTOR3 newPosition = camera->ConvertPosition(_position.x, _position.y);

	RECT rect;
	rect.left = newPosition.x - _width / 2;
	rect.top = newPosition.y - _height / 2;
	rect.right = newPosition.x + _width / 2;
	rect.bottom = newPosition.y + _height / 2;

	Graphics::GetInstance()->GetDevice()->ColorFill(Graphics::GetInstance()->GetBackBuffer(), &rect, D3DCOLOR_XRGB(0, 255, 0));
	*/
}

void Player::CheckCollision()
{
	std::vector<GameObject*> listCanCollide;
	SceneManager::GetInstance()->GetCurrentScene()->GetQuadTree()->Retrieve(listCanCollide, this);

	bool playerGround = false;
	bool allowPlayerMoveLeft = true;
	bool allowPlayerMoveRight = true;

	for (size_t i = 0; i < listCanCollide.size(); i++)
	{
		GameObject *gameObject = listCanCollide.at(i);
		if (!gameObject->IsVisible())
			continue;

		//lay va cham cua other voi this
		GameCollision collisionData = GameCollision::CheckCollision(this->GetBound(), gameObject->GetBound());
		if (collisionData.IsCollided())
		{
			this->OnCollision(gameObject, collisionData.GetSide());

			if (gameObject->GetTag() == GameObject::GameObjectType::Ground ||
				gameObject->GetTag() == GameObject::GameObjectType::FloatGround ||
				gameObject->GetTag() == GameObject::GameObjectType::Wall ||
				gameObject->GetTag() == GameObject::GameObjectType::Stairs)
			{
				if (collisionData.GetSide() == GameCollision::SideCollisions::Bottom
					|| collisionData.GetSide() == GameCollision::SideCollisions::BottomLeft
					|| collisionData.GetSide() == GameCollision::SideCollisions::BottomRight)
				{
					playerGround = true;

					// Kéo Aladdin xuống mọi lúc, để va chạm không bị thục xuống
					// -> không sử dụng được
					//this->_position.y -= (10 * _deltaTime);
				}
			}


			if (gameObject->GetTag() == GameObject::GameObjectType::Stairs)
			{
				// cho aladdin nhích lên
				/*collisionData.GetSide() == GameCollision::SideCollisions::Left ||
				collisionData.GetSide() == GameCollision::SideCollisions::TopLeft*/
				if (collisionData.GetSide() == GameCollision::SideCollisions::Right /*||
					collisionData.GetSide() == GameCollision::SideCollisions::BottomRight*/)
				{
					// code here
					if (this->GetVelocity().y == 0 && (_isRight == true))
						this->_position.y -= (300 * _deltaTime);
					//this->SetVelocityY(-1 * 3);
				//	this->SetAccelerationY(this->GetMass());
				}
			}

			if (gameObject->GetTag() == GameObject::GameObjectType::AllowStairsBellow
				/*(this->_position.x >= 2580.5f) && (this->_position.x <= 2586.5f)*/)
			{
				//	_allowStairsBellow = (_allowStairsBellow) ? false : true;

				_allowStairsBellow = true;

				/*if (collisionData.GetSide() == GameCollision::SideCollisions::Right)
				{
					_allowStairsBellow++;

					if (_allowStairsBellow == 2)
						_allowStairsBellow = 0;
					else
						_allowStairsBellow = 2;
				}*/
			}

			if (_allowStairsBellow)
			{
				if (gameObject->GetTag() == GameObject::GameObjectType::StairsEndBellow)
				{

					//if (collisionData.GetSide() == GameCollision::SideCollisions::Right /*||
					//	collisionData.GetSide() == GameCollision::SideCollisions::BottomRight*/)
					//{
					//	// code here
					//	if (this->GetVelocity().y == 0 && (_isRight == true))
					//		this->_position.y -= (300 * _deltaTime);
					//	//this->SetVelocityY(-1 * 3);
					////	this->SetAccelerationY(this->GetMass());
					//}

					if (collisionData.GetSide() == GameCollision::SideCollisions::Bottom
						|| collisionData.GetSide() == GameCollision::SideCollisions::BottomLeft
						|| collisionData.GetSide() == GameCollision::SideCollisions::BottomRight)
					{
						playerGround = true;
					}
				}

				if (gameObject->GetTag() == GameObject::GameObjectType::StairsEndBellow)
				{
					// cho aladdin nhích lên
					/*collisionData.GetSide() == GameCollision::SideCollisions::Left ||
					collisionData.GetSide() == GameCollision::SideCollisions::TopLeft*/
					if (collisionData.GetSide() == GameCollision::SideCollisions::Left /*||
						collisionData.GetSide() == GameCollision::SideCollisions::BottomRight*/)
					{
						// code here
						if (this->GetVelocity().y == 0 && (_isRight == false))
							this->_position.y -= (300 * _deltaTime);
						//this->SetVelocityY(-1 * 3);
						//	this->SetAccelerationY(this->GetMass());
					}
				}
			}

			////////////////////////////////////////////////////////////////////////////////////////////

			if (gameObject->GetTag() == GameObject::GameObjectType::AllowStairsTop
				/*(this->_position.x >= 2580.5f) && (this->_position.x <= 2586.5f)*/)
			{
				////	_allowStairsBellow = (_allowStairsBellow) ? false : true;

				_allowStairsTop = true;
				//_totalFrameStrairs++;

				/*if (collisionData.GetSide() == GameCollision::SideCollisions::Right)
				{
				_allowStairsBellow++;

				if (_allowStairsBellow == 2)
				_allowStairsBellow = 0;
				else
				_allowStairsBellow = 2;
				}*/
			}

		/*	if (_totalFrameStrairs >= 24)
			{
				_allowStairsTop = (_allowStairsTop) ? false : true;

				_allowStairsTop = true;
			}*/

			if (_allowStairsTop)
			{
				_totalFrameStrairs = 0;
				if (gameObject->GetTag() == GameObject::GameObjectType::StairsEndTop)
				{
					//if (collisionData.GetSide() == GameCollision::SideCollisions::Right /*||
					//	collisionData.GetSide() == GameCollision::SideCollisions::BottomRight*/)
					//{
					//	// code here
					//	if (this->GetVelocity().y == 0 && (_isRight == true))
					//		this->_position.y -= (300 * _deltaTime);
					//	//this->SetVelocityY(-1 * 3);
					////	this->SetAccelerationY(this->GetMass());
					//}

					if (collisionData.GetSide() == GameCollision::SideCollisions::Bottom
						|| collisionData.GetSide() == GameCollision::SideCollisions::BottomLeft
						|| collisionData.GetSide() == GameCollision::SideCollisions::BottomRight)
					{
						playerGround = true;
					}
				}

				if (gameObject->GetTag() == GameObject::GameObjectType::StairsEndTop)
				{
					// cho aladdin nhích lên
					/*collisionData.GetSide() == GameCollision::SideCollisions::Left ||
					collisionData.GetSide() == GameCollision::SideCollisions::TopLeft*/
					if (collisionData.GetSide() == GameCollision::SideCollisions::Right /*||
						collisionData.GetSide() == GameCollision::SideCollisions::BottomRight*/)
					{
						// code here
						if (this->GetVelocity().y == 0 && (_isRight == true))
							this->_position.y -= (300 * _deltaTime);
						//this->SetVelocityY(-1 * 3);
						//	this->SetAccelerationY(this->GetMass());
					}
				}
			}


			if (gameObject->GetTag() == GameObject::GameObjectType::Wall ||
				gameObject->GetTag() == GameObject::GameObjectType::Ground ||
				gameObject->GetTag() == GameObject::GameObjectType::Stairs)
			{
				if (collisionData.GetSide() == GameCollision::SideCollisions::Left)
					allowPlayerMoveLeft = false;
				if (collisionData.GetSide() == GameCollision::SideCollisions::Right)
					allowPlayerMoveRight = false;
			}
		}
	}

	_isGround = playerGround;

	//because climb state has own move rule
	if (_state != NULL && _state->GetName() != PlayerState::StateName::ClimbVertical && 
		_state->GetName() != PlayerState::StateName::ClimbAttack &&
		_state->GetName() != PlayerState::StateName::ClimbThrow &&
		_state->GetName() != PlayerState::StateName::Up &&
		_state->GetName() != PlayerState::StateName::CrouchIdle &&
		_state->GetName() != PlayerState::StateName::CrouchAttack)
	{
		_allowMoveLeft = allowPlayerMoveLeft;
		_allowMoveRight = allowPlayerMoveRight;
	}
}

void Player::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	if (target->GetTag() == GameObject::GameObjectType::Apple)
	{
		Sound::GetInstance()->Play("Apple_Collect", false, 1);
		_numAppleWeapon++;
	}

	if (target->GetTag() == GameObject::GameObjectType::Enemies)
	{
		Enemy *enemy = dynamic_cast<Enemy*>(target);
		if (enemy->GetState()->GetName() == EnemyState::StateName::Attack
			&& !enemy->GetState()->GetAnimation()->IsBegin()
			&& !enemy->GetState()->IsAttackedPlayer())
		{
			SetHealth(_health - enemy->GetDamage());
			enemy->GetState()->SetIsAttackedPlayer(true);
		}
	}

	if (target->GetTag() == GameObject::GameObjectType::Weapons)
	{
		if (_state->GetName() != PlayerState::StateName::Attack &&
			_state->GetName() != PlayerState::StateName::JumpAttack &&
			_state->GetName() != PlayerState::StateName::CrouchAttack)
		{
			Weapon* weapon = dynamic_cast<Weapon*>(target);
			if (weapon->GetWeaponType() == Weapon::WeaponType::EnemiesWeapons && !weapon->IsAttacked())
			{
				weapon->SetIsAttacked(true);
				SetHealth(_health - weapon->GetDamage());
			}
		}
	}

	if (target->GetTag() == GameObject::GameObjectType::Coal)
	{
		//when colliding with coal, each duration, player's health will decrease
		_collidedWithCoalDuration += _deltaTime;
		if (_collidedWithCoalDuration >= 3)
		{
			_collidedWithCoalDuration = 0;
			SetHealth(_health - 10);
		}
	}

	if (target->GetTag() == GameObject::GameObjectType::Bottles)
	{
		_appearPosition = _position;
	}

	if (target->GetTag() == GameObject::GameObjectType::ScoreObjects)
	{
		ScoreObject* scoreObj = dynamic_cast<ScoreObject*>(target);
		_score += scoreObj->GetScore();
		scoreObj->SetIsVisible(false);
	}

	//next scene
	if (target->GetTag() == GameObject::GameObjectType::ToJafarScene && _health > 0)
	{
		SceneManager::GetInstance()->ReplaceScene(new JafarScene());
		_state = NULL;
		return;
	}

	_state->OnCollision(target, side);
}

PlayerState * Player::GetState()
{
	return _state;
}

void Player::SetState(PlayerState * state, bool fixFootPosition)
{
	if (_state->GetName() == PlayerState::StateName::Death)
	{
		return;
	}

	if (fixFootPosition)
	{
		//make sure player's foot at the same position when change state. because each state has own height
		int newHeight = state->GetAnimation()->GetHeight();
		int currentHeight = _state->GetAnimation()->GetHeight();
		float diff = (currentHeight - newHeight) / 2.0;
		_position.y += diff;
	}

	//change state
	delete _state;
	_state = state;
}

bool Player::IsRight()
{
	return _isRight;
}

bool Player::IsGround()
{
	return _isGround;
}

void Player::SetIsGround(bool isGround)
{
	_isGround = isGround;
}

bool Player::IsAllowMoveLeft()
{
	return _allowMoveLeft;
}

bool Player::IsAllowMoveRight()
{
	return _allowMoveRight;
}

void Player::AllowMoveLeft(bool allow)
{
	_allowMoveLeft = allow;
}

void Player::AllowMoveRight(bool allow)
{
	_allowMoveRight = allow;
}

D3DXVECTOR2 Player::GetAppearPosition()
{
	return _appearPosition;
}

void Player::SetAppearPosition(D3DXVECTOR2 appearPositioin)
{
	_appearPosition = appearPositioin;
}

float Player::GetSpeed()
{
	return _speed;
}

void Player::SetSpeed(float speed)
{
	_speed = speed;
}

float Player::GetJumpForce()
{
	return _jumpForce;
}

void Player::SetJumpForce(float force)
{
	_jumpForce = force;
}

float Player::GetJumpRunForce()
{
	return _jumpRunForce;
}

void Player::SetJumpRunForce(float force)
{
	_jumpRunForce = force;
}

int Player::GetHealth()
{
	return _health;
}

void Player::SetHealth(int newHealth)
{
	//check if died
	if (_health <= 0)
		return;

	if (newHealth < _health)
	{
		Sound::GetInstance()->Play("Aladdin_Hurt", 0, 1);
		if (_state->GetName() == PlayerState::StateName::Idle)
		{
			SetState(new PlayerDamageState(this));
		}
	}

	_health = newHealth;

	if (newHealth <= 0)
	{
		SetState(new PlayerDeathState(this));

		//hoi sinh
		if (_timesPlay > 0)
		{
			_timesPlay--;
			Reset();
			_position = _appearPosition;
			_camera->SetPosition(_position);
		}
	}


}

int Player::GetDamage()
{
	return _damage;
}

void Player::SetDamage(int newDamage)
{
	_damage = newDamage;
}

int Player::GetNumAppleWeapon()
{
	return _numAppleWeapon;
}

void Player::SetNumAppleWeapon(int value)
{
	_numAppleWeapon = value;
}


