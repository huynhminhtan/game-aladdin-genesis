#pragma once

#include "../Enemy.h"

class Enemy3 : public Enemy
{
private:
	bool _entryDead;
public:
	Enemy3();
	Enemy3(GameObject * player);
	~Enemy3();

	//void Update(float deltaTime);
};