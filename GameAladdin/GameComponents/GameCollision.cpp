#include "GameCollision.h"

GameCollision::GameCollision()
{
}

GameCollision::~GameCollision()
{
}

GameCollision GameCollision::CheckCollision(RECT rect1, RECT rect2)
{
	GameCollision gameCollision;

	RECT intersect;
	bool isIntersect = IntersectRect(&intersect, &rect1, &rect2);
	if (!isIntersect)
	{
		gameCollision._isCollided = false;
	}
	else
	{
		//collide
		gameCollision._isCollided = true;

		float xCenterCollisionRegion = intersect.left + (intersect.right - intersect.left) / 2.0f;
		float yCenterCollisionRegion = intersect.top + (intersect.bottom - intersect.top) / 2.0f;

		float xCenter1 = rect1.left + (rect1.right - rect1.left) / 2.0f;
		float yCenter1 = rect1.top + (rect1.bottom - rect1.top) / 2.0f;

		D3DXVECTOR2 centerCollisionRegion = D3DXVECTOR2(xCenterCollisionRegion, yCenterCollisionRegion);
		D3DXVECTOR2 centerRect1 = D3DXVECTOR2(xCenter1, yCenter1);

		//vector noi tam Rect va Collision Region
		D3DXVECTOR2 vec = centerCollisionRegion - centerRect1;

		//chuan hoa vector
		D3DXVec2Normalize(&vec, &vec);

		/*
		- neu vec.y > 0 => rect1 nam phia ben tren rect2
		- neu vec.y < 0 => rect1 nam phia ben duoi rect2
		- neu vec.x > 0 => rect1 nam phia ben phai rect2
		- neu vec.x < 0 => rect1 nam phia ben trai rect2
		*/

		//get side collision
		gameCollision._side = GameCollision::SideCollisions::UnKnow;
		if (vec.y < 0)
		{
			//collision top

			if (vec.x >= 0.8f)
			{
				//goc trong khoang 0 -> 35
				gameCollision._side = GameCollision::SideCollisions::Right;
			}
			else if (vec.x > 0.35f && vec.x < 0.8f)
			{
				//goc trong khoang 35 -> 70
				gameCollision._side = GameCollision::SideCollisions::TopRight;
			}
			else if (vec.x <= 0.35f && vec.x >= -0.35f)
			{
				//goc trong khoang 70 -> 110
				gameCollision._side = GameCollision::SideCollisions::Top;
			}
			else if (vec.x < -0.35f && vec.x >= -0.8f)
			{
				//goc trong khoang 110 -> 145
				gameCollision._side = GameCollision::SideCollisions::TopLeft;
			}
			else
			{
				//goc trong khoang 145 -> 180
				gameCollision._side = GameCollision::SideCollisions::Left;
			}
		}
		else
		{
			//collision bottom

			if (vec.x >= 0.8)
			{
				//goc trong khoang 0 -> -35
				gameCollision._side = GameCollision::SideCollisions::Right;
			}
			else if (vec.x > 0.35 && vec.x < 0.8)
			{
				//goc trong khoang -35 -> -70
				gameCollision._side = GameCollision::SideCollisions::BottomRight;
			}
			else if (vec.x <= 0.35f && vec.x >= -0.35)
			{
				//goc trong khoang -70 -> -110
				gameCollision._side = GameCollision::SideCollisions::Bottom;
			}
			else if (vec.x < -0.35f && vec.x > -0.8f)
			{
				//goc trong khoang -110 -> -145
				gameCollision._side = GameCollision::SideCollisions::BottomLeft;
			}
			else
			{
				//goc trong khoang -145 -> -180
				gameCollision._side = GameCollision::SideCollisions::Left;
			}
		}
	}

	return gameCollision;
}

bool GameCollision::IsCollided()
{
	return _isCollided;
}

GameCollision::SideCollisions GameCollision::GetSide()
{
	return _side;
}

bool GameCollision::RectMeeting(const RECT& rect1, const RECT& rect2)
{
	if (rect1.left <= rect2.right && rect2.left <= rect1.right &&
		rect1.top <= rect2.bottom && rect2.top <= rect1.bottom)
		return true;
	return false;
}


GameCollision GameCollision::SweptAABB(RECT move, RECT obstacle, float speedX, float speedY)
{
	GameCollision gameCollision;
	//GameCollision::SideCollisions direction = GameCollision::SideCollisions::UnKnow;
	//gameCollision._isCollided = true;

	RECT intersect;
	bool isIntersect = IntersectRect(&intersect, &move, &obstacle);

	// level 1
	//////////////////////////////
	if (!RectMeeting(move, obstacle) &&
		!isIntersect)
	{
		gameCollision._isCollided = false;
	}
	else
	{
		// level 2 Broading box
		//////////////////////////////
		//RECT BroadPhaseBox;
		//BroadPhaseBox.top = speedY > 0 ? move.top : move.top + speedY / 1000 * dt;
		//BroadPhaseBox.left = speedX > 0 ? move.left : move.left + speedX / 1000 * dt;
		//BroadPhaseBox.right = speedX < 0 ? move.right : move.right + speedX / 1000 * dt;
		//BroadPhaseBox.bottom = speedY < 0 ? move.bottom : move.bottom + speedY / 1000 * dt;
		//if (!RectMeeting(BroadPhaseBox, obstacle))
		//{
		//	gameCollision._side = GameCollision::SideCollisions::UnKnow;
		//	gameCollision._isCollided = false;
		//}

		// level 3 SweptAABB
		//////////////////////////////
		if (!gameCollision._isCollided && ENABLE_SWEPTAABB)
		{

			if (speedX == 0)
				speedX = 0.0001f;
			if (speedY == 0)
				speedY = 0.0001f;

			float x_inv_entry, x_inv_exit;
			float y_inv_entry, y_inv_exit;

			if (speedX > 0)
			{
				x_inv_entry = (float)(obstacle.left - move.right);
				x_inv_exit = (float)(obstacle.right - move.left);
			}
			else
			{
				x_inv_entry = (float)(obstacle.right - move.left);
				x_inv_exit = (float)(obstacle.left - move.right);
			}

			if (speedY > 0)
			{
				y_inv_entry = (float)(obstacle.top - move.bottom);
				y_inv_exit = (float)(obstacle.bottom - move.top);
			}
			else
			{
				y_inv_entry = (float)(obstacle.bottom - move.top);
				y_inv_exit = (float)(obstacle.top - move.bottom);
			}

			float xEntry, xExit;
			float yEntry, yExit;

			xEntry = x_inv_entry / speedX;
			xExit = x_inv_exit / speedX;

			yEntry = y_inv_entry / speedY;
			yExit = y_inv_exit / speedY;

			float entryTime = max(xEntry, yEntry);
			float exitTime = min(xExit, yExit);

			if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
			{
				gameCollision._side = GameCollision::SideCollisions::UnKnow;
				gameCollision._isCollided = false;

				return gameCollision;
			}
		}

		gameCollision._isCollided = true;

		float xCenterCollisionRegion = intersect.left + (intersect.right - intersect.left) / 2.0f;
		float yCenterCollisionRegion = intersect.top + (intersect.bottom - intersect.top) / 2.0f;

		float xCenter1 = move.left + (move.right - move.left) / 2.0f;
		float yCenter1 = move.top + (move.bottom - move.top) / 2.0f;

		D3DXVECTOR2 centerCollisionRegion = D3DXVECTOR2(xCenterCollisionRegion, yCenterCollisionRegion);
		D3DXVECTOR2 centerRect1 = D3DXVECTOR2(xCenter1, yCenter1);

		//vector noi tam Rect va Collision Region
		D3DXVECTOR2 vec = centerCollisionRegion - centerRect1;

		//chuan hoa vector
		D3DXVec2Normalize(&vec, &vec);

		if (vec.y < 0)
		{
			//collision top

			if (vec.x >= 0.8f)
			{
				//goc trong khoang 0 -> 35
				gameCollision._side = GameCollision::SideCollisions::Right;
			}
			else if (vec.x > 0.35f && vec.x < 0.8f)
			{
				//goc trong khoang 35 -> 70
				gameCollision._side = GameCollision::SideCollisions::TopRight;
			}
			else if (vec.x <= 0.35f && vec.x >= -0.35f)
			{
				//goc trong khoang 70 -> 110
				gameCollision._side = GameCollision::SideCollisions::Top;
			}
			else if (vec.x < -0.35f && vec.x >= -0.8f)
			{
				//goc trong khoang 110 -> 145
				gameCollision._side = GameCollision::SideCollisions::TopLeft;
			}
			else
			{
				//goc trong khoang 145 -> 180
				gameCollision._side = GameCollision::SideCollisions::Left;
			}
		}
		else
		{
			//collision bottom

			if (vec.x >= 0.8)
			{
				//goc trong khoang 0 -> -35
				gameCollision._side = GameCollision::SideCollisions::Right;
			}
			else if (vec.x > 0.35 && vec.x < 0.8)
			{
				//goc trong khoang -35 -> -70
				gameCollision._side = GameCollision::SideCollisions::BottomRight;
			}
			else if (vec.x <= 0.35f && vec.x >= -0.35)
			{
				//goc trong khoang -70 -> -110
				gameCollision._side = GameCollision::SideCollisions::Bottom;
			}
			else if (vec.x < -0.35f && vec.x > -0.8f)
			{
				//goc trong khoang -110 -> -145
				gameCollision._side = GameCollision::SideCollisions::BottomLeft;
			}
			else
			{
				//goc trong khoang -145 -> -180
				gameCollision._side = GameCollision::SideCollisions::Left;
			}
		}
	}
	///// true here
	//// check side collision


	return gameCollision;
};