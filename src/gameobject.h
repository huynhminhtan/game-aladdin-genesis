#ifndef GAMEOBJECT_H
#define	GAMEOBJECT_H
#include	<string.h>
#include	<iostream>
using namespace std;
class GameObject{
public:
	GameObject();
	GameObject(int, int, int, int, int, int);
	~GameObject();
	float x0,y0;
	float x1,y1;
	int flip;
	int id;
	int type;
};

#endif // !GAMEOBJECT_H


