#include "Enemy3.h"
#include "Enemy3IdleState.h"
#include "Enemy3Dead.h"

Enemy3::Enemy3()
{
	// not use
}

Enemy3::Enemy3(GameObject * player):Enemy(player)
{
	_state = new Enemy3IdleState(this);

	_attackRangeX = 150;

	_entryDead = false;
}


Enemy3::~Enemy3()
{
}

//void Enemy3::Update(float dt)
//{
//	Enemy::Update(dt);
//
//}

