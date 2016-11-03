#ifndef MATH_HELPER_H
#define MATH_HELPER_H


#include "Vector3.h"
#include "BoundingSphere.h"

bool internalContains(Vector3 corner, float size, BoundingSphere sphere);
double distCheck(double val, double min, double max);
double squaredDistance(Vector3 corner, Vector3 point, float size);

#endif