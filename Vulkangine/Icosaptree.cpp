#include "Icosaptree.h"

#define NODES 27
int minNodeSize;

void writeChild(IcosaptreeNode * parent, int index, IcosaptreeNode * child) {
	parent->child[index] = child;
}

IcosaptreeNode * readChild(IcosaptreeNode * parent, int index) {
	return parent->child[index];
}


void statsInternal(IcosaptreeNode * node,TreeStats * stats)
{
	int childNotNull =0;
	for (int i = 0; i < NODES; ++i) {
		IcosaptreeNode * child = readChild(node, i);
		if (child != NULL) {
			++childNotNull;
			statsInternal(child,stats);
		}
	}
	if (childNotNull == 0) {
		++stats->leafNodes;
	}
	stats->nodesWithObjects += node->objects.size()>0?1:0;
	stats->averageUsage += childNotNull;
	++stats->numberOfNodes;
}

int usedChilds(IcosaptreeNode * node) {
	int n = 0;
	for (int i = 0; i < NODES; ++i) {
		if(node->child[i]!=NULL){
			++n;
		}
	}
	return n;
}


Vector3 getAbstractCorner(int index) {
	switch (index) {
		// corners
	case 0: return Vector3(0, 0, 0);
	case 1: return Vector3(0, 0, 2);
	case 2: return Vector3(0, 2, 0);
	case 3: return Vector3(0, 2, 2);
	case 4: return Vector3(2, 0, 0);
	case 5: return Vector3(2, 0, 2);
	case 6: return Vector3(2, 2, 0);
	case 7: return Vector3(2, 2, 2);
		// middle faces
	case 8: return Vector3(0, 1, 1);
	case 9: return Vector3(1, 0, 1);
	case 10: return Vector3(1, 1, 0);
	case 11: return Vector3(1, 1, 2);
	case 12: return Vector3(1, 2, 1);
	case 13: return Vector3(2, 1, 1);
		// middle edges
	case 14: return Vector3(0, 0, 1);
	case 15: return Vector3(0, 1, 0);
	case 16: return Vector3(0, 1, 2);
	case 17: return Vector3(0, 2, 1);
	case 18: return Vector3(1, 0, 0);
	case 19: return Vector3(1, 0, 2);
	case 20: return Vector3(1, 2, 0);
	case 21: return Vector3(1, 2, 2);
	case 22: return Vector3(2, 0, 1);
	case 23: return Vector3(2, 1, 0);
	case 24: return Vector3(2, 1, 2);
	case 25: return Vector3(2, 2, 1);
		//center
	case 26: return Vector3(1, 1, 1);
	default: return Vector3();
	}
}


Vector3 getCorner(IcosaptreeNode * parent, int index) {
	Vector3 shift = getAbstractCorner(index)*(0.25*parent->size);
	return parent->corner + shift;
}

bool childContains(IcosaptreeNode * parent, int index, BoundingSphere sphere) {
	Vector3 corner = getCorner(parent, index);
	float newSize = parent->size*0.5;
	return internalContains(corner, newSize, sphere);
}


IcosaptreeNode::~IcosaptreeNode() {
	this->objects.clear();
}

void compress(Icosaptree * tree) {
	while (true)
	{		
		if(tree->root->objects.size()==0){
			IcosaptreeNode * candidate = NULL;
			for (int i = 0; i < NODES; ++i) {
				IcosaptreeNode * child = readChild(tree->root, i);
				if (child != NULL) {
					if (candidate != NULL) {
						candidate = NULL;
						break;
					}
					candidate = child;
				}
			}
			if (candidate != NULL) {
				delete tree->root;
				tree->root = candidate;
				tree->root->parent = NULL;
				continue;
			}
		}
		break;	
	}
}


IcosaptreeNode * getContainingNode(IcosaptreeNode * node, BoundingSphere sphere) {
	while (true) {
		bool childContain = false;
		if(node->canSplit()){
			for (int i = 0; i < NODES; ++i) {
				if (childContains(node, i, sphere)) {
					if (readChild(node, i) == NULL) {
						Vector3 corner = getCorner(node, i);
						float newSize = node->size*0.5;
						writeChild(node, i, new IcosaptreeNode(node, corner, newSize));
					}
					node = readChild(node, i);
					childContain = true;
					break;
				}
			}
		}
		if (!childContain) {
			return node;
		}
	}
}

void internalDelete(IcosaptreeNode * node){
	for(int i=0;i < node->objects.size(); ++i){
		delete node->objects[i];
	}
	node->objects.clear();
	for(int i=0;i < NODES; ++i){
		IcosaptreeNode * child = node->child[i];
		if(child!=NULL){
			internalDelete(child);
		}
	}


	delete node;
}

Icosaptree * Icosaptree::clear()
{
	internalDelete(root);
	return this;
}

TreeStats Icosaptree::stats()
{
	TreeStats result;
	statsInternal(root, &result);
	if(result.numberOfNodes!=0){
		result.averageUsage /= NODES * result.numberOfNodes;
	}
	else {
		result.averageUsage = 0;
	}
	return result;
}


Icosaptree::Icosaptree(int mns)
{
	root = new IcosaptreeNode(NULL, Vector3(), 1);
	minNodeSize = mns;
}


void Icosaptree::insert(AbstractObject * object) {
	BoundingSphere sphere = object->getBoundingSphere();
	expand(sphere);
	IcosaptreeNode * node = getContainingNode(root, sphere);
	node->objects.push_back(object);
	compress(this);
}

std::string IcosaptreeNode::toString() {
	std::stringstream ss;
	ss << "{\"corner\":" << this->corner.toString() << ",\"size\":" << size << "}";
	return ss.str();
}

IcosaptreeNode::IcosaptreeNode(IcosaptreeNode * parent, Vector3 corner, float size) {
	this->corner = corner;
	this->size = size;
	this->parent = parent;
	for(int i=0; i < NODES; ++i){
		this->child[i] = NULL;
	}
}

bool IcosaptreeNode::intersects(BoundingSphere sphere) {
	return squaredDistance(corner, sphere.center, size) <= (sphere.radius * sphere.radius);
}

bool IcosaptreeNode::contains(BoundingSphere sphere) {
	return internalContains(corner, size, sphere);
}

bool IcosaptreeNode::canSplit()
{
	return size > minNodeSize;
}

void Icosaptree::expand(BoundingSphere sphere)
{
	while (true) {
		IcosaptreeNode * node = root;
		if (!node->contains(sphere)) {
			float middle = node->size * 0.5f;
			int index = 0;
			float newSize = node->size * 2.0f;
			float shift = 0.5*newSize;
			Vector3 shiftVec = Vector3();

			if (sphere.center.x < node->corner.x + middle) {
				index += 1;
				shiftVec.x -= shift;
			}
			if (sphere.center.y < node->corner.y + middle) {
				index += 2;
				shiftVec.y -= shift;
			}
			if (sphere.center.z < node->corner.z + middle) {
				index += 4;
				shiftVec.z -= shift;
			}
			root = new IcosaptreeNode(NULL, node->corner + shiftVec, newSize);
			if (usedChilds(node) == 0 && node->objects.size() == 0) {
				delete node;
			}
			else {
				writeChild(root, index, node);
			}
		}
		else {
			break;
		}
	}
}

std::string TreeStats::toString()
{
	std::stringstream ss;
	ss << "{\"numberOfNodes\":" << this->numberOfNodes << ",\"averageUsage\":" << averageUsage << ",\"nodesWithObjects\":" << nodesWithObjects << ",\"leafNodes\":" << leafNodes << "}";
	return ss.str();
}

TreeStats::TreeStats()
{
	numberOfNodes = averageUsage = nodesWithObjects = leafNodes =0;
}
