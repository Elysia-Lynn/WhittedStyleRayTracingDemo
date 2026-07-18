#include <iostream>

namespace rt {
	class FloatVec3 {
	public:

		FloatVec3(float x, float y, float z) ;

		float getX() const;

		float getY() const;

		float getZ() const;

	private:
		float x;
		float y;
		float z;
	};
}