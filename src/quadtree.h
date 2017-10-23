#ifndef QUADTREE_H
#define	QUADTREE_H
#include	<d3d9.h>
#include	<vector>
#include	<iostream>
#include	<stdlib.h>
#include	<fstream>
#include	<iomanip>
#include	"GameObject.h"

using namespace std;

extern ofstream	outfile;

class TreeObject{
public:
	~TreeObject();
	float x0, y0, x1, y1;
	int id;
	GameObject *target;
};

class QNode{
public:
	QNode();
	float	x0, y0, x1, y1;
	QNode	*lt;
	QNode	*rt;
	QNode	*lb;
	QNode	*rb;
	int		NodeID;
	vector<TreeObject> object;
	QNode(float, float, float, float);
	void deleteObject(int);
};

class QNodeOptimize
{
public:
	QNodeOptimize();
	float	x0, y0, x1, y1;
	QNodeOptimize	*lt;
	QNodeOptimize	*rt;
	QNodeOptimize	*lb;
	QNodeOptimize	*rb;
	int		NodeID;
	vector<int> ObjectId;
	QNodeOptimize(float, float, float, float);
	void deleteObject(int id);
};

void	SaveQuadTree(QNode *);
void	clip(TreeObject, QNode *);
int		isCliped(TreeObject, QNodeOptimize *);
RECT	DefineRootNode(vector<GameObject> );
void	build(QNode*);

#endif // !QUADTREE_H