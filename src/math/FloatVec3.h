#include <iostream>
#include<cmath>

namespace rt {

	//改进点：可以好好考虑一下这个vec怎么写
	class FloatVec3 {
	public:

		FloatVec3(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
		};

		float getX() const {
			return x;
		};

		float getY() const {
			return y;
		};

		float getZ() const {
			return z;
		};

		FloatVec3& operator+=(const FloatVec3& vec) {
			this->x += vec.getX();
			this->y += vec.getY();
			this->z += vec.getZ();
			return *this;
		}

		FloatVec3& operator-=(const FloatVec3& vec) {
			this->x -= vec.getX();
			this->y -= vec.getY();
			this->z -= vec.getZ();
			return *this;
		}

		FloatVec3& operator*=(const float n) {
			this->x *= n;
			this->y *= n;
			this->z *= n;
			return *this;
		}

		FloatVec3 normalize();
		float cosine(FloatVec3& vec);

	private:
		float x;
		float y;
		float z;
	};
}