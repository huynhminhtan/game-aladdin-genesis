#pragma once

#include "../GameObject.h"
#include "../../GameComponents/Sprite.h"
#include "../../GameComponents/Animation.h"

class Rubby : public GameObject
{
private:
	Sprite * _appleSprite;
	Animation *_animationSprite;
	Animation *_animationRubby;
	bool _entryVisible;

public:
	Rubby();
	~Rubby();

	//void Update(float deltaTime);
	void Draw(Camera* camera);
	void Update(float dt);

	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

