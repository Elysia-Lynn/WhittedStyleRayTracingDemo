// WhittedStyleRayTracingDemo.cpp: 定义应用程序的入口点。
//

#include "WhittedStyleRayTracingDemo.h"

using namespace std;

int regulate(int);

int main()
{
	const int width = 150;
	const int height = 100;
	std::ofstream out("image.ppm");
	out << "P3\n" << width << " " << height << "\n255\n";

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int r = 1;
			int g = 1;
			int b = 1;
			out << regulate(r) << " " << regulate(g) << " " << regulate(b)<<"\n";
		}
	}

	std::cout << "And that is all.";
	return 0;
}

int regulate(int a) {
	return a * 255.99;
}