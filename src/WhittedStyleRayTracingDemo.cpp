// WhittedStyleRayTracingDemo.cpp: 定义应用程序的入口点。
//

#include "WhittedStyleRayTracingDemo.h"

#define EPSILON 1e-4f
#define LIMIT 3
//#define DEBUG

int regulate(float);
rt::FloatVec3 calculateColor(std::vector<Sphere>, Ray,int,rt::FloatVec3&);
float intersection(Sphere globe, Ray ray);
Ray reflection(Sphere globe, rt::FloatVec3 point);

const rt::FloatVec3 cameraPos = rt::FloatVec3(0.0f, 0.0f, 0.0f);
const rt::FloatVec3 lightPos = rt::FloatVec3(0.0f, 1.0f, -2.5f);

int main()
{
	std::vector<Sphere>globes;
#ifndef DEBUG

	globes.emplace_back(Sphere(rt::FloatVec3(0.0f, -100.5f, -4.5f),
		rt::FloatVec3(0.5f, 0.5f, 0.5f),
		99.0f, rt::FloatVec3(1.0f, 0.0f, 0.0f),
		1.0f));
	globes.emplace_back(Sphere(rt::FloatVec3(-1.0f, 0.0f, -4.5f),
		rt::FloatVec3(0.8f, 0.3f, 0.7f),
		0.5f, rt::FloatVec3(0.1f, 0.9f, 0.0f),
		1.0f));
	globes.emplace_back(Sphere(rt::FloatVec3(0.0f, 0.0f, -4.5f),
		rt::FloatVec3(1.0f, 1.0f, 1.0f),
		0.3f, rt::FloatVec3(0.0f, 0.1f, 0.9f),
		1.5f));

#endif
	globes.emplace_back(Sphere(rt::FloatVec3(1.0f, 0.0f, -4.5f),
		rt::FloatVec3(0.8f, 0.1f, 0.1f),
		0.5f, rt::FloatVec3(0.8f, 0.2f, 0.0f),
		1.0f));

	const float imagePlaneZ = -1.0f;
	const int width = 150;
	const int height = 100;
	//可改进点：pixelLength可以用一个函数来根据cameraPos width height imagePlaneZ计算得出
	const float pixelLength=0.005;		

	std::ofstream out("image.ppm");
	out << "P3\n" << width << " " << height << "\n255\n";

	for (int j = height-1; j >= 0; j--) {
		for (int i = 0; i < width; i++) {
			float pixelCentreX = (i - width / 2.0 + 0.5) * pixelLength;
			float pixelCentreY = (j - height / 2.0 + 0.5) * pixelLength;
			rt::FloatVec3 pixelCentrePos = rt::FloatVec3(pixelCentreX,pixelCentreY,imagePlaneZ);
			Ray ray = Ray(cameraPos,pixelCentrePos);

			rt::FloatVec3 rgb = rt::FloatVec3(0.0f, 0.0f, 0.0f);
			//在这里我们使用了深度来防无限循环，也可以用能量来衡量，后面试试（注意到能量不能单独用，比方说两个镜面对弹，那真是完了）
			int depth = 0;

			rgb = calculateColor(globes, ray, depth, rgb);
			
			int r = regulate(rgb.getX());
			int g = regulate(rgb.getY());
			int b = regulate(rgb.getZ());
			out << r << " " << g << " " << b<<"\n";
		}
	}

	std::cout << "And that is all.";
	return 0;
}

int regulate(float a) {
	if (a < 0)
		a = 0;
	else if (a > 1)
		a = 1;
	return a * 255.99;
}

//这个函数将返回最终的颜色值，主要功能是计算现在这条光线能与哪个globe相交，并得出交点
rt::FloatVec3 calculateColor(std::vector<Sphere> globes, Ray ray,int depth,rt::FloatVec3& rgb) {
	if (depth >= LIMIT) {
		return rt::FloatVec3(0.0f,0.0f,0.0f);
	}
	else {
		int index =-1;
		float t=1e9f;
		for (int i = 0; i < globes.size(); i++) {
			Sphere globe = globes[i];
			float t1 = intersection(globe, ray);
			if (t1 < t) {
				if (t1 <=0 ) {
					;
				}
				else {
					t = t1;
					index = i;
				}
			}
		}
		if (index == -1) {
			return rt::FloatVec3(0.0f, 0.0f, 0.0f);
		}
		else {
#ifdef DEBUG
			return rt::FloatVec3(1.0f, 1.0f, 1.0f);
#endif // DEBUG

			Sphere globe = globes[index];
			rt::FloatVec3 point = ray.pointAtParameter(t);

			depth++;
			//这个东西写在这颇为尴尬啊，后面有的地方用了它有的地方直接用point重算了一遍，anyway
			Ray lightRay = Ray(point, lightPos);
			float distance = point.distance(lightPos);
			Ray reflectionLight = reflection(globe, point);
			float cosine = lightRay.getDirection().cosine(reflectionLight.getDirection());
			rt::FloatVec3 specular = calculateColor(globes, reflectionLight, depth, rgb).multiply(globe.getReflectivity().getY()).multiply(pow(cosine, 200)).multiply(1.0f + distance);

			bool lightUp = true;
			for (int i = 0; i < globes.size(); i++) {
				Sphere thisGlobe = globes[i];
				if (intersection(thisGlobe, lightRay)) {
					lightUp = false;
					break;
				}
			}
			//如果有问题排查这里方向对不对，以及是不是有负数
			if (lightUp) {
				rt::FloatVec3 diffuse = globe.getColor().multiply(globe.getNormal(point).cosine(lightRay.getDirection())).multiply(1.0f + distance).multiply(globe.getReflectivity().getX());
				if (std::abs(globe.getRefraction() - 1.0f) <= EPSILON) {
					return diffuse + specular;
				}
				else {
					//rt::FloatVec3 refraction=
					return diffuse + specular;
				}
			}
			else {
				if (std::abs(globe.getRefraction() - 1.0f) <= EPSILON) {
					return specular;
				}
				else {
					//rt::FloatVec3 refraction=
					return specular;
				}
			}

		}
	}
}

float intersection(Sphere globe,Ray ray) {
		float a = pow(ray.getDirection().getX(), 2) + pow(ray.getDirection().getY(), 2) + pow(ray.getDirection().getZ(), 2);
		float b = 2 * (ray.getDirection().getX() * (ray.getPoint().getX() - globe.getCenter().getX()) + ray.getDirection().getY() * (ray.getPoint().getY() - globe.getCenter().getY()) + ray.getDirection().getZ() * (ray.getPoint().getZ() - globe.getCenter().getZ()));
		float c = pow(ray.getPoint().getX() - globe.getCenter().getX(), 2) + pow(ray.getPoint().getY() - globe.getCenter().getY(),2) + pow(ray.getPoint().getZ() - globe.getCenter().getZ(), 2)- pow(globe.getRadius(), 2);
		float delta = b * b - 4 * a * c;
		if (delta < 0) {
			return 0;
		}
		else if (delta > 0) {
			float t1 = (-b + std::sqrt(delta)) / (2 * a);
			float t2 = (-b - std::sqrt(delta)) / (2 * a);
			//不可能=0,不单独写了
			if (t1 < 0) {
				return 0;
			}
			else if (t2 < 0) {
				return t1;
			}
			else if (t1 > 0 && t2 > 0) {
				return t2;
			}
			else
				return 0;
		}
		else {
			if (b >= 0) {
				return 0;
			}
			else {
				return -b / (2 * a);
			}
		}
}

//这个函数返回接下来反射的光线
Ray reflection(Sphere globe, rt::FloatVec3 point) {
	Ray lightRay = Ray(point, lightPos);
	rt::FloatVec3 normal = globe.getNormal(point);
	float a = normal.getX();
	float b = normal.getY();
	float c = normal.getZ();
	float pointX = point.getX();
	float pointY = point.getY();
	float pointZ = point.getZ();
	float x0 = point.getX() + a;
	float y0 = point.getY() + b;
	float z0 = point.getZ() + c;
	float rayX = lightRay.getDirection().getX();
	float rayY = lightRay.getDirection().getY();
	float rayZ = lightRay.getDirection().getZ();
	float right = a * (x0 - pointX) + b * (y0 - pointY) + c * (z0 - pointZ);
	float left = a * rayX + b * rayY + c * rayZ;
	float t = right / left;
	float x1 = pointX + t * rayX;
	float y1 = pointY + t * rayY;
	float z1 = pointZ + t * rayZ;
	float x2 = 2 * x0 - x1;
	float y2 = 2 * y0 - y1;
	float z2 = 2 * z0 - z1;
	rt::FloatVec3 reflectionPoint = rt::FloatVec3(x2, y2, z2);
	return Ray(point, reflectionPoint);
}

//这个函数返回接下来折射的光线（注意区分球内部球外部）
//Ray refract(Sphere globe, rt::FloatVec3 point) {
	
//}