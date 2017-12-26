#include "Enemy.h"
#include "../Player/Player.h"
#include "../Weapons/Weapon.h"
#include "../../GameComponents/SceneManager.h"

Enemy::Enemy() : GameObject(GameObject::GameObjectType::Enemies, true)
{
	//not use
}

Enemy::Enemy(GameObject * target) : GameObject(GameObject::GameObjectType::Enemies)
{
	_target = target;
	_distanceToTarget = _target->GetPosition() - _position;

	_footPosY = 0;

	_health = HEATH_ENEMY;
	_damage = 5;
	_speed = 10;

	_viewRangeX = 300;
	_viewRangeY = 80;

	_attackRangeX = 80;
	_attackRangeY = 80;

	_isRight = false;
	_allowMoveLeft = _allowMoveRight = true;
	_canFlip = true;

	_collidedWithCoalDuration = 0;

	_isDead = false;
	_isAnimationDead = false;

	_animationSprite = new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemyDead(), "enemy_dead", ResourceManager::GetInstance()->GetTextureEnemyDead(), true, 1.2f);
	//_animationSprite->SetScale(D3DXVECTOR2(0.8f, 0.8f));
}

Enemy::~Enemy()
{
	delete _state;
	_state = 0;

	delete _animationSprite;
}

void Enemy::Update(float deltaTime)
{
	_animationSprite->Update(deltaTime);

	// calculate distance to target (player)
	_distanceToTarget = _target->GetPosition() - _position;

	//check isDie
	if (_health <= 0)
	{
		_isDead = true;
		//_isVisible = false;
	}

	//face to left or right
	if (_distanceToTarget.x > 0)
		_isRight = true;
	else if (_distanceToTarget.x < 0)
		_isRight = false;

	//move
	if (IsTargetInViewRange() && !IsTargetInAttackRange())
	{
		if (_distanceToTarget.x > 0 && _isMovableObject && _allowMoveRight)
		{
			//move right
			_velocity.x = _speed;
		}
		else if (_distanceToTarget.x < 0 && _isMovableObject && _allowMoveLeft)
		{
			//move left
			_velocity.x = -1 * _speed;
		}
		else
		{
			_velocity.x = 0;
		}
	}
	else
	{
		//v=0
		_velocity.x = 0;
	}

	GameObject::Update(deltaTime);

	if (_isInCamera || _allowUpdateWhenNotInCamera)
		_state->Update(deltaTime);

	//fix foot posY
	_position.y = _footPosY - _height / 2;
}

void Enemy::Draw(Camera * camera)
{
	Animation *animation = _state->GetAnimation();

	//if (_state->IsAnimationFinish())
	//{
	//	_isAnimationDead = true;
	//}

	if (_isDead)
	{
		_animationSprite->SetPosition(_position);
		_animationSprite->Draw(camera);

		if (_animationSprite->IsFinish())
		{
			_isVisible = false;
		}
	}
	else
	{
		if (animation != NULL)
			animation->Draw(camera);
	}
}

void Enemy::CheckCollision()
{
	std::vector<GameObject*> listCanCollide;
	SceneManager::GetInstance()->GetCurrentScene()->GetQuadTree()->Retrieve(listCanCollide, this);

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

			//prevent enemy walk out of ground

			if (gameObject->GetTag() == GameObject::GameObjectType::Ground ||
				gameObject->GetTag() == GameObject::GameObjectType::FloatGround ||
				gameObject->GetTag() == GameObject::GameObjectType::Stairs)
			{
				if (collisionData.GetSide() == GameCollision::SideCollisions::BottomRight
					|| collisionData.GetSide() == GameCollision::SideCollisions::Left)
					allowPlayerMoveLeft = false;

				if (collisionData.GetSide() == GameCollision::SideCollisions::BottomLeft
					|| collisionData.GetSide() == GameCollision::SideCollisions::Right)
					allowPlayerMoveRight = false;

				if (collisionData.GetSide() == GameCollision::SideCollisions::Bottom)
				{
					allowPlayerMoveRight = true;
					allowPlayerMoveLeft = true;
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

	_allowMoveLeft = allowPlayerMoveLeft;
	_allowMoveRight = allowPlayerMoveRight;
}

void Enemy::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	if (target->GetTag() == GameObject::GameObjectType::Players)
	{
		Player *player = dynamic_cast<Player*>(target);

		if ((player->GetState()->GetName() == PlayerState::StateName::Attack ||
			player->GetState()->GetName() == PlayerState::StateName::JumpAttack ||
			player->GetState()->GetName() == PlayerState::StateName::CrouchAttack) &&
			!player->GetState()->IsAttackedEnemy())
		{
			_health -= player->GetDamage();
			player->GetState()->SetIsAttackedEnemy(true);
		}
	}

	if (target->GetTag() == GameObject::GameObjectType::Weapons)
	{
		Weapon* weapon = dynamic_cast<Weapon*>(target);
		if (weapon->GetWeaponType() == Weapon::WeaponType::PlayerWeapons && !weapon->IsAttacked())
		{
			weapon->SetIsAttacked(true);
			SetHealth(_health - weapon->GetDamage());
		}
	}

	if (target->GetTag() == GameObject::GameObjectType::Coal)
	{
		//when colliding with coal, each duration, player's health will decrease
		_collidedWithCoalDuration += _deltaTime;
		if (_collidedWithCoalDuration >= 3)
		{
			_collidedWithCoalDuration = 0;
			SetHealth(_health - DAMAGE_COAL_OF_ENEMY);
		}
	}

	_state->OnCollision(target, side);
}

bool Enemy::IsTargetInViewRange()
{
	if (abs(_distanceToTarget.x) <= _viewRangeX && abs(_distanceToTarget.y) < _viewRangeY)
		return true;
	return false;
}

bool Enemy::IsTargetInAttackRange()
{
	if (abs(_distanceToTarget.x) <= _attackRangeX && abs(_distanceToTarget.y) < _attackRangeY)
		return true;
	return false;
}

void Enemy::SetFootPosY()
{
	if (_footPosY == 0)
		_footPosY = _position.y + _height / 2;
}

EnemyState * Enemy::GetState()
{
	return _state;
}

void Enemy::SetState(EnemyState * state, bool fixFootPosition)
{
	if (fixFootPosition)
	{
		//make sure enemy's foot at the same position when change state. because each state has own height
		int newHeight = state->GetAnimation()->GetHeight();
		int currentHeight = _state->GetAnimation()->GetHeight();
		float diff = (currentHeight - newHeight) / 2.0;
		_position.y += diff;
	}

	//change state
	delete _state;
	_state = state;
}

GameObject * Enemy::GetTarget()
{
	return _target;
}

int Enemy::GetHealth()
{
	return _health;
}

void Enemy::SetHealth(int newHealth)
{
	_health = newHealth;
}

int Enemy::GetDamage()
{
	return _damage;
}

void Enemy::SetDamage(int newDamage)
{
	_damage = newDamage;
}

bool Enemy::IsRight()
{
	return _isRight;
}

void Enemy::SetIsRight(bool right)
{
	_isRight = right;

	if (_state->GetAnimation()->IsSourceRight())
		_state->GetAnimation()->FlipHorizontal(!_isRight);
	else
		_state->GetAnimation()->FlipHorizontal(_isRight);
}

bool Enemy::IsCanFlip()
{
	return _canFlip;
}

bool Enemy::IsAllowMoveLeft()
{
	return _allowMoveLeft;
}

bool Enemy::IsAllowMoveRight()
{
	return _allowMoveRight;
}

void Enemy::AllowMoveLeft(bool allow)
{
	_allowMoveLeft = allow;
}

void Enemy::AllowMoveRight(bool allow)
{
	_allowMoveRight = allow;
}

void Enemy::SetPosition(float x, float y)
{
	GameObject::SetPosition(x, y);
	SetFootPosY();
}

void Enemy::SetPosition(D3DXVECTOR2 position)
{
	GameObject::SetPosition(position);
	SetFootPosY();
}

void Enemy::SetPosition(D3DXVECTOR3 position)
{
	GameObject::SetPosition(position);
	SetFootPosY();
}

D3DXVECTOR2 Enemy::GetDistanceToTarget()
{
	return _distanceToTarget;
}

bool Enemy::GetIsDead()
{
	return _isDead;
}