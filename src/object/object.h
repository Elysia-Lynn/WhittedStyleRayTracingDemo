#include <iostream>
#include <vector>
#include "math/FloatVec3.h"

struct TrianglePrimitive {
	rt::floatVec3 location;
	rt::FloatVec3 color;
	rt::FloatVec3 normal;
	rt::FloatVec3 reflectivity;
};

class Object {
public:
	void addPrimitive(const TrianglePrimitive& primitive);
	void usePrimitive(int index);
private:
	std::vector<TrianglePrimitive> triangles;
};