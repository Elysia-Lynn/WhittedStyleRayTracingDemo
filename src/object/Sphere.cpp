#include"Sphere.h"

rt::FloatVec3 Sphere::getNormal(rt::FloatVec3 point) {
	float x = point.getX() - centre.getX();
	float y = point.getY() - centre.getY();
	float z = point.getZ() - centre.getZ();
	return rt::FloatVec3(x,y,z).normalize();
}