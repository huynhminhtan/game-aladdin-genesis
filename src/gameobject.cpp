#include "GameObject.h"

GameObject::~GameObject()
{}
GameObject::GameObject(int id,int type,int x, int y, int width, int height)
{
	this->id = id;
	this->type = type;
	this->x0 = x;
	this->x1 = width;
	this->y0 = y;
	this->y1 = height;
	this->flip = 0;
}

GameObject::GameObject()
{
}