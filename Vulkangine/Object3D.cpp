#include "Object3D.h"

Object3D::Object3D(Vector3 position, float radius){
	this->position = position;
	this->radius = radius;
}

BoundingSphere Object3D::getBoundingSphere()
{
	return BoundingSphere(position,radius);
}
