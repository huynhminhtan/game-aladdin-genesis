#include "Enemy3Dead.h"
#include "Enemy3.h"
#include "Enemy3WalkState.h"
#include "../../Weapons/EnemiesWeapons/Enemy3Weapon.h"
#include "../../../GameComponents/SceneManager.h"

Enemy3Dead::Enemy3Dead()
{
	//not use
}

Enemy3Dead::Enemy3Dead(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Attack)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy3Dead(), "enemy3_dead", ResourceManager::GetInstance()->GetTextureEnemy3Dead(), true, 0.5f));

}


Enemy3Dead::~Enemy3Dead()
{
}

void Enemy3Dead::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	////create weapon
	//if (!_isCreatedWeapon && _animation->GetCurrentIndex() == 2)
	//{
	//	_isCreatedWeapon = true;

	//	Enemy3Weapon* weapon = new Enemy3Weapon();
	//	weapon->SetPosition(_enemy->GetPosition().x, _enemy->GetPosition().y - _enemy->GetHeight() / 2);

	//	//set left or right for velocityX
	//	weapon->SetVelocity(_enemy->GetTarget()->GetPosition() - _enemy->GetPosition());

	//	//add gameobject to update&draw list
	//	SceneManager::GetInstance()->GetCurrentScene()->AddGameObjectToWeaponList(weapon);

	//	//add appleWeapon to QuadTree
	//	QuadTree::InsertDynamicObject(weapon);
	//}
	////reset _isCreatedWeapon
	//if (_animation->GetCurrentIndex() == 3)
	//	_isCreatedWeapon = false;

	////change state
	//if (!_enemy->IsTargetInAttackRange() && _enemy->GetTarget()->GetVelocity().x != 0)
	//{
	//	_enemy->SetState(new Enemy3WalkState(_enemy));
	//	return;
	//}
}
