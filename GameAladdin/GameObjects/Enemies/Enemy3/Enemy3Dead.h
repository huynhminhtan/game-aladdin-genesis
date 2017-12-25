#pragma once

#include "../EnemyState.h"

class Enemy3Dead: public EnemyState
{
private:
	
public:
	Enemy3Dead();
	Enemy3Dead(Enemy* enemy);
	~Enemy3Dead();

	void Update(float deltaTime);
};

