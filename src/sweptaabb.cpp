#include <cmath>
#include "SweptAABB.h"
// describes an axis-aligned rectangle with a velocity
Box::Box()
{
	collisionTime = 1;
}

Box::Box(float _x, float _y, float _w, float _h, float _vx, float _vy)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	vx = _vx;
	vy = _vy;
	collisionTime = 1;
}
Box::Box(float _x, float _y, float _w, float _h)
{
	collisionTime = 1;
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	vx = 0.0f;
	vy = 0.0f;
	collisionTime = 1;
}
void Box::InitBox(float _x, float _y, float _w, float _h, float _vx, float _vy)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	vx = _vx;
	vy = _vy;
}

void Box::InitBlock(float _x, float _y, float _w, float _h)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	vx = 0.0f;
	vy = 0.0f;
}

void Box::setPosition(float _x, float _y)
{
	x = _x;
	y = _y;
}

void Box::setVx(float Vx)
{
	vx = Vx;
}

void Box::setVy(float Vy)
{
	vy = Vy;
}

// returns true if the boxes are colliding (velocities are not used)
bool AABBCheck(Box b1, Box b2)
{
	return !(b1.x + b1.w < b2.x || b1.x > b2.x + b2.w || b1.y + b1.h < b2.y || b1.y > b2.y + b2.h);
}

// returns true if the boxes are colliding (velocities are not used)
// moveX and moveY will return the movement the b1 must move to avoid the collision
bool AABB(Box b1, Box b2, float& moveX, float& moveY)
{
	moveX = moveY = 0.0f;

	float l = b2.x - (b1.x + b1.w);
	float r = (b2.x + b2.w) - b1.x;
	float t = b2.y - (b1.y + b1.h);
	float b = (b2.y + b2.h) - b1.y;

	// check that there was a collision
	if (l > 0 || r < 0 || t > 0 || b < 0)
		return false;

	// find the offset of both sides
	moveX = abs(l) < r ? l : r;
	moveY = abs(t) < b ? t : b;

	// only use whichever offset is the smallest
	if (abs(moveX) < abs(moveY))
		moveY = 0.0f;
	else
		moveX = 0.0f;

	return true;
}

// returns a box the spans both a current box and the destination box
Box GetSweptBroadphaseBox(Box b)
{
	Box broadphasebox(0.0f, 0.0f, 0.0f, 0.0f);

	broadphasebox.x = b.vx > 0 ? b.x : b.x + b.vx;
	broadphasebox.y = b.vy > 0 ? b.y : b.y + b.vy;
	broadphasebox.w = b.vx > 0 ? b.vx + b.w : b.w - b.vx;
	broadphasebox.h = b.vy > 0 ? b.vy + b.h : b.h - b.vy;

	return broadphasebox;
}

// performs collision detection on moving box b1 and static box b2
// returns the time that the collision occured (where 0 is the start of the movement and 1 is the destination)
// getting the new position can be retrieved by box.x = box.x + box.vx * collisiontime
// normalx and normaly return the normal of the collided surface (this can be used to do a response)
float SweptAABB(Box b1, Box b2, float& normalx, float& normaly)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (b1.vx > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.w);
		xInvExit = (b2.x + b2.w) - b1.x;
	}
	else
	{
		xInvEntry = (b2.x + b2.w) - b1.x;
		xInvExit = b2.x - (b1.x + b1.w);
	}

	if (b1.vy > 0.0f)
	{
		yInvEntry = b2.y - (b1.y + b1.h);
		yInvExit = (b2.y + b2.h) - b1.y;
	}
	else
	{
		yInvEntry = (b2.y + b2.h) - b1.y;
		yInvExit = b2.y - (b1.y + b1.h);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / b1.vx;
		xExit = xInvExit / b1.vx;
	}

	if (b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / b1.vy;
		yExit = yInvExit / b1.vy;
	}

	// find the earliest/latest times of collision
	float entryTime = std::max(xEntry, yEntry);
	float exitTime = std::min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// return the time of collision
		return entryTime;
	}
}

int Collide(Box& box, Box &block)
{
	// box is the moving box
	// block is the static box
	Box broadphasebox = GetSweptBroadphaseBox(box);
	if (AABBCheck(broadphasebox, block))
	{
		float normalx, normaly;
		float collisiontime = SweptAABB(box, block, normalx, normaly);
		float remainingtime = 1.0f - collisiontime;
		if (collisiontime < 1.0f)
		{
			if (box.collisionTime > collisiontime)
				box.collisionTime = collisiontime;
			if (normalx == -1)
 				return 2;
			if (normalx == 1)
				return 1;
			if (normaly == -1)
				return 4;
			if (normaly == 1)
				return 3;
		}
		else
		if (AABBCheck(box, block))
		{
			return 5;
		}
	}
	return 0;
}

int CollideCheck(Box& box, Box &block)
{
	// box is the moving box
	// block is the static box

	//lam tron van toc
	int temp = box.vx * 1000;
	box.vx = temp / 1000;
	temp = box.vy * 1000;
	box.vy = temp / 1000;
	Box broadphasebox = GetSweptBroadphaseBox(box);
	if (AABBCheck(broadphasebox, block))
	{
		float normalx, normaly;
		float collisiontime = SweptAABB(box, block, normalx, normaly);
		float remainingtime = 1.0f - collisiontime;
		if (collisiontime < 1.0f)
		{
			if (normalx == -1)
				return 2;
			if (normalx == 1)
				return 1;
			if (normaly == -1)
				return 4;
			if (normaly == 1)
				return 3;

		}
		else
		if (AABBCheck(box, block))
		{
			return 5;
		}
	}
	return 0;
}