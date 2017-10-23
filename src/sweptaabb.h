#ifndef _SWEPT_AABB_H
#define _SWEPT_AABB_H
#include <math.h>
#include <algorithm>
#include <limits>
struct Box
{ 
public:
	float	x, y;
	//nsiondim
	float	w, h;
	//veclocity
	float	vx, vy;
	float collisionTime;
	int _Type;
	Box();
	Box(float, float, float, float, float, float);
	Box(float, float, float, float);
	void InitBox(float, float, float, float, float, float);
	void InitBlock(float, float, float, float);
	void setPosition(float, float);

	void setVx(float);
	void setVy(float);
	//position of top - left corner
	
};

extern bool AABBCheck(Box b1, Box b2);
extern bool AABB(Box b1, Box b2, float& moveX, float& moveY);
extern Box GetSweptBroadphaseBox(Box b);
extern float SweptAABB(Box b1, Box b2, float& normalx, float& normaly);
extern int Collide(Box &box, Box &block);
extern int CollideCheck(Box& box, Box &block);
#endif