#pragma once

#include "../GameObject.h"
#include "../../GameComponents/Sprite.h"
#include "../../GameComponents/Animation.h"

class Springboard : public GameObject
{
private:
	Animation * _animation;

public:
	Springboard();
	~Springboard();

	void Draw(Camera* camera);
	void Update(float deltaTime);

	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

