#pragma once

#include "define.h"

class GameCollision
{
public:
	enum SideCollisions
	{
		UnKnow,
		Left,
		Right,
		Top,
		Bottom,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	GameCollision();
	~GameCollision();

	static GameCollision CheckCollision(RECT rect1, RECT rect2);

	bool IsCollided();
	GameCollision::SideCollisions GetSide();

	static GameCollision GameCollision::SweptAABB(RECT rect1, RECT rect2, float speedX, float speedy);
private:
	bool _isCollided;
	SideCollisions _side;

	static bool GameCollision::RectMeeting(const RECT& rect1, const RECT& rect2);
};