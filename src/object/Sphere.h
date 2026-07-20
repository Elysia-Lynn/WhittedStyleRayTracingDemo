#include<iostream>
#include"math/FloatVec3.h"

class Sphere {
public:
	Sphere(rt::FloatVec3 centre, rt::FloatVec3 color, float radius, rt::FloatVec3 reflectivity) {
		this->centre = centre;
		this->color = color;
		this->radius = radius;
		this->reflectivity = reflectivity;
	}

	rt::FloatVec3 getCenter() {
		return centre;
	}

	float getRadius() {
		return radius;
	}

	rt::FloatVec3 getReflectivity() {
		return reflectivity;
	}
	rt::FloatVec3 getColor(){
		return color;
	}
	rt::FloatVec3 getNormal(rt::FloatVec3);		//参数是点坐标

private:
	rt::FloatVec3 centre;
	float radius;
	rt::FloatVec3 reflectivity;
	rt::FloatVec3 color;	//漫反射，镜面反射，折射
};