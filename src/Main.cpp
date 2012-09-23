#include <iostream>
#include <cstdio>

#include "Math/Matrix.h"

int main(int argc, char** argv)
{
	std::cout << "Renderfarm 0.1a - by Leon Rodenburg" << std::endl;

	RFMath::Matrix mat;
	mat.Translate(RFMath::Vector3(10.0f, 1.0f, 80.0f));

	std::cout << mat << std::endl;

	std::getchar();
	return 0;
}