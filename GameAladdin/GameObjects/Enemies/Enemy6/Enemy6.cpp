#include "Enemy6.h"
#include "Enemy6ThrowState.h"


Enemy6::Enemy6()
{
	//not use
}

Enemy6::Enemy6(GameObject * player) : Enemy(player)
{
	_state = new Enemy6ThrowState(this);
	_isMovableObject = false;
	_attackRangeY = 180;

	_isMovableObject = false;
	_canFlip = false;
}


Enemy6::~Enemy6()
{
}
