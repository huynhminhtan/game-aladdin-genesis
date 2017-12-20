#pragma once

#include "../Camera.h"
#include "../GameObject.h"
#include "EnemyState.h"

class Enemy : public GameObject
{
protected:
	GameObject* _target;

	int _health, _damage;
	float _speed;

	// use to detect the target being near
	int _viewRangeX, _viewRangeY, _attackRangeX, _attackRangeY;
	D3DXVECTOR2 _distanceToTarget;

	// face look right?
	bool _isRight, _canFlip, _allowMoveLeft, _allowMoveRight;

	//when colliding with coal, each duration, player's health will decrease
	float _collidedWithCoalDuration;

	EnemyState *_state;

	//fix foot posY
	int _footPosY;
	void SetFootPosY();
public:
	Enemy();//not use
	Enemy(GameObject * target);
	virtual ~Enemy();

	virtual void Update(float deltaTime);
	void Draw(Camera* camera);

	void CheckCollision();
	virtual void OnCollision(GameObject *target, GameCollision::SideCollisions side);

	bool IsTargetInViewRange();
	bool IsTargetInAttackRange();

	EnemyState* GetState();
	void SetState(EnemyState* state, bool fixFootPosition = true);

	GameObject* GetTarget();

	int GetHealth();
	void SetHealth(int newHealth);

	int GetDamage();
	void SetDamage(int newDamage);

	bool IsRight();
	void SetIsRight(bool right);

	bool IsCanFlip();

	bool IsAllowMoveLeft();
	bool IsAllowMoveRight();
	void AllowMoveLeft(bool allow);
	void AllowMoveRight(bool allow);

	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR2 position);
	void SetPosition(D3DXVECTOR3 position);

	D3DXVECTOR2 GetDistanceToTarget();
};

