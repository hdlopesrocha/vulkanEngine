#ifndef ICOSAPTREE_H
#define ICOSAPTREE_H

class IcosaptreeNode;
class Icosaptree;

#include "AbstractSpace.h"
#include "BoundingSphere.h"
#include "MathHelper.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>


class IcosaptreeNode {
public:
	IcosaptreeNode * parent;
	IcosaptreeNode * child[27];
	//std::unordered_map<char, IcosaptreeNode *> child;
	//std::map<int, IcosaptreeNode *> child;
	//std::vector<IcosaptreeNode*> child;

	std::vector<AbstractObject*> objects;
	Vector3 corner;
	float size;

	~IcosaptreeNode();
	IcosaptreeNode(IcosaptreeNode * parent, Vector3 corner, float size);
	bool intersects(BoundingSphere sphere);
	bool contains(BoundingSphere sphere);
	bool canSplit();

	std::string toString();
	long total();
};

class Icosaptree {
public:
	IcosaptreeNode * root;
	Icosaptree(int minNodeSize);
	void expand(BoundingSphere sphere);
	void insert(AbstractObject * object);
	Icosaptree * clear();
};

#endif