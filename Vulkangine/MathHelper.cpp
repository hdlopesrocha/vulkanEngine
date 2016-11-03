#include "MathHelper.h"

bool internalContains(Vector3 corner, float size, BoundingSphere sphere) {
	return (corner.x < sphere.center.x - sphere.radius && sphere.center.x + sphere.radius < corner.x + size &&
		corner.y < sphere.center.y - sphere.radius && sphere.center.y + sphere.radius < corner.y + size &&
		corner.z < sphere.center.z - sphere.radius && sphere.center.z + sphere.radius < corner.z + size);
}


double distCheck(double val, double min, double max) {
	double out = 0;
	if (val < min) {
		out += (min - val) * (min - val);
	}
	if (val > max) {
		out += (val - max) * (val - max);
	}
	return out;
};


double squaredDistance(Vector3 corner, Vector3 point, float size) {
	return	distCheck(point.x, corner.x, corner.x + size)
		+ distCheck(point.y, corner.y, corner.y + size)
		+ distCheck(point.z, corner.z, corner.z + size);
}
