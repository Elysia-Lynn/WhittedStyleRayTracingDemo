#pragma once

#include <iostream>
#include<cmath>

namespace rt {

	//改进点：可以好好考虑一下这个vec怎么写
	class FloatVec3 {
	public:
		FloatVec3() = default;
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

		//回去严肃学习一下这块+严肃补一下引用，感觉引用学的一般呢
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

		FloatVec3& operator*=(float n) {
			this->x *= n;
			this->y *= n;
			this->z *= n;
			return *this;
		}

		//回去严肃学习一下inline和友元函数
		FloatVec3 multiply(float n) {
			float newX = x*n;
			float newY = y*n;
			float newZ= z*n;
			return FloatVec3(newX,newY,newZ);
		}

		FloatVec3 operator+(const FloatVec3& vec)const {
			return FloatVec3(x + vec.getX(), y + vec.getY(), z + vec.getZ());
		}

		FloatVec3 normalize();
		float cosine(FloatVec3 vec);		//算向量夹角
		float distance(FloatVec3 pos);		//算距离平方

	private:
		float x;
		float y;
		float z;
	};
}