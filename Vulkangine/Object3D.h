#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "Icosaptree.h"

class Object3D : public AbstractObject
{
private:
	Vector3 position;
	float radius;

public:
	Object3D(Vector3 position, float radius);
	BoundingSphere getBoundingSphere();

};

#endif 