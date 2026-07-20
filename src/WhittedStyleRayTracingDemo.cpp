// WhittedStyleRayTracingDemo.cpp: 定义应用程序的入口点。
//

#include "WhittedStyleRayTracingDemo.h"

#define EPSILON 1e-4f

int regulate(int);
rt::FloatVec3 calculateColor(std::vector<Sphere>, Ray,int,rt::FloatVec3&);
bool examine(std::vector<Sphere>, Ray);

const rt::FloatVec3 cameraPos = rt::FloatVec3(0.0f, 0.0f, 0.0f);
const rt::FloatVec3 lightPos = rt::FloatVec3(0.0f, 5.0f, 0.0f);

int main()
{
	std::vector<Sphere>globes;
	globes.emplace_back(Sphere(rt::FloatVec3(0.0f, -100.5f, -4.5f),
		rt::FloatVec3(0.5f, 0.5f, 0.5f),
		100.0f, rt::FloatVec3(1.0f, 0.0f, 0.0f)));
	globes.emplace_back(Sphere(rt::FloatVec3(-1.0f, 0.0f, -4.5f),
		rt::FloatVec3(1.0f, 1.0f, 1.0f),
		0.6f, rt::FloatVec3(0.1f, 0.9f, 0.0f)));
	globes.emplace_back(Sphere(rt::FloatVec3(0.0f, 0.0f, -1.0f),
		rt::FloatVec3(1.0f, 1.0f, 1.0f),
		0.4f, rt::FloatVec3(0.0f, 0.1f, 0.9f)));
	globes.emplace_back(Sphere(rt::FloatVec3(1.0f, 0.0f, -1.0f),
		rt::FloatVec3(0.8f, 0.1f, 0.1f),
		0.7f, rt::FloatVec3(0.8f, 0.2f, 0.0f)));

	const float imagePlaneZ = -1.0f;
	const int width = 150;
	const int height = 100;
	//可改进点：pixelLength可以用一个函数来根据cameraPos width height imagePlaneZ计算得出
	const float pixelLength=0.005;		

	std::ofstream out("image.ppm");
	out << "P3\n" << width << " " << height << "\n255\n";

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			float pixelCentreX = (i - width / 2.0 + 0.5) * pixelLength;
			float pixelCentreY = (j - height / 2.0 + 0.5) * pixelLength;
			rt::FloatVec3 pixelCentrePos = rt::FloatVec3(pixelCentreX,pixelCentreY,imagePlaneZ);
			Ray ray = Ray(pixelCentrePos, cameraPos);

			rt::FloatVec3 rgb = rt::FloatVec3(0.0f, 0.0f, 0.0f);
			//在这里我们使用了深度来防无限循环，也可以用能量来衡量，后面试试（注意到能量不能单独用，比方说两个镜面对弹，那真是完了）
			int depth = 0;
			//如果全黑首先怀疑这里是不是没改！先强制rgb=试一下
			calculateColor(globes, ray,depth,rgb);
			
			int r = rgb.getX();
			int g = rgb.getY();
			int b = rgb.getZ();
			out << regulate(r) << " " << regulate(g) << " " << regulate(b)<<"\n";
		}
	}

	std::cout << "And that is all.";
	return 0;
}

int regulate(int a) {
	return a * 255.99;
}

rt::FloatVec3 calculateColor(std::vector<Sphere> globes, Ray ray,int depth,rt::FloatVec3& rgb) {
	if (depth >= 2) {
		return rgb;
	}
	else {
		for (int index = 0; index < globes.size(); index++) {
			Sphere globe = globes[index];
			float a = pow(ray.getDirection().getX(), 2) + pow(ray.getDirection().getY(), 2) + pow(ray.getDirection().getZ(), 2);
			float b = 2 * (ray.getDirection().getX() * (ray.getPoint().getX() - globe.getCenter().getX()) + ray.getDirection().getY() * (ray.getPoint().getY() - globe.getCenter().getY()) + ray.getDirection().getZ() * (ray.getPoint().getZ() - globe.getCenter().getZ()));
			float c = pow(ray.getPoint().getX() - globe.getCenter().getX(), 2) + pow(ray.getPoint().getY() - globe.getCenter().getY() + pow(ray.getPoint().getZ() - globe.getCenter().getZ(), 2), 2) - pow(globe.getRadius(), 2);
			float delta = b * b - 4 * a * c;
			if (delta < 0) {
				return rt::FloatVec3(0.0f, 0.0f, 0.0f);
			}
			else if (delta > 0) {
				float t1 = (-b + std::sqrt(delta)) / (2 * a);
				float t2 = (-b - std::sqrt(delta)) / (2 * a);
				//不可能=0,不单独写了
				if (t1 < 0) {
					return rt::FloatVec3(0.0f, 0.0f, 0.0f);
				}
				else if (t2 < 0) {
					rt::FloatVec3 point = ray.pointAtParameter(t1);
					depth++;
					Ray lightRay = Ray(point, lightPos);
					if (std::abs(globe.getColor().getX() - 1.0f) <= EPSILON) {
						bool lightUp = examine(globes, lightRay);
						if (lightUp) {
							return globe.getColor()*globe.getNormal(lightRay.getDirection())
						}
						else {
							return rt::FloatVec3(0.0f, 0.0f, 0.0f);
						}
					}
					else {

					}
				}
				else if (t1 > 0 && t2 > 0) {
					rt::FloatVec3 point = ray.pointAtParameter(t2);
					depth++;
					//准备反射！
				}
			}
			else {
				float t = -b / (2 * a);
				depth++;
				//准备反射！
			}
		}
	}
}

bool examine(std::vector<Sphere> globes, Ray lightRay) {
	for (int index = 0; index < globes.size(); index++) {
		Sphere globe = globes[index];
		float a = pow(lightRay.getDirection().getX(), 2) + pow(lightRay.getDirection().getY(), 2) + pow(lightRay.getDirection().getZ(), 2);
		float b = 2 * (lightRay.getDirection().getX() * (lightRay.getPoint().getX() - globe.getCenter().getX()) + lightRay.getDirection().getY() * (lightRay.getPoint().getY() - globe.getCenter().getY()) + ray.getDirection().getZ() * (ray.getPoint().getZ() - globe.getCenter().getZ()));
		float c = pow(lightRay.getPoint().getX() - globe.getCenter().getX(), 2) + pow(lightRay.getPoint().getY() - globe.getCenter().getY() + pow(lightRay.getPoint().getZ() - globe.getCenter().getZ(), 2), 2) - pow(globe.getRadius(), 2);
		float delta = b * b - 4 * a * c;
		if (delta >= 0) {
			return false;
		}
	}
	return true;
}