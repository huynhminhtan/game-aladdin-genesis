#include	"QuadTree.h"
#include	"CGame.h"
using namespace std;
ofstream	outfile;
QNode::QNode()
{
}
TreeObject::~TreeObject()
{
}

QNodeOptimize::QNodeOptimize()
{
}

QNodeOptimize::QNodeOptimize(float x0, float y0, float x1, float y1)
{
	this->x0 = x0;
	this->x1 = x1;
	this->y0 = y0;
	this->y1 = y1;
}

void QNodeOptimize::deleteObject(int id)
{
	for (int i = 0; i < ObjectId.size(); i++)
	if (id == ObjectId.at(i))
	{
		ObjectId.erase(ObjectId.begin() + i);
		break;
	}
}

QNode::QNode(float x0, float y0, float x1, float y1)
{
	this->x0 = x0;
	this->x1 = x1;
	this->y0 = y0;
	this->y1 = y1;
}

void QNode::deleteObject(int id)
{
	for (int i = 0; i < object.size(); i++)
		if (id == object.at(i).id)
		{
			object.erase(object.begin() + i);
			break;
		}
}

void SaveQuadTree(QNode *n)
{
	outfile << n->NodeID << " " << n->x0 << " " << n->y0 << " " << n->x1 << " " << n->y1 << " ";
	for (int i = 0; i < n->object.size(); i++)
	{
		outfile << n->object.at(i).id << " ";
	}
	outfile<<"\n";
	if(n->lt!=NULL) 
		SaveQuadTree(n->lt);
	if(n->rt!=NULL)	
		SaveQuadTree(n->rt);
	if(n->lb!=NULL)	
		SaveQuadTree(n->lb);
	if(n->rb!=NULL)	
		SaveQuadTree(n->rb);
}

void clip(TreeObject obj,QNode *node)
{
	bool	LEFT	= false,
			RIGHT	= false,
			TOP		= false, 
			BOTTOM	= false;
	if ( obj.x0 < node->x0 )
	{
		obj.x0 = node->x0;
		LEFT = true;
	}
	else 
		if ( obj.x0 < node->x1 )
			LEFT = true;
	if ( obj.x1 > node->x1 )
	{
		obj.x1 = node->x1;
		RIGHT = true;
	} 
	else
		if ( (obj.x1> node->x0) )
			RIGHT = true;


	if ( obj.y0 < node->y0 )
	{
		obj.y0 = node->y0;
		TOP = true;
	}
	else
		if ( obj.y0 < node->y1 )
			TOP = true;

	if ( obj.y1 > node->y1)
	{
		obj.y1 = node->y1;
		BOTTOM = true;
	}
	else
		if (obj.y1 > node->y0 )
			BOTTOM = true;

	if ( LEFT && RIGHT && TOP && BOTTOM && (obj.x1 - obj.x0 > 0 ) && (obj.y1 - obj.y0 > 0 ))
		node->object.push_back(obj);
}

int isCliped(TreeObject obj, QNodeOptimize *node)
{
	return !(obj.x1  < node->x0 || obj.x0 > node->x1 || obj.y1 < node->y0 || obj.y0 > node->y1);
}

RECT DefineRootNode(vector<GameObject> gameObject)
{
	float minx = gameObject.at(0).x0,
		maxx = gameObject.at(0).x1,
		miny = gameObject.at(0).y0,
		maxy = gameObject.at(0).y1;
	for (int i = 0; i < gameObject.size(); i++)
	{
		float x0 = gameObject.at(i).x0;
		float y0 = gameObject.at(i).y0;
		float x1 = x0 + gameObject.at(i).x1;
		float y1 = y0 + gameObject.at(i).y1;
		if (minx > x0)
			minx = x0;
		if (maxx < x1)
			maxx = x1;
		if (miny > y0)
			miny = y0;
		if (maxy < y1)
			maxy = y1;
	}

	/*
	if (maxx <= maxy) 
		maxx = (maxy / 2 ) * 2 + ((int)maxy % 2) * 2;
	if (maxx >= maxy)
		maxy = (maxx / 2 ) * 2 + ((int)maxx % 2) * 2;
	*/
	/**/
	float temp = 0;
	if (maxx - minx > maxy - miny)
		temp = maxx - minx;
	else
		temp = maxy - miny;

	maxx = minx + temp;
	maxy = temp + miny;

	RECT RootNode;
	RootNode.left	= minx;
	RootNode.right	= maxx;
	RootNode.top	= miny;
	RootNode.bottom = maxy;
	return RootNode;
}

void build(QNode *n)
{
	if (( n->x1 - n->x0 > /*SCREENWIDTH **/ 2)&&
		(n->y1 - n->y0 > /*SCREENHEIGHT **/ 2)&&
		(n->object.size() > 0))
	{
		n->lt = new QNode(n->x0,						n->y0,							n->x0 + (n->x1 - n->x0) / 2,	n->y0 +(n->y1 - n->y0) / 2);
		n->rt = new QNode(n->x0 + (n->x1 - n->x0) / 2,	n->y0,							n->x1,							n->y0 +(n->y1 - n->y0) / 2);
		n->lb = new QNode(n->x0,						n->y0 + (n->y1 - n->y0) / 2,	n->x0 + (n->x1 - n->x0) / 2,	n->y1);
		n->rb = new QNode(n->x0 + (n->x1 - n->x0) / 2,	n->y0 + (n->y1 - n->y0) / 2,	n->x1,							n->y1);

		n->lt->NodeID = n->NodeID * 4 + 1;
		n->rt->NodeID = n->NodeID * 4 + 2;
		n->lb->NodeID = n->NodeID * 4 + 3;
		n->rb->NodeID = n->NodeID * 4 + 4;
		for (int i = 0; i < n->object.size(); i++)
		{
			clip(n->object.at(i), n->lt);
			clip(n->object.at(i), n->rt);
			clip(n->object.at(i), n->lb);
			clip(n->object.at(i), n->rb);
		}
		build(n->lt);
		build(n->rt);
		build(n->lb);
		build(n->rb);
		n->object.clear();
	}
}