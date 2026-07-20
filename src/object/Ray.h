#include<iostream>
#include"math/FloatVec3.h"

class Ray {
public:
	Ray(rt::FloatVec3 start,rt::FloatVec3 goal) {
		point=start;
		float x = goal.getX() - start.getX();
		float y = goal.getY() - start.getY();
		float z = goal.getZ() - start.getZ();
		direction = rt::FloatVec3(x, y, z).normalize();
	}

	rt::FloatVec3 getPoint() const{
		return point;
	}

	rt::FloatVec3 getDirection() const{
		return direction;
	}

	rt::FloatVec3 pointAtParameter(float t);

private:
	rt::FloatVec3 point;
	rt::FloatVec3 direction;
};