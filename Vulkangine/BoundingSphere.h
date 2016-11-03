#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#include "Vector3.h"
#include <sstream>

class BoundingSphere {
	public:
		Vector3 center;
		float  radius;
	
		BoundingSphere(Vector3 center, float radius);
		BoundingSphere(float x, float y, float z, float radius);

		std::string toString();
};

#endif