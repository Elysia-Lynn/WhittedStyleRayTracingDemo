#include"Ray.h"

rt::FloatVec3 Ray::pointAtParameter(float t) {
	float x = point.getX() + t * direction.getX();
	float y = point.getY() + t * direction.getY();
	float z = point.getZ() + t * direction.getZ();
	return rt::FloatVec3(x, y, z);
}