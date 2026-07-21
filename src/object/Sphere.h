#include<iostream>
#include"math/FloatVec3.h"

class Sphere {
public:
	Sphere(rt::FloatVec3 centre, rt::FloatVec3 color, float radius, rt::FloatVec3 reflectivity,float refraction) {
		this->centre = centre;
		this->color = color;
		this->radius = radius;
		this->reflectivity = reflectivity;
		this->refraction = refraction;
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

	float getRefraction() {
		return refraction;
	}

	rt::FloatVec3 getNormal(rt::FloatVec3);		//参数是点坐标,指向球外，归一化过了

private:
	rt::FloatVec3 centre;
	float radius;
	rt::FloatVec3 reflectivity;		//漫反射，镜面反射，折射占比
	rt::FloatVec3 color;	
	float refraction;
};