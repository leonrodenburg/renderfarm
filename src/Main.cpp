#include "Core/Kernel.h"

#include "Geometry/World.h"
#include "Geometry/Cube.h"

#include <iostream>
#include <cstdio>
//#include <vld.h> // Visual Leak Detector (http://vld.codeplex.com/)

int main(int argc, char** argv)
{
    std::cout << "Renderfarm 0.1a - by Leon Rodenburg" << std::endl;

    // Create world
    RFGeometry::World world;

    // Add geometry to world
    RFGeometry::Cube cube(10.0f);
    world.AddGeometry(&cube);

    // Create kernel
    RFCore::Kernel kernel(&world);

    // Start the kernel
    kernel.Run();

    std::getchar();
    return 0;
}