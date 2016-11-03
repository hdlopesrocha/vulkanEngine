#ifndef ABSTRACT_SPACE_H
#define ABSTRACT_SPACE_H

#include "BoundingSphere.h"

class AbstractNode {

};

class AbstractObject {
public:
	AbstractNode * node;
	virtual BoundingSphere getBoundingSphere() = 0;
};

class AbstractSpace {
	virtual void insert(AbstractObject * object) = 0;
};

#endif 
