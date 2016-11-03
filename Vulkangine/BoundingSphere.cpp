#include "BoundingSphere.h"

BoundingSphere::BoundingSphere(Vector3 center, float radius)
{
	this->center = center;
	this->radius = radius;
}

BoundingSphere::BoundingSphere(float x, float y, float z, float radius)
{
	this->center = Vector3(x,y,z);
	this->radius = radius;
}

std::string BoundingSphere::toString()
{
	std::stringstream ss;
	ss << "{\"center\":" << this->center.toString() << ",\"radius\":" << radius << "}";
	return ss.str();
}
