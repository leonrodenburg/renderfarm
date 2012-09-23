#include <iostream>
#include <cstdio>

#include "Math/Matrix.h"

int main(int argc, char** argv)
{
	std::cout << "Renderfarm 0.1a - by Leon Rodenburg" << std::endl;

	RFMath::Matrix mat;
	mat.Translate(RFMath::Vector3(10.0f, 1.0f, 80.0f));

	RFMath::Matrix mat2;
	mat2.Translate(RFMath::Vector3(0.11f, 0.11f, 0.11f));
	std::cout << (mat * mat2) << std::endl;

	std::getchar();
	return 0;
}