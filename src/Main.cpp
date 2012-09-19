#include <iostream>
#include <cstdio>

#include "Math/Vector.h"

int main(int argc, char** argv)
{
	std::cout << "Renderfarm 0.1a - by Leon Rodenburg" << std::endl;

	RFMath::Vector vec1(0.0f, 0.0f, 10.0f);
	RFMath::Vector vec2(1.0f, 0.0f, 0.0f);
	RFMath::Vector vec3(0.0f, 0.0f, 100.0f);

	vec1.Normalize();
	vec2.Normalize();
	vec3.Normalize();
	
	RFMath::Vector vec4 = vec1.Cross(vec3);
	bool vec4result = vec4.IsZero(); // Should be true because pointing in same direction
	float float1 = vec1.Dot(vec2); // Should be 0 because they are perpendicular
	
	std::cout << vec4result << std::endl << float1 << std::endl;

	std::getchar();
	return 0;
}