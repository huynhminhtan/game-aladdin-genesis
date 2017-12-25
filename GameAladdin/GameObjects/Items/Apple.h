#pragma once

#include "../GameObject.h"
#include "../../GameComponents/Sprite.h"
#include "../../GameComponents/Animation.h"

class Apple : public GameObject
{
private:
	Sprite * _appleSprite;
	Animation *_animationSprite;
	bool _entryVisible;

public:
	Apple();
	~Apple();

	//void Update(float deltaTime);
	void Draw(Camera* camera);
	void Update(float dt);

	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

