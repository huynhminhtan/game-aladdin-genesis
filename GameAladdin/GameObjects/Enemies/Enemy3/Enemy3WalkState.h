#pragma once

#include "../EnemyState.h"

class Enemy3WalkState : public EnemyState
{
public:
	Enemy3WalkState();
	Enemy3WalkState(Enemy* enemy);
	~Enemy3WalkState();

	void Update(float deltaTime);
};

