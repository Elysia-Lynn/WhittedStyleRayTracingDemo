#include "FloatVec3.h"

namespace rt {
	FloatVec3 FloatVec3::normalize() {
		float x = this->x;
		float y = this->y;
		float z = this->z;
		constexpr float EPSILON = 1e-4f;
		float length = std::sqrt(x * x + y * y + z * z);
		if (length < EPSILON) {
			return *this;
		}
		else {
			x /= length;
			y /= length;
			z /= length;
			return FloatVec3(x, y, z);
		}
	}

	float FloatVec3::cosine(FloatVec3 vec) {
		FloatVec3 vec1 = (*this).normalize();
		FloatVec3 vec2 = vec.normalize();
		return vec1.getX() * vec2.getX() + vec1.getY() * vec2.getY() + vec1.getZ() * vec2.getZ();
	}

	float FloatVec3::distance(FloatVec3 pos) {
		return pow(this->x - pos.getX(), 2) + pow(this->y - pos.getY(), 2) + pow(this->z - pos.getZ(), 2);
	}
}