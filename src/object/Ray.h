#include<iostream>
#include"math/FloatVec3.h"

class Ray {
public:
	//´ÓstartÖ¸Ïògoal
	Ray(rt::FloatVec3 start,rt::FloatVec3 goal,float reflectionIndex) {
		point=start;
		float x = goal.getX() - start.getX();
		float y = goal.getY() - start.getY();
		float z = goal.getZ() - start.getZ();
		direction = rt::FloatVec3(x, y, z).normalize();
		this->refractionIndex = refractionIndex;
	}

	rt::FloatVec3 getPoint() const{
		return point;
	}

	rt::FloatVec3 getDirection() const{
		return direction;
	}

	float getRefractionIndex() const {
		return refractionIndex;
	}

	rt::FloatVec3 pointAtParameter(float t);

private:
	rt::FloatVec3 point;
	rt::FloatVec3 direction;
	float refractionIndex;
};