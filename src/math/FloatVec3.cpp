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

	FloatVec3 FloatVec3::cross(FloatVec3 vec) {
		float x1 = x;
		float y1 = y;
		float z1 = z;
		float x2 = vec.getX();
		float y2 = vec.getY();
		float z2 = vec.getZ();
		return FloatVec3(y1 * z2 - z1 * y2, x2 * z1 - x1 * z2, x1*y2 - x2*y1);
	}

	float FloatVec3::dot(FloatVec3 vec) {
		return x * vec.getX() + y * vec.getY() + z * vec.getZ();
	}
}